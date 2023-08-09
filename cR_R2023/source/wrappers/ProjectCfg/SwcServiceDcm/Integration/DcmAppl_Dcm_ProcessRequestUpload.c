
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestUpload(
                                            VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                            VAR(uint8,AUTOMATIC) DataFormatIdentifier,
                                            VAR(uint32,AUTOMATIC) MemoryAddress,
                                            VAR(uint32,AUTOMATIC) MemorySize,
                                            P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) BlockLength,
                                            P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode)
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
#include "Dcm_Cfg_MemMap.h"
#endif
