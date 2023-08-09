#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void, DCM_APPL_CODE) DcmAppl_DcmGetRemainingResponseLength(
                                        VAR(uint8, AUTOMATIC) dataSID_u8,
                                        P2VAR(PduLengthType,AUTOMATIC,DCM_INTERN_DATA) dataResponseLength
                                        )
{

	(void)dataSID_u8;
	*dataResponseLength = 0;
	
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
