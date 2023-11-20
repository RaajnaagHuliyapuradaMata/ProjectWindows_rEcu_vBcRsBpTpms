#include "Std_Types.hpp"

#include "DcmDspUds_Rc_Inf.hpp"
#include "DcmDspUds_Uds_Prot.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA)                                        Dcm_RCInPtr_pu8;
P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA)                                        Dcm_RCOutPtr_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RC_NUMRIDS > 0u)
static P2CONST(Dcm_DspRoutineType_tst, DCM_VAR, DCM_INTERN_CONST)           Dcm_adrRoutinePtr_pcst;
static P2CONST(Dcm_DspRoutineType_tst, AUTOMATIC, DCM_INTERN_CONST)         s_adrRoutine_pcst;
#endif
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
static P2CONST(Dcm_DspRoutineRangeType_tst, DCM_VAR, DCM_INTERN_CONST)      Dcm_adrRoutineRangePtr_pcst;
static P2CONST(Dcm_DspRoutineRangeType_tst, AUTOMATIC, DCM_INTERN_CONST)    s_adrRoutineRange_pcst;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_DspRCStateType_ten, DCM_VAR)                                 Dcm_stDspRCState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
static VAR(uint16,DCM_VAR)                                                  s_dataRidRange_u16;
static VAR(uint16,DCM_VAR)                                                  s_PendingRidRange_u16;
#endif
static VAR(uint16,DCM_VAR)                                                  s_dataStatusIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint8,DCM_VAR)                                                   Dcm_dataRCSubFunc_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint16,DCM_VAR)                                                         Dcm_RCCurrDataLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_NegativeResponseCodeType,DCM_VAR)                                   Dcm_RCNegResCode_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_OpStatusType,DCM_VAR)                                               Dcm_RCOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean,DCM_VAR)                                                 s_IsRCSubfunctionCalled_b;
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

static VAR(boolean, DCM_VAR)                                                s_IsRidRange_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Dsp_RC_Ini (void)
{
   VAR(uint16,AUTOMATIC) idxLoop_qu16;
    Dcm_RCOpStatus_u8 = DCM_CANCEL;
   if( Dcm_stDspRCState_en == DCM_RC_PENDING )
   {

        s_IsRCSubfunctionCalled_b = TRUE;
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

        if(s_IsRidRange_b)
        {
            (void)(*Dcm_adrRoutineRangePtr_pcst->adrCallRoutine_pfct)(Dcm_dataRCSubFunc_u8);
        }
        else
#endif
        {
#if(DCM_CFG_RC_NUMRIDS > 0u)
            (void)(*Dcm_adrRoutinePtr_pcst->adrCallRoutine_pfct)(Dcm_dataRCSubFunc_u8);
#endif
        }

        s_IsRCSubfunctionCalled_b = FALSE;
   }

#if(DCM_CFG_RC_NUMRIDS > 0u)

   s_adrRoutine_pcst =  &Dcm_DspRoutine_cast[0];

   for( idxLoop_qu16 = 0 ; idxLoop_qu16 < DCM_CFG_RC_NUMRIDS ; idxLoop_qu16++ )
   {
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)

        if( (s_adrRoutine_pcst->flgStopRoutine_b!= FALSE) && (s_adrRoutine_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineStatus_aen[idxLoop_qu16]== DCM_ROUTINE_STOP_PENDING )  )
        {

            s_IsRCSubfunctionCalled_b = TRUE;
            (void)(*s_adrRoutine_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);

            s_IsRCSubfunctionCalled_b = FALSE;
        }
#endif
        if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 >= DCM_CFG_MAX_WAITPEND)
        {

        }
        else{

            Dcm_RoutineStatus_aen[idxLoop_qu16] = DCM_ROUTINE_IDLE;
        }

        s_adrRoutine_pcst++;
   }
#endif

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

   s_adrRoutineRange_pcst = &Dcm_DspRoutineRange_cast[0];

   s_IsRidRange_b = FALSE;

   for(idxLoop_qu16 = 0; idxLoop_qu16 < DCM_CFG_RC_RANGE_NUMRIDS; idxLoop_qu16++)
   {
#if(DCM_CFG_RCRANGE_STOPSUPPORTED != DCM_CFG_OFF)

        if((s_adrRoutineRange_pcst->flgStopRoutine_b!= FALSE)&& (s_adrRoutineRange_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineRangeStatus_aen[idxLoop_qu16] == DCM_ROUTINE_STOP_PENDING))
        {

            s_IsRCSubfunctionCalled_b = TRUE;
            (void)(*s_adrRoutineRange_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);

            s_IsRCSubfunctionCalled_b = FALSE;
        }
#endif
        if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 >= DCM_CFG_MAX_WAITPEND)
        {

        }
        else{

            Dcm_RoutineRangeStatus_aen[idxLoop_qu16] = DCM_ROUTINE_IDLE;
        }

        s_adrRoutineRange_pcst++;
   }
#endif
    Dcm_RCOpStatus_u8 = DCM_INITIAL;
    Dcm_stDspRCState_en = DCM_RC_IDLE;
}

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_RcIsRIDRangeRoutine(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) flgRidSupported_b
   ,     VAR(uint16,AUTOMATIC)dataRId_u16
   ,     P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) idxLoop_qu16
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) NRC_u8)
{

   VAR(Std_ReturnType, AUTOMATIC) RetVal;

    RetVal = E_NOT_OK;

   s_IsRidRange_b = FALSE;

   s_adrRoutineRange_pcst = &Dcm_DspRoutineRange_cast[0];

   for(*idxLoop_qu16 = 0; *idxLoop_qu16 < DCM_CFG_RC_RANGE_NUMRIDS; (*idxLoop_qu16)++)
   {
        if((dataRId_u16 >= s_adrRoutineRange_pcst->RidRangeLowerLimit_u16) && (dataRId_u16 <= s_adrRoutineRange_pcst->RidRangeUpperLimit_u16))
        {

            s_IsRidRange_b = TRUE;

            s_dataRidRange_u16 = dataRId_u16;

            if(s_adrRoutineRange_pcst->RoutineRangeHasGaps_b == TRUE)
            {
                RetVal = (*(s_adrRoutineRange_pcst->IsRIDRangeAvailFnc_pf))(dataRId_u16,NRC_u8);

                if(RetVal == E_OK)
                {

                    *flgRidSupported_b = TRUE;
                }
                else{

                    s_IsRidRange_b = FALSE;
                }
            }
            else{

                *flgRidSupported_b = TRUE;
            }
#if(DCM_CFG_RCRANGE_STOPSUPPORTED != DCM_CFG_OFF)

            if((*NRC_u8 ==0x00) && (s_adrRoutineRange_pcst->flgStopRoutine_b!= FALSE)&& (s_adrRoutineRange_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineRangeStatus_aen[*idxLoop_qu16] == DCM_ROUTINE_STOP_PENDING ))
            {

                Dcm_RCOpStatus_u8 = DCM_CANCEL;

                s_IsRCSubfunctionCalled_b = TRUE;
                (void)(*s_adrRoutineRange_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);

                s_IsRCSubfunctionCalled_b = FALSE;
                *flgRidSupported_b = FALSE;
                s_IsRidRange_b = FALSE;
                Dcm_RoutineRangeStatus_aen[*idxLoop_qu16] = DCM_ROUTINE_STOP;
            }
            Dcm_RCOpStatus_u8 = DCM_INITIAL;
#endif

            if(*NRC_u8 == 0x00)
            {

                s_dataStatusIdx_u16 = (uint16)(*idxLoop_qu16);
            }
            break;
        }

        s_adrRoutineRange_pcst++;
   }

    return RetVal;
}
#endif

#if(DCM_CFG_RC_NUMRIDS > 0u)

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_RcIsRIDSingleRoutine(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) flgRidSupported_b
   ,     VAR(uint16,AUTOMATIC)dataRId_u16
   ,     P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) idxLoop_qu16
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) NRC_u8)
{

   VAR(Std_ReturnType, AUTOMATIC) RetVal;

    RetVal = E_NOT_OK;

   s_adrRoutine_pcst =  &Dcm_DspRoutine_cast[0];

   for(*idxLoop_qu16 = 0; *idxLoop_qu16 < DCM_CFG_RC_NUMRIDS; (*idxLoop_qu16)++ )
   {
        if(dataRId_u16 == s_adrRoutine_pcst->dataRId_u16)
        {

            *flgRidSupported_b = TRUE;
            RetVal = E_OK;
#if(DCM_CFG_DSP_NUMISRIDAVAIL>0)

            if(*Dcm_RIDIsAvail[s_adrRoutine_pcst->idxRIDSupportedFnc_u16] != NULL_PTR)
            {
                if((*(IsRIDAvailFnc_pf)(Dcm_RIDIsAvail[s_adrRoutine_pcst->idxRIDSupportedFnc_u16]))(s_adrRoutine_pcst->dataRId_u16)!=E_OK)
                {

                    *NRC_u8 = DCM_E_REQUESTOUTOFRANGE;
                    *flgRidSupported_b = FALSE;
                    RetVal = E_NOT_OK;
                }
            }
#else
            DCM_UNUSED_PARAM(NRC_u8);
#endif
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)

            if((*NRC_u8 ==0x00) && (s_adrRoutine_pcst->flgStopRoutine_b!= FALSE)&& (s_adrRoutine_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineStatus_aen[*idxLoop_qu16] == DCM_ROUTINE_STOP_PENDING ))
            {

                Dcm_RCOpStatus_u8 = DCM_CANCEL;

                s_IsRCSubfunctionCalled_b = TRUE;
                (void)(*s_adrRoutine_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);

                s_IsRCSubfunctionCalled_b = FALSE;
                *flgRidSupported_b = FALSE;
                Dcm_RoutineStatus_aen[*idxLoop_qu16] = DCM_ROUTINE_STOP;
            }
            Dcm_RCOpStatus_u8 = DCM_INITIAL;
#endif

            if(*NRC_u8 ==0x00)
            {

                s_dataStatusIdx_u16 = (uint16)(*idxLoop_qu16);
            }
            break;
        }

        s_adrRoutine_pcst++;
   }

   if((*idxLoop_qu16 == DCM_CFG_RC_NUMRIDS) && (*NRC_u8 == 0x00))
   {
        *NRC_u8 = DCM_E_REQUESTOUTOFRANGE;
   }

    return RetVal;
}
#endif

static FUNC(boolean,DCM_CODE) Dcm_Lok_RcIsRIDSupported (VAR(uint16,AUTOMATIC)dataRId_u16
   ,     P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) idxLoop_qu16
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) NRC_u8)
{

   VAR(Std_ReturnType, AUTOMATIC) RetVal;

   VAR(boolean, AUTOMATIC) flgRidSupported_b = FALSE;

   s_dataStatusIdx_u16 = 0xFFFF;

    RetVal = E_NOT_OK;

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
    RetVal = Dcm_Lok_RcIsRIDRangeRoutine(&flgRidSupported_b,dataRId_u16,idxLoop_qu16,NRC_u8);
#endif

   if((!flgRidSupported_b)
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
            && (!s_IsRidRange_b)
#endif
    )
   {
#if(DCM_CFG_RC_NUMRIDS > 0u)
        RetVal = Dcm_Lok_RcIsRIDSingleRoutine(&flgRidSupported_b,dataRId_u16,idxLoop_qu16,NRC_u8);
#endif
   }

   if((!flgRidSupported_b) && ((RetVal == E_NOT_OK) && (*NRC_u8 == 0x00)))
   {

        *NRC_u8 = DCM_E_REQUESTOUTOFRANGE;
   }

    return flgRidSupported_b;
}

#if(DCM_CFG_RC_NUMRIDS > 0u)

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_RcProcessRoutine(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR(uint16,AUTOMATIC) dataRId_u16)
{
   P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_CONST)  adrSignal_pcst;
   VAR(uint32, AUTOMATIC) dataSessionBitMask_u32;
   VAR(uint32, AUTOMATIC) dataSecurityBitMask_u32;
#if(DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
   VAR(uint32, AUTOMATIC)  dataSigVal_u32;
   VAR(uint16,AUTOMATIC) idxLoop_qu16;
