#include "CanSM_Prv.hpp"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"

FUNC(void, CANSM_CODE) CanSM_ClearTrcvWufFlagIndication(VAR(uint8, AUTOMATIC) Transceiver){
   VAR(uint8_least,                    AUTOMATIC) network_indx_uo;
   VAR(boolean,                        AUTOMATIC) CanSM_st_TrcvConfigd = FALSE;
   VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurrNwMode_Temp;

   CANSM_REPORT_ERROR(
         (CanSM_Init_ab == (boolean)CANSM_UNINITED)
      ,  ((uint8)CANSM_CLEARTRCVWUFFLAGIND_SID)
      ,  ((uint8)CANSM_E_UNINIT)
   )
   for(
      network_indx_uo = 0;
      network_indx_uo < CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8;
      network_indx_uo ++
   ){
      CurrNwMode_Temp = CanSM_CurrNw_Mode_en[network_indx_uo];
      if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8 == Transceiver){
         CANSM_REPORT_ERROR(
               (CurrNwMode_Temp == CANSM_BSM_S_NOT_INITIALIZED)
            ,  ((uint8)CANSM_CLEARTRCVWUFFLAGIND_SID)
            ,  ((uint8)CANSM_E_UNINIT)
         )
         CanSM_PN_Substate_Ind_ab[network_indx_uo] = TRUE;
         CanSM_st_TrcvConfigd = TRUE;
         break;
      }
   }
   if(CanSM_st_TrcvConfigd == FALSE){
      CANSM_REPORT_ERROR(
            (CanSM_Init_ab == (boolean)CANSM_INITED)
         ,  (CANSM_CLEARTRCVWUFFLAGIND_SID)
         ,  (CANSM_E_PARAM_TRANSCEIVER)
      )
   }
}

#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif
