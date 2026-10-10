#ifndef MAPS_RUNTIME_API_H_
#define MAPS_RUNTIME_API_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 

#ifdef __cplusplus
  #define __dparm(x) \
          = x
#else
  #define __dparm(x)
#endif

#if defined(__CUDA__) || defined(__SCALE__)
    #define __device__ __attribute__((device))
    #define __shared__ __attribute__((shared))
    #define __host__ __attribute__((host))
#else
    #define __device__
    #define __host__
    #define __shared__
#endif // __CUDA__ || __SCALE__
#define __device_builtin__

#ifndef __dim3
#define __dim3
typedef struct __device_builtin__ uint3 {
    unsigned int x, y, z;
} uint3;
typedef struct __device_builtin__ dim3 {
    unsigned int x, y, z;
#if defined(__cplusplus)
    __host__ __device__ constexpr dim3(unsigned int x = 1, unsigned int y = 1, unsigned int z = 1) : x(x), y(y), z(z) {}
    __host__ __device__ constexpr dim3(uint3 input) : x(input.x), y(input.y), z(input.z) {}
#endif // __cplusplus
} dim3;
#endif // __dim3

/* Flags that can be used with mapsHostRegister */
#define hipHostRegisterDefault      0x00
#define hipHostRegisterPortable     0x01
#define hipHostRegisterMapped       0x02
#define hipHostRegisterIoMemory     0x04
#define hipHostRegisterReadOnly     0x08

#define MAPS_SYMBOL(X) ((const void*) &(X))

/**
 * Flags that can be used with mapsHostAlloc/mapsHostMalloc/mapsMemHostAlloc.
 */
#define mapsHostAllocDefault        0x00
#define mapsHostAllocPortable       0x01
#define mapsHostAllocMapped         0x02
#define mapsHostAllocWriteCombined  0x04

/**
 * Flags that can be used with mapsMallocManaged/mapsMemAllocManaged
 * 
 */
#define mapsMemAttachGlobal  0x01   /**< Memory can be accessed by any stream on any device */
#define mapsMemAttachHost    0x02   /**< Memory cannot be accessed by any stream on any device */

/**
 * Flags that can be used with mapsStreamCreateWithFlags.
 */
//Flags that can be used with mapsStreamCreateWithFlags.
/** Default stream creation flags. These are used with mapsStreamCreate().*/
#define mapsStreamDefault  0x00

/** Stream does not implicitly synchronize with null stream.*/
#define mapsStreamNonBlocking 0x01

//Flags that can be used with mapsEventCreateWithFlags.
/** Default flags.*/
#define mapsEventDefault 0x0

/** Waiting will yield CPU. Power-friendly and usage-friendly but may increase latency.*/
#define mapsEventBlockingSync 0x1

/** Disable event's capability to record timing information. May improve performance.*/
#define mapsEventDisableTiming  0x2

/** Event can support IPC. mapsEventDisableTiming also must be set.*/
#define mapsEventInterprocess 0x4

/** timestamp only.*/
#define mapsEventTimestampOnly 0x08000000

// Stream per thread
/** Implicit stream per application thread.*/
#define mapsStreamPerThread ((mapsStream_t)2)

#define mapsStreamLegacy ((mapsStream_t)1)

// Indicates that the external memory object is a dedicated resource
#define mapsExternalMemoryDedicated 0x1
/**
 * MAPS Memory Advise values
 *
 * @note This memory advise enumeration is used on Linux, not Windows.
 */
typedef enum mapsMemoryAdvise {
    mapsMemAdviseSetReadMostly = 1,          ///< Data will mostly be read and only occassionally
                                            ///< be written to
    mapsMemAdviseUnsetReadMostly = 2,        ///< Undo the effect of mapsMemAdviseSetReadMostly
    mapsMemAdviseSetPreferredLocation = 3,   ///< Set the preferred location for the data as
                                            ///< the specified device
    mapsMemAdviseUnsetPreferredLocation = 4, ///< Clear the preferred location for the data
    mapsMemAdviseSetAccessedBy = 5,          ///< Data will be accessed by the specified device
                                            ///< so prevent page faults as much as possible
    mapsMemAdviseUnsetAccessedBy = 6,        ///< Let MAPS to decide on the page faulting policy
                                            ///< for the specified device
    mapsMemAdviseSetCoarseGrain = 100,       ///< The default memory model is fine-grain. That allows
                                            ///< coherent operations between host and device, while
                                            ///< executing kernels. The coarse-grain can be used
                                            ///< for data that only needs to be coherent at dispatch
                                            ///< boundaries for better performance
    mapsMemAdviseUnsetCoarseGrain = 101      ///< Restores cache coherency policy back to fine-grain
} mapsMemoryAdvise;
/**
 * MAPS Coherency Mode
 */
typedef enum mapsMemRangeCoherencyMode {
    mapsMemRangeCoherencyModeFineGrain = 0,      ///< Updates to memory with this attribute can be
                                                ///< done coherently from all devices
    mapsMemRangeCoherencyModeCoarseGrain = 1,    ///< Writes to memory with this attribute can be
                                                ///< performed by a single device at a time
    mapsMemRangeCoherencyModeIndeterminate = 2   ///< Memory region queried contains subregions with
                                                ///< both mapsMemRangeCoherencyModeFineGrain and
                                                ///< mapsMemRangeCoherencyModeCoarseGrain attributes
} mapsMemRangeCoherencyMode;
/**
 * MAPS range attributes
 */
typedef enum mapsMemRangeAttribute {
    mapsMemRangeAttributeReadMostly = 1,         ///< Whether the range will mostly be read and
                                                ///< only occassionally be written to
    mapsMemRangeAttributePreferredLocation = 2,  ///< The preferred location of the range
    mapsMemRangeAttributeAccessedBy = 3,         ///< Memory range has mapsMemAdviseSetAccessedBy
                                                ///< set for the specified device
    mapsMemRangeAttributeLastPrefetchLocation = 4,///< The last location to where the range was
                                                ///< prefetched
    mapsMemRangeAttributeCoherencyMode = 100,    ///< Returns coherency mode
                                                ///< @ref mapsMemRangeCoherencyMode for the range
} mapsMemRangeAttribute;

/**
 * MAPS memory pool attributes
 */
