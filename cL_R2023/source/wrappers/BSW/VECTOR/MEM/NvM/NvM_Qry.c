

#define NVM_QRY_SOURCE

#include "Std_Types.h"

#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"

#include "NvM_JobProc.h"

#include "NvM_Qry.h"

#include "NvM_Queue.h"

#include "NvM_Crc.h"

#if ((NVM_QRY_MAJOR_VERSION != (5u)) \
        || (NVM_QRY_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Qry.c and NvM_Qry.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Qry.c and NvM_Cfg.h are inconsistent!"
#endif

#ifndef NVM_LOCAL
# define NVM_LOCAL static
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockWriteAll(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void);
#endif

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_ReadAll(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_WriteAll(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void);

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRamValid(void);
#endif

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantBlock(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void);

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void);
#endif

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySuspendRepairRedundantBlocks(void);

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRepairRedBlockDefect(void);
#endif

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCRCCompMechanismSkipWrite(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

CONST(NvM_QryFctPtrType, NVM_PRIVATE_CONST) NvM_QueryTable_ap[NVM_QRY_ID_TRUE + 1] =
{
    NvM_QryBlockWriteAll,
    NvM_QryCancelWriteAll,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NvM_QryWriteAllKilled,
#endif
    NvM_QryCrcBusy,
    NvM_QryCrcMatch,
    NvM_QryLastBlockDone_ReadAll,
    NvM_QryLastBlockDone_WriteAll,
    NvM_QryLastResultOk,
    NvM_QryMainFsmRunning,
    NvM_QryMultiJob,
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    NvM_QryNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
    NvM_QryHighPrioJob,
# endif
#endif
    NvM_QryNvBusy,
    NvM_QryMemHwaBusy,
#if  (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_QryRamValid,
#endif
    NvM_QryRedundantBlock,
    NvM_QrySkipBlock,
    NvM_QrySubFsmRunning,
    NvM_QryWriteBlockOnce,
    NvM_QryWriteRetriesExceeded,
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
    NvM_QryHasRom,
    NvM_QryExtRuntime,
#endif
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NvM_QrySuspendRepairRedundantBlocks,
    NvM_QryRepairRedBlockDefect,
#endif
    NvM_QryCRCCompMechanismSkipWrite,
    NvM_QryTrue
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockWriteAll(void)
{
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    return (boolean)(((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &
               (NVM_WR_PROT_SET | NVM_LOCK_STAT_SET | NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET)) ==
                                              (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET)) &&
            ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_WRITEALL_ON) != 0));
#else
    return (boolean)(((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &
                                                        (NVM_WR_PROT_SET | NVM_LOCK_STAT_SET)) == 0) &&
            ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_WRITEALL_ON) != 0));
#endif
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void)
{
    return (boolean)(NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET);
}

#if (NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void)
{
    return (boolean)((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) &&
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_WR_ALL_SET) != 0));
}
#endif

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void)
{
    return (boolean)NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.ByteCount_u16 > 0) ||
                      NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t));
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_ReadAll(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t >= NvM_NoOfBlockIds_t);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_WriteAll(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t == 0u);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void)
{
    return (boolean)(NVM_REQ_OK == NvM_CurrentBlockInfo_t.LastResult_t);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobMainState_t);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void)
{
    return (boolean)((NvM_ApiFlags_u8 &
        (NVM_APIFLAG_WRITE_ALL_SET | NVM_APIFLAG_READ_ALL_SET
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
        | NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET
#endif
        )) != 0);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void)
{
#if(NVM_POLLING_MODE == STD_ON)
    const uint8 deviceId = (uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8;
    uint8 retVal = FALSE;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING)
    {
        if (MEMIF_BUSY == MemIf_GetStatus(deviceId))
        {
            retVal = TRUE;
        }
        else
        {
            switch(MemIf_GetJobResult(deviceId))
            {
                case MEMIF_JOB_OK:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
                    break;

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
    }
    return retVal;
#else
    return (boolean)(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING);
#endif
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void)
{
    const MemIf_StatusType MemHwaStatus = MemIf_GetStatus(MEMIF_BROADCAST_ID);

    return (boolean)((MemHwaStatus == MEMIF_BUSY) || (MemHwaStatus == MEMIF_BUSY_INTERNAL));
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantBlock(void)
{

    return (boolean)(
        ((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0) &&
        ((NvM_CurrentBlockInfo_t.NvIdentifier_u16 & 0x0001u) == 0));
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void)
{

    return (boolean)(((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_READALL_ON) == 0)
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
        || ((!NvM_QryHasRom()) && (NvM_QryExtRuntime()))
#endif
        );
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobSubState_t);
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void)
{
    return TRUE;
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void)
{

    boolean writeOnce = (boolean)(((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) != 0)
#if(NVM_DYNAMIC_CONFIGURATION == STD_ON)
    && (!NvM_QryExtRuntime())
#endif
    );

    return writeOnce;
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void)
{

    return (boolean)(NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 > NvM_NoOfWrAttempts_u8);
}

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRamValid(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t != NULL_PTR) &&
        ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) != 0)
        && ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) == 0));
}
#endif

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt != NULL_PTR) ||
        (NvM_CurrentBlockInfo_t.Descriptor_pt->InitCallback_pt != NULL_PTR));
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void)
{
    return (boolean)(
        ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_DYN_MISMATCH_SET) != 0) &&

        ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_RESISTANT_TO_CHANGED_SW_ON) == 0));
}
#endif

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySuspendRepairRedundantBlocks(void)
{

    return (
#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
        (NvM_QryNormalPrioJob()) ||
#endif
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_READ_ALL_SET) != 0) ||
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) != 0));
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRepairRedBlockDefect(void)
{

    boolean firstBlockOk = (boolean)((NvM_RepairRedBlockState.NvBlockState & 0x0F) == NVM_NVBLOCK_STATE_UPTODATE);
    boolean secondBlockOk = (boolean)(((NvM_RepairRedBlockState.NvBlockState & 0xF0) >> ((uint8)4)) == NVM_NVBLOCK_STATE_UPTODATE);

    boolean blockDefect = (firstBlockOk ^ secondBlockOk);

    if((firstBlockOk && secondBlockOk) && (NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF))
    {

        blockDefect = (boolean)(NvM_RepairRedBlockState.CrcBuffer != NvM_CurrentBlockInfo_t.BlockCrcJob_t.CurrentCrcValue);

        if(blockDefect)
        {
            NvM_RepairRedBlockState.NvBlockState |= (NVM_NVBLOCK_STATE_DEFECT << 4);
        }
    }

    return blockDefect;
}
#endif

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCRCCompMechanismSkipWrite(void)
{

    boolean skipBlock = FALSE;

    if ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_CRC_COMP_MECHANISM_ON) == NVM_CRC_COMP_MECHANISM_ON)
    {
        skipBlock = ((NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t)) &&
            ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_NVRAM_UPTODATE_SET) == NVM_NVRAM_UPTODATE_SET));
    }

    return skipBlock;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

