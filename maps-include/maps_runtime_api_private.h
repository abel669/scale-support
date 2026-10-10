#ifndef MAPS_RUNTIME_API_PRIVATE_H_
#define MAPS_RUNTIME_API_PRIVATE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 

#include "maps_runtime_api.h"

typedef struct apcRunningData {
    uint64_t runingCnt;
    uint64_t periodicCnt;
} apcRunningData_t;

#define PROF_KERNEL_MAX 4
typedef struct apcProfilingData {
    uint64_t ape_specified_kernel_selected_warp_cnt;
    uint64_t ape_specified_kernel_stall_warp_cnt;
    uint64_t ape_warppool_empty_cnt;
    uint64_t ape_dma_starved_cnt;
    uint64_t ape_mpu_starved_cnt;
    uint64_t ape_spu_starved_cnt;
    uint64_t ape_dm_wr_rd_blocked_cnt;
    uint64_t warp_cnt;
    uint64_t ape_eligible_warp_cnt;
    uint64_t ape_fast_dispatch_stall_cnt;
    uint64_t ape_wg_barrier_stall_cnt;
    uint64_t ape_mpu_stall_cnt;
    uint64_t ape_dma_stall_cnt;
    uint64_t ape_cluster_barrier_stall_cnt;
    uint64_t ape_pre_pass_stall_cnt;
    uint64_t ape_dshm_stall_cnt;
    uint64_t ape_stalled_type0_cnt;
    uint64_t ape_fast_dispatch_resume_cnt;
    uint64_t ape_wg_barrier_resume_cnt;
    uint64_t ape_mpu_resume_cnt;
    uint64_t ape_dma_resume_cnt;
    uint64_t ape_cluster_barrier_resume_cnt;
    uint64_t ape_pre_pass_resume_cnt;
    uint64_t ape_dshm_resume_cnt;
    uint64_t ape_resumed_type0_cnt;
} apcProfilingData_t;

typedef enum cmdPktType {
    cmd_memcpy               = 0,
    cmd_nop                  = 1,
    cmd_compute_kernel       = 2
} cmdPktType_t;

typedef struct cmdPktParams {
    struct {
        uint32_t packet_length : 8;
        uint32_t qfc_present : 1;
        uint32_t fence : 1;
        uint32_t wait_event : 1;
        uint32_t write_event : 1;
        uint32_t callback_enable : 1;
        uint32_t set_event : 1;
        uint32_t set_event_mode : 1; // hal_cp_set_event_mode
        uint32_t time_stamp_enable : 1;
        uint32_t wait_event_mode : 3;
        uint32_t reserved : 3;
        uint32_t cmd_priority : 2;
        uint32_t cmd_type : 8;
    } header;
    struct {
        uint32_t wait_fence_count_id : 9;
        uint32_t qfc_wait_flag : 1;
        uint32_t qfc_wait_mode : 2;
        uint32_t qfc_wait_value_8bit : 8;
        uint32_t qfc_set_flag : 1;
        uint32_t qfc_set_timing : 1;
        uint32_t qfc_set_mode : 2;
        uint32_t qfc_set_value_8bit : 8;
    } qfc_cfg;
    struct {
        uint32_t src_addr_msb;
        uint32_t src_addr_lsb;
        uint32_t dst_addr_msb;
        uint32_t dst_addr_lsb;
        uint32_t copy_size;
        uint32_t tran_type;
        uint32_t reserved;
    } memcpy;
    uint32_t qfc_cfg_dw; // dword4, present when qfc_present = 1
    uint32_t qfcId;
    uint32_t qfcIndex;
    uint32_t cmdId;
    uint32_t object_addr_msb;
    uint32_t object_addr_lsb;
    uint64_t event_id;
    uint32_t object_data_msb;
    uint32_t object_data_lsb;
    uint32_t dependent_queue_id;
    struct {
        uint64_t kernel_args0;
    } kernelParam;
    struct {
        uint32_t kernel_code_addr_lsb;
        uint32_t kernel_code_addr_msb;
        bool kernel_code_addr_enable;
        uint32_t ape_num;
        bool ape_num_enable;
        uint32_t warp_size;
        bool warp_size_enable;
        uint32_t ape_mask;
        bool ape_mask_enable;
        uint32_t per_warp_size_0;
        bool per_warp_size_0_enable;
        bool enableLaunchParam;
    } launchParam;
    bool     autoGenerate;
    bool isInvaliedFormat;
    bool useRawCmd;
    bool NoPadding;
    void *cmdPkt;
} cmdPktParams_t;

