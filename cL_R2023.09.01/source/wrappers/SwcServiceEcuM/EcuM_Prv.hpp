#ifndef ECUM_PRV_H
#define ECUM_PRV_H

#include "Types_SwcServiceEcuM.hpp"
#include "EcuM_Cfg_Startup.hpp"

#define ECUM_MODULE_ID                  (10U)
#define ECUM_INSTANCE_ID                (0U)
#define ECUM_GETVERINFO_APIID           (0x00U)
#define ECUM_GODOWN_APIID               (0x1fU)
#define ECUM_GODOWNHALTPOLL_APIID       (0x2cU)
#define ECUM_INIT_APIID                 (0x01U)
#define ECUM_START_TWO_APIID            (0x1aU)
#define ECUM_SHUTDOWN_APIID             (0x02U)
#define ECUM_SELECT_SHUT_TAR_APIID      (0x06U)
#define ECUM_GET_SHUT_TAR_APIID         (0x09U)
#define ECUM_SELECT_SHUT_CAUSE_APIID    (0x1bU)
#define ECUM_GET_SHUT_CAUSE_APIID       (0x1cU)
#define ECUM_LAST_SHUT_TAR_APIID        (0x08U)
#define ECUM_GET_PEND_APIID             (0x0dU)
#define ECUM_CLEAR_WKEVENT_APIID        (0x16U)
#define ECUM_GET_VALIDATE_APIID         (0x15U)
#define ECUM_GET_EXPIRED_APIID          (0x19U)
#define ECUM_SEL_BOOT_APIID             (0x12U)
#define ECUM_GET_BOOT_APIID             (0x13U)
#define ECUM_MAIN_FUNC_APIID            (0x18U)
#define ECUM_SET_WKEVENT_APIID          (0x0cU)
#define ECUM_VAL_WKEVENT_APIID          (0x14U)
#define ECUM_GOHALT_APIID               (0x20U)
#define ECUM_GOPOLL_APIID               (0x21U)
#define ECUM_RB_MO_GETACTIVEPBINDEX_APIID   (0x22U)
#define ECUM_RB_MO_INITCHECK_APIID      (0x23U)
#define ECUM_RB_MO_INITCHECKINV_APIID   (0x24U)
#define ECUM_LAST_SHUT_CAUSE_APIID      (0x30U)

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
#define ECUM_END_CHECKWAKEUP_APIID      (0X31U)
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
#define ECUM_SETSTATE_APIID             (0x2BU)
#define ECUM_RB_CURRENTSTATE_APIID             (0x30U)
#define ECUM_REQUESTRUN_APIID           (0x03U)
#define ECUM_RELEASERUN_APIID           (0x04U)
#define ECUM_REQUESTPOST_RUN_APIID      (0x0aU)
#define ECUM_RELEASEPOST_RUN_APIID      (0x0bU)
#define ECUM_KILL_ALL_RUN_REQUESTS_APIID      (0x05U)
#define ECUM_KILL_ALL_POST_RUN_REQUESTS_APIID      (0x2aU)
#endif//ECUM_CFG_MODE_HANDLING

#define ECUM_E_OS_GET_RESOURCE_FAILED                                   (0x05U)
#define ECUM_E_OS_RELEASE_RESOURCE_FAILED                               (0x06U)
#define ECUM_E_UNINIT                                                   (0x10U)
#define ECUM_E_SERVICE_DISABLED                                         (0x11U)
#define ECUM_E_NULL_POINTER                                             (0x12U)
#define ECUM_E_INVALID_PAR                                              (0x13U)
#define ECUM_E_NVM_READ_FAILED                                          (0x1AU)
#define ECUM_E_PARAM_POINTER                                            (0x1BU)
#define ECUM_E_STATE_PAR_OUT_OF_RANGE                                   (0x16U)
#define ECUM_E_UNKNOWN_WAKEUP_SOURCE                                    (0x17U)
#define ECUM_E_RAM_CHECK_FAILED                                         (0x19U)
#define ECUM_E_COREREADY_TIMEOUT_EXPIRED                                (0x04U)
#define ECUM_E_SHUTDOWN_INFO_UPDATED                                    (0xFEU)
#define ECUM_E_CONFIGURATION_DATA_INCONSISTENT                          (0x18U)
#define ECUM_E_NULL_PTR_RETURNED                                        (0x30U)
#define ECUM_E_INVALID_PTR_RETURNED                                     (0x31U)
#define ECUM_E_START_CORE_FAILED                                        (0x32U)

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
#define ECUM_E_MULTIPLE_RUN_REQUESTS                                    (0x14U)
#define ECUM_E_MISMATCHED_RUN_RELEASE                                   (0x15U)
#define ECUM_RB_E_ALL_RUN_REQUESTS_KILLED                               (0xffU)
#endif//ECUM_CFG_MODE_HANDLING

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
#define ECUM_E_WAKEUP_TIMEOUT                                           (0x20U)
#define ECUM_E_WAKEUP_NO_SOURCE_FOUND                                   (0x21U)

#define ECUM_SINGLE_CORE 0x00
#define ECUM_SLAVE_CORE  0x01
#define ECUM_MASTER_CORE 0x02
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
typedef enum{
    ECUM_PRV_NO_SLEEP_E = 0
   ,   ECUM_PRV_GOPOLL_E =1
   ,   ECUM_PRV_GOHALT_E=2
}EcuM_Lok_SleepType_Enum_ten;

typedef enum{
    ECUM_PRV_NORMAL_E = 0
   ,   ECUM_PRV_RESOURCE_NOT_ACQUIRED_E =1
   ,   ECUM_PRV_WAKEUP_REQUEST_E=2
   ,   ECUM_PRV_CHECK_WAKEUP_PENDING_E = 3
}EcuM_Lok_WakeupRestartReason_Enum_ten;

