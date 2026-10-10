/*!
 * \file _compat_core.h
 * \brief S2 style（SCALE 风格 CUDA）shim 核心：让 src/scale/*.sc 单源码在 nvcc 下
 *        编译运行。以早期 tests/grad_gg/scale_compat.h 为底扩展为完整算符集
 *        （底本已随 tests→cudaExamples 重构删除，本目录是唯一 shim 事实源，
 *        亦供 scaleExamples/ 的 style 目标复用）。
 *        与 native SCALE 头的对应关系：scale.h / aurora.h / cooperative_groups.h /
 *        maps_runtime.h / scale/barrier / llvm/aurora_s.h / sqrt.h 均为薄转发到本文件。
 * \note 已登记的 shim 简化项（nvcc 通过 ≠ native 正确，KB cuda2scale_style）：
 *         - __mem0__..__mem3__ / __DDR / KERNEL_M / MPU_SYNC 为 no-op：
 *           地址空间与 SPU/MPU 分工边界不被验证；
 *         - memcpy_async 为同步 memcpy，scale::barrier 为 no-op：DMA 异步调度、
 *           完成等待、barrier 语义均不被验证（native 侧 memcpy_async 后必须
 *           arrive_and_wait 的纪律要靠结构审查保证）；
 *         - aurora_counter_start/end 为桩（profiling 值恒 0）；
 *         - v8fp64 算术为逐 lane 标量 f64（-fmad=false 下与 native MPU 逐位一致），
 *           例外：除法是 IEEE 正确舍入，native MPU 向量 f64 除法非正确舍入
 *           （~2^-30 相对偏差，契约 bitwise || maxRelDiff<1e-6，shim 不暴露）；
 *         - v8s64 比较产生全 1/全 0 lane 掩码，与 native ordered compare 一致
 *           （NaN 为 false）；位选 (a & keep) | (b & ~keep) 逐 lane 实现，
 *           语义同 C 三元（含符号零）；
 *         - __builtin_sqrt/pow/fmin/fmax 宏映射到 CUDA 的 IEEE 函数；
 *         - mpu_sqrt 桩为逐 lane IEEE sqrt、忽略配置表（native 库实测 IEEE 正确
 *           舍入，64/64 位级一致）；style 下 *_DM_ADDR(x) 为恒等（指针原样传递，
 *           无 native 的 int DM 地址 ABI——各 .sc 的 DM_ADDR 宏按 SU2_SCALE_STYLE 分派）；
 *         - maps_* 运行时映射到 cuda_*（host 侧，1 rank : 1 device 语义不变）。
 *       native 转换删除本目录全部文件，绝不重定义 native 类型（KB type_mapping R1）。
 */
#pragma once

#include <cuda_runtime.h>

#include <cstddef>
#include <cstring>
#include <cmath>

#define __mem0__
#define __mem1__
#define __mem2__
#define __mem3__
#define __DDR
#define KERNEL_M
#define MPU_SYNC() \
  do {             \
  } while (0)

/*--- native 侧 __builtin_* 为工具链内建；style 映射到 CUDA 的 IEEE 实现。 ---*/
#define __builtin_sqrt(x) sqrt(x)
#define __builtin_pow(x, y) pow(x, y)
#define __builtin_fmin(x, y) fmin(x, y)
#define __builtin_fmax(x, y) fmax(x, y)

/*--- 模拟 8-lane f64 向量（KB type_mapping R1：plain struct + 算符重载）。 ---*/
struct v8fp64 {
  double v[8];
};
struct v8s64 {
  long long v[8];
};

#define SC_SHIM_V8_BINOP(op)                                          \
  __host__ __device__ inline v8fp64 operator op(v8fp64 a, v8fp64 b) { \
    v8fp64 r;                                                         \
    for (int i = 0; i < 8; ++i) r.v[i] = a.v[i] op b.v[i];            \
    return r;                                                         \
  }
SC_SHIM_V8_BINOP(+)
SC_SHIM_V8_BINOP(-)
SC_SHIM_V8_BINOP(*)
SC_SHIM_V8_BINOP(/)
#undef SC_SHIM_V8_BINOP

#define SC_SHIM_V8_SCAL(op)                                            \
  __host__ __device__ inline v8fp64 operator op(v8fp64 a, double s) {  \
    v8fp64 r;                                                          \
    for (int i = 0; i < 8; ++i) r.v[i] = a.v[i] op s;                  \
    return r;                                                          \
  }                                                                    \
  __host__ __device__ inline v8fp64 operator op(double s, v8fp64 a) {  \
    v8fp64 r;                                                          \
    for (int i = 0; i < 8; ++i) r.v[i] = s op a.v[i];                  \
    return r;                                                          \
  }
