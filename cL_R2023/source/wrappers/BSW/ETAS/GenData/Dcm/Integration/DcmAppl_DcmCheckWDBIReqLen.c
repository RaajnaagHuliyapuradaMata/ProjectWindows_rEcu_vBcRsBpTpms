
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Wdbi_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_DcmCheckWDBIReqLen(uint16 nrDID_u16, uint32 dataReqLen_u32)
{

    Std_ReturnType retVal = E_OK;
    (void)nrDID_u16;
    (void)dataReqLen_u32;

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
