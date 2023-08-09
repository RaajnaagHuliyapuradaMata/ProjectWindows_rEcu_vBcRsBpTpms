
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmWriteOrClearDddiInNvM (P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) dataDefinitionOfDDDI,
                                                                     VAR (uint16,AUTOMATIC) dataDddId_u16,
                                                                     VAR (Dcm_OpStatusType,AUTOMATIC) Dcm_StoreDDDiOpstatus_u8,
                                                                     VAR (Dcm_DddiWriteOrClear_ten,AUTOMATIC) Dcm_DddiWriteOrClear_en)
                                                                     {

    VAR (Std_ReturnType,AUTOMATIC) returnValue = E_OK;
    (void)Dcm_StoreDDDiOpstatus_u8;
    (void)dataDefinitionOfDDDI;
    (void)dataDddId_u16;
    (void)Dcm_DddiWriteOrClear_en;

    return returnValue;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
