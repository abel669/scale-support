#pragma once
#include <stddef.h>
#include <stdint.h>

#define CONTROL_TASK_BASE 0x400210000ull
#define GPU_ID_BASE 0x4002100f0ull
#define ROUTE_BASE 0x400210100ull

enum {
    GPU_TYPE_UNKNOWN = 0,
    GPU_TYPE_QEMU,
    GPU_TYPE_EMU,
    GPU_TYPE_PLD = GPU_TYPE_EMU,
    GPU_TYPE_HAPS,
    GPU_TYPE_ASIC_EVB,
    GPU_TYPE_ASIC_OAM,
    GPU_TYPE_HOST = 0x10,
    GPU_TYPE_CAST,
};

/* sync with ncclFunc_t in nccl_common.h*/
enum {
    macclOpSignal = -2,
    macclOpCancel = -1,
    macclOpBroadcast = 0,
    macclOpReduce = 1,
    macclOpAllGather = 2,
    macclOpReduceScatter = 3,
    macclOpAllReduce = 4,
    macclOpSendRecv = 5,
    macclOp_Rsvd1 = 6,
    macclOpMemset = 7,
    macclOpMemcpyd2d = 8,
    macclOpCfgSdbLut = 9,
    macclOpRemoteWrite = 10,
    macclOpGPUCtl = 11,
    macclOpGetLut = 12,
    macclOpSetLut = 13,
    macclOpSetLutFile = 14,
    macclOpMemcpy3d = 15,
    macclOpMemcpy = 16,
    macclOpAccessPeer = 17,
    macclOpMemcpyPush = 18,
    macclOpMemcpyPull = 19,
    macclOpCancelCtr,
    macclOpMax
};

// clang-format off
constexpr const char *op_txt[] = {
    "macclOpBroadcast",
    "macclOpReduce",
    "macclOpAllGather",
    "macclOpReduceScatter",
    "macclOpAllReduce",
    "macclOpSendRecv",
    "macclOp_Rsvd1",
    "macclOpMemset",
    "macclOpMemcpyd2d",
    "macclOpCfgSdbLut",
    "macclOpRemoteWrite",
    "macclOpGPUCtl",
    "macclOpGetLut",
    "macclOpSetLut",
    "macclOpSetLutFile",
    "macclOpMemcpy3d",
    "macclOpMemcpy",
    "macclOpAccessPeer",
    "macclOpMemcpyPush",
    "macclOpMemcpyPull",
    "macclOpCancelCtr,",
    "macclOpMax",
};
// clang-format on

#define TASK_BUF_SIZE 32
#define TASK_WORDS 12

enum lut_type_t {
    FLT_LUT,
    SLM_LUT,
    SDB_LUT,
    POST1_LUT,
    POST2_LUT,
    PKG_LUT,
    SDB_LUT_UCAST,
    SDB_LUT_BCAST,
    SW_SLM_LUT,
};

struct buf_t {
    uint64_t buf;
    uint32_t size;
};
static_assert(sizeof(buf_t) <= TASK_BUF_SIZE, "");

struct memset_t {
    uint64_t s;
    uint64_t c;
    uint64_t n;
    uint32_t ev_val;
    uint32_t cachable : 1;
};
static_assert(sizeof(memset_t) <= TASK_BUF_SIZE, "");

struct memcpy_t {
    uint64_t dest;
    uint64_t src;
    uint64_t n;
    uint32_t ev_val;
    uint32_t rmt_dev : 7;
    uint32_t cachable : 1;
    uint32_t rmt_asid : 5;
};
static_assert(sizeof(memcpy_t) <= TASK_BUF_SIZE, "");

struct access_peer_t {
    uint32_t dst;
    uint32_t src;
    uint64_t ret;
    uint32_t ev_val;
};
static_assert(sizeof(access_peer_t) <= TASK_BUF_SIZE, "");

