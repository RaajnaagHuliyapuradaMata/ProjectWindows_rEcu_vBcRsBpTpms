#include "Std_Types.hpp"

#include "CanIf_Cfg.hpp"
#include "CfgEcuabCanIf.hpp"
#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
Std_ReturnType CanIf_SetPduMode(
      uint8             ControllerId
   ,  Type_EcuabCanIf_eModePdu PduModeRequest
){
   CanIf_ControllerStateType* lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   Std_ReturnType             lRetVal_en = E_NOT_OK;
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
   ,   Type_EcuabCanIf_eModePdu* PduModePtr
){
   CanIf_ControllerStateType* lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   *PduModePtr = (Type_EcuabCanIf_eModePdu)((lControllerState_p->Ctrl_Pdu_mode) & BIT_MASK_CTRL_MODE);
   return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
