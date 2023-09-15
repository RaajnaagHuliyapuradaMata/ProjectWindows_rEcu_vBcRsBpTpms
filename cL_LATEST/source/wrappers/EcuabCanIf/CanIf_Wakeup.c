#include "CanIf_Prv.hpp"

#if(CANIF_WAKEUP_SUPPORT == STD_ON)&&(CANIF_CFG_TRCV_WAKEUP_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
Std_ReturnType CanIf_CheckWakeup(
   Type_SwcServiceEcuM_tSourceWakeup WakeupSource
){
   const CanIf_Wakeup*              WkpEvent_tpcst   = CanIf_WakeupList_tacst;
         CanIf_ControllerStateType* lControllerState_p;
         boolean                    WkpDeviceFound_b = FALSE;
         uint8_least                LoopVar_tqu8;
         uint8_least                WakeupId_tqu8    = 0;
         Std_ReturnType             Ret_trcv_t       = E_NOT_OK;

   for(
      LoopVar_tqu8 = 0u;
      LoopVar_tqu8 < CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT;
      LoopVar_tqu8 ++
   ){
      if(
            (WkpEvent_tpcst + LoopVar_tqu8)->WakeupSourceId
         == WakeupSource
      ){
         WkpDeviceFound_b = TRUE;
         WakeupId_tqu8    = LoopVar_tqu8;
         break;
      }
   }

   lControllerState_p = CanIf_Lok_ControllerState_ast + (WkpEvent_tpcst +WakeupId_tqu8)->ControllerId;

   if(
         (
               (
                     (
                           lControllerState_p->Ctrl_Pdu_mode
                        &  BIT_MASK_PDU_MODE
                     )
                  >> CANIF_Ctrl_BIT_SHIFT
               )
            == (uint8)CANIF_CS_SLEEP
         )
      && (
               WkpDeviceFound_b
            == TRUE
         )
   ){
      Ret_trcv_t = CanTrcv_CheckWakeup(
         (WkpEvent_tpcst + LoopVar_tqu8)->TransceiverId
      );
   }
   return Ret_trcv_t;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

