
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_TransferData_Inf.h"

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_CheckPermissionForTransferData(
                                                    VAR(uint8,AUTOMATIC) BlockSequenceCounter,
                                                    VAR(uint8,AUTOMATIC) memoryId,
                                                    VAR(uint32,AUTOMATIC) memoryAddress,
                                                    P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) memorySize,
                                                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) TransferRequestParameterRecord,
                                                    VAR(uint32,AUTOMATIC) TransferRequestParameterRecordLength,
                                                    VAR(Dcm_TrasferDirection_en,AUTOMATIC) dataTransferDirection_ten,
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                    )
{
    VAR(uint8,AUTOMATIC) dataReturnValue_u8;
    dataReturnValue_u8 = E_OK;
    (void)BlockSequenceCounter;
    (void)memoryId;
    (void)memoryAddress;
    (void)memorySize;
    (void)TransferRequestParameterRecord;
    (void)TransferRequestParameterRecordLength;
    (void)dataTransferDirection_ten;
    (void)ErrorCode;

    return dataReturnValue_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

