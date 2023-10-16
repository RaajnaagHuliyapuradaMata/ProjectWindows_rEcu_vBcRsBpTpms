#ifndef NVM_CFG_H_PRIVATE
#define NVM_CFG_H_PRIVATE

#define NVM_PRIV_CFG_MAJOR_VERSION    (5u)
#define NVM_PRIV_CFG_MINOR_VERSION    (7u)
#define NVM_PRIV_CFG_PATCH_VERSION    (0u)

#define NvM_DemReportErrorReqFailed()
#define NvM_DemReportErrorIntegrityFailed()
#define NvM_DemReportErrorLossOfRedundancy()
#define NvM_DemReportErrorQueueOverflow()
#define NvM_DemReportErrorWriteProtected()

#define NVM_BLOCK_FROM_DCM_ID(blockId)   ((NvM_BlockIdType)((blockId) & ((NVM_DCM_BLOCK_OFFSET) ^ 0xFFFFu)))

#if(!defined NVM_CFG_SOURCE)

#define NVM_DEV_ERROR_REPORT (STD_OFF)

# if(NVM_DEV_ERROR_REPORT == STD_ON)

#  include "Det.hpp"

#  define NvM_Errorhook(ServiceId, ErrorCode) ((void)Det_ReportError((NVM_MODULE_ID), (0u), (ServiceId), (ErrorCode)))

# endif

#define NVM_INTFLAG_WAIT_SET           (0x01u)
#define NVM_INTFLAG_WAIT_CL            (0xFEu)
#define NVM_INTFLAG_ERROR_SET          (0x10u)
#define NVM_INTFLAG_ERROR_CL           (0xEFu)
#define NVM_INTFLAG_DYN_MISMATCH_SET   (0x20u)
#define NVM_INTFLAG_DYN_MISMATCH_CL    (0xDFu)

#define NVM_APIFLAG_WRITE_ALL_SET               (0x02u)
#define NVM_APIFLAG_WRITE_ALL_CL                (0xFDu)
#define NVM_APIFLAG_READ_ALL_SET                (0x04u)
#define NVM_APIFLAG_READ_ALL_CL                 (0xFBu)
#define NVM_APIFLAG_CANCEL_WR_ALL_SET           (0x40u)
#define NVM_APIFLAG_CANCEL_WR_ALL_CL            (0xBFu)
#define NVM_APIFLAG_KILL_WR_ALL_SET             (0x80u)
#define NVM_APIFLAG_KILL_WR_ALL_CL              (0x7Fu)
#define NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET (0x08u)
#define NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_CL  (0xF7u)

#define NvM_SetIntFlag(FlagParam)   (NvM_IntFlags_u8 |= (FlagParam))

#define NvM_ClearIntFlag(FlagParam) (NvM_IntFlags_u8 &= (FlagParam))

#define NvM_PollIntFlag(FlagParam)  ((FlagParam) == (NvM_IntFlags_u8 & (FlagParam)))

#endif

#include "MemIf.hpp"

#define NVM_BLOCK_TYPE_ROM          (NVM_BLOCK_NATIVE_ROM)

typedef unsigned int NvM_BitFieldType;

#define NVM_BLOCK_NATIVE        0x00u
#define NVM_BLOCK_REDUNDANT     0x01u
#define NVM_BLOCK_DATASET       0x02u

typedef struct{
   uint8                   NvDataIndex_t;
    NvM_RequestResultType   NvRamErrorStatus_u8;
   uint8                   NvRamAttributes_u8;
}NvM_RamMngmtAreaType;

typedef P2VAR(NvM_RamMngmtAreaType, AUTOMATIC, NVM_CONFIG_DATA) NvM_RamMngmtPtrType;
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_AsyncCbkPtrType) (NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_InitCbkPtrType)(void);
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_WriteRamToNvMCbkPtrType)(P2VAR(void, AUTOMATIC, NVM_APPL_DATA));
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_ReadRamFromNvMCbkPtrType)(P2CONST(void, AUTOMATIC, NVM_APPL_DATA));
typedef P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_RamAddressType;
typedef P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_ConstRamAddressType;
typedef P2CONST(uint8, AUTOMATIC, NVM_APPL_CONST)NvM_RomAddressType;

