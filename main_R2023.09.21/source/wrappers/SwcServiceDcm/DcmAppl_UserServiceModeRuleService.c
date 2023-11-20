#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserServiceModeRuleService(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8,
   VAR(uint8,AUTOMATIC) Sid_u8){
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
   *Nrc_u8= 0x00;
   return (retVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

