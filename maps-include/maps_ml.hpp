#ifndef MAPS_ML_H
#define MAPS_ML_H

#include <cstdint>
#include <cstddef>

#define MAPSML_DEVICE_UUID_BUFFER_SIZE 80
#define MAPSML_ML_VERSION_BUFFER_SIZE 80
#define MAPSML_VBIOS_VERSION_BUUFER_SIZE 32
#define MAPSML_DEVICE_NAME_BUFFER_SIZE 64
#define MAPSML_DRIVER_VERSION_BUFFER_SIZE 80
#define MAPSML_DEVICE_SERIAL_BUFFER_SIZE 30
#define MAPSML_DEVICE_UUID_BUFFER_SIZE 80
#define MAPSML_DEVICE_UUID_V2_BUFFER_SIZE 96

typedef enum mapsmlReturn_enum
{
    MAPSML_SUCCESS = 0,
    MAPSML_ERROR_UNINITIALIZED = 1,
    MAPSML_ERROR_INVALID_ARGUMENT = 2,
    MAPSML_ERROR_NOT_SUPPORT = 3,
    MAPSML_ERROR_NO_PERMISSION = 4,
    MAPSML_ERROR_ALREADY_INITIALIZED = 5,
    MAPSML_ERROR_NOT_FOUND = 6,
    MAPSML_ERROR_INSUFFICIENT_SIZE = 7, // buff size not
    MAPSML_ERROR_INSUFFICIENT_POWER = 8,
    MAPSML_ERROR_DRIVER_NOT_LOADED = 9,
    MAPSML_ERROR_TIMEOUT = 10,
    MAPSML_ERROR_IRQ_ISSUE = 11,
    MAPSML_ERROR_LIBRARY_NOT_FOUND = 12,
    MAPSML_ERROR_FUNCTION_NOT_FOUND = 13,
    MAPSML_ERROR_CORRUPTED_INFOROM = 14, // info rom bad
    MAPSML_ERROR_GPU_IS_LOST = 15,
    MAPSML_ERROR_RESET_REQUIRED = 16,
    MAPSML_ERROR_OPERATING_SYSTEM = 17,
    MAPSML_ERROR_LIB_RM_VERSION_MISMATCH = 18,
    MAPSML_ERROR_IN_USE = 19,
    MAPSML_ERROR_MEMORY = 20,
    MAPSML_ERROR_NO_DATA = 21,
    MAPSML_ERROR_VGPU_ECC_NOT_SUPPORTED = 22,
    MAPSML_ERROR_INSUFFICIENT_RESOURCES = 23, //
    MAPSML_ERROR_FREQ_NOT_SUPPORTED = 24,
    MAPSML_ERROR_ARGUMENT_VERSION_MISMATCH = 25,
    MAPSML_ERROR_DEPRECATED = 26,
    MAPSML_ERROR_NOT_READY = 27,
    MAPSML_ERROR_GPU_NOT_FOUND = 28,
    MAPSML_ERROR_INVALID_STATE = 29,
    MAPSML_ERROR_RESET_TYPE_NOT_SUPPORTED = 30,
    MAPSML_ERROR_UNKNOWN = 999,
} mapsmlReturn_t;

typedef struct mapsmlDevice *mapsmlDevice_t;

typedef unsigned int mapsmlDeviceIndex_t;

typedef enum mapsmlTemperatureSensors_enum
{
    MAPSML_TEMPERATURE_GPU = 0,
    MAPSML_TEMPERATURE_MEMORY = 1,
    MAPSML_TEMPERATURE_COUNT
} mapsmlTemperatureSensors_t;

typedef enum mapsmlClockType_enum
{
    MAPSML_CLOCK_GRAPHICS = 0,
    MAPSML_CLOCK_SM = 1,
    MAPSML_CLOCK_MEM = 2,
    MAPSML_CLOCK_VIDEO = 3,
    MAPSML_CLOCK_COUNT
} mapsmlClockType_t;

typedef enum mapsmlMemoryLocation_enum
{
    MAPSML_MEMORY_LOCATION_L1_CACHE = 0,
    MAPSML_MEMORY_LOCATION_L2_CACHE = 1,
    MAPSML_MEMORY_LOCATION_DEVICE_MEMORY = 2,
    MAPSML_MEMORY_LOCATION_REGISTER_FILE = 3,
    MAPSML_MEMORY_LOCATION_TEXTURE_MEMORY = 4,
    MAPSML_MEMORY_LOCATION_COUNT
} mapsmlMemoryLocation_t;

