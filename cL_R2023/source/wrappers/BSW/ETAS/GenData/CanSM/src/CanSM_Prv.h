
#ifndef  CANSM_PRV_H
#define  CANSM_PRV_H

#include "CanSM_Cfg_SchM.h"
#include "CanSM.h"
#include "BswM_CanSM.h"
#include "Dem.h"
#include "CanSM_Cbk.h"
#include "CanSM_ComM.h"
#include "CanSM_TxTimeoutException.h"
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#include "CanNM.h"
#endif
#if(CANSM_DEV_ERROR_DETECT != STD_OFF)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != CANSM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define CANSM_RECOVERY_ENABLED   1u

#define CANSM_RECOVERY_DISABLED  2u

#define CANSM_MUTEX_FREE  1u

#define CANSM_MUTEX_BUSY  2u

#define CANSM_NETWORKIDX_ERROR  255u

#define CANSM_ZERO   0u

#define CANSM_INVALID_ID      0xffu

#define CANSM_INITED  0x1u

#define CANSM_UNINITED  0x0u

#define CANSM_FALSE  0x0u

#define CANSM_TRUE   0x01u

#define CANSM_DEM_DISABLED  0xffff

#if CANSM_DEV_ERROR_DETECT != STD_OFF

    #define CANSM_REPORT_ERROR(CONDITION, API, ERROR)                                                       \
                                   if(CONDITION)                                                            \
                                   {                                                                        \
                                        (void)Det_ReportError((CANSM_MODULE_ID), (0u), (API), (ERROR));     \
                                        return;                                                             \
                                   }

    #define CANSM_REPORT_ERROR_NOK(CONDITION, API, ERROR)                                                   \
                                   if(CONDITION)                                                            \
                                   {                                                                        \
                                        (void)Det_ReportError((CANSM_MODULE_ID), (0u), (API), (ERROR));     \
                                        return E_NOT_OK;                                                    \
                                   }

    #define CANSM_REPORT_ERROR_NO_CONDITON(API, ERROR)                                                       \
                                   {                                                                        \
                                        (void)Det_ReportError((CANSM_MODULE_ID), (0u), (API), (ERROR));     \
                                        return;                                                             \
                                   }

#else
    #define CANSM_REPORT_ERROR(CONDITION, API, ERROR)

    #define CANSM_REPORT_ERROR_NOK(CONDITION, API, ERROR)

    #define CANSM_REPORT_ERROR_NO_CONDITON(API, ERROR)

#endif

#define CanSM_ReleaseMutex(Indx_Network)           \
                            \
CanSM_MutexMode_au8[Indx_Network] = CANSM_MUTEX_FREE;  \

#define CanSM_InitTimer(Indx_Network)                                 \
do                                                                    \
{                                                                     \
                                      \
    CanSM_TimerConfig_ast[Indx_Network].cntTick_u16 = 0;                \
                                      \
    CanSM_TimerConfig_ast[Indx_Network].stTimer = CANSM_TIMER_INIT;     \
}while(0)

#define CanSM_StartTimer(Indx_Network)                                \
do                                                                    \
{                                                                     \
                                      \
    CanSM_TimerConfig_ast[Indx_Network].cntTick_u16 = 0;                \
                                   \
    CanSM_TimerConfig_ast[Indx_Network].stTimer = CANSM_TIMER_RUNNING;  \
}while(0)

typedef enum
{
    CANSM_DEFAULT,
    CANSM_S_CC_STOPPED ,
    CANSM_S_PN_CC_STOPPED ,
    CANSM_S_CC_STOPPED_WAIT,
    CANSM_S_PN_CC_STOPPED_WAIT,
    CANSM_S_CC_SLEEP,
    CANSM_S_PN_CC_SLEEP,
    CANSM_S_CC_SLEEP_WAIT,
    CANSM_S_PN_CC_SLEEP_WAIT,
    CANSM_S_TRCV_NORMAL,
    CANSM_S_PN_TRCV_NORMAL,
    CANSM_S_TRCV_NORMAL_WAIT,
    CANSM_S_PN_TRCV_NORMAL_WAIT,
    CANSM_S_TRCV_STANDBY,
    CANSM_S_PN_TRCV_STANDBY,
    CANSM_S_TRCV_STANDBY_WAIT,
    CANSM_S_PN_TRCV_STANDBY_WAIT,
    CANSM_S_PN_CLEAR_WUF ,
    CANSM_S_PN_CLEAR_WUF_WAIT,
    CANSM_S_CHECK_WFLAG_IN_CC_SLEEP,
    CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT,
    CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP,
    CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT
}CanSM_PreNoCom_Substates_ten;

typedef enum
{
    CANSM_BOR_CONTROLLER_STOPPED_REQUEST  = 0,
    CANSM_BOR_CONTROLLER_STOPPED_WAIT     = 1,
    CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED = 2
}CanSM_BOR_Controller_Stopped_stateType_ten;

typedef enum
{
    CANSM_PRE_FULLCOM_DEFAULT,
    CANSM_PRE_FULLCOM_S_TRCV_NORMAL,
    CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT,
    CANSM_PRE_FULLCOM_S_CC_STOPPED,
    CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT,
    CANSM_PRE_FULLCOM_S_CC_STARTED,
    CANSM_PRE_FULLCOM_S_CC_STARTED_WAIT
}CanSM_PreFullCom_Substates_ten;

typedef enum
{
    CANSM_WAKEUP_VALIDATION_DEFAULT,
    CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL,
    CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT,
    CANSM_WAKEUP_VALIDATION_S_CC_STOPPED,
    CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT,
    CANSM_WAKEUP_VALIDATION_S_CC_STARTED,
    CANSM_WAKEUP_VALIDATION_S_CC_STARTED_WAIT
}CanSM_WakeUpValidation_Substates_ten;

#if(CANSM_SET_BAUDRATE_API == STD_ON)

typedef enum
{
    CANSM_BR_DEFAULT,
    CANSM_BR_S_CC_STOPPED,
    CANSM_BR_S_CC_STOPPED_WAIT,
    CANSM_BR_S_CC_STARTED,
    CANSM_BR_S_CC_STARTED_WAIT,
    CANSM_BSM_CHANGE_BR_SYNC
}CanSM_ChangeBR_Substates_ten;
#endif

typedef enum
{
    CANSM_TxTimeoutException_DEFAULT,
    CANSM_TxTimeoutException_S_CC_STOPPED,
    CANSM_TxTimeoutException_S_CC_STOPPED_WAIT,
    CANSM_TxTimeoutException_S_CC_STARTED,
    CANSM_TxTimeoutException_S_CC_STARTED_WAIT
}CanSM_TxTimeoutException_Substates_ten;

typedef enum
{
    CANSM_ControllerState_UNINIT = 0,
    CANSM_ControllerState_STOPPED,
    CANSM_ControllerState_STARTED,
    CANSM_ControllerState_SLEEP
}CanSM_CANControllerStateType_ten;

typedef enum
{
    CANSM_TIMER_INIT        = 1,
    CANSM_TIMER_RUNNING     = 2,
    CANSM_TIMER_ELAPSED     = 3,
    CANSM_TIMER_CANCELLED   = 4
}CanSM_TimerStateType_ten;

typedef struct{
    CanSM_TimerStateType_ten stTimer;
    uint16 cntTick_u16;
}CanSM_TimerConfig_tst;

#if (CANSM_DSM_REINIT_ENABLED != STD_OFF)

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_NetworkConf_DEM_tst CanSM_DSM_ReInit_Status_ast[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#if(CANSM_VARIANT_INFO == CANSM_VARIANT_PRE_COMPILE)
#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"
extern const CanSM_NetworkConf_tst CanSM_Network_Config_acst[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"
extern const uint8 CanSM_NetworktoCtrl_Config_acu8[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#endif

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern const Type_CfgSwcServiceCanSM_st * CanSM_ConfigSet_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern const CanSM_NetworkConf_tst * CanSM_Network_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_TimerConfig_tst CanSM_TimerConfig_ast[CANSM_NUM_CAN_NETWORKS] ;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Init_ab;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_NetworkModeStateType_ten CanSM_CurrNw_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_BusOffRecoveryStateType_ten CanSM_currBOR_State_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern uint8 CanSM_BusOff_Cntr_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern uint8 CanSM_BORMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_BusOff_Indicated_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern uint8 CanSM_MutexMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern ComM_ModeType CanSM_ReqComM_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Wuvalidation_Start_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_BusOffISRPend_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_SET_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

extern CanSM_ChangeBR_Substates_ten CanSM_ChangeBR_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)

#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
extern uint16 CanSM_BaudRateConfigID_Value_au16[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

#endif

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern uint8 CanSM_Num_Unsuccessful_ModeReq_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Trcv_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Ctrl_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

extern boolean CanSM_ModeChangeReq_flag[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

extern CanSM_ReqCanTrcv_States CanSM_ReqMode_a[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_PreNoCom_Substates_ten CanSM_PreNoCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_PN_Substate_Ind_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern ComM_ModeType CanSM_BusSMMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_PreFullCom_Substates_ten CanSM_PreFullCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_WakeUpValidation_Substates_ten CanSM_WakeUpValidation_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_TxTimeoutException_Substates_ten CanSM_TxTimeoutexception_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
extern uint16 CanSM_ModeRepeatReq_Time_u16;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern uint8 CanSM_ModeRepeatReq_Max_u8;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_CANControllerStateType_ten CanSM_ControllerState_en[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Network_Init_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_ControllerIndications_ab[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_BOR_Controller_Stopped_stateType_ten CanSM_BOR_Controller_Stopped_state_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Passive_b;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_Rn_DisableBusOffRecovery_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern boolean CanSM_BOR_SilentCom_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
extern void CanSM_DeInitPnSupported(NetworkHandleType network);
extern void CanSM_CheckWakeUpFlagInSleep(NetworkHandleType network);
extern void CanSM_CheckWakeUpFlagNotInSleep(NetworkHandleType network);
extern void CanSM_PN_ClearWufTrcv(NetworkHandleType network);
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)
extern void CanSM_SetBaudrate_StateMachine(NetworkHandleType network);
#endif
extern void CanSM_DeInitPnNotSupported(NetworkHandleType network);
extern void CanSM_StopCtrl(NetworkHandleType network);
extern void CanSM_StartCtrl(NetworkHandleType network);
extern void CanSM_SleepCtrl(NetworkHandleType network);
#if (CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
extern void CanSM_NormalTrcv(NetworkHandleType network);
extern void CanSM_StandbyTrcv(NetworkHandleType network);
#endif
extern void CanSM_NO2FULL_COM(NetworkHandleType network);
extern void CanSM_FULL2SILENT_COM(NetworkHandleType network);
extern void CanSM_SILENT2FULL_COM(NetworkHandleType network);
extern void CanSM_TxTimeoutException_StateMachine(NetworkHandleType Channel);
extern void CanSM_NetworkModeTrans( NetworkHandleType network,ComM_ModeType ComM_Mode);
#if (CANSM_BOR_TX_CONFIRMATION_POLLING != STD_OFF)
extern Std_ReturnType CanSM_CheckTxRxNotification(NetworkHandleType network);
#endif
extern NetworkHandleType CanSM_GetHandle(NetworkHandleType ComMChannelId);
extern Std_ReturnType CanSM_GetMutex(NetworkHandleType network);
extern void CanSM_BusOffTransitions(NetworkHandleType network);
extern void CanSM_BOR_MultipleCtrlsStop(NetworkHandleType network);
extern void CanSM_BOR_CtrlsStart(NetworkHandleType network);
extern void CanSM_BOR_CtrlsStart_SilentCom(NetworkHandleType network);
extern void CanSM_WakeUpValidation_StateMachine(NetworkHandleType network);
#if(CANSM_SET_BAUDRATE_API == STD_ON)
extern void CanSM_ChangeBR_Exit(NetworkHandleType network);
#endif
extern void CanSM_BOR_SilentCom_Exit(NetworkHandleType network);
extern void CanSM_PreNoCom_Exit(NetworkHandleType network);
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
