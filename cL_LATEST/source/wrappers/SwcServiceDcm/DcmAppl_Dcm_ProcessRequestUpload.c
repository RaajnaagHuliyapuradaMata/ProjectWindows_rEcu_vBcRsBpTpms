
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_Dcm_ProcessRequestUpload(
                                            Dcm_OpStatusType OpStatus
   ,                                           uint8 DataFormatIdentifier
   ,                                           uint32 MemoryAddress
   ,                                           uint32 MemorySize
   ,                                           uint32 * BlockLength
   ,                                           Dcm_NegativeResponseCodeType * ErrorCode)
{
    Std_ReturnType retVal_u8;
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
