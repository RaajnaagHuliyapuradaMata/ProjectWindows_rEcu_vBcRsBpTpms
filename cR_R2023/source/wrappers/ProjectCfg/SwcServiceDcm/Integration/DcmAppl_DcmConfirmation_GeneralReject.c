
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation_GeneralReject (
                                                                VAR(Dcm_IdContextType,AUTOMATIC) idContext,
                                                                VAR(PduIdType,AUTOMATIC) dcmRxPduId,
                                                                VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                                )
{

    (void)(status);
    (void)(dcmRxPduId);
    (void)(idContext);

}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
