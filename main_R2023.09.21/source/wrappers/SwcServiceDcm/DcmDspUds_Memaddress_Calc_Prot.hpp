

#ifndef DCMDSPUDS_MEMADDRESS_CALC_PROT_H
#define DCMDSPUDS_MEMADDRESS_CALC_PROT_H

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || \
   												   (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)|| \
                                                       (DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)       || \
                                                       (DCM_CFG_DSP_TRANSFERDATA_ENABLED !=DCM_CFG_OFF)))

#if((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF))
typedef struct{
   uint32 dataMemoryAddress_u32;
   uint32 dataMemorySize_u32;
   uint32 dataMaxBlockLength_u32;
   uint32 nrMaxBlockSequenceNum_u32;
   uint8  dataMemoryIdentifier_u8;
   boolean isUploadStarted_b;
   boolean isDownloadStarted_b;
   uint8  compressionMethod_u8;
}Dcm_DataTransfer_tst;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DataTransfer_tst,AUTOMATIC) Dcm_DataTransfer_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_DSP_TRANSFERDATA_ENABLED != DCM_CFG_OFF)
typedef struct{
   uint32 dataUploadedDataLength_u32;
   uint32 nrCompletedTransfer_u32;
   uint32 cntCurrentBlockCount;
   uint32 dataTransferedDataSize_u32;
}Dcm_TransferData_tst;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR (Dcm_TransferData_tst,DCM_VAR) Dcm_TransferData_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(boolean,DCM_CODE) Dcm_GetRequestUploadStatus(void);
extern FUNC(boolean,DCM_CODE) Dcm_GetRequestDownloadStatus(void);
extern FUNC(void,DCM_CODE)    Dcm_DspDeactivateRequestUploadDownloadPermission(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)|| \
                                                     (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_UpdateTransferRequestCount(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_Lok_DspReqUploadConfirmation(
   VAR(Dcm_IdContextType,AUTOMATIC) dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status_u8
   													);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_GetMemoryInfo(VAR(uint8,AUTOMATIC) dataSize_u8
   ,   P2CONST (uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pcu8
   ,   P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrMemAddrLength_pu32);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

#if( DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_Lok_DspReqTrfExitConfirmation(
   VAR(Dcm_IdContextType,AUTOMATIC) dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   									                   );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if( DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_Lok_DspReqDownloadConfirmation(
   VAR(Dcm_IdContextType,AUTOMATIC) dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   													     );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif

