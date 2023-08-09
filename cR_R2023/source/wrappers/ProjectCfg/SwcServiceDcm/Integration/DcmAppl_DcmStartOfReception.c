
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void,DCM_APPL_CODE) DcmAppl_StartOfReception(VAR(Dcm_IdContextType,AUTOMATIC) idContext ,
                                                     VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                     VAR(PduLengthType, AUTOMATIC) RequestLength,
                                                     VAR(Dcm_MsgType, AUTOMATIC) RxBufferPtr)
{
    (void)idContext;
    (void)DcmRxPduId;
    (void)RequestLength;
    (void)RxBufferPtr;

}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