#endif
   VAR(uint16,AUTOMATIC) nrCtrlOptRecSize_u16;
   VAR(uint8,AUTOMATIC) dataSubFunc_u8;
   VAR(uint8,AUTOMATIC) nrSig_u8;
   VAR(boolean, AUTOMATIC) flgReqSequenceError_b;
   VAR(boolean, AUTOMATIC) flgModeRetVal_b;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    flgReqSequenceError_b = FALSE;

    flgModeRetVal_b =TRUE;
    adrSignal_pcst = NULL_PTR;
    dataRetVal_u8=DCM_E_PENDING;
    dataSubFunc_u8 = pMsgContext->reqData[0];

    nrCtrlOptRecSize_u16 = (uint16)(pMsgContext->reqDataLen - 3u);
    dataSessionBitMask_u32 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSessBitMask_u32;

   if(((Dcm_DsldGetActiveSessionMask_u32() & dataSessionBitMask_u32) != 0u)
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
            && ((Dcm_ActiveConfiguration_u8 & Dcm_DspRoutine_cast[s_dataStatusIdx_u16].dataConfigMask_u8)!= 0u)
#endif
    )
   {

        dataSecurityBitMask_u32 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSecBitMask_u32;

        if((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityBitMask_u32) != 0u)
        {

            if(( ( dataSubFunc_u8 == 0x01u ) && ( s_adrRoutine_pcst->flgStartRoutine_b != FALSE ))||
                    ( ( dataSubFunc_u8 == 0x02u ) && ( s_adrRoutine_pcst->flgStopRoutine_b != FALSE ))||
                    ( ( dataSubFunc_u8 == 0x03u ) && ( s_adrRoutine_pcst->dataReqRslt_b != FALSE ) ) )
            {

                Dcm_adrRoutinePtr_pcst = s_adrRoutine_pcst;
                Dcm_dataRCSubFunc_u8 = dataSubFunc_u8;
                Dcm_RCOpStatus_u8 = DCM_INITIAL;
                Dcm_RCNegResCode_u8 = 0;
                Dcm_RCCurrDataLength_u16 = 0;
                Dcm_stDspRCState_en = DCM_RC_PENDING;
                nrSig_u8 = 0;

                if( ( dataSubFunc_u8 == 0x01u ) &&
                        ( ( nrCtrlOptRecSize_u16 == s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStart_u16 ) ||
                                ( ( s_adrRoutine_pcst->dataFixedLen_b == FALSE ) &&
                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStart_u16 ) &&
                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16 ) ) ) )
                {

#if(DCM_CFG_STARTSUPPORTED != DCM_CFG_OFF)
                    adrSignal_pcst = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrStartInSignalRef_cpcst;
                    nrSig_u8 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->nrStartInSignals_u8;
                    Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16);
                    Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16]);
                    Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStart_u16]);
#endif
                }

#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
                else if( ( dataSubFunc_u8 == 0x02u ) &&
                        ( ( nrCtrlOptRecSize_u16 == s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStop_u16 ) ||
                                ( ( s_adrRoutine_pcst->dataFixedLen_b == FALSE ) &&
                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStop_u16 ) &&
                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16 ) ) ) )
                {

                    if(((DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])&& (s_adrRoutine_pcst->flgStartRoutine_b==FALSE ))||
                            (((DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]) || (DCM_ROUTINE_STOP == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]))&& ( s_adrRoutine_pcst->flgReqSequenceErrorSupported_b==FALSE))||
                            ((DCM_ROUTINE_IDLE != Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]) &&(DCM_ROUTINE_STOP != Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])))
                    {
                        adrSignal_pcst = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrStopInSignalRef_cpcst;
                        nrSig_u8 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->nrStopInSignals_u8;
                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16);
                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16]);
                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStop_u16]);
                    }
                    else
                    {

                        flgReqSequenceError_b = TRUE;
                    }
                }
#endif
#if(DCM_CFG_REQRESULTSSUPPORTED != DCM_CFG_OFF)

                else if((dataSubFunc_u8 == 0x03u) &&
                        (( nrCtrlOptRecSize_u16 == s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeReqRslt_u16) ||
                                ( ( s_adrRoutine_pcst->dataFixedLen_b == FALSE ) &&
                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeReqRslt_u16  ) &&
                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16 ) ) ))

                {

                    if(((DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]) && (s_adrRoutine_pcst->flgStartRoutine_b==FALSE) )||
                            (( DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])&& ( s_adrRoutine_pcst->flgReqSequenceErrorSupported_b==FALSE))||
                            ((DCM_ROUTINE_IDLE != Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])))
                    {
                        adrSignal_pcst = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrReqRslInSignalRef_cpcst;
                        nrSig_u8 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->nrReqRslInSignals_u8;
                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16);
                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16]);
                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeReqRslt_u16]);
                    }
                    else
                    {

                        flgReqSequenceError_b = TRUE;
                    }
                }
#endif
                else{

                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;

                    Dcm_stDspRCState_en = DCM_RC_IDLE;
                }

                if(*dataNegRespCode_u8 == 0)
                {

                    if(nrCtrlOptRecSize_u16 > 0)
                    {
                        dataRetVal_u8 = DcmAppl_DcmCheckRoutineControlOptionRecord(dataRId_u16,dataSubFunc_u8,&pMsgContext->reqData[3],nrCtrlOptRecSize_u16);
                        if(E_OK != dataRetVal_u8)
                        {
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_stDspRCState_en = DCM_RC_IDLE;
                        }
                    }
                    if(*dataNegRespCode_u8 == 0)
                    {

                        if(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrUserRidModeRule_pfct!=NULL_PTR)
                        {

                            dataRetVal_u8 = (*s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrUserRidModeRule_pfct)(dataNegRespCode_u8,dataRId_u16,dataSubFunc_u8);
                        }
                        else
                        {

                            dataRetVal_u8 = DcmAppl_UserRIDModeRuleService(dataNegRespCode_u8,dataRId_u16,dataSubFunc_u8);
                        }

                        if(dataRetVal_u8 !=E_OK)
                        {
                            if(*dataNegRespCode_u8==0x00)
                            {
                                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                            }
                            flgModeRetVal_b = FALSE;
                        }
                        else
                        {
                            *dataNegRespCode_u8=0x00;
                        }
#if(DCM_CFG_DSP_MODERULEFORROUTINES != DCM_CFG_OFF)
                        if(*dataNegRespCode_u8 == 0x00)
                        {
                            if(( dataSubFunc_u8 == 0x01u ) && (s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStart_pfct != NULL_PTR))
                            {

                                flgModeRetVal_b=(*(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStart_pfct))(dataNegRespCode_u8);
                            }
                            else if(( dataSubFunc_u8 == 0x02u ) && (s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStop_pfct != NULL_PTR))

                            {
                                flgModeRetVal_b=(*(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStop_pfct))(dataNegRespCode_u8);
                            }
                            else if(( dataSubFunc_u8 == 0x03u ) && (s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForRequestResult_pfct != NULL_PTR))
                            {
                                flgModeRetVal_b=(*(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForRequestResult_pfct))(dataNegRespCode_u8);
                            }
                            else
                            {

                            }
                        }
#endif
                        if(flgModeRetVal_b == FALSE)
                        {
                            Dcm_stDspRCState_en = DCM_RC_IDLE;
                        }
                        else
                        {

                            if(flgReqSequenceError_b !=FALSE)
                            {
                                *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
                                Dcm_stDspRCState_en = DCM_RC_IDLE;
                            }
                            else
                            {

#if(DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
                                for( idxLoop_qu16 = 0 ; ( ( idxLoop_qu16 < nrSig_u8 ) && (*dataNegRespCode_u8==0x00)&& (adrSignal_pcst!=NULL_PTR) &&( adrSignal_pcst->dataType_u8 != DCM_VARIABLE_LENGTH ) ) ; idxLoop_qu16++ )
                                {
#if(DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF)
                                    if(adrSignal_pcst->dataType_u8 >= DCM_RCARRAYINDEX)
                                    {
                                        Dcm_RcSetSignalArray(adrSignal_pcst,&(pMsgContext->reqData[3]));
                                    }
                                    else
#endif
                                    {
                                        dataSigVal_u32 = 0;
                                        dataSigVal_u32 = Dcm_GetSignal_u32(adrSignal_pcst->dataType_u8, adrSignal_pcst->posnStart_u16, &(pMsgContext->reqData[3]),adrSignal_pcst->dataEndianness_u8);
                                        Dcm_RCSetSigVal(adrSignal_pcst->dataType_u8,adrSignal_pcst->idxSignal_u16,dataSigVal_u32);
                                    }
                                    adrSignal_pcst++;
                                }

#endif
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u)
                                if(adrSignal_pcst != NULL_PTR)
                                {

                                    if((adrSignal_pcst->dataType_u8 == DCM_VARIABLE_LENGTH) && (Dcm_RCCurrDataLength_u16 != 0x00))
                                    {

                                        DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]),Dcm_RCInPtr_pu8 ,Dcm_RCCurrDataLength_u16);
                                    }
                                }
#endif
                            }
                        }
                    }
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
        }
   }
   else{

        *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
   }
    return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_RcPendingRoutine(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_CONST)  adrSignal_pcst;
#if(DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
   VAR(uint32, AUTOMATIC)                                          dataSigVal_u32;