typedef enum mapsMemPoolAttr
{
    /**
     * (value type = int)
     * Allow @p mapsMemAllocAsync to use memory asynchronously freed
     * in another streams as long as a stream ordering dependency
     * of the allocating stream on the free action exists.
     * maps events and null stream interactions can create the required
     * stream ordered dependencies. (default enabled)
     */
    mapsMemPoolReuseFollowEventDependencies   = 0x1,
    /**
     * (value type = int)
     * Allow reuse of already completed frees when there is no dependency
     * between the free and allocation. (default enabled)
     */
    mapsMemPoolReuseAllowOpportunistic        = 0x2,
    /**
     * (value type = int)
     * Allow @p mapsMemAllocAsync to insert new stream dependencies
     * in order to establish the stream ordering required to reuse
     * a piece of memory released by cuFreeAsync (default enabled).
     */
    mapsMemPoolReuseAllowInternalDependencies = 0x3,
    /**
     * (value type = uint64_t)
     * Amount of reserved memory in bytes to hold onto before trying
     * to release memory back to the OS. When more than the release
     * threshold bytes of memory are held by the memory pool, the
     * allocator will try to release memory back to the OS on the
     * next call to stream, event or context synchronize. (default 0)
     */
    mapsMemPoolAttrReleaseThreshold           = 0x4,
    /**
     * (value type = uint64_t)
     * Amount of backing memory currently allocated for the mempool.
     */
    mapsMemPoolAttrReservedMemCurrent         = 0x5,
    /**
     * (value type = uint64_t)
     * High watermark of backing memory allocated for the mempool since the
     * last time it was reset. High watermark can only be reset to zero.
     */
    mapsMemPoolAttrReservedMemHigh            = 0x6,
    /**
     * (value type = uint64_t)
     * Amount of memory from the pool that is currently in use by the application.
     */
    mapsMemPoolAttrUsedMemCurrent             = 0x7,
    /**
     * (value type = uint64_t)
     * High watermark of the amount of memory from the pool that was in use by the application since
     * the last time it was reset. High watermark can only be reset to zero.
     */
    mapsMemPoolAttrUsedMemHigh                = 0x8
} mapsMemPoolAttr;
/**
 * Specifies the type of location
 */
 typedef enum mapsMemLocationType {
    mapsMemLocationTypeInvalid = 0,
    mapsMemLocationTypeDevice = 1    ///< Device location, thus it's MAPS device ID
} mapsMemLocationType;
/**
 * Specifies a memory location.
 *
 * To specify a gpu, set type = @p mapsMemLocationTypeDevice and set id = the gpu's device ID
 */
typedef struct mapsMemLocation {
    mapsMemLocationType type;  ///< Specifies the location type, which describes the meaning of id
    int id;                   ///< Identifier for the provided location type @p mapsMemLocationType
} mapsMemLocation;
/**
 * Specifies the memory protection flags for mapping
 *
 */
typedef enum mapsMemAccessFlags {
    mapsMemAccessFlagsProtNone      = 0,  ///< Default, make the address range not accessible
    mapsMemAccessFlagsProtRead      = 1,  ///< Set the address range read accessible
    mapsMemAccessFlagsProtReadWrite = 3   ///< Set the address range read-write accessible
} mapsMemAccessFlags;
/**
 * Memory access descriptor
 */
typedef struct mapsMemAccessDesc {
    mapsMemLocation      location; ///< Location on which the accessibility has to change
    mapsMemAccessFlags   flags;    ///< Accessibility flags to set
} mapsMemAccessDesc;
/**
 * Defines the allocation types
 */
typedef enum mapsMemAllocationType {
    mapsMemAllocationTypeInvalid = 0x0,
    /** This allocation type is 'pinned', i.e. cannot migrate from its current
      * location while the application is actively using it
      */
    mapsMemAllocationTypePinned  = 0x1,
    mapsMemAllocationTypeMax     = 0x7FFFFFFF
} mapsMemAllocationType;
/**
 * Flags for specifying handle types for memory pool allocations
 *
 */
typedef enum mapsMemAllocationHandleType {
    mapsMemHandleTypeNone                    = 0x0,  ///< Does not allow any export mechanism
    mapsMemHandleTypePosixFileDescriptor     = 0x1,  ///< Allows a file descriptor for exporting. Permitted only on POSIX systems
    mapsMemHandleTypeWin32                   = 0x2,  ///< Allows a Win32 NT handle for exporting. (HANDLE)
    mapsMemHandleTypeWin32Kmt                = 0x4   ///< Allows a Win32 KMT handle for exporting. (D3DKMT_HANDLE)
} mapsMemAllocationHandleType;
/**
 * Specifies the properties of allocations made from the pool.
 */
typedef struct mapsMemPoolProps {
    mapsMemAllocationType       allocType;   ///< Allocation type. Currently must be specified as @p mapsMemAllocationTypePinned
    mapsMemAllocationHandleType handleTypes; ///< Handle types that will be supported by allocations from the pool
    mapsMemLocation             location;    ///< Location where allocations should reside
    /**
     * Windows-specific LPSECURITYATTRIBUTES required when @p mapsMemHandleTypeWin32 is specified
     */
    void*                       win32SecurityAttributes;
    size_t                      maxSize;  ///< Maximum pool size. When set to 0, defaults to a system dependent value
    unsigned char               reserved[56];  ///< Reserved for future use, must be 0
} mapsMemPoolProps;
/**
 * Opaque data structure for exporting a pool allocation
 */
typedef struct mapsMemPoolPtrExportData {
    unsigned char reserved[64];
} mapsMemPoolPtrExportData;


