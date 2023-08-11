
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
 #include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

 #define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_DcmGetRxPermission (
		Dcm_ProtocolType ProtocolId,
		PduIdType DcmRxPduId,
		const PduInfoType * info,
		PduLengthType TpSduLength)
{
	Std_ReturnType retVal = E_OK;
	

	
	
	
	
		(void)(ProtocolId);
		(void)(DcmRxPduId);
		(void)(TpSduLength);
		(void)(info);
		return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
