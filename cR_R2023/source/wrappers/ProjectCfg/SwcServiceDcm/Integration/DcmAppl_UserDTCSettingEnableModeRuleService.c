
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Cdtcs_Inf.h"

#if (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserDTCSettingEnableModeRuleService(void)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