/* clang-format off */
typedef enum  mapsError_t {
    mapsSuccess = 0,  ///< Successful completion.
    mapsErrorInvalidValue = 1,  ///< One or more of the parameters passed to the API call is NULL
                               ///< or not in an acceptable range.
    mapsErrorOutOfMemory = 2,   ///< out of memory range.
    mapsErrorMemoryAllocation = 2,
    mapsErrorNotInitialized = 3,    ///< Invalid not initialized
    mapsErrorDeinitialized = 4,      ///< Deinitialized
    mapsErrorProfilerDisabled = 5,
    mapsErrorProfilerNotInitialized = 6,
    mapsErrorProfilerAlreadyStarted = 7,
    mapsErrorProfilerAlreadyStopped = 8,
    mapsErrorInvalidConfiguration = 9,  ///< Invalide configuration
    mapsErrorInvalidPitchValue = 12,   ///< Invalid pitch value
    mapsErrorInvalidSymbol = 13,   ///< Invalid symbol
    mapsErrorInvalidDevicePointer = 17,  ///< Invalid Device Pointer
    mapsErrorInvalidMemcpyDirection = 21,  ///< Invalid memory copy direction
    mapsErrorInsufficientDriver = 35,
    mapsErrorMissingConfiguration = 52,
    mapsErrorPriorLaunchFailure = 53,
    mapsErrorInvalidDeviceFunction = 98,  ///< Invalid device function
    mapsErrorInvalidHostFunction = 99, 
    mapsErrorNoDevice = 100,  ///< Call to mapsGetDeviceCount returned 0 devices
    mapsErrorInvalidDevice = 101,  ///< DeviceID must be in range from 0 to compute-devices.
    mapsErrorInvalidImage = 200,   ///< Invalid image
    mapsErrorInvalidContext = 201,  ///< Produced when input context is invalid.
    mapsErrorContextAlreadyCurrent = 202,
    mapsErrorMapFailed = 205,
    mapsErrorUnmapFailed = 206,
    mapsErrorArrayIsMapped = 207,
    mapsErrorAlreadyMapped = 208,
    mapsErrorNoBinaryForGpu = 209,
    mapsErrorAlreadyAcquired = 210,
    mapsErrorNotMapped = 211,
    mapsErrorNotMappedAsArray = 212,
    mapsErrorNotMappedAsPointer = 213,
    mapsErrorECCNotCorrectable = 214,
    mapsErrorUnsupportedLimit = 215,   ///< Unsupported limit
    mapsErrorContextAlreadyInUse = 216,   ///< The context is already in use
    mapsErrorPeerAccessUnsupported = 217,
    mapsErrorInvalidKernelFile = 218,  ///< In CUDA DRV, it is CUDA_ERROR_INVALID_PTX
    mapsErrorInvalidGraphicsContext = 219,
    mapsErrorInvalidSource = 300,   ///< Invalid source.
    mapsErrorFileNotFound = 301,   ///< the file is not found.
    mapsErrorSharedObjectSymbolNotFound = 302,
    mapsErrorSharedObjectInitFailed = 303,   ///< Failed to initialize shared object.
    mapsErrorOperatingSystem = 304,   ///< Not the correct operating system
    mapsErrorInvalidHandle = 400,  ///< Invalide handle
    mapsErrorIllegalState = 401, ///< Resource required is not in a valid state to perform operation.
    mapsErrorNotFound = 500,   ///< Not found
    mapsErrorNotReady = 600,  ///< Indicates that asynchronous operations enqueued earlier are not
                             ///< ready.  This is not actually an error, but is used to distinguish
                             ///< from mapsSuccess (which indicates completion).  APIs that return
                             ///< this error include mapsEventQuery and mapsStreamQuery.
    mapsErrorIllegalAddress = 700,
    mapsErrorLaunchOutOfResources = 701,  ///< Out of resources error.
    mapsErrorLaunchTimeOut = 702,   ///< Timeout for the launch.
    mapsErrorPeerAccessAlreadyEnabled = 704,  ///< Peer access was already enabled from the current
                                             ///< device.
    mapsErrorPeerAccessNotEnabled = 705,  ///< Peer access was never enabled from the current device.
    mapsErrorSetOnActiveProcess = 708,   ///< The process is active.
    mapsErrorContextIsDestroyed = 709,   ///< The context is already destroyed
    mapsErrorAssert = 710,  ///< Produced when the kernel calls assert.
    mapsErrorHostMemoryAlreadyRegistered = 712,  ///< Produced when trying to lock a page-locked
                                                ///< memory.
    mapsErrorHostMemoryNotRegistered = 713,  ///< Produced when trying to unlock a non-page-locked
                                            ///< memory.
    mapsErrorLaunchFailure = 719,  ///< An exception occurred on the device while executing a kernel.
    mapsErrorCooperativeLaunchTooLarge = 720,  ///< This error indicates that the number of blocks
                                              ///< launched per grid for a kernel that was launched
                                              ///< via cooperative launch APIs exceeds the maximum
                                              ///< number of allowed blocks for the current device.
    mapsErrorNotSupported = 801,  ///< Produced when the maps API is not supported/implemented
    mapsErrorStreamCaptureUnsupported = 900,  ///< The operation is not permitted when the stream
                                             ///< is capturing.
    mapsErrorStreamCaptureInvalidated = 901,  ///< The current capture sequence on the stream
                                             ///< has been invalidated due to a previous error.
    mapsErrorStreamCaptureMerge = 902,  ///< The operation would have resulted in a merge of
                                       ///< two independent capture sequences.
    mapsErrorStreamCaptureUnmatched = 903,  ///< The capture was not initiated in this stream.
    mapsErrorStreamCaptureUnjoined = 904,  ///< The capture sequence contains a fork that was not
                                          ///< joined to the primary stream.
    mapsErrorStreamCaptureIsolation = 905,  ///< A dependency would have been created which crosses
                                           ///< the capture sequence boundary. Only implicit
                                           ///< in-stream ordering dependencies  are allowed
                                           ///< to cross the boundary
    mapsErrorStreamCaptureImplicit = 906,  ///< The operation would have resulted in a disallowed
                                          ///< implicit dependency on a current capture sequence
                                          ///< from mapsStreamLegacy.
    mapsErrorCapturedEvent = 907,  ///< The operation is not permitted on an event which was last
                                  ///< recorded in a capturing stream.
    mapsErrorStreamCaptureWrongThread = 908,  ///< A stream capture sequence not initiated with
                                             ///< the mapsStreamCaptureModeRelaxed argument to
                                             ///< mapsStreamBeginCapture was passed to
                                             ///< mapsStreamEndCapture in a different thread.
    mapsErrorGraphExecUpdateFailure = 910,  ///< This error indicates that the graph update
                                           ///< not performed because it included changes which
                                           ///< violated constraintsspecific to instantiated graph
                                           ///< update.
    mapsErrorUnknown = 999,  ///< Unknown error.
    // MAPS Runtime Error Codes start here.
    mapsErrorRuntimeMemory = 1052,  ///< MAPS runtime memory call returned error.  Typically not seen
                                   ///< in production systems.
    mapsErrorRuntimeOther = 1053,  ///< MAPS runtime call other than memory returned error.  Typically
                                  ///< not seen in production systems.
    mapsErrorTbd  ///< Marker that more error codes are needed.
} mapsError_t;

typedef struct mapsUUID_t {
    char bytes[16];
} mapsUUID;
/**
 * mapsDeviceAttribute_t
 * mapsDeviceAttributeUnused number: 5
 */
