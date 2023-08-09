
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_ManufacturerNotification (
                                              VAR(uint8,AUTOMATIC) SID,
                                              CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
                                              VAR(PduLengthType,AUTOMATIC)RequestLength,
                                              VAR(uint8,AUTOMATIC) RequestType,
                                              VAR(PduIdType,AUTOMATIC) DcmRxPduId,
                                              VAR(uint16,AUTOMATIC) SourceAddress,
                                              P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) adrMsgContext_pcst,
                                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                  )
{

    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	(void)(RequestData);
    (void)(SID);
    (void)(RequestLength);
    (void)(RequestType);
    (void)(DcmRxPduId);
    (void)(SourceAddress);

	

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

