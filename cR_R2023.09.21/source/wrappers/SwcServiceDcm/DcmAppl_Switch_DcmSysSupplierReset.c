#include "Std_Types.hpp"

#include "SysManagerX.hpp"
#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_APPL_CODE)  DcmAppl_Switch_DcmSysSupplierReset(void){
   SYSMGR_PrepareSmartTesterJump(
      50);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
