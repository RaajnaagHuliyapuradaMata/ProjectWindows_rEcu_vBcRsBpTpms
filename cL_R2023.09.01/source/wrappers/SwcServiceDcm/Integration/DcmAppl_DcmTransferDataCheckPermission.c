
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_TransferData_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_Dcm_CheckPermissionForTransferData(
                                                    uint8 BlockSequenceCounter
   ,                                                   uint8 memoryId
   ,                                                   uint32 memoryAddress
   ,                                                   uint32 * memorySize
   ,                                                   uint8 * TransferRequestParameterRecord
   ,                                                   uint32 TransferRequestParameterRecordLength
   ,                                                   Dcm_TrasferDirection_en dataTransferDirection_ten
   ,                                                   Dcm_NegativeResponseCodeType * ErrorCode
                                                    )
{
   uint8 dataReturnValue_u8;
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
#include "Dcm_Cfg_MemMap.hpp"
#endif

