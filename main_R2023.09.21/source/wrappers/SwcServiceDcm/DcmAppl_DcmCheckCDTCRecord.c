#include "Std_Types.hpp"

#include "DcmDspUds_Cdtcs_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckCDTCRecord (
                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlOptionRecord
   ,     VAR(uint8,AUTOMATIC) Length
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
){
   VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
   (void)ControlOptionRecord;
    (void)Length;
    *ErrorCode = 0x00;
    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

