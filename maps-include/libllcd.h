#pragma once

#include <aurora_s.h>
#include <aurora_s-intrin.h>
#include "scale.h"
#include "scale_types.h"
#include "device_scale.h"

#if defined(__SCALE_ARCH__)
extern "C" _LIBSCALECXX_INLINE_VISIBILITY int printf(const char *fmt, ...);
#else
extern "C" __device__ int printf(const char *fmt, ...);
#endif

#ifndef STAND_ALONE_PRINTF
//#include <cstdio>
#else
#include "../3rd_party/inc/printf.h"
#endif

#define _LIBLLCD_DEVICE_VISIBILITY __device__

#define USE_DMAFETCHFIFO
#define USE_SCALE_N_MODE

//#define DEBUG
#ifdef DEBUG
#define dbg_print(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_print(fmt, ...) //do nothing
#endif
