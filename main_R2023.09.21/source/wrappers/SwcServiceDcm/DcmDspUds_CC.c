#include "Std_Types.hpp"

#include "DcmDspUds_Uds_Inf.hpp"

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )

#define DCM_DSP_CC_COMMTYPEMSK  0x0Fu
#define DCM_DSP_CC_REQLEN       0x02u
#define DCM_DSP_CC_RESLEN       0x01u
#define DCM_DSP_CC_POSCTRLTYPE  0x00u
#define DCM_DSP_CC_POSCOMMTYPE  0x01u
#define DCM_DSP_CC_SUBNETMASK   0xF0u
#define DCM_SUBNET_DISEN_SPECIFIED_COMTYPE 0x0
#define DCM_SUBNET_DISEN_REQUEST_RECIEVED_NODE 0xF
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

static VAR(Dcm_CommunicationModeType,DCM_VAR) Dcm_stCommunicationMode_u8 ;

static VAR(uint8,DCM_VAR) Dcm_idxCommChannel_u8 ;

static VAR(NetworkHandleType,AUTOMATIC) Dcm_nrSubNet_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(Dcm_CommunicationModeType,DCM_CODE) Dcm_Lok_GetCommModeType_u8(VAR(uint8,AUTOMATIC) ControlType_u8
   ,     VAR(uint8,AUTOMATIC) dataCommType_u8 )
{

   VAR(uint8,AUTOMATIC) adrComModeIndex_au8[4]={0,0,4,8};

   VAR(Dcm_CommunicationModeType,AUTOMATIC) CommModeType[12] =
   {
            DCM_ENABLE_RX_TX_NORM
   ,     DCM_ENABLE_RX_DISABLE_TX_NORM
   ,     DCM_DISABLE_RX_ENABLE_TX_NORM
   ,     DCM_DISABLE_RX_TX_NORMAL
   ,     DCM_ENABLE_RX_TX_NM
   ,     DCM_ENABLE_RX_DISABLE_TX_NM
   ,     DCM_DISABLE_RX_ENABLE_TX_NM
   ,     DCM_DISABLE_RX_TX_NM
   ,     DCM_ENABLE_RX_TX_NORM_NM
   ,     DCM_ENABLE_RX_DISABLE_TX_NORM_NM
   ,     DCM_DISABLE_RX_ENABLE_TX_NORM_NM
   ,     DCM_DISABLE_RX_TX_NORM_NM
   };

    return(CommModeType[adrComModeIndex_au8[dataCommType_u8]+ControlType_u8]);
}

#if( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
static FUNC(uint8,DCM_CODE) Dcm_Lok_DspChkSubnetID_u8(VAR(NetworkHandleType,AUTOMATIC) dataSubnetID_u8
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint8,AUTOMATIC) idxIndex_u8;
   VAR(uint8,AUTOMATIC) dataReturnVal_u8;

   for(idxIndex_u8 =0;idxIndex_u8<DCM_CFG_NUM_SPECIFIC_SUBNETS;idxIndex_u8++)
   {
        if(Dcm_specific_subnet_table[idxIndex_u8].SpecificSubNetId_u8 == dataSubnetID_u8)
        {
            break;
        }
   }
   if(idxIndex_u8 < DCM_CFG_NUM_SPECIFIC_SUBNETS)
   {
        dataReturnVal_u8 = idxIndex_u8;
   }
   else{
        dataReturnVal_u8 = DCM_CFG_NUM_SPECIFIC_SUBNETS;

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

        DCM_DET_ERROR(DCM_CC_ID , DCM_E_SUBNET_NOT_SUPPORTED )

   }
    return(dataReturnVal_u8);
}

