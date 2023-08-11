
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType Dcm_SetProgConditions(Dcm_OpStatusType OpStatus,
                                                        const Dcm_ProgConditionsType * ProgConditions)
{

	

	Std_ReturnType retVal = E_OK;
	
	return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
