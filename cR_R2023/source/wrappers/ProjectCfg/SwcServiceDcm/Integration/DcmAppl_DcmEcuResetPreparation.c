
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Er_Inf.h"
#include "DcmAppl.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmEcuResetPreparation(
                                                                VAR(uint8,AUTOMATIC) ResetType,
                                                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                )
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	  *ErrorCode = 0x00;
    (void)(ResetType);

	

    return retVal;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
