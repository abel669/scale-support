#pragma once
#include <cstdint>
#include "libllcd.h"

enum ApcAxiCntType {
	T_DMA_R=0,
	T_DMA_RW,
	T_ASID,
	T_ALL              //DMA and load/store and fetch
};

enum ApcAxiDataPath {
	P_AXI_M0=0,
	P_AXI_M1
};
//APC CSU
_LIBLLCD_DEVICE_VISIBILITY
void start_apc_axi_counter(uint8_t apc_id, ApcAxiCntType type, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void stop_apc_axi_counter(uint8_t apc_id, ApcAxiCntType type, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void read_apc_axi_counter(uint8_t apc_id, ApcAxiDataPath path, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall);

//SDMA to AXI, sdma_id should be one of number in {4, 5, 6, 7, 15, 14, 13, 12}, correspond to sbuf 0 to 7.
_LIBLLCD_DEVICE_VISIBILITY
void start_sdma_axi_counter(uint8_t sdma_id, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void stop_sdma_axi_counter(uint8_t sdma_id, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void read_sdma_axi_counter(uint8_t sdma_id, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall);

//SDMA to SBUF
_LIBLLCD_DEVICE_VISIBILITY
void start_sdma_to_sbuf_counter(uint8_t sbuf_id, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void stop_sdma_to_sbuf_counter(uint8_t sbuf_id, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void read_sdma_to_sbuf_counter(uint8_t sbuf_id, uint64_t& to_sbuf_bw, uint64_t& to_sbuf_stall);

//Local SBUF, sbuf_to_apcs_mask=0xffffffff (apc0 to apc31)
_LIBLLCD_DEVICE_VISIBILITY
void start_local_sbuf_counter(uint8_t apc_id, uint32_t sbuf_to_apcs_mask, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void stop_local_sbuf_counter(uint8_t apc_id, uint32_t sbuf_to_apcs_mask, uint8_t asid=0);
_LIBLLCD_DEVICE_VISIBILITY
void read_local_sbuf_counter(uint8_t apc_id, uint64_t& local_sbuf_bw, uint64_t& local_sbuf_stall );

_LIBLLCD_DEVICE_VISIBILITY
void soc_init_for_axi_perf_counter();
_LIBLLCD_DEVICE_VISIBILITY
void soc_init_for_sdb_perf_counter();