#define READY_TIMESTAMP_NUM 8
typedef struct apcKernelProfilingData {
    struct apcProfilingData apc_profiling;
    uint64_t periodic_cnt;
/***********************************************************************************
*profiling_ready_stamp[63:60] evnet_id
*4'd1: Specified Kernel_id [0] and Workgroup_id [0] Ready TimeStamp;
*4'd2: Specified Kernel_id [1] and Workgroup_id [1] Ready TimeStamp;
*4'd3: Specified Kernel_id [2] and Workgroup_id [2] Ready TimeStamp;
*4'd4: Specified Kernel_id [3] and Workgroup_id [3] Ready TimeStamp;
*4'd5: Specified Kernel_id [0], Workgroup_id  [0] and Warp_id [0] Ready TimeStamp;
*4'd6: Specified Kernel_id [1], Workgroup_id  [1] and Warp_id [1] Ready TimeStamp;
*4'd7: Specified Kernel_id [2], Workgroup_id  [2] and Warp_id [2] Ready TimeStamp;
*4'd8: Specified Kernel_id [3], Workgroup_id  [3] and Warp_id [3] Ready TimeStamp;
***********************************************************************************/
    uint64_t ready_stamp[READY_TIMESTAMP_NUM];
} __attribute__((packed))apcKernelProfilingData_t;

#if __GUNC__
#pragma GCC visibility push(default)
#endif

#ifdef __cplusplus
extern "C" {
#endif

mapsError_t mapsStartKernelProfiling(
    mapsStream_t stream, uint32_t apcMask, uint32_t *kernelIds, uint32_t *workGropIds, uint32_t *warpIds);
mapsError_t mapsReadKernelProfiling(mapsStream_t stream, uint32_t apcMask, void *kernelProfData);
mapsError_t mapsStopKernelProfiling(mapsStream_t stream, uint32_t apcMask);
mapsError_t mapsStartRunningPerfCnt(int deviceId, uint32_t apcMask);
mapsError_t mapsReadRunningPerfCnt(int deviceId, uint32_t apcMask, apcRunningData_t *runningCnts);
mapsError_t mapsStopRunningPerfCnt(int deviceId, uint32_t apcMask);
mapsError_t mapsStartCbWarpPerfAxi(int deviceId, uint32_t cbMask);
mapsError_t mapsStopCbWarpPerfAxi(int deviceId, uint32_t cbMask);
mapsError_t mapsStartCbWarpPerfSdb(int deviceId, uint32_t cbMask);
mapsError_t mapsStopCbWarpPerfSdb(int deviceId, uint32_t cbMask);
mapsError_t mapsSetProfilerBufferEx(void* dev_buffer, mapsStream_t stream __dparm(0));
mapsError_t mapsRecordKernelPerfTime(mapsStream_t stream, uint32_t kernelId);
mapsError_t mapsGetKernelPerfTime(mapsStream_t stream, uint64_t* ns, uint64_t *cycle);
mapsError_t mapsEventGetTimestamp(uint64_t* ns, uint64_t *timestamp, mapsEvent_t event); // ms is the runtime calculated  by the dev based on the timestamp
mapsError_t mapsStreamEmitTestCmd(mapsStream_t stream, cmdPktType_t type, cmdPktParams_t* params);
mapsError_t mapsReadHWFrequency(uint64_t *freq);
mapsError_t mapsDeviceGetPhysicId(int deviceId, int *physicId);

#ifdef __cplusplus
}
#endif

#if __GUNC__
#pragma GCC visibility pop
#endif

#endif // MAPS_RUNTIME_API_PRIVATE_H_
