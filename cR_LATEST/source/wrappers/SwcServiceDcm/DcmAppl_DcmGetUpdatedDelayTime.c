#include "Std_Types.hpp"

#include "DcmDspUds_Seca_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayTime(
   VAR(uint8,AUTOMATIC) SecurityLevel
   ,     VAR(uint8,AUTOMATIC) Delaycount
   ,     VAR(uint32,AUTOMATIC) DelayTime
){
    (void)(SecurityLevel);
    (void)(Delaycount);
    return (DelayTime);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