struct memcpy3d_t {
    uint64_t dest;
    uint64_t src;
    uint32_t dsize;
    uint32_t ssize;
    uint32_t ev_val;
    uint32_t cachable : 1;
};
static_assert(sizeof(memcpy3d_t) <= TASK_BUF_SIZE, "");

struct memcpy4_t {
    uint64_t dest;
    uint64_t src;
    uint64_t len;
    uint32_t step;
};
static_assert(sizeof(memcpy4_t) <= TASK_BUF_SIZE, "");

struct cfg_sdb_lut_t {
    uint64_t recv_ptr;
    int lut_addr;
    int slm_mask;
};
static_assert(sizeof(cfg_sdb_lut_t) <= TASK_BUF_SIZE, "");

struct remote_write_t {
    uint64_t dst;
    uint64_t src;
    uint64_t len;
    uint32_t slm_mask : 8;
    uint32_t asid : 5;
    uint32_t die2die : 1;
};
static_assert(sizeof(remote_write_t) <= TASK_BUF_SIZE, "");

struct route_item_t {
    int lut;
    int mask;
};

struct gpu_id_t {
    int gpu_id;
    int gpu_cnt;
    int gpu_type;
    int flag_print;
};

struct counter_t {
    int act;  // bit0 StartCounter, bit1 StopCounter, bit2 ReadCounter
    int id;   // 0 AllCycleCounter, 1 Fetch Miss, 2 DPStall ... 14 AllInst
    uint64_t ptr;
};

// clang-format off
constexpr const char *gpuctl_op_txt[] = {
    "SPU_STOP",
    "FW_VER",
    "GPU_ID",
    "FLAG_PRN",
    "ROUTE",
    "COUNTER",
    "FUNC",
    "LINK_INIT",
    "SLM_INIT",
    "MAX",
};
// clang-format on
struct gpu_ctl_t {
    enum {
        SPU_STOP,
        FW_VER,
        GPU_ID,
        FLAG_PRN,
        ROUTE,
        COUNTER,
        FUNC,
        LINK_INIT,
        SLM_INIT,
        MAX
    };

    int op;
    int fn;
    union {
        uint64_t dst;  // FW_VER
        gpu_id_t gpu_id;
        int flag_print;
        buf_t route;
        counter_t cnt;
        int para[6];
    };
};
static_assert(sizeof(gpu_ctl_t) <= TASK_BUF_SIZE, "");

struct get_lut_t {
    uint64_t dst;
    int type;
    int port;
    int lut;
    int cnt;
};
static_assert(sizeof(get_lut_t) <= TASK_BUF_SIZE, "");

struct set_lut_t {
    int type;
    int port;
    int lut_addr;
    union {
        int free;
        uint64_t recv_ptr;  // for bcast
    };
};
static_assert(sizeof(set_lut_t) <= TASK_BUF_SIZE, "");

struct lut_t {
    int type;
    int port;
    int addr;
    int free;
};

struct cfg_task_t {
    enum {
        EVENT_ORIG_VAL = 0,
        EVENT_WAIT_VAL = 1,
    };
    union {
        uint32_t buf[TASK_BUF_SIZE / sizeof(uint32_t)] = {0};
        memset_t memset_task;
        memcpy_t memcpy_task;
        memcpy3d_t memcpy3d_task;
        memcpy4_t memcpy4_task;
        access_peer_t peer_task;
        cfg_sdb_lut_t sdb_lut;
        remote_write_t rmt_wr;
        get_lut_t get_lut;
        set_lut_t set_lut;
        gpu_ctl_t gpu_ctl;
        buf_t lut_buf;
    };
    uint64_t event = 0;  // the completion flag for the whole kernel
    int32_t op = 0;
    uint32_t valid = 1;

    cfg_task_t(void *event) : event((uint64_t)event) {}
    cfg_task_t(int32_t op) : op(op) {}