#endif
   VAR(uint16,AUTOMATIC) idxLoop_qu16;
   VAR(uint8,AUTOMATIC) nrSig_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    adrSignal_pcst = NULL_PTR;
    dataRetVal_u8=DCM_E_PENDING;

   s_IsRCSubfunctionCalled_b = TRUE;
    dataRetVal_u8 = (*Dcm_adrRoutinePtr_pcst->adrCallRoutine_pfct)(Dcm_dataRCSubFunc_u8);

   s_IsRCSubfunctionCalled_b = FALSE;

   if((Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE) && (Dcm_adrRoutinePtr_pcst->UsePort != FALSE))
   {
        dataRetVal_u8 = DCM_INFRASTRUCTURE_ERROR;
   }
   if(dataRetVal_u8 == E_OK)
   {
        if( Dcm_dataRCSubFunc_u8 == 0x01 )
        {
#if(DCM_CFG_STARTSUPPORTED != DCM_CFG_OFF)
            adrSignal_pcst = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->adrStartOutSignalRef_cpcst;
            nrSig_u8 = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->nrStartOutSignals_u8;
            pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStart_u16;

            Dcm_RoutineStatus_aen[s_dataStatusIdx_u16] = DCM_ROUTINE_STARTED;
#endif
        }
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
        else if( Dcm_dataRCSubFunc_u8 == 0x02 )
        {
            adrSignal_pcst = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->adrStopOutSignalRef_cpcst;
            nrSig_u8 = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->nrStopOutSignals_u8;
            pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStop_u16;

            Dcm_RoutineStatus_aen[s_dataStatusIdx_u16] = DCM_ROUTINE_STOP;
        }
#endif
        else{
#if(DCM_CFG_REQRESULTSSUPPORTED != DCM_CFG_OFF)
            adrSignal_pcst = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->adrReqRsltOutSignalRef_cpcst;
            nrSig_u8 = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->nrReqRsltOutSignals_u8;
            pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeReqRslt_u16;
#endif
        }
        for( idxLoop_qu16 = 0 ; ( ( idxLoop_qu16 < nrSig_u8 ) && ( adrSignal_pcst->dataType_u8 != DCM_VARIABLE_LENGTH ) ) ; idxLoop_qu16++ )
        {
#if(DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
#if(DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF)
            if(adrSignal_pcst->dataType_u8 >= DCM_RCARRAYINDEX)
            {
                Dcm_RcStoreSignalArray(adrSignal_pcst,&(pMsgContext->resData[3]));
            }
            else
#endif
            {
                dataSigVal_u32 = Dcm_RCGetSigVal_u32 ( adrSignal_pcst->dataType_u8, adrSignal_pcst->idxSignal_u16 );
                Dcm_StoreSignal(adrSignal_pcst->dataType_u8, adrSignal_pcst->posnStart_u16, &(pMsgContext->resData[3]), dataSigVal_u32, adrSignal_pcst->dataEndianness_u8 );
            }
#endif
            adrSignal_pcst++;
        }

        if( idxLoop_qu16 != nrSig_u8 )
        {

            pMsgContext->resDataLen = pMsgContext->resDataLen + Dcm_RCCurrDataLength_u16;
        }

        pMsgContext->resData[0] = Dcm_dataRCSubFunc_u8;

        pMsgContext->resData[1] = ( uint8 )( Dcm_adrRoutinePtr_pcst->dataRId_u16 >> 8u ) ;
        pMsgContext->resData[2] = ( uint8 )( Dcm_adrRoutinePtr_pcst->dataRId_u16 & 0x00ffu ) ;

        Dcm_stDspRCState_en = DCM_RC_IDLE;
   }
   else if(dataRetVal_u8 == E_NOT_OK)
   {

        if( Dcm_RCNegResCode_u8 != 0 )
        {
            *dataNegRespCode_u8 = Dcm_RCNegResCode_u8;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
   }
   else if(dataRetVal_u8 == DCM_E_PENDING)
   {

        Dcm_RCOpStatus_u8 = DCM_PENDING;

   }
   else if(dataRetVal_u8 == DCM_E_FORCE_RCRRP)
   {

        Dcm_RCOpStatus_u8=DCM_FORCE_RCRRP_OK;
   }
   else if((dataRetVal_u8 == DCM_INFRASTRUCTURE_ERROR) && (Dcm_adrRoutinePtr_pcst->UsePort != FALSE))
   {
        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
   }
   else{
        if( Dcm_RCNegResCode_u8 == 0 )
        {

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
        else{

            *dataNegRespCode_u8 = Dcm_RCNegResCode_u8;
        }
   }
    return dataRetVal_u8;
}
#endif

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_RcProcessRangeRoutine(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR(uint16,AUTOMATIC) dataRId_u16)
{
   P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_CONST)  adrSignal_pcst;
   VAR(uint32, AUTOMATIC) dataSessionBitMask_u32;
   VAR(uint32, AUTOMATIC) dataSecurityBitMask_u32;
#if(DCM_CFG_RCRANGE_ROUTINEVARLENGTH == DCM_CFG_OFF)
   VAR(uint32, AUTOMATIC)  dataSigVal_u32;
   VAR(uint16,AUTOMATIC) idxLoop_qu16;
#endif
   VAR(uint16,AUTOMATIC) nrCtrlOptRecSize_u16;
   VAR(uint8,AUTOMATIC) dataSubFunc_u8;
   VAR(uint8,AUTOMATIC) nrSig_u8;
   VAR(boolean, AUTOMATIC) flgReqSequenceError_b;
   VAR(boolean, AUTOMATIC) flgModeRetVal_b;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    flgReqSequenceError_b = FALSE;

    flgModeRetVal_b =TRUE;
    adrSignal_pcst = NULL_PTR;
    dataRetVal_u8=DCM_E_PENDING;
    dataSubFunc_u8 = pMsgContext->reqData[0];

    nrCtrlOptRecSize_u16 = (uint16)(pMsgContext->reqDataLen - 3u);
    dataSessionBitMask_u32 = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataSessBitMask_u32;

   if(((Dcm_DsldGetActiveSessionMask_u32() & dataSessionBitMask_u32) != 0u)
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
            && ((Dcm_ActiveConfiguration_u8 & Dcm_DspRoutineRange_cast[s_dataStatusIdx_u16].dataConfigMask_u8)!= 0u)
#endif
    )
   {

        dataSecurityBitMask_u32 = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataSecBitMask_u32;

        if((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityBitMask_u32) != 0u)
        {

            if(( ( dataSubFunc_u8 == 0x01u ) && ( s_adrRoutineRange_pcst->flgStartRoutine_b != FALSE ))||
                    ( ( dataSubFunc_u8 == 0x02u ) && ( s_adrRoutineRange_pcst->flgStopRoutine_b != FALSE ))||
                    ( ( dataSubFunc_u8 == 0x03u ) && ( s_adrRoutineRange_pcst->flgReqRsltRoutine_b != FALSE ) ) )
            {

                Dcm_adrRoutineRangePtr_pcst = s_adrRoutineRange_pcst;
                s_PendingRidRange_u16 = dataRId_u16;
                Dcm_dataRCSubFunc_u8 = dataSubFunc_u8;
                Dcm_RCOpStatus_u8 = DCM_INITIAL;
                Dcm_RCNegResCode_u8 = 0;
                Dcm_RCCurrDataLength_u16 = 0;
                Dcm_stDspRCState_en = DCM_RC_PENDING;
                nrSig_u8 = 0;

                if( ( dataSubFunc_u8 == 0x01u ) &&
                        ( ( nrCtrlOptRecSize_u16 == s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStart_u16 ) ||
                                ( ( s_adrRoutineRange_pcst->dataFixedLen_b == FALSE ) &&
                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStart_u16 ) &&
                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16 ) ) ) )
                {

#if(DCM_CFG_RCRANGE_STARTSUPPORTED != DCM_CFG_OFF)
                    adrSignal_pcst = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrStartInSignalRef_cpcst;
                    nrSig_u8 = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->nrStartInSignals_u8;
                    Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16);
                    Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16]);
                    Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStart_u16]);
#endif
                }

#if(DCM_CFG_RCRANGE_STOPSUPPORTED != DCM_CFG_OFF)
                else if( ( dataSubFunc_u8 == 0x02u ) &&
                        ( ( nrCtrlOptRecSize_u16 == s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStop_u16 ) ||
                                ( ( s_adrRoutineRange_pcst->dataFixedLen_b == FALSE ) &&
                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStop_u16 ) &&
                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16 ) ) ) )
                {

                    if(((DCM_ROUTINE_IDLE == Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16])&& (s_adrRoutineRange_pcst->flgStartRoutine_b==FALSE ))||
                            (((DCM_ROUTINE_IDLE == Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16]) || (DCM_ROUTINE_STOP == Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16]))&& ( s_adrRoutineRange_pcst->flgReqSequenceErrorSupported_b==FALSE))||
                            ((DCM_ROUTINE_IDLE != Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16]) &&(DCM_ROUTINE_STOP != Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16])))
                    {
                        adrSignal_pcst = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrStopInSignalRef_cpcst;
                        nrSig_u8 = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->nrStopInSignals_u8;
                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16);
                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16]);
                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStop_u16]);
                    }
                    else
                    {

                        flgReqSequenceError_b = TRUE;
                    }
                }
