
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_DcmStartProtocol(Dcm_ProtocolType ProtocolID)
{
Std_ReturnType retVal;
retVal = E_OK;
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_StartProtocol(ProtocolID);
#else

    (void)(ProtocolID);
#endif
	
return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

