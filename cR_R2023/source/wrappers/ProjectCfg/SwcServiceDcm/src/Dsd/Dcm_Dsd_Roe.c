

#include "DcmCore_DslDsd_Inf.h"

#define DEFAULT_VALUE                   0x00u
#define DEFAULT_MASKVALUE               0x00000001uL

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

P2CONST(Dcm_ProtocolExtendedInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoe_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
VAR(StatusType,DCM_VAR) Dcm_CounterValueTimerStatus_uchr;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
VAR(StatusType,DCM_VAR) Dcm_RoeType2TimerStatus_uchr;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
static VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) s_dataNrc_u8;
#endif
VAR (uint8, DCM_VAR) DcmRoeQueueIndex_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_DsdStatesType_ten,DCM_VAR) Dcm_DsdRoe2State_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_MsgContextType,DCM_VAR) Dcm_Roe2MesContext_st;
VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Roe2ResponseType_en;
VAR(PduInfoType,DCM_VAR) Dcm_DsldRoe2PduInfo_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,DCM_VAR) Dcm_DsldSrvIndex_u8;
VAR(Std_ReturnType,DCM_VAR) Dcm_Roe2TxResult_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
P2CONST(Dcm_ProtocolExtendedInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoe2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

static FUNC(Dcm_StatusType,DCM_CODE) Dcm_UpdateROEQueue( uint8 RoeEventId, PduIdType RxPdu)
{
    VAR(uint8,AUTOMATIC) index_u8;
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;
    dataReturnValue_u8=DCM_E_ROE_NOT_ACCEPTED;
    for(index_u8=0;index_u8<DCM_MAX_SETUPROEEVENTS;index_u8++)
    {
        if(Dcm_DcmDspEventQueue[index_u8].EventId_u8 == RoeEventId)
        {
            Dcm_DcmDspEventQueue[index_u8].Is_Queued = TRUE;
            Dcm_DcmDspEventQueue[index_u8].RxPduId_u8 = RxPdu;
            dataReturnValue_u8 = DCM_E_OK;
            break;
        }
    }
    return dataReturnValue_u8;
}

void Dcm_Lok_ROEResetOnConfirmation(void)
{
    Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed = FALSE;

    Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
    Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdVerifyROESubFncID(
        P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) Msgcontext_s,
        uint8* idxSubservice_u8,
        const Dcm_Dsld_ServiceType* service_pcs,
        Dcm_NegativeResponseCodeType* ErrorCode)
{
    const Dcm_Dsld_SubServiceType* adrSubservice_pcst;
    Std_ReturnType VerificationResult_u8 = E_NOT_OK;

    uint8 dataSubfunction_u8 = Msgcontext_s->reqData[0];
    *idxSubservice_u8 = 0u;
    *ErrorCode = DEFAULT_VALUE;

    if (Msgcontext_s->reqDataLen > DEFAULT_VALUE)
    {

        adrSubservice_pcst = service_pcs->ptr_subservice_table_pcs;
        if(Dcm_DsldGlobal_st.dataSid_u8 ==0x86)
        {
            dataSubfunction_u8 =  (dataSubfunction_u8 & ((uint8)(~(0x40u))));
        }

        while(*idxSubservice_u8 < service_pcs->num_sf_u8)
        {
            if (dataSubfunction_u8 == adrSubservice_pcst[*idxSubservice_u8].subservice_id_u8)
            {
                break;
            }
            (*idxSubservice_u8)++;
        }

        if (*idxSubservice_u8 < service_pcs->num_sf_u8)
        {
            VerificationResult_u8 = E_OK;
        }

        else
        {
            *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
    else
    {

        if (service_pcs->servicelocator_b == FALSE)
        {

            DcmAppl_DcmGetNRCForMinLengthCheck(
                    Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8, service_pcs->sid_u8,
                    ErrorCode);
        }
        if (*ErrorCode == DEFAULT_VALUE)
        {

            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }
    return VerificationResult_u8;
}

LOCAL_INLINE Std_ReturnType Dcm_CheckRoeSubFunction(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) Msgcontext_s,
        P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) service_pcs,
        P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) ErrorCode_u8 )
{

    uint8 idxSubservice_u8;
    uint32 dataActiveMask_u32;
    Std_ReturnType VerificationResult_u8 = Dcm_Lok_DsdVerifyROESubFncID(Msgcontext_s,&idxSubservice_u8,service_pcs,ErrorCode_u8);

    const Dcm_Dsld_SubServiceType* adrSubservice_pcst =service_pcs->ptr_subservice_table_pcs;
    *ErrorCode_u8 = 0u;

    if(VerificationResult_u8 == E_OK)
    {
        VerificationResult_u8 = E_NOT_OK;

        dataActiveMask_u32 = (uint32) (DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSession_u8);

        if ((adrSubservice_pcst[idxSubservice_u8].allowed_session_b32 & dataActiveMask_u32) == (dataActiveMask_u32))
        {

            dataActiveMask_u32 = (uint32) (DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSecurity_u8);

            if ((adrSubservice_pcst[idxSubservice_u8].allowed_security_b32 & dataActiveMask_u32)
                    == (dataActiveMask_u32))
            {

                VerificationResult_u8 = (*adrSubservice_pcst[idxSubservice_u8].adrUserSubServiceModeRule_pfct)(ErrorCode_u8,
                            Dcm_DsldGlobal_st.dataSid_u8, adrSubservice_pcst[idxSubservice_u8].subservice_id_u8);

                *ErrorCode_u8=((VerificationResult_u8 != E_OK) && (*ErrorCode_u8 == 0x00))?DCM_E_CONDITIONSNOTCORRECT:*ErrorCode_u8;
#if(DCM_CFG_DSD_MODERULESUBFNC_ENABLED != DCM_CFG_OFF)

                if((adrSubservice_pcst[idxSubservice_u8].moderule_fp != NULL_PTR) && (VerificationResult_u8==E_OK))
                {

                    VerificationResult_u8 = ((*adrSubservice_pcst[idxSubservice_u8].moderule_fp)(ErrorCode_u8) == TRUE)?E_OK:E_NOT_OK;
                }
#endif
            }

            else
            {
                *ErrorCode_u8 = DCM_E_SECURITYACCESSDENIED;
            }
        }

        else
        {
            *ErrorCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
        }
    }
    return VerificationResult_u8;
}

static FUNC(Dcm_StatusType,DCM_CODE) Dcm_GetRoeProtValidity(VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) idxProtocol_u8)
{
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;

    *idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    dataReturnValue_u8 = (Dcm_DsldProtocol_pcst[*idxProtocol_u8].roe_info_pcs != NULL_PTR) ? E_OK : DCM_E_ROE_NOT_ACCEPTED;

    return dataReturnValue_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

static FUNC(void,DCM_CODE) Dcm_DsldRoeInitiateResponseTransmission(VAR(Std_ReturnType,AUTOMATIC) retVal_u8)
{
    if(retVal_u8 == E_OK)
    {

        Dcm_ProcessingDone ( & Dcm_Roe2MesContext_st);
    }
    else if (retVal_u8 == DCM_E_PENDING)
    {

    }
    else if (retVal_u8 == DCM_E_FORCE_RCRRP)
    {
        (void)Dcm_ForceRespPend();
    }
    else
    {

        if(s_dataNrc_u8 ==0x00)
        {
            s_dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }

        Dcm_SetNegResponse( & Dcm_Roe2MesContext_st ,s_dataNrc_u8);
        Dcm_ProcessingDone ( & Dcm_Roe2MesContext_st);
    }
}

FUNC(boolean,DCM_CODE) Dcm_ChkIfDidServiceIsActive(VAR(uint8, AUTOMATIC) TesterReqSid_u8,
        VAR(uint8, AUTOMATIC) RoeType2Sid_u8)
{
    VAR(boolean,AUTOMATIC) retval_b;
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSrvTable_pcst;
    adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;

    retval_b = TRUE;

    if((Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b)&&
            (adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].servicelocator_b))
    {

        if(TesterReqSid_u8 == RoeType2Sid_u8)
        {

            retval_b = FALSE;
        }

        else if(
                ((TesterReqSid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER) ||
                        (TesterReqSid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER)||
                        (TesterReqSid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER)||
                        (TesterReqSid_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER))
                &&
                ((RoeType2Sid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER) ||
                        (RoeType2Sid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER)||
                        (RoeType2Sid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER)||
                        (RoeType2Sid_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER))
        )
        {

            retval_b = FALSE;
        }
        else
        {

        }
    }
    return(retval_b);
}

static FUNC(void,DCM_CODE) Dcm_Lok_DsldRoe2StateMachine_DSD_VERIFY_DIAGNOSTIC_DATA(
        P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST)  adrSrvTable_pcst)
{
    VAR(uint8,AUTOMATIC) dataNrc_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    dataNrc_u8=0x00;

    if(Dcm_Roe2MesContext_st.dcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID)
    {
        Dcm_Roe2MesContext_st.msgAddInfo.reqType = DCM_PRV_FUNCTIONAL_REQUEST;
    }
    else
    {
        Dcm_Roe2MesContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
    }

    Dcm_Roe2MesContext_st.reqData = &(Dcm_DsldRoe2_pcst->txbuffer_ptr[1]);

    Dcm_Roe2MesContext_st.resData = &(Dcm_DsldRoe2_pcst->txbuffer_ptr[3]);

    Dcm_Roe2MesContext_st.resMaxDataLen = Dcm_DsldRoe2_pcst->txbuffer_length_u32 - 1u;

    if((adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].subfunction_exist_b != FALSE)&&
            ((Dcm_DsldRoe2_pcst->txbuffer_ptr[1]&0x80u) == 0x80u))
    {

        Dcm_Roe2MesContext_st.msgAddInfo.suppressPosResponse = TRUE;

        (*Dcm_Roe2MesContext_st.reqData) = ((*Dcm_Roe2MesContext_st.reqData) & 0x7Fu);
    }

    if((adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].subfunction_exist_b!= FALSE) &&
            (adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].num_sf_u8!=0))
    {

        dataRetVal_u8 = Dcm_CheckRoeSubFunction(&Dcm_Roe2MesContext_st,&adrSrvTable_pcst[Dcm_DsldSrvIndex_u8],&dataNrc_u8);
        if(dataRetVal_u8 != E_OK)
        {
            dataNrc_u8 = (dataNrc_u8==0u)?DCM_E_CONDITIONSNOTCORRECT:dataNrc_u8;
        }
        else
        {
            dataNrc_u8 = 0u;
        }
    }
    if(dataNrc_u8 == 0x00)
    {

        Dcm_DsdRoe2State_en = DSD_CALL_SERVICE;

        DCM_TimerStart(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,DCM_CFG_GET_TIMEOUT,
                Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr);

        dataRetVal_u8=(*adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].service_handler_fp)
        (DCM_INITIAL,&Dcm_Roe2MesContext_st,&dataNrc_u8);

        Dcm_DsldRoeInitiateResponseTransmission(dataRetVal_u8);
    }
    else
    {
        Dcm_SetNegResponse(&Dcm_Roe2MesContext_st,dataNrc_u8);
        Dcm_ProcessingDone(&Dcm_Roe2MesContext_st );
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_DsldRoe2StateMachine_DSD_CALL_SERVICE(
        P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST)  adrSrvTable_pcst)
{
    VAR(uint8,AUTOMATIC) dataNrc_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    if(DCM_TimerElapsed(Dcm_DsldGlobal_st.datRoeType2Timeout_u32)== FALSE)
    {

        DCM_TimerProcess(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,Dcm_Roe2StartTick_u32,
                Dcm_RoeType2TimerStatus_uchr);

        if(adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].servicelocator_b != FALSE)
        {
            dataRetVal_u8=(*adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].service_handler_fp)
            (DCM_INITIAL,&Dcm_Roe2MesContext_st,&dataNrc_u8);

            Dcm_DsldRoeInitiateResponseTransmission(dataRetVal_u8);
        }
    }
    else
    {

        DcmAppl_DcmConfirmation(Dcm_Roe2MesContext_st.idContext,
                Dcm_Roe2MesContext_st.dcmRxPduId,
                Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_Roe2MesContext_st.dcmRxPduId].testsrcaddr_u16,
                DCM_RES_POS_NOT_OK);

        if(adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].Service_init_fp != NULL_PTR)
        {

            (*adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].Service_init_fp)();
        }

        Dcm_DsdRoe2State_en = DSD_IDLE;
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_DsldRoe2StateMachine_DSD_TX_CONFIRMATION(void)
{
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) stConfirm_u8;

    if(Dcm_Roe2TxResult_u8 == E_OK)
    {
        if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE)
        {

            stConfirm_u8 = DCM_RES_POS_OK;
        }
        else
        {

            stConfirm_u8 = DCM_RES_NEG_OK;
        }
    }
    else
    {
        if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE )
        {

            stConfirm_u8 = DCM_RES_POS_NOT_OK;
        }
        else
        {

            stConfirm_u8 = DCM_RES_NEG_NOT_OK;
        }
    }

    Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed = FALSE;

    DcmAppl_DcmConfirmation(Dcm_Roe2MesContext_st.idContext,
            Dcm_Roe2MesContext_st.dcmRxPduId,
            Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_Roe2MesContext_st.dcmRxPduId].testsrcaddr_u16,
            stConfirm_u8);

    Dcm_DsdRoe2State_en = DSD_IDLE;

    DCM_TimerStart(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,
            DCM_CFG_ROETYPE2_INTERMSGTIME,Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr);

}

