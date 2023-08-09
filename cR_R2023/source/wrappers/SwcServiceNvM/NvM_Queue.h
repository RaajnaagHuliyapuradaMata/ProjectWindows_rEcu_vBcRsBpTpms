

#if (!defined NVM_QUEUE_H_)
#define NVM_QUEUE_H_

#define NVM_QUEUE_MAJOR_VERSION    (5u)
#define NVM_QUEUE_MINOR_VERSION    (7u)
#define NVM_QUEUE_PATCH_VERSION    (0u)

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

typedef struct
{
    NvM_QueueEntryRefType SrvList;
    NvM_QueueEntryRefType EmptyList;
} NvM_JobQueueType;

#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_PRIVATE_CODE) NvM_QueueInit(void);

extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QueueJob(NvM_BlockIdType, NvM_InternalServiceIdType, NvM_RamAddressType);

extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_UnQueueJob(NvM_BlockIdType);

extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNormalPrioJob(void);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetNormalPrioJob(void);

#if (NVM_JOB_PRIORISATION == STD_ON)

extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHighPrioJob(void);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetHighPrioJob(void);

extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActQueueFreeLastJob(void);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif

#endif

