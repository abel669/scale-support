#ifndef MAPS_DRIVER_API_H_
#define MAPS_DRIVER_API_H_

#include "maps_runtime_api.h"

#if __GUNC__
#pragma GCC visibility push(default)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef mapsCtx_t maCtx_t;
typedef mapsDevice_t maDevice_t;
typedef mapsPointer_attribute maPointer_attribute;
typedef mapsModule_t maModule_t;

// maps context flags
typedef enum maCtxFlags {
    MAPS_CTX_SCHED_AUTO =            0x0,
    MAPS_CTX_SCHED_SPIN =            0x1,
    MAPS_CTX_SCHED_YIELD =           0x2,
    MAPS_CTX_SCHED_BLOCKING_SYNC =   0x4,
    MAPS_CTX_MAP_HOST =              0x8,
    MAPS_CTX_LMEM_RESIZE_TO_MAX =    0x10,
    MAPS_CTX_COREDUMP_ENABLE =       0x20,
    MAPS_CTX_USER_COREDUMP_ENABLE =  0x40,
    MAPS_CTX_SYNC_MEMOPS =           0x80,
    MAPS_CTX_FLAGS_MASK =            0xFF
} maCtxFlags;

// Stream wait value conidtions
#define maStreamWaitValueGte 0x0
#define maStreamWaitValueEq 0x1

// Stream write value flags
#define maStreamWriteValueDefault 0x0

typedef enum maFuncCache_t {
    maFuncCachePreferNone,    ///< no preference for shared memory or L1 (default)
    maFuncCachePreferShared,  ///< prefer larger shared memory and smaller L1 cache
    maFuncCachePreferL1,      ///< prefer larger L1 cache and smaller shared memory
    maFuncCachePreferEqual,   ///< prefer equal size L1 cache and shared memory
} maFuncCache_t;
/**
 * @warning On AMD devices and some Nvidia devices, these hints and controls are ignored.
 */
typedef enum maSharedMemConfig {
    maSharedMemBankSizeDefault,  ///< The compiler selects a device-specific value for the banking.
    maSharedMemBankSizeFourByte,  ///< Shared mem is banked at 4-bytes intervals and performs best
                                   ///< when adjacent threads access data 4 bytes apart.
    maSharedMemBankSizeEightByte  ///< Shared mem is banked at 8-byte intervals and performs best
                                   ///< when adjacent threads access data 4 bytes apart.
} maSharedMemConfig;

typedef enum maDevice_attribute {
    MA_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS = 93,
    MA_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES = 98,
    MA_DEVICE_ATTRIBUTE_MULTICAST_SUPPORTED = 132,
    MA_DEVICE_ATTRIBUTE_MAX
} maDevice_attribute;

typedef enum maMemAllocationType {
    maMemAllocationTypeInvalid = 0x0,
    /** This allocation type is 'pinned', i.e. cannot migrate from its current
      * location while the application is actively using it
      */
    maMemAllocationTypePinned  = 0x1,
    maMemAllocationTypeMax     = 0x7FFFFFFF
} maMemAllocationType;

typedef enum maMemAllocationHandleType {
    maMemHandleTypeNone                    = 0x0,  ///< Does not allow any export mechanism
    maMemHandleTypePosixFileDescriptor     = 0x1,  ///< Allows a file descriptor for exporting. Permitted only on POSIX systems
    maMemHandleTypeWin32                   = 0x2,  ///< Allows a Win32 NT handle for exporting. (HANDLE)
    maMemHandleTypeWin32Kmt                = 0x4   ///< Allows a Win32 KMT handle for exporting. (D3DKMT_HANDLE)
} maMemAllocationHandleType;

 typedef enum maMemLocationType {
    maMemLocationTypeInvalid = 0,
    maMemLocationTypeDevice = 1    ///< Device location, thus it's maps device ID
} maMemLocationType;

typedef struct maMemLocation {
    maMemLocationType type;  ///< Specifies the location type, which describes the meaning of id
    int id;                   ///< Identifier for the provided location type @p maMemLocationType
} maMemLocation;

/**
 * Memory allocation properties
 */
