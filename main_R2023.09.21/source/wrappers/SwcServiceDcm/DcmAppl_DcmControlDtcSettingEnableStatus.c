#include "Std_Types.hpp"

#include "DcmDspUds_Cdtcs_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (void, DCM_APPL_CODE) DcmAppl_DcmControlDtcSettingEnableStatus(VAR(boolean,AUTOMATIC) ControlDtcSettingEnableStatus)
{
   (void)(ControlDtcSettingEnableStatus);

}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
