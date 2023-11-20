#include "Std_Types.hpp"

#include "CanSM_Prv.hpp"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(VAR(uint8, AUTOMATIC) TransceiverId){
   VAR(uint8_least,     AUTOMATIC) network_indx_uo;
   VAR(boolean,     AUTOMATIC) CanSM_TrcvConfigd_b = FALSE;
   VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurrNwMode_Temp_uo;
   VAR(uint8,     AUTOMATIC) CanSM_networkHandle_u8;

   for(
      network_indx_uo = 0;
      network_indx_uo < CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8;
      network_indx_uo ++
   ){
      CurrNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_uo];
      if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8 == TransceiverId){
         CanSM_TrcvConfigd_b = TRUE;
         CanSM_networkHandle_u8 = CanSM_Network_pcst[network_indx_uo].ComM_channelId_uo;
         CanNm_ConfirmPnAvailability((NetworkHandleType)CanSM_networkHandle_u8);
         break;
      }
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif
