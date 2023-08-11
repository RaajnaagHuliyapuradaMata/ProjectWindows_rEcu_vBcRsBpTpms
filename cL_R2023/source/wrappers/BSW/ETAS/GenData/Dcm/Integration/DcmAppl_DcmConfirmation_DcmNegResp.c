
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_NR_CONF_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void DcmAppl_DcmConfirmation_DcmNegResp(
                                                        Dcm_IdContextType idContext,
                                                        PduIdType dcmRxPduId,
                                                        Dcm_ConfirmationStatusType status
                                                      )
{
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_Confirmation(idContext, dcmRxPduId, status);
#else

    (void)(status);
    (void)(dcmRxPduId);
    (void)(idContext);
#endif
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

