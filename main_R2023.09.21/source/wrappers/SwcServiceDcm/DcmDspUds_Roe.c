#include "Std_Types.hpp"

#include "DcmDspUds_Roe_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Roe_Priv.hpp"

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

 VAR (uint8,DCM_VAR) Dcm_RoeDidIdx_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_DspRoeState_ten, DCM_VAR) Dcm_stDspRoeState_en;
static VAR(Dcm_DspRoeEventState_ten, DCM_VAR) s_DcmOldRoeDtcState;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint8,  DCM_VAR) Dcm_stRoeEventWindowTime_u8;
static VAR(uint8, DCM_VAR) Dcm_stEventType_u8;
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRoeOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean,     DCM_VAR) Dcm_stDspRoeStorageState_b;
static VAR(boolean,     DCM_VAR) Dcm_stDspRoeDidOpStatusIsPending_b;
static VAR(boolean,     DCM_VAR) Dcm_stDspRoeDtcOpStatusIsPending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)

static FUNC(Std_ReturnType,DCM_CODE) Dcm_StoreRoeDidEventInfo(VAR(Std_ReturnType, AUTOMATIC) dataDoeDidIdx_u8
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8;

   if(Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)
   {

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDidEvents[dataDoeDidIdx_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].RoeEventStatus);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataDoeDidIdx_u8].RoeEventId_u8
   ,     DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].RoeEventStatus);

        Dcm_stRoeOpstatus_u8=DCM_INITIAL;

   }

    dataRetValue_u8=DcmAppl_DcmStoreRoeDidInfo( DcmDspRoeDidEvents[dataDoeDidIdx_u8].RoeEventDid_u16
   ,     DcmDspRoeDidEvents[dataDoeDidIdx_u8].RoeEventId_u8
   ,     DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].RoeEventStatus
   ,     DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].SourceAddress_u16
   ,     DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].stDspRoeStorageState_b
   ,     Dcm_stRoeOpstatus_u8
   ,     DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].stDspRoeSessionIsDefault_b
   ,     dataNegRespCode_u8);

   if(dataRetValue_u8 == E_OK)
   {
        dataRetValue_u8 = E_OK;
        *dataNegRespCode_u8 = 0x0u;
        Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;

   }
   else if(dataRetValue_u8 == DCM_E_PENDING)
   {
        dataRetValue_u8 = DCM_E_PENDING;
        Dcm_stDspRoeDidOpStatusIsPending_b = TRUE;
        Dcm_stRoeOpstatus_u8=DCM_PENDING;
        *dataNegRespCode_u8 = 0x0u;

   }
   else{
        dataRetValue_u8 = E_NOT_OK;
        Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        if(*dataNegRespCode_u8 == 0)
        {

            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }

        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
   }
    return dataRetValue_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_ControlRoeDidEventType(
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(boolean, AUTOMATIC) dataStoreEventInfo_b;
   VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
   VAR(uint8, AUTOMATIC) dataidxLoop_u8;
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;

   VAR(Dcm_DspRoeEventState_ten, AUTOMATIC) dataRoeEvtStatus_u8 = DCM_ROE_CLEARED;
    dataReturnVal_u8=E_OK;
    dataStoreEventInfo_b=FALSE;
    *dataNegRespCode_u8 =0x0u;

    dataidxLoop_u8 = (Dcm_stDspRoeDidOpStatusIsPending_b == FALSE) ? 0x0u : Dcm_RoeDidIdx_u8;

    dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];
   for(;((dataidxLoop_u8<DCM_MAX_DIDROEEVENTS) && (*dataNegRespCode_u8 == 0x0u));dataidxLoop_u8++)
   {
        if(Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)
        {
            switch(Dcm_stEventType_u8)

            {
                case DCM_ROE_STOP:
                if(DCM_ROE_STARTED == DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus)
                {
                    dataRoeEvtStatus_u8=DCM_ROE_STOPPED;

                    dataStoreEventInfo_b=TRUE;
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b = FALSE;
                }
                break;
                case DCM_ROE_START:
                if(DCM_ROE_STOPPED == DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus)
                {
                    dataRoeEvtStatus_u8=DCM_ROE_STARTED;

                    dataStoreEventInfo_b=TRUE;

                    DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b =
                            (dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]) ? TRUE:FALSE;
                }
                break;
                case DCM_ROE_CLEAR:
                {
                    dataRoeEvtStatus_u8 = DCM_ROE_CLEARED;

                    dataStoreEventInfo_b=TRUE;
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b = FALSE;
                }
                break;
                default:
                {

                }
                break;
            }
        }

        if((dataStoreEventInfo_b != FALSE) ||(Dcm_stDspRoeDidOpStatusIsPending_b != FALSE))
        {
            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus=dataRoeEvtStatus_u8;
            DcmDspRoeDidStateVariables[dataidxLoop_u8].SourceAddress_u16=
                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;

            dataReturnVal_u8 = Dcm_StoreRoeDidEventInfo(dataidxLoop_u8,dataNegRespCode_u8);

            if(dataReturnVal_u8 != E_OK)
            {
                break;
            }
        }
   }
    Dcm_RoeDidIdx_u8 = (dataReturnVal_u8 == DCM_E_PENDING) ? dataidxLoop_u8 : Dcm_RoeDidIdx_u8;
    return (dataReturnVal_u8);
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_SetUpRoeDidEvent(
        P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;
   VAR(uint16, AUTOMATIC) dataRoeDid_u16;
   VAR(uint16, AUTOMATIC) StoreVar_u16;
   VAR(uint8, AUTOMATIC) dataidxLoop_u8;
    Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
    dataReturnVal_u8 = E_NOT_OK;

    StoreVar_u16=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD]);
    StoreVar_u16=StoreVar_u16<<8u;
    StoreVar_u16+=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+1u]);
    dataRoeDid_u16=StoreVar_u16;
   if(Dcm_stDspRoeDidOpStatusIsPending_b != TRUE)
   {

        for(dataidxLoop_u8=0;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
        {
            if(dataRoeDid_u16 == DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16)
            {
                break;
            }
        }

   }
   else{
        dataidxLoop_u8 = Dcm_RoeDidIdx_u8;
   }
   if(dataidxLoop_u8<DCM_MAX_DIDROEEVENTS)
   {

        dataReturnVal_u8 = DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8
   ,     Dcm_stEventType_u8
   ,     Dcm_stDspRoeStorageState_b
   ,     Dcm_stRoeEventWindowTime_u8
   ,     &pMsgContext->reqData[DCM_ROE_POSEVENTRECORD]
   ,     &pMsgContext->reqData[DCM_ROE_POSDIDSRVTORESPTORECORD]
   ,     Dcm_stRoeOpstatus_u8
   ,     dataNegRespCode_u8 );

        if(dataReturnVal_u8 == E_OK)
        {
            *dataNegRespCode_u8 = 0;
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
            Dcm_stRoeOpstatus_u8=DCM_INITIAL;

            DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventWindowTime_u8 = Dcm_stRoeEventWindowTime_u8;
            StoreVar_u16=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD]);
            StoreVar_u16=StoreVar_u16<<8u;
            StoreVar_u16+=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+1u]);
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventRecord_u16=StoreVar_u16;
            StoreVar_u16=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+3u]);
            StoreVar_u16=StoreVar_u16<<8u;
            StoreVar_u16+=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+4u]);
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stSrvToRespDid_u16=StoreVar_u16;

            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus=DCM_ROE_STOPPED;
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);

            for(dataidxLoop_u8=(uint8)(pMsgContext->reqDataLen-1u); dataidxLoop_u8 > 0u; dataidxLoop_u8--)
            {

                pMsgContext->resData[dataidxLoop_u8+0x1u] = pMsgContext->reqData[dataidxLoop_u8];
            }

            pMsgContext->resData[0x1] = 0x0u;
            pMsgContext->resData[0x0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
            pMsgContext->resDataLen = (pMsgContext->reqDataLen+0x1u);

            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;

        }
        else if(dataReturnVal_u8 == DCM_E_PENDING)
        {

            Dcm_stDspRoeDidOpStatusIsPending_b = TRUE;
            *dataNegRespCode_u8 =0x0u;
            Dcm_stRoeOpstatus_u8=DCM_PENDING;
            Dcm_RoeDidIdx_u8 =dataidxLoop_u8;

        }
        else{
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
            Dcm_stRoeOpstatus_u8=DCM_INITIAL;
            if(*dataNegRespCode_u8 == 0x0u)
            {

                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
    return dataReturnVal_u8;
}

#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

static FUNC(Std_ReturnType,DCM_CODE) Dcm_SetUpRoeDtcEvent(
        P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;
   VAR(uint8, AUTOMATIC) dataidxLoop_u8;

    dataReturnVal_u8 = E_NOT_OK;

    dataReturnVal_u8 = DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDtcEvent.RoeEventId_u8
   ,     Dcm_stEventType_u8
   ,     Dcm_stDspRoeStorageState_b
   ,     Dcm_stRoeEventWindowTime_u8
   ,     &pMsgContext->reqData[DCM_ROE_POSEVENTRECORD]
   ,     &pMsgContext->reqData[DCM_ROE_POSDTCSRVTORESPTORECORD]
   ,     Dcm_stRoeOpstatus_u8
   ,     dataNegRespCode_u8 );

   if(dataReturnVal_u8 == E_OK)
   {
        *dataNegRespCode_u8 = 0;
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;

        DcmDspRoeDtcStateVariable.stRoeEventWindowTime_u8 = Dcm_stRoeEventWindowTime_u8;
        DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8=pMsgContext->reqData[DCM_ROE_POSEVENTRECORD];
        DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STOPPED;
        DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);

        for(dataidxLoop_u8=(uint8)(pMsgContext->reqDataLen-1u); dataidxLoop_u8 > 0u; dataidxLoop_u8--)
        {

            pMsgContext->resData[dataidxLoop_u8+0x1u] = pMsgContext->reqData[dataidxLoop_u8];
        }
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;

        pMsgContext->resData[0x1] = 0x0u;
        pMsgContext->resData[0x0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
        pMsgContext->resDataLen = (pMsgContext->reqDataLen+0x1u);

        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
   }
   else if(dataReturnVal_u8 == DCM_E_PENDING)
   {

        *dataNegRespCode_u8 =0x0u;
        Dcm_stRoeOpstatus_u8=DCM_PENDING;
        Dcm_stDspRoeDtcOpStatusIsPending_b = TRUE;
   }
   else{
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        if(*dataNegRespCode_u8 == 0)
        {

            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
   }
    return dataReturnVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_StoreRoeDtcEventInfo(
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8;

    dataRetValue_u8=DcmAppl_DcmStoreRoeDTCInfo (DcmDspRoeDtcEvent.RoeEventId_u8
   ,     DcmDspRoeDtcStateVariable.RoeEventStatus
   ,     DcmDspRoeDtcStateVariable.SourceAddress_u16
   ,     DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8
   ,     DcmDspRoeDtcStateVariable.stDspRoeStorageState_b
   ,     Dcm_stRoeOpstatus_u8
   ,     DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b
   ,     dataNegRespCode_u8);

   if(dataRetValue_u8 == E_OK)
   {
        dataRetValue_u8 = E_OK;

        if(Dcm_stDspRoeDtcOpStatusIsPending_b == FALSE)
        {

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DcmDspRoeDtcStateVariable.RoeEventStatus);

            Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        }

        *dataNegRespCode_u8 = 0x0u;
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;

   }
   else if(dataRetValue_u8 == DCM_E_PENDING)
   {
        dataRetValue_u8 = DCM_E_PENDING;
        Dcm_stDspRoeDtcOpStatusIsPending_b = TRUE;
        Dcm_stRoeOpstatus_u8=DCM_PENDING;
        *dataNegRespCode_u8 = 0x0u;

   }
   else{
        dataRetValue_u8 = E_NOT_OK;

        DcmDspRoeDtcStateVariable.RoeEventStatus = s_DcmOldRoeDtcState;
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        if(*dataNegRespCode_u8 == 0)
        {

            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }

        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
   }
    return dataRetValue_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_ControlRoeDtcEventType(
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(boolean, AUTOMATIC) dataDtcStatusflag_b = FALSE;
   VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8 = E_NOT_OK;

   if( Dcm_stDspRoeDtcOpStatusIsPending_b == FALSE)
   {

        dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];

        DcmDspRoeDtcStateVariable.SourceAddress_u16=
                Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
        s_DcmOldRoeDtcState = DcmDspRoeDtcStateVariable.RoeEventStatus;

        if((DCM_ROE_STOP==Dcm_stEventType_u8) && (DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus))
        {

            DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STOPPED;
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            dataDtcStatusflag_b=TRUE;
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b=FALSE;
        }

        else if((DCM_ROE_START==Dcm_stEventType_u8) && (DCM_ROE_STOPPED==DcmDspRoeDtcStateVariable.RoeEventStatus))
        {

            DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STARTED;
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            dataDtcStatusflag_b=TRUE;
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b =FALSE;

            if(dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
            {
                DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b =TRUE;
            }
        }
        else if(DCM_ROE_CLEAR == Dcm_stEventType_u8)
        {

            DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_CLEARED;
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            dataDtcStatusflag_b=TRUE;
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b=FALSE;

        }
        else{

        }
   }

   if((dataDtcStatusflag_b != FALSE) || ( Dcm_stDspRoeDtcOpStatusIsPending_b != FALSE))
   {

        DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;

        dataReturnVal_u8 =Dcm_StoreRoeDtcEventInfo(dataNegRespCode_u8);
   }

    return dataReturnVal_u8;
}

#endif

static FUNC(void,DCM_CODE) Dcm_CheckRoeEventType(void){

   if((Dcm_stEventType_u8 == DCM_ROE_STOP) ||
            (Dcm_stEventType_u8 == DCM_ROE_START)||
            (Dcm_stEventType_u8 == DCM_ROE_CLEAR))
   {

        Dcm_stDspRoeState_en = DCM_DSP_ROE_CONTROLEVENT;
   }

   else if((Dcm_stEventType_u8 == DCM_ROE_ONDTCSTATUSCHANGE)||
            (Dcm_stEventType_u8 == DCM_ROE_ONCHANGEOFDID))
   {

        Dcm_stDspRoeState_en = DCM_DSP_ROE_SETUPEVENT;
   }

   else if(Dcm_stEventType_u8 == DCM_ROE_REPORTACTIVEEVENTS)
   {

        Dcm_stDspRoeState_en = DCM_DSP_ROE_REPORTEVENTS;
   }

   else{

   }
}

static FUNC(void,DCM_CODE) Dcm_RoeLengthCheck(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint16, AUTOMATIC) dataReqLen_u16;

    Dcm_stEventType_u8 = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];

    Dcm_stDspRoeStorageState_b = ((Dcm_stEventType_u8 & DCM_DSP_ROE_STORAGEBIT_MSK) != 0x00u);

    Dcm_stEventType_u8 = (Dcm_stEventType_u8 & ((uint8)(~DCM_DSP_ROE_STORAGEBIT_MSK)));

    dataReqLen_u16 = 0x02u;

   if(Dcm_stEventType_u8 == DCM_ROE_ONCHANGEOFDID)
   {

        dataReqLen_u16 = (dataReqLen_u16 + DCM_DSP_ROE_DIDRECORDLEN);
   }

   else if(Dcm_stEventType_u8 == DCM_ROE_ONDTCSTATUSCHANGE)
   {

        dataReqLen_u16 = (dataReqLen_u16 + DCM_DSP_ROE_DTCRECORDLEN);
   }

#if(DCM_CFG_ROE_WINTIMEINREPEVENTSREQ == DCM_CFG_OFF)

   else if(Dcm_stEventType_u8 == DCM_ROE_REPORTACTIVEEVENTS)
   {
        dataReqLen_u16 = DCM_DSP_ROE_MINREQLEN;
   }
#endif
   else{

   }

   if(pMsgContext->reqDataLen == dataReqLen_u16)
   {

        Dcm_CheckRoeEventType();
   }
   else{
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   }
}

