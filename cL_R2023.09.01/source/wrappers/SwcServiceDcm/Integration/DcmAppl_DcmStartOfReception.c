
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void DcmAppl_StartOfReception(Dcm_IdContextType idContext 
   ,                                                    PduIdType DcmRxPduId
   ,                                                    PduLengthType RequestLength
   ,                                                    Dcm_MsgType RxBufferPtr)
{
    (void)idContext;
    (void)DcmRxPduId;
    (void)RequestLength;
    (void)RxBufferPtr;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

