#pragma once
#include <cstdint>
#include "libllcd.h"
#include "dma_param.h"

_LIBLLCD_DEVICE_VISIBILITY
void set_ape_axi_datapath(uint8_t path_sel_flag, uint8_t is_smq=0);

_LIBLLCD_DEVICE_VISIBILITY
uint8_t apc_id_to_sbuf_id(uint8_t apc_id);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_async(DmaFetchData &fetch_data, deviceMemcpyKind kind, DMAHandle& handle);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_hbm2dm_async(void *dst, __DDR const void *src, uint32_t size, DMAHandle& handle, DmaFetchData &fetch_data);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_dm2hbm_async(__DDR void *dst, const void *src, uint32_t size, DMAHandle& handle, DmaFetchData &fetch_data);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_hbm2hbm_async(__DDR void *dst, __DDR const void *src, uint32_t size, DMAHandle& handle, DmaFetchData &fetch_data);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_dm2dm_bdcast_async(DmaFetchData &fetch_data, DMAHandle& handle);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_local_apc_outband2_async(DmaFetchData &fetch_data, DMAHandle& handle);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_cast_async(DmaFetchData &fetch_data, deviceMemcpyKind kind, DMAHandle& handle, uint8_t cast_type);
//Only HbmToDm data path support padding
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_padding_async(DmaFetchDataPad &fetch_data, DMAHandle& handle);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t device_memcpy_bdcast_async(SdmaCmdData &cmd_data, DMAHandle& handle, DmaFetchData &fetch_data);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t wait(DMAHandle& handle, uint16_t dma_uncompleted = 0);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t c_mode_wait(DMAHandle& handle, uint16_t dma_uncompleted = 0);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t deviceMemcpyAsync(const DataParam& dst, const DataParam& src, deviceMemcpyKind kind, DMAHandle& handle, DmaFetchData &fetch_data); // async
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t deviceMemcpy(const DataParam& dst, const DataParam& src, deviceMemcpyKind kind, DMAHandle& handle);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t deviceMemcpyBdcastAsync(const DataParam& dst, const DataParam& src, DMAHandle& handle, DmaFetchData &fetch_data, SdmaCmdData &cmd_data); // async
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t deviceMemcpyPaddingAsync(const DataParam& dst, const DataParam& src, deviceMemcpyKind kind, DMAHandle& handle, DmaFetchDataPad &fetch_data);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t deviceMemcpyPadding(const DataParam& dst, const DataParam& src, deviceMemcpyKind kind, DMAHandle& handle);

_LIBLLCD_DEVICE_VISIBILITY
void configure_local_writeadapter_lut(uint16_t wa_lut_index, uint32_t dm_16byte_offset, const DmVector& dm_regions,
	bool cgran=1, uint8_t gran=4, uint8_t ksize=0xc, uint8_t swap_size=3, uint8_t gran_type=0);
_LIBLLCD_DEVICE_VISIBILITY
void configure_local_writeadapter_lut(uint8_t bdcast_apc_id, uint16_t wa_lut_index, uint32_t dm_16byte_offset, const DmVector& dm_regions,
	bool cgran=1, uint8_t gran=4, uint8_t ksize=0xc, uint8_t swap_size=3, uint8_t gran_type=0);
_LIBLLCD_DEVICE_VISIBILITY
void configure_outband2_writeadapter_lut(uint16_t wa_lut_index, uint32_t dm_16byte_offset, const DmVector& dm_regions,
	bool cgran=1, uint8_t gran=4, uint8_t ksize=0xc, uint8_t swap_size=3, uint8_t gran_type=0);

_LIBLLCD_DEVICE_VISIBILITY
void configure_sbuf_lut(uint16_t sbuf_lut_index, const ApcVector& apcs);

_LIBLLCD_DEVICE_VISIBILITY
void configure_csu_dm_addr_monitor(uint8_t dma_tag, uint32_t dm_addr);
_LIBLLCD_DEVICE_VISIBILITY
void configure_csu_dm_axi_addr_monitor(uint8_t dma_tag, uint64_t dm_axi_addr);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t write_csu_monitor_dm_addr_zero(DmaFetchData &fetch_data, DMAHandle& handle, uint16_t apc_id, uint32_t dm_addr, SbufCfgWrData& wr_data);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t write_csu_monitor_dm_axi_addr_zero(DmaFetchData &fetch_data, DMAHandle& handle, uint16_t apc_id, uint64_t dm_axi_addr, SbufCfgWrData& wr_data);

_LIBLLCD_DEVICE_VISIBILITY
void sdma_write_csu_monitor_dm_addr_zero(DMAHandle& handle, uint16_t apc_id, uint32_t dm_addr, SbufCfgWrData& wr_data);
_LIBLLCD_DEVICE_VISIBILITY
void sdma_write_csu_monitor_dm_axi_addr_zero(DMAHandle& handle, uint16_t apc_id, uint64_t dm_axi_addr, SbufCfgWrData& wr_data);

_LIBLLCD_DEVICE_VISIBILITY
devRunError_t csu_outband2_write_csu_monitor_dm_addr_zero(DmaFetchData &fetch_data, DMAHandle& handle, uint32_t dm_addr, Outband2CfgWrData& wr_data);
_LIBLLCD_DEVICE_VISIBILITY
devRunError_t csu_outband2_write_csu_monitor_dm_axi_addr_zero(DmaFetchData &fetch_data, DMAHandle& handle, uint64_t dm_axi_addr, Outband2CfgWrData& wr_data);

_LIBLLCD_DEVICE_VISIBILITY
void configure_slm_recv_lut(uint8_t slm_id, uint16_t slm_lut_index, uint16_t intr_number = 0);
_LIBLLCD_DEVICE_VISIBILITY
void configure_slm_to_dm_recv_lut(uint8_t slm_id, uint16_t slm_lut_index, const ApcVector& apcs, uint16_t wa_lut_index, uint16_t intr_number = 0);

_LIBLLCD_DEVICE_VISIBILITY
void apc_writeadapter_init();
_LIBLLCD_DEVICE_VISIBILITY
void apc_csu_init();
_LIBLLCD_DEVICE_VISIBILITY
void sbuf_init();

_LIBLLCD_DEVICE_VISIBILITY
uint8_t pcie_m3_dma_copy_dm_to_hostddr(__DDR void *dst, const void *src, uint8_t asid, uint8_t size);
_LIBLLCD_DEVICE_VISIBILITY
uint8_t pcie_m3_dma_copy_hostddr_to_dm(void *dst, __DDR const void *src, uint8_t asid, uint8_t size);