#endif

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_CC_Check(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint8,AUTOMATIC) dataCommType_u8;
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

   if(pMsgContext->reqDataLen== DCM_DSP_CC_REQLEN)
   {
        dataCommType_u8 = (pMsgContext->reqData[DCM_DSP_CC_POSCOMMTYPE] & DCM_DSP_CC_COMMTYPEMSK);
        if((dataCommType_u8 > 0x0) && (dataCommType_u8 < 0x4))
        {
            retVal_u8 = DcmAppl_DcmCommControlConditionCheck(pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE]
   ,     dataCommType_u8,&pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE],((uint16)(pMsgContext->reqDataLen))
   ,     dataNegRespCode_u8);
            if(E_OK == retVal_u8)
            {
                *dataNegRespCode_u8=0x00;

                Dcm_stCommunicationMode_u8 = Dcm_Lok_GetCommModeType_u8(pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE]
   ,     dataCommType_u8);

                Dcm_nrSubNet_u8 = (uint8)(pMsgContext->reqData[DCM_DSP_CC_POSCOMMTYPE] & (uint8)DCM_DSP_CC_SUBNETMASK);
                Dcm_nrSubNet_u8 =  Dcm_nrSubNet_u8>>4u;

                switch(Dcm_nrSubNet_u8)
                {
                    case DCM_SUBNET_DISEN_REQUEST_RECIEVED_NODE:

                    Dcm_idxCommChannel_u8 = Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId;
                         break;

                    case DCM_SUBNET_DISEN_SPECIFIED_COMTYPE:
                        \
                         break;

                    default :
#if( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )

                        Dcm_idxCommChannel_u8 = Dcm_Lok_DspChkSubnetID_u8(Dcm_nrSubNet_u8,dataNegRespCode_u8);
                        retVal_u8 = ((*dataNegRespCode_u8==DCM_E_REQUESTOUTOFRANGE) ? E_NOT_OK : E_OK);
#else
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        retVal_u8 = E_NOT_OK;

                        DCM_DET_ERROR(DCM_CC_ID , DCM_E_SUBNET_NOT_SUPPORTED )

#endif
                        break;
                }

            }
            else{

                if(0x00 == *dataNegRespCode_u8)
                {

                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

                }
            }
        }
        else{

            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            retVal_u8 = E_NOT_OK;

        }
   }
   else{
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        retVal_u8 = E_NOT_OK;

   }

   return retVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tCommunicationControl (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    *dataNegRespCode_u8 = 0x00;
    retVal_u8 = E_NOT_OK;

   if(OpStatus == DCM_CANCEL)
   {

        retVal_u8 = E_OK;
   }
   else{

        if(E_OK == Dcm_Lok_CC_Check(pMsgContext,dataNegRespCode_u8))
        {
            retVal_u8 = E_OK;

            pMsgContext->resDataLen   = DCM_DSP_CC_RESLEN;

            pMsgContext->resData[DCM_DSP_CC_POSCTRLTYPE] = pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE];

        }

   }
    return retVal_u8;
}

static FUNC(void,DCM_CODE) Dcm_Lok_DspCommunicationControlSwitchMode(void){
   VAR(uint8,AUTOMATIC)idxIndex_u8;
   if( Dcm_nrSubNet_u8 == 0)
   {
        for(idxIndex_u8=0;idxIndex_u8 < DCM_CFG_NUM_ALLCHANNELS_MODE_INFO;idxIndex_u8++)
        {
#if(DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId
   ,     Dcm_stCommunicationMode_u8);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
            (void)((*(Dcm_AllChannels_ForModeInfo[idxIndex_u8].switch_fp))(Dcm_stCommunicationMode_u8));
#endif
            DcmAppl_DcmSwitchCommunicationControl(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId
   ,     Dcm_stCommunicationMode_u8);
        }
   }
#if( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
   else if(( Dcm_nrSubNet_u8 != 0 ) && ( Dcm_nrSubNet_u8 != 0xF ))
   {
#if(DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
        BswM_Dcm_CommunicationMode_CurrentState(Dcm_specific_subnet_table[Dcm_idxCommChannel_u8].SpecificComMChannelId
   ,     Dcm_stCommunicationMode_u8);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
        (void)((*(Dcm_specific_subnet_table[Dcm_idxCommChannel_u8].switch_fp))(Dcm_stCommunicationMode_u8));
#endif
        DcmAppl_DcmSwitchCommunicationControl(Dcm_specific_subnet_table[Dcm_idxCommChannel_u8].SpecificComMChannelId
   ,     Dcm_stCommunicationMode_u8);
   }
#endif
   else{

        for(idxIndex_u8=0; idxIndex_u8 < DCM_CFG_NUM_ALLCHANNELS_MODE_INFO;idxIndex_u8++)
        {
            if(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId == Dcm_idxCommChannel_u8)
            {
#if(DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
                BswM_Dcm_CommunicationMode_CurrentState(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId
   ,     Dcm_stCommunicationMode_u8);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
                (void)((*(Dcm_AllChannels_ForModeInfo[idxIndex_u8].switch_fp))(Dcm_stCommunicationMode_u8));
#endif
                DcmAppl_DcmSwitchCommunicationControl(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId
   ,     Dcm_stCommunicationMode_u8);
                break;
            }
        }
   }
}

FUNC(void, DCM_CODE) Dcm_Lok_DspCommCntrlConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
   if((status_u8 == DCM_RES_POS_OK)||(status_u8 == DCM_RES_POS_NOT_OK))
   {
        Dcm_Lok_DspCommunicationControlSwitchMode();
   }
    DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,status_u8);
}

static FUNC(boolean, DCM_CODE) Dcm_Lok_CCMmodeStatusCheck(void){

   VAR(uint8,AUTOMATIC)    dataNRC_u8;
   VAR(boolean,AUTOMATIC)  flgStatus_b;
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

    flgStatus_b = TRUE;
    dataNRC_u8 = 0x00;

   if(Dcm_ComMUserReEnableModeRuleRef !=NULL_PTR)
   {
        retVal_u8 = (*Dcm_ComMUserReEnableModeRuleRef)();

        if((retVal_u8!=E_OK))
        {

            flgStatus_b = FALSE;
        }
   }

#if(DCM_CFG_DSP_MODERULEFORCC!=DCM_CFG_OFF)

   if((flgStatus_b!=FALSE) && (Dcm_ComMReEnableModeRuleRef != NULL_PTR))
   {
        flgStatus_b = (*Dcm_ComMReEnableModeRuleRef)(&dataNRC_u8);
   }
#endif

   if(dataNRC_u8 != 0u)
   {

        flgStatus_b = FALSE;

   }

    return flgStatus_b;
}

static FUNC(void,DCM_CODE) Dcm_Lok_ResetCommunicationMode(void){
   VAR(uint8,AUTOMATIC)    idxLoop_u8;
   VAR(boolean,AUTOMATIC)  stStatus_b;

   for(idxLoop_u8=0;idxLoop_u8 < DCM_CFG_NUM_ALLCHANNELS_MODE_INFO;idxLoop_u8++)
   {

#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
        stStatus_b = (*(Dcm_AllChannels_ForModeInfo[idxLoop_u8].checkmode_fp))();
#else
        stStatus_b = DcmAppl_DcmIsComModeDefault(Dcm_AllChannels_ForModeInfo[idxLoop_u8].AllComMChannelId);
#endif

        if(stStatus_b == FALSE)
        {

#if(DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_AllChannels_ForModeInfo[idxLoop_u8].AllComMChannelId
   ,     DCM_ENABLE_RX_TX_NORM_NM);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
            (void)((*(Dcm_AllChannels_ForModeInfo[idxLoop_u8].switch_fp))(DCM_ENABLE_RX_TX_NORM_NM));
#endif
            DcmAppl_DcmSwitchCommunicationControl(Dcm_AllChannels_ForModeInfo[idxLoop_u8].AllComMChannelId
   ,     DCM_ENABLE_RX_TX_NORM_NM);
        }
        else{

        }
   }

#if( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
   for(idxLoop_u8=0;idxLoop_u8 < DCM_CFG_NUM_SPECIFIC_SUBNETS;idxLoop_u8++)
   {

#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
        stStatus_b = (*(Dcm_specific_subnet_table[idxLoop_u8].checkmode_fp))();
#else
        stStatus_b = DcmAppl_DcmIsComModeDefault(Dcm_specific_subnet_table[idxLoop_u8].SpecificComMChannelId);
#endif

        if(stStatus_b == FALSE)
        {

#if(DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_specific_subnet_table[idxLoop_u8].SpecificComMChannelId
   ,     DCM_ENABLE_RX_TX_NORM_NM);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
            (void)((*(Dcm_specific_subnet_table[idxLoop_u8].switch_fp))(DCM_ENABLE_RX_TX_NORM_NM));
#endif
            DcmAppl_DcmSwitchCommunicationControl(Dcm_specific_subnet_table[idxLoop_u8].SpecificComMChannelId
   ,     DCM_ENABLE_RX_TX_NORM_NM);
        }
        else{

        }
   }
#endif
}

FUNC(void,DCM_CODE) Dcm_Lok_CC_Mainfunction (void){

   VAR(Dcm_SesCtrlType,DCM_VAR) ActiveSession_u8;
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

   VAR(boolean,AUTOMATIC)  CC_Resetmoderuleflg_b;
   VAR(boolean,AUTOMATIC)  CC_Resetsessionflg_b;

   CC_Resetsessionflg_b = TRUE;
   CC_Resetmoderuleflg_b = Dcm_Lok_CCMmodeStatusCheck();

    retVal_u8 = Dcm_GetSesCtrlType(&ActiveSession_u8);

   if((retVal_u8 == E_OK)&&(Dcm_CC_ActiveSession_u8 != ActiveSession_u8))
   {
        // session changed and new session stored
        Dcm_CC_ActiveSession_u8 =  ActiveSession_u8;
        if( ActiveSession_u8 != DCM_DEFAULT_SESSION )
        {
            CC_Resetsessionflg_b = Dcm_Lok_CC_IsSupportedInSession(ActiveSession_u8);
        }
        else{
            CC_Resetsessionflg_b = FALSE;
        }
   }
   if((CC_Resetsessionflg_b == FALSE)||(CC_Resetmoderuleflg_b == FALSE ))
   {
        Dcm_Lok_ResetCommunicationMode();
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

