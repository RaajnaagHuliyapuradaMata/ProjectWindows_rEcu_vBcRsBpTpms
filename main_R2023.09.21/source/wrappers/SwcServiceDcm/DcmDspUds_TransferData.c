#include "Std_Types.hpp"

#include "DcmDspUds_TransferData_Inf.hpp"
#include "DcmCore_DslDsd_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#include "DcmDspUds_TransferData_Priv.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_DataTransfer_tst,AUTOMATIC) Dcm_DataTransfer_st;
static VAR(Dcm_DspTransferDataStates_ten,     DCM_VAR  ) s_stTransferDataState_en;
VAR (Dcm_TransferData_tst,DCM_VAR) Dcm_TransferData_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint32,DCM_VAR) s_dataCurrentBlockSize_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_OpStatusType,  DCM_VAR) s_stTransferOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
static FUNC(uint32,DCM_CODE) Dcm_GetLastBlockSize(void);
#endif
static FUNC(Std_ReturnType,AUTOMATIC)Dcm_CheckNRCfromApplication(VAR(uint32,AUTOMATIC) dataLengthReceived_u32
   ,     P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8);

FUNC(void,DCM_CODE) Dcm_Dsp_TransferDataIni(void){

   if((DCM_PENDING == s_stTransferOpstatus_u8 ) && (Dcm_DataTransfer_st.isUploadStarted_b != FALSE))
   {

        (void)(DcmAppl_Dcm_ReadMemory(DCM_CANCEL
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     Dcm_DataTransfer_st.dataMemoryAddress_u32
   ,     s_dataCurrentBlockSize_u32
   ,     NULL_PTR
   ,     NULL_PTR));
   }

   else if((DCM_PENDING == s_stTransferOpstatus_u8 ) && (Dcm_DataTransfer_st.isDownloadStarted_b != FALSE))
   {

        (void)(DcmAppl_Dcm_WriteMemory(DCM_CANCEL
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     Dcm_DataTransfer_st.dataMemoryAddress_u32
   ,     s_dataCurrentBlockSize_u32
   ,     NULL_PTR
   ,     NULL_PTR));
   }
   else{

   }

    Dcm_TransferData_st.cntCurrentBlockCount = 0u;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;

   s_stTransferOpstatus_u8 = DCM_INITIAL;

   s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_IDLE;

    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

static FUNC(void,DCM_CODE) Dcm_CheckNrcForTransferData(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8);
static FUNC(void,DCM_CODE) Dcm_CheckNrcForTransferData(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8)
{
   VAR(uint8,AUTOMATIC) dataReceivedBlockSequenceNr_u8;
   VAR(uint32,AUTOMATIC) dataLengthReceived_u32;

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
   VAR(uint32,AUTOMATIC) lastDataBlockSize_u32;
#endif

    dataReceivedBlockSequenceNr_u8 = pMsgContext->reqData[0];
    dataLengthReceived_u32 = pMsgContext->reqDataLen-1uL;

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
    lastDataBlockSize_u32 = Dcm_GetLastBlockSize();
#endif

   if((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(pMsgContext->reqDataLen < DCM_TRANSFERDATAUPLOAD_MIN_LEN))
   {
        *dataNegResponseCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }

   else if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(pMsgContext->reqDataLen < DCM_TRANSFERDATADOWNLOAD_MIN_LEN))
   {
        *dataNegResponseCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }

   else if(((Dcm_DataTransfer_st.isUploadStarted_b == FALSE)&&(Dcm_DataTransfer_st.isDownloadStarted_b == FALSE)) ||
    (((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)||(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE))&&
            (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&(Dcm_TransferData_st.dataTransferedDataSize_u32 == Dcm_DataTransfer_st.dataMemorySize_u32) && (dataReceivedBlockSequenceNr_u8 !=  Dcm_TransferData_st.cntCurrentBlockCount)))
   {
        *dataNegResponseCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
   }

   else if( ((Dcm_CheckNRCfromApplication(dataLengthReceived_u32,dataNegResponseCode_u8))!= E_OK) && (Dcm_DataTransfer_st.compressionMethod_u8 != 0x00) )
   {

   }
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)

   else if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE) &&
            (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00) &&
            (((Dcm_TransferData_st.dataTransferedDataSize_u32 == Dcm_DataTransfer_st.dataMemorySize_u32)&&(dataReceivedBlockSequenceNr_u8 ==  Dcm_TransferData_st.cntCurrentBlockCount)) ||
             ((Dcm_TransferData_st.dataTransferedDataSize_u32 == (Dcm_DataTransfer_st.dataMemorySize_u32 - lastDataBlockSize_u32)) && (dataReceivedBlockSequenceNr_u8 == (Dcm_TransferData_st.cntCurrentBlockCount+1u)))) &&
            (dataLengthReceived_u32!=lastDataBlockSize_u32))

   {
        *dataNegResponseCode_u8 = DCM_E_TRANSFERDATASUSPENDED;
   }
