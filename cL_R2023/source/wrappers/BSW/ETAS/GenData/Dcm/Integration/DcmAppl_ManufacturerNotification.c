
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_ManufacturerNotification (
                                              uint8 SID,
                                              const uint8 * const RequestData,
                                              PduLengthType RequestLength,
                                              uint8 RequestType,
                                              PduIdType DcmRxPduId,
                                              uint16 SourceAddress,
                                              Dcm_MsgContextType * adrMsgContext_pcst,
                                              Dcm_NegativeResponseCodeType * ErrorCode
                                                                  )
{

    Std_ReturnType retVal = E_OK;
	(void)(RequestData);
    (void)(SID);
    (void)(RequestLength);
    (void)(RequestType);
    (void)(DcmRxPduId);
    (void)(SourceAddress);

	

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

