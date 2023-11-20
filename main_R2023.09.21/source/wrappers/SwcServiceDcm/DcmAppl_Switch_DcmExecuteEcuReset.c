#include "Std_Types.hpp"

#include "SysManagerX.hpp"
#include "DcmCore_DslDsd_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_APPL_CODE) DcmAppl_Switch_DcmExecuteEcuReset(
   VAR(uint8,AUTOMATIC) ResetType_u8){
     (void) ResetType_u8;
  SYSMGR_PrepareReset(0);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