typedef enum mapsDeviceAttribute_t {
    mapsDeviceAttributeCudaCompatibleBegin = 0,

    mapsDeviceAttributeEccEnabled = mapsDeviceAttributeCudaCompatibleBegin, ///< Whether ECC support is enabled.
    mapsDeviceAttributeAccessPolicyMaxWindowSize,        ///< Cuda only. The maximum size of the window policy in bytes.
    mapsDeviceAttributeAsyncEngineCount,                 ///< Asynchronous engines number.
    mapsDeviceAttributeCanMapHostMemory,                 ///< Whether host memory can be mapped into device address space
    mapsDeviceAttributeCanUseHostPointerForRegisteredMem,///< Device can access host registered memory
                                                        ///< at the same virtual address as the CPU
    mapsDeviceAttributeClockRate,                        ///< Peak clock frequency in kilohertz.
    mapsDeviceAttributeComputeMode,                      ///< Compute mode that device is currently in.
    mapsDeviceAttributeComputePreemptionSupported,       ///< Device supports Compute Preemption.
    mapsDeviceAttributeConcurrentKernels,                ///< Device can possibly execute multiple kernels concurrently.
    mapsDeviceAttributeConcurrentManagedAccess,          ///< Device can coherently access managed memory concurrently with the CPU
    mapsDeviceAttributeCooperativeLaunch,                ///< Support cooperative launch
    mapsDeviceAttributeCooperativeMultiDeviceLaunch,     ///< Support cooperative launch on multiple devices
    mapsDeviceAttributeDeviceOverlap,                    ///< Device can concurrently copy memory and execute a kernel.
                                                        ///< Deprecated. Use instead asyncEngineCount.
    mapsDeviceAttributeDirectManagedMemAccessFromHost,   ///< Host can directly access managed memory on
                                                        ///< the device without migration
    mapsDeviceAttributeGlobalL1CacheSupported,           ///< Device supports caching globals in L1
    mapsDeviceAttributeHostNativeAtomicSupported,        ///< Link between the device and the host supports native atomic operations
    mapsDeviceAttributeIntegrated,                       ///< Device is integrated GPU
    mapsDeviceAttributeIsMultiGpuBoard,                  ///< Multiple GPU devices.
    mapsDeviceAttributeKernelExecTimeout,                ///< Run time limit for kernels executed on the device
    mapsDeviceAttributeL2CacheSize,                      ///< Size of L2 cache in bytes. 0 if the device doesn't have L2 cache.
    mapsDeviceAttributeLocalL1CacheSupported,            ///< caching locals in L1 is supported
    mapsDeviceAttributeLuid,                             ///< 8-byte locally unique identifier in 8 bytes. Undefined on TCC and non-Windows platforms
    mapsDeviceAttributeLuidDeviceNodeMask,               ///< Luid device node mask. Undefined on TCC and non-Windows platforms
    mapsDeviceAttributeComputeCapabilityMajor,           ///< Major compute capability version number.
    mapsDeviceAttributeManagedMemory,                    ///< Device supports allocating managed memory on this system
    mapsDeviceAttributeMaxBlocksPerMultiProcessor,       ///< Max block size per multiprocessor
    mapsDeviceAttributeMaxBlockDimX,                     ///< Max block size in width.
    mapsDeviceAttributeMaxBlockDimY,                     ///< Max block size in height.
    mapsDeviceAttributeMaxBlockDimZ,                     ///< Max block size in depth.
    mapsDeviceAttributeMaxGridDimX,                      ///< Max grid size  in width.
    mapsDeviceAttributeMaxGridDimY,                      ///< Max grid size  in height.
    mapsDeviceAttributeMaxGridDimZ,                      ///< Max grid size  in depth.
    mapsDeviceAttributeMaxSurface1D,                     ///< Maximum size of 1D surface.
    mapsDeviceAttributeMaxSurface1DLayered,              ///< Cuda only. Maximum dimensions of 1D layered surface.
    mapsDeviceAttributeMaxSurface2D,                     ///< Maximum dimension (width, height) of 2D surface.
    mapsDeviceAttributeMaxSurface2DLayered,              ///< Cuda only. Maximum dimensions of 2D layered surface.
    mapsDeviceAttributeMaxSurface3D,                     ///< Maximum dimension (width, height, depth) of 3D surface.
    mapsDeviceAttributeMaxSurfaceCubemap,                ///< Cuda only. Maximum dimensions of Cubemap surface.
    mapsDeviceAttributeMaxSurfaceCubemapLayered,         ///< Cuda only. Maximum dimension of Cubemap layered surface.
    mapsDeviceAttributeMaxTexture1DWidth,                ///< Maximum size of 1D texture.
    mapsDeviceAttributeMaxTexture1DLayered,              ///< Maximum dimensions of 1D layered texture.
    mapsDeviceAttributeMaxTexture1DLinear,               ///< Maximum number of elements allocatable in a 1D linear texture.
                                                        ///< Use cudaDeviceGetTexture1DLinearMaxWidth() instead on Cuda.
    mapsDeviceAttributeMaxTexture1DMipmap,               ///< Maximum size of 1D mipmapped texture.
    mapsDeviceAttributeMaxTexture2DWidth,                ///< Maximum dimension width of 2D texture.
    mapsDeviceAttributeMaxTexture2DHeight,               ///< Maximum dimension hight of 2D texture.
    mapsDeviceAttributeMaxTexture2DGather,               ///< Maximum dimensions of 2D texture if gather operations  performed.
    mapsDeviceAttributeMaxTexture2DLayered,              ///< Maximum dimensions of 2D layered texture.
    mapsDeviceAttributeMaxTexture2DLinear,               ///< Maximum dimensions (width, height, pitch) of 2D textures bound to pitched memory.
    mapsDeviceAttributeMaxTexture2DMipmap,               ///< Maximum dimensions of 2D mipmapped texture.
    mapsDeviceAttributeMaxTexture3DWidth,                ///< Maximum dimension width of 3D texture.
    mapsDeviceAttributeMaxTexture3DHeight,               ///< Maximum dimension height of 3D texture.
    mapsDeviceAttributeMaxTexture3DDepth,                ///< Maximum dimension depth of 3D texture.
    mapsDeviceAttributeMaxTexture3DAlt,                  ///< Maximum dimensions of alternate 3D texture.
    mapsDeviceAttributeMaxTextureCubemap,                ///< Maximum dimensions of Cubemap texture
    mapsDeviceAttributeMaxTextureCubemapLayered,         ///< Maximum dimensions of Cubemap layered texture.
    mapsDeviceAttributeMaxThreadsDim,                    ///< Maximum dimension of a block
    mapsDeviceAttributeMaxThreadsPerBlock,               ///< Maximum number of threads per block.
    mapsDeviceAttributeMaxThreadsPerMultiProcessor,      ///< Maximum resident threads per multiprocessor.
    mapsDeviceAttributeMaxPitch,                         ///< Maximum pitch in bytes allowed by memory copies
    mapsDeviceAttributeMemoryBusWidth,                   ///< Global memory bus width in bits.
    mapsDeviceAttributeMemoryClockRate,                  ///< Peak memory clock frequency in kilohertz.
    mapsDeviceAttributeComputeCapabilityMinor,           ///< Minor compute capability version number.
    mapsDeviceAttributeMultiGpuBoardGroupID,             ///< Unique ID of device group on the same multi-GPU board
    mapsDeviceAttributeMultiprocessorCount,              ///< Number of multiprocessors on the device.
    mapsDeviceAttributeUnused1,                          ///< Previously mapsDeviceAttributeName
    mapsDeviceAttributePageableMemoryAccess,             ///< Device supports coherently accessing pageable memory
                                                        ///< without calling mapsHostRegister on it
    mapsDeviceAttributePageableMemoryAccessUsesHostPageTables, ///< Device accesses pageable memory via the host's page tables
    mapsDeviceAttributePciBusId,                         ///< PCI Bus ID.
    mapsDeviceAttributePciDeviceId,                      ///< PCI Device ID.
    mapsDeviceAttributePciDomainID,                      ///< PCI Domain ID.
    mapsDeviceAttributePersistingL2CacheMaxSize,         ///< Maximum l2 persisting lines capacity in bytes
    mapsDeviceAttributeMaxRegistersPerBlock,             ///< 32-bit registers available to a thread block. This number is shared
                                                        ///< by all thread blocks simultaneously resident on a multiprocessor.
    mapsDeviceAttributeMaxRegistersPerMultiprocessor,    ///< 32-bit registers available per block.
    mapsDeviceAttributeReservedSharedMemPerBlock,        ///< Shared memory reserved by CUDA driver per block.
    mapsDeviceAttributeMaxSharedMemoryPerBlock,          ///< Maximum shared memory available per block in bytes.
    mapsDeviceAttributeSharedMemPerBlockOptin,           ///< Maximum shared memory per block usable by special opt in.
    mapsDeviceAttributeSharedMemPerMultiprocessor,       ///< Shared memory available per multiprocessor.
    mapsDeviceAttributeSingleToDoublePrecisionPerfRatio, ///< Cuda only. Performance ratio of single precision to double precision.
    mapsDeviceAttributeStreamPrioritiesSupported,        ///< Whether to support stream priorities.
    mapsDeviceAttributeSurfaceAlignment,                 ///< Alignment requirement for surfaces
    mapsDeviceAttributeTccDriver,                        ///< Cuda only. Whether device is a Tesla device using TCC driver
    mapsDeviceAttributeTextureAlignment,                 ///< Alignment requirement for textures
    mapsDeviceAttributeTexturePitchAlignment,            ///< Pitch alignment requirement for 2D texture references bound to pitched memory;
    mapsDeviceAttributeTotalConstantMemory,              ///< Constant memory size in bytes.
    mapsDeviceAttributeTotalGlobalMem,                   ///< Global memory available on devicice.
    mapsDeviceAttributeUnifiedAddressing,                ///< Cuda only. An unified address space shared with the host.
    mapsDeviceAttributeUnused2,                          ///< Previously mapsDeviceAttributeUuid
    mapsDeviceAttributeWarpSize,                         ///< Warp size in threads.
    mapsDeviceAttributeMemoryPoolsSupported,             ///< Device supports HIP Stream Ordered Memory Allocator
    mapsDeviceAttributeVirtualMemoryManagementSupported, ///< Device supports HIP virtual memory management
    mapsDeviceAttributeHostRegisterSupported,            ///< Can device support host memory registration via mapsHostRegister
    mapsDeviceAttributeMemoryPoolSupportedHandleTypes,   ///< Supported handle mask for HIP Stream Ordered Memory Allocator

    mapsDeviceAttributeCudaCompatibleEnd = 9999,
    mapsDeviceAttributeAmdSpecificBegin = 10000,

    mapsDeviceAttributeClockInstructionRate = mapsDeviceAttributeAmdSpecificBegin,  ///< Frequency in khz of the timer used by the device-side "clock*"
    mapsDeviceAttributeUnused3,                                  ///< Previously mapsDeviceAttributeArch
    mapsDeviceAttributeMaxSharedMemoryPerMultiprocessor,         ///< Maximum Shared Memory PerMultiprocessor.
    mapsDeviceAttributeUnused4,                                  ///< Previously mapsDeviceAttributeGcnArch
    mapsDeviceAttributeUnused5,                                  ///< Previously mapsDeviceAttributeGcnArchName
    mapsDeviceAttributeHdpMemFlushCntl,                          ///< Address of the HDP_MEM_COHERENCY_FLUSH_CNTL register
    mapsDeviceAttributeHdpRegFlushCntl,                          ///< Address of the HDP_REG_COHERENCY_FLUSH_CNTL register
    mapsDeviceAttributeCooperativeMultiDeviceUnmatchedFunc,      ///< Supports cooperative launch on multiple
                                                                ///< devices with unmatched functions
    mapsDeviceAttributeCooperativeMultiDeviceUnmatchedGridDim,   ///< Supports cooperative launch on multiple
                                                                ///< devices with unmatched grid dimensions
    mapsDeviceAttributeCooperativeMultiDeviceUnmatchedBlockDim,  ///< Supports cooperative launch on multiple
                                                                ///< devices with unmatched block dimensions
    mapsDeviceAttributeCooperativeMultiDeviceUnmatchedSharedMem, ///< Supports cooperative launch on multiple
                                                                ///< devices with unmatched shared memories
    mapsDeviceAttributeIsLargeBar,                               ///< Whether it is LargeBar
    mapsDeviceAttributeAsicRevision,                             ///< Revision of the GPU in this device
    mapsDeviceAttributeCanUseStreamWaitValue,                    ///< '1' if Device supports mapsStreamWaitValue32() and
                                                                ///< mapsStreamWaitValue64(), '0' otherwise.
    mapsDeviceAttributeImageSupport,                             ///< '1' if Device supports image, '0' otherwise.
    mapsDeviceAttributePhysicalMultiProcessorCount,              ///< All available physical compute
                                                                ///< units for the device
    mapsDeviceAttributeFineGrainSupport,                         ///< '1' if Device supports fine grain, '0' otherwise
    mapsDeviceAttributeWallClockRate,                            ///< Constant frequency of wall clock in kilohertz.
    mapsDeviceAttributeGPUDirectRDMASupported,                   ///< Indicates device support of RDMA APIs

    mapsDeviceAttributeAmdSpecificEnd = 19999,
    mapsDeviceAttributeVendorSpecificBegin = 20000,
    // Extended attributes for vendors
} mapsDeviceAttribute_t;

