/* S2 style shim for libnonlinear "sqrt.h" — mpu_sqrt 逐 lane IEEE sqrt 桩
 * （native 库实测 IEEE 正确舍入；配置表忽略；地址为裸指针，无 int DM ABI）。 */
#pragma once
#include "_compat_core.h"