FUNC(void,DCM_CODE) Dcm_DsldRoe2StateMachine(void)
{
    VAR(uint8,AUTOMATIC) nrService_u8;
    VAR(uint8,AUTOMATIC) idxIndex_u8;
    VAR(uint8,AUTOMATIC) dataNrc_u8;
    VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en;
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSrvTable_pcst;

    switch(Dcm_DsdRoe2State_en)
    {
        case DSD_IDLE:
        break;

        case DSD_VERIFY_DIAGNOSTIC_DATA:

        dataNrc_u8=0x00;

        Dcm_Roe2ResponseType_en = DCM_DSLD_POS_RESPONSE;

        Dcm_Roe2MesContext_st.resDataLen = 0x0u;

        nrService_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].num_services_u8;

        adrSrvTable_pcst =
        Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;

        Dcm_Roe2MesContext_st.idContext = Dcm_DsldRoe2_pcst->txbuffer_ptr[0];

        Dcm_Roe2MesContext_st.msgAddInfo.sourceofRequest = DCM_ROE_SOURCE;

        for(idxIndex_u8 = 0x00; idxIndex_u8 != nrService_u8; idxIndex_u8++)
        {
            if(Dcm_Roe2MesContext_st.idContext == adrSrvTable_pcst[idxIndex_u8].sid_u8)
            {

                break;
            }
        }

        if(idxIndex_u8 != nrService_u8)
        {
            DsdState_en = Dcm_Lok_GetDsdState();

            if(((Dcm_Lok_GetDslState() == DSL_STATE_IDLE)&&
                            (DsdState_en == DSD_IDLE)) ||
                    (Dcm_ChkIfDidServiceIsActive(Dcm_DsldGlobal_st.dataSid_u8,Dcm_Roe2MesContext_st.idContext)!=FALSE))
            {
                Dcm_Lok_DsldRoe2StateMachine_DSD_VERIFY_DIAGNOSTIC_DATA(adrSrvTable_pcst);
            }
            else
            {

                Dcm_SetNegResponse(&Dcm_Roe2MesContext_st,DCM_E_SERVICENOTSUPPORTED);
                Dcm_ProcessingDone(&Dcm_Roe2MesContext_st );
            }
        }
        break;

        case DSD_CALL_SERVICE:

        adrSrvTable_pcst =
        Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;
        Dcm_Lok_DsldRoe2StateMachine_DSD_CALL_SERVICE(adrSrvTable_pcst);
        break;

        case DSD_WAITFORTXCONF:

        break;

        case DSD_SENDTXCONF_APPL:

        Dcm_Lok_DsldRoe2StateMachine_DSD_TX_CONFIRMATION();
        break;

        default:

        break;
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

static FUNC(Dcm_StatusType,DCM_CODE) Dcm_Lok_ROE_StartProtocol(void)
{
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;
    idxProtocol_u8 = 0x0;

    dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;

    if (Dcm_StartProtocol(Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8) == E_OK)
    {

        Dcm_Dsd_ServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);

        Dcm_DsldSrvTable_pcst =
                Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
    }
    else
    {

        DCM_DET_ERROR(DCM_ROE_ID, DCM_E_PROTOCOL_NOT_STARTED)

        Dcm_DsldGlobal_st.flgCommActive_b = FALSE;
        dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;
    }
    return (dataReturnValue_u8);
}

static FUNC(Dcm_StatusType,DCM_CODE) Dcm_Lok_ROE_TYPE1( VAR(Dcm_MsgType,AUTOMATIC) adrSrc_pu8,
        CONST(Dcm_MsgType,AUTOMATIC) MsgPtr,
        VAR(Dcm_MsgLenType, AUTOMATIC) MsgLen,
        VAR(PduIdType,AUTOMATIC) dcmRxPduId_u8)
{
    VAR(Dcm_MsgType,AUTOMATIC) adrDest_pu8;
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;
    VAR(uint16_least,AUTOMATIC) idxIndex_qu16;
    VAR(boolean,AUTOMATIC) roeReqAccepted_b;
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en = Dcm_Lok_GetDsdState();
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(uint8, AUTOMATIC) DslPreemptionStateTemp_u8;
#endif
    adrDest_pu8 = MsgPtr;
    idxProtocol_u8 = 0x0;

    roeReqAccepted_b = FALSE;

    dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;

    SchM_Enter_Dcm_Global_NoNest();

    if ((Dcm_Lok_GetDslState() == DSL_STATE_IDLE) && (DsdState_en== DSD_IDLE)
            && (adrDest_pu8 != NULL_PTR) && (adrSrc_pu8 != NULL_PTR))
    {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        DslPreemptionStateTemp_u8 = Dcm_Lok_GetDslPreemptionState();
        if((DslPreemptionStateTemp_u8 != DSL_SUBSTATE_STOP_PROTOCOL)&& (DslPreemptionStateTemp_u8 != DSL_SUBSTATE_STOP_PROTOCOL))
#endif
        {

            Dcm_Lok_SetDslState(DSL_STATE_ROETYPE1_RECEIVED);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            Dcm_Lok_SetDsdState(DSD_VERIFY_DIAGNOSTIC_DATA);
            Dcm_Lok_SetDslNextState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);

            roeReqAccepted_b = TRUE;
        }
    }

    SchM_Exit_Dcm_Global_NoNest();
    if (roeReqAccepted_b)
    {

        Dcm_DsldGlobal_st.dataActiveRxPduId_u8 = dcmRxPduId_u8;
        Dcm_DsldGlobal_st.dataRequestLength_u16 = (PduLengthType) MsgLen;
        Dcm_DsldRoe_pcst = Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs;

        Dcm_DsldGlobal_st.dataSid_u8 = adrDest_pu8[0];

        Dcm_DsldGlobal_st.dataOldSrvtable_u8 = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
        Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldRoe_pcst->servicetable_Id_u8;
        Dcm_DsldSrvTable_pcst =
                Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;

        Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

        Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_ROE_SOURCE;

        for (idxIndex_qu16 = (uint16) MsgLen; idxIndex_qu16 != 0x00u; idxIndex_qu16--)
        {

            *adrSrc_pu8 = *adrDest_pu8;

            adrSrc_pu8++;

            adrDest_pu8++;

        }
    }
    else
    {

        dataReturnValue_u8 = Dcm_UpdateROEQueue(*(MsgPtr + MsgLen), dcmRxPduId_u8);
    }

    return (dataReturnValue_u8);
}

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

static FUNC(Dcm_StatusType,DCM_CODE) Dcm_Lok_ROE_TYPE2(VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8,
                                                       VAR(Dcm_MsgType,AUTOMATIC) adrSrc_pu8,
                                                       CONST(Dcm_MsgType,AUTOMATIC) MsgPtr,
                                                       VAR(Dcm_MsgLenType, AUTOMATIC) MsgLen,
                                                       VAR(PduIdType,AUTOMATIC) dcmRxPduId_u8)
{
    VAR(Dcm_MsgType,AUTOMATIC) adrDest_pu8;
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(uint8,AUTOMATIC) idxIndex_u8;
    VAR(uint16_least,AUTOMATIC) idxIndex_qu16;

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) nrService_u8;
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSrvTable_pcst;
#endif

    adrDest_pu8 = MsgPtr;
    idxProtocol_u8 = 0x0;

    if((Dcm_DsdRoe2State_en == DSD_IDLE) &&
            (dataReturnValue_u8 == DCM_E_OK) &&
            (adrDest_pu8 != NULL_PTR) && (adrSrc_pu8 != NULL_PTR))
    {

        for(idxIndex_qu16 = (uint16)MsgLen; idxIndex_qu16 != 0x00u; idxIndex_qu16--)
        {
            *adrSrc_pu8 = *adrDest_pu8;

            adrSrc_pu8++;

            adrDest_pu8++;
        }

        Dcm_DsldRoe2_pcst = Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs;

        Dcm_Roe2MesContext_st.reqDataLen = MsgLen - 1u;

        Dcm_Roe2MesContext_st.dcmRxPduId = dcmRxPduId_u8;

        nrService_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].num_services_u8;

        adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;

        Dcm_Roe2MesContext_st.idContext = Dcm_DsldRoe2_pcst->txbuffer_ptr[0];

        for(idxIndex_u8 = 0x00u; idxIndex_u8 != nrService_u8; idxIndex_u8++)
        {
            if(Dcm_Roe2MesContext_st.idContext == adrSrvTable_pcst[idxIndex_u8].sid_u8)
            {

                break;
            }
        }

        if(idxIndex_u8 != nrService_u8)
        {

            Dcm_DsldSrvIndex_u8 = idxIndex_u8;

            Dcm_DsdRoe2State_en = DSD_VERIFY_DIAGNOSTIC_DATA;
        }
        else
        {

            dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;
        }
    }
    else
    {

        dataReturnValue_u8= Dcm_UpdateROEQueue(*(adrDest_pu8+MsgLen+1) , dcmRxPduId_u8);
    }
    return(dataReturnValue_u8);
}
#endif

static FUNC(Dcm_StatusType,DCM_CODE) Dcm_Lok_ROE_CheckLength(CONST(Dcm_MsgType,AUTOMATIC) MsgPtr,
        VAR(Dcm_MsgLenType, AUTOMATIC) MsgLen,
        VAR(PduIdType,AUTOMATIC) dcmRxPduId_u8)
{
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;
    VAR(boolean,AUTOMATIC) dataStartProtocol_b;
    VAR(Dcm_MsgType,AUTOMATIC) adrSrc_pu8;
    VAR(uint8,AUTOMATIC) idxProtocol_u8;

    dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;

    dataStartProtocol_b = FALSE;
    idxProtocol_u8 = 0x0;
    adrSrc_pu8 = NULL_PTR;

    if (dcmRxPduId_u8 < DCM_CFG_NUM_RX_PDUID)
    {
        dataReturnValue_u8 = Dcm_GetRoeProtValidity(dcmRxPduId_u8, &idxProtocol_u8);
    }

    if ((dataReturnValue_u8 == DCM_E_OK)
            && (DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dcmRxPduId_u8]].channel_idx_u8))
            && (MsgLen <= Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs->txbuffer_length_u32)

            )
    {
        adrSrc_pu8 = Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs->txbuffer_ptr;

        SchM_Enter_Dcm_Global_NoNest();

        if ((Dcm_DsldGlobal_st.flgCommActive_b == FALSE) && (Dcm_Lok_GetDslState()  == DSL_STATE_IDLE)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                &&
                ((Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING) &&
                                (Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL))
#endif
                )
        {

            Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
            Dcm_DsldGlobal_st.nrActiveConn_u8 = Dcm_DsldRxTable_pcu8[dcmRxPduId_u8];
            Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldProtocol_pcst[idxProtocol_u8].sid_tableid_u8;

            Dcm_DsldGlobal_st.flgCommActive_b = TRUE;

            dataStartProtocol_b = TRUE;
        }

        SchM_Exit_Dcm_Global_NoNest();

        if (dataStartProtocol_b != FALSE)
        {
            dataReturnValue_u8 = Dcm_Lok_ROE_StartProtocol();
        }

        if ((DCM_PRV_DSLD_TYPE1 == (Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs)->protocolTransType_u8)
                && (dataReturnValue_u8 == DCM_E_OK))
        {
            dataReturnValue_u8 = Dcm_Lok_ROE_TYPE1(adrSrc_pu8, MsgPtr, MsgLen, dcmRxPduId_u8);
        }
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
        else if((dataReturnValue_u8 == DCM_E_OK) &&
                (DCM_PRV_DSLD_TYPE2 == (Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs)->protocolTransType_u8))
        {
            dataReturnValue_u8 = Dcm_Lok_ROE_TYPE2(dataReturnValue_u8, adrSrc_pu8, MsgPtr, MsgLen, dcmRxPduId_u8);
        }
#endif
        else
        {

            dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;
        }
    }
    else
    {

        dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;
    }
    return (dataReturnValue_u8);
}

FUNC(Dcm_StatusType,DCM_CODE) Dcm_Lok_ResponseOnOneEvent( CONST(Dcm_MsgType,AUTOMATIC) MsgPtr,
        VAR(Dcm_MsgLenType, AUTOMATIC) MsgLen,
        VAR(uint16,AUTOMATIC) TesterSrcAddr
)
{
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;

    VAR(uint8,AUTOMATIC) idxIndex_u8;

    VAR(PduIdType,AUTOMATIC) dcmRxPduId_u8;

    dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;

    for (idxIndex_u8 = 0; idxIndex_u8 < DCM_CFG_NUM_RX_PDUID; idxIndex_u8++)
    {
        if (Dcm_Dsld_RoeRxToTestSrcMappingTable[idxIndex_u8].testsrcaddr_u16 == TesterSrcAddr)
        {
            break;
        }

    }
    if (idxIndex_u8 < DCM_CFG_NUM_RX_PDUID)
    {

        dcmRxPduId_u8 = Dcm_Dsld_RoeRxToTestSrcMappingTable[idxIndex_u8].rxpduid_num_u8;

        if ((Dcm_isInitialised_b != FALSE) && (Dcm_acceptRequests_b != FALSE))
        {
            dataReturnValue_u8 = Dcm_Lok_ROE_CheckLength(MsgPtr, MsgLen, dcmRxPduId_u8);
        }

    }
    return (dataReturnValue_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_CODE) Dcm_DsldRoeTimeOut(void)
{

    if(Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)
    {

        if(DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimerTimeout_u32)== FALSE)
        {

            DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimerTimeout_u32,Dcm_TimerStartTick_u32,
                    Dcm_CounterValueTimerStatus_uchr);
        }
        else
        {

            DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
                    Dcm_DsldMsgContext_st.dcmRxPduId,
                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                    DCM_RES_POS_NOT_OK);

            Dcm_Lok_SetDsdState(DSD_IDLE);

            Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
            Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].
            ptr_service_table_pcs;

            Dcm_Lok_SetDslState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
        }
    }
}
#endif

FUNC(Std_ReturnType,DCM_CODE) Dcm_TriggerOnEvent( VAR(uint8,AUTOMATIC) RoeEventId)
{
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF) &&\
    (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
    VAR(uint16,AUTOMATIC) idxRoeDid_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataRetStartFunc_u8;
    VAR(Dcm_StatusType,AUTOMATIC) dataRoeStatus_u8;
    VAR(uint8,AUTOMATIC) dataSrc_u8[4];
    VAR(uint32,AUTOMATIC) datatMsgLen_u32;

    idxRoeDid_u8=0x0;
    dataRetStartFunc_u8=E_NOT_OK;
    datatMsgLen_u32=0;

    for(idxRoeDid_u8=0;idxRoeDid_u8<DCM_MAX_DIDROEEVENTS;idxRoeDid_u8++)
    {
        if(RoeEventId==DcmDspRoeDidEvents[idxRoeDid_u8].RoeEventId_u8)
        {

            break;
        }
    }

    if(idxRoeDid_u8<DCM_MAX_DIDROEEVENTS)
    {

        if(DCM_ROE_STARTED==DcmDspRoeDidStateVariables[idxRoeDid_u8].RoeEventStatus)
        {

            dataRetStartFunc_u8=E_OK;
        }
    }

    if(E_OK==dataRetStartFunc_u8)
    {

        dataSrc_u8[0]=0x22u;
        dataSrc_u8[1]=(uint8)((DcmDspRoeDidStateVariables[idxRoeDid_u8].stSrvToRespDid_u16)>>8u);
        dataSrc_u8[2]=(uint8)(DcmDspRoeDidStateVariables[idxRoeDid_u8].stSrvToRespDid_u16);
        dataSrc_u8[3]= RoeEventId;
        datatMsgLen_u32=3;
        dataRoeStatus_u8=Dcm_Lok_ResponseOnOneEvent(dataSrc_u8,datatMsgLen_u32,
                DcmDspRoeDidStateVariables[idxRoeDid_u8].SourceAddress_u16);

        if(dataRoeStatus_u8!=DCM_E_OK)
        {
            dataRetStartFunc_u8=E_NOT_OK;
        }
    }
    return dataRetStartFunc_u8;
#else
    (void) RoeEventId;
    return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_DemTriggerOnDTCStatus( VAR(uint32, AUTOMATIC) Dtc,
                                                         VAR(uint8, AUTOMATIC) DTCStatusOld,
                                                         VAR(uint8, AUTOMATIC) DTCStatusNew )
{
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&&\
    (DCM_ROE_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
    VAR(uint8,AUTOMATIC) dataSid_u8;
    VAR(uint8,AUTOMATIC) dataSrc_u8[3];
    VAR(uint32,AUTOMATIC) datatMsgLen_u32;

    SchM_Enter_Dcm_Global_NoNest();
    dataSid_u8=Dcm_DsldGlobal_st.dataSid_u8;
    SchM_Exit_Dcm_Global_NoNest();

    if((dataSid_u8 != 0x14) && (dataSid_u8 != 0x0))
    {

        if(DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus)
        {

            if(((DTCStatusOld & DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8) ^\
 (DTCStatusNew & DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8)) != 0x0)
            {

                dataSrc_u8[0]=0x19u;
                dataSrc_u8[1]=0x0Eu;
                dataSrc_u8[2]= DcmDspRoeDtcEvent.RoeEventId_u8;
                datatMsgLen_u32=0x02u;
                (void)Dcm_Lok_ResponseOnOneEvent(dataSrc_u8,datatMsgLen_u32,
                        DcmDspRoeDtcStateVariable.SourceAddress_u16);
            }
        }
    }
#else

    (void)(DTCStatusOld);
    (void)(DTCStatusNew);
#endif

    (void)(Dtc);
    return E_OK;
}

#if(DCM_ROE_ENABLED != DCM_CFG_OFF && DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDTCEventWindowTimeROE_STARTED(VAR(uint8, AUTOMATIC) roeEventWindowTime_u8)
{
    if((roeEventWindowTime_u8 == 0x02u) || (roeEventWindowTime_u8 == 0x04u))
    {

        if((TRUE == DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b )&&
                (TRUE == DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b)&&
                (TRUE == DcmDspRoeDtcStateVariable.stDspRoeStorageState_b))
        {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STARTED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STARTED);

        }
        else
        {

            DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
        }
    }

    else if(roeEventWindowTime_u8 == 0x03u)
    {

        if(FALSE != DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
        {
            DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_STOPPED;
        }
        else
        {

            if(FALSE == DcmDspRoeDtcStateVariable.stDspRoeStorageState_b)
            {
                DcmDspRoeDtcStateVariable.RoeEventStatus = DCM_ROE_CLEARED;
            }
            else
            {
                DcmDspRoeDtcStateVariable.RoeEventStatus = DCM_ROE_STOPPED;
            }
        }
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,
                DcmDspRoeDtcStateVariable.RoeEventStatus);
    }
    else
    {

    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDTCEventWindowTimeROE_STOPPED(VAR(uint8, AUTOMATIC) roeEventWindowTime_u8)
{

    if(((roeEventWindowTime_u8 == 0x02u) ||(roeEventWindowTime_u8 == 0x04u)) &&
            (TRUE == DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b) &&
            (TRUE == DcmDspRoeDtcStateVariable.stDspRoeStorageState_b) )
    {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
    }
    else
    {

        if(FALSE == DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
        {
            DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,
                    DcmDspRoeDtcStateVariable.RoeEventStatus);
        }
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDTCEventWindowTime(VAR(uint8, AUTOMATIC) roeEventWindowTime_u8)
{

    if((DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus))
    {
        Dcm_Lok_CheckDTCEventWindowTimeROE_STARTED(roeEventWindowTime_u8);
    }
    else if(DCM_ROE_STOPPED == DcmDspRoeDtcStateVariable.RoeEventStatus)
    {
        Dcm_Lok_CheckDTCEventWindowTimeROE_STOPPED(roeEventWindowTime_u8);
    }
    else
    {

        if(FALSE==DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
        {

            DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_CLEARED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_CLEARED);
        }
    }
    if(roeEventWindowTime_u8 == 0x04u)
    {

        DcmAppl_DcmStoreROEcycleCounter(DcmDspRoeDtcEvent.RoeEventId_u8,0x03u);
    }
}

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDIDEventWindowTimeROE_STARTED(VAR(uint8, AUTOMATIC) roeEventWindowTime_u8,
                                                                      VAR(uint8,DCM_VAR) dataidxLoop_u8)
{
    if((roeEventWindowTime_u8 == 0x02u) || (roeEventWindowTime_u8 == 0x04u))
    {

        if((TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b )&&
                (TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b)&&
                (TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b) )
        {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STARTED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STARTED);

        }
        else
        {

            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);
        }
    }

    else
    {
        if(roeEventWindowTime_u8 == 0x03u)
        {
            if(FALSE != DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
            {
                DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_STOPPED;
            }
            else
            {

                if(FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b)
                {
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus = DCM_ROE_CLEARED;
                }
                else
                {
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus = DCM_ROE_STOPPED;
                }
            }
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
        }
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDIDEventWindowTimeROE_STOPPED(VAR(uint8, AUTOMATIC) roeEventWindowTime_u8,
                                                                      VAR(uint8,DCM_VAR) dataidxLoop_u8)
{

    if(((roeEventWindowTime_u8 == 0x02u) ||(roeEventWindowTime_u8 == 0x04u)) &&
            (TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b) &&
            (TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b))
    {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);

    }
    else
    {

        if(FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
        {
            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_CLEARED;

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
        }
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDIDEventWindowTime(VAR(uint8, AUTOMATIC) roeEventWindowTime_u8,
                                                           VAR(uint8,DCM_VAR) dataidxLoop_u8)
{

    if ((DCM_ROE_STARTED == DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus))
    {
        Dcm_Lok_CheckDIDEventWindowTimeROE_STARTED(roeEventWindowTime_u8, dataidxLoop_u8);
    }
    else if (DCM_ROE_STOPPED == DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus)
    {
        Dcm_Lok_CheckDIDEventWindowTimeROE_STOPPED(roeEventWindowTime_u8, dataidxLoop_u8);
    }
    else
    {
        if (FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
        {

            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus = DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_CLEARED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8, DCM_ROE_CLEARED);
        }
    }

    if (roeEventWindowTime_u8 == 0x04u)
    {

        DcmAppl_DcmStoreROEcycleCounter(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8, 0x03u);
    }
}
#endif

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_CODE) Dcm_RestoreROEDtcEvents(void)
{
    VAR(uint8, AUTOMATIC) roeEventWindowTime_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataResult_u8;
    roeEventWindowTime_u8 =0x0u;

    if(TRUE==DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
    {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
    }
    if((TRUE == DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b )&&
            (FALSE == DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b))
    {

        dataResult_u8 = E_NOT_OK;
    }
    else
    {

        dataResult_u8 = DcmAppl_DcmGetRoeDTCInfo(DcmDspRoeDtcEvent.RoeEventId_u8,
                   &DcmDspRoeDtcStateVariable.RoeEventStatus,
                   &roeEventWindowTime_u8,
                   &DcmDspRoeDtcStateVariable.SourceAddress_u16,
                   &DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8,
                   &DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b,
                   &DcmDspRoeDtcStateVariable.stDspRoeStorageState_b,
                   &DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b);
    }
    if(E_OK == dataResult_u8)
    {
        Dcm_Lok_CheckDTCEventWindowTime(roeEventWindowTime_u8);
    }
    else
    {
        if(FALSE==DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
        {

            DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_CLEARED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_CLEARED);
        }
    }
}
#endif

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
FUNC(void,DCM_CODE) Dcm_RestoreROEDidEvents(void)
{

    VAR(Std_ReturnType,AUTOMATIC) dataResult_u8;
    VAR(uint8,DCM_VAR) dataidxLoop_u8;
    VAR(uint8, AUTOMATIC) roeEventWindowTime_u8;

    for(dataidxLoop_u8 =0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
    {
        roeEventWindowTime_u8 =0x0u;

        if(TRUE==DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
        {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);
        }
        if((TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b )&&
                (FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b))
        {

            dataResult_u8 = E_NOT_OK;
        }
        else
        {

        dataResult_u8 = DcmAppl_DcmGetROEDidInfo(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16,
                DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus,
                &roeEventWindowTime_u8,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].SourceAddress_u16,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b);
        }

        if(E_OK == dataResult_u8)
        {
            Dcm_Lok_CheckDIDEventWindowTime(roeEventWindowTime_u8, dataidxLoop_u8);
        }
        else
        {
            if(FALSE==DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
            {

                DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_CLEARED);
#endif
                DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_CLEARED);
            }
        }
    }

}
#endif

FUNC(void,DCM_CODE) Dcm_ResetROEEvents(void)
{
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) dataidxLoop_u8;
#endif

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

    if((DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus) &&
            (DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b == FALSE))
    {
        DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DcmDspRoeDtcStateVariable.RoeEventStatus);
    }
#endif

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
    for(dataidxLoop_u8 =0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
    {
        if((DCM_ROE_STARTED==DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus) &&
                (FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b ))
        {
            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_STOPPED;

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
        }
    }
#endif
}

#if(DCM_CFG_ROETYPE2_ENABLED == DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_CheckRoeType1StartProtocol(void)
{

    if(Dcm_StartProtocol(Dcm_DsldProtocol_pcst[ Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8)== E_OK )
    {

        Dcm_Dsd_ServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);

        Dcm_DsldSrvTable_pcst =
        Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
    }
    else
    {

        Dcm_DsldGlobal_st.flgCommActive_b = FALSE;
    }
}

static FUNC(void,DCM_CODE) Dcm_DsldProcessRoeType1(void)
{
    VAR(Dcm_MsgType,AUTOMATIC) adrSrc_pu8;
    VAR(uint8,AUTOMATIC) RxPduId_u8;
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
	VAR(uint8,AUTOMATIC) dataidxLoop_u8;
#endif
    VAR(boolean,AUTOMATIC) dataStartProtocol_b = FALSE;
    VAR(uint8, AUTOMATIC) DslPreemptionStateTemp_u8;
    VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en ;

    RxPduId_u8 = (uint8)Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].RxPduId_u8;

    if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].channel_idx_u8))
    {
        adrSrc_pu8 =
        Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].protocol_num_u8].roe_info_pcs->txbuffer_ptr;

        SchM_Enter_Dcm_Global_NoNest();

        if((Dcm_DsldGlobal_st.flgCommActive_b == FALSE) && ( Dcm_Lok_GetDslState() == DSL_STATE_IDLE)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                &&
                ((Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING) &&
                        (Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL))
#endif
        )
        {

            Dcm_DsldGlobal_st.idxCurrentProtocol_u8 =
            Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].protocol_num_u8;
            Dcm_DsldGlobal_st.nrActiveConn_u8 = Dcm_DsldRxTable_pcu8[RxPduId_u8];
            Dcm_DsldGlobal_st.datActiveSrvtable_u8 =
            Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].protocol_num_u8].sid_tableid_u8;

            Dcm_DsldGlobal_st.flgCommActive_b = TRUE;

            dataStartProtocol_b = TRUE;
        }

        SchM_Exit_Dcm_Global_NoNest();

        if(dataStartProtocol_b != FALSE)
        {
            Dcm_Lok_CheckRoeType1StartProtocol();
        }

        SchM_Enter_Dcm_Global_NoNest();

		DsdState_en = Dcm_Lok_GetDsdState();
        if((Dcm_Lok_GetDslState()   == DSL_STATE_IDLE)&&
                (DsdState_en == DSD_IDLE) &&
                (adrSrc_pu8 != NULL_PTR))
        {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            DslPreemptionStateTemp_u8 = Dcm_Lok_GetDslPreemptionState();
            if((DslPreemptionStateTemp_u8 != DSL_SUBSTATE_STOP_PROTOCOL)&& (DslPreemptionStateTemp_u8 != DSL_SUBSTATE_STOP_ROE))
#endif
            {

                Dcm_Lok_SetDslState(DSL_STATE_ROETYPE1_RECEIVED);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
                Dcm_Lok_SetDsdState(DSD_VERIFY_DIAGNOSTIC_DATA);
                Dcm_Lok_SetDslNextState(DSL_STATE_IDLE);
                Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            }
        }
        SchM_Exit_Dcm_Global_NoNest();

        Dcm_DsldGlobal_st.dataActiveRxPduId_u8 =RxPduId_u8;

        Dcm_DsldRoe_pcst = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].roe_info_pcs;

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if( Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].EventId_u8 == DCM_ROE_DTCEVENTID)
        {
            Dcm_DsldGlobal_st.dataSid_u8=0x19u;
            (*adrSrc_pu8)= 0x19;
            adrSrc_pu8++;
            *adrSrc_pu8 = 0x0Eu;

            Dcm_DsldGlobal_st.dataRequestLength_u16 =(PduLengthType)2u;
        }
        else
