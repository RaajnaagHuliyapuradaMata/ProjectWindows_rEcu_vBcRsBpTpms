#include "Std_Types.hpp"

#include "DcmDspUds_Uds_Inf.hpp"

#if(((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserDIDModeRuleService(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8,
   VAR(uint16,AUTOMATIC) did_u16,
   VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en){
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
   *Nrc_u8= 0x00;
   return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

