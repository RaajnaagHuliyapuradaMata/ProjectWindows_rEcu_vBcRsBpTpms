
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )

#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

boolean DcmAppl_DcmIsComModeDefault( uint8 NetworkID )
{

	boolean retVal = TRUE;
	(void)(NetworkID);

	

	return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#endif
