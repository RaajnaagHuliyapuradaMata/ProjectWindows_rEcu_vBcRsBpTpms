
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#include "DcmMsgAuthenticationX.hpp"
#include "CanManagerX.hpp"

#if(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmNotification (
                                                uint8 SID
   ,                                               const uint8 * const RequestData
   ,                                               PduLengthType RequestLength
   ,                                               uint8 RequestType
   ,                                               PduIdType DcmRxPduId
   ,                                               uint16 SourceAddress
   ,                                               Dcm_NegativeResponseCodeType * ErrorCode
                                                         )
{
   Std_ReturnType retVal = E_OK;

    //(void)(RequestData);
    //(void)(SID);
    //(void)(RequestLength);
    //(void)(RequestType);
    //(void)(DcmRxPduId);
    //(void)(SourceAddress);

   uint8 ucMsgAuthenticationResult;

   CANMGR_ElongateCommTimeout(0);

   if(SID != 0x3E)
   {

      ucMsgAuthenticationResult = DcmCheckMessageAuthentication(SID, RequestData, RequestLength);

      if(ucMsgAuthenticationResult == MSG_AUTH_SUCCESSFUL)
      {

        if(Dcm_DsldMsgContext_st.reqDataLen > cSIZE_OF_HASH)
        {
          Dcm_DsldMsgContext_st.reqDataLen -= cSIZE_OF_HASH;
        }
        *ErrorCode = 0;
        retVal = DCM_E_OK;
      }

      else if(ucMsgAuthenticationResult == MSG_NO_AUTH_NEEDED)
      {
        *ErrorCode = 0;
        retVal = DCM_E_OK;
      }

      else //ucMsgAuthenticationResult == MSG_REJECTED
      {
        *ErrorCode = DCM_E_SECURITYACCESSDENIED;
        retVal = DCM_E_COMPARE_KEY_FAILED;
      }
   }

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

