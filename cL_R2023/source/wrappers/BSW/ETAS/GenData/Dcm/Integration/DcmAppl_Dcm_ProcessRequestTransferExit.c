
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_Dcm_ProcessRequestTransferExit(
                                                                Dcm_OpStatusType OpStatus,
                                                                const uint8 * transferRequestParameterRecord,
                                                                uint32 transferRequestParameterRecordSize,
                                                                uint8 * transferResponseParameterRecord,
                                                                uint32 * transferResponseParameterRecordSize,
                                                                Dcm_NegativeResponseCodeType * ErrorCode)

{
    Std_ReturnType retVal_u8;
    retVal_u8 = E_OK;

    (void)OpStatus;
    (void)transferRequestParameterRecord;
    (void)transferRequestParameterRecordSize;
    (void)transferResponseParameterRecord;
    (void)transferResponseParameterRecordSize;
    (void)ErrorCode;
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