#endif
#if(DCM_CFG_RCRANGE_REQRESULTSSUPPORTED != DCM_CFG_OFF)

                else if((dataSubFunc_u8 == 0x03u) &&
                        (( nrCtrlOptRecSize_u16 == s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeReqRslt_u16) ||
                                ( ( s_adrRoutineRange_pcst->dataFixedLen_b == FALSE ) &&
                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeReqRslt_u16  ) &&
                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16 ) ) ))

                {

                    if(((DCM_ROUTINE_IDLE == Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16]) && (s_adrRoutineRange_pcst->flgStartRoutine_b==FALSE) )||
                            (( DCM_ROUTINE_IDLE == Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16])&& ( s_adrRoutineRange_pcst->flgReqSequenceErrorSupported_b==FALSE))||
                            ((DCM_ROUTINE_IDLE != Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16])))
                    {
                        adrSignal_pcst = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrReqRslInSignalRef_cpcst;
                        nrSig_u8 = s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->nrReqRslInSignals_u8;
                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16);
                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16]);
                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeReqRslt_u16]);
                    }
                    else
                    {

                        flgReqSequenceError_b = TRUE;
                    }
                }
#endif
                else{

                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;

                    Dcm_stDspRCState_en = DCM_RC_IDLE;
                }

                if(*dataNegRespCode_u8 == 0)
                {

                    if(nrCtrlOptRecSize_u16 > 0)
                    {
                        dataRetVal_u8 = DcmAppl_DcmCheckRoutineControlOptionRecord(dataRId_u16,dataSubFunc_u8,&pMsgContext->reqData[3],nrCtrlOptRecSize_u16);
                        if(E_OK != dataRetVal_u8)
                        {
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_stDspRCState_en = DCM_RC_IDLE;
                        }
                    }
                    if(*dataNegRespCode_u8 == 0)
                    {

                        if(s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrUserRidModeRule_pfct!=NULL_PTR)
                        {

                            dataRetVal_u8 = (*s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrUserRidModeRule_pfct)(dataNegRespCode_u8,dataRId_u16,dataSubFunc_u8);
                        }
                        else
                        {

                            dataRetVal_u8 = DcmAppl_UserRIDModeRuleService(dataNegRespCode_u8,dataRId_u16,dataSubFunc_u8);
                        }

                        if(dataRetVal_u8 !=E_OK)
                        {
                            if(*dataNegRespCode_u8==0x00)
                            {
                                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                            }
                            flgModeRetVal_b = FALSE;
                        }
                        else
                        {
                            *dataNegRespCode_u8=0x00;
                        }
#if(DCM_CFG_DSP_MODERULEFORRCRANGE != DCM_CFG_OFF)
                        if(*dataNegRespCode_u8 == 0x00)
                        {
                            if(( dataSubFunc_u8 == 0x01u ) && (s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStart_pfct != NULL_PTR))
                            {

                                flgModeRetVal_b=(*(s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStart_pfct))(dataNegRespCode_u8);
                            }
                            else if(( dataSubFunc_u8 == 0x02u ) && (s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStop_pfct != NULL_PTR))

                            {
                                flgModeRetVal_b=(*(s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStop_pfct))(dataNegRespCode_u8);
                            }
                            else if(( dataSubFunc_u8 == 0x03u ) && (s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForRequestResult_pfct != NULL_PTR))
                            {
                                flgModeRetVal_b=(*(s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForRequestResult_pfct))(dataNegRespCode_u8);
                            }
                            else
                            {

                            }
                        }
#endif
                        if(flgModeRetVal_b == FALSE)
                        {
                            Dcm_stDspRCState_en = DCM_RC_IDLE;
                        }
                        else
                        {

                            if(flgReqSequenceError_b !=FALSE)
                            {
                                *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
                                Dcm_stDspRCState_en = DCM_RC_IDLE;
                            }
                            else
                            {

#if(DCM_CFG_RCRANGE_ROUTINEVARLENGTH == DCM_CFG_OFF)
                                for( idxLoop_qu16 = 0 ; ( ( idxLoop_qu16 < nrSig_u8 ) && (*dataNegRespCode_u8==0x00)&& (adrSignal_pcst!=NULL_PTR) &&( adrSignal_pcst->dataType_u8 != DCM_VARIABLE_LENGTH ) ) ; idxLoop_qu16++ )
                                {
#if(DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG != DCM_CFG_OFF)
                                    if(adrSignal_pcst->dataType_u8 >= DCM_RCARRAYINDEX)
                                    {
                                        Dcm_RcSetSignalArray(adrSignal_pcst,&(pMsgContext->reqData[3]));
                                    }
                                    else
#endif
                                    {
                                        dataSigVal_u32 = 0;
                                        dataSigVal_u32 = Dcm_GetSignal_u32(adrSignal_pcst->dataType_u8, adrSignal_pcst->posnStart_u16, &(pMsgContext->reqData[3]),adrSignal_pcst->dataEndianness_u8);
                                        Dcm_RCSetSigVal(adrSignal_pcst->dataType_u8,adrSignal_pcst->idxSignal_u16,dataSigVal_u32);
                                    }
                                    adrSignal_pcst++;
                                }

#endif
#if(DCM_CFG_IN_PARAM_MAXLEN > 0u)
                                if(adrSignal_pcst != NULL_PTR)
                                {

                                    if((adrSignal_pcst->dataType_u8 == DCM_VARIABLE_LENGTH) && (Dcm_RCCurrDataLength_u16 != 0x00))
                                    {

                                        DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]),Dcm_RCInPtr_pu8 ,Dcm_RCCurrDataLength_u16);
                                    }
                                }
#endif
                            }
                        }
                    }
                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
        else{

            *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
        }
   }
   else{

        *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
   }
    return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_RcPendingRangeRoutine(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_CONST)  adrSignal_pcst;
#if(DCM_CFG_RCRANGE_ROUTINEVARLENGTH == DCM_CFG_OFF)
   VAR(uint32, AUTOMATIC)                                          dataSigVal_u32;
