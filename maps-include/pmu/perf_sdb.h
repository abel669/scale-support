#pragma once
#include <cstdint>

#define cb0_wrap0_sdb_base_addr 0x0295400C00ull
#define cb0_wrap1_sdb_base_addr 0x0295404C00ull
#define cb0_wrap2_sdb_base_addr 0x0295408C00ull
#define cb0_wrap3_sdb_base_addr 0x029540CC00ull

#define cb1_wrap0_sdb_base_addr 0x0295900C00ull
#define cb1_wrap1_sdb_base_addr 0x0295904C00ull
#define cb1_wrap2_sdb_base_addr 0x0295908C00ull
#define cb1_wrap3_sdb_base_addr 0x029590CC00ull

#define cb2_wrap0_sdb_base_addr 0x0295E00C00ull
#define cb2_wrap1_sdb_base_addr 0x0295E04C00ull
#define cb2_wrap2_sdb_base_addr 0x0295E08C00ull
#define cb2_wrap3_sdb_base_addr 0x0295E0CC00ull

#define cb3_wrap0_sdb_base_addr 0x0296300C00ull
#define cb3_wrap1_sdb_base_addr 0x0296304C00ull
#define cb3_wrap2_sdb_base_addr 0x0296308C00ull
#define cb3_wrap3_sdb_base_addr 0x029630CC00ull

#define	cr_perf_cnt_sdb_c0w0_rst				0x0
#define	cr_perf_cnt_sdb_c0w0_always_on			0x4
#define	cr_perf_cycle_cnt_sdb_c0w0_enable		0x8

#define	cr_perf_local_slm0_setting				0xc
#define	cr_perf_local_slm0_asid1				0x10

#define	cr_perf_local_sbuf0_setting				0x14
#define	cr_perf_local_sbuf0_asid1				0x18

#define	cr_perf_apc_to_sbuf_up_setting			0x1c
#define	cr_perf_apc_to_sbuf_up_asid1			0x20

#define	cr_perf_apc_to_sbuf_down_setting		0x24
#define	cr_perf_apc_to_sbuf_down_asid1			0x28

#define	local_sbuf0_valid_sel					0x40
#define	local_sbuf0_valid_sel_apc32				0x44

#define	cr_perf_sdb_c0w0_threshold_setting		0x48

#define	perf_cycle_cnt_c0w0_sdb_l				0x60
#define	perf_cycle_cnt_c0w0_sdb_h				0x64

#define	perf_cnt_bw_local_slm0_sdb_l			0x68
#define	perf_cnt_bw_local_slm0_sdb_h			0x6c
#define	perf_cnt_stall_local_slm0_sdb_l			0x70
#define	perf_cnt_stall_local_slm0_sdb_h			0x74

#define	perf_cnt_bw_local_sbuf0_sdb_l			0x78
#define	perf_cnt_bw_local_sbuf0_sdb_h			0x7c
#define	perf_cnt_stall_local_sbuf0_sdb_l		0x80
#define	perf_cnt_stall_local_sbuf0_sdb_h		0x84

#define	perf_cnt_bw_apc_to_sbuf_up_sdb_l		0x88
#define	perf_cnt_bw_apc_to_sbuf_up_sdb_h		0x8c
#define	perf_cnt_stall_apc_to_sbuf_up_sdb_l	    0x90
#define	perf_cnt_stall_apc_to_sbuf_up_sdb_h	    0x94

#define	perf_cnt_bw_apc_to_sbuf_down_sdb_l	    0x98
#define	perf_cnt_bw_apc_to_sbuf_down_sdb_h	    0x9c
#define	perf_cnt_stall_apc_to_sbuf_down_sdb_l	0xa0
#define	perf_cnt_stall_apc_to_sbuf_down_sdb_h	0xa4

