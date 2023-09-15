#include "Std_Types.hpp"

#include "DcmDspUds_Wdbi_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckWDBIReqLen(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint32,AUTOMATIC) dataReqLen_u32)
{
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
    (void)nrDID_u16;
    (void)dataReqLen_u32;
    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
