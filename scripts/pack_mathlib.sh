#!/usr/bin/env bash
# pack_mathlib.sh — 从厂商 libnonlinear 归档生成工作区共享的 MPU 数学库产物（mathlib/）：
#   mathlib/libaurora_nolinear_math_bundled.a   mpu_sqrt 链的 offload bundle 归档
#   mathlib/mathlib-config/{sqrt_config.h,rsqrt_config.h,manifest.json}
#
# 背景（KB mpu_library.md）：
# - 厂商 libaurora_nolinear_math.a 内是裸设备对象（sqrt.spu.o / sqrt.mpu.o /
#   mpu_sqrt.m.o），不符合 clang offload 链接模型——驱动只认带
#   __CLANG_OFFLOAD_BUNDLE__ 段的对象。打包 = 把设备对象**原样**（目标码不动）
#   嵌进 host 壳：mA.o = stub + sqrt.spu.o + sqrt.mpu.o，mB.o = stub +
#   空 aurora_s 填充 + mpu_sqrt.m.o（sqrt.mpu.o 的 UND mpu_sqrt.m 由它提供）。
# - 配置表（sqrt 1344B / rsqrt 1024B）的库 getter 返回构建期烤死的绝对地址
#   0x1200000000，访问即 AMMU RANGE FAULT；配置字节是 .spu.o 的常量 section，
#   只读 dump 出来与 getter 内容一致。
#
# 用法：bash scripts/pack_mathlib.sh [厂商归档] [输出目录]
#   归档默认 $HOST_DRIVER_DIR/mathlib/libnonlinear/lib/release/libaurora_nolinear_math.a
#   输出默认 mathlib/（产物随仓库入库，构建期无需厂商库）。
# 依赖：ar / cc / python3 / aurora 工具链（clang-offload-bundler、clang++、
#   llvm-objcopy，取 $SCALE_TOOLCHAIN_ROOT 或 $HOST_DRIVER_DIR/toolchain）。
#   工具链 llvm 组件需要 libtinfo.so.5；宿主缺失时自动用
#   ../.deps/libtinfo-compat 兜底（若存在）。
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

DRIVER_DIR="${HOST_DRIVER_DIR:-/home/tyb/driver}"
ARCHIVE="${1:-${DRIVER_DIR}/mathlib/libnonlinear/lib/release/libaurora_nolinear_math.a}"
OUT="${2:-${ROOT}/mathlib}"

TC="${SCALE_TOOLCHAIN_ROOT:-${DRIVER_DIR}/toolchain}/bin"
BUNDLER="${TC}/clang-offload-bundler"
AURORA_CXX="${TC}/clang++"
OBJCOPY="${TC}/llvm-objcopy"
if [[ -d "${ROOT}/../.deps/libtinfo-compat" ]]; then
  export LD_LIBRARY_PATH="${ROOT}/../.deps/libtinfo-compat${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"
fi

[[ -f "${ARCHIVE}" ]] || { echo "找不到数学库归档: ${ARCHIVE}" >&2; exit 1; }
for t in "${BUNDLER}" "${AURORA_CXX}" "${OBJCOPY}"; do
  [[ -x "${t}" ]] || { echo "找不到工具链组件: ${t}" >&2; exit 1; }
done

WORK="$(mktemp -d)"
trap 'rm -rf "${WORK}"' EXIT
mkdir -p "${OUT}/mathlib-config"

# ---- 1. 提取设备对象（原样，不重编） ----
for m in sqrt.spu.o sqrt.mpu.o mpu_sqrt.m.o; do
  ar p "${ARCHIVE}" "${m}" > "${WORK}/${m}"
done

# ---- 2. host 壳 + 空 aurora_s 填充（mB 无 SPU 侧对象，bundle 需全目标） ----
printf 'int __su2_mathlib_bundle_stub;\n' > "${WORK}/stub.c"
${CC:-cc} -c "${WORK}/stub.c" -o "${WORK}/stub.o"
printf '' > "${WORK}/empty.s"
"${AURORA_CXX}" --target=scale-aurora_s -c "${WORK}/empty.s" -o "${WORK}/empty_s.o"

# ---- 3. 打 bundle 并归档 ----
"${BUNDLER}" --type=o \
  --targets=host-x86_64-unknown-linux-gnu,scale-aurora_s,scale-aurora_m \
  --inputs="${WORK}/stub.o,${WORK}/sqrt.spu.o,${WORK}/sqrt.mpu.o" \
  --outputs="${WORK}/mA.o"
"${BUNDLER}" --type=o \
  --targets=host-x86_64-unknown-linux-gnu,scale-aurora_s,scale-aurora_m \
  --inputs="${WORK}/stub.o,${WORK}/empty_s.o,${WORK}/mpu_sqrt.m.o" \
  --outputs="${WORK}/mB.o"
ar rcs "${OUT}/libaurora_nolinear_math_bundled.a" "${WORK}/mA.o" "${WORK}/mB.o"

# ---- 4. 配置表提取（只读 dump 常量 section，生成 host 常量头） ----
for name in sqrt rsqrt; do
  ar p "${ARCHIVE}" "${name}.spu.o" > "${WORK}/${name}.raw.spu.o"
  if [[ "${name}" == sqrt ]]; then
    section='.DDR.rodata.4.ddr_sqrt_config.@public'
  else
    section='.DDR.rodata.4.config_ddr.@public'
  fi
  "${OBJCOPY}" --dump-section "${section}=${WORK}/${name}.config.bin" "${WORK}/${name}.raw.spu.o"
done

python3 - "${WORK}" "${OUT}/mathlib-config" <<'PY'
from pathlib import Path
import hashlib, json, sys
work, out = Path(sys.argv[1]), Path(sys.argv[2])
manifest = {}
for name, size, symbol in [('sqrt', 1344, 'vendor_sqrt_config'),
                           ('rsqrt', 1024, 'vendor_rsqrt_config')]:
    data = (work / (name + '.config.bin')).read_bytes()
    if len(data) != size:
        raise SystemExit(f'配置表大小异常: {name} {len(data)} != {size}')
    lines = []
    for i in range(0, len(data), 16):
        lines.append('  ' + ','.join(str(b) for b in data[i:i+16]) + ',')
    (out / (name + '_config.h')).write_text(
        f'/* 自动生成（scripts/pack_mathlib.sh）：libnonlinear {name} 配置表，\n'
        f'   从 .spu.o 常量 section 只读提取，sha256 见同目录 manifest.json。勿手改。 */\n'
        f'static const unsigned char {symbol}[] = {{\n' + '\n'.join(lines) + '\n};\n')
    manifest[name] = {'size': size, 'sha256': hashlib.sha256(data).hexdigest()}
(out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
print(json.dumps(manifest))
PY

echo "已生成 ${OUT}/libaurora_nolinear_math_bundled.a 与 mathlib-config/{sqrt,rsqrt}_config.h"
