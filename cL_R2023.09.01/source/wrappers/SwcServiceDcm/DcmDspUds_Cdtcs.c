
#warning "1 ok"
#include "DcmDspUds_Cdtcs_Inf.hpp"
#warning "2 ok"
#include "DcmDsp_Lib_Prv.hpp"
#warning "3 ok"
#include "Rte_Dcm.hpp"
#warning "4 ok"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static boolean Dcm_Cdtcs_IsReEnablePending_b=FALSE;
static boolean Dcm_Cdtcs_IsPermisionPending_b=FALSE;
static boolean Dcm_Cdtcs_ProceedPermissionHandling_b=FALSE;
static boolean Dcm_Cdtcs_IsDisableInProgress_b=FALSE;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_DspCDTCStatus_b = TRUE;
#define DCM_STOP_SEC_VAR_INIT_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 Dcm_Cdtcs_SettingType_u8;
static uint8 Dcm_Cdtcs_CurrentClientId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
static const uint8 Dcm_CdtcsNoNrc_u8=0x00;
#define DCM_STOP_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_16
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_SUPPORTCDTCRECORD != DCM_CFG_ON)
static const uint16 Dcm_CdtcsExpectedRequestLength_u16 = 1;
#endif
static const uint16 Dcm_CdtcsResponseLength_u16 = 1;
static const uint16 Dcm_CdtcsExpectedTotalLength_u16 = 4;
#define DCM_STOP_SEC_CONST_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_32
#include "Dcm_Cfg_MemMap.hpp"
static const uint32 Dcm_CdtcsValidRecord_u32=0xFFFFFF;
#define DCM_STOP_SEC_CONST_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_CDTCS_ON 1
#define DCM_CDTCS_OFF 2

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static Std_ReturnType Dcm_CdtcsStartService (const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
static Std_ReturnType Dcm_CdtcsPerformService (Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
static Std_ReturnType Dcm_CdtcsIsRequestValid (const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
static boolean Dcm_CdtcsIsModeStatusCheckPassed (void);
static Std_ReturnType Dcm_CdtcsProcessServiceResult (Std_ReturnType Dem_Result, Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
static void Dcm_CdtcsInformApplication (void);

static Std_ReturnType Dcm_CdtcsProcessPermissionState (Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
static Std_ReturnType Dcm_CdtcsProcessDisablePermission (Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
static boolean Dcm_CdtcsProceedRequest ( const Dcm_MsgContextType* pMsgContext);

#if(DCM_CFG_DSP_SUPPORTCDTCRECORD == DCM_CFG_ON)
static Std_ReturnType Dcm_CdtcsIsControlOptionRecordValid (const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8);
#endif

Std_ReturnType SwcServiceDcm_tControlDTCSetting (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType serviceResult = E_NOT_OK;

   switch(OpStatus)
   {
        case DCM_CANCEL:
        if(!Dcm_Cdtcs_IsPermisionPending_b)
        {
            Dcm_Cdtcs_IsReEnablePending_b=TRUE;
        }
        else{
            Dcm_Cdtcs_ProceedPermissionHandling_b=TRUE;
        }

        serviceResult=E_OK;
        break;

        case DCM_INITIAL:
        serviceResult=Dcm_CdtcsStartService(pMsgContext, dataNegRespCode_u8);
        break;

        case DCM_CHECKDATA:
        serviceResult=Dcm_CdtcsProcessDisablePermission(dataNegRespCode_u8);
        break;

        case DCM_PROCESSSERVICE:

        if(Dcm_CdtcsProceedRequest(pMsgContext))
        {
            serviceResult=Dcm_CdtcsPerformService(dataNegRespCode_u8);
        }
        else{
            *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
        }
        break;

        default:

        break;

   }

   if((serviceResult==E_OK) && (OpStatus!=DCM_CANCEL))
   {
        pMsgContext->resDataLen = Dcm_CdtcsResponseLength_u16;

        pMsgContext->resData[DCM_PRV_CDTC_POSITION_SUBFUNC] = Dcm_Cdtcs_SettingType_u8;
   }

    return serviceResult;
}

static Std_ReturnType Dcm_CdtcsStartService (const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType startServiceResult = E_NOT_OK;

   if(!Dcm_Cdtcs_IsReEnablePending_b)
   {
        if(Dcm_CdtcsIsRequestValid(pMsgContext, dataNegRespCode_u8)!=E_NOT_OK)
        {
            Dcm_Cdtcs_CurrentClientId_u8=Dcm_Lok_GetDemClientId(DCM_UDSCONTEXT);

            Dcm_Cdtcs_SettingType_u8= *(pMsgContext->reqData);
            startServiceResult=Dcm_CdtcsProcessPermissionState(dataNegRespCode_u8);
        }
   }
   else{
        *dataNegRespCode_u8=DCM_E_BUSYREPEATREQUEST;
   }

    return startServiceResult;
}

static Std_ReturnType Dcm_CdtcsPerformService(Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType operationResult = E_NOT_OK;

   switch(Dcm_Cdtcs_SettingType_u8)
   {
        case DCM_CDTCS_ON:
        operationResult=Dem_EnableDTCSetting(Dcm_Cdtcs_CurrentClientId_u8);
        DcmAppl_EnableDTCSetting(operationResult);
        break;
        case DCM_CDTCS_OFF:
            operationResult=Dem_DisableDTCSetting(Dcm_Cdtcs_CurrentClientId_u8);
        break;
        default:
        *dataNegRespCode_u8=DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
   }

   if(*dataNegRespCode_u8==Dcm_CdtcsNoNrc_u8)
   {
        operationResult=Dcm_CdtcsProcessServiceResult(operationResult, dataNegRespCode_u8);
   }

    return operationResult;
}

static Std_ReturnType Dcm_CdtcsIsRequestValid (const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType requestValid = E_NOT_OK;

#if(DCM_CFG_DSP_SUPPORTCDTCRECORD == DCM_CFG_ON)
    requestValid=Dcm_CdtcsIsControlOptionRecordValid(pMsgContext, dataNegRespCode_u8);
#else
   if(pMsgContext->reqDataLen == Dcm_CdtcsExpectedRequestLength_u16)
   {
        requestValid = E_OK;
   }
   else{
        *dataNegRespCode_u8=DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
#endif

    return requestValid;
}

#if(DCM_CFG_DSP_SUPPORTCDTCRECORD == DCM_CFG_ON)
static Std_ReturnType Dcm_CdtcsIsControlOptionRecordValid (const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType controlOptionRecordValid = E_NOT_OK;
   uint32 controlOptionRecord=0x0;

   if((pMsgContext->reqDataLen == Dcm_CdtcsExpectedTotalLength_u16))
   {

        controlOptionRecord =((((uint32) pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC+1u]) << 16u) |
                (((uint32) pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC+2u]) << 8u) |
                ((uint32) pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC+3u]));

        if(DcmAppl_DcmCheckCDTCRecord(&pMsgContext->reqData[1], DCM_PRV_CDTC_RECORD_LENGTH, dataNegRespCode_u8)==E_OK)
        {
            if(controlOptionRecord==Dcm_CdtcsValidRecord_u32)
            {
                controlOptionRecordValid=E_OK;
            }
            else{
                *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
            }
        }
        else{
            if(*dataNegRespCode_u8==Dcm_CdtcsNoNrc_u8)
            {
                *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
            }
        }
   }
   else{
        *dataNegRespCode_u8=DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }

    return controlOptionRecordValid;
}
#endif

static boolean Dcm_CdtcsIsModeStatusCheckPassed (void){
   boolean flgModeRetval_b;
   uint8 dataNegRespCode_u8;
   boolean modeStatusCheckPassed=TRUE;
    dataNegRespCode_u8 =Dcm_CdtcsNoNrc_u8;

   if((Dcm_DspCDTCStatus_b == FALSE) || Dcm_Cdtcs_IsDisableInProgress_b)
   {

        flgModeRetval_b=Dcm_ControlDtcSettingModecheck_b(&dataNegRespCode_u8);

        if((flgModeRetval_b == FALSE) || (dataNegRespCode_u8 != 0u))
        {

            Dcm_Cdtcs_SettingType_u8=DCM_CDTCS_ON;
            modeStatusCheckPassed=FALSE;

        }

   }

    return modeStatusCheckPassed;
}

#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)

boolean Dcm_GetControlDTCSetting_EnableStatus(void){
    return (Dcm_DspCDTCStatus_b);
}
#endif

void Dcm_ControlDtcSettingExit(void){
   uint8 idxCdtc_u8;
   uint32 session_active_u32;
   uint32 allowed_session_u32;

   idxCdtc_u8 = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].cdtc_index_u8;

   if(idxCdtc_u8 != 0xFFu)
   {
        allowed_session_u32=CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxCdtc_u8].allowed_session_b32;
   }
   else{
        allowed_session_u32=0xffffffffu;
   }

   session_active_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSession_u8);

   if((session_active_u32 == ((uint32)DCM_DEFAULT_SESSION))||((allowed_session_u32 & session_active_u32) != session_active_u32))
   {

        if((Dcm_DspCDTCStatus_b == FALSE) || Dcm_Cdtcs_IsDisableInProgress_b)
        {
            Dcm_Cdtcs_SettingType_u8=DCM_CDTCS_ON;
            Dcm_Cdtcs_IsReEnablePending_b=TRUE;

        }

   }
}

void Dcm_Dsp_CDTCSIni(void){

    Dcm_DspCDTCStatus_b = TRUE;
}

void Dcm_Lok_Cdtcs_Mainfunction (void){
   uint8 dataNegRespCode_u8 =Dcm_CdtcsNoNrc_u8;
   boolean isModeCheckPassed=TRUE;

   isModeCheckPassed=Dcm_CdtcsIsModeStatusCheckPassed();

   if(Dcm_Cdtcs_ProceedPermissionHandling_b)
   {
        DcmAppl_DisableDTCSetting(&dataNegRespCode_u8);
        if(dataNegRespCode_u8==0x00)
        {
            Dcm_Cdtcs_IsReEnablePending_b=TRUE;
            Dcm_Cdtcs_ProceedPermissionHandling_b=FALSE;
        }
        if(dataNegRespCode_u8!=DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING)
        {
            Dcm_Cdtcs_ProceedPermissionHandling_b=FALSE;
        }
        else{

        }
   }

   if(Dcm_Cdtcs_IsReEnablePending_b||(!isModeCheckPassed))
   {

        if(DCM_E_PENDING == Dcm_CdtcsPerformService(&dataNegRespCode_u8))
        {
            Dcm_Cdtcs_IsReEnablePending_b=TRUE;
        }
        else{
            Dcm_Cdtcs_IsReEnablePending_b=FALSE;
        }
   }
}

static Std_ReturnType Dcm_CdtcsProcessServiceResult (Std_ReturnType Dem_Result, Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType processingResult = E_NOT_OK;

   switch(Dem_Result)
   {

        case E_OK:
        Dcm_CdtcsInformApplication();
        processingResult=E_OK;
        break;

        case E_NOT_OK:
        *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
        break;

        default:
        processingResult=DCM_E_PENDING;
        break;
   }

    return processingResult;
}

static void Dcm_CdtcsInformApplication (void){
   if(Dcm_Cdtcs_SettingType_u8==DCM_CDTCS_OFF)
   {
#if(DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_ON)
        (void)SchM_Switch_SwcServiceDcm_tControlDTCSetting(RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING);
#endif
        Dcm_DspCDTCStatus_b=FALSE;
        Dcm_Cdtcs_IsDisableInProgress_b=FALSE;
        DcmAppl_DcmControlDtcSettingEnableStatus(Dcm_DspCDTCStatus_b);
   }
   else{
#if(DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_ON)
        (void)SchM_Switch_SwcServiceDcm_tControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
        Dcm_DspCDTCStatus_b=TRUE;
        DcmAppl_DcmControlDtcSettingEnableStatus(Dcm_DspCDTCStatus_b);
   }
}

static Std_ReturnType Dcm_CdtcsProcessPermissionState (Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType permissionResult = E_NOT_OK;

   {
        if(Dcm_Cdtcs_SettingType_u8==DCM_CDTCS_OFF)
        {
            permissionResult=Dcm_CdtcsProcessDisablePermission(dataNegRespCode_u8);
        }

        else{
            Dcm_SrvOpstatus_u8= DCM_PROCESSSERVICE;
            permissionResult = Dcm_CdtcsPerformService(dataNegRespCode_u8);
        }
   }

    return permissionResult;
}

static Std_ReturnType Dcm_CdtcsProcessDisablePermission (Dcm_NegativeResponseCodeType* dataNegRespCode_u8)
{
    Std_ReturnType permissionResult = E_NOT_OK;

    Dcm_Cdtcs_IsDisableInProgress_b=TRUE;

   if(Dcm_Cdtcs_SettingType_u8==DCM_CDTCS_OFF)
   {
        DcmAppl_DisableDTCSetting(dataNegRespCode_u8);
        if(*dataNegRespCode_u8==Dcm_CdtcsNoNrc_u8)
        {
            Dcm_Cdtcs_IsPermisionPending_b=FALSE;
            Dcm_SrvOpstatus_u8= DCM_PROCESSSERVICE;

            permissionResult=Dcm_CdtcsPerformService(dataNegRespCode_u8);

        }
        else if(*dataNegRespCode_u8==DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING)
        {
            Dcm_Cdtcs_IsPermisionPending_b=TRUE;
            Dcm_SrvOpstatus_u8= DCM_CHECKDATA;
            permissionResult = DCM_E_PENDING;
        }
        else{

        }
   }
   else{
        Dcm_Cdtcs_IsDisableInProgress_b=FALSE;
        *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
   }

    return permissionResult;
}

static boolean Dcm_CdtcsProceedRequest(const Dcm_MsgContextType* pMsgContext)
{
   boolean proceedRequest = FALSE;
   uint8 RequestSettingType_u8= *(pMsgContext->reqData);

   if(RequestSettingType_u8==DCM_CDTCS_OFF)
   {
        Dcm_ControlDtcSettingExit();
        (void) Dcm_CdtcsIsModeStatusCheckPassed();

        if(Dcm_Cdtcs_SettingType_u8==DCM_CDTCS_OFF)
        {
            proceedRequest=TRUE;
        }
   }
   else{
        proceedRequest=TRUE;
   }

    return proceedRequest;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
