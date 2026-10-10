#pragma once
#include <cstdint>

#define cb0_wrap0_axi_base_addr 0x0295400800ull
#define cb0_wrap1_axi_base_addr 0x0295404800ull
#define cb0_wrap2_axi_base_addr 0x0295408800ull
#define cb0_wrap3_axi_base_addr 0x029540C800ull

#define cb1_wrap0_axi_base_addr 0x0295900800ull
#define cb1_wrap1_axi_base_addr 0x0295904800ull
#define cb1_wrap2_axi_base_addr 0x0295908800ull
#define cb1_wrap3_axi_base_addr 0x029590C800ull

#define cb2_wrap0_axi_base_addr 0x0295E00800ull
#define cb2_wrap1_axi_base_addr 0x0295E04800ull
#define cb2_wrap2_axi_base_addr 0x0295E08800ull
#define cb2_wrap3_axi_base_addr 0x0295E0C800ull

#define cb3_wrap0_axi_base_addr 0x0296300800ull
#define cb3_wrap1_axi_base_addr 0x0296304800ull
#define cb3_wrap2_axi_base_addr 0x0296308800ull
#define cb3_wrap3_axi_base_addr 0x029630C800ull

#define cr_perf_cnt_axi_c0w0_rst	                0x0
#define cr_perf_cnt_axi_c0w0_always_on	            0x4
#define cr_perf_cycle_cnt_axi_c0w0_enable	        0x8

#define cr_perf_sdma0_ar_setting	                0x0c
#define cr_perf_sdma0_ar_asid1	                    0x10
#define cr_perf_sdma0_aw_setting	                0x14
#define cr_perf_sdma0_aw_asid1	                    0x18

#define cr_perf_ammu0_ptw_ar_setting	            0x1c
#define cr_perf_ammu0_ptw_ar_asid1	                0x20

#define cr_perf_local_slm0_p0_aw_setting	        0x24
#define cr_perf_local_slm0_p0_aw_asid1	            0x28

#define cr_perf_local_slm0_p1_aw_setting	        0x2c
#define cr_perf_local_slm0_p1_aw_asid1	            0x30

#define cr_perf_remote_slm7_p0_aw_setting	        0x34
#define cr_perf_remote_slm7_p0_aw_asid1	            0x38

#define cr_perf_remote_slm7_p1_aw_setting	        0x3c
#define cr_perf_remote_slm7_p1_aw_asid1	            0x40

#define cr_perf_pl_apcg0_apc0_axi_m0_ar_setting	    0x44
#define cr_perf_pl_apcg0_apc0_axi_m0_ar_asid1	    0x48

#define cr_perf_pl_apcg0_apc0_axi_m0_aw_setting	    0x4c
#define cr_perf_pl_apcg0_apc0_axi_m0_aw_asid1	    0x50

#define cr_perf_pl_apcg0_apc0_noc_m1_ar_setting	    0x54
#define cr_perf_pl_apcg0_apc0_noc_m1_ar_asid1	    0x58

#define cr_perf_pl_apcg0_apc0_noc_m1_aw_setting	    0x5c
#define cr_perf_pl_apcg0_apc0_noc_m1_aw_asid1	    0x60

#define cr_perf_pl_apcg1_apc0_axi_m0_ar_setting	    0x64
#define cr_perf_pl_apcg1_apc0_axi_m0_ar_asid1	    0x68

#define cr_perf_pl_apcg1_apc0_axi_m0_aw_setting	    0x6c
#define cr_perf_pl_apcg1_apc0_axi_m0_aw_asid1	    0x70

#define cr_perf_pl_apcg1_apc0_noc_m1_ar_setting	    0x74
#define cr_perf_pl_apcg1_apc0_noc_m1_ar_asid1	    0x78

#define cr_perf_pl_apcg1_apc0_noc_m1_aw_setting	    0x7c
#define cr_perf_pl_apcg1_apc0_noc_m1_aw_asid1	    0x80

#define cr_perf_apc32_axi_m0_ar_setting	            0x84
#define cr_perf_apc32_axi_m0_ar_asid1	            0x88

#define cr_perf_apc32_axi_m0_aw_setting	            0x8c
#define cr_perf_apc32_axi_m0_aw_asid1	            0x90