SC_SHIM_V8_SCAL(+)
SC_SHIM_V8_SCAL(-)
SC_SHIM_V8_SCAL(*)
SC_SHIM_V8_SCAL(/)
#undef SC_SHIM_V8_SCAL

__host__ __device__ inline v8fp64& operator+=(v8fp64& a, v8fp64 b) {
  for (int i = 0; i < 8; ++i) a.v[i] += b.v[i];
  return a;
}
__host__ __device__ inline v8fp64& operator-=(v8fp64& a, v8fp64 b) {
  for (int i = 0; i < 8; ++i) a.v[i] -= b.v[i];
  return a;
}
__host__ __device__ inline v8fp64 operator-(v8fp64 a) {
  v8fp64 r;
  for (int i = 0; i < 8; ++i) r.v[i] = -a.v[i];
  return r;
}

/*--- ordered compare → 全 1/全 0 掩码（NaN 为 false，与 native 一致）。 ---*/
#define SC_SHIM_V8_CMP(op)                                            \
  __host__ __device__ inline v8s64 operator op(v8fp64 a, v8fp64 b) {  \
    v8s64 r;                                                          \
    for (int i = 0; i < 8; ++i) r.v[i] = (a.v[i] op b.v[i]) ? ~0LL : 0LL; \
    return r;                                                         \
  }
SC_SHIM_V8_CMP(>)
SC_SHIM_V8_CMP(<)
SC_SHIM_V8_CMP(>=)
SC_SHIM_V8_CMP(<=)
SC_SHIM_V8_CMP(==)
SC_SHIM_V8_CMP(!=)
#undef SC_SHIM_V8_CMP

__host__ __device__ inline v8s64 operator&(v8s64 a, v8s64 b) {
  v8s64 r;
  for (int i = 0; i < 8; ++i) r.v[i] = a.v[i] & b.v[i];
  return r;
}
__host__ __device__ inline v8s64 operator|(v8s64 a, v8s64 b) {
  v8s64 r;
  for (int i = 0; i < 8; ++i) r.v[i] = a.v[i] | b.v[i];
  return r;
}
__host__ __device__ inline v8s64 operator~(v8s64 a) {
  v8s64 r;
  for (int i = 0; i < 8; ++i) r.v[i] = ~a.v[i];
  return r;
}

/*--- 执行域/同步桩（同步模拟，语义不被验证，见头注释登记）。 ---*/
namespace cooperative_groups {
struct thread_block {};
__host__ __device__ inline thread_block this_thread_block() { return {}; }
}  // namespace cooperative_groups

namespace scale {
enum thread_scope { thread_scope_thread, thread_scope_block };
template <thread_scope>
struct barrier {
  __host__ __device__ void arrive_and_wait() {}
};
}  // namespace scale

__host__ __device__ inline void init(scale::barrier<scale::thread_scope_thread>*, int) {}

__host__ __device__ inline void memcpy_async(cooperative_groups::thread_block, void* dst, const void* src,
                                             size_t bytes, scale::barrier<scale::thread_scope_thread>&) {
  memcpy(dst, src, bytes);
}

/*--- SPU cycle counter 桩（native-only，llvm/aurora_s.h）。 ---*/
__host__ __device__ inline void aurora_counter_start() {}
__host__ __device__ inline float aurora_counter_end() { return 0.0f; }

/*--- mpu_sqrt 桩（对应 libnonlinear 的 KERNEL_M mpu_sqrt；native 实测 IEEE
 *    正确舍入。style 下配置表忽略、地址为裸指针——各 .sc 的 *_DM_ADDR 宏在
 *    SU2_SCALE_STYLE 下恒等）。 ---*/
__host__ __device__ inline void mpu_sqrt(int len, const void* in_addr, const void* in_cfg_addr,
                                         void* out_addr) {
  (void)in_cfg_addr;
  const double* in = (const double*)in_addr;
  double* out = (double*)out_addr;
  for (int i = 0; i < len; ++i) out[i] = sqrt(in[i]);
}

/*--- style-only（登记的 shim 补偿，非简化）：CUDA 动态 shared 超过 48KB 默认上限
 *    必须 cudaFuncSetAttribute opt-in；native SCALE 的 Bank0 预算模型无此概念，
 *    该调用在 native 树不存在（调用点以 SU2_SCALE_STYLE 守卫）。 ---*/
template <typename KernelT>
inline void sc_style_shared_optin(KernelT kernel, size_t bytes) {
  cudaFuncSetAttribute((const void*)kernel, cudaFuncAttributeMaxDynamicSharedMemorySize, (int)bytes);
}
