
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Dcm_RestoreDddiReturn_ten,DCM_APPL_CODE) DcmAppl_DcmReadDddiFromNvM (P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) dataDefinitionOfDDDI,
                                                                          VAR (uint16,AUTOMATIC) dataDddId_u16)
{

    VAR (Dcm_RestoreDddiReturn_ten,AUTOMATIC) returnValue = DCM_DDDI_READ_OK;
    (void)dataDefinitionOfDDDI;
    (void)dataDddId_u16;

    return returnValue;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