#define NVM_CALC_RAM_CRC_USED STD_OFF

typedef P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvM_RamCrcAddressType;

#define NVM_BLOCK_USE_CRC_OFF                (0u)
#define NVM_BLOCK_CRC_8_ON                   (1u)
#define NVM_BLOCK_CRC_16_ON                  (2u)
#define NVM_BLOCK_CRC_32_ON                  (3u)
#define NVM_BLOCK_CRC_MASK                   (0x03)
#define NVM_CALC_RAM_BLOCK_CRC_ON            (1u)
#define NVM_CALC_RAM_BLOCK_CRC_OFF           (0u)
#define NVM_BLOCK_WRITE_PROT_ON              (2u)
#define NVM_BLOCK_WRITE_PROT_OFF             (0u)
#define NVM_BLOCK_WRITE_BLOCK_ONCE_ON        (4u)
#define NVM_BLOCK_WRITE_BLOCK_ONCE_OFF       (0u)
#define NVM_RESISTANT_TO_CHANGED_SW_ON       (8u)
#define NVM_RESISTANT_TO_CHANGED_SW_OFF      (0u)
#define NVM_SELECT_BLOCK_FOR_READALL_ON      (16u)
#define NVM_SELECT_BLOCK_FOR_READALL_OFF     (0u)
#define NVM_SELECT_BLOCK_FOR_WRITEALL_ON     (32)
#define NVM_SELECT_BLOCK_FOR_WRITEALL_OFF    (0u)
#define NVM_CBK_DURING_READALL_ON            (64)
#define NVM_CBK_DURING_READALL_OFF           (0u)
#define NVM_CRC_COMP_MECHANISM_ON            (128u)
#define NVM_CRC_COMP_MECHANISM_OFF           (0u)

typedef uint32 NvM_GenericRomDefaultsPtrType;

typedef struct{
    NvM_RamAddressType      RamBlockDataAddr_t;
    NvM_RomAddressType      RomBlockDataAddr_pt;
    NvM_InitCbkPtrType      InitCallback_pt;
    NvM_AsyncCbkPtrType     CallbackFunc_pt;
    NvM_ReadRamFromNvMCbkPtrType CbkGetMirrorFunc_pt;
    NvM_WriteRamToNvMCbkPtrType CbkSetMirrorFunc_pt;
    NvM_RamCrcAddressType   RamBlockCrcAddr_t;
   uint16                  NvIdentifier_u16;
   uint16                  NvBlockLength_u16;
    NvM_BitFieldType        NvBlockCount_u8 :8;
    NvM_BitFieldType        BlockPrio_u8    :8;
    NvM_BitFieldType        DeviceId_u8     :4;
    NvM_BitFieldType        MngmtType_t     :2;
    NvM_BitFieldType        CrcSettings     :2;
    NvM_BitFieldType        Flags_u8        :8;
    NvM_BitFieldType        NotifyBswM      :1;
}NvM_BlockDescriptorType;

typedef P2CONST(NvM_BlockDescriptorType, AUTOMATIC, NVM_CONFIG_CONST) NvM_BlockDescrPtrType;

typedef enum{
    NVM_INT_FID_WRITE_BLOCK = 0u
   ,   NVM_INT_FID_READ_BLOCK
   ,   NVM_INT_FID_RESTORE_DEFAULTS
   ,   NVM_INT_FID_INVALIDATE_NV_BLOCK
   ,   NVM_INT_FID_ERASE_BLOCK
   ,   NVM_INT_FID_WRITE_ALL
   ,   NVM_INT_FID_READ_ALL
   ,   NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS
   ,   NVM_INT_FID_NO_JOB_PENDING
}NvM_InternalServiceIdEnumType;

typedef uint8 NvM_InternalServiceIdType;
typedef uint8 NvM_QueueEntryRefType;