typedef enum{
    ECUM_PRV_HALT_SEQUENCE_E = 0
   ,   ECUM_PRV_RESTART_SEQUENCE_E =1
   ,   ECUM_PRV_CLEAR_SLEEP_E=2
   ,  ECUM_PRV_POLL_SEQUENCE_E=3
}EcuM_Lok_OperationType_Enum_ten;

typedef enum{
    EXIT_SLEEP_E = 1
   ,   ENTER_SLEEP_E = 2
   ,  CONTINUE_WAIT
}EcuM_Lok_SleepStatus_ten;

typedef struct{
   uint8  CurrentCore;
   uint16 CurrentCoreID;
}EcuM_CurrentCoreInfoType;
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_MemMap.hpp"
extern EcuM_BootTargetType EcuM_Lok_dataSelectedBootTarget_u8;
extern uint8 EcuM_Lok_dataSelectedBootTargetInit_u8;
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_8
#include "EcuM_MemMap.hpp"
extern VAR(Type_SwcServiceEcuM_ePhase, SWCSERVICEECUM_VAR) SwcServiceEcuM_ePhase;
extern uint8 EcuM_Lok_SlaveCoreTimeoutCtr_u8;
extern Type_SwcServiceEcuM_tCauseShutdown EcuM_Lok_dataSelectedShutdownCause_u8;

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
extern uint8 EcuM_Lok_RunRequested_u8;
extern uint8 EcuM_Lok_Post_Run_Requested_u8;
#endif //ECUM_CFG_MODE_HANDLING

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern EcuM_Lok_SleepType_Enum_ten EcuM_Lok_SleepReqType_en;
extern EcuM_Lok_WakeupRestartReason_Enum_ten EcuM_Lok_WakeupRestartReason_en;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_8
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern EcuM_CurrentCoreInfoType EcuM_Lok_CoreStatus_st;
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_MemMap.hpp"
extern Type_SwcServiceEcuM_tSourceWakeup SwcServiceEcuM_tSourceWakeup_EventsPending;
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataOldPendingWakeupEvents_u32;
extern Type_SwcServiceEcuM_tSourceWakeup SwcServiceEcuM_tSourceWakeup_Validated;
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataExpiredWakeupEvents_u32;
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataClrWkpEventsInd_u32;
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataPndWkpEventsInd_u32;
extern Type_SwcServiceEcuM_tSourceWakeup SwcServiceEcuM_tSourceWakeup_ValInd;
extern Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataExpWkpEventsInd_u32;
#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_16
#include "EcuM_MemMap.hpp"
extern uint16 EcuM_Lok_WkpSrcValidationTimeoutCtr_u16;
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern Type_SwcServiceEcuM_tModeShutdown EcuM_Lok_SleepMode_u16;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_16
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.hpp"
extern boolean EcuM_Lok_flgIsStartupTwoCalled_ab[ECUM_CFG_NUM_OS_CORES];
extern boolean SwcServiceEcuM_bIsInitialised ;
extern boolean EcuM_Lok_flgCoreReady_ab[ECUM_CFG_NUM_OS_CORES];
extern boolean EcuM_Lok_isEcuMGoDownFailed_b;
extern boolean EcuM_Lok_flgShutdownInfoDoNotUpdate_b;
extern boolean EcuM_Lok_flgGoDown_b;

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
extern boolean EcuM_Lok_userRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];
extern boolean EcuM_Lok_userPostRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];
extern boolean EcuM_Lok_KillAllRUNRequests_b;
extern boolean EcuM_Lok_KillAllPostRUNRequests_b;
#endif//ECUM_CFG_MODE_HANDLING

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
extern boolean EcuM_Lok_flgNvMReadStatus_b;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern boolean EcuM_Lok_flgwakeupRestart_b;
extern boolean EcuM_Lok_flgClearWakeupRestart_b;
extern boolean EcuM_Lok_AllCoreSleepReady_b;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_INIT_16
#include "EcuM_MemMap.hpp"
#if(ECUM_CFG_MODE_HANDLING == STD_ON)
extern uint16 EcuM_Lok_RunMinDuration_u16;
#endif//ECUM_CFG_MODE_HANDLING
#define ECUM_STOP_SEC_VAR_INIT_16
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
extern Type_SwcServiceEcuM_stInfoTargetShutdown EcuM_Lok_dataShutdownInfo_st;
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"

extern boolean EcuM_Lok_hasCheckWakeupSourceGetHandle_b(
        Type_SwcServiceEcuM_tSourceWakeup datasource_u32);
extern void EcuM_Lok_WakeupIndication(
        Type_SwcServiceEcuM_tSourceWakeup dataPendingWakeupEvents_u32  );
extern void EcuM_Lok_DecValidationCtr(void);
extern void infSwcApplEcuMSwcServiceEcuM_vStartOS(void);
extern uint32 EcuM_Lok_ComMWakeupHandling(Type_SwcServiceEcuM_tSourceWakeup dataPendingWakeupEvents);

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
extern boolean EcuM_Lok_IsUserHandlingPossible_b(
        EcuM_UserType * user, uint8 apiid);
#endif//ECUM_CFG_MODE_HANDLING

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern void EcuM_Lok_GoSleepSequence(uint16 dataSleepModeHandle_u16);
extern void EcuM_Lok_WakeupRestartSequence ( uint16 dataSleepModeHandle_u16 );
extern StatusType EcuM_Lok_GetResource(CoreIdType core_ID);
extern StatusType EcuM_Lok_ReleaseResource(CoreIdType core_ID);
extern boolean EcuM_Lok_CheckWakeupTimerHandling (void);
#endif// ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"
#endif

