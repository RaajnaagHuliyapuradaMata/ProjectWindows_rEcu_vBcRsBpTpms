

#include "DcmDspUds_RequestDownload_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_RequestDownload_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_DspRequestDownloadStates_ten Dcm_stDspStateRequestDownload_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static uint32 Dcm_dataMemoryAddress_Download_u32;
static uint32 Dcm_dataMemoryLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static uint8 Dcm_dataMemdatasize_Download_u8;

static uint8 Dcm_dataMemaddrsize_Download_u8;
static uint8 Dcm_dataFormatIdentifier_u8;
static uint8 s_dataCompressionMethod_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_SrvOpStatusType Dcm_stRequestDownloadOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_Dsp_RequestDownload_Ini (void){
    Dcm_NegativeResponseCodeType dataNegResCode_u8;
   uint32 dataBlockLength_u32;

   if(Dcm_stRequestDownloadOpstatus_u8 == DCM_PENDING)
   {

        (void)DcmAppl_Dcm_ProcessRequestDownload(DCM_CANCEL,Dcm_dataFormatIdentifier_u8,Dcm_dataMemoryAddress_Download_u32,Dcm_dataMemoryLength_u32,&dataBlockLength_u32,&dataNegResCode_u8);
        (void)dataNegResCode_u8;
        (void)dataBlockLength_u32;
   }

    Dcm_stRequestDownloadOpstatus_u8 = DCM_INITIAL;
    Dcm_stDspStateRequestDownload_en = DCM_DSP_REQUESTDOWNLOAD_IDLE;
    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

static Std_ReturnType Dcm_GetIndexOfRequestDownloadMemory_u8(uint32 dataMemAddr_u32
   ,                                                                          uint32 nrMemLength_u32
   ,                                                                          uint16 * idxIndex_u16);
static Std_ReturnType Dcm_GetIndexOfRequestDownloadMemory_u8(uint32 dataMemAddr_u32
   ,                                                                          uint32 nrMemLength_u32
   ,                                                                          uint16 * idxIndex_u16)
{

   uint16 dataSize_u16;
   uint16 idxLoop_u16;
    Std_ReturnType dataRetVal_u8;
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;

    dataSize_u16 = Dcm_RequestDownloadCalculateTableSize_u16();

   if(0u != nrMemLength_u32)
   {

         for(idxLoop_u16 = 0;idxLoop_u16<dataSize_u16;idxLoop_u16++)
        {
             if((dataMemAddr_u32 >= Dcm_RequestDownloadConfig_cast[idxLoop_u16].dataRequestDownloadMemoryRangeLow_u32) && ((dataMemAddr_u32 + (nrMemLength_u32-1u))<=(Dcm_RequestDownloadConfig_cast[idxLoop_u16].dataRequestDownloadMemoryRangeHigh_u32)))
             {
                 *idxIndex_u16 = idxLoop_u16;
                 dataRetVal_u8 = E_OK;
                 Dcm_DataTransfer_st.dataMemoryIdentifier_u8 = Dcm_RequestDownloadConfig_cast[idxLoop_u16].dataMemoryValue_u8;
                 break;
             }
        }
   }
     return (dataRetVal_u8);
}

Std_ReturnType SwcServiceDcm_tRequestDownload (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
   uint8 dataEncryptionMethod_u8;
    Std_ReturnType dataretVal_u8;
   uint16 idxIndex_u16 = 0u;
   uint32 dataBlockLength_u32;

    *dataNegRespCode_u8 =0x00;
    dataBlockLength_u32=0x00;
   s_dataCompressionMethod_u8 = 0x00;
    dataretVal_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_RequestDownload_Ini();

        dataretVal_u8 = E_OK;
   }
   else{

        if(Dcm_stDspStateRequestDownload_en==DCM_DSP_REQUESTDOWNLOAD_IDLE)
        {

            if(pMsgContext->reqDataLen >= DCM_DSP_REQUESTDOWNLOAD_MINREQLEN)
            {

                Dcm_dataFormatIdentifier_u8 = pMsgContext->reqData[0];

                dataEncryptionMethod_u8 = (Dcm_dataFormatIdentifier_u8& (0xFu));

                s_dataCompressionMethod_u8 = (uint8)((Dcm_dataFormatIdentifier_u8 & (0xF0u))>>4u);

                dataretVal_u8 = DcmAppl_CheckEncryptionCompressionMethod (0x34,s_dataCompressionMethod_u8,dataEncryptionMethod_u8);

                if(dataretVal_u8==E_OK)
                {

                    Dcm_dataMemaddrsize_Download_u8 = ((pMsgContext->reqData[1])& (0xFu));

                    Dcm_dataMemdatasize_Download_u8 = (uint8)(((pMsgContext->reqData[1])& (0xF0u))>>4u);

                    if((0u!=Dcm_dataMemaddrsize_Download_u8)&&(0u!=Dcm_dataMemdatasize_Download_u8)&&(Dcm_dataMemdatasize_Download_u8 <=4u)&&(Dcm_dataMemaddrsize_Download_u8<=4u))
                    {

                    if(pMsgContext->reqDataLen == (Dcm_dataMemaddrsize_Download_u8 + Dcm_dataMemdatasize_Download_u8 + 2u))
                    {

                        Dcm_GetMemoryInfo(Dcm_dataMemaddrsize_Download_u8,&(pMsgContext->reqData[2]),&Dcm_dataMemoryAddress_Download_u32);

                        Dcm_GetMemoryInfo(Dcm_dataMemdatasize_Download_u8,&(pMsgContext->reqData[Dcm_dataMemaddrsize_Download_u8+2]),&Dcm_dataMemoryLength_u32);

                        dataretVal_u8 = Dcm_GetIndexOfRequestDownloadMemory_u8(Dcm_dataMemoryAddress_Download_u32,Dcm_dataMemoryLength_u32,&idxIndex_u16);

                        if(E_OK == dataretVal_u8)
                        {

                            if((Dcm_DsldGetActiveSecurityMask_u32 () &  Dcm_RequestDownloadConfig_cast[idxIndex_u16].dataAllowedSec_u32) != 0x0uL)
                            {
#if( DCM_CFG_DSP_REQUESTDOWNLOAD_SEQUENCECHECK_ENABLED !=DCM_CFG_OFF)

                                if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE) || (Dcm_DataTransfer_st.isUploadStarted_b != FALSE))
                                {
                                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                                }

                                else
#endif
                                {
                                    Dcm_stRequestDownloadOpstatus_u8 = DCM_INITIAL;
                                    Dcm_stDspStateRequestDownload_en = DCM_DSP_REQUESTDOWNLOAD_GETBLOCKNUM;
                                }
                            }

                            else
                            {
                                *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
                            }
                        }

                        else
                        {
                              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        }
                    }
                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                        }
                    }
                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else if(dataretVal_u8 == DCM_E_PENDING)
                {

                }
                else{

                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }

            if(*dataNegRespCode_u8!=0x00)
            {
                Dcm_stDspStateRequestDownload_en = DCM_DSP_REQUESTDOWNLOAD_ERROR;
            }
        }

        if(Dcm_stDspStateRequestDownload_en==DCM_DSP_REQUESTDOWNLOAD_GETBLOCKNUM)
        {

            dataretVal_u8 = DcmAppl_Dcm_ProcessRequestDownload(Dcm_stRequestDownloadOpstatus_u8,Dcm_dataFormatIdentifier_u8,Dcm_dataMemoryAddress_Download_u32,Dcm_dataMemoryLength_u32,&dataBlockLength_u32,dataNegRespCode_u8);

            if(dataretVal_u8==E_OK)
            {
                *dataNegRespCode_u8=0x00;
                Dcm_DataTransfer_st.dataMaxBlockLength_u32  = dataBlockLength_u32;
                Dcm_DataTransfer_st.dataMemoryAddress_u32   = Dcm_dataMemoryAddress_Download_u32;
                Dcm_DataTransfer_st.dataMemorySize_u32      = Dcm_dataMemoryLength_u32;
                Dcm_DataTransfer_st.compressionMethod_u8	= s_dataCompressionMethod_u8;

                Dcm_stDspStateRequestDownload_en=DCM_DSP_REQUESTDOWNLOAD_IDLE;
                Dcm_stRequestDownloadOpstatus_u8 = DCM_INITIAL;

                if(dataBlockLength_u32<=0xFFu)
                {
                    pMsgContext->resData[0]=0x10;
                    pMsgContext->resData[1]=(uint8)dataBlockLength_u32;
                    pMsgContext->resDataLen=0x02;
                }
                else if(dataBlockLength_u32<=0xFFFFuL)
                {
                    pMsgContext->resData[0]=0x20;
                    pMsgContext->resData[1]= (uint8)(dataBlockLength_u32>>8u);
                    pMsgContext->resData[2]=(uint8)dataBlockLength_u32;
                    pMsgContext->resDataLen=0x03;
                }
                else if(dataBlockLength_u32<=0xFFFFFFuL)
                {
                    pMsgContext->resData[0]=0x30;
                    pMsgContext->resData[1]= (uint8)(dataBlockLength_u32>>16u);
                    pMsgContext->resData[2]= (uint8)(dataBlockLength_u32>>8u);
                    pMsgContext->resData[3]=(uint8)dataBlockLength_u32;
                    pMsgContext->resDataLen=0x04;
                }
                else{
                    pMsgContext->resData[0]=0x40;
                    pMsgContext->resData[1]= (uint8)(dataBlockLength_u32>>24u);
                    pMsgContext->resData[2]= (uint8)(dataBlockLength_u32>>16u);
                    pMsgContext->resData[3]= (uint8)(dataBlockLength_u32>>8u);
                    pMsgContext->resData[4]= (uint8)dataBlockLength_u32;
                    pMsgContext->resDataLen=0x05;
                }
            }

            else if(dataretVal_u8==DCM_E_PENDING)
            {
                *dataNegRespCode_u8=0x00;
                Dcm_stRequestDownloadOpstatus_u8 = DCM_PENDING;

            }

            else{
                if(*dataNegRespCode_u8 == 0x00)
                {
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }

            }

            if(*dataNegRespCode_u8!=0x00u)
            {
                Dcm_stDspStateRequestDownload_en = DCM_DSP_REQUESTDOWNLOAD_ERROR;
                dataretVal_u8=E_NOT_OK;
            }
        }

        if(Dcm_stDspStateRequestDownload_en==DCM_DSP_REQUESTDOWNLOAD_ERROR)
        {
            Dcm_stRequestDownloadOpstatus_u8 = DCM_INITIAL;

            Dcm_stDspStateRequestDownload_en=DCM_DSP_REQUESTDOWNLOAD_IDLE;
            dataretVal_u8=E_NOT_OK;
        }
   }
    return dataretVal_u8;
}

static void Dcm_DspActivateRequestDownloadPermission(void){

    Dcm_DataTransfer_st.isDownloadStarted_b  = TRUE;

    Dcm_DataTransfer_st.isUploadStarted_b    = FALSE;
    Dcm_TransferData_st.cntCurrentBlockCount = 0x00;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
    Dcm_UpdateTransferRequestCount();
}

void Dcm_Lok_DspReqDownloadConfirmation(
   Dcm_IdContextType dataIdContext_u8
   ,  Type_SwcServiceCom_tIdPdu dataRxPduId_u8
   ,  uint16 dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8)
{
            if(status_u8 == DCM_RES_POS_OK)
            {
                Dcm_DspActivateRequestDownloadPermission();
            }
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  															    status_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

