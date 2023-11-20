#include "Std_Types.hpp"

#include "DcmDspUds_Dsc_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Dsc_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_DscStateType_ten,DCM_VAR) Dcm_stDsc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8,     DCM_VAR) Dcm_ctDiaSess_u8;
VAR(uint8,     DCM_VAR) Dcm_ReqSess_u8;

static VAR(Dcm_SesCtrlType,DCM_VAR) s_stDspDscActiveSession_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Dsp_DscIni(void){

    Dcm_stDsc_en = DCM_DSP_DSC_INIT;
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

    Dcm_ResetBootLoader();
#endif
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tDiagnosticSessionControl (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
   VAR(uint16,AUTOMATIC) dataTimingValue_u16;
#endif
   VAR(uint8_least,     AUTOMATIC) idxLoop_qu8;
   VAR(Std_ReturnType,     AUTOMATIC) dataRetVal_u8;

    *dataNegRespCode_u8 = 0x00;
    dataRetVal_u8 = E_NOT_OK;

   if(OpStatus == DCM_CANCEL)
   {
        Dcm_Dsp_DscIni();
        dataRetVal_u8 = E_OK;
   }
   else{

        if(Dcm_stDsc_en == DCM_DSP_DSC_INIT)
        {

            Dcm_ReqSess_u8 = pMsgContext->reqData[DCM_DSP_DSC_POSITION_SUBFUNC];

            for(idxLoop_qu8 = 0; idxLoop_qu8 < DCM_CFG_DSP_NUMSESSIONS; idxLoop_qu8++)
            {
                if(Dcm_ReqSess_u8 == Dcm_Dsp_Session[idxLoop_qu8].session_level)
                {
                    break;
                }
            }

            if(idxLoop_qu8 < DCM_CFG_DSP_NUMSESSIONS)
            {

                if(pMsgContext->reqDataLen == DCM_DSP_DSC_REQ_LEN)
                {

                    dataRetVal_u8 = Dcm_GetSesCtrlType(&s_stDspDscActiveSession_u8);

                    if(dataRetVal_u8 == E_OK)
                    {

                        Dcm_ctDiaSess_u8 = (uint8)idxLoop_qu8;

                        Dcm_stDsc_en     = DCM_DSP_DSC_CHECK_PERMISSION;

                    }
                    else
                    {

                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
                }

                else{
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                DCM_DET_ERROR(DCM_DSC_ID , DCM_E_SESSION_NOT_CONFIGURED )
            }

            if(*dataNegRespCode_u8 != 0x0)
            {
                Dcm_stDsc_en     = DCM_DSP_DSC_ERROR;
            }
        }

        if(Dcm_stDsc_en == DCM_DSP_DSC_CHECK_PERMISSION)
        {

            dataRetVal_u8 = DcmAppl_DcmGetSesChgPermission(s_stDspDscActiveSession_u8
   ,     Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level
   ,     dataNegRespCode_u8);

            if(dataRetVal_u8 == E_OK)
            {
                *dataNegRespCode_u8=0x00;
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

                if((Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_OEM_BOOT)||
                        (Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_SYS_BOOT))
                {
                    Dcm_stDsc_en = DCM_DSP_DSC_WAIT;
                }

                else
#endif
                {
                    Dcm_stDsc_en = DCM_DSP_DSC_SEND_RESP;
                }
            }

            else if(dataRetVal_u8 == DCM_E_PENDING)
            {
                *dataNegRespCode_u8=0x00;

            }

            else{
                if(*dataNegRespCode_u8 == 0)
                {
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }

            if(*dataNegRespCode_u8 != 0x0)
            {
                Dcm_stDsc_en     = DCM_DSP_DSC_ERROR;
            }
        }

        if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
        {
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
            if(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_OEM_BOOT )
            {
                Dcm_JumpToBootLoader(DCM_JUMPTOOEMBOOTLOADER,dataNegRespCode_u8);
            }
            if(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_SYS_BOOT)
            {
                Dcm_JumpToBootLoader(DCM_JUMPTOSYSSUPPLIERBOOTLOADER,dataNegRespCode_u8);
            }
#endif
            dataRetVal_u8 = DCM_E_PENDING;
        }

        if(Dcm_stDsc_en == DCM_DSP_DSC_SEND_RESP)
        {

            pMsgContext->resDataLen = DCM_DSP_DSC_RESP_LEN;

            pMsgContext->resData[0] = Dcm_ReqSess_u8;

#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)

            dataTimingValue_u16         = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000u);
            pMsgContext->resData[1] = (uint8)(dataTimingValue_u16 >> 8u);
            pMsgContext->resData[2] = (uint8)(dataTimingValue_u16 & 0x00ffu);

            dataTimingValue_u16         = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000u);
            pMsgContext->resData[3] = (uint8)(dataTimingValue_u16 >> 8u);
            pMsgContext->resData[4] = (uint8)(dataTimingValue_u16 & 0x00ffu);
#endif
            dataRetVal_u8 = E_OK;
        }

        if(Dcm_stDsc_en == DCM_DSP_DSC_ERROR)
        {

            if(*dataNegRespCode_u8==0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }

            Dcm_stDsc_en = DCM_DSP_DSC_INIT;
            dataRetVal_u8 = E_NOT_OK;
        }
   }
    return dataRetVal_u8;
}

static FUNC(void,DCM_CODE) Dcm_Dsp_DscChgSession(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status)
{
   VAR(uint8,AUTOMATIC) dataReqSess_u8;

   if( (status == DCM_RES_POS_OK) || (status == DCM_RES_POS_NOT_OK) )
   {

        if(Dcm_stDsc_en == DCM_DSP_DSC_SEND_RESP)
        {

            dataReqSess_u8  = Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level;

            Dcm_DsldSetsessionTiming(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32
   ,     Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32);

            Dcm_Lok_SetSesCtrlType(dataReqSess_u8);
        }
   }

    Dcm_Dsp_DscIni();
    return;
}

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
FUNC(void, DCM_CODE) Dcm_GetP2Timings(
        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2Timing_pu32
   ,     P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2StarTiming_pu32
   ,     VAR(Dcm_SesCtrlType, AUTOMATIC) dSessionId
)
{
   VAR(uint8_least,AUTOMATIC)  idxSessionId_qu8;

   for(idxSessionId_qu8 = 0; idxSessionId_qu8 < DCM_CFG_DSP_NUMSESSIONS; idxSessionId_qu8++)
   {
        if(dSessionId == Dcm_Dsp_Session[idxSessionId_qu8].session_level)
        {

            SchM_Enter_Dcm_DsldTimer_NoNest();
            *dP2Timing_pu32 = Dcm_Dsp_Session[idxSessionId_qu8].P2_max_u32;
            *dP2StarTiming_pu32 = Dcm_Dsp_Session[idxSessionId_qu8].P2str_max_u32;
            SchM_Exit_Dcm_DsldTimer_NoNest();

            break;
        }
        else{

        }
   }
   if(idxSessionId_qu8 == DCM_CFG_DSP_NUMSESSIONS)
   {

        DCM_DET_ERROR(DCM_GETP2TIMINGS_ID , DCM_E_SESSION_NOT_CONFIGURED )
   }

    return;
}
#endif

FUNC(void, DCM_CODE) Dcm_Lok_DspDscConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
){
   if( (status_u8 == DCM_RES_POS_OK) || (status_u8 == DCM_RES_POS_NOT_OK) ){
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   	(void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(Dcm_Dsp_Session
   											[Dcm_ctDiaSess_u8].SessionMode);
#endif
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
   	if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT){
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   		(void)SchM_Switch_SwcServiceDcm_tEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
#endif
   			Dcm_acceptRequests_b = FALSE;
   	}
#endif
   }
   Dcm_Dsp_DscChgSession(status_u8);

#if DCM_ROE_ENABLED != DCM_CFG_OFF
     Dcm_ResetROEEvents();
#endif

DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  status_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

