#include "Std_Types.hpp"

#include "DcmDspUds_Cdtcs_Inf.hpp"

#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserDTCSettingEnableModeRuleService(void){
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
   return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

