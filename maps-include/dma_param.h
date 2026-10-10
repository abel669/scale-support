#pragma once
#include <cstdint>

#include "libllcd.h"
#include "vec.h"

enum devRunError_t {
	Success = 0,
	InvalidDmaSrc,
	InvalidDmaDst,
	InvalidDmaID,
	InvalidMemcpyDirection,
	DmaNotCompletedError,
	DmaFetchFifoFullError
};

enum AccType {
	Fixed32=0,
	Fixed64,
	Float32,
	Float64
};

enum AlignType {
	None=0,
	Byte4,
	Byte16,
	Byte32,
	Byte64,
	Byte128
};

enum MemType {
	Dm=0,
	Hbm
};

enum deviceMemcpyKind {
	deviceMemcpyHbmToDm=0,
	deviceMemcpyDmToHbm,
	deviceMemcpyDmToDm,
	deviceMemcpyDmToDmBdCast,
	deviceMemcpyHbmToHbm
};
enum CSUDataPath {
    AXI_M2 = 0,
    AXI_M0 = 1,
    APE = 3,
    Sbuf = 4,
    WriteAdapter = 6
};

struct CSUPort {

	uint8_t dpath_sel{CSUDataPath::AXI_M0};
	uint8_t write_flag{0};

    _LIBLLCD_DEVICE_VISIBILITY
    uint8_t is_axi() const { return dpath_sel == CSUDataPath::AXI_M0; }
    _LIBLLCD_DEVICE_VISIBILITY
    uint8_t is_sbuf() const { return dpath_sel == CSUDataPath::Sbuf; }
    _LIBLLCD_DEVICE_VISIBILITY
    uint8_t is_ape() const { return dpath_sel == CSUDataPath::APE; }
    _LIBLLCD_DEVICE_VISIBILITY
    uint8_t is_write() const { return write_flag == 1; }
};

struct DMAPara1Padding {
	uint32_t postwnum:12;           //12bits, 11:0
	uint32_t repeat_num1_dim_2:4;   //4bits, 15:12
	uint32_t repeat_num1_dim_1:4;   //4bits, 19:16
	uint32_t repeat_num0_dim_1:4;   //4bits, 23:20
	uint32_t wnum_en:1;             //1bit, 24
	uint32_t repeat_en_sel_dim_2:1;  //1bit, 25
	uint32_t repeat_en_sel_dim_1:2;  //2bit, 27:26
	uint32_t repeat_step_sel_dim_2:2;  //2bit, 29:28
	uint32_t repeat_step_sel_dim_1:2;  //2bit, 31:30
};

struct DMAPara2Padding {
	uint32_t prewnum:12;          //12bits, 11:0
	uint32_t repeat_num0_dim_2:4; //4bits, 15:12
	uint32_t c_len:16;            //16bits, 31:16
};

struct DMAPara3Padding {
	uint32_t patid:3;          //3bits, 2:0
	uint32_t usepat:1;         //1bit,  3
	uint32_t cmode:4;          //4bits, 7:4
	uint32_t paddk:2;          //2bits, 9:8
	uint32_t columnmode:2;     //2bits, 11:10
	uint32_t resv1:3;          //3bits, 14:12
	uint32_t dim_sel:1;        //1bit,  15
	uint32_t rdata_length:6;      //6bits  21:16
	uint32_t first_rdata_cut_en:1;       //1bit, 22
	uint32_t data_for_mat:3;             //3bit, 25:23
	uint32_t data_type:2;                //2bit, 27:26
	uint32_t data_for_mat_conversion:4;  //3bit, 31:28
};

struct DMAParaLReg {
    uint32_t axiqos_dmasize_pkgen03:4;         // 4 bits,  3:0
    uint32_t acesnoop_dmagran_pkgen47:4;       // 4 bits,  7:4
    uint32_t acedom_overflow:2;                // 2 bits,  9:8
    uint32_t axiprot_burstlen:3;               // 3 bits,  12:10
    uint32_t axilock_bursten:1;                // 1 bits,  13
    uint32_t axiuser_obuser_obasid:10;         // 10 bits, 23:14
    uint32_t axicache_convert_type:5;          // 5 bits,  28:24
    uint32_t dpath_sel:3;                      // 3 bits,  31:29
};

