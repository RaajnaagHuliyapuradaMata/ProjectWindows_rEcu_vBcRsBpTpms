
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Seca_Inf.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayForPowerOn(
                                                            VAR(uint8,AUTOMATIC) SecurityLevel,
                                                            VAR(uint8,AUTOMATIC) Delaycount,
                                                            VAR(uint32,AUTOMATIC) DelayTime
                                                                )
{

    (void)(SecurityLevel);
    (void)(Delaycount);

    return (DelayTime);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
