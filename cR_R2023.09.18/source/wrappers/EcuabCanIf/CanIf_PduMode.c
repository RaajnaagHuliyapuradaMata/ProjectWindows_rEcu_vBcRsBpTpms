#include "Std_Types.hpp"

#include "CanIf_Cfg.hpp"
#include "CfgEcuabCanIf.hpp"
#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode(
      VAR(uint8,     AUTOMATIC) ControllerId
   ,  VAR(CanIf_PduModeType, AUTOMATIC) PduModeRequest
){
     VAR(Std_ReturnType,     AUTOMATIC) lRetVal_en         = E_NOT_OK;
   P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

   if(
         lControllerState_p->DeviceMode
      != CANIF_CS_STARTED
   ){
      lRetVal_en = E_NOT_OK;
   }
   else{
      lControllerState_p->ChannelMode = PduModeRequest;
      lRetVal_en = E_OK;
   }
   return(lRetVal_en);
}

FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetPduMode(
        VAR(uint8,     AUTOMATIC                 ) ControllerId
   ,  P2VAR(CanIf_PduModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr
){
   P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
   *PduModePtr = lControllerState_p->ChannelMode;
   return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
