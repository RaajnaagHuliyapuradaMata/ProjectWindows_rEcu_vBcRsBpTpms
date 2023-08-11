
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_StopProtocol(ProtocolID);
#else

    (void)(ProtocolID);
#endif

    return(E_OK);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"