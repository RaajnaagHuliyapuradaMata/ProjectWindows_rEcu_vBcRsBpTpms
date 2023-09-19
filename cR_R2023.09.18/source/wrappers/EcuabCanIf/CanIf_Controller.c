#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(
      VAR(uint8,                    AUTOMATIC) ControllerId
   ,  VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
){
      P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC)       lControllerState_p;
        VAR(Can_ReturnType,            AUTOMATIC)                  lCanStatus_en = CAN_NOT_OK;
        VAR(Std_ReturnType,            AUTOMATIC)                  lRetVal_en    = E_NOT_OK;
        VAR(Can_StateTransitionType,   AUTOMATIC)                  lCanMode;
   P2CONST(CanIf_Cfg_CtrlConfig_tst,  AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;
   VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
   lCtrlCustId_u8     = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
   lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   lCtrlConfig_pst    = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + lCtrlCustId_u8;

   switch(ControllerMode){
        case CANIF_CS_SLEEP:
            lCanStatus_en = Can_SetControllerMode((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), CAN_T_SLEEP);
            if(lCanStatus_en != CAN_NOT_OK){
                lRetVal_en = E_OK;
                lControllerState_p->ChannelMode = CANIF_OFFLINE;
            }
            break;

        case CANIF_CS_STARTED:
           lCanStatus_en = Can_SetControllerMode((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), CAN_T_START);
           if(lCanStatus_en != CAN_NOT_OK){
               lRetVal_en = E_OK;
            }
            break;

        case CANIF_CS_STOPPED:
            if(lControllerState_p->DeviceMode == CANIF_CS_SLEEP){
                lCanMode = CAN_T_WAKEUP;
            }
            else{
                lCanMode = CAN_T_STOP;
            }
            lCanStatus_en = Can_SetControllerMode((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), lCanMode);
            if(lCanStatus_en != CAN_NOT_OK){
                lRetVal_en = E_OK;
                lControllerState_p->ChannelMode = CANIF_TX_OFFLINE;
            }
            break;

        default:
            break;
   }
   return(lRetVal_en);
}

FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(
        VAR(uint8,                    AUTOMATIC)                  ControllerId
   ,  P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr
){
   P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;
    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
    *ControllerModePtr = lControllerState_p->DeviceMode;
    return E_OK;
}

FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(
   VAR(uint8, AUTOMATIC) ControllerId
){
   P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;
   P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) lCallBackPtr_p;
   lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   lCallBackPtr_p = &CanIf_Callback;
   SchM_Enter_CanIf_ControllerState();
   if(lControllerState_p->DeviceMode != CANIF_CS_UNINIT){
        lControllerState_p->DeviceMode = CANIF_CS_STOPPED;
   }
   lControllerState_p->ChannelMode = CANIF_TX_OFFLINE;
   SchM_Exit_CanIf_ControllerState();
   if(lCallBackPtr_p->User_ControllerBusOff != NULL_PTR){
        lCallBackPtr_p->User_ControllerBusOff(ControllerId);
   }
}

FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication(
      VAR(uint8,                    AUTOMATIC) ControllerId
   ,  VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
){
     P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;
   P2CONST(CanIf_CallbackFuncType,    AUTOMATIC, AUTOMATIC) lCallBackPtr_p;
   lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   lCallBackPtr_p =  &CanIf_Callback;
   if(ControllerMode != CANIF_CS_UNINIT){
        lControllerState_p->DeviceMode = ControllerMode;
   }
   if(lCallBackPtr_p->User_ControllerModeIndication != NULL_PTR){
      lCallBackPtr_p->User_ControllerModeIndication(ControllerId, ControllerMode);
   }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
