
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmWriteOrClearDddiInNvM (const Dcm_DddiMainConfig_tst * dataDefinitionOfDDDI
   ,                                                                    uint16 dataDddId_u16
   ,                                                                    Dcm_OpStatusType Dcm_StoreDDDiOpstatus_u8
   ,                                                                    Dcm_DddiWriteOrClear_ten Dcm_DddiWriteOrClear_en)
                                                                     {

    Std_ReturnType returnValue = E_OK;
    (void)Dcm_StoreDDDiOpstatus_u8;
    (void)dataDefinitionOfDDDI;
    (void)dataDddId_u16;
    (void)Dcm_DddiWriteOrClear_en;

    return returnValue;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
