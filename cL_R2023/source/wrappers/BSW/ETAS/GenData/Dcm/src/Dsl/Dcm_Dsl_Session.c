

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
static boolean Dcm_isResetToDefaultRequested_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE void Dcm_Lok_ResetRoeEvents(void)
{
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
    Dcm_ResetRoeDidevents();
#endif

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
    Dcm_ResetRoeOnDtcevents();
#endif
}
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static boolean Dcm_Lok_SetNonDefaultSesCtrlType (Dcm_SesCtrlType SesCtrlType_u8)
{
    boolean isSessionAvailable = FALSE;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
    uint32 sessionMask_u32 = 0u;
#endif

    uint8 nrSessions_u8 = 0u;
    uint8 idxIndex_u8   = 0u;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
    {
        nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
    }
    else
    {
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
    else
    {
        DCM_DET_ERROR(DCM_SETSESSIONLEVEL , DCM_E_SESSION_NOT_CONFIGURED)
    }

    return isSessionAvailable;
}

static void Dcm_Lok_SetDefaultSesCtrlType (Dcm_SesCtrlType CurrentSession_u8,
        Dcm_SesCtrlType SesCtrlType_u8)
{
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    uint8 idxKwpTiming_u8 = 0u;
#endif

    SchM_Enter_Dcm_DsldTimer_NoNest();
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
    {

        Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
    }
    else
    {

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
#if (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
        Dcm_DsldResetRDPI();
#endif

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_ResetRoeEvents();
#endif
    }
}

void Dcm_Lok_SetSesCtrlType (Dcm_SesCtrlType SesCtrlType_u8)
{
    Dcm_SesCtrlType currentSession_u8 = 0u;

    if(FALSE != Dcm_isSessionStored_b)
    {
        currentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.PreviousSessionIndex];
        Dcm_isSessionStored_b = FALSE;
    }
    else
    {
        currentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];
    }

    if(SesCtrlType_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
    {
        Dcm_Lok_SetDefaultSesCtrlType(currentSession_u8,SesCtrlType_u8);
    }
    else
    {
        if(FALSE == Dcm_Lok_SetNonDefaultSesCtrlType(SesCtrlType_u8))
        {

            SesCtrlType_u8 = currentSession_u8;
        }
    }

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
    Dcm_Dsp_SecaSessIni();
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF))
    Dcm_ControlDtcSettingExit();
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
        ((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!=DCM_CFG_OFF)))
    Dcm_DspDeactivateRequestUploadDownloadPermission();
#endif

    (void)Dcm_SesCtrlChangeIndication(currentSession_u8, SesCtrlType_u8);
}

Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType * SesCtrlType)
{
    if(SesCtrlType != NULL_PTR)
    {

        if(FALSE != Dcm_isSessionStored_b)
        {
            *SesCtrlType = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.PreviousSessionIndex];
        }
        else
        {
            *SesCtrlType = Dcm_DsldSessionTable_pcu8[ Dcm_DsldGlobal_st.idxActiveSession_u8];
        }
    }
    else
    {

        DCM_DET_ERROR(DCM_SETSESSION_ID, DCM_E_PARAM_POINTER);
    }

    return(E_OK);
}

Std_ReturnType Dcm_ResetToDefaultSession(void)
{

   Dcm_isResetToDefaultRequested_b = TRUE;
   return (E_OK);
}

void Dcm_Lok_ProcessResetToDefaultSession(void)
{
    if(FALSE != Dcm_isResetToDefaultRequested_b)
    {
        uint8 dslState;
        Dcm_DsdStatesType_ten dsdState;
        SchM_Enter_Dcm_Global_NoNest();
        dslState=Dcm_Lok_GetDslState();
        dsdState=Dcm_Lok_GetDsdState();
        SchM_Exit_Dcm_Global_NoNest();
        if((dslState==DSL_STATE_IDLE)&&(dsdState == DSD_IDLE))
        {
            ComM_DCM_InactiveDiagnostic (Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
            Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif

            (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif
#endif
            Dcm_isResetToDefaultRequested_b = FALSE;
        }
    }
}

void Dcm_Lok_ResetDefaultSessionRequestFlag(void)
{
   Dcm_isResetToDefaultRequested_b = FALSE;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