static FUNC(void,DCM_CODE) Dcm_ReportRoeEvents(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{

   VAR(uint8, AUTOMATIC) idxReportEvents_u8;
   VAR(uint8, AUTOMATIC) idxRoeResponse_u8;
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
   VAR(uint8, AUTOMATIC) dataidxLoop_u8;
   VAR(uint16, AUTOMATIC) dataID_u16;
#endif

   idxReportEvents_u8 =0u;

    pMsgContext->resData[0x0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
   idxRoeResponse_u8=0x2u;

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)

   for(dataidxLoop_u8=0;(dataidxLoop_u8<DCM_MAX_DIDROEEVENTS);dataidxLoop_u8++)
   {
        if(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus == DCM_ROE_STARTED)
        {
            dataID_u16 = DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventRecord_u16;

            pMsgContext->resData[idxRoeResponse_u8] = DCM_ROE_ONCHANGEOFDID;
            idxRoeResponse_u8++;

            pMsgContext->resData[idxRoeResponse_u8] = DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventWindowTime_u8;
            idxRoeResponse_u8++;

            pMsgContext->resData[idxRoeResponse_u8] = (uint8)(dataID_u16>>8u);
            idxRoeResponse_u8++;
            pMsgContext->resData[idxRoeResponse_u8] =(uint8) dataID_u16;
            idxRoeResponse_u8++;
            pMsgContext->resData[idxRoeResponse_u8] = 0x22u;
            idxRoeResponse_u8++;
            pMsgContext->resData[idxRoeResponse_u8] = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16>>8u);
            idxRoeResponse_u8++;
            pMsgContext->resData[idxRoeResponse_u8] = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16);
            idxRoeResponse_u8++;
            idxReportEvents_u8++;
        }

   }
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
   if(DcmDspRoeDtcStateVariable.RoeEventStatus == DCM_ROE_STARTED)
   {
        pMsgContext->resData[idxRoeResponse_u8] = DCM_ROE_ONDTCSTATUSCHANGE;
        idxRoeResponse_u8=idxRoeResponse_u8+1;
        pMsgContext->resData[idxRoeResponse_u8] = DcmDspRoeDtcStateVariable.stRoeEventWindowTime_u8;
        idxRoeResponse_u8=idxRoeResponse_u8+1;
        pMsgContext->resData[idxRoeResponse_u8] = DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8;
        idxRoeResponse_u8=idxRoeResponse_u8+1;
        pMsgContext->resData[idxRoeResponse_u8] = 0x19u;
        idxRoeResponse_u8=idxRoeResponse_u8+1;
        pMsgContext->resData[idxRoeResponse_u8] = 0x0Eu;
        idxRoeResponse_u8=idxRoeResponse_u8+1;
        idxReportEvents_u8++;
   }
#endif
    pMsgContext->resData[0x1] = idxReportEvents_u8;
    pMsgContext->resDataLen = idxRoeResponse_u8;
}

static FUNC(void,DCM_CODE)Dcm_RoeCtrlConditionAndSequenceCheck(
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
   VAR(uint8, AUTOMATIC) dataidxLoop_u8;
#endif
   if(Dcm_stEventType_u8 == DCM_ROE_START)
   {

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

        if((DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus)&&
           (DcmDspRoeDtcStateVariable.SourceAddress_u16!=
                   Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16))
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
#endif

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

        for(dataidxLoop_u8=0x0u;((dataidxLoop_u8<DCM_MAX_DIDROEEVENTS) && (*dataNegRespCode_u8 == 0x0u));
                dataidxLoop_u8++)
        {
            if((DCM_ROE_STARTED==DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus)&&
               (DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].SourceAddress_u16!=
                       Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16))
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                break;
            }
        }
#endif
   }

   if((Dcm_stEventType_u8 == DCM_ROE_START) ||(Dcm_stEventType_u8 == DCM_ROE_STOP))
   {
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(DcmDspRoeDtcStateVariable.RoeEventStatus==DCM_ROE_CLEARED)
#endif
        {
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

            for(dataidxLoop_u8=0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
            {
                if(DCM_ROE_CLEARED!=DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus)
                {
                    break;
                }
            }
            if(dataidxLoop_u8==DCM_MAX_DIDROEEVENTS)
#endif
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
            }
        }
   }
}

FUNC(void,DCM_CODE) Dcm_DcmResponseOnEventIni (void){
   VAR(Dcm_NegativeResponseCodeType, AUTOMATIC) NegRespCode_u8 = 0u;
   if((DCM_PENDING == Dcm_stRoeOpstatus_u8) && (Dcm_stDspRoeState_en == DCM_DSP_ROE_SETUPEVENT))
   {
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDidOpStatusIsPending_b != FALSE)
        {

            (void)DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8
   ,     Dcm_stEventType_u8
   ,     FALSE
   ,     0x0u
   ,     NULL_PTR
   ,     NULL_PTR
   ,     DCM_CANCEL
   ,     &NegRespCode_u8 );
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        }
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDtcOpStatusIsPending_b != FALSE)
        {
            (void)DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDtcEvent.RoeEventId_u8
   ,     Dcm_stEventType_u8
   ,     Dcm_stDspRoeStorageState_b
   ,     Dcm_stRoeEventWindowTime_u8
   ,     NULL_PTR
   ,     NULL_PTR
   ,     DCM_CANCEL
   ,     &NegRespCode_u8 );
            Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        }
#endif
   }
   else if((DCM_PENDING == Dcm_stRoeOpstatus_u8) && (Dcm_stDspRoeState_en == DCM_DSP_ROE_CONTROLEVENT))
   {
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDidOpStatusIsPending_b != FALSE)
        {

            (void)DcmAppl_DcmStoreRoeDidInfo(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventDid_u16
   ,     DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8
   ,     DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus
   ,     DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].SourceAddress_u16
   ,     DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].stDspRoeStorageState_b
   ,     DCM_CANCEL
   ,     DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].stDspRoeSessionIsDefault_b
   ,     &NegRespCode_u8);
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        }
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDtcOpStatusIsPending_b != FALSE)
        {

            (void)DcmAppl_DcmStoreRoeDTCInfo (DcmDspRoeDtcEvent.RoeEventId_u8
   ,     DcmDspRoeDtcStateVariable.RoeEventStatus
   ,     DcmDspRoeDtcStateVariable.SourceAddress_u16
   ,     DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8
   ,     DcmDspRoeDtcStateVariable.stDspRoeStorageState_b
   ,     DCM_CANCEL
   ,     DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b
   ,     &NegRespCode_u8);
            Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        }
