

#define NVM_JOBPROC_SOURCE

#include "Std_Types.h"

#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"

#include "NvM_JobProc.h"

#include "NvM_Act.h"
#include "NvM_Qry.h"

#if ((NVM_JOBPROC_MAJOR_VERSION != (5u)) \
        || (NVM_JOBPROC_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_JobProc.c and NvM_JobProc.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_JobProc.c and NvM_Cfg.h are inconsistent!"
#endif

#if ((NVM_ACT_MAJOR_VERSION != (5u)) \
        || (NVM_ACT_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_JobProc.c and NvM_Act.h are inconsistent!"
#endif

#if ((NVM_QRY_MAJOR_VERSION != (5u)) \
        || (NVM_QRY_MINOR_VERSION != (7u)))
# error "Version numbers of NvM_JobProc.c and NvM_Qry.h are inconsistent!"
#endif

#if (3u != NVM_MAX_NUM_OF_STATE_CONDITIONS)
# error "Only case '3 conditions (4 state exits)' is implemented"
#endif

#if (2u != NVM_MAX_NUM_OF_QRY_AND)
# error "Currently two AND-associated queries per state exit are supported"
#endif

#ifndef NVM_LOCAL
# define NVM_LOCAL static
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_FsmQuery(NvM_StateQueryPtrType);

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_FsmAction(NvM_StateChangeActionsPtrType);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#define NVM_START_SEC_VAR_FAST_8
#include "MemMap.h"

VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobMainState_t;
VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobSubState_t;

#define NVM_STOP_SEC_VAR_FAST_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

VAR(NvM_StateType, NVM_PRIVATE_DATA) NvM_TaskState_t = NVM_STATE_UNINIT;

#define NVM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
VAR(NvM_RepairBlockStateType, NVM_PRIVATE_DATA) NvM_RepairRedBlockState;
#endif

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_NO_OF_SERVICES (NVM_INT_FID_NO_JOB_PENDING + 1u)

CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[NVM_NO_OF_SERVICES] =
{

    {
        NVM_ACT_ID_InitWriteBlock, NVM_STATE_WRITE_INITIAL, NVM_WRITE_BLOCK
    },

    {
        NVM_ACT_ID_ReadNvBlock, NVM_STATE_READ_READ_DATA, NVM_READ_BLOCK
    },

    {
        NVM_ACT_ID_InitRestoreBlockDefaults, NVM_STATE_RESTORE_LOAD_ROM, NVM_RESTORE_BLOCK_DEFAULTS
    },

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

    {
        NVM_ACT_ID_InvalidateNvBlock, NVM_STATE_INVALIDATING_BLOCK, NVM_INVALIDATE_NV_BLOCK
    },

    {
        NVM_ACT_ID_EraseNvBlock, NVM_STATE_ERASE_ERASE_BLOCK, NVM_ERASE_BLOCK
    },
#else

    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_INVALIDATE_NV_BLOCK
    },

    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_ERASE_BLOCK
    },
#endif

    {
        NVM_ACT_ID_InitWriteAll, NVM_STATE_WRITEALL_PROC_BLOCK, NVM_WRITE_ALL
    },

    {
        NVM_ACT_ID_InitReadAll, NVM_STATE_READALL_PROC_CONFIG_ID, NVM_READ_ALL
    },
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

    {
        NVM_ACT_ID_RepairRedBlocksInit, NVM_STATE_REPAIRREDUNDANT_MAIN, NVM_REPAIR_REDUNDANT_BLOCKS
    },
#else

    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_REPAIR_REDUNDANT_BLOCKS
    },
#endif

    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_MAINFUNCTION
    }
};

#define NVM_STATE_IF
#define NVM_STATE_ELSEIF
#define NVM_STATE_THEN
#define NVM_STATE_ELSE

#define NVM_NEXT_STATE(state) (state)

