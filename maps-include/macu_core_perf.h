/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2026 Smart Logic, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#pragma once

#include <scale.h>

/**
 * NOTE: Just use as the following:
 *
 * #include "macu_core_perf.h"
 * ...
 * {
 *    macu_config_perf_param<DmRegion::SHARED, CommLib::LLCD, 16>();
 *    MACU_CORE_PERF_GUARD;
 *    // code that you want to profile.
 *    {
 *       MACU_CORE_MPU_PERF_GUARD(3); // use 'MACU_CORE_MPU_PERF_GUARD_MPUC;' if you want to use mpuc programming model.
 *       // mpu functions those you want to profile.
 *    }
 * }
 */

enum class DmRegion { MEM0, SHARED };
enum class CommLib { LLCD, BUILTIN };

template<DmRegion dm_region = DmRegion::MEM0, CommLib comm_lib = CommLib::LLCD,
         int max_num_threads_per_block_for_share = 4>
__device__ void macu_config_perf_param() {
  // must call this for each thread
  scale_init_maps_profiler_buffer_addr();
}

class [[nodiscard]] MacuSPUPerfGuard {
public:
  __device__ MacuSPUPerfGuard();
  __device__ ~MacuSPUPerfGuard();

  __device__ MacuSPUPerfGuard(const MacuSPUPerfGuard&) = delete;
  __device__ MacuSPUPerfGuard& operator=(const MacuSPUPerfGuard&) = delete;
  __device__ MacuSPUPerfGuard(MacuSPUPerfGuard&&) = delete;
  __device__ MacuSPUPerfGuard& operator=(MacuSPUPerfGuard&&) = delete;
};

class [[nodiscard]] MacuMPUPerfGuard {
public:
  explicit __device__ MacuMPUPerfGuard(unsigned mreg_idx);
  __device__ ~MacuMPUPerfGuard();

  __device__ MacuMPUPerfGuard() = delete;
  __device__ MacuMPUPerfGuard(const MacuMPUPerfGuard&) = delete;
  __device__ MacuMPUPerfGuard& operator=(const MacuMPUPerfGuard&) = delete;
  __device__ MacuMPUPerfGuard(MacuMPUPerfGuard&&) = delete;
  __device__ MacuMPUPerfGuard& operator=(MacuMPUPerfGuard&&) = delete;
};

class [[nodiscard]] MacuMPUCPerfGuard {
public:
  __device__ MacuMPUCPerfGuard();
  __device__ ~MacuMPUCPerfGuard();

  __device__ MacuMPUCPerfGuard(const MacuMPUCPerfGuard&) = delete;
  __device__ MacuMPUCPerfGuard& operator=(const MacuMPUCPerfGuard&) = delete;
  __device__ MacuMPUCPerfGuard(MacuMPUCPerfGuard&&) = delete;
  __device__ MacuMPUCPerfGuard& operator=(MacuMPUCPerfGuard&&) = delete;
};

#define MACU_CORE_CONCAT_IMPL(name, line) name##line
#define MACU_CORE_CONCAT(name, line) MACU_CORE_CONCAT_IMPL(name, line)

#define MACU_CORE_PERF_GUARD MacuSPUPerfGuard MACU_CORE_CONCAT(__macu_spu_perf_guard_, __LINE__)
#define MACU_CORE_MPU_PERF_GUARD(mreg_idx) MacuMPUPerfGuard MACU_CORE_CONCAT(__macu_mpu_perf_guard_, __LINE__)(mreg_idx)
#define MACU_CORE_MPU_PERF_GUARD_MPUC MacuMPUCPerfGuard MACU_CORE_CONCAT(__macu_mpuc_perf_guard_, __LINE__)