struct DMACmdDesc {
    uint32_t list_mode_s:1;
    uint32_t list_mode_d:1;
    uint32_t unalign:1;
    uint32_t paden:1;                  //if enable padding
    uint32_t continue_next_dma:1;      //default value =1
    uint32_t continue_last_dma:1;      //default value =1
    uint32_t buffer_id_s:5;            // 5 bits, dma param reg id of src
    uint32_t buffer_id_d:5;            // 5 bits, dma param reg id of dst
    uint32_t cmd_tag:5;                // 5 bits, command id
    uint32_t outband_extend:1;
    uint32_t burst_len:2;              // 2 bits, default value =5
    uint32_t pri_shift:1;              // 1 bit, if set cmd to high priority
    uint32_t long_list_en:1;           // 1 bit
    uint32_t resv:3;                   // 3 bits, reserved
    uint32_t drop:1;
    uint32_t allnum_sel:1;             // 1 bit
    uint32_t stall:1;                 // Does it support modification during blocking
};

struct PaddingPatternInfo {
	uint8_t info[64];
}__attribute__((packed, aligned(64)));

struct DataParam {

	uint64_t address{0};
	uint32_t allnum;
	uint32_t xnum;
	uint32_t ystep;
	uint32_t zstep;
	uint16_t ynum;
	uint8_t element_size;

	// col/row mode of dm
	bool cgran{1};
	uint8_t gran{4};
	uint8_t ksize{0xc};

	uint8_t dm_access_mode{0};

	//padding
	uint8_t pad_en{0};
	uint32_t padding_param0{0};
	uint32_t padding_param1{0};
	uint32_t padding_param2{0};
	uint16_t padding_znum{0};

	uint16_t sbuf_lut_index{0};
	uint16_t wa_lut_index{0};


