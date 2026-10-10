/*
 * Please note that this head file is only to be called by maps-umd for initialization,
 * other usage is forbidden.
 */
#pragma once

#include <cstdint>
#include <aurora_s.h>
#include <aurora_s-intrin.h>
#include "scale.h"
#include "scale_types.h"
#include "device_scale.h"

#define _LIB_MAPS_DEVICE_RUNTIME __device__

#define AURORA_SM0_BASE_ADDR 0x88a00000ull
#define SM_APC_FLAG_REGION_0 (AURORA_SM0_BASE_ADDR + 0x20000 - 0x40)  //SM0_BASE_ADDR + 128K - 64
#define SM_APC_FLAG_REGION_1 (SM_APC_FLAG_REGION_0 + 0x20)            //SM0_BASE_ADDR + 128K - 32

#define AURORA_APC_CSU_BASE_ADDRESS 0x800000

#define AURORA_CSU_SUB_H_PREDATANUM0 (AURORA_APC_CSU_BASE_ADDRESS + 0x50)
#define AURORA_CSU_SUB_H_PREDATANUM1 (AURORA_APC_CSU_BASE_ADDRESS + 0x54)

#define AURORA_CSU_SUB_L_PREDATANUM0 (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x50)
#define AURORA_CSU_SUB_L_PREDATANUM1 (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x54)

#define AURORA_CSU_SUB_H_AXIRDNUM (AURORA_APC_CSU_BASE_ADDRESS + 0x14C0)
#define AURORA_CSU_SUB_H_AXIRANUM (AURORA_APC_CSU_BASE_ADDRESS + 0x14C4)
#define AURORA_CSU_SUB_H_AXIWDNUM (AURORA_APC_CSU_BASE_ADDRESS + 0x14C8)
#define AURORA_CSU_SUB_H_AXIWANUM (AURORA_APC_CSU_BASE_ADDRESS + 0x14CC)
#define AURORA_CSU_SUB_H_AXIRWDNUM (AURORA_APC_CSU_BASE_ADDRESS + 0x14D0)
#define AURORA_CSU_SUB_H_AXIRWANUM (AURORA_APC_CSU_BASE_ADDRESS + 0x14D4)

#define AURORA_CSU_SUB_L_AXIRDNUM (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x14C0)
#define AURORA_CSU_SUB_L_AXIRANUM (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x14C4)
#define AURORA_CSU_SUB_L_AXIWDNUM (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x14C8)
#define AURORA_CSU_SUB_L_AXIWANUM (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x14CC)
#define AURORA_CSU_SUB_L_AXIRWDNUM (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x14D0)
#define AURORA_CSU_SUB_L_AXIRWANUM (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x14D4)

#define AURORA_CSU_SUB_H_DMAWAXILIMIT (AURORA_APC_CSU_BASE_ADDRESS + 0x6C)
#define AURORA_CSU_SUB_L_DMAWAXILIMIT (AURORA_APC_CSU_BASE_ADDRESS + 0x2000 + 0x6C)


#define AURORA_WRITEADAPTER0_BASE_ADDRESS 0x880000
#define AURORA_WRITEADAPTER1_BASE_ADDRESS 0x8c0000

#define AURORA_SBUF0_BASE_ADDRESS 0x0295000000ull
#define AURORA_SBUF1_BASE_ADDRESS 0x0295100000ull
#define AURORA_SBUF2_BASE_ADDRESS 0x0295500000ull
#define AURORA_SBUF3_BASE_ADDRESS 0x0295600000ull
#define AURORA_SBUF4_BASE_ADDRESS 0x0295A00000ull
#define AURORA_SBUF5_BASE_ADDRESS 0x0295B00000ull
#define AURORA_SBUF6_BASE_ADDRESS 0x0295F00000ull
#define AURORA_SBUF7_BASE_ADDRESS 0x0296000000ull

namespace maps_device_runtime {

    _LIB_MAPS_DEVICE_RUNTIME
    static inline bool is_llcd_need_init(uint8_t apc_id) {
        uint8_t cur_apc_id = (apc_id <= 31) ? apc_id : 0;
        uint8_t in_process_flag = *(volatile  __DDR uint8_t *) (SM_APC_FLAG_REGION_0 + cur_apc_id);
        uint8_t done_flag = *(volatile  __DDR uint8_t *) (SM_APC_FLAG_REGION_1 + cur_apc_id);
        return (in_process_flag == 0) && (done_flag == 0);
    }
    