// cuda compatible
const enum mapsDeviceAttribute_t mapsDevAttrMultiProcessorCount = mapsDeviceAttributeMultiprocessorCount;
const enum mapsDeviceAttribute_t mapsDevAttrCanUseHostPointerForRegisteredMem = mapsDeviceAttributeCanUseHostPointerForRegisteredMem;
const enum mapsDeviceAttribute_t mapsDevAttrCooperativeLaunch = mapsDeviceAttributeCooperativeLaunch;
/* clang-format on */

typedef struct mapsDeviceProp_t {
    char name[256];                   ///< Device name.
    mapsUUID uuid;                     ///< UUID of a device
    size_t totalGlobalMem;            ///< Size of global memory region (in bytes).
    size_t sharedMemPerBlock;         ///< Size of shared memory per block (in bytes).
    int warpSize;                     ///< Warp size.
    size_t memPitch;                  ///< Maximum pitch in bytes allowed by memory copies
                                      ///< pitched memory
    int maxThreadsPerBlock;           ///< Max work items per work group or workgroup max size.
    int maxThreadsDim[3];             ///< Max number of threads in each dimension (XYZ) of a block.
    int maxGridSize[3];               ///< Max grid dimensions (XYZ).
    int clockRate;                    ///< Max clock frequency of the multiProcessors in khz.
    int major;  ///< Major compute capability.  On HCC, this is an approximation and features may
                ///< differ from CUDA CC.  See the arch feature flags for portable ways to query
                ///< feature caps.
    int minor;  ///< Minor compute capability.  On HCC, this is an approximation and features may
                ///< differ from CUDA CC.  See the arch feature flags for portable ways to query
                ///< feature caps.
    int pciBusID;                  ///< PCI Bus ID.
    int pciDeviceID;               ///< PCI Device ID.
    int pciDomainID;               ///< PCI Domain ID
    int pciFunctionID;             ///< PCI Function ID
} mapsDeviceProp_t;

typedef struct imapsCtx_t* mapsCtx_t;
typedef struct imapsModule_t* mapsModule_t;
typedef struct imapsModuleSymbol_t* mapsFunction_t;
typedef struct imapsMemPoolHandle_t* mapsMemPool_t;
typedef struct imapsEvent_t* mapsEvent_t;
typedef struct imapsStream_t* mapsStream_t;
typedef void* mapsDeviceptr_t;

#define maps_IPC_HANDLE_SIZE 64
typedef struct mapsIpcMemHandle_st {
    char reserved[maps_IPC_HANDLE_SIZE];
} mapsIpcMemHandle_t;

typedef struct mapsIpcEventHandle_st {
    char reserved[maps_IPC_HANDLE_SIZE];
} mapsIpcEventHandle_t;