#else

   else if( ((Dcm_CheckNRCfromApplication(dataLengthReceived_u32,dataNegResponseCode_u8))!= E_OK) && (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00) )
   {

   }
#endif

   else if((Dcm_TransferData_st.dataTransferedDataSize_u32 == 0u)&&(dataReceivedBlockSequenceNr_u8!=1u))
   {
        *dataNegResponseCode_u8 = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
   }

   else if((Dcm_TransferData_st.cntCurrentBlockCount == 0xFFu)&&
            (dataReceivedBlockSequenceNr_u8!=0x00u) &&
            (dataReceivedBlockSequenceNr_u8!=0xFFu))
   {

        *dataNegResponseCode_u8 = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
   }

   else if((Dcm_TransferData_st.cntCurrentBlockCount != 0xffu)&&
            (dataReceivedBlockSequenceNr_u8 != Dcm_TransferData_st.cntCurrentBlockCount)&&
            (dataReceivedBlockSequenceNr_u8 != (Dcm_TransferData_st.cntCurrentBlockCount+1u)))
   {

        *dataNegResponseCode_u8 = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
   }
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
   else if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&
            (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&
            (Dcm_TransferData_st.dataTransferedDataSize_u32 != (Dcm_DataTransfer_st.dataMemorySize_u32 - lastDataBlockSize_u32))&&
            (Dcm_TransferData_st.dataTransferedDataSize_u32 != Dcm_DataTransfer_st.dataMemorySize_u32)&&
            (dataLengthReceived_u32!= (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u)))
   {

        *dataNegResponseCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
#endif
   else{

        *dataNegResponseCode_u8 = 0;
   }
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tTransferData(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten = DCM_TRANSFER_NOT_AVAILABLE;
   VAR(Dcm_ReadMemoryRet_t,AUTOMATIC) dataReadMemRetValue_en = DCM_READ_NOT_AVAILABLE;
   VAR(Dcm_WriteMemoryRet_t,AUTOMATIC)dataWriteMemRetValue_en = DCM_WRITE_NOT_AVAILABLE;
   VAR(Std_ReturnType,AUTOMATIC) dataReturnValue_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataServRetValue_u8;
   VAR(uint8,AUTOMATIC) dataReceivedBlockSequenceNr_u8;

    *dataNegRespCode_u8 = 0u;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_TransferDataIni();

        dataServRetValue_u8 = E_OK;
   }
   else{

        dataReceivedBlockSequenceNr_u8 = pMsgContext->reqData[0];
        dataServRetValue_u8=E_NOT_OK;

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_IDLE)
        {

            s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_ERROR;

            Dcm_CheckNrcForTransferData(pMsgContext,dataNegRespCode_u8);
            if(*dataNegRespCode_u8 == 0)
            {

                if(((Dcm_TransferData_st.cntCurrentBlockCount == 0xffu) && (dataReceivedBlockSequenceNr_u8==0x00u)) ||
                        ((Dcm_TransferData_st.cntCurrentBlockCount != 0xffu)&&(dataReceivedBlockSequenceNr_u8 == (Dcm_TransferData_st.cntCurrentBlockCount+1u))))
                {

                   if((Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&(Dcm_TransferData_st.dataTransferedDataSize_u32!=0u))
                    {

                        Dcm_DataTransfer_st.dataMemoryAddress_u32 = Dcm_DataTransfer_st.dataMemoryAddress_u32 + (s_dataCurrentBlockSize_u32);
                    }
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)

                   if(Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)
                   {
                       if(Dcm_TransferData_st.dataTransferedDataSize_u32 < (Dcm_DataTransfer_st.dataMemorySize_u32 - Dcm_GetLastBlockSize()))
                       {

                           s_dataCurrentBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u;
                       }

                       else
                       {

                           s_dataCurrentBlockSize_u32 = Dcm_GetLastBlockSize();
                       }
                   }
                   else
                   {
                       if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                       {

                           s_dataCurrentBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u;
                       }
                       else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                       {

                           s_dataCurrentBlockSize_u32 = pMsgContext->reqDataLen-1u;
                       }
                       else
                       {

                       }
                   }
#else

                    if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                    {

                        s_dataCurrentBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u;
                    }
                    else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                    {

                        s_dataCurrentBlockSize_u32 = pMsgContext->reqDataLen-1uL;
                    }
                    else
                    {

                    }

#endif

                }

                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_CHECKACCESS;
            }
        }

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_CHECKACCESS)
        {
            if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
            {

                dataTransferDirection_ten = DCM_UPLOAD;
            }
            else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
            {

                dataTransferDirection_ten = DCM_DOWNLOAD;
            }
            else{

            }

            if(pMsgContext->reqDataLen>1u)
            {

                dataReturnValue_u8 = DcmAppl_Dcm_CheckPermissionForTransferData(dataReceivedBlockSequenceNr_u8
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     Dcm_DataTransfer_st.dataMemoryAddress_u32
   ,     &s_dataCurrentBlockSize_u32
   ,     &pMsgContext->reqData[1]
   ,     (pMsgContext->reqDataLen)-1u
   ,     dataTransferDirection_ten
   ,     dataNegRespCode_u8
                );
            }

            else{

                dataReturnValue_u8 = DcmAppl_Dcm_CheckPermissionForTransferData(dataReceivedBlockSequenceNr_u8
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     Dcm_DataTransfer_st.dataMemoryAddress_u32
   ,     &s_dataCurrentBlockSize_u32
   ,     NULL_PTR
   ,     0
   ,     dataTransferDirection_ten
   ,     dataNegRespCode_u8
                );

            }

            if(dataReturnValue_u8 == DCM_E_PENDING)
            {

                dataServRetValue_u8=DCM_E_PENDING;
            }
            else if(dataReturnValue_u8 == E_OK)
            {

                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_READWRITE;
            }
            else{
                if(*dataNegRespCode_u8 == 0)
                {

                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }

                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_ERROR;
            }

        }

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_READWRITE)
        {

            if((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(s_dataCurrentBlockSize_u32 > pMsgContext->resMaxDataLen))
            {

                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;

                DCM_DET_ERROR(DCM_TRANSFERDATA_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
            }
            else if((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(s_dataCurrentBlockSize_u32 <=pMsgContext->resMaxDataLen))
            {

                dataReadMemRetValue_en =  DcmAppl_Dcm_ReadMemory(s_stTransferOpstatus_u8
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     Dcm_DataTransfer_st.dataMemoryAddress_u32
   ,     s_dataCurrentBlockSize_u32
   ,     &pMsgContext->resData[1]
   ,     dataNegRespCode_u8);
            }
            else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
            {

                dataWriteMemRetValue_en =  DcmAppl_Dcm_WriteMemory(s_stTransferOpstatus_u8
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     Dcm_DataTransfer_st.dataMemoryAddress_u32
   ,     s_dataCurrentBlockSize_u32
   ,     &pMsgContext->reqData[1]
   ,     dataNegRespCode_u8);

            }
            else{

            }

             if(((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(DCM_READ_PENDING == dataReadMemRetValue_en))||
                    ((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(DCM_WRITE_PENDING == dataWriteMemRetValue_en)))
            {
                s_stTransferOpstatus_u8 = DCM_PENDING;

                dataServRetValue_u8=DCM_E_PENDING;
            }
            else if(((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(DCM_READ_FORCE_RCRRP == dataReadMemRetValue_en))||
                    ((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(DCM_WRITE_FORCE_RCRRP == dataWriteMemRetValue_en)))
            {
                s_stTransferOpstatus_u8 = DCM_FORCE_RCRRP_OK;

                dataServRetValue_u8=DCM_E_FORCE_RCRRP;
            }
            else if(((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(DCM_READ_OK == dataReadMemRetValue_en))||
                    ((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(DCM_WRITE_OK == dataWriteMemRetValue_en)))
            {

                if((Dcm_TransferData_st.cntCurrentBlockCount == 0xffu)&&(dataReceivedBlockSequenceNr_u8==0u))
                {

                    Dcm_TransferData_st.cntCurrentBlockCount = 0;

                    Dcm_TransferData_st.dataTransferedDataSize_u32 = Dcm_TransferData_st.dataTransferedDataSize_u32 + s_dataCurrentBlockSize_u32;
                }

                else if((Dcm_TransferData_st.cntCurrentBlockCount != 0xffu)&&(dataReceivedBlockSequenceNr_u8 == (Dcm_TransferData_st.cntCurrentBlockCount+1u)))
                {

                    Dcm_TransferData_st.cntCurrentBlockCount++;

                    Dcm_TransferData_st.dataTransferedDataSize_u32 = Dcm_TransferData_st.dataTransferedDataSize_u32 + s_dataCurrentBlockSize_u32;
                }
                else{

                }

                if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                {

                    pMsgContext->resDataLen =  s_dataCurrentBlockSize_u32+1u;
                }
                else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                {

                    pMsgContext->resDataLen =  1u;
                }
                else{

                }

                pMsgContext->resData[0]= dataReceivedBlockSequenceNr_u8;

                s_stTransferDataState_en  = DCM_DSP_TRANSFERDATA_IDLE;

                s_stTransferOpstatus_u8    = DCM_INITIAL;

                dataServRetValue_u8=E_OK;

            }
            else{

                s_stTransferOpstatus_u8 = DCM_INITIAL;

                if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                {
                    if(*dataNegRespCode_u8 == 0x00)
                    {

                        *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
                    }
                }
                else{
                    if(*dataNegRespCode_u8 == 0)
                    {

                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }
                }

                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_ERROR;
            }
        }

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_ERROR)
        {

            if(*dataNegRespCode_u8==0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }

            Dcm_DspDeactivateRequestUploadDownloadPermission();

            s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_IDLE;

            s_stTransferOpstatus_u8    = DCM_INITIAL;

            dataServRetValue_u8=E_NOT_OK;
        }
   }
    return dataServRetValue_u8;
}

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)

static FUNC(uint32,AUTOMATIC) Dcm_GetLastBlockSize(void){
   VAR(uint32,AUTOMATIC) dataLastBlockSize_u32;

   if((Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u))==0u)
   {
        dataLastBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u;
   }

   else{
        dataLastBlockSize_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u));
   }
    return dataLastBlockSize_u32;
}

#endif

static FUNC(Std_ReturnType,AUTOMATIC)Dcm_CheckNRCfromApplication(VAR(uint32,AUTOMATIC) dataLengthReceived_u32
   ,     P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8)
{
   VAR(uint8,AUTOMATIC) dataReturnValue_u8;
   VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten = DCM_TRANSFER_NOT_AVAILABLE;
    dataReturnValue_u8 = E_OK;
   if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
   {

        dataTransferDirection_ten = DCM_UPLOAD;
   }
   else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
   {

        dataTransferDirection_ten = DCM_DOWNLOAD;
   }
   else{

   }

    (void)DcmAppl_DcmMemSizeCheckForTransferData(Dcm_DataTransfer_st.compressionMethod_u8
   ,     Dcm_DataTransfer_st.dataMemoryIdentifier_u8
   ,     dataLengthReceived_u32
   ,     dataTransferDirection_ten
   ,     dataNegResponseCode_u8);
   if(*dataNegResponseCode_u8 != 0)
   {
        dataReturnValue_u8 = E_NOT_OK;
   }
    return dataReturnValue_u8;
}

FUNC(void,DCM_CODE) Dcm_DspDeactivateRequestUploadDownloadPermission(void){

    Dcm_DataTransfer_st.isDownloadStarted_b       = FALSE;

    Dcm_DataTransfer_st.isUploadStarted_b       = FALSE;
    Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = 0x00;
    Dcm_TransferData_st.cntCurrentBlockCount = 0x00;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
   Dcm_DataTransfer_st.compressionMethod_u8  = 0x00;
}

 FUNC(void, DCM_CODE) Dcm_Lok_DspReqTrfExitConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
#if( DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)
            if(status_u8 == DCM_RES_POS_OK)
            {
                Dcm_DspDeactivateRequestUploadDownloadPermission();
            }
#endif
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  status_u8);
}

FUNC(boolean,DCM_CODE)Dcm_GetRequestUploadStatus(void){
    return (Dcm_DataTransfer_st.isUploadStarted_b);
}

FUNC(boolean,DCM_CODE)Dcm_GetRequestDownloadStatus(void){
    return (Dcm_DataTransfer_st.isDownloadStarted_b);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

