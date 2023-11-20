#include "Std_Types.hpp"

#include "DcmDspUds_Seca_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSecaValidKey(
   VAR(uint8,AUTOMATIC) SecTabIdx){
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
    (void)(SecTabIdx);
    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