#endif
        {
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)

            for(dataidxLoop_u8 =0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
            {
                if(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8 == Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].EventId_u8)
                {
                    break;
                }
            }
            Dcm_DsldGlobal_st.dataSid_u8=0x22u;
            (*adrSrc_pu8)= 0x22;
            adrSrc_pu8++;
            *(adrSrc_pu8) = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16>>8u);
            adrSrc_pu8++;
            *(adrSrc_pu8) = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16);
            Dcm_DsldGlobal_st.dataRequestLength_u16 =(PduLengthType)3u;
#endif
        }
        Dcm_DsldGlobal_st.dataOldSrvtable_u8 = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
        Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldRoe_pcst->servicetable_Id_u8;
        Dcm_DsldSrvTable_pcst =
        Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;

        Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

        Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_ROE_SOURCE;
    }
}

#endif

FUNC(void,DCM_CODE) Dcm_DsldProcessRoeQueue(void)
{
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

    if(DCM_TimerElapsed(Dcm_DsldGlobal_st.datRoeType2Timeout_u32)== FALSE)
    {

        DCM_TimerProcess(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr)
    }
    else
#endif
    {
        if(DcmRoeQueueIndex_u8 == DCM_MAX_SETUPROEEVENTS)
        {
            DcmRoeQueueIndex_u8 = 0x00u;
        }
        while(DcmRoeQueueIndex_u8<DCM_MAX_SETUPROEEVENTS)
        {
            if(Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Queued == TRUE)
            {
                Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Queued = FALSE;
                Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed = TRUE;
                break;
            }
            DcmRoeQueueIndex_u8++;
        }
        if(DcmRoeQueueIndex_u8!=DCM_MAX_SETUPROEEVENTS)
        {

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
            if(Dcm_DsdRoe2State_en == DSD_IDLE)
            {
                Dcm_DsdRoe2State_en = DSD_VERIFY_DIAGNOSTIC_DATA;

                Dcm_DsldRoe2StateMachine();
            }
#else
            Dcm_DsldProcessRoeType1();
#endif
        }
    }
}
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