_LIBLLCD_DEVICE_VISIBILITY
inline void get_apc_sdb_perf_cnt_base_addr(uint8_t apc_id, uint64_t& base_addr, uint8_t& apc_to_sbuf_flag, uint8_t& cb_wrap_flag) {
	switch (apc_id) {
		case 0:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap0_sdb_base_addr;
			break;
		case 4:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap0_sdb_base_addr;
			break;
		case 8:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap0_sdb_base_addr;
			break;
		case 12:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap0_sdb_base_addr;
			break;
		case 1:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap1_sdb_base_addr;
			break;
		case 5:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap1_sdb_base_addr;
			break;
		case 9:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap1_sdb_base_addr;
			break;
		case 13:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap1_sdb_base_addr;
			break;
		case 2:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap2_sdb_base_addr;
			break;
		case 6:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap2_sdb_base_addr;
			break;
		case 10:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap2_sdb_base_addr;
			break;
		case 14:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap2_sdb_base_addr;
			break;
		case 3:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap3_sdb_base_addr;
			break;
		case 7:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb0_wrap3_sdb_base_addr;
			break;
		case 11:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap3_sdb_base_addr;
			break;
		case 15:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb1_wrap3_sdb_base_addr;
			break;
		case 19:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap3_sdb_base_addr;
			break;
		case 23:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap3_sdb_base_addr;
			break;
		case 27:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap3_sdb_base_addr;
			break;
		case 31:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap3_sdb_base_addr;
			break;
		case 18:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap2_sdb_base_addr;
			break;
		case 22:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap2_sdb_base_addr;
			break;
		case 26:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap2_sdb_base_addr;
			break;
		case 30:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap2_sdb_base_addr;
			break;
		case 17:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap1_sdb_base_addr;
			break;
		case 21:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap1_sdb_base_addr;
			break;
		case 25:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap1_sdb_base_addr;
			break;
		case 29:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap1_sdb_base_addr;
			break;
		case 16:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap0_sdb_base_addr;
			break;
		case 20:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 0;
			base_addr = cb2_wrap0_sdb_base_addr;
			break;
		case 24:
			apc_to_sbuf_flag = 0;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap0_sdb_base_addr;
			break;
		case 28:
			apc_to_sbuf_flag = 1;
			cb_wrap_flag = 1;
			base_addr = cb3_wrap0_sdb_base_addr;
			break;
		default:
			return;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_sdb_cw_start(uint64_t base_addr) {
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cnt_sdb_c0w0_rst) = 1;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cnt_sdb_c0w0_rst) = 0;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cnt_sdb_c0w0_always_on) = 1;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cycle_cnt_sdb_c0w0_enable) = 1;
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_local_slm0_setting) = 0x80;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_sdb_cw_cycles_stop(uint64_t base_addr) {
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cycle_cnt_sdb_c0w0_enable) = 0;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_sdb_cw_cycles_start(uint64_t base_addr) {
	*(volatile __DDR uint32_t*)(base_addr + cr_perf_cycle_cnt_sdb_c0w0_enable) = 1;
}