    _LIB_MAPS_DEVICE_RUNTIME
    static inline bool is_llcd_init_done(uint8_t apc_id) {
        uint8_t cur_apc_id = (apc_id <= 31) ? apc_id : 0;
        uint8_t done_flag = *(volatile __DDR uint8_t *) (SM_APC_FLAG_REGION_1 + cur_apc_id);
        return (done_flag == 1);
    }
    
    _LIB_MAPS_DEVICE_RUNTIME
    static inline void set_llcd_init_in_process_flag (uint8_t apc_id) {
        uint8_t cur_apc_id = (apc_id <= 31) ? apc_id : 0;
        *(volatile __DDR uint8_t *) (SM_APC_FLAG_REGION_0 + cur_apc_id) = 1;
    }
    
    _LIB_MAPS_DEVICE_RUNTIME
    static inline void set_llcd_init_done_flag (uint8_t apc_id) {
        uint8_t cur_apc_id = (apc_id <= 31) ? apc_id : 0;
        *( volatile __DDR uint8_t *) (SM_APC_FLAG_REGION_1 + cur_apc_id) = 1;
    }

    //////csu init configuration start
    _LIB_MAPS_DEVICE_RUNTIME
    static inline void apc_csu_init() {

    	*(volatile uint32_t*)AURORA_CSU_SUB_H_PREDATANUM0 = 0xf9f ;
    	*(volatile uint32_t*)AURORA_CSU_SUB_H_PREDATANUM1 = 0xf9f;

    	*(volatile uint32_t*)AURORA_CSU_SUB_L_PREDATANUM0 = 0xf9f;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_PREDATANUM1 = 0xf9f;

    	*(volatile uint32_t*)AURORA_CSU_SUB_H_AXIRDNUM = 0x6000;
    	*(volatile uint32_t*)AURORA_CSU_SUB_H_AXIRANUM = 0x20;
    	*(volatile uint32_t*)AURORA_CSU_SUB_H_AXIWDNUM = 0x2000;
    	*(volatile uint32_t*)AURORA_CSU_SUB_H_AXIWANUM = 0x18;
    	*(volatile uint32_t*)AURORA_CSU_SUB_H_AXIRWDNUM = 0x8000;
    	*(volatile uint32_t*)AURORA_CSU_SUB_H_AXIRWANUM = 0x30;

    	*(volatile uint32_t*)AURORA_CSU_SUB_L_AXIRDNUM = 0x6000;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_AXIRANUM = 0x20;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_AXIWDNUM = 0x2000;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_AXIWANUM = 0x18;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_AXIRWDNUM = 0x8000;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_AXIRWANUM = 0x30;

    	*(volatile uint32_t*)AURORA_CSU_SUB_H_DMAWAXILIMIT = 0xff;
    	*(volatile uint32_t*)AURORA_CSU_SUB_L_DMAWAXILIMIT = 0xff;
    }
    //////csu init configuration end

    //////writeadpater init configuration start
    struct ExtendPara {
        uint32_t data{0};
    
        static const uint64_t lut_base{0x800};
        static const uint64_t step{0x40};
        static const uint8_t extend_para_num{4};
    
        _LIB_MAPS_DEVICE_RUNTIME
        void write(uint8_t lut_index, uint64_t config_port_base) {
            //write_32bit(data, config_port_base, lut_base, lut_index * step, "WriteAdapter::ExtendPara");
            __aurora_s_fenceD();
            *(volatile __DDR uint32_t*)(config_port_base + lut_base + lut_index * step) = data;
            __aurora_s_fenceD();
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        static void init_regs(uint64_t config_port_base) {
            for (auto i = 0; i < extend_para_num; ++i) {
                ExtendPara default_word;
                default_word.write(i, config_port_base);
            }
        }
    };

    struct KRegion {
        uint32_t data{0};

        static const uint64_t lut_base{0xc00};
        static const uint64_t step{0x4};
        static const uint8_t kregion_num{32};
    
