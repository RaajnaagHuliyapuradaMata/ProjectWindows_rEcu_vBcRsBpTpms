
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
     (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) && \
     (DCM_ROE_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void DcmAppl_DcmClearRoeEventInformation (void)
{
    #if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

    //Dcm_DslDsd_ResetROEScheduler();
    #endif

	
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
