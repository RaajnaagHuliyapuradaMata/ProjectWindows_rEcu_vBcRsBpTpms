
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void,DCM_APPL_CODE) DcmAppl_DcmGetNRCForMinLengthCheck (
                                    VAR(Dcm_ProtocolType, AUTOMATIC) dataProtocolId_u8,
				    VAR(uint8,AUTOMATIC) dataSid_u8,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
                                                                )
{
	(void)dataProtocolId_u8;
	(void)dataSid_u8;
	*dataErrorCode_u8 =0x00;

	

}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
