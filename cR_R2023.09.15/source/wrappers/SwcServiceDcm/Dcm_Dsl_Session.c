#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean,DCM_VAR) Dcm_isResetToDefaultRequested_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Lok_ResetRoeEvents(void){
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
    Dcm_ResetRoeDidevents();
#endif

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
    Dcm_ResetRoeOnDtcevents();
#endif
}
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(boolean,DCM_CODE) Dcm_Lok_SetNonDefaultSesCtrlType (VAR(Dcm_SesCtrlType,AUTOMATIC) CurrentSession_u8
   ,     VAR(Dcm_SesCtrlType, AUTOMATIC) SesCtrlType_u8)
{
   VAR(boolean,AUTOMATIC) isSessionAvailable = FALSE;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
   VAR(uint32,AUTOMATIC) sessionMask_u32 = 0u;
#endif

   VAR(uint8,AUTOMATIC) nrSessions_u8 = 0u;
   VAR(uint8,AUTOMATIC) idxIndex_u8   = 0u;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
   if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
   {
        nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
   }
   else{
        nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
   }
#else
    nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
#endif

   for(idxIndex_u8 = 0x1; idxIndex_u8 < nrSessions_u8 ; idxIndex_u8++)
   {
        if(Dcm_DsldSessionTable_pcu8[idxIndex_u8]== SesCtrlType_u8)
        {

            break;
        }
   }

   if(idxIndex_u8 != nrSessions_u8)
   {
        isSessionAvailable = TRUE;

        Dcm_DsldGlobal_st.idxActiveSession_u8 = idxIndex_u8;

        if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
        {

            Dcm_DsldGlobal_st.idxActiveSecurity_u8 = 0x00u;
        }

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
        Dcm_RoutineSetSesCtrlType(SesCtrlType_u8);
#endif

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_ResetRoeEvents();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
        sessionMask_u32 = Dcm_DsldGetActiveSessionMask_u32();

        Dcm_ResetActiveIoCtrl(sessionMask_u32,0x1u,TRUE);
#endif
   }
   else{
        DCM_DET_ERROR(DCM_SETSESSIONLEVEL , DCM_E_SESSION_NOT_CONFIGURED)
   }

    return isSessionAvailable;
}

static FUNC(void,DCM_CODE) Dcm_Lok_SetDefaultSesCtrlType (VAR(Dcm_SesCtrlType,AUTOMATIC) CurrentSession_u8
   ,     VAR(Dcm_SesCtrlType, AUTOMATIC) SesCtrlType_u8)
{
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
   VAR(uint8,AUTOMATIC) idxKwpTiming_u8 = 0u;
#endif

    SchM_Enter_Dcm_DsldTimer_NoNest();
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
   if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
   {

        Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
   }
   else{

        idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;
        Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;
        Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P3_max_u32;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;
   }
#else

    Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
#endif
    SchM_Exit_Dcm_DsldTimer_NoNest();

    Dcm_DsldGlobal_st.idxActiveSecurity_u8 = 0x00u;

    Dcm_DsldGlobal_st.idxActiveSession_u8 = 0x00u;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))

    Dcm_ResetActiveIoCtrl(0x1,0x1,TRUE);
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
    Dcm_RoutineSetSesCtrlType(SesCtrlType_u8);
#endif

   if(CurrentSession_u8 != Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
   {
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
        Dcm_DsldResetRDPI();
#endif

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_ResetRoeEvents();
#endif
   }
}

FUNC(void,DCM_CODE) Dcm_Lok_SetSesCtrlType (VAR(Dcm_SesCtrlType, AUTOMATIC) SesCtrlType_u8)
{
   VAR(Dcm_SesCtrlType,AUTOMATIC) currentSession_u8 = 0u;
   if(FALSE != Dcm_isSessionStored_b)
   {
        currentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.PreviousSessionIndex];
        Dcm_isSessionStored_b = FALSE;
   }
   else{
        currentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];
   }
   if(SesCtrlType_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
   {
        Dcm_Lok_SetDefaultSesCtrlType(currentSession_u8,SesCtrlType_u8);
   }
   else{
        if(FALSE == Dcm_Lok_SetNonDefaultSesCtrlType(currentSession_u8,SesCtrlType_u8))
        {
            SesCtrlType_u8 = currentSession_u8;
        }
   }

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
    Dcm_Dsp_SecaSessIni();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF))
    Dcm_ControlDtcSettingExit();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
        ((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!=DCM_CFG_OFF)))
    Dcm_DspDeactivateRequestUploadDownloadPermission();
#endif

    (void)Dcm_SesCtrlChangeIndication(currentSession_u8, SesCtrlType_u8);
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA)  SesCtrlType){
   if(SesCtrlType != NULL_PTR){
        if(FALSE != Dcm_isSessionStored_b){
            *SesCtrlType = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.PreviousSessionIndex];
        }
        else{
            *SesCtrlType = Dcm_DsldSessionTable_pcu8[ Dcm_DsldGlobal_st.idxActiveSession_u8];
        }
   }
   else{

        DCM_DET_ERROR(DCM_SETSESSION_ID, DCM_E_PARAM_POINTER);
   }
    return(E_OK);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_ResetToDefaultSession(void){
   Dcm_isResetToDefaultRequested_b = TRUE;
   return (E_OK);
}

FUNC(void, DCM_CODE) Dcm_Lok_ProcessResetToDefaultSession(void){
   if(FALSE != Dcm_isResetToDefaultRequested_b){
      Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
      (void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
#endif
#endif
      Dcm_isResetToDefaultRequested_b = FALSE;
   }
}

FUNC(void, DCM_CODE) Dcm_Lok_ResetDefaultSessionRequestFlag(void){
   Dcm_isResetToDefaultRequested_b = FALSE;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
