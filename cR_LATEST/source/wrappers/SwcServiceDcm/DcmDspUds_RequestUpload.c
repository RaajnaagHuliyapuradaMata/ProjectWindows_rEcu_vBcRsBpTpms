#include "Std_Types.hpp"

#include "DcmDspUds_RequestUpload_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_RequestUpload_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_DspRequestUploadStates_ten,DCM_VAR) Dcm_stDspStateRequestUpload_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint32,     DCM_VAR) Dcm_dataMemoryAddress_u32;
static VAR(uint32,     DCM_VAR) Dcm_dataMemoryLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR (uint8,  DCM_VAR) Dcm_dataMemdatasize_u8;

static VAR (uint8,  DCM_VAR) Dcm_dataMemaddrsize_u8;
static VAR (uint8,  DCM_VAR) Dcm_dataFormatIdentifier_u8;
static VAR(uint8,   DCM_VAR) s_dataCompressionMethod_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRequestUploadOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Dsp_RequestUpload_Ini (void){
   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8;
   VAR(uint32,AUTOMATIC)  dataBlockLength_u32;

   if(Dcm_stRequestUploadOpstatus_u8 == DCM_PENDING)
   {

        (void)DcmAppl_Dcm_ProcessRequestUpload(DCM_CANCEL,Dcm_dataFormatIdentifier_u8,Dcm_dataMemoryAddress_u32,Dcm_dataMemoryLength_u32,&dataBlockLength_u32,&dataNegResCode_u8);
        (void)dataNegResCode_u8;
        (void)dataBlockLength_u32;
   }

    Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;
    Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_IDLE;
    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

static FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfRequestUploadMemory_u8(VAR   (uint32,AUTOMATIC) dataMemAddr_u32
   ,     VAR   (uint32,AUTOMATIC) nrMemLength_u32
   ,     P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16);
static FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfRequestUploadMemory_u8(VAR   (uint32,AUTOMATIC) dataMemAddr_u32
   ,     VAR   (uint32,AUTOMATIC) nrMemLength_u32
   ,     P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16)
{

   VAR (uint16,     AUTOMATIC) dataSize_u16;
   VAR (uint16,     AUTOMATIC) idxLoop_u16;
   VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;

    dataSize_u16 = Dcm_RequestUploadCalculateTableSize_u16();

   if(0u != nrMemLength_u32)
   {

         for(idxLoop_u16 = 0;idxLoop_u16<dataSize_u16;idxLoop_u16++)
        {
             if((dataMemAddr_u32 >= Dcm_RequestUploadConfig_cast[idxLoop_u16].dataRequestUploadMemoryRangeLow_u32) && ((dataMemAddr_u32 + (nrMemLength_u32-1u))<=(Dcm_RequestUploadConfig_cast[idxLoop_u16].dataRequestUploadMemoryRangeHigh_u32)))
             {
                 *idxIndex_u16 = idxLoop_u16;
                 dataRetVal_u8 = E_OK;
                 Dcm_DataTransfer_st.dataMemoryIdentifier_u8 = Dcm_RequestUploadConfig_cast[idxLoop_u16].dataMemoryValue_u8;
                 break;
             }
        }
   }
     return (dataRetVal_u8);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmRequestUpload (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint8,AUTOMATIC) dataEncryptionMethod_u8;
   VAR(Std_ReturnType,AUTOMATIC)  dataretVal_u8 = E_NOT_OK;
   VAR(uint16,AUTOMATIC) idxIndex_u16 = 0u;
   VAR(uint32,AUTOMATIC)  dataBlockLength_u32;

    *dataNegRespCode_u8 =0x00;
    dataBlockLength_u32=0x00;
   s_dataCompressionMethod_u8 = 0x00;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_RequestUpload_Ini();

        dataretVal_u8 = E_OK;
   }
   else{

        if(Dcm_stDspStateRequestUpload_en==DCM_DSP_REQUESTUPLOAD_IDLE)
        {

            if(pMsgContext->reqDataLen >= DCM_DSP_REQUESTUPLOAD_MINREQLEN)
            {

                Dcm_dataFormatIdentifier_u8 = pMsgContext->reqData[0];

                dataEncryptionMethod_u8 = (Dcm_dataFormatIdentifier_u8& (0xFu));

                s_dataCompressionMethod_u8 = (uint8)((Dcm_dataFormatIdentifier_u8 & (0xF0u))>>4u);

                dataretVal_u8 = DcmAppl_CheckEncryptionCompressionMethod (0x35,s_dataCompressionMethod_u8,dataEncryptionMethod_u8);

                if(dataretVal_u8==E_OK)
                {

                    Dcm_dataMemaddrsize_u8 = ((pMsgContext->reqData[1])& (0xFu));

                    Dcm_dataMemdatasize_u8 = (uint8)(((pMsgContext->reqData[1])& (0xF0u))>>4u);

                    if((0u!=Dcm_dataMemaddrsize_u8)&&(0u!=Dcm_dataMemdatasize_u8)&&(Dcm_dataMemdatasize_u8 <=4u)&&(Dcm_dataMemaddrsize_u8<=4u))
                    {

                    if(pMsgContext->reqDataLen == (Dcm_dataMemaddrsize_u8 + Dcm_dataMemdatasize_u8 + 2u))
                    {

                        Dcm_GetMemoryInfo(Dcm_dataMemaddrsize_u8,&(pMsgContext->reqData[2]),&Dcm_dataMemoryAddress_u32);

                        Dcm_GetMemoryInfo(Dcm_dataMemdatasize_u8,&(pMsgContext->reqData[Dcm_dataMemaddrsize_u8+2]),&Dcm_dataMemoryLength_u32);

                        dataretVal_u8 = Dcm_GetIndexOfRequestUploadMemory_u8(Dcm_dataMemoryAddress_u32,Dcm_dataMemoryLength_u32,&idxIndex_u16);

                        if(E_OK == dataretVal_u8)
                        {

                            if((Dcm_DsldGetActiveSecurityMask_u32 () &  Dcm_RequestUploadConfig_cast[idxIndex_u16].dataAllowedSec_u32) != 0x0uL)
                            {
#if( DCM_CFG_DSP_REQUESTUPLOAD_SEQUENCECHECK_ENABLED !=DCM_CFG_OFF)

                                if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE) || (Dcm_DataTransfer_st.isUploadStarted_b != FALSE))
                                {
                                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                                }

                                else
#endif
                                {
                                    Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;
                                    Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_GETBLOCKNUM;
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
                Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_ERROR;
            }
        }

        if(Dcm_stDspStateRequestUpload_en==DCM_DSP_REQUESTUPLOAD_GETBLOCKNUM)
        {

            dataretVal_u8 = DcmAppl_Dcm_ProcessRequestUpload(Dcm_stRequestUploadOpstatus_u8,Dcm_dataFormatIdentifier_u8,Dcm_dataMemoryAddress_u32,Dcm_dataMemoryLength_u32,&dataBlockLength_u32,dataNegRespCode_u8);

                if(dataretVal_u8==E_OK)
                {

                    *dataNegRespCode_u8=0x00;
                    Dcm_DataTransfer_st.dataMaxBlockLength_u32  = dataBlockLength_u32;
                    Dcm_DataTransfer_st.dataMemoryAddress_u32   = Dcm_dataMemoryAddress_u32;
                    Dcm_DataTransfer_st.dataMemorySize_u32      = Dcm_dataMemoryLength_u32;
                    Dcm_DataTransfer_st.compressionMethod_u8	= s_dataCompressionMethod_u8;
                    dataretVal_u8=E_OK;

                    Dcm_stDspStateRequestUpload_en=DCM_DSP_REQUESTUPLOAD_IDLE;
                    Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;

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
                    else
                    {
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
                    Dcm_stRequestUploadOpstatus_u8 = DCM_PENDING;

                }

                else{
                    if(*dataNegRespCode_u8 == 0x00u)
                    {
                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
                }

            if(*dataNegRespCode_u8!=0x00u)
            {
                Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_ERROR;
            }
        }

        if(Dcm_stDspStateRequestUpload_en==DCM_DSP_REQUESTUPLOAD_ERROR)
        {
            Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;

            Dcm_stDspStateRequestUpload_en=DCM_DSP_REQUESTUPLOAD_IDLE;
            dataretVal_u8=E_NOT_OK;

        }
   }
    return dataretVal_u8;
}

static FUNC(void,DCM_CODE) Dcm_DspActivateRequestUploadPermission(void){

    Dcm_DataTransfer_st.isUploadStarted_b  = TRUE;

    Dcm_DataTransfer_st.isDownloadStarted_b  = FALSE;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
    Dcm_TransferData_st.cntCurrentBlockCount = 0x00;
    Dcm_UpdateTransferRequestCount();
}

 FUNC(void, DCM_CODE) Dcm_Lok_DspReqUploadConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
            if(status_u8 == DCM_RES_POS_OK)
            {
                Dcm_DspActivateRequestUploadPermission();
            }
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  status_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

