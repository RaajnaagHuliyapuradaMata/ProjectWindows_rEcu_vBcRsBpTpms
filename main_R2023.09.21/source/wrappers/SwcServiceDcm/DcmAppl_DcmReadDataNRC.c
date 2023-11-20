#include "Std_Types.hpp"

#include "DcmDspUds_Rdbi_Inf.hpp"

#if( (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmReadDataNRC(
   VAR(uint16,AUTOMATIC) Did,
   VAR(uint32,AUTOMATIC) DidSignalPosn,
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode){
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
   return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

