#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "CanManagerX.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (void, DCM_APPL_CODE) DcmAppl_DcmSwitchCommunicationControl(
   VAR(uint8,DCM_VAR) NetworkID,
   Dcm_CommunicationModeType RequestedMode){
   switch(RequestedMode){
   case DCM_ENABLE_RX_TX_NORM:
      CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Rx);
      CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx);
   break;

   case DCM_DISABLE_RX_TX_NORMAL:
      CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Rx);
      CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);
   break;

   case DCM_ENABLE_RX_DISABLE_TX_NORM:
      CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Rx);
      CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);
   break;

   case DCM_DISABLE_RX_ENABLE_TX_NORM:
      CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Rx);
      CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx);
   break;

    default:
   break;
  }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
