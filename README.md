# scale-support — SCALE 平台跨项目共享组件

从 new-ai 工作区拆分（2026-10-10，方案 B：独立仓、单一事实源）。

| 目录 | 内容 |
|---|---|
| `cuda-support-scale-stub/` | SCALE→CUDA shim/stub 头：`maps*`/MPU 原语/`__memX__` 地址空间等映射为 CUDA 语义，让 .sc 源码可被 nvcc 双编译（style 后端）。各头注释登记 shim 简化项 |
| `mathlib/` | MPU 数学库产物：`libaurora_nolinear_math_bundled.a`（clang offload bundle 归档，驱动只认 bundled）+ `mathlib-config/{sqrt_config.h,rsqrt_config.h,manifest.json}`（配置表） |
| `maps-include/` | maps 运行时头（native SCALE 编译期需要） |
| `scripts/pack_mathlib.sh` | mathlib 产物再生：从厂商 libnonlinear 归档（`$HOST_DRIVER_DIR/mathlib/...`）提取设备对象重打 bundle + 提取配置表。换厂商库版本时运行 |

## 使用方

- new-ai 工作区：以子模块挂根目录 `scale-support/`（projects/su2 与 scaleExamples 共用）
- projects/su2 standalone：CMake 选项 `-DSCALE_SUPPORT_DIR=<本仓路径>`，或把本仓作为
  嵌套子模块放 `su2/externals/scale-support/`（自动探测）

注意：mpu_sqrt 等的头文件接口（sqrt.h 等）仍在 SCALE 驱动包内（`$HOST_DRIVER_DIR/mathlib/
libnonlinear/inc`），属正常外部依赖；本仓只携带构建期必需的产物与 shim。
