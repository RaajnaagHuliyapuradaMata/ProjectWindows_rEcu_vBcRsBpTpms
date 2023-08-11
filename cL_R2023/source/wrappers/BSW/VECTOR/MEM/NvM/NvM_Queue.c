

#define NVM_QUEUE_SOURCE

#include "Std_Types.h"

#include "NvM.h"
#include "NvM_PrivateCfg.h"

#include "NvM_JobProc.h"

#include "NvM_Queue.h"

#if ((NVM_QUEUE_MAJOR_VERSION != (5u)) \
        || (NVM_QUEUE_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Queue.c and NvM_Queue.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_Queue.c and NvM_cfg.h are inconsistent!"
#endif

#ifndef NVM_LOCAL
# define NVM_LOCAL static
#endif

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

#define NVM_IMMEDIATE_JOB_PRIO  (0x00u)
#define NVM_LOWEST_JOB_PRIO     (0xFFu)
#define NVM_LIST_END            (0xFFu)

typedef P2VAR(NvM_QueueEntryRefType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_QueueListHeadRefType;

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#if(NVM_JOB_PRIORISATION == STD_ON)
NVM_LOCAL VAR(NvM_JobQueueType, NVM_PRIVATE_DATA) NvM_HighPrioQueue;

NVM_LOCAL VAR(NvM_QueueEntryRefType, NVM_PRIVATE_DATA) NvM_LastJobEntry;
#endif

NVM_LOCAL VAR(NvM_JobQueueType, NVM_PRIVATE_DATA) NvM_NormalPrioQueue;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueuePush(NvM_QueueListHeadRefType, NvM_QueueEntryRefType);

NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueuePop(NvM_QueueListHeadRefType);

NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueueFindBlock(NvM_QueueEntryRefType, NvM_BlockIdType);

#if (NVM_JOB_PRIORISATION == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueueRequeueLastJob(void);
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, NVM_PRIVATE_CODE) NvM_QueueInit(void)
{
    uint8 index = NvM_QueueSizes_t.MaxIndex;

    while(index > 0)
    {

        NvM_JobQueue_at[index].PrevEntry = index - 1u;

        NvM_JobQueue_at[index - 1u].NextEntry = index;

        --index;
    }

    index = NvM_QueueSizes_t.NpSize;

#if (NVM_JOB_PRIORISATION == STD_ON)
        NvM_LastJobEntry = NVM_LIST_END;

        NvM_HighPrioQueue.SrvList = NVM_LIST_END;
        NvM_HighPrioQueue.EmptyList = index;

        NvM_JobQueue_at[NvM_QueueSizes_t.MaxIndex].NextEntry = index;
        NvM_JobQueue_at[index].PrevEntry = NvM_QueueSizes_t.MaxIndex;
#endif

    NvM_JobQueue_at[--index].NextEntry = 0;
    NvM_JobQueue_at[0].PrevEntry = index;

    NvM_NormalPrioQueue.EmptyList = 0;
    NvM_NormalPrioQueue.SrvList = NVM_LIST_END;
}

FUNC(boolean, NVM_PRIVATE_CODE) NvM_QueueJob(NvM_BlockIdType BlockId,
                                   NvM_InternalServiceIdType ServiceId,
                                          NvM_RamAddressType RamAddress
    )
{
    boolean retVal = FALSE;
    boolean queueFull = TRUE;
    boolean blockAlreadyPending = TRUE;

    const NvM_RamMngmtPtrType ramMngmtPtr =
        ((BlockId & NVM_DCM_BLOCK_OFFSET) != 0) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);

#if(NVM_JOB_PRIORISATION == STD_ON)
    const uint8 priority = (uint8)NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].BlockPrio_u8;

    P2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) usedQueue =
        ((priority == 0) && (ServiceId == NVM_INT_FID_WRITE_BLOCK) && ((BlockId & NVM_DCM_BLOCK_OFFSET) == 0)) ?
        (&NvM_HighPrioQueue) : (&NvM_NormalPrioQueue);
#else
    P2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) usedQueue = &NvM_NormalPrioQueue;
#endif

    NvM_EnterCriticalSection();

    queueFull = (usedQueue->EmptyList == NVM_LIST_END);
    blockAlreadyPending = (ramMngmtPtr->NvRamErrorStatus_u8 == NVM_REQ_PENDING);

    if((queueFull == FALSE) && (blockAlreadyPending == FALSE))
    {

        const NvM_QueueEntryRefType elem = NvM_QueuePop(&usedQueue->EmptyList);
        CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[elem];

        elemPtr->BlockId   = BlockId;
        elemPtr->RamAddr_t = RamAddress;
        elemPtr->ServiceId = ServiceId;
#if(NVM_JOB_PRIORISATION == STD_ON)
        elemPtr->JobPrio = priority;
#endif
        NvM_QueuePush(&usedQueue->SrvList, elem);

        ramMngmtPtr->NvRamErrorStatus_u8 = NVM_REQ_PENDING;

        retVal = TRUE;
    }

    NvM_ExitCriticalSection();

    if(queueFull == TRUE)
    {

    	NvM_DemReportErrorQueueOverflow();
    }

    else if (blockAlreadyPending == FALSE)
    {

        NvM_BlockNotification(BlockId, NvM_IntServiceDescrTable_at[ServiceId].PublicFid_t, NVM_REQ_PENDING);
    }
    else
    {

    }

    return retVal;
}

FUNC(boolean, NVM_PRIVATE_CODE) NvM_UnQueueJob(NvM_BlockIdType BlockId)
{
   const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc =
    ((BlockId & NVM_DCM_BLOCK_OFFSET) != 0) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    boolean retVal = FALSE;
    NvM_QueueEntryRefType elem;
    P2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) UsedQueue = &NvM_NormalPrioQueue;

    NvM_EnterCriticalSection();

    elem = NvM_QueueFindBlock(UsedQueue->SrvList, BlockId);

#if(NVM_JOB_PRIORISATION == STD_ON)

    if((elem == NVM_LIST_END) &&
        (NvM_BlockDescriptorTable_at[NVM_BLOCK_FROM_DCM_ID(BlockId)].BlockPrio_u8 == 0) &&
        ((BlockId & NVM_DCM_BLOCK_OFFSET) == 0))
    {
        UsedQueue = &NvM_HighPrioQueue;
        elem = NvM_QueueFindBlock(UsedQueue->SrvList, BlockId);
    }
#endif

    if(elem != NVM_LIST_END)
    {
        const NvM_InternalServiceIdType srvId = NvM_JobQueue_at[elem].ServiceId;
        const NvM_ServiceIdType   PublicServiceId =  NvM_IntServiceDescrTable_at[srvId].PublicFid_t;
        NvM_QueueEntryRefType tmpElem;

        retVal = TRUE;

        tmpElem = NvM_QueuePop(&elem);

        if(UsedQueue->SrvList == tmpElem)
        {
            UsedQueue->SrvList = elem;
        }

        NvM_QueuePush(&UsedQueue->EmptyList, tmpElem);

        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_CANCELED;
        NvM_BlockNotification(BlockId, PublicServiceId, NVM_REQ_CANCELED);
    }

    NvM_ExitCriticalSection();

    return retVal;
}

FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNormalPrioJob(void)
{
    return (boolean)(NvM_NormalPrioQueue.SrvList != NVM_LIST_END);
}

FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetNormalPrioJob(void)
{
#if (NVM_JOB_PRIORISATION == STD_ON)

    NvM_QueueEntryRefType maxPrioElem;
    NvM_QueueEntryRefType currentElem;
    uint8 maxPrio;

    NvM_EnterCriticalSection();

    currentElem = maxPrioElem = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;

    maxPrio = NvM_JobQueue_at[maxPrioElem].JobPrio;

    NvM_ExitCriticalSection();

    do
    {
        currentElem = NvM_JobQueue_at[currentElem].PrevEntry;

        if(NvM_JobQueue_at[currentElem].JobPrio < maxPrio)
        {
            maxPrioElem = currentElem;
            maxPrio = NvM_JobQueue_at[currentElem].JobPrio;
        }
    }
    while(currentElem != NvM_NormalPrioQueue.SrvList);

    NvM_LastJobEntry = maxPrioElem;

    NvM_CurrentJob_t.JobBlockId_t = NvM_JobQueue_at[maxPrioElem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[maxPrioElem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t = NvM_JobQueue_at[maxPrioElem].RamAddr_t;

    NvM_EnterCriticalSection();

    (void)NvM_QueuePop(&maxPrioElem);

    if(NvM_NormalPrioQueue.SrvList == NvM_LastJobEntry)
    {
        NvM_NormalPrioQueue.SrvList = maxPrioElem;
    }

    NvM_ExitCriticalSection();
#else

    NvM_QueueEntryRefType elem;

    NvM_EnterCriticalSection();

    NvM_NormalPrioQueue.SrvList = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;
    elem = NvM_QueuePop(&NvM_NormalPrioQueue.SrvList);

    NvM_QueuePush(&NvM_NormalPrioQueue.EmptyList, elem);

    NvM_CurrentJob_t.JobBlockId_t = NvM_JobQueue_at[elem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[elem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t = NvM_JobQueue_at[elem].RamAddr_t;

    NvM_ExitCriticalSection();
#endif
}

#if (NVM_JOB_PRIORISATION == STD_ON)

FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHighPrioJob(void)
{
    return (boolean)(NvM_HighPrioQueue.SrvList != NVM_LIST_END);
}

FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetHighPrioJob(void)
{
    NvM_QueueEntryRefType elem;

    if(NVM_STATE_NORMAL_PRIO_JOB == NvM_TaskState_t)
    {
        if(MemIf_GetStatus((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8) == MEMIF_BUSY)
        {
            MemIf_Cancel((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8);
        }

        NvM_QueueRequeueLastJob();
    }

    NvM_EnterCriticalSection();

    NvM_HighPrioQueue.SrvList = NvM_JobQueue_at[NvM_HighPrioQueue.SrvList].PrevEntry;

    elem = NvM_QueuePop(&NvM_HighPrioQueue.SrvList);

    NvM_QueuePush(&NvM_HighPrioQueue.EmptyList, elem);

    NvM_CurrentJob_t.JobBlockId_t   = NvM_JobQueue_at[elem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[elem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t      = NvM_JobQueue_at[elem].RamAddr_t;

    NvM_LastJobEntry = NVM_LIST_END;

    NvM_ExitCriticalSection();
}

FUNC(void, NVM_PRIVATE_CODE) NvM_ActQueueFreeLastJob(void)
{
    if(NvM_LastJobEntry != NVM_LIST_END)
    {
        NvM_EnterCriticalSection();

        NvM_QueuePush(&NvM_NormalPrioQueue.EmptyList, NvM_LastJobEntry);

        NvM_LastJobEntry = NVM_LIST_END;
        NvM_ExitCriticalSection();
    }
}
#endif

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueuePush(NvM_QueueListHeadRefType queue, NvM_QueueEntryRefType elem)
{
    CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[elem];

    if(*queue == NVM_LIST_END)
    {

        *queue = elem;
        elemPtr->NextEntry = elemPtr->PrevEntry = elem;
    }
    else
    {
        CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) NextPtr = &NvM_JobQueue_at[*queue];

        elemPtr->NextEntry = *queue;
        elemPtr->PrevEntry = NextPtr->PrevEntry;

        NvM_JobQueue_at[NextPtr->PrevEntry].NextEntry = elem;
        NextPtr->PrevEntry = elem;
        *queue = elem;
    }
}

NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueuePop(NvM_QueueListHeadRefType queue)
{
    const uint8 retVal = *queue;
    CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[retVal];

    if(elemPtr->NextEntry == retVal)
    {

        *queue = NVM_LIST_END;
    }
    else
    {
        *queue = elemPtr->NextEntry;

        NvM_JobQueue_at[elemPtr->NextEntry].PrevEntry = elemPtr->PrevEntry;
        NvM_JobQueue_at[elemPtr->PrevEntry].NextEntry = elemPtr->NextEntry;
    }

    return retVal;
}

NVM_LOCAL FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueueFindBlock(NvM_QueueEntryRefType QueueHead, NvM_BlockIdType BlockId)
{
    NvM_QueueEntryRefType entryRef = NVM_LIST_END;

    if(QueueHead != NVM_LIST_END)
    {
        NvM_QueueEntryRefType elem = QueueHead;

        do
        {
            elem = NvM_JobQueue_at[elem].NextEntry;

            if(NvM_JobQueue_at[elem].BlockId == BlockId)
            {

                entryRef = elem;
                break;
            }
        }
        while(elem != QueueHead);
    }

    return entryRef;
}

#if (NVM_JOB_PRIORISATION == STD_ON)

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_QueueRequeueLastJob(void)
{
    if(NvM_LastJobEntry != NVM_LIST_END)
    {
        NvM_EnterCriticalSection();

        NvM_QueuePush(&NvM_NormalPrioQueue.SrvList, NvM_LastJobEntry);

        NvM_JobQueue_at[NvM_LastJobEntry].JobPrio = NVM_IMMEDIATE_JOB_PRIO;

        NvM_NormalPrioQueue.SrvList = NvM_JobQueue_at[NvM_LastJobEntry].NextEntry;

        NvM_LastJobEntry = NVM_LIST_END;
        NvM_ExitCriticalSection();
    }
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif

