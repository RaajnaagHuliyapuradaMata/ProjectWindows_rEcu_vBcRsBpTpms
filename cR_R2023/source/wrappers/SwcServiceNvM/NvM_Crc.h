

#if (!defined NVM_CRC_H_)
# define NVM_CRC_H_

# define NVM_CRC_MAJOR_VERSION    (5u)
# define NVM_CRC_MINOR_VERSION    (7u)
# define NVM_CRC_PATCH_VERSION    (0u)

# if(NVM_CRC_INT_BUFFER == STD_ON)
#  define NVM_CRC_BUFFER_PTR_CLASS NVM_PRIVATE_DATA
# else
#  define NVM_CRC_BUFFER_PTR_CLASS NVM_APPL_DATA
# endif

# define NvM_CrcJob_GetCrcLength(selfPtr)                    ((selfPtr)->HandlerInstance_pt->crcLength)
# define NvM_CrcJob_isBusy(selfPtr)                          ((selfPtr)->RemainingLength_u16 != 0)
# define NvM_CrcJob_ReassignBuffer(selfPtr, crcPtr)          ((selfPtr)->CrcBuffer = (crcPtr))

# if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))

#  define NVM_CRC_QUEUE_ENTRY_BITS     32u
#  define NVM_CRC_QUEUE_BITINDEX_MASK  0x1Fu
#  define NVM_CRC_QUEUE_ENTRY_SHIFT    5
#  define NVM_CRC_QUEUE_ENTRY_MASK     0xFFFFFFFFu

# endif

typedef P2VAR(uint8, AUTOMATIC, NVM_CRC_BUFFER_PTR_CLASS) NvM_CrcBufferPtrType;
typedef P2CONST(uint8, AUTOMATIC, NVM_CRC_BUFFER_PTR_CLASS) NvM_CrcBufferConstPtrType;

typedef P2VAR(uint32, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcValuePtrType;
typedef P2CONST(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcValueRefType;

typedef P2FUNC(void, NVM_PRIVATE_CODE, NvM_CrcCalculateFPtr) (NvM_ConstRamAddressType, uint16, NvM_CrcValuePtrType);
typedef P2FUNC(boolean, NVM_PRIVATE_CODE, NvM_CrcCompareFPtr) (NvM_CrcBufferConstPtrType, NvM_CrcValueRefType);
typedef P2FUNC(void, NVM_PRIVATE_CODE, NvM_CrcCopyToBufferFPtr) (NvM_CrcBufferPtrType, NvM_CrcValueRefType);

struct NvM_CrcHandlerClass
{
    NvM_CrcCalculateFPtr    calc;
    NvM_CrcCompareFPtr      compare;
    NvM_CrcCopyToBufferFPtr copyToBuffer;
    uint32                  initialCrcValue;
    uint8                   crcLength;
};

typedef P2CONST(struct NvM_CrcHandlerClass, AUTOMATIC, NVM_PRIVATE_CONST) NvM_CrcHandlerClassConstPtr;

typedef struct NvM_CrcJobStruct
{
    uint32                      CurrentCrcValue;
    NvM_ConstRamAddressType     RamData_pt;
    NvM_CrcBufferPtrType        CrcBuffer;
    NvM_CrcHandlerClassConstPtr HandlerInstance_pt;
    uint16                      RemainingLength_u16;
} NvM_CrcJobType;

typedef P2VAR(NvM_CrcJobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcJobPtrType;
typedef P2CONST(NvM_CrcJobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcJobConstPtrType;

# define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"

# if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))

typedef uint32 NvM_CrcQueueEntryType;
typedef P2VAR(NvM_CrcQueueEntryType, AUTOMATIC, NVM_CONFIG_DATA) NvM_CrcQueueEntryPtr;

extern VAR(NvM_CrcQueueEntryType, NVM_CONFIG_DATA) NvM_CrcQueue_at[];

# endif

# define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"

# define NVM_START_SEC_CODE
# include "MemMap.h"

# if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueInit(void);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueJob(NvM_BlockIdType);

extern FUNC(NvM_BlockIdType, NVM_PRIVATE_CODE) NvM_CrcGetQueuedBlockId(void);
# endif

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Create(NvM_CrcJobPtrType, NvM_BlockIdType, NvM_RamAddressType);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Process(NvM_CrcJobPtrType, uint16);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_CopyToBuffer(NvM_CrcJobConstPtrType);

extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_CrcJob_Compare(NvM_CrcJobConstPtrType);

# if (NVM_CRC_INT_BUFFER == STD_ON)

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ExportBufferedValue(NvM_CrcJobConstPtrType, NvM_CrcBufferPtrType);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ImportBufferedValue(NvM_CrcJobConstPtrType, NvM_CrcBufferConstPtrType);
# endif

# define NVM_STOP_SEC_CODE
# include "MemMap.h"

#endif