typedef enum mapsStreamCaptureMode {
    mapsStreamCaptureModeGlobal = 0,
    mapsStreamCaptureModeThreadLocal,
    mapsStreamCaptureModeRelaxed
} mapsStreamCaptureMode;
typedef enum mapsStreamCaptureStatus {
    mapsStreamCaptureStatusNone = 0,    ///< Stream is not capturing
    mapsStreamCaptureStatusActive,      ///< Stream is actively capturing
    mapsStreamCaptureStatusInvalidated  ///< Stream is part of a capture sequence that has been
                                     ///< invalidated, but not terminated
} mapsStreamCaptureStatus;

typedef int mapsDevice_t;

typedef void (*mapsStreamCallback_t)(mapsStream_t stream, mapsError_t status, void* userData);

typedef void (*mapsHostFn_t)(void* userData);

typedef enum mapsMemcpyKind
{
    mapsMemcpyHostToHost = 0,     ///< Host-to-Host Copy
    mapsMemcpyHostToDevice = 1,   ///< Host-to-Device Copy
    mapsMemcpyDeviceToHost = 2,   ///< Device-to-Host Copy
    mapsMemcpyDeviceToDevice = 3, ///< Device-to-Device Copy
    mapsMemcpyDefault = 4, ///< Runtime will automatically determine
} mapsMemcpyKind;

typedef struct mapsArray* mapsArray_t;
typedef const struct mapsArray* mapsArray_const_t;
typedef struct mapsPitchedPtr {
    void* ptr;
    size_t pitch;
    size_t xsize;
    size_t ysize;
} mapsPitchedPtr;
typedef struct mapsExtent {
    size_t width;  // Width in elements when referring to array memory, in bytes when referring to linear memory
    size_t height;
    size_t depth;
} mapsExtent;
typedef struct mapsPos {
    size_t x;
    size_t y;
    size_t z;
} mapsPos;
typedef struct mapsMemcpy3DParms {
    mapsArray_t srcArray;
    struct mapsPos srcPos;
    struct mapsPitchedPtr srcPtr;
    mapsArray_t dstArray;
    struct mapsPos dstPos;
    struct mapsPitchedPtr dstPtr;
    struct mapsExtent extent;
    enum mapsMemcpyKind kind;
} mapsMemcpy3DParms;
static inline struct mapsPitchedPtr make_mapsPitchedPtr(void* d, size_t p, size_t xsz, size_t ysz) {
    struct mapsPitchedPtr s;
    s.ptr = d;
    s.pitch = p;
    s.xsize = xsz;
    s.ysize = ysz;
    return s;
}
static inline struct mapsPos make_mapsPos(size_t x, size_t y, size_t z) {
    struct mapsPos p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}
static inline struct mapsExtent make_mapsExtent(size_t w, size_t h, size_t d) {
    struct mapsExtent e;
    e.width = w;
    e.height = h;
    e.depth = d;
    return e;
}

typedef enum mapsMemoryType {
    mapsMemoryTypeUnregistered = 0,  ///< Unregistered memory
    mapsMemoryTypeHost         = 1,  ///< Memory is physically located on host
    mapsMemoryTypeDevice       = 2,  ///< Memory is physically located on device. (see deviceId for
                                    ///< specific device)
    mapsMemoryTypeManaged      = 3,  ///< Managed memory, automaticallly managed by the unified
                                    ///< memory system
                                    ///< place holder for new values.
    mapsMemoryTypeArray        = 10, ///< Array memory, physically located on device. (see deviceId for
                                    ///< specific device)
    mapsMemoryTypeUnified      = 11  ///< unified address space

} mapsMemoryType;

/* maps-scale malloc flag */
typedef enum mapsScaleMemoryFlag {
    mapsScaleMemorySpu              = 0,
    mapsScaleMemoryMpu              = 1,
    mapsScaleMemoryDdr              = 2,
    mapsScaleMemorySpuNocCacheable  = 3,
} mapsScaleMemoryFlag;

/**
 * MAPS launch attributes
 */
typedef enum mapsLaunchAttributeID {
    mapsLaunchAttributeIgnore                = 0,
    mapsLaunchAttributeCooperative           = 1,
    mapsLaunchAttributeClusterDimension      = 2,
    mapsLaunchAttributeSmq                   = 3,
    mapsLaunchAttributeApcMask               = 4,
    mapsLaunchAttributeMetricsMask           = 5,               
    mapsLaunchAttributeConcurrencyThread     = 999
} mapsLaunchAttributeID;

typedef union mapsLaunchAttributeValue {
    char pad[64]; /* Pad to 64 bytes */
    int cooperative; /**< Nonzero indicates a cooperative kernel */
    struct {
        unsigned int x;
        unsigned int y;
        unsigned int z;
    } clusterDim; /**< Cluster dimensions for the kernel node. */
    int concurrencyThread;
    int smqEnable;
    uint32_t apcMask;
    uint64_t metricsMask;
} mapsLaunchAttributeValue;

typedef struct mapsLaunchAttribute_st {
    mapsLaunchAttributeID id;
    char pad[8 - sizeof(mapsLaunchAttributeID)];
    mapsLaunchAttributeValue val;
} mapsLaunchAttribute;

/**
 * used for mapsLaunchKernelExc
 */
typedef struct mapsLaunchConfig_st {
    dim3 gridDim;               /**< Grid dimensions */
    dim3 blockDim;              /**< Block dimensions */
    size_t dynamicSmemBytes;    /**< Dynamic shared-memory size per thread block in bytes */
    mapsStream_t stream;        /**< Stream identifier */
    mapsLaunchAttribute *attrs; /**< nullable if numAttrs == 0 */
    unsigned int numAttrs;      /**< Number of attributes populated in attrs */
} mapsLaunchConfig_t;