typedef enum mapsmlEccErrorType_enum
{
    MAPSML_SINGLE_BIT_ECC = 0,
    MAPSML_DOUBLE_BIT_ECC = 1,
    MAPSML_ECC_ERROR_TYPE_COUNT
} mapsmlEccErrorType_t;

typedef enum mapsmlEccCounterType_enum
{
    MAPSML_VOLATILE_ECC = 0,
    MAPSML_AGGREGATE_ECC = 1,
    MAPSML_ECC_COUNTER_TYPE_COUNT
} mapsmlEccCounterType_t;

typedef enum mapsmlPstates_enum
{
    MAPSML_PSTATE_0 = 0,
    MAPSML_PSTATE_1 = 1,
    MAPSML_PSTATE_2 = 2,
    MAPSML_PSTATE_3 = 3,
    MAPSML_PSTATE_4 = 4,
    MAPSML_PSTATE_5 = 5,
    MAPSML_PSTATE_6 = 6,
    MAPSML_PSTATE_7 = 7,
    MAPSML_PSTATE_8 = 8,
    MAPSML_PSTATE_9 = 9,
    MAPSML_PSTATE_10 = 10,
    MAPSML_PSTATE_11 = 11,
    MAPSML_PSTATE_12 = 12,
    MAPSML_PSTATE_13 = 13,
    MAPSML_PSTATE_14 = 14,
    MAPSML_PSTATE_15 = 15,
    MAPSML_PSTATE_UNKNOWN = 32
} mapsmlPstates_t;

typedef enum mapsmlBrandType_enum
{
    MAPSML_BRAND_UNKNOWN = 0,
    MAPSML_BRAND_A = 1,
    MAPSML_BRAND_S = 2,
    MAPSML_BRAND_COUNT = 3
} mapsmlBrandType_t;

/**
 * Represents the queryable PCIe utilization counters
 */
typedef enum mapsmlPcieUtilCounter_enum
{
    MAPSML_PCIE_UTIL_TX_BYTES = 0, // 1KB granularity
    MAPSML_PCIE_UTIL_RX_BYTES = 1, // 1KB granularity

    // Keep this last
    MAPSML_PCIE_UTIL_COUNT
} mapsmlPcieUtilCounter_t;

/**
 * Represents level relationships within a system between two GPUs
 * The enums are spaced to allow for future relationships
 */
typedef enum mapsmlGpuLevel_enum
{
    MAPSML_TOPOLOGY_INTERNAL = 0,    // e.g. Tesla K80
    MAPSML_TOPOLOGY_SINGLE = 10,     // all devices that only need traverse a single PCIe switch
    MAPSML_TOPOLOGY_MULTIPLE = 20,   // all devices that need not traverse a host bridge
    MAPSML_TOPOLOGY_HOSTBRIDGE = 30, // all devices that are connected to the same host bridge
    MAPSML_TOPOLOGY_NODE = 40,       // all devices that are connected to the same NUMA node but possibly multiple host bridges
    MAPSML_TOPOLOGY_SYSTEM = 50      // all devices in the system

    // there is purposefully no COUNT here because of the need for spacing above
} mapsmlGpuTopologyLevel_t;

/**
 * Generic enable/disable enum.
 */
typedef enum mapsmlEnableState_enum
{
    MAPSML_FEATURE_DISABLED = 0, //!< Feature disabled
    MAPSML_FEATURE_ENABLED = 1   //!< Feature enabled
} mapsmlEnableState_t;

/**
 * Enum to represent NvLink queryable capabilities
 */
typedef enum mapsmlNvLinkCapability_enum
{
    MAPSML_NVLINK_CAP_P2P_SUPPORTED = 0,  // P2P over NVLink is supported
    MAPSML_NVLINK_CAP_SYSMEM_ACCESS = 1,  // Access to system memory is supported
    MAPSML_NVLINK_CAP_P2P_ATOMICS = 2,    // P2P atomics are supported
    MAPSML_NVLINK_CAP_SYSMEM_ATOMICS = 3, // System memory atomics are supported
    MAPSML_NVLINK_CAP_SLI_BRIDGE = 4,     // SLI is supported over this link
    MAPSML_NVLINK_CAP_VALID = 5,          // Link is supported on this device
    // should be last
    MAPSML_NVLINK_CAP_COUNT
} mapsmlNvLinkCapability_t;

