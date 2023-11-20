#include "Std_Types.hpp"

#include "DcmDspUds_TransferData_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmMemSizeCheckForTransferData(
   VAR(uint8,AUTOMATIC) dataCompressionMethod_u8
   ,     VAR(uint8,AUTOMATIC) dataMemoryId_u8
   ,     VAR(uint32,AUTOMATIC) dataTransferRequestParameterRecordLength_u32
   ,     VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
){
    (void)dataCompressionMethod_u8;
    (void)dataMemoryId_u8;
    (void)dataTransferRequestParameterRecordLength_u32;
    (void)dataTransferDirection_ten;
    *dataErrorCode_u8 = 0;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