#define cr_perf_sdma0_sdb_setting	                0x94
#define cr_perf_sdma0_sdb_asid1	                    0x98

#define cr_perf_axi_c0w0_threshold_setting	        0x9c

#define perf_cycle_cnt_c0w0_axi_l	                0x0a0
#define perf_cycle_cnt_c0w0_axi_h	                0x0a4

#define perf_cnt_bw_sdma0_ar_l	                    0x0a8
#define perf_cnt_bw_sdma0_ar_h	                    0x0ac
#define perf_cnt_stall_sdma0_ar_l	                0x0b0
#define perf_cnt_stall_sdma0_ar_h	                0x0b4
#define perf_cnt_bw_sdma0_aw_l	                    0x0b8
#define perf_cnt_bw_sdma0_aw_h	                    0x0bc
#define perf_cnt_stall_sdma0_aw_l	                0x0c0
#define perf_cnt_stall_sdma0_aw_h	                0x0c4

#define perf_cnt_bw_ammu0_ptw_ar_l	                0x0c8
#define perf_cnt_bw_ammu0_ptw_ar_h	                0x0cc
#define perf_cnt_stall_ammu0_ptw_ar_l	            0x0d0
#define perf_cnt_stall_ammu0_ptw_ar_h	            0x0d4

#define perf_cnt_bw_local_slm0_p0_aw_l	            0x0d8
#define perf_cnt_bw_local_slm0_p0_aw_h	            0x0dc
#define perf_cnt_stall_local_slm0_p0_aw_l	        0x0e0
#define perf_cnt_stall_local_slm0_p0_aw_h	        0x0e4

#define perf_cnt_bw_local_slm0_p1_aw_l	            0x0e8
#define perf_cnt_bw_local_slm0_p1_aw_h	            0x0ec
#define perf_cnt_stall_local_slm0_p1_aw_l	        0x0f0
#define perf_cnt_stall_local_slm0_p1_aw_h	        0x0f4

#define perf_cnt_bw_remote_slm7_p0_aw_l	            0x0f8
#define perf_cnt_bw_remote_slm7_p0_aw_h	            0x0fc
#define perf_cnt_stall_remote_slm7_p0_aw_l	        0x100
#define perf_cnt_stall_remote_slm7_p0_aw_h	        0x104

#define perf_cnt_bw_remote_slm7_p1_aw_l	            0x108
#define perf_cnt_bw_remote_slm7_p1_aw_h	            0x10c
#define perf_cnt_stall_remote_slm7_p1_aw_l	        0x110
#define perf_cnt_stall_remote_slm7_p1_aw_h	        0x114

#define perf_cnt_bw_pl_apcg0_apc0_axi_m0_ar_l	    0x118
#define perf_cnt_bw_pl_apcg0_apc0_axi_m0_ar_h	    0x11c
#define perf_cnt_stall_pl_apcg0_apc0_axi_m0_ar_l	0x120
#define perf_cnt_stall_pl_apcg0_apc0_axi_m0_ar_h	0x124
#define perf_cnt_bw_pl_apcg0_apc0_axi_m0_aw_l	    0x128
#define perf_cnt_bw_pl_apcg0_apc0_axi_m0_aw_h	    0x12c
#define perf_cnt_stall_pl_apcg0_apc0_axi_m0_aw_l	0x130
#define perf_cnt_stall_pl_apcg0_apc0_axi_m0_aw_h	0x134

#define perf_cnt_bw_pl_apcg0_apc0_noc_m1_ar_l	    0x138
#define perf_cnt_bw_pl_apcg0_apc0_noc_m1_ar_h	    0x13c
#define perf_cnt_stall_pl_apcg0_apc0_noc_m1_ar_l	0x140
#define perf_cnt_stall_pl_apcg0_apc0_noc_m1_ar_h	0x144
#define perf_cnt_bw_pl_apcg0_apc0_noc_m1_aw_l	    0x148
#define perf_cnt_bw_pl_apcg0_apc0_noc_m1_aw_h	    0x14c
#define perf_cnt_stall_pl_apcg0_apc0_noc_m1_aw_l	0x150
#define perf_cnt_stall_pl_apcg0_apc0_noc_m1_aw_h	0x154