_LIBLLCD_DEVICE_VISIBILITY
inline void perf_cnt_sdb_cw_read_cycles(uint64_t base_addr, uint64_t& cw_cycle_cnt) {
	uint32_t cycle_cnt_cw_sdb[2];
	cycle_cnt_cw_sdb[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cycle_cnt_c0w0_sdb_l);
	cycle_cnt_cw_sdb[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cycle_cnt_c0w0_sdb_h);
	cw_cycle_cnt = ((uint64_t)cycle_cnt_cw_sdb[1] << 32) | cycle_cnt_cw_sdb[0];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_sdb_apc_to_sbuf_up(uint64_t base_addr, uint8_t cb_wrap_flag, uint32_t setting, uint32_t asid) {
	if (cb_wrap_flag == 0) {
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_up_setting)	= setting;
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_up_asid1)	= asid;
	} else if (cb_wrap_flag == 1) {
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_up_setting + 0x8) = setting;
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_up_asid1 + 0x8)	= asid;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_sdb_apc_to_sbuf_up(uint64_t base_addr, uint8_t cb_wrap_flag, uint64_t& bw, uint64_t& stall) {

	uint32_t perf_cnt_res[4];
	if (cb_wrap_flag == 0) {
		perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_up_sdb_l);
		perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_up_sdb_h);
		perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_up_sdb_l);
		perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_up_sdb_h);
	} else if (cb_wrap_flag == 1) {
		perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_up_sdb_l + 0x10);
		perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_up_sdb_h + 0x10);
		perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_up_sdb_l + 0x10);
		perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_up_sdb_h + 0x10);
	}

	bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_sdb_apc_to_sbuf_down(uint64_t base_addr, uint8_t cb_wrap_flag, uint32_t setting, uint32_t asid) {
	if (cb_wrap_flag == 0) {
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_down_setting) = setting;
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_down_asid1)	 = asid;
	} else 	if (cb_wrap_flag == 1) {
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_down_setting + 0x8) = setting;
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_apc_to_sbuf_down_asid1 + 0x8) = asid;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_sdb_apc_to_sbuf_down(uint64_t base_addr, uint8_t cb_wrap_flag, uint64_t& bw, uint64_t& stall) {

	uint32_t perf_cnt_res[4];
	if (cb_wrap_flag == 0) {
		perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_down_sdb_l);
		perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_down_sdb_h);
		perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_down_sdb_l);
		perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_down_sdb_h);
	} else if (cb_wrap_flag == 1) {
		perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_down_sdb_l + 0x10);
		perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_apc_to_sbuf_down_sdb_h + 0x10);
		perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_down_sdb_l + 0x10);
		perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_apc_to_sbuf_down_sdb_h + 0x10);
	}

	bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_sdb_apc_to_sbuf(uint8_t apc_id, uint32_t setting, uint32_t asid) {
	uint64_t base_addr = 0;
	uint8_t apc_to_sbuf_flag = 0;
	uint8_t cb_wrap_flag = 0;
	get_apc_sdb_perf_cnt_base_addr(apc_id, base_addr, apc_to_sbuf_flag, cb_wrap_flag);
	if (apc_to_sbuf_flag == 0) {
		set_perf_cnt_sdb_apc_to_sbuf_down(base_addr, cb_wrap_flag, setting, asid);
	} else {
		set_perf_cnt_sdb_apc_to_sbuf_up(base_addr, cb_wrap_flag, setting, asid);
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_sdb_apc_to_sbuf(uint8_t apc_id, uint64_t& bw, uint64_t& stall) {
	uint64_t base_addr = 0;
	uint8_t apc_to_sbuf_flag = 0;
	uint8_t cb_wrap_flag = 0;
	get_apc_sdb_perf_cnt_base_addr(apc_id, base_addr, apc_to_sbuf_flag, cb_wrap_flag);
	if (apc_to_sbuf_flag == 0) {
		get_perf_cnt_sdb_apc_to_sbuf_down(base_addr, cb_wrap_flag, bw, stall);
	} else {
		get_perf_cnt_sdb_apc_to_sbuf_up(base_addr, cb_wrap_flag, bw, stall);
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_cb_wrap_perf_cnt_sdb_local_sbuf(uint64_t base_addr, uint8_t cb_wrap_flag, uint32_t setting, uint32_t asid, uint32_t valid_sel, uint32_t valid_sel_apc32) {
	if (cb_wrap_flag == 0) {
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_local_sbuf0_setting) = setting;
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_local_sbuf0_asid1)   = asid;
		*(volatile __DDR uint32_t*)(base_addr + local_sbuf0_valid_sel) = valid_sel;
		*(volatile __DDR uint32_t*)(base_addr + local_sbuf0_valid_sel_apc32)   = valid_sel_apc32;
	} else {
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_local_sbuf0_setting + 0x8) = setting;
		*(volatile __DDR uint32_t*)(base_addr + cr_perf_local_sbuf0_asid1 + 0x8)   = asid;
		*(volatile __DDR uint32_t*)(base_addr + local_sbuf0_valid_sel) = valid_sel;
		*(volatile __DDR uint32_t*)(base_addr + local_sbuf0_valid_sel_apc32)   = valid_sel_apc32;
	}
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_cb_wrap_perf_cnt_sdb_local_sbuf(uint64_t base_addr, uint8_t cb_wrap_flag, uint64_t& bw, uint64_t& stall) {

	uint32_t perf_cnt_res[4];
	if (cb_wrap_flag == 0) {
		perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_local_sbuf0_sdb_l);
		perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_local_sbuf0_sdb_h);
		perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_local_sbuf0_sdb_l);
		perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_local_sbuf0_sdb_h);
	} else {
		perf_cnt_res[0] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_local_sbuf0_sdb_l + 0x10);
		perf_cnt_res[1] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_bw_local_sbuf0_sdb_h + 0x10 );
		perf_cnt_res[2] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_local_sbuf0_sdb_l + 0x10);
		perf_cnt_res[3] = *(volatile __DDR uint32_t*)(base_addr + perf_cnt_stall_local_sbuf0_sdb_h + 0x10);
	}

	bw = ((uint64_t)perf_cnt_res[1] << 32) | perf_cnt_res[0];
	stall = ((uint64_t)perf_cnt_res[3] << 32) | perf_cnt_res[2];
}

_LIBLLCD_DEVICE_VISIBILITY
inline void set_perf_cnt_sdb_local_sbuf(uint8_t apc_id, uint32_t setting, uint32_t asid, uint32_t valid_sel, uint32_t valid_sel_apc32) {
	uint64_t base_addr = 0;
	uint8_t apc_to_sbuf_flag = 0;
	uint8_t cb_wrap_flag = 0;
	get_apc_sdb_perf_cnt_base_addr(apc_id, base_addr, apc_to_sbuf_flag, cb_wrap_flag);
	set_cb_wrap_perf_cnt_sdb_local_sbuf(base_addr, cb_wrap_flag, setting, asid, valid_sel, valid_sel_apc32);
}

_LIBLLCD_DEVICE_VISIBILITY
inline void get_perf_cnt_sdb_local_sbuf(uint8_t apc_id, uint64_t& bw, uint64_t& stall) {
	uint64_t base_addr = 0;
	uint8_t apc_to_sbuf_flag = 0;
	uint8_t cb_wrap_flag = 0;
	get_apc_sdb_perf_cnt_base_addr(apc_id, base_addr, apc_to_sbuf_flag, cb_wrap_flag);
	get_cb_wrap_perf_cnt_sdb_local_sbuf(base_addr, cb_wrap_flag, bw, stall);
}
