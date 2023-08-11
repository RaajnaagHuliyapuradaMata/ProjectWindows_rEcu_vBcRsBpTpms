#include "CanIf_Prv.h"

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
const Type_CfgEcuabCanIf_st *CanIf_Lok_ConfigSet_tpst;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_SetControllerMode(
   uint8 ControllerId,
   CanIf_ControllerModeType ControllerMode){
    CanIf_ControllerStateType * lControllerState_p;
    Can_ReturnType lCanStatus_en        = CAN_NOT_OK;
    Std_ReturnType lRetVal_en           = E_NOT_OK;
    Can_StateTransitionType lCanMode;
    const CanIf_Cfg_CtrlConfig_tst * lCtrlConfig_pst;

    uint8 lCtrlCustId_u8;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_CONTROLLER_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_SET_CONTROLLER_SID, CANIF_E_PARAM_CONTROLLERID)
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_SET_CONTROLLER_SID, CANIF_E_PARAM_CONTROLLERID)
    CANIF_DET_REPORT_ERROR_NOT_OK((CANIF_CS_STARTED != ControllerMode) && (CANIF_CS_STOPPED != ControllerMode) && \
                (CANIF_CS_SLEEP != ControllerMode), CANIF_SET_CONTROLLER_SID, CANIF_E_PARAM_CTRLMODE)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
    lCtrlConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + lCtrlCustId_u8;

   switch(ControllerMode){
        case CANIF_CS_SLEEP:
            lCanStatus_en = CanIf_SetControllerMode_Integration((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), CAN_T_SLEEP);
            if(lCanStatus_en != CAN_NOT_OK)
            {
                lRetVal_en = E_OK;
                lControllerState_p->Ctrl_Pdu_mode = ((uint8)CANIF_OFFLINE)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE);
            }
            break;

        case CANIF_CS_STARTED:
           lCanStatus_en = CanIf_SetControllerMode_Integration((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), CAN_T_START);
            if(lCanStatus_en!= CAN_NOT_OK)
            {
               #if (CANIF_LITE_CONFIGURATION == STD_ON)
                lControllerState_p->Ctrl_Pdu_mode = (ControllerMode<<CANIF_Ctrl_BIT_SHIFT)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_CTRL_MODE);
               #endif
               lRetVal_en = E_OK;
            }
            break;

        case CANIF_CS_STOPPED:
            if((((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT) == (uint8)CANIF_CS_SLEEP)
            {
                lCanMode = CAN_T_WAKEUP;
            }
            else
            {
                lCanMode = CAN_T_STOP;
            }
          lCanStatus_en = CanIf_SetControllerMode_Integration((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), lCanMode);
            if(lCanStatus_en != CAN_NOT_OK)
            {
                lRetVal_en = E_OK;
                lControllerState_p->Ctrl_Pdu_mode = ((uint8)CANIF_TX_OFFLINE)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE);
            }
            break;

        default:
            break;
    }

return(lRetVal_en);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_GetControllerMode(
                                           uint8 ControllerId,
                                           CanIf_ControllerModeType * ControllerModePtr
                                                        )
{

    CanIf_ControllerStateType * lControllerState_p;
#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
    uint8 lCtrlCustId_u8;
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_CONTROLLER_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_GET_CONTROLLER_SID, \
                                                                            CANIF_E_PARAM_CONTROLLERID)
#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_GET_CONTROLLER_SID, \
                                                                            CANIF_E_PARAM_CONTROLLERID)

    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == ControllerModePtr), CANIF_GET_CONTROLLER_SID,CANIF_E_PARAM_POINTER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    *ControllerModePtr = (CanIf_ControllerModeType)(((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT);

    return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

void CanIf_ControllerBusOff( uint8 ControllerId )
{

    CanIf_ControllerStateType * lControllerState_p;
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON))
    uint8 lCtrlCustId_u8;
#endif

    const CanIf_CallbackFuncType * lCallBackPtr_p;

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CONTROLLER_BUSOFF_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET((ControllerId >= CANIF_TOTAL_CTRLS), \
                                                                    CANIF_CONTROLLER_BUSOFF_SID,CANIF_E_PARAM_CONTROLLER)
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON))
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((lCtrlCustId_u8 == 0xFFu), CANIF_CONTROLLER_BUSOFF_SID,CANIF_E_PARAM_CONTROLLER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    lCallBackPtr_p = &CanIf_Callback;

    SchM_Enter_CanIf_ControllerState();

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT!= STD_OFF

    lControllerState_p->CanIf_TxCnfmStatus = CANIF_NO_NOTIFICATION;

#endif

    lControllerState_p->Ctrl_Pdu_mode = ((uint8)CANIF_TX_OFFLINE)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE);
    SchM_Exit_CanIf_ControllerState();
   if(lCallBackPtr_p->User_ControllerBusOff != NULL_PTR){
        lCallBackPtr_p->User_ControllerBusOff(ControllerId);
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

void CanIf_ControllerModeIndication_Internal( uint8 ControllerId,
        CanIf_ControllerModeType ControllerMode )
{

    CanIf_ControllerStateType * lControllerState_p;

    const CanIf_CallbackFuncType * lCallBackPtr_p;
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    uint8 lCtrlCustId_u8;
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CONTROLLER_MODE_IND_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET((ControllerId >= CANIF_TOTAL_CTRLS), \
                                                                CANIF_CONTROLLER_MODE_IND_SID,CANIF_E_PARAM_CONTROLLER)
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((lCtrlCustId_u8 == 0xFFu), CANIF_CONTROLLER_MODE_IND_SID,CANIF_E_PARAM_CONTROLLER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    lCallBackPtr_p =  &CanIf_Callback;

    if(ControllerMode != CANIF_CS_UNINIT)
    {

        lControllerState_p->Ctrl_Pdu_mode = ((((uint8)ControllerMode)<<CANIF_Ctrl_BIT_SHIFT)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_CTRL_MODE));

    }

    if(lCallBackPtr_p->User_ControllerModeIndication != NULL_PTR)
    {

        lCallBackPtr_p->User_ControllerModeIndication(ControllerId, ControllerMode);
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
