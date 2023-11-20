#include "Std_Types.hpp"

#include "DcmDspUds_Wmba_Inf.hpp"
#include "DcmDspUds_Rmba_Inf.hpp"
#include "DcmDspUds_RequestUpload_Inf.hpp"
#include "DcmDspUds_RequestDownload_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Wmba_Priv.hpp"
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Rmba_Priv.hpp"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_RequestUpload_Priv.hpp"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_RequestDownload_Priv.hpp"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)   ||    \
   												   (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)  ||    \
                                                       (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)       ||    \
                                                       (DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_GetMemoryInfo(VAR   (uint8,AUTOMATIC) dataSize_u8
   ,    P2CONST (uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pcu8
   ,    P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrMemAddrLength_pu32)
{
   VAR(uint8,     AUTOMATIC) idxIndex_u8=0;
   VAR(uint32,     AUTOMATIC) tempResult_u32=0;
   VAR(uint32,     AUTOMATIC) dataMemAlFid_u32=0;
   do{
        tempResult_u32 = (uint32)(adrReqBuf_pcu8[idxIndex_u8]);
        tempResult_u32 <<= (uint32)((dataSize_u8-1)*8u);
        dataMemAlFid_u32 |= (uint32)(tempResult_u32);
   	dataSize_u8--;
   	idxIndex_u8++;
   }while(dataSize_u8!=0);
   *adrMemAddrLength_pu32 = dataMemAlFid_u32;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)|| \
                                                     (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_UpdateTransferRequestCount(void){

   if((Dcm_DataTransfer_st.isUploadStarted_b!=FALSE)||(Dcm_DataTransfer_st.isDownloadStarted_b!=FALSE))
   {

        if((Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u)) != 0x00u)
        {
            Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 / (Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u)) +1u;
        }
        else{
            Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 / (Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u));
        }
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