#endif
   VAR(uint16,AUTOMATIC) idxLoop_qu16;
   VAR(uint8,AUTOMATIC) nrSig_u8;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    adrSignal_pcst = NULL_PTR;
    dataRetVal_u8=DCM_E_PENDING;

   s_IsRCSubfunctionCalled_b = TRUE;
    dataRetVal_u8 = (*Dcm_adrRoutineRangePtr_pcst->adrCallRoutine_pfct)(Dcm_dataRCSubFunc_u8);

   s_IsRCSubfunctionCalled_b = FALSE;

   if((Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE) && (Dcm_adrRoutineRangePtr_pcst->RoutineRangeUsePort_b != FALSE))
   {
        dataRetVal_u8 = DCM_INFRASTRUCTURE_ERROR;
   }
   if(dataRetVal_u8 == E_OK)
   {
        if( Dcm_dataRCSubFunc_u8 == 0x01 )
        {
#if(DCM_CFG_RCRANGE_STARTSUPPORTED != DCM_CFG_OFF)
            adrSignal_pcst = Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->adrStartOutSignalRef_cpcst;
            nrSig_u8 = Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->nrStartOutSignals_u8;
            pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStart_u16;

            Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16] = DCM_ROUTINE_STARTED;
#endif
        }
#if(DCM_CFG_RCRANGE_STOPSUPPORTED != DCM_CFG_OFF)
        else if( Dcm_dataRCSubFunc_u8 == 0x02 )
        {
            adrSignal_pcst = Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->adrStopOutSignalRef_cpcst;
            nrSig_u8 = Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->nrStopOutSignals_u8;
            pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStop_u16;

            Dcm_RoutineRangeStatus_aen[s_dataStatusIdx_u16] = DCM_ROUTINE_STOP;
        }