typedef enum mapsPointer_attribute {
    MAPS_POINTER_ATTRIBUTE_CONTEXT = 1,   ///< The context on which a pointer was allocated
                                         ///< @warning - not supported in MAPS
    MAPS_POINTER_ATTRIBUTE_MEMORY_TYPE,   ///< memory type describing location of a pointer
    MAPS_POINTER_ATTRIBUTE_DEVICE_POINTER,///< address at which the pointer is allocated on device
    MAPS_POINTER_ATTRIBUTE_HOST_POINTER,  ///< address at which the pointer is allocated on host
    MAPS_POINTER_ATTRIBUTE_P2P_TOKENS,    ///< A pair of tokens for use with linux kernel interface
                                         ///< @warning - not supported in MAPS
    MAPS_POINTER_ATTRIBUTE_SYNC_MEMOPS,   ///< Synchronize every synchronous memory operation
                                         ///< initiated on this region
    MAPS_POINTER_ATTRIBUTE_BUFFER_ID,     ///< Unique ID for an allocated memory region
    MAPS_POINTER_ATTRIBUTE_IS_MANAGED,    ///< Indicates if the pointer points to managed memory
    MAPS_POINTER_ATTRIBUTE_DEVICE_ORDINAL,///< device ordinal of a device on which a pointer
                                         ///< was allocated or registered
    MAPS_POINTER_ATTRIBUTE_IS_LEGACY_MAPS_IPC_CAPABLE, ///< if this pointer maps to an allocation
                                                     ///< that is suitable for mapsIpcGetMemHandle
                                                     ///< @warning - not supported in MAPS
    MAPS_POINTER_ATTRIBUTE_RANGE_START_ADDR,///< Starting address for this requested pointer
    MAPS_POINTER_ATTRIBUTE_RANGE_SIZE,      ///< Size of the address range for this requested pointer
    MAPS_POINTER_ATTRIBUTE_MAPPED,          ///< tells if this pointer is in a valid address range
                                           ///< that is mapped to a backing allocation
    MAPS_POINTER_ATTRIBUTE_ALLOWED_HANDLE_TYPES,///< Bitmask of allowed mapsmemAllocationHandleType
                                           ///< for this allocation @warning - not supported in MAPS
    MAPS_POINTER_ATTRIBUTE_IS_GPU_DIRECT_RDMA_CAPABLE, ///< returns if the memory referenced by
                                           ///< this pointer can be used with the GPUDirect RDMA API
                                           ///< @warning - not supported in MAPS
    MAPS_POINTER_ATTRIBUTE_ACCESS_FLAGS,    ///< Returns the access flags the device associated with
                                           ///< for the corresponding memory referenced by the ptr
    MAPS_POINTER_ATTRIBUTE_MEMPOOL_HANDLE   ///< Returns the mempool handle for the allocation if
                                           ///< it was allocated from a mempool
                                           ///< @warning - not supported in MAPS
} mapsPointer_attribute;

/**
 * Pointer attributes
 */
typedef struct mapsPointerAttribute_t {
    enum mapsMemoryType type;
    int device;
    void* devicePointer;
    void* hostPointer;
    int isManaged;
    unsigned allocationFlags; /* flags specified when memory was allocated*/
    size_t size;
    void* devicePointerStart;
    /* peers? */
} mapsPointerAttribute_t;
#define mapsInvalidDeviceId ((int)-2)

enum mapsLimit_t {
    mapsLimitStackSize = 0x0,        ///< Limit of stack size in bytes on the current device, per
                                    ///< thread. The size is in units of 256 dwords, up to the
                                    ///< limit of (128K - 16)
    mapsLimitPrintfFifoSize = 0x01,  ///< Size limit in bytes of fifo used by printf call on the
                                    ///< device. Currently not supported
    mapsLimitMallocHeapSize = 0x02,  ///< Limit of heap size in bytes on the current device, should
                                    ///< be less than the global memory size on the device
    mapsLimitRange                   ///< Supported limit range
};

typedef struct mapsFuncAttributes {
    int binaryVersion;
    int cacheModeCA;
    size_t constSizeBytes;
    size_t localSizeBytes;
    int maxDynamicSharedSizeBytes;
    int maxThreadsPerBlock;
    int numRegs;
    int preferredShmemCarveout;
    int ptxVersion;
    size_t sharedSizeBytes;
} mapsFuncAttributes;

typedef enum mapsDeviceP2PAttr {
  mapsDevP2PAttrPerformanceRank = 0,
  mapsDevP2PAttrAccessSupported,
  mapsDevP2PAttrNativeAtomicSupported,
  mapsDevP2PAttrMapsArrayAccessSupported
} mapsDeviceP2PAttr;

#if __GUNC__
#pragma GCC visibility push(default)
#endif

