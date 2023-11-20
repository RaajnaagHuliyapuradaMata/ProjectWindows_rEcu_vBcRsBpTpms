#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRxPermission (
   	VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolId
   ,  VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) info
   ,  VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength)
{
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
   	(void)(ProtocolId);
   	(void)(DcmRxPduId);
   	(void)(TpSduLength);
   	(void)(info);
   	return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