        _LIB_MAPS_DEVICE_RUNTIME
        void write(uint8_t lut_index, uint64_t config_port_base) {
            //write_32bit(data, config_port_base, lut_base, lut_index * step, "WriteAdapter::KRegion");
            __aurora_s_fenceD();
            *(volatile __DDR uint32_t*)(config_port_base + lut_base + lut_index * step) = data;
            __aurora_s_fenceD();
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        static void init_regs(uint64_t config_port_base) {
            for (auto i = 0; i < kregion_num; ++i) {
                KRegion default_word;
                default_word.write(i, config_port_base);
            }
        }
    };

    struct CompressInfoLut {
        uint32_t data{0b00000010000000100000001000000010};
        static const uint64_t lut_base{0x0};
        static const uint64_t step{0x4};
        static const uint8_t compress_info_lut_word_num{16};
    
        _LIB_MAPS_DEVICE_RUNTIME
        void write(uint8_t lut_index_by_word, uint64_t config_port_base) {
            //write_32bit(data, config_port_base, lut_base, lut_index_by_word * step, "WriteAdapter::CompressInfo");
            __aurora_s_fenceD();
            *(volatile __DDR uint32_t*)(config_port_base + lut_base + lut_index_by_word * step) = data;
            __aurora_s_fenceD();

        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        static void init_luts(uint64_t config_port_base) {
            for (auto i = 0; i < compress_info_lut_word_num; ++i) {
                CompressInfoLut default_lut;
                default_lut.write(i, config_port_base);
            }
        }
    };

    struct WriteAdapterLutEntry {
        uint32_t mask_num:4;
        uint32_t swap_size:2;
        uint32_t gran_type:2;
        uint32_t k_region_addr:5;
        uint32_t extend_type:2;
        uint32_t acc_type:2;
        uint32_t acc_en:1;
        uint32_t start_addr:17;    //dm_addr = start_addr<<2
        uint32_t ksize:4;
        uint32_t cgran:1;
        uint32_t gran:3;
        uint32_t dm_region_en:4;
        uint32_t onek_addr:8;
    }__attribute__((packed, aligned(8)));
    
    struct WriteAdapterLut {
    
        WriteAdapterLutEntry lut_entry = {0};
    
        static const uint64_t lut_base{0x4000};
        static const uint64_t lut_step{0x8};

