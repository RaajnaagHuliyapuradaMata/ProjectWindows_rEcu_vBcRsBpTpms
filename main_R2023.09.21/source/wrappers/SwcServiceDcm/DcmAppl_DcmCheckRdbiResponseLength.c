#include "Std_Types.hpp"

#include "DcmDspUds_Rdbi_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckRdbiResponseLength(
                                                    VAR(uint32,AUTOMATIC) dataTotalRespLength_u32
   ,     VAR(uint16,AUTOMATIC) dataNumOfDids_u16
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_APPL_DATA) ErrorCode
){
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
    *ErrorCode= 0;
    (void)dataTotalRespLength_u32;
    (void)dataNumOfDids_u16;
    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
