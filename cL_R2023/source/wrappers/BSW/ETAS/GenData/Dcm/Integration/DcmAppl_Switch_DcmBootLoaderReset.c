
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "SysManagerX.h"
#include "WrapNv_Cfg.h"
#include "MemConversion.h"

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

 void DcmAppl_Switch_DcmBootLoaderReset(void)
 {
	

	 vuint8 nvBuffer[3];
// #if 0
  vuint8 progAttempts;
  // vuint8 nvBuffer[3];
  tFblResult status;

  status = (tFblResult)ApplFblNvReadProgAttemptsCounter(nvBuffer);
  progAttempts = (vuint8)FblMemGetInteger(kEepSizeProgAttemptsCounter, nvBuffer);

  if (status == kFblOk)
  {

    progAttempts = FblInvert8Bit(progAttempts);
    progAttempts++;
    progAttempts = FblInvert8Bit(progAttempts);

    FblMemSetInteger(kEepSizeProgAttemptsCounter, progAttempts, nvBuffer);
    status = (tFblResult)ApplFblNvWriteProgAttemptsCounter(nvBuffer);
  }
// #endif

  nvBuffer[0] = kEepFblReprogram;
  ApplFblNvWriteProgReqFlag(nvBuffer);
  nvBuffer[0] = RESET_RESPONSE_ECURESET_REQUIRED; //RESET_RESPONSE_SDS_REQUIRED; //  ;
  ApplFblNvWriteResetResponseFlag(nvBuffer);

  // SYSMGR_PrepareBootloaderJump(0);  // KF integration code. let's try to jump to the bootloader via StartFbl function. LMC has no 11 4C.
  SYSMGR_PrepareReset(0); // KF integration code: see above line

 }
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
