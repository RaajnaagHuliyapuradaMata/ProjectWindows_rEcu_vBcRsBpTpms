
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_TransferData_Inf.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#include "DcmDspUds_TransferData_Priv.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
Dcm_DataTransfer_tst Dcm_DataTransfer_st;
static Dcm_DspTransferDataStates_ten s_stTransferDataState_en;
Dcm_TransferData_tst Dcm_TransferData_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
static uint32 s_dataCurrentBlockSize_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static Dcm_OpStatusType s_stTransferOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
static uint32 Dcm_GetLastBlockSize(void);
#endif
static Std_ReturnType Dcm_CheckNRCfromApplication(uint32 dataLengthReceived_u32,
                                                                 Dcm_NegativeResponseCodeType * dataNegResponseCode_u8);

void Dcm_Dsp_TransferDataIni(void)
{

    if((DCM_PENDING == s_stTransferOpstatus_u8 ) && (Dcm_DataTransfer_st.isUploadStarted_b != FALSE))
    {

        (void)(DcmAppl_Dcm_ReadMemory(DCM_CANCEL,
                                      Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                                      Dcm_DataTransfer_st.dataMemoryAddress_u32,
                                      s_dataCurrentBlockSize_u32,
                                      NULL_PTR,
                                      NULL_PTR));
    }

    else if((DCM_PENDING == s_stTransferOpstatus_u8 ) && (Dcm_DataTransfer_st.isDownloadStarted_b != FALSE))
    {

        (void)(DcmAppl_Dcm_WriteMemory(DCM_CANCEL,
                                      Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                                      Dcm_DataTransfer_st.dataMemoryAddress_u32,
                                      s_dataCurrentBlockSize_u32,
                                      NULL_PTR,
                                      NULL_PTR));
    }
    else
    {

    }

    Dcm_TransferData_st.cntCurrentBlockCount = 0u;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;

    s_stTransferOpstatus_u8 = DCM_INITIAL;

    s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_IDLE;

    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

static void Dcm_CheckNrcForTransferData(const Dcm_MsgContextType * pMsgContext,
                                                                 Dcm_NegativeResponseCodeType * dataNegResponseCode_u8);
static void Dcm_CheckNrcForTransferData(const Dcm_MsgContextType * pMsgContext,
                                                                 Dcm_NegativeResponseCodeType * dataNegResponseCode_u8)
{
    uint8 dataReceivedBlockSequenceNr_u8;
    uint32 dataLengthReceived_u32;

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
    uint32 lastDataBlockSize_u32;
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
    else
    {

        *dataNegResponseCode_u8 = 0;
    }
}

Std_ReturnType Dcm_DcmTransferData(Dcm_SrvOpStatusType OpStatus,
                                                  Dcm_MsgContextType * pMsgContext,
                                                  Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{

    Dcm_TrasferDirection_en dataTransferDirection_ten = DCM_TRANSFER_NOT_AVAILABLE;
    Dcm_ReadMemoryRet_t dataReadMemRetValue_en = DCM_READ_NOT_AVAILABLE;
    Dcm_WriteMemoryRet_t dataWriteMemRetValue_en = DCM_WRITE_NOT_AVAILABLE;
    Std_ReturnType dataReturnValue_u8;
    Std_ReturnType dataServRetValue_u8;
    uint8 dataReceivedBlockSequenceNr_u8;

    *dataNegRespCode_u8 = 0u;

    if (OpStatus == DCM_CANCEL)
    {

        Dcm_Dsp_TransferDataIni();

        dataServRetValue_u8 = E_OK;
    }
    else
    {

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
            else
            {

            }

            if(pMsgContext->reqDataLen>1u)
            {
                dataReturnValue_u8 = DcmAppl_Dcm_CheckPermissionForTransferData(dataReceivedBlockSequenceNr_u8,
                        Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                        Dcm_DataTransfer_st.dataMemoryAddress_u32,
                        &s_dataCurrentBlockSize_u32,
                        &pMsgContext->reqData[1],
                        (pMsgContext->reqDataLen)-1u,
                        dataTransferDirection_ten,
                        dataNegRespCode_u8
                );
            }

            else
            {
                dataReturnValue_u8 = DcmAppl_Dcm_CheckPermissionForTransferData(dataReceivedBlockSequenceNr_u8,
                        Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                        Dcm_DataTransfer_st.dataMemoryAddress_u32,
                        &s_dataCurrentBlockSize_u32,
                        NULL_PTR,
                        0,
                        dataTransferDirection_ten,
                        dataNegRespCode_u8
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
            else
            {
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

                if(dataReceivedBlockSequenceNr_u8!=(Dcm_TransferData_st.cntCurrentBlockCount))
                {

                    dataReadMemRetValue_en =  DcmAppl_Dcm_ReadMemory(s_stTransferOpstatus_u8,
                            Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                            Dcm_DataTransfer_st.dataMemoryAddress_u32,
                            s_dataCurrentBlockSize_u32,
                            &pMsgContext->resData[1],
                            dataNegRespCode_u8);
                }
                else
                {

                    dataReadMemRetValue_en = DCM_READ_OK;
                }
            }
            else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
            {

                if(dataReceivedBlockSequenceNr_u8!=(Dcm_TransferData_st.cntCurrentBlockCount))
                {

                    dataWriteMemRetValue_en =  DcmAppl_Dcm_WriteMemory(s_stTransferOpstatus_u8,
                            Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                            Dcm_DataTransfer_st.dataMemoryAddress_u32,
                            s_dataCurrentBlockSize_u32,
                            &pMsgContext->reqData[1],
                            dataNegRespCode_u8);
                }
                else
                {

                    dataWriteMemRetValue_en = DCM_WRITE_OK;
                }
            }
            else
            {

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
                else
                {

                }

                if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                {

                    pMsgContext->resDataLen =  s_dataCurrentBlockSize_u32+1u;
                }
                else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                {

                    pMsgContext->resDataLen =  1u;
                }
                else
                {

                }

                pMsgContext->resData[0]= dataReceivedBlockSequenceNr_u8;

                s_stTransferDataState_en  = DCM_DSP_TRANSFERDATA_IDLE;

                s_stTransferOpstatus_u8    = DCM_INITIAL;

                dataServRetValue_u8=E_OK;

            }
            else
            {

                s_stTransferOpstatus_u8 = DCM_INITIAL;

                if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                {
                    if(*dataNegRespCode_u8 == 0x00)
                    {

                        *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
                    }
                }
                else
                {
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

static uint32 Dcm_GetLastBlockSize(void)
{
    uint32 dataLastBlockSize_u32;

    if((Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u))==0u)
    {
        dataLastBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u;
    }

    else
    {
        dataLastBlockSize_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u));
    }
    return dataLastBlockSize_u32;
}

#endif

static Std_ReturnType Dcm_CheckNRCfromApplication(uint32 dataLengthReceived_u32,
                                                                 Dcm_NegativeResponseCodeType * dataNegResponseCode_u8)
{
    uint8 dataReturnValue_u8;
    Dcm_TrasferDirection_en dataTransferDirection_ten = DCM_TRANSFER_NOT_AVAILABLE;
    dataReturnValue_u8 = E_OK;
    if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
    {

        dataTransferDirection_ten = DCM_UPLOAD;
    }
    else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
    {

        dataTransferDirection_ten = DCM_DOWNLOAD;
    }
    else
    {

    }

    (void)DcmAppl_DcmMemSizeCheckForTransferData(Dcm_DataTransfer_st.compressionMethod_u8,
            Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
            dataLengthReceived_u32,
            dataTransferDirection_ten,
            dataNegResponseCode_u8);
    if(*dataNegResponseCode_u8 != 0)
    {
        dataReturnValue_u8 = E_NOT_OK;
    }
    return dataReturnValue_u8;
}

void Dcm_DspDeactivateRequestUploadDownloadPermission(void)
{

    Dcm_DataTransfer_st.isDownloadStarted_b       = FALSE;

    Dcm_DataTransfer_st.isUploadStarted_b       = FALSE;
    Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = 0x00;
    Dcm_TransferData_st.cntCurrentBlockCount = 0x00;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
	Dcm_DataTransfer_st.compressionMethod_u8  = 0x00;
}

 void Dcm_Lok_DspReqTrfExitConfirmation(
	Dcm_IdContextType dataIdContext_u8,
	PduIdType dataRxPduId_u8,
	uint16 dataSourceAddress_u16,
	Dcm_ConfirmationStatusType status_u8)
{
#if( DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)
            if(status_u8 == DCM_RES_POS_OK)
            {
                Dcm_DspDeactivateRequestUploadDownloadPermission();
            }
#endif
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
																	status_u8);
}

boolean Dcm_GetRequestUploadStatus(void)
{
    return (Dcm_DataTransfer_st.isUploadStarted_b);
}

boolean Dcm_GetRequestDownloadStatus(void)
{
    return (Dcm_DataTransfer_st.isDownloadStarted_b);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

