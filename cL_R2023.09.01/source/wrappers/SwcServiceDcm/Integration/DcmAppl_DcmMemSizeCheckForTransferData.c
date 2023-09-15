
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_TransferData_Inf.hpp"
#include "Rte_Dcm.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void DcmAppl_DcmMemSizeCheckForTransferData    (
                                                    uint8 dataCompressionMethod_u8
   ,                                                   uint8 dataMemoryId_u8
   ,                                                   uint32 dataTransferRequestParameterRecordLength_u32
   ,                                                   Dcm_TrasferDirection_en dataTransferDirection_ten
   ,                                                   Dcm_NegativeResponseCodeType * dataErrorCode_u8
                                                    )
{
    (void)dataCompressionMethod_u8;
    (void)dataMemoryId_u8;
    (void)dataTransferRequestParameterRecordLength_u32;
    (void)dataTransferDirection_ten;
    *dataErrorCode_u8 = 0;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