#define perf_cnt_bw_pl_apcg1_apc0_axi_m0_ar_l	    0x158
#define perf_cnt_bw_pl_apcg1_apc0_axi_m0_ar_h	    0x15c
#define perf_cnt_stall_pl_apcg1_apc0_axi_m0_ar_l	0x160
#define perf_cnt_stall_pl_apcg1_apc0_axi_m0_ar_h	0x164
#define perf_cnt_bw_pl_apcg1_apc0_axi_m0_aw_l	    0x168
#define perf_cnt_bw_pl_apcg1_apc0_axi_m0_aw_h	    0x16c
#define perf_cnt_stall_pl_apcg1_apc0_axi_m0_aw_l	0x170
#define perf_cnt_stall_pl_apcg1_apc0_axi_m0_aw_h	0x174

#define perf_cnt_bw_pl_apcg1_apc0_noc_m1_ar_l	    0x178
#define perf_cnt_bw_pl_apcg1_apc0_noc_m1_ar_h	    0x17c
#define perf_cnt_stall_pl_apcg1_apc0_noc_m1_ar_l	0x180
#define perf_cnt_stall_pl_apcg1_apc0_noc_m1_ar_h	0x184
#define perf_cnt_bw_pl_apcg1_apc0_noc_m1_aw_l	    0x188
#define perf_cnt_bw_pl_apcg1_apc0_noc_m1_aw_h	    0x18c
#define perf_cnt_stall_pl_apcg1_apc0_noc_m1_aw_l	0x190
#define perf_cnt_stall_pl_apcg1_apc0_noc_m1_aw_h	0x194

#define perf_cnt_bw_apc32_axi_m0_ar_l	            0x198
#define perf_cnt_bw_apc32_axi_m0_ar_h	            0x19c
#define perf_cnt_stall_apc32_axi_m0_ar_l	        0x1a0
#define perf_cnt_stall_apc32_axi_m0_ar_h	        0x1a4
#define perf_cnt_bw_apc32_axi_m0_aw_l	            0x1a8
#define perf_cnt_bw_apc32_axi_m0_aw_h	            0x1ac
#define perf_cnt_stall_apc32_axi_m0_aw_l	        0x1b0
#define perf_cnt_stall_apc32_axi_m0_aw_h	        0x1b4

#define perf_cnt_bw_sdma0_sdb_l	                    0x1b8
#define perf_cnt_bw_sdma0_sdb_h	                    0x1bc
#define perf_cnt_stall_sdma0_sdb_l	                0x1c0
#define perf_cnt_stall_sdma0_sdb_h	                0x1c4

#define bus_timeout_cnt_ctrl                        0x1d0
#define bus_timeout_cnt_c0w0_threshold	            0x1d4

