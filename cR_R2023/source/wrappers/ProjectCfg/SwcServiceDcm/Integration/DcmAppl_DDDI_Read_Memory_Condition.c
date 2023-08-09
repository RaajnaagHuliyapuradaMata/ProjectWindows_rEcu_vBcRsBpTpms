
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Dddi_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC (Std_ReturnType,DCM_APPL_CODE) DcmAppl_DDDI_Read_Memory_Condition (
    P2CONST (Dcm_DDDI_DEF_MEM_t,AUTOMATIC,DCM_INTERN_CONST) record,
    P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) NegRespCode
                                                                  )
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	*NegRespCode = 0;
	

    (void)(record);

	

    return retVal;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
