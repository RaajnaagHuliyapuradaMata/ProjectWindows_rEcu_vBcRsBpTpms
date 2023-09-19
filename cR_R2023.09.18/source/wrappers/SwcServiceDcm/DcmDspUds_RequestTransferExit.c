#include "Std_Types.hpp"

#include "DcmDspUds_RequestTransferExit_Inf.hpp"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRequestTranferExitOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Dsp_RequestTransferExit_Ini (void){
   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8;
   VAR(uint32,AUTOMATIC) transferResponseParameterRecordSize_u32;

   if(Dcm_stRequestTranferExitOpstatus_u8 == DCM_PENDING)
   {

        (void)DcmAppl_Dcm_ProcessRequestTransferExit( DCM_CANCEL,NULL_PTR,0,NULL_PTR,&transferResponseParameterRecordSize_u32,&dataNegResCode_u8);
        (void)dataNegResCode_u8;
        (void)transferResponseParameterRecordSize_u32;
   }

    Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;

    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tRequestTransferExit (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType,AUTOMATIC)  dataRetVal_u8;
   VAR(uint32,AUTOMATIC) transferRequestParameterRecordSize_u32;
   VAR(uint32,AUTOMATIC) transferResponseParameterRecordSize_u32;
   VAR(boolean,AUTOMATIC) getDownloadStatus_b = FALSE;
   VAR(boolean,AUTOMATIC) getUploadStatus_b = FALSE;

    *dataNegRespCode_u8 = 0x00;
    transferResponseParameterRecordSize_u32 = 0x00;
    dataRetVal_u8=DCM_E_PENDING;

    DCM_UNUSED_PARAM(OpStatus);

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_RequestTransferExit_Ini();

        dataRetVal_u8 = E_OK;
   }
   else{

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
                    dataRetVal_u8 = DcmAppl_Dcm_ProcessRequestTransferExit(  Dcm_stRequestTranferExitOpstatus_u8
   ,     &pMsgContext->reqData[0]
   ,     transferRequestParameterRecordSize_u32
   ,     &pMsgContext->resData[0]
   ,     &transferResponseParameterRecordSize_u32
   ,     dataNegRespCode_u8);
                }

                else{
                    dataRetVal_u8 = DcmAppl_Dcm_ProcessRequestTransferExit(  Dcm_stRequestTranferExitOpstatus_u8
   ,     NULL_PTR
   ,     0
   ,     &pMsgContext->resData[0]
   ,     &transferResponseParameterRecordSize_u32
   ,     dataNegRespCode_u8);
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

                else{
                    if(*dataNegRespCode_u8==0x00)
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }

                }
            }
            else{

            }
        }

        else{
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
#include "Dcm_Cfg_MemMap.hpp"
#endif

