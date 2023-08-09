

#include "CanIf_Prv.h"

#if (CANIF_WAKEUP_SUPPORT == STD_ON)&&(CANIF_TRCV_WAKEUP_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup (VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) WakeupSource)
{

    P2CONST(CanIf_Wakeup, AUTOMATIC, AUTOMATIC) WkpEvent_tpcst;

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;

    VAR(boolean, AUTOMATIC) WkpDeviceFound_b= FALSE;

    VAR(uint8_least, AUTOMATIC) LoopVar_tqu8;

    VAR(Std_ReturnType, AUTOMATIC) Ret_trcv_t = E_NOT_OK;

    WkpEvent_tpcst = CanIf_WakeupList_tacst;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_CHECKWAKEUP_SID, CANIF_E_UNINIT)

    for(LoopVar_tqu8 = 0u; LoopVar_tqu8 < CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT; LoopVar_tqu8++)
    {

        if((WkpEvent_tpcst +LoopVar_tqu8)->WakeupSourceId == WakeupSource)
        {

            WkpDeviceFound_b = TRUE;

            break;
        }
    }

    CANIF_DET_REPORT_ERROR_NOT_OK((WkpDeviceFound_b == FALSE), CANIF_CHECKWAKEUP_SID, CANIF_E_PARAM_WAKEUPSOURCE)

    lControllerState_p = CanIf_Lok_ControllerState_ast + (WkpEvent_tpcst +LoopVar_tqu8)->ControllerId;

    CANIF_DET_REPORT_ERROR_NOT_OK((lControllerState_p->DeviceMode !=CANIF_CS_SLEEP), CANIF_CHECKWAKEUP_SID, CANIF_E_NOT_SLEEP)

    if((lControllerState_p->DeviceMode == CANIF_CS_SLEEP) && (WkpDeviceFound_b == TRUE))
    {

        Ret_trcv_t = CanTrcv_CheckWakeup((WkpEvent_tpcst +LoopVar_tqu8)->TransceiverId);
    }

    return(Ret_trcv_t);

}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if (CANIF_CFG_TRCV_WAKEUP_SUPPORT == STD_ON && CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation (VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) WakeupSource)
{

    P2CONST(CanIf_Wakeup, AUTOMATIC, AUTOMATIC) WkpEvent_tpcst;

    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) CallBackFunc_ps;

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) ControllerState_ps;

    VAR(uint8_least, AUTOMATIC) LoopVar_tqu8;

    VAR(Std_ReturnType, AUTOMATIC) WkpDeviceFound_b= E_NOT_OK;

    WkpEvent_tpcst = CanIf_WakeupList_tacst;

    CallBackFunc_ps = &CanIf_Callback;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_CHECKVALIDATION_SID, CANIF_E_UNINIT)

    for(LoopVar_tqu8 = 0; LoopVar_tqu8 < CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT; LoopVar_tqu8++)
    {

        if((WkpEvent_tpcst +LoopVar_tqu8)->WakeupSourceId == WakeupSource)
        {

            WkpDeviceFound_b = E_OK;

            break;
        }
    }

    CANIF_DET_REPORT_ERROR_NOT_OK((WkpDeviceFound_b == E_NOT_OK), CANIF_CHECKVALIDATION_SID, CANIF_E_PARAM_WAKEUPSOURCE)

    ControllerState_ps= CanIf_Lok_ControllerState_ast + (WkpEvent_tpcst +LoopVar_tqu8)->ControllerId;

    if((ControllerState_ps->DeviceMode == CANIF_CS_STARTED) && (WkpDeviceFound_b ==E_OK))
    {

        if((NULL_PTR != CallBackFunc_ps->User_ValidateWakeupEvent) && (ControllerState_ps->ValidationSts_b == CANIF_SET))
        {
            CallBackFunc_ps->User_ValidateWakeupEvent(WakeupSource);
        }
    }

    return(WkpDeviceFound_b);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif
