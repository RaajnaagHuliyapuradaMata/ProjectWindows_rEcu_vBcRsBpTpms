
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

 #include "DcmCore_DslDsd_Inf.h"

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRxPermission (
		VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolId,
		VAR(PduIdType, AUTOMATIC) DcmRxPduId,
		P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
		VAR(PduLengthType, AUTOMATIC) TpSduLength)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	

	
	
	
	
		(void)(ProtocolId);
		(void)(DcmRxPduId);
		(void)(TpSduLength);
		(void)(info);
		return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
