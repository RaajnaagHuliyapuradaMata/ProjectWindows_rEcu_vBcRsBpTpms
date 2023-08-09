
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Er_Inf.h"

#include "SysManagerX.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void,DCM_APPL_CODE)  DcmAppl_Switch_DcmEcuReset(VAR(uint8,AUTOMATIC) ResetMode)
{
  (void)ResetMode;
	

}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
