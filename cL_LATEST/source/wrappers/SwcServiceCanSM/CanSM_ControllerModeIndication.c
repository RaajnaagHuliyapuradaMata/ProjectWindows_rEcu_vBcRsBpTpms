#include "CanSM_Prv.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
void CanSM_ControllerModeIndication(uint8 ControllerId,CanIf_ControllerModeType ControllerMode){
         uint8                  network_indx_u8;
         uint8_least            CanSM_ControllerId_u8;
         uint8_least            CanSM_Ctrl_index_u8;
         uint8                  CanSM_Controller_Counter_u8;
   const CanSM_NetworkConf_tst* CanSM_NetworkConf_ps;

#if(CANSM_DEV_ERROR_DETECT != STD_OFF)
   CanSM_NetworkModeStateType_ten CurNwMode_Temp_uo;
#endif

   CanSM_Controller_Counter_u8 =  CANSM_ZERO;

   CANSM_REPORT_ERROR((ControllerId >= CANSM_NUM_CAN_CONTROLLERS)
   ,                      (uint8)CANSM_CTRLMODEINDICATION_SID
   ,                      (uint8)CANSM_E_PARAM_CONTROLLER)

   CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED)
   ,                          ((uint8)CANSM_CTRLMODEINDICATION_SID)
   ,                          ((uint8)CANSM_E_UNINIT)
                           )
   network_indx_u8 = (uint8)CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_NetworktoCtrlConf_pcu8[ControllerId];
   CANSM_REPORT_ERROR((network_indx_u8 == CANSM_INVALID_ID), (uint8)CANSM_CTRLMODEINDICATION_SID
   ,           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)
   CanSM_NetworkConf_ps = &CanSM_Network_pcst[network_indx_u8];

#if(CANSM_DEV_ERROR_DETECT != STD_OFF)
   CurNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_u8];
#endif

   CANSM_REPORT_ERROR((CANSM_BSM_S_NOT_INITIALIZED == CurNwMode_Temp_uo)
   ,                          ((uint8)CANSM_CTRLMODEINDICATION_SID)
   ,                          ((uint8)CANSM_E_UNINIT)
                           )

   CanSM_ControllerIndications_ab[ControllerId] = TRUE;
   CanSM_ControllerId_u8 = ControllerId;
   if(ControllerMode==CANIF_CS_STOPPED){
        CanSM_ControllerState_en[CanSM_ControllerId_u8]=CANSM_ControllerState_STOPPED;
   }
   if(ControllerMode==CANIF_CS_STARTED){
        CanSM_ControllerState_en[CanSM_ControllerId_u8]=CANSM_ControllerState_STARTED;
   }
   if(ControllerMode==CANIF_CS_SLEEP){
        CanSM_ControllerState_en[CanSM_ControllerId_u8]=CANSM_ControllerState_SLEEP;
   }
   if(CanSM_NetworkConf_ps->SizeofController_u8 > 1u){
        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++){
            CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
            if(CanSM_ControllerIndications_ab[CanSM_ControllerId_u8] == TRUE){
                CanSM_Controller_Counter_u8++ ;
            }
        }
        if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 ){
            CanSM_Ctrl_ModeInd_ab[network_indx_u8] = TRUE;
            for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++){
                CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                CanSM_ControllerIndications_ab[CanSM_ControllerId_u8] = FALSE;
            }
        }
   }
   else{
        CanSM_Ctrl_ModeInd_ab[network_indx_u8] = TRUE;
        CanSM_ControllerIndications_ab[ControllerId] = FALSE;
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