FUNC(BufReq_ReturnType, DCM_CODE) Dcm_DsldPersistentRoeHandling_en(
                                         P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrArrivedProt_pcst,
                                         VAR(PduLengthType,AUTOMATIC) nrTpSduLength_u16,
                                         VAR(PduIdType,AUTOMATIC) dataRxpduId_u8
                                                     )

{

    VAR(BufReq_ReturnType,AUTOMATIC) dataReturnVal_en;

    VAR(uint8,AUTOMATIC) dataRoeConnId_u8;

    VAR(uint8,AUTOMATIC) idxRoeProt_u8;

    VAR(PduIdType,AUTOMATIC) dataRoeRxPduId_u8;

    P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrRoeProtTable_pcst;

    dataRoeRxPduId_u8 = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

    dataRoeConnId_u8 = Dcm_DsldRxTable_pcu8[dataRoeRxPduId_u8];

    idxRoeProt_u8 = Dcm_DsldConnTable_pcst[dataRoeConnId_u8].protocol_num_u8;

    adrRoeProtTable_pcst = &Dcm_DsldProtocol_pcst[idxRoeProt_u8];

    dataReturnVal_en = BUFREQ_E_NOT_OK;

    if(Dcm_DsldGlobal_st.dataPassRxPduId_u8 == 0xff)
    {

        if((uint32)nrTpSduLength_u16 <= adrArrivedProt_pcst->rx_buffer_size_u32)
        {

            if(adrRoeProtTable_pcst->premption_level_u8 > adrArrivedProt_pcst->premption_level_u8)
            {

                if(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8 ==
                 adrArrivedProt_pcst->protocolid_u8)
                {

                    Dcm_DsldGlobal_st.dataPassRxPduId_u8 = dataRxpduId_u8;
                    Dcm_DsldGlobal_st.dataPassdataRequestLength_u16  = nrTpSduLength_u16;

                    Dcm_DslRxPduArray_ast[dataRxpduId_u8].Dcm_DslCopyRxData_b = TRUE;
                    Dcm_Lok_ResetCopyRxDataStatus(dataRxpduId_u8);
                    dataReturnVal_en = BUFREQ_OK;

                    Dcm_Lok_SetDslNextState(DSL_STATE_WAITING_FOR_RXINDICATION);
                }
            }
            else
            {
                 if(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8 ==
                  adrArrivedProt_pcst->protocolid_u8)
                 {

                     Dcm_Lok_ReloadS3Timer();
                 }

             dataReturnVal_en = BUFREQ_E_NOT_OK;
            }

        }
        else
        {

            dataReturnVal_en = BUFREQ_E_OVFL;
        }
    }
    return dataReturnVal_en;
}
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
