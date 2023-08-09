
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED == DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void, DCM_APPL_CODE) DcmAppl_DcmGetP2Timings(
                                        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrP2Timing_pu32,
                                        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrP2StarTiming_pu32,
                                        VAR(Dcm_SesCtrlType, AUTOMATIC) dataSessionId_u8
                                     )
{
	
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
