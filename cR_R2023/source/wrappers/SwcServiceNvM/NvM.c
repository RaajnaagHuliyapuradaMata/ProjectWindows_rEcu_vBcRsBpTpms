

#define NVM_SOURCE

#include "Std_Types.h"

#include "NvM.h"

#include "NvM_PrivateCfg.h"

#include "NvM_JobProc.h"

#include "NvM_Act.h"
#include "NvM_Qry.h"
#include "NvM_Queue.h"
#include "NvM_Crc.h"

#include "NvM_Cbk.h"

#if ((NVM_SW_MAJOR_VERSION != (5u)) \
        || (NVM_SW_MINOR_VERSION != (7u)))
# error "Version numbers of NvM.c and NvM.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM.c and NvM_Cfg.h are inconsistent!"
#endif

#if ((NVM_PRIV_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_PRIV_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM.c and NvM_PrivateCfg.h are inconsistent!"
#endif

#if ((NVM_TYPES_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
        || (NVM_TYPES_MINOR_VERSION != NVM_SW_MINOR_VERSION))
# error "Version numbers of NvM.c and NvM_Types.h are inconsistent!"
#endif

#if ((NVM_ACT_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
        || (NVM_ACT_MINOR_VERSION != NVM_SW_MINOR_VERSION))
# error "Version numbers of NvM.c and NvM_Act.h are inconsistent!"
#endif

#if ((NVM_QRY_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
        || (NVM_QRY_MINOR_VERSION != NVM_SW_MINOR_VERSION))
# error "Version numbers of NvM.c and NvM_Qry.h are inconsistent!"
#endif

#if ((NVM_JOBPROC_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
        || (NVM_JOBPROC_MINOR_VERSION != NVM_SW_MINOR_VERSION))
# error "Version numbers of NvM.c and NvM_JobProc.h are inconsistent!"
#endif

#if ((NVM_CRC_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
        || (NVM_CRC_MINOR_VERSION != NVM_SW_MINOR_VERSION))
# error "Version numbers of NvM.c and NvM_Crc.h are inconsistent!"
#endif

#if ((NVM_QUEUE_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
        || (NVM_QUEUE_MINOR_VERSION != NVM_SW_MINOR_VERSION))
# error "Version numbers of NvM.c and NvM_Queue.h are inconsistent!"
#endif

#ifndef NVM_LOCAL
# define NVM_LOCAL static
#endif

#ifndef NVM_LOCAL_INLINE
# define NVM_LOCAL_INLINE LOCAL_INLINE
#endif

typedef P2CONST(NvM_RamMngmtAreaType, AUTOMATIC, NVM_CONFIG_DATA) NvM_RamMngmtConstPtrType;

#define NVM_START_SEC_VAR_FAST_8
#include "MemMap.h"

VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8;

#define NVM_STOP_SEC_VAR_FAST_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
NVM_LOCAL VAR(struct NvM_CrcJobStruct, NVM_PRIVATE_DATA) NvM_AsyncCrcJob_t;
#endif

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

NVM_LOCAL_INLINE boolean NvM_WriteProtectionChecks(const NvM_RamMngmtConstPtrType mngmtPtr);
#endif

NVM_LOCAL_INLINE boolean NvM_CheckBlockType(const NvM_BlockIdType BlockId);

# if ((NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON))

NVM_LOCAL_INLINE boolean NvM_CheckAddress(const NvM_BlockIdType BlockId, const void * RamPtr);
#endif

# if ((NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_KILL_WRITEALL_API == STD_ON))

NVM_LOCAL_INLINE boolean NvM_CheckBlockId(const NvM_BlockIdType BlockId);
# endif

#if(NVM_DEV_ERROR_DETECT == STD_ON)

NVM_LOCAL_INLINE boolean NvM_CheckCurrDataIndex(const NvM_BlockIdType BlockId);

NVM_LOCAL_INLINE boolean NvM_CheckDataIndex(const NvM_BlockIdType BlockId, const uint8 DataIndex);

NVM_LOCAL_INLINE boolean NvM_CheckNotNull(const uint8 * Ptr);

NVM_LOCAL_INLINE boolean NvM_CheckInitialized(void);

NVM_LOCAL_INLINE boolean NvM_CheckMultiBlockPending(void);
#endif

NVM_LOCAL_INLINE boolean NvM_CheckBlockPending(const NvM_BlockIdType blockId);

NVM_LOCAL_INLINE NvM_RamMngmtPtrType NvM_GetMngmtAreaPtr(const NvM_BlockIdType blockId);

FUNC(void, NVM_PUBLIC_CODE) NvM_Init(void)
{

    uint16_least NvM_BlockCount_u16loc;

#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)

    NvM_QueueInit();
#endif

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
    NvM_CrcQueueInit();

    NvM_CrcJob_Create(&NvM_AsyncCrcJob_t, (NvM_BlockIdType)0, NULL_PTR);
#endif

    NvM_ApiFlags_u8 = 0;

    NvM_BlockMngmtArea_at[0u].NvRamErrorStatus_u8 = NVM_REQ_OK;

    NvM_BlockCount_u16loc = NvM_NoOfBlockIds_t;

    do
    {
        --NvM_BlockCount_u16loc;
        NvM_BlockMngmtArea_at[NvM_BlockCount_u16loc].NvDataIndex_t = 0;
    } while(NvM_BlockCount_u16loc > 0);

    NvM_DcmBlockMngmt_t.NvDataIndex_t = 0;
    NvM_DcmBlockMngmt_t.NvRamAttributes_u8 = 0u;
    NvM_DcmBlockMngmt_t.NvRamErrorStatus_u8 = 0u;

    NvM_JobProcInit();
}

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetDataIndex(NvM_BlockIdType BlockId, uint8 DataIndex)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if(NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else if (NvM_CheckDataIndex(BlockId, DataIndex) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else
#endif
    {
        if(NvM_CheckBlockType(BlockId) == TRUE)
        {
            const NvM_RamMngmtPtrType NvM_RamMngt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

            NvM_RamMngt_ptloc->NvDataIndex_t = DataIndex;

            returnValue = E_OK;
        }
        else
        {
#if (NVM_DEV_ERROR_REPORT == STD_ON)
            detErrorId = NVM_E_PARAM_BLOCK_TYPE;
#endif
        }
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_SET_DATA_INDEX, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif

    return returnValue;
}

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetDataIndex(NvM_BlockIdType BlockId, P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)

    if(NvM_CheckNotNull(DataIndexPtr) == FALSE)
    {
        detErrorId = NVM_E_PARAM_DATA;
    }
    else if(NvM_CheckInitialized() == FALSE)
    {
        *DataIndexPtr = 0;

        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if(NvM_CheckBlockId(BlockId) == FALSE)
    {
        *DataIndexPtr = 0;

        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else
#endif
    {
        if(NvM_CheckBlockType(BlockId) == TRUE)
        {
            const NvM_RamMngmtPtrType NvM_RamMngt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

            *DataIndexPtr = NvM_RamMngt_ptloc->NvDataIndex_t;

            returnValue = E_OK;
        }
        else
        {
            *DataIndexPtr = 0;

#if (NVM_DEV_ERROR_REPORT == STD_ON)
            detErrorId = NVM_E_PARAM_BLOCK_TYPE;
#endif
        }
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_GET_DATA_INDEX, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif

    return returnValue;
}

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetBlockProtection(NvM_BlockIdType BlockId, boolean ProtectionEnabled)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {
        const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

        if((NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) == 0)
        {
            NvM_EnterCriticalSection();

            if (ProtectionEnabled)
            {
                NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= NVM_WR_PROT_SET;
            }
            else
            {
                NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= NVM_WR_PROT_CL;
            }

            NvM_ExitCriticalSection();

            returnValue = E_OK;
        }
        else
        {
# if (NVM_DEV_ERROR_REPORT == STD_ON)
            detErrorId = NVM_E_BLOCK_CONFIG;
# endif
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_SET_BLOCK_PROTECTION, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}
#endif

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetErrorStatus(NvM_BlockIdType BlockId,
    P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

#if(NVM_DEV_ERROR_DETECT == STD_ON)
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }

    else if (NVM_BLOCK_FROM_DCM_ID(BlockId) >= NvM_NoOfBlockIds_t)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckNotNull(RequestResultPtr) == FALSE)
    {
        detErrorId = NVM_E_PARAM_DATA;
    }
    else
#endif
    {
        if(NvM_CheckBlockPending(BlockId) == TRUE)
        {
            *RequestResultPtr = NVM_REQ_PENDING;
        }
        else
        {
            const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

            *RequestResultPtr = NvM_RamMngmt_ptloc->NvRamErrorStatus_u8;
        }

        returnValue = E_OK;
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_GET_ERROR_STATUS, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif

    return returnValue;
}

#if (NVM_VERSION_INFO_API == STD_ON)

FUNC(void, NVM_PUBLIC_CODE) NvM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) Versioninfo)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if (Versioninfo == NULL_PTR)
    {
        detErrorId = NVM_E_PARAM_DATA;
    }
    else
# endif
    {

        Versioninfo->vendorID         = NVM_VENDOR_ID;
        Versioninfo->moduleID         = NVM_MODULE_ID;
        Versioninfo->sw_major_version = NVM_SW_MAJOR_VERSION;
        Versioninfo->sw_minor_version = NVM_SW_MINOR_VERSION;
        Versioninfo->sw_patch_version = NVM_SW_PATCH_VERSION;
    }

# if(NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_GET_VERSION_INFO, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif
}
#endif

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType BlockId, boolean BlockChanged)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {

        if(NvM_CheckAddress(BlockId, NULL_PTR) == TRUE)
        {
            const NvM_RamMngmtPtrType blockMngmtPtr = NvM_GetMngmtAreaPtr(BlockId);

            NvM_EnterCriticalSection();

            if (BlockChanged)
            {
                blockMngmtPtr->NvRamAttributes_u8 |= (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET);

                blockMngmtPtr->NvRamAttributes_u8 &= NVM_NVRAM_UPTODATE_CL;

                NvM_ExitCriticalSection();

# if (NVM_CALC_RAM_CRC_USED == STD_ON)

                if ((NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].Flags_u8 &
                    (NvM_BitFieldType)NVM_CALC_RAM_BLOCK_CRC_ON) != 0)
                {
                    NvM_CrcQueueJob(NVM_BLOCK_FROM_DCM_ID(BlockId));
                }
# endif
            }
            else
            {
                blockMngmtPtr->NvRamAttributes_u8 &= (NVM_STATE_CHANGED_CL & NVM_STATE_VALID_CL);

                NvM_ExitCriticalSection();
            }

            returnValue = E_OK;
        }
        else
        {
# if (NVM_DEV_ERROR_REPORT == STD_ON)
            detErrorId = NVM_E_PARAM_BLOCK_TYPE;
#  endif
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_SET_RAM_BLOCK_STATUS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}
#endif

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_ReadBlock(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_CheckAddress(BlockId, NvM_DstPtr) == FALSE)
    {
        detErrorId = NVM_E_PARAM_ADDRESS;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {

        if (NvM_QueueJob(BlockId, NVM_INT_FID_READ_BLOCK, (NvM_RamAddressType)NvM_DstPtr))
        {
            if(NvM_DstPtr == NULL_PTR)
            {
                const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

                NvM_EnterCriticalSection();

                NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_VALID_CL & NVM_STATE_CHANGED_CL);

                NvM_ExitCriticalSection();
            }

            returnValue = E_OK;
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_READ_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock(NvM_BlockIdType BlockId, P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_CheckAddress(BlockId, NvM_SrcPtr) == FALSE)
    {
        detErrorId = NVM_E_PARAM_ADDRESS;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {
        const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

        if(NvM_WriteProtectionChecks(NvM_RamMngmt_ptloc) == TRUE)
        {

            if (NvM_QueueJob(BlockId, NVM_INT_FID_WRITE_BLOCK, (NvM_RamAddressType)NvM_SrcPtr))
            {
                if(NvM_SrcPtr == NULL_PTR)
                {
                    NvM_EnterCriticalSection();

                    NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET);

                    NvM_ExitCriticalSection();
                }

                returnValue = E_OK;
            }
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_WRITE_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_RestoreBlockDefaults(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_CheckAddress(BlockId, NvM_DstPtr) == FALSE)
    {
        detErrorId = NVM_E_PARAM_ADDRESS;
    }
    else if ((NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].RomBlockDataAddr_pt == NULL_PTR) &&
        (NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].InitCallback_pt == NULL_PTR))
    {
        detErrorId = NVM_E_BLOCK_CONFIG;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {

        if (NvM_QueueJob(BlockId, NVM_INT_FID_RESTORE_DEFAULTS, (NvM_RamAddressType)NvM_DstPtr))
        {
            if(NvM_DstPtr == NULL_PTR)
            {
                const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

                NvM_EnterCriticalSection();

                NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_VALID_CL & NVM_STATE_CHANGED_CL);

                NvM_ExitCriticalSection();
            }

            returnValue = E_OK;
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_RESTORE_BLOCK_DEFAULTS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}
#endif

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_EraseNvBlock(NvM_BlockIdType BlockId)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if (NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].BlockPrio_u8 != 0)
    {
        detErrorId = NVM_E_BLOCK_CONFIG;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {
        const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

        if(NvM_WriteProtectionChecks(NvM_RamMngmt_ptloc) == TRUE)
        {

            returnValue = NvM_QueueJob(BlockId, NVM_INT_FID_ERASE_BLOCK, NULL_PTR) ? E_OK : E_NOT_OK;
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_ERASE_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_InvalidateNvBlock(NvM_BlockIdType BlockId)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if(NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else if(NvM_CheckBlockPending(BlockId) == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
# endif
    {
        const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = NvM_GetMngmtAreaPtr(BlockId);

        if(NvM_WriteProtectionChecks(NvM_RamMngmt_ptloc) == TRUE)
        {

            returnValue = NvM_QueueJob(BlockId, NVM_INT_FID_INVALIDATE_NV_BLOCK, NULL_PTR) ? E_OK : E_NOT_OK;
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_INVALIDATE_NV_BLOCK, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}
#endif

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_CancelJobs(NvM_BlockIdType BlockId)
{
    Std_ReturnType returnValue = E_NOT_OK;
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else
# endif
    {
        returnValue = (NvM_UnQueueJob(BlockId) == TRUE) ? E_OK : E_NOT_OK;
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_CANCEL_JOBS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif

    return returnValue;
}
#endif

FUNC(void, NVM_PUBLIC_CODE) NvM_ReadAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckMultiBlockPending() == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
#endif
    {
        NvM_EnterCriticalSection();

        NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = NVM_REQ_PENDING;

        NvM_ApiFlags_u8 |= NVM_APIFLAG_READ_ALL_SET;

        NvM_ExitCriticalSection();

        NvM_MultiBlockCbk(NVM_READ_ALL, NVM_REQ_PENDING);
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_READ_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif
}

FUNC(void, NVM_PUBLIC_CODE) NvM_WriteAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckMultiBlockPending() == TRUE)
    {
        detErrorId = NVM_E_BLOCK_PENDING;
    }
    else
#endif
    {
        NvM_EnterCriticalSection();

        NvM_BlockMngmtArea_at[0u].NvRamErrorStatus_u8 = NVM_REQ_PENDING;

        NvM_ApiFlags_u8 &= (NVM_APIFLAG_KILL_WR_ALL_CL & NVM_APIFLAG_CANCEL_WR_ALL_CL);
        NvM_ApiFlags_u8 |= NVM_APIFLAG_WRITE_ALL_SET;

        NvM_ExitCriticalSection();

        NvM_MultiBlockCbk(NVM_WRITE_ALL, NVM_REQ_PENDING);
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_WRITE_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif
}

FUNC(void, NVM_PUBLIC_CODE) NvM_CancelWriteAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
#endif
    {
        NvM_EnterCriticalSection();

        NvM_ApiFlags_u8 |= NVM_APIFLAG_CANCEL_WR_ALL_SET;

        NvM_ExitCriticalSection();
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_CANCEL_WRITE_ALL, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif
}

#if (NVM_KILL_WRITEALL_API == STD_ON)

FUNC(void, NVM_PUBLIC_CODE) NvM_KillWriteAll(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
# endif
    {

        NvM_BlockIdType blockEndNotificationId = 0;
        boolean writeAllEndNotification = FALSE;

        NvM_EnterCriticalSection();

        if((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) != 0)
        {

            NvM_ApiFlags_u8 &= NVM_APIFLAG_WRITE_ALL_CL;
            NvM_ApiFlags_u8 |= NVM_APIFLAG_KILL_WR_ALL_SET | NVM_APIFLAG_CANCEL_WR_ALL_SET;

            if((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) && (NvM_CheckBlockId(NvM_CurrentJob_t.JobBlockId_t)))
            {
                const NvM_RamMngmtPtrType mngmt_pt = NvM_CurrentBlockInfo_t.Mngmt_pt;
                blockEndNotificationId = NvM_CurrentJob_t.JobBlockId_t;

                mngmt_pt->NvRamErrorStatus_u8 =
                    ((mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) != 0) ? NVM_REQ_OK : NVM_REQ_BLOCK_SKIPPED;
            }

            NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = NVM_REQ_CANCELED;

            writeAllEndNotification = TRUE;
        }

        NvM_ExitCriticalSection();

        if(blockEndNotificationId > 0)
        {
            NvM_BlockNotification(blockEndNotificationId, NVM_WRITE_ALL, NVM_REQ_CANCELED);
        }

        if(writeAllEndNotification == TRUE)
        {
            NvM_MultiBlockCbk(NVM_WRITE_ALL, NVM_REQ_CANCELED);
        }
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_KILL_WRITE_ALL, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif
}
#endif

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

FUNC(void, NVM_PUBLIC_CODE) NvM_RepairRedundantBlocks(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

# if (NVM_DEV_ERROR_DETECT == STD_ON)
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
# endif
    {
        NvM_EnterCriticalSection();

        NvM_ApiFlags_u8 |= NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET;

        NvM_ExitCriticalSection();
    }

# if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_REPAIR_REDUNDANT_BLOCKS, detErrorId);
    }
# else
    NVM_DUMMY_STATEMENT(detErrorId);
# endif
}
#endif

FUNC(void, NVM_PUBLIC_CODE) NvM_MainFunction(void)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    if (NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else
#endif
    {

        NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_WAIT_CL;

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
        if(!NvM_CrcJob_isBusy(&NvM_AsyncCrcJob_t))
        {
            const NvM_BlockIdType newCrcBlockId = NvM_CrcGetQueuedBlockId();
            const NvM_BlockDescrPtrType descr_pt = &NvM_BlockDescriptorTable_at[newCrcBlockId];

            NvM_CrcJob_CopyToBuffer(&NvM_AsyncCrcJob_t);

            NvM_CrcJob_Create(&NvM_AsyncCrcJob_t, newCrcBlockId, descr_pt->RamBlockDataAddr_t);

# if (NVM_CRC_INT_BUFFER == STD_ON)
            NvM_CrcJob_ReassignBuffer(&NvM_AsyncCrcJob_t, descr_pt->RamBlockCrcAddr_t);
# endif
        }

        NvM_CrcJob_Process(&NvM_AsyncCrcJob_t, NvM_NoOfCrcBytes_u16);
#endif

        do
        {
            NvM_TaskState_t = NvM_Fsm(NvM_TaskState_t);

            NvM_JobMainState_t = NvM_Fsm(NvM_JobMainState_t);

            NvM_JobSubState_t = NvM_Fsm(NvM_JobSubState_t);
        }
        while ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_WAIT_SET) == 0);
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_MAINFUNCTION, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif
}

#if (NVM_POLLING_MODE == STD_OFF)

FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void)
{
     NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
}

FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void)
{

    switch(MemIf_GetJobResult((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8))
    {

        case MEMIF_BLOCK_INCONSISTENT:
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
            break;

        case MEMIF_BLOCK_INVALID:
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NV_INVALIDATED;
            break;

        default:
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}
#endif

FUNC(void, NVM_PUBLIC_CODE) NvM_SetBlockLockStatus(NvM_BlockIdType BlockId, boolean BlockLocked)
{
    uint8 detErrorId = NVM_E_NO_ERROR;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    if(NvM_CheckInitialized() == FALSE)
    {
        detErrorId = NVM_E_NOT_INITIALIZED;
    }
    else if (NvM_CheckBlockId(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_ID;
    }
    else if (NvM_CheckCurrDataIndex(BlockId) == FALSE)
    {
        detErrorId = NVM_E_PARAM_BLOCK_DATA_IDX;
    }
    else
#endif
    {
        NvM_EnterCriticalSection();

        if (BlockLocked)
        {
            NvM_BlockMngmtArea_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvRamAttributes_u8 |= NVM_LOCK_STAT_SET;
        }
        else
        {
            NvM_BlockMngmtArea_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvRamAttributes_u8 &= NVM_LOCK_STAT_CL;
        }

        NvM_ExitCriticalSection();
    }

#if (NVM_DEV_ERROR_REPORT == STD_ON)
    if(detErrorId != NVM_E_NO_ERROR)
    {
        NvM_Errorhook(NVM_SET_BLOCK_LOCK_STATUS, detErrorId);
    }
#else
    NVM_DUMMY_STATEMENT(detErrorId);
#endif
}

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

NVM_LOCAL_INLINE boolean NvM_WriteProtectionChecks(const NvM_RamMngmtConstPtrType mngmtPtr)
{
    boolean returnValue = FALSE;

    if ((mngmtPtr->NvRamAttributes_u8 & NVM_WR_PROT_SET) != 0)
    {
    	NvM_DemReportErrorWriteProtected();
    }

    else if (mngmtPtr != &NvM_DcmBlockMngmt_t)
    {
        returnValue = (boolean)((mngmtPtr->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) == 0);
    }

    else
    {
        returnValue = TRUE;
    }

    return returnValue;
}
#endif

NVM_LOCAL_INLINE boolean NvM_CheckBlockType(const NvM_BlockIdType BlockId)
{

    return (boolean)((NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].MngmtType_t & NVM_BLOCK_DATASET) != 0);
}

# if ((NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON))

NVM_LOCAL_INLINE boolean NvM_CheckAddress(const NvM_BlockIdType BlockId, const void * RamPtr)
{
    NvM_BlockDescrPtrType descPtr = &NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)];
    boolean returnValue = TRUE;

    if(RamPtr == NULL_PTR)
    {
        returnValue = (boolean)((NVM_BLOCK_FROM_DCM_ID(BlockId) == BlockId) &&
            ((descPtr->RamBlockDataAddr_t != NULL_PTR) || (descPtr->CbkGetMirrorFunc_pt != NULL_PTR)));
    }

    return returnValue;
}
#endif

# if (NVM_DEV_ERROR_DETECT == STD_ON) || (NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL_INLINE boolean NvM_CheckBlockId(const NvM_BlockIdType BlockId)
{
    return (boolean)((NVM_BLOCK_FROM_DCM_ID(BlockId) > 0) && (NVM_BLOCK_FROM_DCM_ID(BlockId) < NvM_NoOfBlockIds_t));
}
# endif

#if (NVM_DEV_ERROR_DETECT == STD_ON)

NVM_LOCAL_INLINE boolean NvM_CheckCurrDataIndex(const NvM_BlockIdType BlockId)
{
    return (boolean)(NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvBlockCount_u8 >=
        NvM_BlockMngmtArea_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvDataIndex_t);
}

NVM_LOCAL_INLINE boolean NvM_CheckDataIndex(const NvM_BlockIdType BlockId, const uint8 DataIndex)
{
    return (boolean)(NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].NvBlockCount_u8 >= DataIndex);
}

NVM_LOCAL_INLINE boolean NvM_CheckNotNull(const uint8 * Ptr)
{
    return (boolean)(Ptr != NULL_PTR);
}

NVM_LOCAL_INLINE boolean NvM_CheckInitialized(void)
{
    return (boolean)(NvM_TaskState_t != NVM_STATE_UNINIT);
}

NVM_LOCAL_INLINE boolean NvM_CheckMultiBlockPending(void)
{
    return (boolean)(NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 == NVM_REQ_PENDING);
}
#endif

NVM_LOCAL_INLINE boolean NvM_CheckBlockPending(const NvM_BlockIdType blockId)
{
    boolean blockPending = FALSE;

    if((blockId > 0x0) && ((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) || (NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_READ_ALL)))
    {

        if((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) == NVM_APIFLAG_WRITE_ALL_SET)
        {

            blockPending = (boolean)(blockId < NvM_CurrentJob_t.JobBlockId_t);
        }

        else
        {

            blockPending = (boolean)(blockId > NvM_CurrentJob_t.JobBlockId_t);
        }
    }

    else
    {

        blockPending = (boolean)(NvM_GetMngmtAreaPtr(blockId)->NvRamErrorStatus_u8 == NVM_REQ_PENDING);
    }

    return blockPending;
}

NVM_LOCAL_INLINE NvM_RamMngmtPtrType NvM_GetMngmtAreaPtr(const NvM_BlockIdType blockId)
{
    return (blockId == NVM_BLOCK_FROM_DCM_ID(blockId)) ? (&NvM_BlockMngmtArea_at[blockId]) : (&NvM_DcmBlockMngmt_t);
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

