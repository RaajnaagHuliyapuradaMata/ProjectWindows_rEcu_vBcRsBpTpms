
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Roe_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
FUNC(void,DCMAPPL_CODE) DcmAppl_DcmStoreROEcycleCounter(VAR(uint8,AUTOMATIC) RoeeventID,
                                                                  VAR(uint8,AUTOMATIC) CycleValue
                                                                  )
{

    (void)(RoeeventID);
    (void)(CycleValue);

	
    return ;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
#endif
