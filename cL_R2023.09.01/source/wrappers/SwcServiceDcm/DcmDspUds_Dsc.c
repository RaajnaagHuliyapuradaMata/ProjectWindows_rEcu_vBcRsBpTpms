
#include "DcmDspUds_Dsc_Inf.hpp"
#include "Rte_Dcm.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Dsc_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_DscStateType_ten Dcm_stDsc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
uint8 Dcm_ctDiaSess_u8;
uint8 Dcm_ReqSess_u8;

static Dcm_SesCtrlType s_stDspDscActiveSession_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_Dsp_DscIni(void){

    Dcm_stDsc_en = DCM_DSP_DSC_INIT;
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

    Dcm_ResetBootLoader();
#endif
}

Std_ReturnType SwcServiceDcm_tDiagnosticSessionControl (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
   uint16 dataTimingValue_u16;
#endif
   uint8_least idxLoop_qu8;
    Std_ReturnType dataRetVal_u8;

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
                if(Dcm_ReqSess_u8 == CfgSwcServiceDcm_astListSession[idxLoop_qu8].session_level)
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
   ,                   CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].session_level
   ,                   dataNegRespCode_u8);

            if(dataRetVal_u8 == E_OK)
            {
                *dataNegRespCode_u8=0x00;
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

                if((CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].sessionForBoot == DCM_OEM_BOOT)||
                        (CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].sessionForBoot == DCM_SYS_BOOT))
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
            if(CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].sessionForBoot == DCM_OEM_BOOT )
            {
                Dcm_JumpToBootLoader(DCM_JUMPTOOEMBOOTLOADER,dataNegRespCode_u8);
            }
            if(CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].sessionForBoot == DCM_SYS_BOOT)
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

            dataTimingValue_u16         = (uint16)(CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].P2_max_u32 / 1000u);
            pMsgContext->resData[1] = (uint8)(dataTimingValue_u16 >> 8u);
            pMsgContext->resData[2] = (uint8)(dataTimingValue_u16 & 0x00ffu);

            dataTimingValue_u16         = (uint16)(CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].P2str_max_u32/10000u);
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

static void Dcm_Dsp_DscChgSession(Dcm_ConfirmationStatusType status)
{
   uint8 dataReqSess_u8;

   if( (status == DCM_RES_POS_OK) || (status == DCM_RES_POS_NOT_OK) )
   {

        if(Dcm_stDsc_en == DCM_DSP_DSC_SEND_RESP)
        {

            dataReqSess_u8  = CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].session_level;

            Dcm_DsldSetsessionTiming(CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].P2str_max_u32
   ,                   CfgSwcServiceDcm_astListSession[Dcm_ctDiaSess_u8].P2_max_u32);

            Dcm_Lok_SetSesCtrlType(dataReqSess_u8);
        }
   }

    Dcm_Dsp_DscIni();
    return;
}

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
void Dcm_GetP2Timings(
        uint32 * dP2Timing_pu32
   ,       uint32 * dP2StarTiming_pu32
   ,       Dcm_SesCtrlType dSessionId
)
{
   uint8_least idxSessionId_qu8;

   for(idxSessionId_qu8 = 0; idxSessionId_qu8 < DCM_CFG_DSP_NUMSESSIONS; idxSessionId_qu8++)
   {
        if(dSessionId == CfgSwcServiceDcm_astListSession[idxSessionId_qu8].session_level)
        {

            SchM_Enter_Dcm_DsldTimer_NoNest();
            *dP2Timing_pu32 = CfgSwcServiceDcm_astListSession[idxSessionId_qu8].P2_max_u32;
            *dP2StarTiming_pu32 = CfgSwcServiceDcm_astListSession[idxSessionId_qu8].P2str_max_u32;
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

void Dcm_Lok_DspDscConfirmation(
   Dcm_IdContextType dataIdContext_u8
   ,  PduIdType dataRxPduId_u8
   ,  uint16 dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8)
{
   if( (status_u8 == DCM_RES_POS_OK) || (status_u8 == DCM_RES_POS_NOT_OK) )
   {
   	#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   	(void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(CfgSwcServiceDcm_astListSession
   											[Dcm_ctDiaSess_u8].SessionMode);
   	#endif
   	(void)DcmAppl_Switch_DcmDiagnosticSessionControl(CfgSwcServiceDcm_astListSession
   										[Dcm_ctDiaSess_u8].session_level);
   	#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
   	if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
   	{
   		#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   		(void)SchM_Switch_SwcServiceDcm_tEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
   		#endif
   		(void)DcmAppl_Switch_DcmExecuteDscReset(CfgSwcServiceDcm_astListSession
   										[Dcm_ctDiaSess_u8].session_level);
   		(void)DcmAppl_Switch_DcmExecuteReset();

   			Dcm_acceptRequests_b = FALSE;
   	}
   	#endif
   }

   Dcm_Dsp_DscChgSession(status_u8);

#if DCM_ROE_ENABLED != DCM_CFG_OFF
     Dcm_ResetROEEvents();
#endif

DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16
   ,  																status_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

