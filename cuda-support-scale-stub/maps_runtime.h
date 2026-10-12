/*!
 * \file maps_runtime.h（S2 style shim）
 * \brief native maps 运行时 host API → CUDA runtime 映射。仅 host 侧使用
 *        （scale_flow_glue.cpp / scale_runtime.cpp / .sc 内的 sc_* 启动包装）。
 *        简化项登记：1 rank : 1 device 语义不变；流/事件语义不模拟
 *        （默认流同步语义，与 native 包装里的 mapsDeviceSynchronize 用法相容）。
 */
#pragma once

#include <cuda_runtime.h>

#include <cstddef>
#include <cstdint>

typedef cudaError_t mapsError_t;
#define mapsSuccess cudaSuccess

typedef cudaMemcpyKind mapsMemcpyKind;
#define mapsMemcpyHostToDevice cudaMemcpyHostToDevice
#define mapsMemcpyDeviceToHost cudaMemcpyDeviceToHost
#define mapsMemcpyDeviceToDevice cudaMemcpyDeviceToDevice

inline const char* mapsGetErrorString(mapsError_t e) { return cudaGetErrorString(e); }
inline mapsError_t mapsMalloc(void** p, size_t bytes) { return cudaMalloc(p, bytes); }
inline mapsError_t mapsFree(void* p) { return cudaFree(p); }
inline mapsError_t mapsMemcpy(void* dst, const void* src, size_t bytes, mapsMemcpyKind kind) {
  return cudaMemcpy(dst, src, bytes, kind);
}
inline mapsError_t mapsMemset(void* p, int v, size_t bytes) { return cudaMemset(p, v, bytes); }
inline mapsError_t mapsGetLastError() { return cudaGetLastError(); }
inline mapsError_t mapsDeviceSynchronize() { return cudaDeviceSynchronize(); }
inline mapsError_t mapsGetDeviceCount(int* n) { return cudaGetDeviceCount(n); }
inline mapsError_t mapsSetDevice(int dev) { return cudaSetDevice(dev); }

/*--- style：设备"物理地址"即设备指针值本身（调用点随即将 uint64 强转回
 *    __DDR T*，64 位 CUDA 下自洽；native 侧为 DMA 用的真实物理地址）。 ---*/
inline void mapsMemobjGetPhysicalAddress(const void* p, unsigned long long* out) {
  *out = (unsigned long long)(uintptr_t)p;
}
inline void mapsMemobjGetPhysicalAddress(const void* p, uint64_t* out) {
  *out = (uint64_t)(uintptr_t)p;
}
