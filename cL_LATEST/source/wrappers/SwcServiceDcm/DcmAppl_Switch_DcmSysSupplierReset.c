
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

//RST integration code start
#include "SysManagerX.hpp"
//RST integration code end

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void DcmAppl_Switch_DcmSysSupplierReset(void){

  //RST integration code start

  SYSMGR_PrepareSmartTesterJump(50); //RST Debug: warte 100ms um evtl. noch laufende Iniitalisierungen (Atmel) abschließen zu können.
  //RST integration code end
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
