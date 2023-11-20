#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )
#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (boolean, DCM_APPL_CODE) DcmAppl_DcmIsComModeDefault(
   VAR(uint8,DCM_VAR) NetworkID){
   VAR(boolean,AUTOMATIC) retVal = TRUE;
   (void)(NetworkID);
   return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
