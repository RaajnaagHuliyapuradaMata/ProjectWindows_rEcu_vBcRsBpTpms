#include "Std_Types.hpp"

#include "CanSM_Prv.hpp"

#if(CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(VAR(uint8, AUTOMATIC) TransceiverId,VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode){
   VAR(uint8_least, AUTOMATIC)  network_indx_uo;
   VAR(boolean, AUTOMATIC)  CanSM_TrcvConfigd_b;

#if(CANSM_DEV_ERROR_DETECT != STD_OFF)
   VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurNwMode_Temp_uo;
#endif

   CanSM_TrcvConfigd_b = FALSE;
   (void)TransceiverMode;
   for(
      network_indx_uo = 0;
      network_indx_uo < CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8;
      network_indx_uo++
   ){
            if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8==TransceiverId){
#if(CANSM_DEV_ERROR_DETECT != STD_OFF)
                    CurNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_uo];
#endif
                    CanSM_Trcv_ModeInd_ab[network_indx_uo] = TRUE;
                    CanSM_TrcvConfigd_b = TRUE;
                    break;
                }
        }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif
