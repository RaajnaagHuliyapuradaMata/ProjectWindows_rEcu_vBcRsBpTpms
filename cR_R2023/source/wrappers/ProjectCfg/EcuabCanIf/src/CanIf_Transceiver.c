

#include "CanIf_Prv.h"
#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#include "CanTrcv.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvMode(VAR(uint8, AUTOMATIC) TransceiverId,
        VAR(CanTrcv_TrcvModeType, AUTOMATIC) TransceiverMode)
{

    VAR(Std_ReturnType, AUTOMATIC) Status_t;

    Status_t = E_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_TRCV_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_SET_TRCV_MODE_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK(((TransceiverMode!=CANTRCV_TRCVMODE_NORMAL)&&(TransceiverMode!=CANTRCV_TRCVMODE_SLEEP)&&(TransceiverMode!=CANTRCV_TRCVMODE_STANDBY)), CANIF_SET_TRCV_MODE_SID, CANIF_E_PARAM_TRCVMODE)

    Status_t = CanTrcv_SetOpMode(TransceiverId,TransceiverMode);

     return (Status_t);

}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvMode(P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANIF_APPL_DATA)TransceiverModePtr,
                                       VAR(uint8, AUTOMATIC) TransceiverId)

{

    VAR(Std_ReturnType, AUTOMATIC) Status_t;

    Status_t = E_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_TRCV_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_GET_TRCV_MODE_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK((TransceiverModePtr== NULL_PTR), CANIF_GET_TRCV_MODE_SID, CANIF_E_PARAM_POINTER)

    Status_t =CanTrcv_GetOpMode(TransceiverId, TransceiverModePtr);

    return (Status_t);

}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason( VAR(uint8, AUTOMATIC) TransceiverId,
        P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_DATA) TrcvWuReasonPtr)
{

    VAR(Std_ReturnType, AUTOMATIC) Status_t;

    Status_t = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_TRCV_WUMODE_REASON_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_GET_TRCV_WUMODE_REASON_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK((TrcvWuReasonPtr== NULL_PTR), CANIF_GET_TRCV_WUMODE_REASON_SID, CANIF_E_PARAM_POINTER)

    Status_t =CanTrcv_GetBusWuReason(TransceiverId,TrcvWuReasonPtr);

    return (Status_t);

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvWakeupMode(VAR(uint8, AUTOMATIC) TransceiverId,
        VAR(CanTrcv_TrcvWakeupModeType, AUTOMATIC) TrcvWakeupMode)
{

    VAR(Std_ReturnType, AUTOMATIC) Status_t;

    Status_t = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_TRCV_WAKEUPMODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_SET_TRCV_WAKEUPMODE_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK(((TrcvWakeupMode!=CANTRCV_WUMODE_ENABLE)&&(TrcvWakeupMode!=CANTRCV_WUMODE_DISABLE)&&(TrcvWakeupMode!=CANTRCV_WUMODE_CLEAR)), CANIF_SET_TRCV_WAKEUPMODE_SID, CANIF_E_PARAM_TRCVWAKEUPMODE)

    Status_t =CanTrcv_SetWakeupMode(TransceiverId, TrcvWakeupMode);

    return (Status_t);

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if(CANIF_PUBLIC_PN_SUPPORT == STD_ON && CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearTrcvWufFlag(VAR(uint8,AUTOMATIC) TransceiverId)
{

    VAR(Std_ReturnType, AUTOMATIC) Status_t;

    Status_t = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_CLEARTRCVWUFFLAG_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_CLEARTRCVWUFFLAG_SID, CANIF_E_PARAM_TRCV)

#if (CANIF_CFG_TRCV_PN_SUPPORT == STD_ON)
    Status_t = CanTrcv_ClearTrcvWufFlag(TransceiverId);
#endif

    return(Status_t);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication(VAR(uint8,AUTOMATIC) TransceiverId,
        VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode)
{

    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackPtr_Temp;

    CallBackPtr_Temp = &CanIf_Callback;

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_TRCVMODEINDICATION_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_TRCVMODEINDICATION_SID, CANIF_E_PARAM_TRCV)

    if(NULL_PTR != CallBackPtr_Temp->User_TransceiverModeIndication)
    {
        CallBackPtr_Temp->User_TransceiverModeIndication(TransceiverId, TransceiverMode);
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if(CANIF_PUBLIC_PN_SUPPORT == STD_ON && CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckTrcvWakeFlag(VAR(uint8,AUTOMATIC) TransceiverId)
{

    VAR(Std_ReturnType, AUTOMATIC) Status_t;

    Status_t = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_CHECKTRCVWAKEFLAG_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_CHECKTRCVWAKEFLAG_SID, CANIF_E_PARAM_TRCV)

    Status_t = CanTrcv_CheckWakeFlag(TransceiverId);

    return(Status_t);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if(CANIF_PUBLIC_PN_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication(VAR(uint8,AUTOMATIC) TransceiverId)
{

        P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackPtr_Temp;

        CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CLEARTRCVWAKEFLAGIND_SID, CANIF_E_UNINIT)

        CANIF_DET_REPORT_ERROR_VOID_RET(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_CLEARTRCVWAKEFLAGIND_SID, CANIF_E_PARAM_TRCV)

    CallBackPtr_Temp = &CanIf_Callback;

        if(CallBackPtr_Temp->User_ClearTrcvWufFlagIndication != NULL_PTR)
        {

            CallBackPtr_Temp->User_ClearTrcvWufFlagIndication(TransceiverId);
        }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if(CANIF_PUBLIC_PN_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication(VAR(uint8,AUTOMATIC) TransceiverId)
{

    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackPtr_Temp;

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CHECKTRCVWAKEFLAGIND_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_CHECKTRCVWAKEFLAGIND_SID, CANIF_E_PARAM_TRCV)

    CallBackPtr_Temp = &CanIf_Callback;

    if(CallBackPtr_Temp->User_CheckTrcvWakeFlagIndication != NULL_PTR)
    {

        CallBackPtr_Temp->User_CheckTrcvWakeFlagIndication(TransceiverId);
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if(CANIF_PUBLIC_PN_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability(VAR(uint8,AUTOMATIC) TransceiverId)
{

    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackPtr_Temp;

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CONFIRMPNAVAILABILITY_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_CONFIRMPNAVAILABILITY_SID, CANIF_E_PARAM_TRCV)

    CallBackPtr_Temp = &CanIf_Callback;

     if(CallBackPtr_Temp->User_ConfirmPnAvailability != NULL_PTR)
     {

         CallBackPtr_Temp->User_ConfirmPnAvailability(TransceiverId);
     }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif
