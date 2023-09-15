
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

 #include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmGetRxPermission (
   	Dcm_ProtocolType ProtocolId
   ,  	Type_SwcServiceCom_tIdPdu DcmRxPduId
   ,  	const Type_SwcServiceCom_stInfoPdu * info
   ,  	Type_SwcServiceCom_tLengthPdu TpSduLength)
{
   Std_ReturnType retVal = E_OK;

   	(void)(ProtocolId);
   	(void)(DcmRxPduId);
   	(void)(TpSduLength);
   	(void)(info);
   	return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