typedef struct{
    NvM_RamAddressType          RamAddr_t;
    NvM_BlockIdType             BlockId;
    NvM_InternalServiceIdType   ServiceId;
    NvM_QueueEntryRefType       NextEntry;
    NvM_QueueEntryRefType       PrevEntry;
}NvM_QueueEntryType;

typedef struct{
   uint8 MaxIndex;
   uint8 NpSize;
}NvM_QueueSizesType;

#define NVM_STATE_VALID_SET    (0x01u)
#define NVM_STATE_VALID_CL     (0xFEu)
#define NVM_STATE_CHANGED_SET  (0x02u)
#define NVM_STATE_CHANGED_CL   (0xFDu)
#define NVM_NVRAM_UPTODATE_SET (0x04u)
#define NVM_NVRAM_UPTODATE_CL  (0xFBu)
#define NVM_WR_PROT_SET        (0x80u)
#define NVM_WR_PROT_CL         (0x7Fu)
#define NVM_LOCK_STAT_SET      (0x40u)
#define NVM_LOCK_STAT_CL       (0xBFu)
#define NVM_NVBLOCK_STATE_UPTODATE (0x00u)
#define NVM_NVBLOCK_STATE_OUTDATED (0x01u)
#define NVM_NVBLOCK_STATE_DEFECT   (0x02u)
#define NVM_NVBLOCK_STATE_UNKNOWN  (0x03u)
#define NVM_NVBLOCK_STATE_SEC_ACTIVE   (0x80u)
#define NVM_NVBLOCK_STATE_PRI_ACTIVE   (0x7Fu)
#define NVM_PRI_NVBLOCK_STATE_SHIFT (0x5u)
#define NVM_SEC_NVBLOCK_STATE_SHIFT (0x3u)
#define NVM_NVBLOCK_STATE_BIT_MASK (0x3u)
#define NVM_USE_BLOCK_ID_CHECK STD_OFF

extern FUNC(void, NVM_PRIVATE_CODE) NvM_EnterCriticalSection(void);
extern FUNC(void, NVM_PRIVATE_CODE) NvM_ExitCriticalSection(void);
extern FUNC(void, NVM_PRIVATE_CODE) NvM_MultiBlockCbk(NvM_ServiceIdType, NvM_RequestResultType);
extern FUNC(void, NVM_PRIVATE_CODE) NvM_BlockNotification(NvM_BlockIdType, NvM_ServiceIdType, NvM_RequestResultType);
extern VAR(uint8, NVM_PRIVATE_DATA) NvM_InternalBuffer_au8[];
extern VAR(uint8, NVM_PRIVATE_DATA) NvM_TestBuffer_u8;
extern VAR(NvM_QueueEntryType, NVM_PRIVATE_DATA) NvM_JobQueue_at[];
extern CONST(uint8, NVM_PRIVATE_CONST) NvM_NoOfWrAttempts_u8;
extern CONST(uint16, NVM_CONFIG_CONST) NvM_NoOfCrcBytes_u16;
extern CONST(uint16, NVM_PRIVATE_CONST) NvM_CrcQueueSize_u16;

#include "LibAutosar_Crc.hpp"

#define NVM_USE_CRC16 STD_ON
#define NVM_USE_CRC32 STD_OFF
#define NVM_CRC32_XOR_VALUE     0xFFFFFFFFuL
#define NVM_INITIAL_CRC_16_VALUE    0xFFFFFFFFuL
#define NVM_INITIAL_CRC_32_VALUE    (0xFFFFFFFFuL ^ NVM_CRC32_XOR_VALUE)

extern CONST(NvM_QueueSizesType, NVM_PRIVATE_CONST) NvM_QueueSizes_t;
extern CONST(NvM_BlockDescriptorType, NVM_CONFIG_CONST) NvM_BlockDescriptorTable_at[];
extern VAR(NvM_RamMngmtAreaType, NVM_CONFIG_DATA) NvM_BlockMngmtArea_at[];
extern VAR(NvM_RamMngmtAreaType, NVM_CONFIG_DATA) NvM_DcmBlockMngmt_t;

#endif

