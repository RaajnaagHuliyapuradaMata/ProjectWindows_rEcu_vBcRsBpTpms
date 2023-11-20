#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!= DCM_CFG_OFF)))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_CheckEncryptionCompressionMethod(
                                            VAR(uint8,AUTOMATIC) Sid_u8
   ,     VAR(uint8,AUTOMATIC) CompressionMethod
   ,     VAR(uint8,AUTOMATIC) EncryptionMethod )
{
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;

    (void)Sid_u8;
    (void)CompressionMethod;
    (void)EncryptionMethod;
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