NVM_LOCAL CONST(NvM_StateDescrType, NVM_PRIVATE_CONST) NvM_StateDescrTable_at[] =
{

    {
        {

            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
            NVM_NEXT_STATE(NVM_STATE_UNINIT)
        }
    },

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_1)

    {
        {

            {
                NVM_STATE_IF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob, NVM_ACT_ID_InitMainFsm},
# if (NVM_KILL_WRITEALL_API == STD_ON)
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
# else
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
# endif
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#elif (NVM_JOB_PRIORISATION == STD_ON)

    {
        {

            {
                NVM_STATE_IF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_NORMAL_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetNormalPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob, NVM_ACT_ID_InitMainFsm},
# if (NVM_KILL_WRITEALL_API == STD_ON)
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
# else
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
# endif
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#else

    {
        {

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_NORMAL_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetNormalPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob, NVM_ACT_ID_InitMainFsm},
# if (NVM_KILL_WRITEALL_API == STD_ON)
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
# else
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
# endif
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#endif
#if ((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && (NVM_JOB_PRIORISATION == STD_ON))

    {
        {

            {
                NVM_STATE_IF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#endif
#if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1))

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_QueueFreeLastJob},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#else

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },

#endif

#if (NVM_KILL_WRITEALL_API == STD_ON)

# if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1))

        {
            {
                {
                    NVM_STATE_IF{NVM_QR_ID_WRITEALL_KILLED, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_KillWritAll, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_IDLE)
                },
                {
                    NVM_STATE_ELSEIF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                        NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
                },
                {
                    NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
                }
            },

            {
                NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
# else

        {
            {
                {
                    NVM_STATE_IF{NVM_QR_ID_WRITEALL_KILLED, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_KillWritAll, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_IDLE)
                },
                {
                    NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
                },
                {
                    NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_IDLE)
                },
            },

            {
                NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
# endif
#endif

    {
        {
            {

                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_READ_DATA)
            },
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrcRead, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READ_CMP_CRC)
            },
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ValidateRam, NVM_ACT_ID_FinishReadBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }

        },
        {

            NVM_STATE_ELSE{NVM_ACT_ID_Nop,  NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
        }
    },

    {
        {
            {

                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrcRead, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READ_CMP_CRC)
            },
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_MATCH, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ValidateRam, NVM_ACT_ID_FinishReadBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqIntegrityFailed, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetReqIntegrityFailed, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    {
        {
            {

                NVM_STATE_IF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_ReadNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_READ_READ_DATA)
            },
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitRestoreBlockDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitRestoreBlockDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
            }
        },

        {
            NVM_STATE_THEN{NVM_ACT_ID_InitRestoreBlockDefaults, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
        }
    },
    {
        {
            {

                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
            },
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },

        {
            NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_CopyNvDataToBuf, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_INITIAL)
            },
            {
                NVM_STATE_ELSEIF{NvM_QRY_CRC_COMP_MECHANISM_SKIPWRITE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            },
            {
                NVM_STATE_IF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_LAST_RESULT_OK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_TestBlockBlank},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_SEC_READ)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_SEC_READ)
            },
            {
                NVM_STATE_IF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_WRITE_RETRIES_EXCEEDED, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_WRITE_RETRIES_EXCEEDED, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_RESTORE_LOAD_ROM)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_INVALIDATING_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_REDUNDANT_BLOCK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_InvalidateNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_INVALIDATING_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_ERASE_ERASE_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_REDUNDANT_BLOCK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_EraseNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_ERASE_ERASE_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#endif

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_CONFIG_ID)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_LAST_BLOCK_DONE_READALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_RAM_VALID, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_RAM_VALIDITY)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
        }
    },
#else

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_LAST_BLOCK_DONE_READALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
        }
    },
#endif

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_WRITE_BLOCK_ONCE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_TestBlockBlank},
                    NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_TestBlockBlank},
                    NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_InitNextBlockReadAll},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_RAM_VALIDITY)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_MATCH, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
        }
    },
#endif

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },

        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_CANCEL_WRITE_ALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_BLOCK_DONE_WRITEALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WAIT_MEMHWA)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_BLK_WRITE_ALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetBlockPendingWriteAll, NVM_ACT_ID_InitWriteBlockFsm},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WRITE_FSM)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_InitNextBlockWriteAll},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WRITE_FSM)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockWriteAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            },

            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockWriteAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            }
        },

        {
            NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockWriteAll, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_CANCEL_WRITE_ALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MEMHWA_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WAIT_MEMHWA)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },

        {
            NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

    {
        {
            {

                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_BLOCK_DONE_READALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinish, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_IF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockReadCheck, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST)
            }
        },
        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksInitNext, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST)
            }
        },
        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockFinishReadCheck, NVM_ACT_ID_RepairRedBlockReadCheck},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND)
            }
        },
        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockFinishReadCheck, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_VALIDATE_BLOCK)
        }
    },

    {
        {
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_REPAIR_RED_BLOCK_DEFECT, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksReadValid, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK)
            },
            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksInitNext, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
            }
        },

        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksInitNext, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockWriteInvalid, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK)
            }
        },
        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
            }
        },

        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },
#endif

    {
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    }
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void)
{
    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;

    NvM_CurrentBlockInfo_t.InternalFlags_u8 = 0;

    NvM_JobMainState_t = NVM_STATE_FSM_FINISHED;
    NvM_JobSubState_t  = NVM_STATE_FSM_FINISHED;
    NvM_TaskState_t    = NVM_STATE_IDLE;
}

FUNC(NvM_StateType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateType NvM_CurrentState_t)
{

    NvM_StateType NvM_RetState_tloc;
    NvM_StateChangeActionsPtrType ChangeActions_ptloc;
    CONSTP2CONST(NvM_StateDescrType, AUTOMATIC, NVM_PRIVATE_CONST) CurrentState_ptloc =
        &NvM_StateDescrTable_at[NvM_CurrentState_t];

    if(NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[0].Queries_at))
    {
        NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[0].NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[0].Actions_t;
    }
    else if (NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[1].Queries_at))
    {
        NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[1].NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[1].Actions_t;
    }
    else if (NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[2].Queries_at))
    {
        NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[2].NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[2].Actions_t;
    }
    else
    {
        NvM_RetState_tloc = CurrentState_ptloc->FinalCondition_t.NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->FinalCondition_t.Actions_t;
    }

    NvM_FsmAction(ChangeActions_ptloc);

    return NvM_RetState_tloc;
}

NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_FsmQuery(NvM_StateQueryPtrType NvM_Queries_at)
{

    boolean retVal = NvM_QueryTable_ap[NvM_Queries_at[0u]]();

    if (retVal)
    {
        retVal = NvM_QueryTable_ap[NvM_Queries_at[1u]]();
    }

    return retVal;
}

NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_FsmAction(NvM_StateChangeActionsPtrType NvM_Actions_pt)
{
    NvM_ActionTable_ap[NvM_Actions_pt->ExitHandler_t]();
    NvM_ActionTable_ap[NvM_Actions_pt->EntryHandler_t]();
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