/**
 * Enum to represent NvLink queryable error counters
 */
typedef enum mapsmlNvLinkErrorCounter_enum
{
    MAPSML_NVLINK_ERROR_DL_REPLAY = 0,   // Data link transmit replay error counter
    MAPSML_NVLINK_ERROR_DL_RECOVERY = 1, // Data link transmit recovery error counter
    MAPSML_NVLINK_ERROR_DL_CRC_FLIT = 2, // Data link receive flow control digit CRC error counter
    MAPSML_NVLINK_ERROR_DL_CRC_DATA = 3, // Data link receive data CRC error counter
    MAPSML_NVLINK_ERROR_DL_ECC_DATA = 4, // Data link receive data ECC error counter

    // this must be last
    MAPSML_NVLINK_ERROR_COUNT
} mapsmlNvLinkErrorCounter_t;

/**
 * Memory error types
 */
typedef enum mapsmlMemoryErrorType_enum
{
    /**
     * A memory error that was corrected
     *
     * For ECC errors, these are single bit errors
     * For Texture memory, these are errors fixed by resend
     */
    MAPSML_MEMORY_ERROR_TYPE_CORRECTED = 0,
    /**
     * A memory error that was not corrected
     *
     * For ECC errors, these are double bit errors
     * For Texture memory, these are errors where the resend fails
     */
    MAPSML_MEMORY_ERROR_TYPE_UNCORRECTED = 1,

    // Keep this last
    MAPSML_MEMORY_ERROR_TYPE_COUNT //!< Count of memory error types

} mapsmlMemoryErrorType_t;

/**
 * Simplified chip architecture
 */
#define MAPSML_DEVICE_ARCH_A 1 //
#define MAPSML_DEVICE_ARCH_S 2 //
// #define MAPSML_DEVICE_ARCH_PASCAL 4  // Devices based on the NVIDIA Pascal architecture
// #define MAPSML_DEVICE_ARCH_VOLTA 5   // Devices based on the NVIDIA Volta architecture
// #define MAPSML_DEVICE_ARCH_TURING 6  // Devices based on the NVIDIA Turing architecture

// #define MAPSML_DEVICE_ARCH_AMPERE 7 // Devices based on the NVIDIA Ampere architecture

#define MAPSML_DEVICE_ARCH_UNKNOWN 0xffffffff // Anything else, presumably something newer

typedef unsigned int mapsmlDeviceArchitecture_t;

typedef struct mapsmlDeviceAttributes_st
{
    char name[64];   // 设备名称
    char brand[32];  // 品牌
    char serail[30]; // 序列号
    unsigned short pciVendorId;
    unsigned int pciDeviceId;
    unsigned int pciSubSystemId;
    unsigned int pciDomain;
    unsigned int pciBus;
    unsigned int pciDevice;
    unsigned int pciFunction;
} mapsmlDeviceAttributes_t;

typedef struct mapsmlMemory_st
{
    unsigned long long total;
    unsigned long long free;
    unsigned long long used;
} mapsmlMemory_t;

typedef struct mapsmlUtilization_st
{
    unsigned int gpu;
    unsigned int memory;
} mapsmlUtilization_t;

typedef struct mapsmlEccErrorCounts_st
{
    unsigned long long l1Cached;
    unsigned long long l2Cached;
    unsigned long long deviceMemory;
    unsigned long long registerFile;
} mapsmlEccErrorCounts_t;

typedef struct mapsmlPowerUsage_st
{
    unsigned int power;
    unsigned int powerLimit;
    unsigned int powerDefaultLimit;
    unsigned int powerMinLimit;
    unsigned int powerMaxLimit;
} mapsmlPowerUsage_t;

typedef struct mapsmlTemperature_st
{
    unsigned int gpu;         // GPU温度
    unsigned int memory;      // 内存温度
    unsigned int powerSupply; // 电源温度
    unsigned int board;       // 板卡温度
} mapsmlTemperature_t;

typedef struct mapsmlClockInfo_st
{
    unsigned int graphicsClock; // 图形时钟
    unsigned int smClock;       // sm时钟
    unsigned int memClock;      // 内存时钟
    unsigned int videoClock;    // 视频时钟
} mapsmlClockInfo_t;

typedef struct mapsmlPerformanceState_st
{
    mapsmlPstates_t pState;                  // 性能状态
    unsigned int clocks[MAPSML_CLOCK_COUNT]; // 时钟频率
} mapsmlPerformanceState_t;

#define MAPSML_DEVICE_PCI_BUS_ID_BUFFER_SIZE 32
#define MAPSML_DEVICE_PCI_BUS_ID_BUFFER_V2_SIZE 16

typedef struct mapsmlPciInfo_st
{
    char busIdLegacy[MAPSML_DEVICE_PCI_BUS_ID_BUFFER_V2_SIZE]; //!< The legacy tuple domain:bus:device.function PCI identifier (&amp; NULL terminator)
    unsigned int domain;                                       //!< The PCI domain on which the device's bus resides, 0 to 0xffffffff
    unsigned int bus;                                          //!< The bus on which the device resides, 0 to 0xff
    unsigned int device;                                       //!< The device's id on the bus, 0 to 31
    unsigned int pciDeviceId;                                  //!< The combined 16-bit device id and 16-bit vendor id

    // Added in NVML 2.285 API
    unsigned int pciSubSystemId; //!< The 32-bit Sub System Device ID

    char busId[MAPSML_DEVICE_PCI_BUS_ID_BUFFER_SIZE]; //!< The tuple domain:bus:device.function PCI identifier (&amp; NULL terminator)
} mapsmlPciInfo_t;

/**
 * Structure to store utilization value and process Id
 */
typedef struct mapsmlProcessUtilizationSample_st
{
    unsigned int pid;             //!< PID of process
    unsigned long long timeStamp; //!< CPU Timestamp in microseconds
    unsigned int smUtil;          //!< SM (3D/Compute) Util Value
    unsigned int memUtil;         //!< Frame Buffer Memory Util Value
    unsigned int encUtil;         //!< Encoder Util Value
    unsigned int decUtil;         //!< Decoder Util Value
} mapsmlProcessUtilizationSample_t;

/**
 * Information about running compute processes on the GPU
 */
typedef struct mapsmlProcessInfo_st
{
    unsigned int pid;                 //!< Process ID
    unsigned long long usedGpuMemory; //!< Amount of used GPU memory in bytes.
                                      //! Under WDDM, \ref NVML_VALUE_NOT_AVAILABLE is always reported
                                      //! because Windows KMD manages all the memory and not the NVIDIA driver
    unsigned int gpuInstanceId;       //!< If MIG is enabled, stores a valid GPU instance ID. gpuInstanceId is set to
                                      //  0xFFFFFFFF otherwise.
    unsigned int computeInstanceId;   //!< If MIG is enabled, stores a valid compute instance ID. computeInstanceId is set to
                                      //  0xFFFFFFFF otherwise.
} mapsmlProcessInfo_t;

#define mapsmlEventTypeNone 0x0000000000000000LL
#define mapsmlEventTypeSingleBitEccError 0x0000000000000080LL
#define mapsmlEventTypeTemp 0x0000000000000010LL

typedef struct mapsmlEventSet_st *mapsmlEventSet_t;
typedef struct {
    mapsmlDevice_t device;
    unsigned long long eventType;
    unsigned long long mask;
    unsigned long long eventData;
    unsigned int reserved[8];
} mapsmlEventData_t;

#ifdef __cplusplus
extern "C"
{
#endif

    mapsmlReturn_t mapsmlInit(void);
    mapsmlReturn_t mapsmlShutdown(void);

    mapsmlReturn_t mapsmlDeviceGetCount(unsigned int *deviceCount);
    mapsmlReturn_t mapsmlDeviceGetHandleByIndex(unsigned int index, mapsmlDevice_t *device);
    mapsmlReturn_t mapsmlDeviceGetHandleByPciBusId(const char *pciBusId, mapsmlDevice_t *device);
    mapsmlReturn_t mapsmlDeviceGetHandleByUUID(const char *uuid, mapsmlDevice_t *device);
    mapsmlReturn_t mapsmlDeviceGetAttributes(mapsmlDevice_t device, mapsmlDeviceAttributes_t *attributes);

    mapsmlReturn_t mapsmlDeviceGetTemperature(mapsmlDevice_t device, mapsmlTemperature_t *temp);
    mapsmlReturn_t mapsmlDeviceGetTemperatureThreshold(mapsmlDevice_t device, mapsmlTemperatureSensors_t sensorType, unsigned int *temp);

    mapsmlReturn_t mapsmlDeviceGetPowerUsage(mapsmlDevice_t device, unsigned int *power);
    mapsmlReturn_t mapsmlDeviceGetPowerManagementLimit(mapsmlDevice_t device, unsigned int *limit);
    mapsmlReturn_t mapsmlDeviceGetPowermanagermentDefaultLimit(mapsmlDevice_t device, unsigned int *limit);

    mapsmlReturn_t mapsmlDeviceGetMemoryInfo(mapsmlDevice_t device, mapsmlMemory_t *memory);
    mapsmlReturn_t mapsmlDeviceGetUtilRates(mapsmlDevice_t device, mapsmlUtilization_t *util);

    mapsmlReturn_t mapsmlDeviceReset(mapsmlDevice_t device);
    mapsmlReturn_t mapsmlDeviceGetClockInfo(mapsmlDevice_t device, mapsmlClockType_t type, unsigned int *clock);
    mapsmlReturn_t mapsmlDeviceSetGpuLockedClocks(mapsmlDevice_t device, unsigned int minGpuClockMHz, unsigned int maxGpuClockMHz);
    mapsmlReturn_t mapsmlDeviceResetGpuLockedClocks(mapsmlDevice_t device);
    mapsmlReturn_t mapsmlDeviceSetMemoryLockedClocks(mapsmlDevice_t device, unsigned int minMemClockMHz, unsigned int maxMemClockMHz);
    mapsmlReturn_t mapsmlDeviceGetMaxClockInfo(mapsmlDevice_t device, mapsmlClockType_t type, unsigned int *clock);
    mapsmlReturn_t mapsmlDeviceGetApplicationsClock(mapsmlDevice_t device, mapsmlClockType_t type, unsigned int *clock);

    mapsmlReturn_t mapsmlDeviceGetTotalEccErrors(mapsmlDevice_t device, mapsmlEccErrorType_t errorType, mapsmlMemoryLocation_t location, unsigned long long *counts);

    mapsmlReturn_t mapsmlDeviceGetEccMode(mapsmlDevice_t device, mapsmlEnableState_t *current, mapsmlEnableState_t *pending);
    mapsmlReturn_t mapsmlDeviceSetEccMode(mapsmlDevice_t device, mapsmlEnableState_t ecc);
    mapsmlReturn_t mapsmlDeviceClearEccErrorCounts(mapsmlDevice_t device, mapsmlEccCounterType_t counterType);

    mapsmlReturn_t mapsmlDeviceGetPerformanceState(mapsmlDevice_t device, mapsmlPstates_t *pState);
    mapsmlReturn_t mapsmlDeviceGetSupportedPerformanceStates(mapsmlDevice_t device, mapsmlPstates_t *pStates, unsigned int *count);

    mapsmlReturn_t mapsmlSystemGetMapsmlVersion(char *version, unsigned int length);
    mapsmlReturn_t mapsmlSystemGetDriverVersion(char *version, unsigned int length);
    mapsmlReturn_t mapsmlSystemGetMapsVersion(int *mapsVersion);
    mapsmlReturn_t mapsmlDeviceGetVbiosVersion(mapsmlDevice_t device, char *version, unsigned int length);

    mapsmlReturn_t mapsmlDeviceGetName(mapsmlDevice_t device, char *name, unsigned int length);
    mapsmlReturn_t mapsmlDeviceGetBrand(mapsmlDevice_t device, mapsmlBrandType_t *type);
    mapsmlReturn_t mapsmlDeviceGetArchitecture(mapsmlDevice_t device, mapsmlDeviceArchitecture_t *arch);

    mapsmlReturn_t mapsmlDeviceGetCudaComputeCapability(mapsmlDevice_t device, int *major, int *minor);
    mapsmlReturn_t mapsmlDeviceGetUUID(mapsmlDevice_t device, char *uuid, unsigned int length);
    mapsmlReturn_t mapsmlDeviceGetSerial(mapsmlDevice_t device, char *serial, unsigned int length);
    mapsmlReturn_t mapsmlDeviceGetMinorNumber(mapsmlDevice_t device, unsigned int *minorNumber);

    mapsmlReturn_t mapsmlDeviceGetBoardPartNumber(mapsmlDevice_t device, char *partNumber, unsigned int length);
    mapsmlReturn_t mapsmlDeviceGetBoardId(mapsmlDevice_t device, unsigned int *boardId);
    mapsmlReturn_t mapsmlDeviceGetMultiGpuBoard(mapsmlDevice_t device, unsigned int *multiGpuBool);

    mapsmlReturn_t mapsmlDeviceGetPciInfo(mapsmlDevice_t device, mapsmlPciInfo_t *pci);
    mapsmlReturn_t mapsmlDeviceGetMaxPcieLinkGeneration(mapsmlDevice_t device, unsigned int *maxLinkGen);
    mapsmlReturn_t mapsmlDeviceGetCurrPcieLinkGeneration(mapsmlDevice_t device, unsigned int *currLinkGen);
    mapsmlReturn_t mapsmlDeviceGetCurrPcieLinkWidth(mapsmlDevice_t device, unsigned int *currLinkWidth);
    mapsmlReturn_t mapsmlDeviceGetPcieThroughput(mapsmlDevice_t device, mapsmlPcieUtilCounter_t counter, unsigned int *value);

    mapsmlReturn_t mapsmlDeviceGetTopologyCommonAncestor(mapsmlDevice_t device1, mapsmlDevice_t device2, mapsmlGpuTopologyLevel_t *pathInfo);
    mapsmlReturn_t mapsmlDeviceGetTopologyNearestGpus(mapsmlDevice_t device, mapsmlGpuTopologyLevel_t level, unsigned int *count, mapsmlDevice_t *deviceArray);

    mapsmlReturn_t mapsmlDeviceGetNvLinkState(mapsmlDevice_t device, unsigned int link, mapsmlEnableState_t *isActive);
    mapsmlReturn_t mapsmlDeviceGetNvLinkVersion(mapsmlDevice_t device, unsigned int link, unsigned int *version);
    mapsmlReturn_t mapsmlDeviceGetNvLinkCapability(mapsmlDevice_t device, unsigned int link,
                                                   mapsmlNvLinkCapability_t capability, unsigned int *capResult);

    mapsmlReturn_t mapsmlDeviceGetNvLinkErrorCounter(mapsmlDevice_t device, unsigned int link,
                                                     mapsmlNvLinkErrorCounter_t counter, unsigned long long *counterValue);
    mapsmlReturn_t mapsmlDeviceResetNvLinkErrorCounter(mapsmlDevice_t device, unsigned int link);
    // mapsmlReturn_t mapsmlDeviceGetMarginTemperature(mapsmlDevice_t device, unsigned int link);
    // mapsmlReturn_t mapsmlDeviceGetThermalSettings(mapsmlDevice_t device, unsigned int link);
    mapsmlReturn_t mapsmlDeviceGetTotalEnergyConsumption(mapsmlDevice_t device, unsigned long long *energy);
    mapsmlReturn_t mapsmlDeviceGetProcessUtilization(mapsmlDevice_t device, mapsmlProcessUtilizationSample_t *utilization,
                                                     unsigned int *processSamplesCount, unsigned long long lastSeenTimeStamp);

    // mapsmlReturn_t mapsmlDeviceGetMemoryBusWidth(mapsmlDevice_t device, unsigned long long *energy);
    mapsmlReturn_t mapsmlDeviceGetComputeRunningProcesses(mapsmlDevice_t device, unsigned int *infoCount, mapsmlProcessInfo_t *infos);
    mapsmlReturn_t mapsmlSystemGetProcessName(unsigned int pid, char* name, unsigned int length);
    mapsmlReturn_t mapsmlDeviceGetMemoryErrorCounter(mapsmlDevice_t device, mapsmlMemoryErrorType_t errorType,
                                                     mapsmlEccCounterType_t counterType,
                                                     mapsmlMemoryLocation_t locationType, unsigned long long *count);
    mapsmlReturn_t mapsmlDeviceGetSupportEventTypes(mapsmlDevice_t device, unsigned long long* eventTypes);
    mapsmlReturn_t mapsmlDeviceRegisterEvents(mapsmlDevice_t device, unsigned long long eventTypes, mapsmlEventSet_t set);
    mapsmlReturn_t mapsmlEventSetCreate(mapsmlEventSet_t* set);
    mapsmlReturn_t mapsmlEventSetFree(mapsmlEventSet_t set);
    mapsmlReturn_t mapsmlEventSetWait_v2(mapsmlEventSet_t set, mapsmlEventData_t* data, unsigned int timeoutms);

    const char *mapsmlErrorString(mapsmlReturn_t result);

#ifdef __cplusplus
}
#endif

#endif