#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestDownload(
                                            VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) DataFormatIdentifier
   ,     VAR(uint32,AUTOMATIC) MemoryAddress
   ,     VAR(uint32,AUTOMATIC) MemorySize
   ,     P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) BlockLength
   ,     P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode)
{
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;
    (void)OpStatus;
    (void)DataFormatIdentifier;
    (void)MemoryAddress;
    (void)MemorySize;
    (void)BlockLength;
    (void)ErrorCode;
    return retVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