#endif
        else{
#if(DCM_CFG_RCRANGE_REQRESULTSSUPPORTED != DCM_CFG_OFF)
            adrSignal_pcst = Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->adrReqRsltOutSignalRef_cpcst;
            nrSig_u8 = Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->nrReqRsltOutSignals_u8;
            pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutineRangePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeReqRslt_u16;
#endif
        }
        for( idxLoop_qu16 = 0 ; ( ( idxLoop_qu16 < nrSig_u8 ) && ( adrSignal_pcst->dataType_u8 != DCM_VARIABLE_LENGTH ) ) ; idxLoop_qu16++ )
        {
#if(DCM_CFG_RCRANGE_ROUTINEVARLENGTH == DCM_CFG_OFF)
#if(DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF)
            if(adrSignal_pcst->dataType_u8 >= DCM_RCARRAYINDEX)
            {
                Dcm_RcStoreSignalArray(adrSignal_pcst,&(pMsgContext->resData[3]));
            }
            else
#endif
            {
                dataSigVal_u32 = Dcm_RCGetSigVal_u32 ( adrSignal_pcst->dataType_u8, adrSignal_pcst->idxSignal_u16 );
                Dcm_StoreSignal(adrSignal_pcst->dataType_u8, adrSignal_pcst->posnStart_u16, &(pMsgContext->resData[3]), dataSigVal_u32, adrSignal_pcst->dataEndianness_u8 );
            }
#endif
            adrSignal_pcst++;
        }

        if( idxLoop_qu16 != nrSig_u8 )
        {

            pMsgContext->resDataLen = pMsgContext->resDataLen + Dcm_RCCurrDataLength_u16;
        }

        pMsgContext->resData[0] = Dcm_dataRCSubFunc_u8;

        pMsgContext->resData[1] = ( uint8 )( s_PendingRidRange_u16 >> 8u ) ;
        pMsgContext->resData[2] = ( uint8 )( s_PendingRidRange_u16 & 0x00ffu ) ;

        Dcm_stDspRCState_en = DCM_RC_IDLE;
   }
   else if(dataRetVal_u8 == E_NOT_OK)
   {

        if( Dcm_RCNegResCode_u8 != 0 )
        {
            *dataNegRespCode_u8 = Dcm_RCNegResCode_u8;
        }
        else{

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
   }
   else if(dataRetVal_u8 == DCM_E_PENDING)
   {

        Dcm_RCOpStatus_u8 = DCM_PENDING;

   }
   else if(dataRetVal_u8 == DCM_E_FORCE_RCRRP)
   {

        Dcm_RCOpStatus_u8=DCM_FORCE_RCRRP_OK;
   }
   else if((dataRetVal_u8 == DCM_INFRASTRUCTURE_ERROR) && (Dcm_adrRoutineRangePtr_pcst->RoutineRangeUsePort_b != FALSE))
   {
        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
   }
   else{
        if( Dcm_RCNegResCode_u8 == 0 )
        {

            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
        else{

            *dataNegRespCode_u8 = Dcm_RCNegResCode_u8;
        }
   }
    return dataRetVal_u8;
}
#endif

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tRoutineControl(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(uint16,AUTOMATIC) dataRId_u16;

   VAR(uint16,AUTOMATIC) idxLoop_qu16;
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   VAR(boolean, AUTOMATIC) flgProcessReq_b;
    *dataNegRespCode_u8 = 0;

    flgProcessReq_b =TRUE;

   idxLoop_qu16 = 0xFFFF;
    dataRetVal_u8=DCM_E_PENDING;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dsp_RC_Ini();

        dataRetVal_u8 = E_OK;
   }
   else{
        if( Dcm_stDspRCState_en == DCM_RC_IDLE )
        {

            if( pMsgContext->reqDataLen >= DSP_RC_MINREQLEN )
            {

                dataRId_u16 = (uint16)((uint16)pMsgContext->reqData[1] <<(uint8)8);
                dataRId_u16 = (uint16)(dataRId_u16 | pMsgContext->reqData[2]);

                flgProcessReq_b = Dcm_Lok_RcIsRIDSupported(dataRId_u16,&idxLoop_qu16,dataNegRespCode_u8);

                if((flgProcessReq_b) && (*dataNegRespCode_u8 ==0x00u))
                {

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

                    if(s_IsRidRange_b)
                    {

                        dataRetVal_u8 = Dcm_Lok_RcProcessRangeRoutine(pMsgContext,dataNegRespCode_u8,dataRId_u16);
                    }
                    else
#endif
                    {
#if(DCM_CFG_RC_NUMRIDS > 0u)

                        dataRetVal_u8 = Dcm_Lok_RcProcessRoutine(pMsgContext,dataNegRespCode_u8,dataRId_u16);
#endif
                    }
                }
                else{

                }
            }
            else{

                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        if(Dcm_stDspRCState_en == DCM_RC_PENDING)
        {
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

            if(s_IsRidRange_b)
            {

                dataRetVal_u8 = Dcm_Lok_RcPendingRangeRoutine(pMsgContext, dataNegRespCode_u8);
            }
            else
#endif
            {
#if(DCM_CFG_RC_NUMRIDS > 0u)

                dataRetVal_u8 = Dcm_Lok_RcPendingRoutine(pMsgContext, dataNegRespCode_u8);
#endif
            }
        }

        if(*dataNegRespCode_u8 != 0 )
        {

            Dcm_stDspRCState_en = DCM_RC_IDLE;
            dataRetVal_u8=E_NOT_OK;
        }
   }
    return dataRetVal_u8;
}

#if(DCM_CFG_RC_NUMRIDS > 0u)
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_DcmcallStopRoutine(VAR(uint16,AUTOMATIC) idxLoop_qu16)
{
   VAR(Std_ReturnType, AUTOMATIC) dataRetType_u8;

   s_IsRCSubfunctionCalled_b = TRUE;
    dataRetType_u8=(*s_adrRoutine_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);

   s_IsRCSubfunctionCalled_b = FALSE;

   if(dataRetType_u8 == DCM_E_PENDING)
   {

        Dcm_RoutineStatus_aen[idxLoop_qu16]  = DCM_ROUTINE_STOP_PENDING;
   }
   else{

        Dcm_RoutineStatus_aen[idxLoop_qu16]  = DCM_ROUTINE_STOP;
   }
}
#endif
#endif

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
#if(DCM_CFG_RCRANGE_STOPSUPPORTED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_DcmCallStopRoutineRange(VAR(uint16,AUTOMATIC) idxLoop_qu16)
{
   VAR(Std_ReturnType, AUTOMATIC) dataRetType_u8;

   s_IsRCSubfunctionCalled_b = TRUE;

    dataRetType_u8=(*s_adrRoutineRange_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);

   s_IsRCSubfunctionCalled_b = FALSE;

   if(dataRetType_u8 == DCM_E_PENDING)
   {

        Dcm_RoutineRangeStatus_aen[idxLoop_qu16]  = DCM_ROUTINE_STOP_PENDING;
   }
   else{

        Dcm_RoutineRangeStatus_aen[idxLoop_qu16]  = DCM_ROUTINE_STOP;
   }
}
#endif
#endif

FUNC(void,DCM_CODE) Dcm_RoutineSetSesCtrlType (VAR(Dcm_SesCtrlType, AUTOMATIC) dataSesCtrlType_u8)
{

   VAR (uint16,AUTOMATIC) idxLoop_qu16;

#if(DCM_CFG_RC_NUMRIDS > 0u)
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)

   s_adrRoutine_pcst =  &Dcm_DspRoutine_cast[0];

   for( idxLoop_qu16 = 0 ; idxLoop_qu16 < DCM_CFG_RC_NUMRIDS ; idxLoop_qu16++ )
   {

        if( (s_adrRoutine_pcst->flgStopRoutine_b!= FALSE)&&(s_adrRoutine_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineStatus_aen[idxLoop_qu16] == DCM_ROUTINE_STARTED))
        {
            if(dataSesCtrlType_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
            {
                Dcm_DcmcallStopRoutine(idxLoop_qu16);
            }
            else{

                if(( (Dcm_DsldGetActiveSessionMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSessBitMask_u32 )) == 0u )|| ( ( Dcm_DsldGetActiveSecurityMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSecBitMask_u32 )) == 0u ) )
                {

                    Dcm_DcmcallStopRoutine(idxLoop_qu16);
                }
            }
        }

        s_adrRoutine_pcst++;
   }
#endif
#endif

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
#if(DCM_CFG_RCRANGE_STOPSUPPORTED != DCM_CFG_OFF)

   s_adrRoutineRange_pcst = &Dcm_DspRoutineRange_cast[0];

   for(idxLoop_qu16 = 0; idxLoop_qu16 < DCM_CFG_RC_RANGE_NUMRIDS; idxLoop_qu16++)
   {

        if((s_adrRoutineRange_pcst->flgStopRoutine_b!= FALSE)&&(s_adrRoutineRange_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineRangeStatus_aen[idxLoop_qu16] == DCM_ROUTINE_STARTED))
        {
            if(dataSesCtrlType_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
            {
                Dcm_DcmCallStopRoutineRange(idxLoop_qu16);
            }
            else{

                if(((Dcm_DsldGetActiveSessionMask_u32() & (s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataSessBitMask_u32)) == 0u)|| ((Dcm_DsldGetActiveSecurityMask_u32() & (s_adrRoutineRange_pcst->adrRoutineInfoRef_cpcst->dataSecBitMask_u32)) == 0u))
                {

                    Dcm_DcmCallStopRoutineRange(idxLoop_qu16);
                }
            }
        }

        s_adrRoutineRange_pcst++;
   }
#endif
#endif
}

static FUNC(void,DCM_CODE) Dcm_SetFlagforRC(VAR (boolean,AUTOMATIC) isFlag_b)
 {

   s_IsRCSubfunctionCalled_b = isFlag_b;
}

 FUNC(void, DCM_CODE) Dcm_Lok_DspRCConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
     if(dataIdContext_u8 == DCM_DSP_SID_ROUTINECONTROL)
     {
         Dcm_SetFlagforRC(TRUE);
     }
     DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,status_u8);
     if(dataIdContext_u8 == DCM_DSP_SID_ROUTINECONTROL)
     {
         Dcm_SetFlagforRC(FALSE);
     }
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataRid_u16)
{
   VAR(Std_ReturnType, AUTOMATIC) RetVal;

   if((s_IsRCSubfunctionCalled_b != FALSE) && (dataRid_u16!= NULL_PTR))
   {
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
        if(s_IsRidRange_b)
        {

            if(Dcm_stDspRCState_en == DCM_RC_PENDING)
            {
                *dataRid_u16 = s_PendingRidRange_u16;
            }
            else{
                *dataRid_u16 = s_dataRidRange_u16;
            }
        }
        else
#endif
        {
#if(DCM_CFG_RC_NUMRIDS > 0u)
            if(Dcm_stDspRCState_en == DCM_RC_PENDING)
            {
                *dataRid_u16 = Dcm_adrRoutinePtr_pcst->dataRId_u16;
            }
            else{
                *dataRid_u16 = s_adrRoutine_pcst->dataRId_u16 ;
            }
#endif
        }
        RetVal = E_OK;
   }
   else{
        RetVal = E_NOT_OK;
   }
    return RetVal;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
