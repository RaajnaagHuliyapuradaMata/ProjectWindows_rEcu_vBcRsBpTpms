#include "Std_Types.hpp"

#include "CanIf_Cfg.hpp"
#include "CfgEcuabCanIf.hpp"
#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
Std_ReturnType CanIf_SetPduMode(
      uint8             ControllerId
   ,  CanIf_PduModeType PduModeRequest
){
   CanIf_ControllerStateType* lControllerState_p;
   Std_ReturnType             lRetVal_en = E_NOT_OK;

   if(
         (CANIF_OFFLINE    != PduModeRequest)
      && (CANIF_TX_OFFLINE != PduModeRequest)
      && (CANIF_ONLINE     != PduModeRequest)
   ){
      CANIF_DET_REPORT_ERROR_NO_CONDITON((CANIF_SET_PDU_MODE_SID), (CANIF_E_PARAM_PDU_MODE))
   }
   lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

   if(
         (
               (
                     lControllerState_p->Ctrl_Pdu_mode
                  &  BIT_MASK_PDU_MODE
               )
            >> CANIF_Ctrl_BIT_SHIFT
         )
      != (uint8)CANIF_CS_STARTED
   ){
      lRetVal_en = E_NOT_OK;
   }
   else{
      lControllerState_p->Ctrl_Pdu_mode = ((uint8)PduModeRequest)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE);
      lRetVal_en = E_OK;
   }
   return lRetVal_en;
}

Std_ReturnType CanIf_GetPduMode(
       uint8              ControllerId
   ,   CanIf_PduModeType* PduModePtr
){
   CanIf_ControllerStateType* lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   *PduModePtr = (CanIf_PduModeType)((lControllerState_p->Ctrl_Pdu_mode)& BIT_MASK_CTRL_MODE);
   return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
