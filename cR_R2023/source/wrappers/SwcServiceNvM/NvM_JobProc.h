

#if (!defined NVM_JOBPROC_H_)
#define NVM_JOBPROC_H_

#define NVM_JOBPROC_MAJOR_VERSION    (5u)
#define NVM_JOBPROC_MINOR_VERSION    (7u)
#define NVM_JOBPROC_PATCH_VERSION    (0u)

#include "NvM_Act.h"
#include "NvM_Qry.h"
#include "NvM_Crc.h"

typedef struct
{
    NvM_BlockIdType             JobBlockId_t;
    NvM_InternalServiceIdType   JobServiceId_t;
    NvM_RamAddressType          RamAddr_t;
} NvM_JobType;

typedef P2VAR(NvM_JobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_JobPtrType;

typedef struct
{
    NvM_BlockDescrPtrType       Descriptor_pt;
    NvM_RamMngmtPtrType         Mngmt_pt;
    NvM_RamAddressType          RamAddr_t;
    NvM_CrcJobType              BlockCrcJob_t;
    uint16                      NvIdentifier_u16;
    uint16                      ByteCount_u16;
    NvM_RequestResultType       LastResult_t;
    uint8                       WriteRetryCounter_u8;
    uint8                       InternalFlags_u8;
    uint8                       NvState_u8;
} NvM_BlockInfoType;

typedef P2VAR(NvM_BlockInfoType, AUTOMATIC, NVM_FAST_DATA) NvM_BlockInfoPtrType;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

typedef struct
{
    NvM_BlockIdType CurrentBlockId;
    uint8 NvBlockState;
    uint32 CrcBuffer;
} NvM_RepairBlockStateType;

extern VAR(NvM_RepairBlockStateType, NVM_PRIVATE_DATA) NvM_RepairRedBlockState;
#endif

typedef enum
{

    NVM_STATE_UNINIT = 0u,

    NVM_STATE_IDLE,
#if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1))

    NVM_STATE_HIGH_PRIO_JOB,
#endif

    NVM_STATE_NORMAL_PRIO_JOB,
#if (NVM_KILL_WRITEALL_API == STD_ON)

    NVM_STATE_MULTI_BLOCK_JOB,
#endif

    NVM_STATE_READ_READ_DATA,

    NVM_STATE_READ_CMP_CRC,

    NVM_STATE_READ_IMPL_RECOV,

    NVM_STATE_READ_LOAD_ROM,

    NVM_STATE_WRITE_INITIAL,

    NVM_STATE_WRITE_TEST_PRI_READ,

    NVM_STATE_WRITE_TEST_SEC_READ,

    NVM_STATE_WRITE_WR_DATA_CRC_1,

    NVM_STATE_WRITE_WR_DATA_CRC_2,

    NVM_STATE_RESTORE_LOAD_ROM,

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

    NVM_STATE_INVALIDATING_BLOCK,

    NVM_STATE_ERASE_ERASE_BLOCK,
#endif

    NVM_STATE_READALL_PROC_CONFIG_ID,

    NVM_STATE_READALL_PROC_RAM_BLOCK,

    NVM_STATE_READALL_CHK_SKIP,

    NVM_STATE_READALL_WR_ONCE_PROT,
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

    NVM_STATE_READALL_CHK_RAM_VALIDITY,
#endif

    NVM_STATE_READALL_READ_NV,

    NVM_STATE_WRITEALL_PROC_BLOCK,

    NVM_STATE_WRITEALL_WRITE_FSM,

    NVM_STATE_WRITEALL_WAIT_MEMHWA,

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

    NVM_STATE_REPAIRREDUNDANT_MAIN,

    NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST,

    NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND,

    NVM_STATE_REPAIRREDUNDANT_VALIDATE_BLOCK,

    NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK,

    NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK,
#endif

    NVM_STATE_FSM_FINISHED
} NvM_StateIdType;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    typedef NvM_StateIdType NvM_StateType;
#else
    typedef uint8 NvM_StateType;
#endif

typedef struct
{
    NvM_StateActionType    InitialActionId;
    NvM_StateType          InitialState_t;
    NvM_ServiceIdType      PublicFid_t;
} NvM_IntServiceDescrType;

#define NVM_MAX_NUM_OF_STATE_CONDITIONS (3u)

#define NVM_MAX_NUM_OF_QRY_AND (2u)

typedef struct
{
    NvM_StateActionType ExitHandler_t;
    NvM_StateActionType EntryHandler_t;
} NvM_StateChangeActionsType;

typedef P2CONST(NvM_StateChangeActionsType, AUTOMATIC, NVM_PRIVATE_CONST) NvM_StateChangeActionsPtrType;

typedef struct
{
    NvM_StateQueryType         Queries_at[NVM_MAX_NUM_OF_QRY_AND];
    NvM_StateChangeActionsType Actions_t;
    NvM_StateType              NextState_t;
} NvM_StateChangeIfDescrType;

typedef struct
{
    NvM_StateChangeActionsType Actions_t;
    NvM_StateType              NextState_t;
} NvM_StateChangeElseDescrType;

typedef struct
{
    NvM_StateChangeIfDescrType   ChangeConditions_at[NVM_MAX_NUM_OF_STATE_CONDITIONS];
    NvM_StateChangeElseDescrType FinalCondition_t;
} NvM_StateDescrType;

#define NVM_START_SEC_VAR_FAST_8
#include "MemMap.h"

extern VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobMainState_t;
extern VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobSubState_t;

extern VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8;

#define NVM_STOP_SEC_VAR_FAST_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

extern VAR(NvM_StateType, NVM_PRIVATE_DATA) NvM_TaskState_t;

#define NVM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

extern VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;
extern VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void);

extern FUNC(NvM_StateType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateType);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif

