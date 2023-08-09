

#define NVM_ACT_SOURCE

#include "Std_Types.h"

#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"

#include "NvM_JobProc.h"

#include "NvM_Act.h"

#include "NvM_Queue.h"

#include "NvM_Crc.h"

#if ((NVM_ACT_MAJOR_VERSION != (5u)) \
        || (NVM_ACT_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Act.c and NvM_Act.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Act.c and NvM_Cfg.h are inconsistent!"
#endif

#define NVM_MAX_DATA_COPY_BYTES (NvM_NoOfCrcBytes_u16 << 2)

#define NVM_EXTRACT_NVSTATE_PRI(NvState)    (((NvState) >> NVM_PRI_NVBLOCK_STATE_SHIFT) & NVM_NVBLOCK_STATE_BIT_MASK)

#define NVM_EXTRACT_NVSTATE_SEC(NvState)    (((NvState) >> NVM_SEC_NVBLOCK_STATE_SHIFT) & NVM_NVBLOCK_STATE_BIT_MASK)

#ifndef NVM_LOCAL
# define NVM_LOCAL static
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetInitialAttr(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitMainFsm(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadAll(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadBlockFsm(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteAll(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlockFsm(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaults(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishMainJob(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillWriteAll(void);
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockReadAll(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockWriteAll(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishCfgIdCheck(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishWriteBlock(void);

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishEraseBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActEraseNvBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInvalidateNvBlock(void);
#endif

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON))

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrc(void);
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWriteNvBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrcRead(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRestoreRomDefaults(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishRestoreRomDefaults(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActTestBlockBlank(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActValidateRam(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupRedundant(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupOther(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActUpdateNvState(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqIntegrityFailed(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqSkipped(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_SetBlockPendingWriteAll(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWait(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActNop(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetMultiBlockJob(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActCopyNvDataToBuf(void);

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInit(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInitNext(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NVM_ActRepairRedBlocksInitBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockReadCheck(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockFinishReadCheck(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksReadValid(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockWriteInvalid(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinishBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinish(void);
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_UpdateConfigIdBlock(void);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyData(NvM_BlockInfoPtrType, NvM_RamAddressType, NvM_ConstRamAddressType);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyBufferedData(NvM_BlockInfoPtrType, NvM_ConstRamAddressType);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntCreateNvState(P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvState, uint8 NewState);

#if(NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_IsWriteAllAndKilled(const NvM_InternalServiceIdType currServiceId, const uint8 currApiFlag);
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntUpdateCurrentBlockNVRAMStatus(const NvM_RequestResultType result);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

CONST(NvM_ActFctPtrType, NVM_PRIVATE_CONST) NvM_ActionTable_ap[NVM_ACT_ID_Nop + 1] =
{
    NvM_ActSetInitialAttr,
    NvM_ActInitMainFsm,
    NvM_ActInitBlock,
    NvM_ActInitReadAll,
    NvM_ActInitReadBlockFsm,
    NvM_ActInitWriteAll,
    NvM_ActInitWriteBlock,
    NvM_ActInitWriteBlockFsm,
    NvM_ActInitRestoreBlockDefaults,
    NvM_ActFinishMainJob,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NvM_ActKillWriteAll,
#endif
    NvM_ActFinishBlock,
    NvM_ActInitNextBlockReadAll,
    NvM_ActInitNextBlockWriteAll,
    NvM_ActFinishCfgIdCheck,
    NvM_ActFinishReadBlock,
    NvM_ActFinishWriteBlock,

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    NvM_ActFinishEraseBlock,
    NvM_ActEraseNvBlock,
    NvM_ActInvalidateNvBlock,
#endif
#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON))
    NvM_ActProcessCrc,
#endif
    NvM_ActWriteNvBlock,
    NvM_ActReadNvBlock,
    NvM_ActProcessCrcRead,
    NvM_ActRestoreRomDefaults,
    NvM_ActFinishRestoreRomDefaults,
    NvM_ActTestBlockBlank,
    NvM_ActValidateRam,
    NvM_ActSetupRedundant,
    NvM_ActSetupOther,
    NvM_ActUpdateNvState,
    NvM_ActSetReqIntegrityFailed,
    NvM_ActSetReqSkipped,
    NvM_SetBlockPendingWriteAll,
    NvM_ActCopyNvDataToBuf,
    NvM_ActGetMultiBlockJob,
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NvM_ActRepairRedBlocksInit,
    NvM_ActRepairRedBlocksInitNext,
    NvM_ActRepairRedBlockReadCheck,
    NvM_ActRepairRedBlockFinishReadCheck,
    NvM_ActRepairRedBlocksReadValid,
    NvM_ActRepairRedBlockWriteInvalid,
    NvM_ActRepairRedBlocksFinishBlock,
    NvM_ActRepairRedBlocksFinish,
#endif
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
    NvM_ActGetNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
        NvM_ActGetHighPrioJob,
        NvM_ActQueueFreeLastJob,
# endif
#endif
    NvM_ActWait,
    NvM_ActNop
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActEraseNvBlock(void)
{
    if (E_OK != MemIf_EraseImmediateBlock((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                          NvM_CurrentBlockInfo_t.NvIdentifier_u16))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishBlock(void)
{
#if(NVM_KILL_WRITEALL_API == STD_ON)

    if(!NvM_IsWriteAllAndKilled(NvM_CurrentJob_t.JobServiceId_t, NvM_ApiFlags_u8))
    {
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NvM_CurrentBlockInfo_t.LastResult_t;
    }

#else
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NvM_CurrentBlockInfo_t.LastResult_t;
#endif

    if((NvM_CurrentJob_t.JobServiceId_t != NVM_INT_FID_WRITE_ALL) || (NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_BLOCK_SKIPPED))
    {
        NvM_BlockNotification(NvM_CurrentJob_t.JobBlockId_t,
                              NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].PublicFid_t,
                              NvM_CurrentBlockInfo_t.LastResult_t);
    }

    NvM_CurrentJob_t.RamAddr_t = NULL_PTR;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockReadAll(void)
{
    NvM_ActFinishBlock();

    NvM_CurrentJob_t.JobBlockId_t++;

    if(NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t)
    {
        NvM_ActInitBlock();

        NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t,
                           NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t);

#if(NVM_CRC_INT_BUFFER == STD_ON)

    NvM_CrcJob_ReassignBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t,
                    NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockCrcAddr_t);
#endif
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockWriteAll(void)
{
    NvM_ActFinishBlock();

    --NvM_CurrentJob_t.JobBlockId_t;

    NvM_ActInitBlock();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishMainJob(void)
{
    const NvM_InternalServiceIdType currSrvId = NvM_CurrentJob_t.JobServiceId_t;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    if(currSrvId < NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS)
#endif
    {
        if((currSrvId == NVM_INT_FID_READ_ALL) || (currSrvId == NVM_INT_FID_WRITE_ALL))
        {
            NvM_RequestResultType JobResult;

            if((currSrvId == NVM_INT_FID_WRITE_ALL) && ((NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET) != 0))
            {
                JobResult = NVM_REQ_CANCELED;
            }
            else if((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_ERROR_SET) != 0)
            {
                JobResult = NVM_REQ_NOT_OK;
            }
            else
            {
                JobResult = NVM_REQ_OK;
            }

            NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = JobResult;

            NvM_MultiBlockCbk(NvM_IntServiceDescrTable_at[currSrvId].PublicFid_t, JobResult);

            NvM_EnterCriticalSection();

            NvM_ApiFlags_u8 &= (NVM_APIFLAG_READ_ALL_CL & NVM_APIFLAG_WRITE_ALL_CL);

            NvM_ExitCriticalSection();

    #if(NVM_DRV_MODE_SWITCH == STD_ON)
            MemIf_SetMode(MEMIF_MODE_SLOW);
    #endif
        }
        else
        {
            NvM_ActFinishBlock();
        }
    }

    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;
}

#if (NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillWriteAll(void)
{
#if(NVM_DRV_MODE_SWITCH == STD_ON)
    MemIf_SetMode(MEMIF_MODE_SLOW);
#endif

    if(MemIf_GetStatus((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8) == MEMIF_BUSY)
    {
        MemIf_Cancel((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8);
    }

    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;

    NvM_JobMainState_t = NvM_JobSubState_t = NVM_STATE_FSM_FINISHED;

    NvM_EnterCriticalSection();

    NvM_ApiFlags_u8 &= (NVM_APIFLAG_CANCEL_WR_ALL_CL & NVM_APIFLAG_KILL_WR_ALL_CL);

    NvM_ExitCriticalSection();
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlock(void)
{
    const NvM_RamMngmtPtrType MngmtPtr = NvM_CurrentBlockInfo_t.Mngmt_pt;
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;

    NvM_ActUpdateNvState();

    if(((descr_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0)    &&
       (NVM_EXTRACT_NVSTATE_PRI(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_OUTDATED) &&
       (NVM_EXTRACT_NVSTATE_SEC(NvM_CurrentBlockInfo_t.NvState_u8) == NVM_NVBLOCK_STATE_OUTDATED))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }

    if((descr_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) != 0)
    {
        if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NV_INVALIDATED)
        {
            MngmtPtr->NvRamAttributes_u8 &= NVM_WR_PROT_CL;
        }
        else
        {
            MngmtPtr->NvRamAttributes_u8 |= NVM_WR_PROT_SET;
        }
    }

    NvM_IntUpdateCurrentBlockNVRAMStatus(NvM_CurrentBlockInfo_t.LastResult_t);

    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;

        if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NOT_OK)
        {
        	NvM_DemReportErrorReqFailed();
        }
        else if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_INTEGRITY_FAILED)
        {
        	NvM_DemReportErrorIntegrityFailed();
        }
        else
        {

        }
    }

#if(NVM_CRC_INT_BUFFER == STD_ON)

    if((NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK) &&
       (NvM_CurrentJob_t.RamAddr_t == NULL_PTR))
    {
        NvM_CrcJob_ExportBufferedValue(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, descr_pt->RamBlockCrcAddr_t);
    }
#endif
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishWriteBlock(void)
{
    const NvM_RamMngmtPtrType MngmtPtr = NvM_CurrentBlockInfo_t.Mngmt_pt;

    if((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0)
    {
        boolean firstBlockDefect = (boolean)(NVM_EXTRACT_NVSTATE_PRI(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE);
        boolean secondBlockDefect = (boolean)(NVM_EXTRACT_NVSTATE_SEC(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE);

        if(firstBlockDefect && secondBlockDefect)
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }

        else
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;

            if(firstBlockDefect ^ secondBlockDefect)
            {
            	NvM_DemReportErrorLossOfRedundancy();
            }
        }

        NvM_IntUpdateCurrentBlockNVRAMStatus((firstBlockDefect || secondBlockDefect) ? NVM_REQ_NOT_OK : NVM_REQ_OK);
    }
    else
    {
        NvM_IntUpdateCurrentBlockNVRAMStatus(NvM_CurrentBlockInfo_t.LastResult_t);
    }

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {

        if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR)
        {
            MngmtPtr->NvRamAttributes_u8 &= NVM_STATE_CHANGED_CL;
        }

        if((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) != 0)
        {
            MngmtPtr->NvRamAttributes_u8 |= NVM_WR_PROT_SET;
        }
    }
    else
    {
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;
        NvM_DemReportErrorReqFailed();
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitBlock(void)
{

    const NvM_BlockIdType orgBlockId = NVM_BLOCK_FROM_DCM_ID(NvM_CurrentJob_t.JobBlockId_t);

    const NvM_BlockDescrPtrType DescrPtr = &NvM_BlockDescriptorTable_at[orgBlockId];

    NvM_CurrentBlockInfo_t.Mngmt_pt =
        ((NvM_CurrentJob_t.JobBlockId_t == orgBlockId) ? (&NvM_BlockMngmtArea_at[orgBlockId]) : (&NvM_DcmBlockMngmt_t));

    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;

    NvM_CurrentBlockInfo_t.Descriptor_pt = DescrPtr;
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 = DescrPtr->NvIdentifier_u16;

    if((DescrPtr->MngmtType_t & NVM_BLOCK_DATASET) != 0)
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= NvM_CurrentBlockInfo_t.Mngmt_pt->NvDataIndex_t;
    }

    NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;

#if(NVM_CRC_INT_BUFFER == STD_ON)

    NvM_CurrentBlockInfo_t.RamAddr_t = NvM_InternalBuffer_au8;

    if(DescrPtr->CrcSettings == NVM_BLOCK_USE_CRC_OFF)
    {
        if(NvM_CurrentJob_t.RamAddr_t != NULL_PTR)
        {
            NvM_CurrentBlockInfo_t.RamAddr_t = NvM_CurrentJob_t.RamAddr_t;
        }

        else if(DescrPtr->CbkGetMirrorFunc_pt == NULL_PTR)
        {
            NvM_CurrentBlockInfo_t.RamAddr_t = DescrPtr->RamBlockDataAddr_t;
        }
        else
        {

        }
    }
#else
    NvM_CurrentBlockInfo_t.RamAddr_t =
            (NvM_CurrentJob_t.RamAddr_t != NULL_PTR) ? NvM_CurrentJob_t.RamAddr_t : DescrPtr->RamBlockDataAddr_t;
#endif

    if((DescrPtr->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0)
    {

      NvM_CurrentBlockInfo_t.NvState_u8 = NVM_NVBLOCK_STATE_PRI_ACTIVE;

      NvM_IntCreateNvState(&NvM_CurrentBlockInfo_t.NvState_u8, NVM_NVBLOCK_STATE_UNKNOWN);
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitMainFsm(void)
{
    NvM_ActInitBlock();

    NvM_JobMainState_t = NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].InitialState_t;

    NvM_ActionTable_ap[NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].InitialActionId]();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadAll(void)
{
    NvM_BlockIdType currBlockId = NvM_NoOfBlockIds_t;

    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ERROR_CL & NVM_INTFLAG_DYN_MISMATCH_CL;

    do
    {
        currBlockId--;
        NvM_BlockMngmtArea_at[currBlockId].NvRamErrorStatus_u8 = NVM_REQ_PENDING;
        NvM_BlockNotification(currBlockId, NVM_READ_ALL, NVM_REQ_PENDING);

    } while(currBlockId > 0);

    NvM_ActSetInitialAttr();

#if(NVM_DRV_MODE_SWITCH == STD_ON)
    MemIf_SetMode(MEMIF_MODE_FAST);
#endif

    NvM_ActInitReadBlockFsm();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishCfgIdCheck(void)
{

    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_DYN_MISMATCH_CL;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {
        if((NvM_CompiledConfigId_t.Bytes_au8[0] != NvM_CurrentBlockInfo_t.RamAddr_t[0]) ||
           (NvM_CompiledConfigId_t.Bytes_au8[1] != NvM_CurrentBlockInfo_t.RamAddr_t[1]))
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
            NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_DYN_MISMATCH_SET;

            NvM_UpdateConfigIdBlock();
#endif
        }
    }
    else if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NV_INVALIDATED)
    {
        NvM_UpdateConfigIdBlock();
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_DYN_MISMATCH_SET;

        NvM_UpdateConfigIdBlock();
#endif
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteAll(void)
{

    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ERROR_CL;

#if(NVM_DRV_MODE_SWITCH == STD_ON)
    MemIf_SetMode(MEMIF_MODE_FAST);
#endif
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlock(void)
{
    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0;

    if((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0)
    {

        NvM_ActTestBlockBlank();
    }

#if(NVM_CRC_INT_BUFFER == STD_ON)
    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;
#endif

    NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t,
                      NvM_CurrentJob_t.JobBlockId_t,
                      NvM_CurrentBlockInfo_t.RamAddr_t);

    NvM_ActCopyNvDataToBuf();

#if (NVM_CRC_INT_BUFFER == STD_ON)

    NvM_CrcJob_ImportBufferedValue(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockCrcAddr_t);
#endif
}

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishEraseBlock(void)
{
    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
    	NvM_DemReportErrorReqFailed();
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }

    NvM_IntUpdateCurrentBlockNVRAMStatus(NVM_REQ_NOT_OK);
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadBlockFsm(void)
{
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)

    const NvM_InternalServiceIdEnumType jobId =
        (((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_DYN_MISMATCH_SET) != 0) &&
        ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_RESISTANT_TO_CHANGED_SW_ON) == 0)) ?
                                                                NVM_INT_FID_RESTORE_DEFAULTS : NVM_INT_FID_READ_BLOCK;
#else

    const NvM_InternalServiceIdEnumType jobId = NVM_INT_FID_READ_BLOCK;
#endif

    const NvM_StateActionType InitialActId = NvM_IntServiceDescrTable_at[jobId].InitialActionId;
    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[jobId].InitialState_t;

    NvM_ActionTable_ap[InitialActId]();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlockFsm(void)
{
    const NvM_StateActionType InitialActId = NvM_IntServiceDescrTable_at[NVM_INT_FID_WRITE_BLOCK].InitialActionId;

    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[NVM_INT_FID_WRITE_BLOCK].InitialState_t;
    NvM_ActionTable_ap[InitialActId]();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaults(void)
{

    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;
}

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActInvalidateNvBlock(void)
{
    if (E_OK != MemIf_InvalidateBlock((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                      NvM_CurrentBlockInfo_t.NvIdentifier_u16))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActNop(void)
{
    return;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWriteNvBlock(void)
{
    const NvM_RamAddressType src_pt = NvM_CurrentBlockInfo_t.RamAddr_t;
    Std_ReturnType retValMemIf;

    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8++;

    NvM_IntUpdateCurrentBlockNVRAMStatus(NVM_REQ_NOT_OK);

    NvM_CrcJob_CopyToBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);

#if(NVM_CRC_INT_BUFFER == STD_ON)

    if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR)
    {
        NvM_CrcJob_ExportBufferedValue(&NvM_CurrentBlockInfo_t.BlockCrcJob_t,
                                        NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockCrcAddr_t);
    }
#endif

#if(NVM_KILL_WRITEALL_API == STD_ON)

    NvM_EnterCriticalSection();

    if(NvM_IsWriteAllAndKilled(NvM_CurrentJob_t.JobServiceId_t, NvM_ApiFlags_u8))
    {

        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
#endif
    {
        retValMemIf = MemIf_Write((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                                        NvM_CurrentBlockInfo_t.NvIdentifier_u16, src_pt);
        if(E_OK == retValMemIf)
        {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
        }
        else
        {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
    }

#if(NVM_KILL_WRITEALL_API == STD_ON)
    NvM_ExitCriticalSection();
#endif
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlock(void)
{
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;
    const uint16 BlockLength = descr_pt->NvBlockLength_u16;
    const NvM_RamAddressType readDest_pt = NvM_CurrentBlockInfo_t.RamAddr_t;
    uint8 crcLen;

    NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t, readDest_pt);

    crcLen = NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);

    NvM_CurrentBlockInfo_t.ByteCount_u16 = BlockLength;

    if (E_OK != MemIf_Read((uint8)descr_pt->DeviceId_u8,
                           NvM_CurrentBlockInfo_t.NvIdentifier_u16,
                           0u,
                           readDest_pt,
                           (uint16)(BlockLength + crcLen)))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrcRead(void)
{
    if(NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t))
    {
        NvM_CrcJob_Process(&(NvM_CurrentBlockInfo_t.BlockCrcJob_t), NvM_NoOfCrcBytes_u16);
    }
    else
    {
#if(NVM_CRC_INT_BUFFER == STD_ON)

        if(NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t))
        {

            NvM_InternalCopyBufferedData(&NvM_CurrentBlockInfo_t, NvM_CurrentBlockInfo_t.RamAddr_t);
        }
        else
        {
            NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;
        }
#else

        NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;
#endif
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyBufferedData(NvM_BlockInfoPtrType info_pt, NvM_ConstRamAddressType srcPtr)
{
#if(NVM_CRC_INT_BUFFER == STD_ON)
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;

    if((descr_pt->CbkGetMirrorFunc_pt != NULL_PTR) && (NvM_CurrentJob_t.RamAddr_t == NULL_PTR))
    {
        if(descr_pt->CbkGetMirrorFunc_pt(srcPtr) == E_OK)
        {
            info_pt->ByteCount_u16 = 0;
        }
    }
    else
    {
        const NvM_RamAddressType destPtr = (NvM_CurrentJob_t.RamAddr_t != NULL_PTR) ?
            NvM_CurrentJob_t.RamAddr_t : descr_pt->RamBlockDataAddr_t;
        if(srcPtr != destPtr)
        {
            NvM_InternalCopyData(info_pt, destPtr, srcPtr);
        }
        else
        {
            info_pt->ByteCount_u16 = 0;
        }
    }
#else
    NvM_InternalCopyData(info_pt, info_pt->RamAddr_t, srcPtr);
#endif
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRestoreRomDefaults(void)
{

    NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t, NULL_PTR);

    if(NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt != NULL_PTR)
    {
        NvM_InternalCopyBufferedData(&NvM_CurrentBlockInfo_t,
            NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt);
    }
    else
    {

        if (NvM_CurrentBlockInfo_t.Descriptor_pt->InitCallback_pt != NULL_PTR)
        {

            if(!((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_READ_ALL) &&
                ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_CBK_DURING_READALL_ON) != NVM_CBK_DURING_READALL_ON)))
            {
                (void)((*NvM_CurrentBlockInfo_t.Descriptor_pt->InitCallback_pt)());
            }
        }

        NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;
    }

    NvM_ActWait();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishRestoreRomDefaults(void)
{

    if((NvM_CurrentJob_t.RamAddr_t == NULL_PTR) && (
         (NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt != NULL_PTR) ||
         (NvM_CurrentBlockInfo_t.Descriptor_pt->InitCallback_pt != NULL_PTR)))
    {
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET);

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_CALC_RAM_CRC_USED == STD_ON))
        NvM_CrcQueueJob(NvM_CurrentJob_t.JobBlockId_t);
#endif
    }

    NvM_IntUpdateCurrentBlockNVRAMStatus(NVM_REQ_NOT_OK);
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetInitialAttr(void)
{
    uint8 attribs_u8loc;

    if ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_PROT_ON) != 0)
    {

         attribs_u8loc = NVM_WR_PROT_SET;
    }
    else
    {

          attribs_u8loc = 0u;
    }

    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 = attribs_u8loc;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqIntegrityFailed(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqSkipped(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_BLOCK_SKIPPED;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_SetBlockPendingWriteAll(void)
{
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    NvM_BlockNotification(NvM_CurrentJob_t.JobBlockId_t, NVM_WRITE_ALL, NVM_REQ_PENDING);
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupRedundant(void)
{

    NvM_ActUpdateNvState();

    NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= 0x01u;

    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupOther(void)
{

    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;

    NvM_CurrentBlockInfo_t.NvIdentifier_u16 ^= 0x0001u;

    NvM_ActUpdateNvState();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActUpdateNvState(void)
{
    uint8 NvBlockState_u8;

    switch (NvM_CurrentBlockInfo_t.LastResult_t)
    {
        case (NVM_REQ_OK):

            NvBlockState_u8 = NVM_NVBLOCK_STATE_UPTODATE;
            break;

        case (NVM_REQ_NV_INVALIDATED):

            NvBlockState_u8 = NVM_NVBLOCK_STATE_OUTDATED;
            break;

        default:

            NvBlockState_u8 = NVM_NVBLOCK_STATE_DEFECT;
            break;
    }

    NvM_IntCreateNvState(&NvM_CurrentBlockInfo_t.NvState_u8, NvBlockState_u8);

    NvM_CurrentBlockInfo_t.NvState_u8 ^= NVM_NVBLOCK_STATE_SEC_ACTIVE;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntCreateNvState(P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvState, uint8 NewState)
{
    uint8 shift;

    if((*NvState & NVM_NVBLOCK_STATE_SEC_ACTIVE) != 0)
    {
        shift = NVM_SEC_NVBLOCK_STATE_SHIFT;
    }
    else
    {
        shift = NVM_PRI_NVBLOCK_STATE_SHIFT;
    }

    *NvState &= (NVM_NVBLOCK_STATE_UNKNOWN << shift) ^ 0xFFu;

    *NvState |= (uint8)(NewState << shift);
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetMultiBlockJob(void)
 {
    const uint8 multiJobFlags = NvM_ApiFlags_u8;

    NvM_CurrentJob_t.JobBlockId_t   = 0x00u;
    NvM_CurrentJob_t.RamAddr_t      = NULL_PTR;

    if ((multiJobFlags & NVM_APIFLAG_WRITE_ALL_SET) != 0)
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_WRITE_ALL;

        NvM_CurrentJob_t.JobBlockId_t = (NvM_NoOfBlockIds_t - 1);
    }
    else if ((multiJobFlags & NVM_APIFLAG_READ_ALL_SET) != 0)
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_READ_ALL;

        NvM_CurrentJob_t.JobBlockId_t = 1u;
    }
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    else if ((multiJobFlags & NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET) != 0)
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS;
    }
#endif
    else
    {

    }
 }

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActTestBlockBlank(void)
{

    if(E_OK == MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                          NvM_CurrentBlockInfo_t.NvIdentifier_u16,
                          0u,
                          &NvM_TestBuffer_u8,
                          1u))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActValidateRam(void)
{

    if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR)
    {
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= NVM_STATE_VALID_SET;
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &= NVM_STATE_CHANGED_CL;
#else

        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET);
#endif
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActWait(void)
{
    NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_WAIT_SET;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActCopyNvDataToBuf(void)
{
#if(NVM_CRC_INT_BUFFER == STD_ON)

    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;

    if(NvM_CurrentBlockInfo_t.ByteCount_u16 > 0)
    {

        if((descr_pt->CbkSetMirrorFunc_pt != NULL_PTR) && (NvM_CurrentJob_t.RamAddr_t == NULL_PTR))
        {
            if(descr_pt->CbkSetMirrorFunc_pt(NvM_InternalBuffer_au8) == E_OK)
            {
                NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;
            }
        }

        else if(descr_pt->CrcSettings > NVM_BLOCK_USE_CRC_OFF)
        {
            const NvM_RamAddressType ramAddr = (NvM_CurrentJob_t.RamAddr_t != NULL_PTR) ?
                NvM_CurrentJob_t.RamAddr_t : NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t;

            NvM_InternalCopyData(&NvM_CurrentBlockInfo_t,  NvM_CurrentBlockInfo_t.RamAddr_t, ramAddr);
        }

        else
        {
            NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;
        }
    }
    else
#endif

    {

        NvM_CrcJob_Process(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_NoOfCrcBytes_u16);
    }
}

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInit(void)
{

    NvM_CurrentJob_t.JobBlockId_t = (NvM_RepairRedBlockState.CurrentBlockId == 0) ? 1u : NvM_RepairRedBlockState.CurrentBlockId;

    NVM_ActRepairRedBlocksInitBlock();
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksInitNext(void)
{

    do
    {
        NvM_CurrentJob_t.JobBlockId_t++;
    }while((NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t) &&

        (NvM_BlockDescriptorTable_at[NvM_CurrentJob_t.JobBlockId_t].MngmtType_t != NVM_BLOCK_REDUNDANT));

    if(NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t)
    {
        NVM_ActRepairRedBlocksInitBlock();
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NVM_ActRepairRedBlocksInitBlock(void)
{
    const NvM_BlockIdType orgBlockId = NVM_BLOCK_FROM_DCM_ID(NvM_CurrentJob_t.JobBlockId_t);
    const NvM_BlockDescrPtrType DescrPtr = &NvM_BlockDescriptorTable_at[orgBlockId];

    NvM_CurrentBlockInfo_t.Mngmt_pt = &NvM_BlockMngmtArea_at[orgBlockId];
    NvM_CurrentBlockInfo_t.Descriptor_pt = DescrPtr;
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 = DescrPtr->NvIdentifier_u16;
    NvM_CurrentBlockInfo_t.ByteCount_u16 = 0;

    NvM_CurrentBlockInfo_t.RamAddr_t = NvM_InternalBuffer_au8;

    NvM_RepairRedBlockState.CurrentBlockId = NvM_CurrentJob_t.JobBlockId_t;
    NvM_RepairRedBlockState.NvBlockState = NVM_NVBLOCK_STATE_UPTODATE;
    NvM_RepairRedBlockState.CrcBuffer = 0u;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockReadCheck(void)
{
    const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;
    uint16 blockLength;
    NvM_RamAddressType readDest_pt;

    if(descr_pt->CrcSettings == NVM_BLOCK_USE_CRC_OFF)
    {
        blockLength = 1;
        readDest_pt = &NvM_TestBuffer_u8;
    }

    else
    {

        readDest_pt = NvM_CurrentBlockInfo_t.RamAddr_t;

        NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentJob_t.JobBlockId_t, readDest_pt);

        blockLength = descr_pt->NvBlockLength_u16 + NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
    }

    if (MemIf_Read((uint8)descr_pt->DeviceId_u8, NvM_CurrentBlockInfo_t.NvIdentifier_u16, 0u, readDest_pt,
        (uint16)blockLength) == E_OK)
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockFinishReadCheck(void)
{
    sint32 stateShift =
        (NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16 == NvM_CurrentBlockInfo_t.NvIdentifier_u16) ? 0 : 4;

    boolean blockValid = FALSE;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {

        if(NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF)
        {

            blockValid = NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);

            if(stateShift == 0)
            {

                NvM_RepairRedBlockState.CrcBuffer = NvM_CurrentBlockInfo_t.BlockCrcJob_t.CurrentCrcValue;
            }
        }
        else
        {

            blockValid = TRUE;
        }
    }

    NvM_RepairRedBlockState.NvBlockState |= blockValid ?
        (NVM_NVBLOCK_STATE_UPTODATE << stateShift) : (NVM_NVBLOCK_STATE_DEFECT << stateShift);

    NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= 1u;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksReadValid(void)
{

    uint8 crcNrOfBytes = 0;

    if((NvM_RepairRedBlockState.NvBlockState & 0x0F) == NVM_NVBLOCK_STATE_DEFECT)
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16 + 1u;
    }

    else
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16;
    }

    if(NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF)
    {
        crcNrOfBytes = NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
    }

    if (MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8, NvM_CurrentBlockInfo_t.NvIdentifier_u16,
        0u, NvM_CurrentBlockInfo_t.RamAddr_t, (uint16)(NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16 + crcNrOfBytes))
        == E_OK)
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlockWriteInvalid(void)
{

    if((NvM_RepairRedBlockState.NvBlockState & 0x0F) == NVM_NVBLOCK_STATE_DEFECT)
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16;
    }

    else
    {
        NvM_CurrentBlockInfo_t.NvIdentifier_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvIdentifier_u16 + 1u;
    }

    if(MemIf_Write((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
        NvM_CurrentBlockInfo_t.NvIdentifier_u16, NvM_CurrentBlockInfo_t.RamAddr_t) == E_OK)
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinishBlock(void)
{

    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
    	NvM_DemReportErrorLossOfRedundancy();
    }

}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActRepairRedBlocksFinish(void)
{
    NvM_RepairRedBlockState.CurrentBlockId = 0;
    NvM_RepairRedBlockState.CrcBuffer = 0;
    NvM_RepairRedBlockState.NvBlockState = NVM_NVBLOCK_STATE_UPTODATE;

    NvM_ApiFlags_u8 &= NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_CL;
}
#endif

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) || (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON))

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrc(void)
{
    NvM_CrcJob_Process(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_NoOfCrcBytes_u16);
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_UpdateConfigIdBlock(void)
{
    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;

    NvM_InternalCopyBufferedData(&NvM_CurrentBlockInfo_t, NvM_CompiledConfigId_t.Bytes_au8);

    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET);
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_InternalCopyData(
    NvM_BlockInfoPtrType info_pt, NvM_RamAddressType destPtr, NvM_ConstRamAddressType srcPtr)
{
    uint16 length = (info_pt->ByteCount_u16 < NVM_MAX_DATA_COPY_BYTES) ?
                     info_pt->ByteCount_u16 : NVM_MAX_DATA_COPY_BYTES;

    info_pt->ByteCount_u16 -= length;

    destPtr = &destPtr[info_pt->ByteCount_u16];
    srcPtr = &srcPtr[info_pt->ByteCount_u16];

    while(length > 0)
    {
        --length;
        destPtr[length] = srcPtr[length];
    }
}

#if (NVM_KILL_WRITEALL_API == STD_ON)

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_IsWriteAllAndKilled(const NvM_InternalServiceIdType currServiceId, const uint8 currApiFlag)
{
    return (boolean)((currServiceId == NVM_INT_FID_WRITE_ALL) && ((currApiFlag & NVM_APIFLAG_KILL_WR_ALL_SET) != 0));
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_IntUpdateCurrentBlockNVRAMStatus(const NvM_RequestResultType result)
{
    if(result == NVM_REQ_OK)
    {
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= NVM_NVRAM_UPTODATE_SET;
    }
    else
    {
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &= NVM_NVRAM_UPTODATE_CL;
    }
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