_LIBLLCD_DEVICE_VISIBILITY
inline void get_apc_axi_perf_cnt_base_addr(uint8_t apc_id, uint64_t& base_addr, uint8_t& wrap_apc_num) {
	switch (apc_id) {
		case 0:
			wrap_apc_num = 0;
			base_addr = cb0_wrap0_axi_base_addr;
			break;
		case 4:
			wrap_apc_num = 1;
			base_addr = cb0_wrap0_axi_base_addr;
			break;
		case 8:
			wrap_apc_num = 0;
			base_addr = cb1_wrap0_axi_base_addr;
			break;
		case 12:
			wrap_apc_num = 1;
			base_addr = cb1_wrap0_axi_base_addr;
			break;
		case 1:
			wrap_apc_num = 0;
			base_addr = cb0_wrap1_axi_base_addr;
			break;
		case 5:
			wrap_apc_num = 1;
			base_addr = cb0_wrap1_axi_base_addr;
			break;
		case 9:
			wrap_apc_num = 0;
			base_addr = cb1_wrap1_axi_base_addr;
			break;
		case 13:
			wrap_apc_num = 1;
			base_addr = cb1_wrap1_axi_base_addr;
			break;
		case 2:
			wrap_apc_num = 0;
			base_addr = cb0_wrap2_axi_base_addr;
			break;
		case 6:
			wrap_apc_num = 1;
			base_addr = cb0_wrap2_axi_base_addr;
			break;
		case 10:
			wrap_apc_num = 0;
			base_addr = cb1_wrap2_axi_base_addr;
			break;
		case 14:
			wrap_apc_num = 1;
			base_addr = cb1_wrap2_axi_base_addr;
			break;
		case 3:
			wrap_apc_num = 0;
			base_addr = cb0_wrap3_axi_base_addr;
			break;
		case 7:
			wrap_apc_num = 1;
			base_addr = cb0_wrap3_axi_base_addr;
			break;
		case 11:
			wrap_apc_num = 0;
			base_addr = cb1_wrap3_axi_base_addr;
			break;
		case 15:
			wrap_apc_num = 1;
			base_addr = cb1_wrap3_axi_base_addr;
			break;
		case 19:
			wrap_apc_num = 0;
			base_addr = cb2_wrap3_axi_base_addr;
			break;
		case 23:
			wrap_apc_num = 1;
			base_addr = cb2_wrap3_axi_base_addr;
			break;
		case 27:
			wrap_apc_num = 0;
			base_addr = cb3_wrap3_axi_base_addr;
			break;
		case 31:
			wrap_apc_num = 1;
			base_addr = cb3_wrap3_axi_base_addr;
			break;
		case 18:
			wrap_apc_num = 0;
			base_addr = cb2_wrap2_axi_base_addr;
			break;
		case 22:
			wrap_apc_num = 1;
			base_addr = cb2_wrap2_axi_base_addr;
			break;
		case 26:
			wrap_apc_num = 0;
			base_addr = cb3_wrap2_axi_base_addr;
			break;
		case 30:
			wrap_apc_num = 1;
			base_addr = cb3_wrap2_axi_base_addr;
			break;
		case 17:
			wrap_apc_num = 0;
			base_addr = cb2_wrap1_axi_base_addr;
			break;
		case 21:
			wrap_apc_num = 1;
			base_addr = cb2_wrap1_axi_base_addr;
			break;
		case 25:
			wrap_apc_num = 0;
			base_addr = cb3_wrap1_axi_base_addr;
			break;
		case 29:
			wrap_apc_num = 1;
			base_addr = cb3_wrap1_axi_base_addr;
			break;
		case 16:
			wrap_apc_num = 0;
			base_addr = cb2_wrap0_axi_base_addr;
			break;
		case 20:
			wrap_apc_num = 1;
			base_addr = cb2_wrap0_axi_base_addr;
			break;
		case 24:
			wrap_apc_num = 0;
			base_addr = cb3_wrap0_axi_base_addr;
			break;
		case 28:
			wrap_apc_num = 1;
			base_addr = cb3_wrap0_axi_base_addr;
			break;
		default:
			return;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_axi_cw_start(uint64_t base_addr) {
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cnt_axi_c0w0_rst) = 1;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cnt_axi_c0w0_rst) = 0;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cnt_axi_c0w0_always_on) = 1;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cycle_cnt_axi_c0w0_enable) = 1;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_sdma0_ar_setting) = 0x80;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_axi_cw_cycles_stop(uint64_t base_addr) {
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cycle_cnt_axi_c0w0_enable) = 0;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_axi_cw_cycles_start(uint64_t base_addr) {
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cycle_cnt_axi_c0w0_enable) = 1;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_axi_cw_read_cycles(uint64_t base_addr, uint64_t& cw_cycle_cnt) {
	uint32_t cycle_cnt_cw_axi[2];
	cycle_cnt_cw_axi[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cycle_cnt_c0w0_axi_l);
	cycle_cnt_cw_axi[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cycle_cnt_c0w0_axi_h);
	cw_cycle_cnt = ((uint64_t)cycle_cnt_cw_axi[1] << 32) | cycle_cnt_cw_axi[0];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_cw_1st_apc_m0(uint64_t base_addr, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_axi_m0_ar_setting) = ar_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_axi_m0_ar_asid1)   = ar_asid;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_axi_m0_aw_setting) = aw_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_axi_m0_aw_asid1)   = aw_asid;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_cw_1st_apc_m1(uint64_t base_addr, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_noc_m1_ar_setting) = ar_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_noc_m1_ar_asid1) = ar_asid;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_noc_m1_aw_setting) = aw_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg0_apc0_noc_m1_aw_asid1) = aw_asid;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_cw_1st_apc_m0(uint64_t base_addr, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint32_t perf_cnt_res[8];
	perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_axi_m0_ar_l);
	perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_axi_m0_ar_h);
	perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_axi_m0_ar_l);
	perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_axi_m0_ar_h);
	perf_cnt_res[4] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_axi_m0_aw_l);
	perf_cnt_res[5] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_axi_m0_aw_h);
	perf_cnt_res[6] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_axi_m0_aw_l);
	perf_cnt_res[7] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_axi_m0_aw_h);
	ar_bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	ar_stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
	aw_bw = ((uint64_t)perf_cnt_res[5] << 32) | perf_cnt_res[4];
	aw_stall = ((uint64_t)perf_cnt_res[7] << 32) | perf_cnt_res[6];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_cw_1st_apc_m1(uint64_t base_addr, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint32_t perf_cnt_res[8];
	perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_noc_m1_ar_l);
	perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_noc_m1_ar_h);
	perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_noc_m1_ar_l);
	perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_noc_m1_ar_h);
	perf_cnt_res[4] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_noc_m1_aw_l);
	perf_cnt_res[5] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg0_apc0_noc_m1_aw_h);
	perf_cnt_res[6] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_noc_m1_aw_l);
	perf_cnt_res[7] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg0_apc0_noc_m1_aw_h);
	ar_bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	ar_stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
	aw_bw = ((uint64_t)perf_cnt_res[5] << 32) | perf_cnt_res[4];
	aw_stall = ((uint64_t)perf_cnt_res[7] << 32) | perf_cnt_res[6];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_cw_2nd_apc_m0(uint64_t base_addr, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_axi_m0_ar_setting) = ar_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_axi_m0_ar_asid1)  = ar_asid;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_axi_m0_aw_setting) = aw_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_axi_m0_aw_asid1)   = aw_asid;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_cw_2nd_apc_m1(uint64_t base_addr, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_noc_m1_ar_setting)	= ar_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_noc_m1_ar_asid1)	= ar_asid;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_noc_m1_aw_setting)	= aw_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_pl_apcg1_apc0_noc_m1_aw_asid1)	= aw_asid;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_cw_2nd_apc_m0(uint64_t base_addr, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint32_t perf_cnt_res[8];
	perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_axi_m0_ar_l);
	perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_axi_m0_ar_h);
	perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_axi_m0_ar_l);
	perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_axi_m0_ar_h);
	perf_cnt_res[4] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_axi_m0_aw_l);
	perf_cnt_res[5] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_axi_m0_aw_h);
	perf_cnt_res[6] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_axi_m0_aw_l);
	perf_cnt_res[7] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_axi_m0_aw_h);
	ar_bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	ar_stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
	aw_bw = ((uint64_t)perf_cnt_res[5] << 32) | perf_cnt_res[4];
	aw_stall = ((uint64_t)perf_cnt_res[7] << 32) | perf_cnt_res[6];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_cw_2nd_apc_m1(uint64_t base_addr, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint32_t perf_cnt_res[8];
	perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_noc_m1_ar_l);
	perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_noc_m1_ar_h);
	perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_noc_m1_ar_l);
	perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_noc_m1_ar_h);
	perf_cnt_res[4] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_noc_m1_aw_l);
	perf_cnt_res[5] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_pl_apcg1_apc0_noc_m1_aw_h);
	perf_cnt_res[6] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_noc_m1_aw_l);
	perf_cnt_res[7] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_pl_apcg1_apc0_noc_m1_aw_h);
	ar_bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	ar_stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
	aw_bw = ((uint64_t)perf_cnt_res[5] << 32) | perf_cnt_res[4];
	aw_stall = ((uint64_t)perf_cnt_res[7] << 32) | perf_cnt_res[6];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_apc_m0(uint8_t apc_id, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	uint64_t base_addr = 0;
	uint8_t wrap_apc_num = 0;
	get_apc_axi_perf_cnt_base_addr(apc_id, base_addr, wrap_apc_num);
	if (wrap_apc_num == 0) {
		set_perf_cnt_axi_cw_1st_apc_m0(base_addr, ar_setting, ar_asid, aw_setting, aw_asid);
	} else {
		set_perf_cnt_axi_cw_2nd_apc_m0(base_addr, ar_setting, ar_asid, aw_setting, aw_asid);
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_apc_m0(uint8_t apc_id, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint64_t base_addr = 0;
	uint8_t wrap_apc_num = 0;
	get_apc_axi_perf_cnt_base_addr(apc_id, base_addr, wrap_apc_num);
	if (wrap_apc_num == 0) {
		get_perf_cnt_axi_cw_1st_apc_m0(base_addr, ar_bw, ar_stall, aw_bw, aw_stall);
	} else {
		get_perf_cnt_axi_cw_2nd_apc_m0(base_addr, ar_bw, ar_stall, aw_bw, aw_stall);
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_apc_m1(uint8_t apc_id, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	uint64_t base_addr = 0;
	uint8_t wrap_apc_num = 0;
	get_apc_axi_perf_cnt_base_addr(apc_id, base_addr, wrap_apc_num);
	if (wrap_apc_num == 0) {
		set_perf_cnt_axi_cw_1st_apc_m1(base_addr, ar_setting, ar_asid, aw_setting, aw_asid);
	} else {
		set_perf_cnt_axi_cw_2nd_apc_m1(base_addr, ar_setting, ar_asid, aw_setting, aw_asid);
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_apc_m1(uint8_t apc_id, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint64_t base_addr = 0;
	uint8_t wrap_apc_num = 0;
	get_apc_axi_perf_cnt_base_addr(apc_id, base_addr, wrap_apc_num);
	if (wrap_apc_num == 0) {
		get_perf_cnt_axi_cw_1st_apc_m1(base_addr, ar_bw, ar_stall, aw_bw, aw_stall);
	} else {
		get_perf_cnt_axi_cw_2nd_apc_m1(base_addr, ar_bw, ar_stall, aw_bw, aw_stall);
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline uint8_t apc_id_to_sbuf_id(uint8_t apc_id) {
	uint8_t sbuf_id = 0;
	switch (apc_id) {
		case 0:
		case 4:
		case 8:
		case 12:
			sbuf_id = 0;
			break;
		case 1:
		case 5:
		case 9:
		case 13:
			sbuf_id = 1;
			break;
		case 2:
		case 6:
		case 10:
		case 14:
			sbuf_id = 2;
			break;
		case 3:
		case 7:
		case 11:
		case 15:
			sbuf_id = 3;
			break;
		case 19:
		case 23:
		case 27:
		case 31:
			sbuf_id = 4;
			break;
		case 18:
		case 22:
		case 26:
		case 30:
			sbuf_id = 5;
			break;
		case 17:
		case 21:
		case 25:
		case 29:
			sbuf_id = 6;
			break;
		case 16:
		case 20:
		case 24:
		case 28:
			sbuf_id = 7;
			break;
		default:
			break;
	}
	return sbuf_id;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_sdma_to_sbuf_perf_cnt_base_addr(uint8_t sbuf_id, uint64_t& base_addr) {

	switch (sbuf_id) {
		case 0:
			base_addr = cb1_wrap0_axi_base_addr;
			break;
		case 1:
			base_addr = cb1_wrap1_axi_base_addr;
			break;
		case 2:
			base_addr = cb1_wrap2_axi_base_addr;
			break;
		case 3:
			base_addr = cb1_wrap3_axi_base_addr;
			break;
		case 7:
			base_addr = cb3_wrap0_axi_base_addr;
			break;
		case 6:
			base_addr = cb3_wrap1_axi_base_addr;
			break;
		case 5:
			base_addr = cb3_wrap2_axi_base_addr;
			break;
		case 4:
			base_addr = cb3_wrap3_axi_base_addr;
			break;
		default:
			return;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_sdma_to_sbuf(uint8_t sbuf_id, uint32_t setting, uint32_t asid) {

	uint64_t base_addr = 0;
	get_sdma_to_sbuf_perf_cnt_base_addr(sbuf_id, base_addr);

	*(volatile __DDR uint32_t*)(base_addr +  cr_perf_sdma0_sdb_setting - 0x10)	= setting;
	*(volatile __DDR uint32_t*)(base_addr +  cr_perf_sdma0_sdb_asid1 - 0x10) = asid;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_sdma_to_sbuf(uint8_t sbuf_id, uint64_t& bw, uint64_t& stall) {

	uint64_t base_addr = 0;
	get_sdma_to_sbuf_perf_cnt_base_addr(sbuf_id, base_addr);

	uint32_t perf_cnt_res[4];
	perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_sdma0_sdb_l - 0x20);
	perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_sdma0_sdb_h - 0x20);
	perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_sdma0_sdb_l - 0x20);
	perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_sdma0_sdb_h - 0x20);

	bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];

}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_sdma_perf_cnt_base_addr(uint8_t sdma_id, uint64_t& base_addr) {
	switch (sdma_id) {
		case 0:
			base_addr = cb0_wrap0_axi_base_addr;
			break;
		case 1:
			base_addr = cb0_wrap1_axi_base_addr;
			break;
		case 2:
			base_addr = cb0_wrap2_axi_base_addr;
			break;
		case 3:
			base_addr = cb0_wrap3_axi_base_addr;
			break;

		case 4:
			base_addr = cb1_wrap0_axi_base_addr;
			break;
		case 5:
			base_addr = cb1_wrap1_axi_base_addr;
			break;
		case 6:
			base_addr = cb1_wrap2_axi_base_addr;
			break;
		case 7:
			base_addr = cb1_wrap3_axi_base_addr;
			break;

		case 8:
			base_addr = cb2_wrap0_axi_base_addr;
			break;
		case 9:
			base_addr = cb2_wrap1_axi_base_addr;
			break;
		case 10:
			base_addr = cb2_wrap2_axi_base_addr;
			break;
		case 11:
			base_addr = cb2_wrap3_axi_base_addr;
			break;

		case 12:
			base_addr = cb3_wrap0_axi_base_addr;
			break;
		case 13:
			base_addr = cb3_wrap1_axi_base_addr;
			break;
		case 14:
			base_addr = cb3_wrap2_axi_base_addr;
			break;
		case 15:
			base_addr = cb3_wrap3_axi_base_addr;
			break;

		default:
			return;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_axi_sdma(uint8_t sdma_id, uint32_t ar_setting, uint32_t ar_asid, uint32_t aw_setting, uint32_t aw_asid) {

	uint64_t base_addr = 0;
	get_sdma_perf_cnt_base_addr(sdma_id, base_addr);
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_sdma0_ar_setting)	 = ar_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_sdma0_ar_asid1)	  = ar_asid;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_sdma0_aw_setting)	 = aw_setting;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_sdma0_aw_asid1)	  = aw_asid;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_axi_sdma(uint8_t sdma_id, uint64_t& ar_bw, uint64_t& ar_stall, uint64_t& aw_bw, uint64_t& aw_stall) {

	uint64_t base_addr = 0;
	get_sdma_perf_cnt_base_addr(sdma_id, base_addr);
	uint32_t perf_cnt_res[8];
	perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_sdma0_ar_l);
	perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_sdma0_ar_h);
	perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_sdma0_ar_l);
	perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_sdma0_ar_h);
	perf_cnt_res[4] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_sdma0_aw_l);
	perf_cnt_res[5] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_sdma0_aw_h);
	perf_cnt_res[6] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_sdma0_aw_l);
	perf_cnt_res[7] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_sdma0_aw_h);
	ar_bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	ar_stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
	aw_bw = ((uint64_t)perf_cnt_res[5] << 32) | perf_cnt_res[4];
	aw_stall = ((uint64_t)perf_cnt_res[7] << 32) | perf_cnt_res[6];
}

_LIBLLCD_DEVICE_VISIBILITY
inline uint8_t sbuf_id_to_sdma_id(uint8_t sbuf_id) {
	uint8_t sdma_id = 0;
	switch (sbuf_id) {
		case 0:
			sdma_id = 4;
			break;
		case 1:
			sdma_id = 5;
			break;
		case 2:
			sdma_id = 6;
			break;
		case 3:
			sdma_id = 7;
			break;
		case 4:
			sdma_id = 15;
			break;
		case 5:
			sdma_id = 14;
			break;
		case 6:
			sdma_id = 13;
			break;
		case 7:
			sdma_id = 12;
			break;
		default:
			break;
	}
	return sdma_id;
}