        _LIB_MAPS_DEVICE_RUNTIME
        void set_gran(uint8_t value) {
            lut_entry.gran = value;
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        void set_cgran(uint8_t value) {
            lut_entry.cgran = value;
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        void set_ksize(uint8_t value) {
            lut_entry.ksize = value;
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        void set_swap_size(uint8_t value) {
            lut_entry.swap_size = value;
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        void set_gran_type(uint8_t value) {
            lut_entry.gran_type = value;
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        void write(uint16_t lut_index, uint64_t config_port_base) {
            auto lut_offset = lut_index * lut_step;
            uint32_t *words = (uint32_t *) &lut_entry;
            //write_32bit(words[0], config_port_base, lut_base, lut_offset, "WriteAdapter::LUT");
            //write_32bit(words[1], config_port_base, lut_base, lut_offset+0x4, "WriteAdapter::LUT");
            *(volatile __DDR uint32_t*)(config_port_base + lut_base + lut_offset) = words[0];
            *(volatile __DDR uint32_t*)(config_port_base + lut_base + lut_offset + 4) = words[1];
            __aurora_s_fenceD();
        }

        _LIB_MAPS_DEVICE_RUNTIME
        static WriteAdapterLutEntry gen_default_lut(uint16_t lut_index) {
            WriteAdapterLutEntry entry = {0};
            entry.acc_en = 0;       //disable acc by default
            entry.acc_type = 0;
            entry.dm_region_en = 1; // csu port should not reconfig lut
            entry.swap_size = 3;
            entry.gran_type = 0;
            return entry;
        }

        _LIB_MAPS_DEVICE_RUNTIME
        static void write_wa_lut_sel_csu(bool cgran, uint8_t gran, uint8_t ksize, uint8_t swap_size, uint8_t gran_type, uint16_t lut_index, uint64_t config_port_base) {
    
            WriteAdapterLut wa_lut = {0};
            wa_lut.lut_entry = WriteAdapterLut::gen_default_lut(lut_index);
            wa_lut.set_gran(gran);
            wa_lut.set_cgran(cgran);
            wa_lut.set_ksize(ksize);
            wa_lut.set_swap_size(swap_size);
            wa_lut.set_gran_type(gran_type);
            //select writeadapter CSU outport 
            wa_lut.lut_entry.start_addr = 0x1C000; //0b1 1100 0000 0000 0000
            wa_lut.write(lut_index, config_port_base);
        }
    };

    _LIB_MAPS_DEVICE_RUNTIME
    static inline void writeadapter_init(uint64_t config_port_base) {
	    CompressInfoLut::init_luts(config_port_base);
	    KRegion::init_regs(config_port_base);
	    ExtendPara::init_regs(config_port_base);
	    //select writeadapter CSU outport 
	    //use wa lut_index=2047 for broadcast configuration across apcs
	    WriteAdapterLut::write_wa_lut_sel_csu(1, 4, 0xc, 3, 0, 2047, config_port_base);
	    //use wa lut_index=2046 for outband2 configuration
	    WriteAdapterLut::write_wa_lut_sel_csu(1, 4, 0xc, 3, 0, 2046, config_port_base);
    }
    
    _LIB_MAPS_DEVICE_RUNTIME
    static inline void apc_writeadapter_init() {
	    writeadapter_init(AURORA_WRITEADAPTER0_BASE_ADDRESS);
	    writeadapter_init(AURORA_WRITEADAPTER1_BASE_ADDRESS);
    }
    //////writeadpater init configuration end

    //////sbuf init configuration start
    struct SbufLutEntry
    {
        uint32_t int_id:11;
        uint32_t src_id:5;
        uint32_t endframe_offset:4;
        uint32_t low_byte_mask:2;
        uint32_t new_lut_addr:13;
        uint64_t seg_infos:45;
        uint64_t apc_valid_local:36;
        uint64_t apc_valid_remote:36;
        uint32_t slc_valid:1;
        uint32_t saac_valid:1;
        uint32_t pkg_valid:9;
        uint32_t acc_type:2;
        uint32_t extend:1;
        uint32_t olen:4;
    
    }__attribute__((packed, aligned(32)));
    
    struct SbufLut
    {
        SbufLutEntry lut_entry = {0};
    
        static const uint64_t lut_base{0x0};
        static const uint64_t lut_step{0x20};
    
        _LIB_MAPS_DEVICE_RUNTIME
        void write(uint16_t lut_index, uint64_t config_port_base) {
            auto lut_offset = lut_index * lut_step;
            //write_256bit((uint32_t *)&lut_entry, config_port_base, lut_base, lut_offset, "SBUF::LUT");
            uint32_t *words = (uint32_t *)&lut_entry;
            v8u32 value = {words[0], words[1], words[2], words[3], words[4], words[5], words[6], words[7]};
            __aurora_s_fenceD();
            __aurora_s_configV256_ext(config_port_base + lut_base + lut_offset, value, 0);
            __aurora_s_fenceD();
        }
 
        _LIB_MAPS_DEVICE_RUNTIME
        void set_single_apc_valid(uint16_t lut_index) {
            if (lut_index < 33) {
                lut_entry.apc_valid_local = 1ULL << lut_index;
            } else if (lut_index == 33) {
                lut_entry.slc_valid = 1;
            }
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        static SbufLutEntry gen_default_lut(uint16_t lut_index) {
            SbufLutEntry entry = {0};
            entry.endframe_offset = 15;
            entry.new_lut_addr = lut_index;
            entry.seg_infos |= 0x180;   //lut.attrs["seg_infos"], {7, 8}); 4bit lengthinfo, 1100 = 12
            entry.olen = 12;
            return entry;
        }
    
        _LIB_MAPS_DEVICE_RUNTIME
        static void init_luts(uint64_t config_port_base) {
            SbufLut sbuf_lut = {0};
            //Initialize lut index 0-32 for apc 0-32 unicast usage, lut_index 33 for sbuf to slc
            for (auto i = 0; i <= 33; ++i) {
                sbuf_lut.lut_entry = gen_default_lut(i);
                sbuf_lut.set_single_apc_valid(i);
                sbuf_lut.write(i, config_port_base);
            }
        }
    };
    
    _LIB_MAPS_DEVICE_RUNTIME
    static inline void sbuf_init() {
	    SbufLut::init_luts(AURORA_SBUF0_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF1_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF2_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF3_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF4_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF5_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF6_BASE_ADDRESS);
	    SbufLut::init_luts(AURORA_SBUF7_BASE_ADDRESS);
    }
    //////sbuf init configuration end
}
