
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Rc_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_UserRIDModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 rid_u16, uint8 subfunction_u8)
{
   Std_ReturnType retVal_u8 = E_OK;
   *Nrc_u8= 0x00;

   return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