typedef struct maMemAllocationProp {
    maMemAllocationType type;                       ///< Memory allocation type
    maMemAllocationHandleType requestedHandleType;  ///< Requested handle type
    maMemLocation location;                         ///< Memory location
    void* win32HandleMetaData;                       ///< Metadata for Win32 handles
    struct {
        unsigned char compressionType;               ///< Compression type
        unsigned char gpuDirectRDMACapable;          ///< RDMA capable
        unsigned short usage;                        ///< Usage
    } allocFlags;
} maMemAllocationProp;

/**
 * Flags for granularity
 */
typedef enum maMemAllocationGranularity_flags {
    maMemAllocationGranularityMinimum     = 0x0,  ///< Minimum granularity
    maMemAllocationGranularityRecommended = 0x1   ///< Recommended granularity for performance
} maMemAllocationGranularity_flags;

/**
 * Specifies the memory protection flags for mapping
 *
 */
typedef enum maMemAccessFlags {
    maMemAccessFlagsProtNone      = 0,  ///< Default, make the address range not accessible
    maMemAccessFlagsProtRead      = 1,  ///< Set the address range read accessible
    maMemAccessFlagsProtReadWrite = 3   ///< Set the address range read-write accessible
} maMemAccessFlags;
/**
 * Memory access descriptor
 */
typedef struct maMemAccessDesc {
    maMemLocation      location; ///< Location on which the accessibility has to change
    maMemAccessFlags   flags;    ///< Accessibility flags to set
} maMemAccessDesc;

typedef uint64_t maMemGenericAllocationHandle_t ;
mapsError_t maDeviceGet(maDevice_t* device, int deviceId);
mapsError_t maCtxGetDevice(maDevice_t* device);
mapsError_t maCtxGetFlags(maCtxFlags* flags);
mapsError_t maCtxSetFlags(maCtxFlags flags);
mapsError_t maCtxPushCurrent(maCtx_t ctx);
mapsError_t maCtxPopCurrent(maCtx_t* ctx);
mapsError_t maCtxGetApiVersion(maCtx_t ctx, int* apiVersion);
mapsError_t maCtxGetCacheConfig(maFuncCache_t* cacheConfig);
mapsError_t maCtxSetCacheConfig(maFuncCache_t cacheConfig);
mapsError_t maCtxSetSharedMemConfig(maSharedMemConfig config);
mapsError_t maCtxGetSharedMemConfig(maSharedMemConfig* pConfig);
mapsError_t maCtxEnablePeerAccess(maCtx_t peerCtx, unsigned int flags);
mapsError_t maCtxDisablePeerAccess(maCtx_t peerCtx);


mapsError_t maDevicePrimaryCtxRetain(maCtx_t* ctx, maDevice_t device);
mapsError_t maDevicePrimaryCtxRelease(maDevice_t device);
mapsError_t maPointerSetAttribute(const void* value, maPointer_attribute attribute, void* ptr);
mapsError_t maModuleGetGlobal(void* dptr, size_t* bytes, maModule_t mod, const char* name);
#define maModuleGetGlobal_v2 maModuleGetGlobal;
mapsError_t maDeviceGetAttribute(int *pi, maDevice_attribute attrib, int dev);

mapsError_t maStreamWriteValue32(mapsStream_t stream, void* ptr, uint32_t value, unsigned int flags);
mapsError_t maStreamWaitValue32(mapsStream_t stream, void* ptr, uint32_t value, unsigned int flags);
mapsError_t maMemGetAllocationGranularity(size_t* granularity, const maMemAllocationProp* prop, maMemAllocationGranularity_flags option);
mapsError_t maMemAddressReserve(void** ptr, size_t size, size_t alignment, void* addr, unsigned long long flags);
mapsError_t maMemAddressFree(void* ptr, size_t size);
mapsError_t maMemCreate(maMemGenericAllocationHandle_t* handle, size_t size, const maMemAllocationProp* prop, unsigned long long flags);
mapsError_t maMemRelease(maMemGenericAllocationHandle_t handle);
mapsError_t maMemMap(void* ptr, size_t size, size_t offset, maMemGenericAllocationHandle_t handle, unsigned long long flags);
mapsError_t maMemUnmap(void* ptr, size_t size);
mapsError_t maMemSetAccess(void* ptr, size_t size, const maMemAccessDesc* desc, size_t count);

#ifdef __cplusplus
}
#endif

#if __GUNC__
#pragma GCC visibility pop
#endif

#endif // MAPS_DRIVER_API_H_