	_LIBLLCD_DEVICE_VISIBILITY
	void set_dm_access_mode(uint8_t unalign) {
		dm_access_mode = (unalign > 0) ? 1 : 0;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_element_size() const {
		return element_size;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint32_t get_byte_allnum() const {
		return allnum * get_element_size();
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint32_t get_byte_xnum() const{
		return xnum * get_element_size();
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint32_t get_byte_ystep() const{
		return ystep * get_element_size();
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint16_t get_byte_ynum() const{
		return ynum;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint32_t get_byte_zstep() const{
		return zstep * get_element_size();
	}
	_LIBLLCD_DEVICE_VISIBILITY
	bool get_cgran() const{
		return cgran;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_gran() const{
		return gran;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_ksize() const{
		return ksize;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	static DataParam construct_dm_param(
		uint32_t dm_addr, uint8_t element_size,
		uint32_t allnum, uint32_t xnum, uint32_t ystep, uint16_t ynum, uint32_t zstep,
		bool cgran=1, uint8_t gran=4, uint8_t ksize=0xc) {

		DataParam data_param;

		data_param.address = dm_addr;
		data_param.element_size = element_size;
		data_param.allnum = allnum;
		data_param.xnum = xnum;
		data_param.ystep = ystep;
		data_param.ynum = ynum;
		data_param.zstep = zstep;

		// col/row mode of dm
		data_param.cgran = cgran;
		data_param.gran = gran;
		data_param.ksize = ksize;

		return data_param;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	static DataParam construct_bdcast_dm_param(
		uint16_t sbuf_lut_index, uint16_t wa_lut_index, uint8_t element_size,
		uint32_t allnum, uint32_t xnum, uint32_t ystep, uint16_t ynum, uint32_t zstep) {

		DataParam data_param;

		data_param.element_size = element_size;
		data_param.allnum = allnum;
		data_param.xnum = xnum;
		data_param.ystep = ystep;
		data_param.ynum = ynum;
		data_param.zstep = zstep;

		data_param.sbuf_lut_index = sbuf_lut_index;
		data_param.wa_lut_index = wa_lut_index;

		return data_param;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	static DataParam construct_hbm_param(
		uint64_t address, uint8_t element_size,
		uint32_t allnum, uint32_t xnum, uint32_t ystep, uint16_t ynum, uint32_t zstep) {

		DataParam data_param;

		data_param.address = address;
		data_param.element_size = element_size;
		data_param.allnum = allnum;
		data_param.xnum = xnum;
		data_param.ystep = ystep;
		data_param.ynum = ynum;
		data_param.zstep = zstep;

		return data_param;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	void configure_padding_param(DMAPara1Padding &pad1, DMAPara2Padding &pad2, DMAPara3Padding &pad3, uint16_t pad_znum) {
		pad_en = 1;
		padding_param0 = *(uint32_t*)(&pad1);
		padding_param1 = *(uint32_t*)(&pad2);
		padding_param2 = *(uint32_t*)(&pad3);
		padding_znum = pad_znum;
	}
	_LIBLLCD_DEVICE_VISIBILITY
	void configure_cast_type(uint32_t type) {
		padding_param2 |= (type << 28);
	}
};

struct DmaFetchParam {
	uint32_t addr_l32;
	uint32_t addr_h24:24;
	uint32_t resv1:8;
	uint32_t ystep_l32;
	uint32_t ystep_h24:24;
	uint32_t resv2:8;
	uint32_t zstep_l32;
	uint32_t zstep_h24:24;
	uint32_t resv3:8;
	uint32_t ynum;
	uint32_t allnum;
	uint32_t dmaparal;
	uint32_t dmaparam;
	uint32_t dmaparah;
	uint32_t dmaparahh;
	uint32_t xnum;
	uint32_t resv4;
	uint32_t resv5;
	uint32_t cmd;

	_LIBLLCD_DEVICE_VISIBILITY
	void write_dma_addr(uint64_t addr, uint32_t x_num, uint32_t ystep, uint16_t y_num, uint32_t zstep, uint32_t all_num, uint16_t pad_znum=0) {
		addr_l32 = (uint32_t) addr;
		addr_h24 = (uint32_t) (addr >> 32);
		ystep_l32 = ystep;
		zstep_l32 = zstep;
		ynum = y_num;
		allnum = (all_num | ((uint32_t)pad_znum << 22));
		xnum = x_num;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_dma_addr(uint64_t addr) {
		addr_l32 = (uint32_t) addr;
		addr_h24 = (uint32_t) (addr >> 32);
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_ctrl_param(uint32_t param[4]) {
		dmaparal = param[0];
		dmaparam = param[1];
		dmaparah = param[2];
		dmaparahh = param[3];
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_cmd(uint32_t dma_cmd) {
		cmd = dma_cmd;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_dm_param(uint32_t dm_addr, uint32_t all_num, uint32_t x_num, uint32_t ystep, uint16_t y_num, uint32_t zstep, bool cgran=1, uint8_t gran=4, uint8_t ksize=0xc) {

		addr_l32 = (uint32_t)dm_addr;
		addr_h24 = 0;
		ystep_l32 = ystep;
		zstep_l32 = zstep;
		ynum = y_num;
		allnum = all_num;
		xnum = x_num;

		DMAParaLReg &dmapara0 = *reinterpret_cast<DMAParaLReg *>(&dmaparal);
		dmapara0.axiqos_dmasize_pkgen03 = ksize;                  //data_param.get_ksize();
		dmapara0.acesnoop_dmagran_pkgen47 = (cgran << 3) + gran;  //(data_param.get_cgran() << 3) + data_param.get_gran();
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_hbm_param(uint64_t address, uint32_t all_num, uint32_t x_num, uint32_t ystep, uint16_t y_num, uint32_t zstep) {
		addr_l32 = (uint32_t) address;
		addr_h24 = (uint32_t) (address >> 32);
		ystep_l32 = ystep;
		zstep_l32 = zstep;
		ynum = y_num;
		allnum = all_num;
		xnum = x_num;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_bdcast_dm_param(uint16_t sbuf_lut_index, uint16_t wa_lut_index, uint32_t all_num, uint32_t x_num, uint32_t ystep, uint16_t y_num, uint32_t zstep) {

		uint64_t csu_dma_dst_addr = 0;
		uint64_t wa_dst_addr = ((uint64_t)wa_lut_index << 18);
		csu_dma_dst_addr = (wa_dst_addr & 0x7ffffffffff) + ((uint64_t)sbuf_lut_index << 43);

		addr_l32 = (uint32_t) csu_dma_dst_addr;
		addr_h24 = (uint32_t) (csu_dma_dst_addr >> 32);
		ystep_l32 = ystep;
		zstep_l32 = zstep;
		ynum = y_num;
		allnum = all_num;
		xnum = x_num;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_outband2_dm_param(uint16_t wa_lut_index, uint32_t all_num, uint32_t x_num, uint32_t ystep, uint16_t y_num, uint32_t zstep) {

		uint64_t csu_dma_dst_addr = (uint64_t)wa_lut_index << 18;

		addr_l32 = (uint32_t) csu_dma_dst_addr;
		addr_h24 = (uint32_t) (csu_dma_dst_addr >> 32);
		ystep_l32 = ystep;
		zstep_l32 = zstep;
		ynum = y_num;
		allnum = all_num;
		xnum = x_num;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_dma_para0_cmd_param(CSUDataPath data_path, uint8_t asid) {
		DMAParaLReg &dmapara0 = *reinterpret_cast<DMAParaLReg *>(&dmaparal);
		dmapara0.dpath_sel = data_path;
		dmapara0.axiuser_obuser_obasid = asid;
		if ((data_path == CSUDataPath::Sbuf) || (data_path == CSUDataPath::WriteAdapter)) { //datapath = 4 or 6 are outband, 4 is sbuf
			dmapara0.axiprot_burstlen = 5;
			dmapara0.axilock_bursten = 1;
		}
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_dma_para0_cmd_outband2_pkgen(uint8_t apc_id) {

		constexpr uint8_t apc_id_to_outband2_pkgen[32] = {
	    	0, 1, 2, 3,
			0, 1, 2, 3,
			0, 1, 2, 3,
			0, 1, 2, 3,
			7, 6, 5, 4,
			7, 6, 5, 4,
			7, 6, 5, 4,
			7, 6, 5, 4
	    };
		DMAParaLReg &dmapara0 = *reinterpret_cast<DMAParaLReg *>(&dmaparal);
		if (apc_id < 16) {
			dmapara0.axiqos_dmasize_pkgen03 |= (1<< apc_id_to_outband2_pkgen[apc_id]);
		} else {
			dmapara0.acesnoop_dmagran_pkgen47 |= (1<< (apc_id_to_outband2_pkgen[apc_id] - 4));
		}
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_cmd(uint8_t fifo_id, uint8_t dma_tag, uint8_t un_align, uint8_t pad_en, uint8_t dm_hbm_cast_en) {

		DMACmdDesc &cmd_desc = *reinterpret_cast<DMACmdDesc *>(&cmd);
		//DMAPara3Padding &para3_padding = *reinterpret_cast<DMAPara3Padding *>(&dmaparahh);  
		//uint8_t dm_hbm_cast_en = para3_padding.data_for_mat_conversion;
		
		if(!dm_hbm_cast_en) {
			cmd_desc.buffer_id_s = fifo_id * 2;
			cmd_desc.buffer_id_d = fifo_id * 2 + 1;
		} else {
			cmd_desc.buffer_id_s = fifo_id * 2 + 1;
			cmd_desc.buffer_id_d = fifo_id * 2;
		}		
		cmd_desc.cmd_tag = dma_tag;
		cmd_desc.unalign = un_align;
		cmd_desc.paden = pad_en;
		cmd_desc.allnum_sel = 1;
		cmd_desc.continue_last_dma = 1;
		cmd_desc.continue_next_dma = 1;
		cmd_desc.burst_len = 3;
		//handle.cmdfifo_id = fifo_id;
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_padding_param(DMAPara1Padding &pad1, DMAPara2Padding &pad2, DMAPara3Padding &pad3, uint16_t pad_znum) {
		dmaparam = *(uint32_t*)(&pad1);
		dmaparah = *(uint32_t*)(&pad2);
		dmaparahh = *(uint32_t*)(&pad3);
		allnum = (allnum | ((uint32_t)pad_znum << 22));	
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_cast_type(uint8_t type) {
		DMAPara3Padding &para3_padding = *reinterpret_cast<DMAPara3Padding *>(&dmaparahh);
		para3_padding.data_for_mat_conversion = type;
	}

}__attribute__((packed, aligned(64)));

struct DmaFetchData {
	DmaFetchParam s;
	DmaFetchParam d;
}__attribute__((packed, aligned(128)));

struct DmaFetchDataPad {
	DmaFetchParam s;
	PaddingPatternInfo p;
	DmaFetchParam d;
	//DmaFetchParam dummy;

	_LIBLLCD_DEVICE_VISIBILITY
	void write_pattern_info(const PaddingPatternInfo &pat_info) {
		p = pat_info;
	}
}__attribute__((packed, aligned(128)));

struct DMAHandle
{
	uint8_t ape_id{0};
	uint8_t cmd_tag{0};
	uint8_t cmdfifo_id{0};
	uint8_t hbm_write_flag{0xff};
	uint8_t need_switch_flag{0};
	uint8_t user_asid{0};

	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_cmd_tag() const { return cmd_tag; }
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_cmdfifo_id() const { return cmdfifo_id; }
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_src_reg_id() const { return cmd_tag*2; }
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_dst_reg_id() const { return cmd_tag*2 + 1; }

	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t is_need_switch() const { return need_switch_flag == 1; }

	_LIBLLCD_DEVICE_VISIBILITY
	void set_ape_id(uint8_t ape_num) { ape_id = ape_num; }
	_LIBLLCD_DEVICE_VISIBILITY
	void set_cmd_tag(uint8_t tag_id) { cmd_tag = tag_id; }
	_LIBLLCD_DEVICE_VISIBILITY
	void set_cmdfifo_id(uint8_t fifo_id) { cmdfifo_id = fifo_id; }

	_LIBLLCD_DEVICE_VISIBILITY
	void set_hbm_write_flag(uint8_t flag) { hbm_write_flag = (flag > 0) ? 1 : 0; }
	_LIBLLCD_DEVICE_VISIBILITY
	void set_need_switch_flag(uint8_t flag) { need_switch_flag = (flag > 0) ? 1 : 0; }

	_LIBLLCD_DEVICE_VISIBILITY
	void set_user_asid(uint8_t asid) { user_asid = asid < 32 ? asid : 0; }
	_LIBLLCD_DEVICE_VISIBILITY
	uint8_t get_user_asid() const { return user_asid; }
};

struct SbufCfgWrData
{
    uint32_t data0;
    uint32_t data1;
    uint32_t data2;
    uint32_t data3;
    uint32_t mask:4;
    uint32_t resv1:4;
    uint64_t addr_d:56;
    uint32_t resv2:8;
    uint32_t para_sel_d:3;
    uint32_t resv3:5;
    uint32_t dpath_sel_d:3;
    uint32_t resv4:15;
    uint32_t asid_d:5;
    uint32_t resv5:3;
    uint32_t atomic:1;
    uint32_t resv6:21;
}__attribute__((packed, aligned(64)));

typedef SbufCfgWrData Outband2CfgWrData;

struct sdma_cmd_write_t {
    uint64_t addr_r:48;//47:0
    uint64_t nbytes_s_h:8;//55:48 //combine with nbytes_s_l
    uint64_t asid_r:5;//60:56
    uint64_t noc_r:1;//61 //whether go throught noc for reading
    uint64_t resv:2;//63:62
    uint64_t addr_w:56;//119:64
    uint64_t asid_w:5;//124:120
    uint64_t extend_noc:1;//125 //for write: extend for pkg or d2d; whether go through noc for axi
    uint64_t sel_aisle:2;//127:126 //00: use axi to DDR/DM/SM, remote DIE DDR/DM/SM; 01: PKG; 10:SLM to remote DIE; 11: SBUF to remote DIE
    uint64_t nbytes_s_l:32;//159:128 //combine with nbytes_s_h
    uint64_t pkg_int:11;//170:160 //if sel_aisle is 01, it is map of pkg. if sel_aisle is other value, it is int count
    uint64_t ddr_flag:1;//171 //1: need all burst valid response received for next writing;
    uint64_t resv1:4;//175:172
    uint64_t write_status:1;//176 //write command status to the following 256bit with the value of sdma_response_t
    uint64_t block_size:4;//180:177 //0:1KB, 1:2KB, 2:4KB,... 9:512KB
    uint64_t resv2:1;//181
    uint64_t check_cancel:1;//182 //if sel_aisle is 01, 0: no need check cancel flag, 1:check cannel flag from snbm
    uint64_t clear_space:1;//183 //0: keep space for next command, 1:clear space, and the next command will request new space from snbm
    uint64_t snbm:1;//184 //0: no depend on snbm, 1:need request space from snbm
    uint64_t snbm_id:7;//191:185
    uint64_t d2d_dst:35;//226:192
    uint64_t sbuf_flag:1;//227 //valible when sel_aisle is 10 or 11
    uint64_t resv3:12;//239:228
    uint64_t dm_op_r:2;//241:240 DM op code, aruser[8:7](atomic)
    uint64_t resv4:2;//243:242
    uint64_t axi_op:2;//245:244
    uint64_t resv5:2;//247:246
    uint64_t dm_op_w:2;//249:248 DM op code, aruser[8:7](atomic)
    uint64_t resv6:2;//251:250
    uint64_t axi_sig:2;//253:252
    uint64_t mode_3d:2;//255:254 //00: xnum=allnum, continus; 01:use the previous xnum, step... 10:config xnum, ynum, ystep, zstep, no start DMA; 11:config ystep, ztep, no start DMA
} __attribute__((packed));
static_assert(sizeof(sdma_cmd_write_t) == 32, "sdma_cmd_write_t must be 32 Bytes");

struct sdma_cmd_10_t {
    uint64_t xnum_r:32;//31:0
    uint64_t ystep_r:32;//63:32
    uint64_t zstep_r:32;//95:64
    uint64_t ynum_r:30;//125:96
    uint64_t resv:2;//127:126
    uint64_t xnum_w:32;//159:128
    uint64_t ystep_w:32;//191:160
    uint64_t zstep_w:32;//223:192
    uint64_t ynum_w:30;//253:224
    uint64_t mode_3d:2;//255:254 //value 10 is accepted only
} __attribute__((packed));
static_assert(sizeof(sdma_cmd_10_t) == 32, "sdma_cmd_10_t must be 32 Bytes");

struct sdma_cmd_11_t {
    uint64_t ystep_r:40;//39:0
    uint64_t resv1:24;//63:40
    uint64_t zstep_r:40;//103:64
    uint64_t resv2:24;//127:104
    uint64_t ystep_w:40;//167:128
    uint64_t resv3:24;//191:168
    uint64_t zstep_w:40;//231:192
    uint64_t resv4:22;//253:232
    uint64_t mode_3d:2;//255:254 //value 11 is accepted only
} __attribute__((packed));
static_assert(sizeof(sdma_cmd_11_t) == 32, "sdma_cmd_11_t must be 32 Bytes");

enum aisle_t {
    AXI = 0,
    SDMA_PKG = 1,
    SLM_D2D = 2,
    SBUF_D2D = 3,
    SBUF_LOCAL = 4
};

struct SdmaCmdData
{
	v8u32 cmd[3];

	_LIBLLCD_DEVICE_VISIBILITY
	void write_src_param(uint64_t address, uint64_t allnum, uint32_t xnum, uint64_t ystep, uint32_t ynum, uint64_t zstep) {
		sdma_cmd_10_t *pcmd10 = (sdma_cmd_10_t*)&cmd[0];
		sdma_cmd_11_t *pcmd11 = (sdma_cmd_11_t*)&cmd[1];
		sdma_cmd_write_t *pcmd = (sdma_cmd_write_t *)&cmd[2];

		pcmd->addr_r = address;
		pcmd->nbytes_s_h = (allnum >> 32) & 0xff;
		pcmd->nbytes_s_l = allnum;
		//pcmd->asid_r = asid;
		pcmd10->xnum_r = xnum;
		pcmd10->ynum_r = ynum;
		pcmd10->ystep_r = ystep;
		pcmd10->zstep_r = zstep;
		pcmd11->ystep_r = ystep;
		pcmd11->zstep_r = zstep;
		dbg_print("%s %llx %x %x %x %x %x %x %llx %llx\n", \
			__func__, pcmd->addr_r, pcmd->nbytes_s_h, pcmd->nbytes_s_l, pcmd10->xnum_r, \
			pcmd10->ynum_r, pcmd10->ystep_r, pcmd10->zstep_r, pcmd11->ystep_r, pcmd11->zstep_r);
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_dst_param(uint64_t address, uint64_t allnum, uint32_t xnum, uint64_t ystep, uint32_t ynum, uint64_t zstep) {
		sdma_cmd_10_t *pcmd10 = (sdma_cmd_10_t*)&cmd[0];
		sdma_cmd_11_t *pcmd11 = (sdma_cmd_11_t*)&cmd[1];
		sdma_cmd_write_t *pcmd = (sdma_cmd_write_t *)&cmd[2];

		pcmd->addr_w = address;
		//pcmd->asid_w = asid;
		pcmd10->xnum_w = xnum;
		pcmd10->ynum_w = ynum;
		pcmd10->ystep_w = ystep;
		pcmd10->zstep_w = zstep;
		pcmd11->ystep_w = ystep;
		pcmd11->zstep_w = zstep;
		pcmd10->mode_3d = 2;
		pcmd11->mode_3d = 3;
		pcmd->mode_3d = 1;
		dbg_print("%s %llx %x %x %x %x %llx %llx %x %x %x\n", \
			__func__, pcmd->addr_w, pcmd10->xnum_w, pcmd10->ynum_w, pcmd10->ystep_w, pcmd10->zstep_w, \
			pcmd11->ystep_w, pcmd11->zstep_w, pcmd10->mode_3d, pcmd11->mode_3d, pcmd->mode_3d);
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void write_bdcast_dst_param(uint16_t sbuf_lut_index, uint16_t wa_lut_index, uint64_t allnum, uint32_t xnum, uint64_t ystep, uint32_t ynum, uint64_t zstep) {
		sdma_cmd_10_t *pcmd10 = (sdma_cmd_10_t*)&cmd[0];
		sdma_cmd_11_t *pcmd11 = (sdma_cmd_11_t*)&cmd[1];
		sdma_cmd_write_t *pcmd = (sdma_cmd_write_t *)&cmd[2];

		uint64_t sdma_dst_addr = 0;
		uint64_t wa_dst_addr = ((uint64_t)wa_lut_index << 18);
		sdma_dst_addr = (wa_dst_addr & 0x7ffffffffff) + ((uint64_t)sbuf_lut_index << 43);

		pcmd->addr_w = sdma_dst_addr;
		//pcmd->asid_w = asid;
		pcmd10->xnum_w = xnum;
		pcmd10->ynum_w = ynum;
		pcmd10->ystep_w = ystep;
		pcmd10->zstep_w = zstep;
		pcmd11->ystep_w = ystep;
		pcmd11->zstep_w = zstep;
		pcmd10->mode_3d = 2;
		pcmd11->mode_3d = 3;
		pcmd->mode_3d = 1;
		dbg_print("%s %llx %x %x %x %x %llx %llx %x %x %x\n", \
			__func__, pcmd->addr_w, pcmd10->xnum_w, pcmd10->ynum_w, pcmd10->ystep_w, pcmd10->zstep_w, \
			pcmd11->ystep_w, pcmd11->zstep_w, pcmd10->mode_3d, pcmd11->mode_3d, pcmd->mode_3d);
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void set_sdma_aisle(aisle_t sel_aisle) {

		sdma_cmd_write_t *pcmd = (sdma_cmd_write_t *)&cmd[2];
		switch (sel_aisle) {
			case AXI:
				pcmd->sel_aisle = 0;
				pcmd->sbuf_flag = 0;
				break;
			case SDMA_PKG:
				pcmd->sel_aisle = 1;
				pcmd->sbuf_flag = 0;
				break;
			case SLM_D2D:
				pcmd->sel_aisle = 2;
				pcmd->sbuf_flag = 0;
				break;
			case SBUF_D2D:
				pcmd->sel_aisle = 3;
				pcmd->sbuf_flag = 0;
				break;
			case SBUF_LOCAL:
				pcmd->sel_aisle = 3;
				pcmd->sbuf_flag = 1;
				break;
		}
		dbg_print("sel_aisle=%d, sbuf_flag=%d\n", pcmd->sel_aisle, pcmd->sbuf_flag);
	}

	_LIBLLCD_DEVICE_VISIBILITY
	void set_asid(uint8_t asid) {
		sdma_cmd_write_t *pcmd = (sdma_cmd_write_t *)&cmd[2];
		pcmd->asid_r = asid;
		pcmd->asid_w = asid;
	}
};