    void set_task_memset(void *s, int c, size_t n, uint32_t ev_val, uint32_t cachable) {
        op = macclOpMemset;
        memset_task.s = (uint64_t)s;
        memset_task.c = (uint64_t)c;
        memset_task.n = (uint64_t)n;
        memset_task.ev_val = ev_val;
        memset_task.cachable = cachable;
    }

    void set_task_memcpy(void *dest, const void *src, size_t n, uint32_t ev_val, uint32_t cachable) {
        op = macclOpMemcpyd2d;
        memcpy_task.dest = (uint64_t)dest;
        memcpy_task.src = (uint64_t)src;
        memcpy_task.n = (uint64_t)n;
        memcpy_task.ev_val = ev_val;
        memcpy_task.cachable = cachable;
    }

    void set_task_sdb_lut(int lut_addr, int slm_mask, void *recv_ptr) {
        op = macclOpCfgSdbLut;
        sdb_lut.lut_addr = lut_addr;
        sdb_lut.slm_mask = slm_mask;
        sdb_lut.recv_ptr = (uint64_t)recv_ptr;
    }

    void set_task_remote_write(uint64_t dst, uint64_t src, uint64_t len, uint32_t slm_mask, uint32_t asid) {
        op = macclOpRemoteWrite;
        rmt_wr.dst = dst;
        rmt_wr.src = src;
        rmt_wr.len = len;
        rmt_wr.slm_mask = slm_mask;
        rmt_wr.asid = asid;
    }

    void set_task_get_lut(void *dst, int type, int port, int lut, int cnt) {
        op = macclOpGetLut;
        get_lut.dst = (uint64_t)dst;
        get_lut.type = type;
        get_lut.port = port;
        get_lut.lut = lut;
        get_lut.cnt = cnt;
    }

    void set_task_set_sdb_lut_bcast(int lut_addr, int port, void *recv_ptr) {
        op = macclOpSetLut;
        set_lut.type = SDB_LUT_BCAST;
        set_lut.port = port;
        set_lut.lut_addr = lut_addr;
        set_lut.recv_ptr = (uint64_t)recv_ptr;
    }

    void set_task_set_sdb_lut_ucast(int port, int lut_addr) {
        op = macclOpSetLut;
        set_lut.type = SDB_LUT_UCAST;
        set_lut.port = port;
        set_lut.lut_addr = lut_addr;
    }

    void set_task_set_slm_lut(int port, int lut_addr) {
        op = macclOpSetLut;
        set_lut.type = SLM_LUT;
        set_lut.port = port;
        set_lut.lut_addr = lut_addr;
    }

    void set_task_set_lut_file(void *buf, size_t size) {
        op = macclOpSetLutFile;
        lut_buf.buf = (uint64_t)buf;
        lut_buf.size = size;
    }

    void set_task_spu_stop() {
        op = macclOpGPUCtl;
        gpu_ctl.op = gpu_ctl_t::SPU_STOP;
    }

    void set_task_fw_ver(void *dst) {
        op = macclOpGPUCtl;
        gpu_ctl.op = gpu_ctl_t::FW_VER;
        gpu_ctl.dst = (uint64_t)dst;
    }

    void set_task_gpu_id(int gpu_id, int gpu_cnt, int gpu_type, int flag_print) {
        op = macclOpGPUCtl;
        gpu_ctl.op = gpu_ctl_t::GPU_ID;
        gpu_ctl.gpu_id.gpu_id = gpu_id;
        gpu_ctl.gpu_id.gpu_cnt = gpu_cnt;
        gpu_ctl.gpu_id.gpu_type = gpu_type;
    }

    void set_task_route(void *buf, size_t size) {
        op = macclOpGPUCtl;
        gpu_ctl.op = gpu_ctl_t::ROUTE;
        gpu_ctl.route.buf = (uint64_t)buf;
        gpu_ctl.route.size = size;
    }
};
static_assert(sizeof(cfg_task_t) == 12 * sizeof(uint32_t), "The size of cfg_task_t must be 12 dwords");
