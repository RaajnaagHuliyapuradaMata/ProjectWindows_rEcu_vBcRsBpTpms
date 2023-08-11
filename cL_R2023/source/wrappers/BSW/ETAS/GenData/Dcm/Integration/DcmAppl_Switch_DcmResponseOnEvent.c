
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"

#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
 void DcmAppl_Switch_DcmResponseOnEvent(uint8 RoeEventId_u8 , Dcm_DspRoeEventState_ten RoeEventStatus_en)
 {
     (void)RoeEventId_u8;
     (void)RoeEventStatus_en;

 }

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