#endif
   }
   else{

   }

    Dcm_stRoeOpstatus_u8=DCM_INITIAL;
    Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
    Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;

    Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;

    Dcm_stDspRoeStorageState_b = FALSE;
    (void)NegRespCode_u8;
}

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)

FUNC(void,DCM_CODE)Dcm_ResetRoeOnDtcevents(void){
   VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];

    DcmDspRoeDtcStateVariable.SourceAddress_u16=0xFFu;
    DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STOPPED;

    DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=FALSE;
    DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8=0x0u;

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
    (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
    DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);

   if((DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b != FALSE) &&
            (dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]))
   {
        DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STARTED;
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STARTED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STARTED);
   }
}

#endif
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)

FUNC(void,DCM_CODE) Dcm_ResetRoeDidevents(void){
   VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];

    Dcm_RoeDidIdx_u8=0;
   while(Dcm_RoeDidIdx_u8<DCM_MAX_DIDROEEVENTS)
   {
        if(DCM_ROE_STARTED==DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus)
        {

            DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus=DCM_ROE_STOPPED;
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8,DCM_ROE_STOPPED);
        }
        if((DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].stDspRoeSessionIsDefault_b != FALSE) &&
                (dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]))
        {
            DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus=DCM_ROE_STARTED;
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].ROEDID_fp))(DCM_ROE_STARTED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8,DCM_ROE_STARTED);
        }
        Dcm_RoeDidIdx_u8++;
   }
}
#endif

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_DcmRoe_Controlevent (
                                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;

    dataReturnVal_u8=E_NOT_OK;

    Dcm_stRoeEventWindowTime_u8 = pMsgContext->reqData[DCM_DSP_ROE_POSWINDOWTIME];
   if(Dcm_stRoeOpstatus_u8!=DCM_PENDING)
   {
        Dcm_RoeCtrlConditionAndSequenceCheck(dataNegRespCode_u8);
   }

   if((*dataNegRespCode_u8 == 0x0u))
   {

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if( ((Dcm_stRoeOpstatus_u8==DCM_INITIAL)&&( Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)) ||
                ( Dcm_stDspRoeDtcOpStatusIsPending_b == TRUE))
        {
            dataReturnVal_u8 = Dcm_ControlRoeDtcEventType(dataNegRespCode_u8);
        }
#endif
        if((((Dcm_stRoeOpstatus_u8==DCM_INITIAL)&&( Dcm_stDspRoeDtcOpStatusIsPending_b == FALSE)) ||
                ( Dcm_stDspRoeDidOpStatusIsPending_b == TRUE)) && (*dataNegRespCode_u8 == 0x0u))
        {
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

            dataReturnVal_u8 = Dcm_ControlRoeDidEventType(dataNegRespCode_u8);

#endif
        }
        else{

        }
        if((dataReturnVal_u8==E_OK) &&(*dataNegRespCode_u8 == 0x0u))
        {

            pMsgContext->resData[2] = Dcm_stRoeEventWindowTime_u8;
            pMsgContext->resData[1] = 0x0u;
            pMsgContext->resData[0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
            pMsgContext->resDataLen = 0x03u;

        }

   }

    return(dataReturnVal_u8);
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_DcmRoe_SetUpevent_WindowTime (
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   if((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_INFINITE) ||
            (Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_CYCLE) ||
            (Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_AND_FOLLOWING_CYCLE))
   {
        if(((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_INFINITE) && (DCM_ROE_VALIDATE_STORAGESTATE_INFINITE == TRUE)) ||\
         ((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_CYCLE) && (DCM_ROE_VALIDATE_STORAGESTATE_CURRENT == TRUE)) ||\
         ((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_AND_FOLLOWING_CYCLE) && (DCM_ROE_VALIDATE_STORAGESTATE_CURRENT_FOLLOWING == TRUE)))

        {

            if(( ((Dcm_stRoeEventWindowTime_u8 == 0x02u) || (Dcm_stRoeEventWindowTime_u8 == 0x04u)) && (Dcm_stDspRoeStorageState_b == FALSE))
                    ||((Dcm_stRoeEventWindowTime_u8 == 0x03u) &&(Dcm_stDspRoeStorageState_b != FALSE) ) )
            {

                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }

        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }

    return(*dataNegRespCode_u8);
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_DcmRoe_SetUpevent_ONCHANGEOFDID (

                                      P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType, AUTOMATIC)   dataReturnVal_u8;

    dataReturnVal_u8=E_NOT_OK;

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
   if(pMsgContext->reqData[4] == 0x22u)
   {

    dataReturnVal_u8 = Dcm_SetUpRoeDidEvent(pMsgContext,dataNegRespCode_u8);

   if(dataReturnVal_u8 != DCM_E_PENDING)
   {
        if(dataReturnVal_u8!=E_OK)
        {

            if(*dataNegRespCode_u8 ==0x0u)
            {

                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }

        }

        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
        Dcm_stRoeOpstatus_u8 =DCM_INITIAL;
   }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
#else
    (void)pMsgContext;
    (void)dataNegRespCode_u8;
#endif
    return(dataReturnVal_u8);
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_DcmRoe_SetUpevent_ONDTCSTATUSCHANGE (
                                     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;

    dataReturnVal_u8=E_NOT_OK;

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
   if((pMsgContext->reqData[3] == 0x19u) && (pMsgContext->reqData[4] == 0x0Eu))
   {

        dataReturnVal_u8 = Dcm_SetUpRoeDtcEvent(pMsgContext,dataNegRespCode_u8);

        if(dataReturnVal_u8 != DCM_E_PENDING)
        {
            if(dataReturnVal_u8!=E_OK)
            {

                if(*dataNegRespCode_u8 ==0x0u)
                {

                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                }

                Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
                Dcm_stRoeOpstatus_u8 =DCM_INITIAL;
            }
        }
   }
   else{

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
#endif
    return(dataReturnVal_u8);
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_DcmRoe_SetUpevent (
        P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;

    dataReturnVal_u8=E_NOT_OK;

    Dcm_stRoeEventWindowTime_u8 = pMsgContext->reqData[DCM_DSP_ROE_POSWINDOWTIME];

   if((*dataNegRespCode_u8 == 0u) && (Dcm_stRoeEventWindowTime_u8 != 0u) )
   {

        if(Dcm_stRoeOpstatus_u8 == DCM_INITIAL)
        {
            *dataNegRespCode_u8 = Dcm_Lok_DcmRoe_SetUpevent_WindowTime(dataNegRespCode_u8);
        }

        if(*dataNegRespCode_u8 == 0u)
        {

            if(Dcm_stEventType_u8 == DCM_ROE_ONCHANGEOFDID)
            {
                dataReturnVal_u8 = Dcm_Lok_DcmRoe_SetUpevent_ONCHANGEOFDID(pMsgContext,dataNegRespCode_u8);
            }
            else{
                if(Dcm_stEventType_u8 == DCM_ROE_ONDTCSTATUSCHANGE)
                {
                    dataReturnVal_u8 = Dcm_Lok_DcmRoe_SetUpevent_ONDTCSTATUSCHANGE(pMsgContext,dataNegRespCode_u8);
                }
            }
        }

   }

   else{

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }

    return(dataReturnVal_u8);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmResponseOnEvent (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Std_ReturnType, AUTOMATIC) dataReturnVal_u8;

    *dataNegRespCode_u8 = 0x0u;
    dataReturnVal_u8=E_NOT_OK;

    DCM_UNUSED_PARAM(OpStatus);

   if(DCM_CANCEL == OpStatus)
   {

        Dcm_DcmResponseOnEventIni();
        dataReturnVal_u8=E_OK;
   }
   else{

        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_INIT)
        {
            Dcm_RoeLengthCheck(pMsgContext,dataNegRespCode_u8);

        }

        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_CONTROLEVENT)
        {
            dataReturnVal_u8 = Dcm_Lok_DcmRoe_Controlevent(pMsgContext,dataNegRespCode_u8);
        }

        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_SETUPEVENT)
        {
            dataReturnVal_u8 = Dcm_Lok_DcmRoe_SetUpevent(pMsgContext,dataNegRespCode_u8);
        }

        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_REPORTEVENTS)
        {
            dataReturnVal_u8=E_OK;
            Dcm_ReportRoeEvents(pMsgContext);
            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
        }

        if(*dataNegRespCode_u8 != 0x0u)
        {
            dataReturnVal_u8=E_NOT_OK;

            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
        }
        if(dataReturnVal_u8 == E_OK)
        {

            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
            Dcm_stRoeOpstatus_u8 = DCM_INITIAL;
        }
   }
    return dataReturnVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

