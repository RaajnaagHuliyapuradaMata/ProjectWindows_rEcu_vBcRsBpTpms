#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmMsgAuthenticationX.hpp"
#include "CanManagerX.hpp"

#if(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmNotification (
   VAR(uint8,AUTOMATIC) SID
   ,     CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData
   ,     VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC) RequestLength
   ,     VAR(uint8,AUTOMATIC) RequestType
   ,     VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmRxPduId
   ,     VAR(uint16,AUTOMATIC) SourceAddress
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
){
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
   uint8 ucMsgAuthenticationResult;
   CANMGR_ElongateCommTimeout(0);
   if(SID != 0x3E){
      ucMsgAuthenticationResult = DcmCheckMessageAuthentication(SID, RequestData, RequestLength);
      if(ucMsgAuthenticationResult == MSG_AUTH_SUCCESSFUL){
         if(Dcm_DsldMsgContext_st.reqDataLen > cSIZE_OF_HASH){
          Dcm_DsldMsgContext_st.reqDataLen -= cSIZE_OF_HASH;
        }
        *ErrorCode = 0;
        retVal = DCM_E_OK;
      }
      else if(ucMsgAuthenticationResult == MSG_NO_AUTH_NEEDED){
        *ErrorCode = 0;
        retVal = DCM_E_OK;
      }

      else{
        *ErrorCode = DCM_E_SECURITYACCESSDENIED;
        retVal = DCM_E_COMPARE_KEY_FAILED;
      }
   }
    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

