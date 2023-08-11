

#include "DcmDspUds_RequestTransferExit_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static Dcm_OpStatusType Dcm_stRequestTranferExitOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_Dsp_RequestTransferExit_Ini (void)
{
    Dcm_NegativeResponseCodeType dataNegResCode_u8;
    uint32 transferResponseParameterRecordSize_u32;

    if(Dcm_stRequestTranferExitOpstatus_u8 == DCM_PENDING)
    {

        (void)DcmAppl_Dcm_ProcessRequestTransferExit( DCM_CANCEL,NULL_PTR,0,NULL_PTR,&transferResponseParameterRecordSize_u32,&dataNegResCode_u8);
        (void)dataNegResCode_u8;
        (void)transferResponseParameterRecordSize_u32;
    }

    Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;

    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

Std_ReturnType Dcm_DcmRequestTransferExit (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Std_ReturnType dataRetVal_u8;
    uint32 transferRequestParameterRecordSize_u32;
    uint32 transferResponseParameterRecordSize_u32;
    boolean getDownloadStatus_b = FALSE;
    boolean getUploadStatus_b = FALSE;

    *dataNegRespCode_u8 = 0x00;
    transferResponseParameterRecordSize_u32 = 0x00;
    dataRetVal_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

    if (OpStatus == DCM_CANCEL)
    {

        Dcm_Dsp_RequestTransferExit_Ini();

        dataRetVal_u8 = E_OK;
    }
    else
    {

        getUploadStatus_b = Dcm_GetRequestUploadStatus();
        getDownloadStatus_b = Dcm_GetRequestDownloadStatus();

        if((getUploadStatus_b != FALSE )||(getDownloadStatus_b != FALSE ))
        {

            if((Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&(Dcm_TransferData_st.dataTransferedDataSize_u32 != Dcm_DataTransfer_st.dataMemorySize_u32))
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
            }
            else if(*dataNegRespCode_u8==0)
            {

                transferRequestParameterRecordSize_u32 = pMsgContext->reqDataLen;

                if(transferRequestParameterRecordSize_u32 >0u)
                {
                    dataRetVal_u8 = DcmAppl_Dcm_ProcessRequestTransferExit(  Dcm_stRequestTranferExitOpstatus_u8,
                            &pMsgContext->reqData[0],
                            transferRequestParameterRecordSize_u32,
                            &pMsgContext->resData[0],
                            &transferResponseParameterRecordSize_u32,
                            dataNegRespCode_u8);
                }

                else
                {
                    dataRetVal_u8 = DcmAppl_Dcm_ProcessRequestTransferExit(  Dcm_stRequestTranferExitOpstatus_u8,
                            NULL_PTR,
                            0,
                            &pMsgContext->resData[0],
                            &transferResponseParameterRecordSize_u32,
                            dataNegRespCode_u8);
                }

                if(dataRetVal_u8==E_OK)
                {
                    *dataNegRespCode_u8=0x00;

                    Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;

                    if(transferResponseParameterRecordSize_u32>pMsgContext->resMaxDataLen)
                    {
                        *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;

                        DCM_DET_ERROR(DCM_TRANSFEREXIT_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                    }
                    else
                    {

                        pMsgContext->resDataLen=transferResponseParameterRecordSize_u32;
                    }
                }

                else if(dataRetVal_u8==DCM_E_PENDING)
                {
                    *dataNegRespCode_u8=0x00;

                    Dcm_stRequestTranferExitOpstatus_u8 = DCM_PENDING;
                }

                else
                {
                    if(*dataNegRespCode_u8==0x00)
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }

                }
            }
            else
            {

            }
        }

        else
        {
            *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
        }

        if(*dataNegRespCode_u8!=0x00)
        {

            Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;

            Dcm_DspDeactivateRequestUploadDownloadPermission();
            dataRetVal_u8=E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

