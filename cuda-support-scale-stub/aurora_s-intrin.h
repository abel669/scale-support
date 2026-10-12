/*!
 * \file aurora_s-intrin.h（S2 style shim）
 * \brief native 工具链的 SPU intrinsic 总头在 style 下为空——sympic 的
 *        inner_split_pass.kernel_runtime.sc 无条件包含它；本代码不使用
 *        _vel_* 等 SPU intrinsic（SU2/SymPIC 均零调用），转发到核心即可。
 */
#pragma once

#include "_compat_core.h"