#ifdef __cplusplus
extern "C" {
#endif

mapsError_t mapsInit(unsigned int flags);
mapsError_t mapsInitEarly(unsigned int flags);
mapsError_t mapsDeviceSynchronize();
mapsError_t mapsSetDevice(int deviceId);
mapsError_t mapsDeviceReset(void);
mapsError_t mapsGetDeviceCount(int* count);
mapsError_t mapsGetDeviceProperties(mapsDeviceProp_t* prop, int deviceId);
mapsError_t mapsDeviceGetAttribute(int* pi, mapsDeviceAttribute_t attr, int deviceId);
mapsError_t mapsGetDevice(int* deviceId);
mapsError_t mapsDriverGetVersion(int* driverVersion);
mapsError_t mapsDeviceGetPCIBusId(char* pciBusId, int len, int device);
mapsError_t mapsDeviceCanAccessPeer(int* canAccessPeer, int device, int peerDevice);
mapsError_t mapsDeviceEnablePeerAccess(int peerDevice, unsigned int flags);
mapsError_t mapsDeviceDisablePeerAccess(int peerDevice);
mapsError_t mapsMemcpyPeer(void* dst, int dstDevice, const void *src, int srcDevice, size_t count);
mapsError_t mapsMemcpyPeerAsync(void * dst, int dstDevice, const void* src, int srcDevice, size_t count, mapsStream_t stream __dparm(0));

mapsError_t mapsThreadExchangeStreamCaptureMode(enum mapsStreamCaptureMode* mode);

mapsError_t mapsMalloc(void** ptr, size_t size);
mapsError_t mapsMallocHost(void** ptr, size_t size);
mapsError_t mapsHostAlloc(void** ptr, size_t size, unsigned int flags);
mapsError_t mapsHostMalloc(void** ptr, size_t size, unsigned int flags);
mapsError_t mapsHostGetDevicePointer(void** devPtr, void* hstPtr, unsigned int flags);
mapsError_t mapsMallocManaged(void** devPtr, size_t size, unsigned int flags __dparm(mapsMemAttachGlobal));
mapsError_t mapsMallocPitch(void** ptr, size_t* pitch, size_t width, size_t height);
mapsError_t mapsMalloc3D(mapsPitchedPtr* pitchedDevPtr, mapsExtent extent);
mapsError_t mapsFree(void* ptr);
mapsError_t mapsFreeHost(void* ptr);
mapsError_t mapsHostFree(void* ptr);
mapsError_t mapsMemGetInfo(size_t *free, size_t *total);

mapsError_t mapsMemAlloc(void** dptr, size_t size);
mapsError_t mapsMemAllocHost(void** ptr, size_t size);
mapsError_t mapsMemAllocManaged(void** dptr, size_t size, unsigned int flags __dparm(mapsMemAttachGlobal));
mapsError_t mapsMemAllocPitch(void** dptr, size_t* pitch, size_t width, size_t height);
mapsError_t mapsMemFree(void* dptr);
mapsError_t mapsMemFreeHost(void* ptr);
mapsError_t mapsMemHostAlloc(void **ptr, size_t size, unsigned int flags);

mapsError_t mapsMemcpy(void* dst, const void* src, size_t sizeBytes, mapsMemcpyKind kind);
mapsError_t mapsMemcpyAsync(void* dst, const void* src, size_t sizeBytes, mapsMemcpyKind kind,
                            mapsStream_t stream __dparm(0));
mapsError_t mapsMemcpy2D(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height,
                         mapsMemcpyKind kind);
mapsError_t mapsMemcpy2DAsync(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height,
                              mapsMemcpyKind kind, mapsStream_t stream __dparm(0));
mapsError_t mapsMemcpy3D(const struct mapsMemcpy3DParms* p);
mapsError_t mapsMemcpy3DAsync(const struct mapsMemcpy3DParms* p, mapsStream_t stream __dparm(0));
mapsError_t mapsMemset(void* dst, int value, size_t sizeBytes);
mapsError_t mapsMemsetAsync(void* dst, int value, size_t sizeBytes, mapsStream_t stream __dparm(0));
mapsError_t mapsCfgUpdateEx(int nargs, uint32_t args[], int nevents, void* e_addrs[], uint32_t write_values[],
                            uint32_t wait_values[], mapsStream_t stream);

mapsError_t mapsIpcGetMemHandle(mapsIpcMemHandle_t* handle, void* devPtr);
mapsError_t mapsIpcOpenMemHandle(void** devPtr, mapsIpcMemHandle_t handle, unsigned int flags);
mapsError_t mapsIpcCloseMemHandle(void* devPtr);
mapsError_t mapsIpcGetEventHandle(mapsIpcEventHandle_t* handle, mapsEvent_t event);
mapsError_t mapsIpcOpenEventHandle(mapsEvent_t* event, mapsIpcEventHandle_t handle);

mapsError_t mapsStreamCreate(mapsStream_t* stream, bool useQfc __dparm(true));
mapsError_t mapsStreamCreateWithFlags(mapsStream_t* stream, unsigned int flags, bool useQfc __dparm(true));
mapsError_t mapsStreamCreateWithPriority(mapsStream_t* stream, unsigned int flags, int priority,
                                         bool useQfc __dparm(true));
mapsError_t mapsStreamDestroy(mapsStream_t stream);
mapsError_t mapsStreamQuery(mapsStream_t stream);
mapsError_t mapsStreamSynchronize(mapsStream_t stream);
mapsError_t mapsStreamGetDevice(mapsStream_t stream, mapsDevice_t* device);
mapsError_t mapsExtStreamCreateWithCUMask(mapsStream_t* stream, uint32_t cuMaskSize, const uint32_t* cuMask);

mapsError_t mapsStreamAddCallback(mapsStream_t stream, mapsStreamCallback_t callback, void* userData,
                                  unsigned int flags);
mapsError_t mapsStreamSynchronize(mapsStream_t stream);
mapsError_t mapsStreamWaitEvent(mapsStream_t stream, mapsEvent_t event, unsigned int flags __dparm(0));
mapsError_t mapsStreamTestNop(mapsStream_t stream, uint32_t qfcMode __dparm(0));


mapsError_t mapsEventCreate(mapsEvent_t* event);
mapsError_t mapsEventRecord(mapsEvent_t event, mapsStream_t stream __dparm(NULL));
mapsError_t mapsEventDestroy(mapsEvent_t event);
mapsError_t mapsEventSynchronize(mapsEvent_t event);
mapsError_t mapsEventElapsedTime(float* ms, mapsEvent_t start, mapsEvent_t stop);
mapsError_t mapsEventElapsedTimeEx(float* ms, uint64_t *cycle, mapsEvent_t start, mapsEvent_t stop);
mapsError_t mapsEventQuery(mapsEvent_t event);
mapsError_t mapsEventCreateWithFlags(mapsEvent_t* event, unsigned flags);

mapsError_t mapsLaunchKernel(const void* function_address, dim3 numBlocks, dim3 dimBlocks, void** args,
                             size_t sharedMemBytes __dparm(0), mapsStream_t stream __dparm(0));
mapsError_t mapsLaunchKernelExc(const mapsLaunchConfig_t *config, const void *function_address, void **args);
mapsError_t mapsMemobjGetPhysicalAddress(void *ptr, uint64_t *pa);
mapsError_t mapsLaunchHostFunc(mapsStream_t stream, mapsHostFn_t fn, void* userData);
mapsError_t mapsMemobjGetDevMemGpupaEx(void* ptr, void** pa);
mapsError_t mapsFuncGetName(const char** name, const void* func);
mapsError_t mapsFuncGetParamCount(const void* func, size_t* paramCount);
mapsError_t mapsFuncGetParamInfo(const void* func, size_t paramIndex, size_t* paramOffset, size_t* paramSize);

mapsError_t mapsGetLastError();
const char* mapsGetErrorString(mapsError_t maps_error);
const char* mapsGetErrorName(mapsError_t maps_error);

mapsError_t mapsGetApcMask(int device_id, uint32_t* hwApcMask);

mapsError_t mapsSetEnv(const char* name, const char* value);
mapsError_t mapsDevReset(uint32_t reset_type, int32_t *reset_status);
mapsError_t mapsCtxCreate(mapsCtx_t* ctx, unsigned int flags, mapsDevice_t device);
mapsError_t mapsCtxSetCurrent(mapsCtx_t ctx);
mapsError_t mapsCtxGetCurrent(mapsCtx_t* ctx);
mapsError_t mapsCtxDestroy(mapsCtx_t ctx);
mapsError_t mapsCtxSynchronize(void);

mapsError_t mapsApc32FwUpdateEx(void);
mapsError_t mapsGetAsidEx(uint32_t *asid);
mapsError_t mapsGetAmmuBaseAddrEx(uint64_t *addr);
mapsError_t mapsGetSymbolAddress(void** device_ptr, const void* symbol);
mapsError_t mapsDeviceSetLimit ( enum mapsLimit_t limit, size_t value );
mapsError_t mapsDeviceGetP2PAttribute(int* value, mapsDeviceP2PAttr attr, int srcDevice, int dstDevice);
mapsError_t mapsRuntimeGetVersion(int* version);

mapsError_t mapsPointerGetAttributes(mapsPointerAttribute_t* attributes, const void* ptr);
mapsError_t mapsOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, const void *func,
                                                          int blockSize, size_t dynamicSMemSize);
mapsError_t mapsOccupancyMaxPotentialBlockSize(int* gridSize, int* blockSize,
                                             const void* f, size_t dynSharedMemPerBlk,
                                             int blockSizeLimit);

/* host register */
mapsError_t mapsHostRegister(void* hostPtr, size_t size, unsigned int flags);
mapsError_t mapsHostUnregister(void* hostPtr);
mapsError_t mapsHostGetDevicePointer(void** devPtr, void* hostPtr, unsigned int flags);

mapsError_t mapsGetSymbolAddress(void** devPtr, const void* hostVar);
mapsError_t mapsGetSymbolSize(size_t* size, const void* hostVar);
mapsError_t mapsMemcpyToSymbol(const void* hostVar, void* src, size_t sizeBytes, size_t offset, mapsMemcpyKind kind);
mapsError_t mapsMemcpyToSymbolAsync(const void* hostVar, void* src, size_t sizeBytes, size_t offset, mapsMemcpyKind kind, mapsStream_t stream);
mapsError_t mapsMemcpyFromSymbol(void* dst, const void* hostVar, size_t sizeBytes, size_t offset, mapsMemcpyKind kind);
mapsError_t mapsMemcpyFromSymbolAsync(void* dst, const void* hostVar, size_t sizeBytes, size_t offset, mapsMemcpyKind kind, mapsStream_t stream);

#ifdef __cplusplus
}
#endif

#if __GUNC__
#pragma GCC visibility pop
#endif

#endif // MAPS_RUNTIME_API_H_
