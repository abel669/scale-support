#pragma once
#include <cstdint>
#include "libllcd.h"
#include "dma_param.h"

struct sdma_putget_para {
    uint8_t local_slm_id;
    uint8_t remote_slm_id;
    uint8_t local_asid;
    uint8_t remote_asid;
    uint16_t local_lut_index;
    uint16_t remote_lut_index;
    bool     non_posted{false};
    uint8_t  rsd[7];
};
static_assert(sizeof(sdma_putget_para) == 16, "sdma_putget_para must be 16 Bytes");

struct cpl_handle {
	uint32_t flag;
	uint32_t pad[7];
} __attribute__((aligned(32)));

_LIBLLCD_DEVICE_VISIBILITY
int sdma_copy_3d(SdmaCmdData& cmd_data, aisle_t path, DMAHandle& handle, DmaFetchData &fetch_data);

_LIBLLCD_DEVICE_VISIBILITY
int sdma_memcpy_async(__DDR void *dst, __DDR const void *src, uint64_t size, aisle_t path, uint8_t asid);

_LIBLLCD_DEVICE_VISIBILITY
int sdma_memcpy(__DDR void *dst, __DDR const void *src, uint64_t size, uint8_t asid=0);

_LIBLLCD_DEVICE_VISIBILITY
int sdma_slm_write(__DDR void *remote_dst, __DDR const void *local_src, uint64_t size, uint8_t local_slm_id, uint16_t remote_lut_index,
                   uint8_t local_asid, uint8_t remote_asid);

_LIBLLCD_DEVICE_VISIBILITY
int sdma_slm_read(__DDR void *local_dst, __DDR const void *remote_src, uint64_t size, uint8_t local_slm_id, uint8_t remote_slm_id,
                  uint16_t local_lut_index, uint16_t remote_lut_index, uint8_t local_asid, uint8_t remote_asid, v8u32 *peer_cmd);

_LIBLLCD_DEVICE_VISIBILITY
void set_slm_order_region_range(uint8_t slm_id, uint8_t region_id, uint64_t region_start, uint64_t region_size);

_LIBLLCD_DEVICE_VISIBILITY
void set_sdma_conf_register_to_slm_order_region(void);

_LIBLLCD_DEVICE_VISIBILITY
int sdma_slm_write_local_done(__DDR void *dst, __DDR const void *src, uint64_t size, uint8_t local_slm_id, uint8_t asid);

_LIBLLCD_DEVICE_VISIBILITY
void sdma_slm_put(__DDR void *remote_dst, __DDR const void *local_src, uint64_t size, sdma_putget_para &putget_para);

_LIBLLCD_DEVICE_VISIBILITY
void sdma_slm_get(__DDR void *local_dst, __DDR const void *remote_src, uint64_t size, sdma_putget_para &putget_para);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t poll_completion_flag(cpl_handle &handle);

_LIBLLCD_DEVICE_VISIBILITY
uint64_t local_dm_address_to_global_address(uint32_t dm_addr);

_LIBLLCD_DEVICE_VISIBILITY
uint64_t get_sm_slm_imm_value_addr(void);

_LIBLLCD_DEVICE_VISIBILITY
void sm_slm_imm_value_init(void);

_LIBLLCD_DEVICE_VISIBILITY
void set_apc_dm_region_to_slm_order_region(void);


