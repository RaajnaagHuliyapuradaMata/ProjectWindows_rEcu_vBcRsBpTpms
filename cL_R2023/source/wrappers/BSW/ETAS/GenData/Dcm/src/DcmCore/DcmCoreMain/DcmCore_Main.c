
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_Main_Inf.h"
#include  "DcmDspUds_Seca_Prv.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

const Dcm_Dsld_connType * Dcm_DsldConnTable_pcst;
const Dcm_Dsld_protocol_tableType * Dcm_DsldProtocol_pcst;
const uint8 * Dcm_DsldRxTable_pcu8;
const uint8 * Dcm_DsldSessionTable_pcu8;
Dcm_MsgContextType Dcm_DsldMsgContext_st;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
Dcm_MsgContextType Dcm_OBDMsgContext_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
const Dcm_ConfigType * Dcm_ActiveConfigSet_Ptr;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
Dcm_DsldInternalStructureType_tst Dcm_DsldGlobal_st;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
Dcm_OBDInternalStructureType_tst Dcm_OBDGlobal_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#if (DCM_CFG_OSTIMER_USE != FALSE)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
uint32 Dcm_P2OrS3StartTick_u32;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
uint32 Dcm_OBDP2OrS3StartTick_u32;
#endif
uint32 Dcm_CurrTick_u32;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
uint32 Dcm_PagedBufferStartTick_u32;
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
uint32 Dcm_TimerStartTick_u32;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#if ((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
uint32 Dcm_SysPrevTick_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
uint32 Dcm_SysCurrTick_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#endif

#endif

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
uint32 Dcm_Dsp_SecaGlobaltimer_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
uint8 Dcm_ActiveConfiguration_u8;
#endif

uint8 Dcm_CurProtocol_u8;
Dcm_SesCtrlType Dcm_CC_ActiveSession_u8;

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
static uint8 s_VinWaitPendingCounter_u8 ;
static Std_ReturnType s_VinBufferInitStatus_u8 = E_OK;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
Dcm_Dsld_activediagnostic_ten Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
boolean Dcm_ReadyForBoot_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
boolean Dcm_ObdSendTxConfirmation_b;
#endif
boolean Dcm_isInitialised_b;
boolean Dcm_acceptRequests_b;
boolean Dcm_isCancelTransmitInvoked_b;
boolean Dcm_isStopProtocolInvoked_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_Lok_DSL_Mainfunction(void);

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_OBDMainFunction(void)
{

    if(Dcm_ObdSendTxConfirmation_b == TRUE)
    {
       Dcm_Lok_ConfirmationToOBDApl();
       Dcm_ObdSendTxConfirmation_b = FALSE;
    }

    Dcm_Lok_OBDTimerProcessing();
    // State Machine for OBD request processing
    Dcm_Lok_OBDStateMachine();
}
#endif

static void Dcm_Lok_Statemachine_Init (void)
{
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_OBDMainFunction();
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    if(Dcm_Lok_GetDslPreemptionState()   != DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING)
#endif
    {
        Dcm_Lok_DSL_Mainfunction();
        Dcm_Lok_DsdStateMachine();
    }
}

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
static void Dcm_Lok_MainVINinit (void)
{

          if(Dcm_VinReceived_b != TRUE)
          {

              if((s_VinBufferInitStatus_u8 == E_OK) || ((s_VinBufferInitStatus_u8 == DCM_E_PENDING) && (s_VinWaitPendingCounter_u8 < DCM_CFG_WAIT_FOR_VIN)))
              {
                  s_VinBufferInitStatus_u8 = Dcm_VinBuffer_Init();

                  if(s_VinBufferInitStatus_u8 == DCM_E_PENDING)
                  {
                      s_VinWaitPendingCounter_u8++;
                  }
                  if(Dcm_VinReceived_b == TRUE)
                  {

                      s_VinWaitPendingCounter_u8 = 0x00;
                  }
              }
          }
}
#endif

static void Dcm_Lok_UdsMainFunction(void)
{
#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)

    Dcm_Lok_Cdtcs_Mainfunction();
#endif

#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )

    Dcm_Lok_CC_Mainfunction();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

    Dcm_Lok_RoeMainFunction();
#endif
}

void Dcm_Lok_DSL_Mainfunction(void)
{

    if(Dcm_Lok_GetDsdState() == DSD_SENDTXCONF_APPL )
    {

        Dcm_Lok_DsdSendTxConfirmation();
    }

    Dcm_Lok_ProcessResetToDefaultSession();

#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
    Dcm_RdpiMainFunction();
#endif

    Dcm_Lok_DslStateMachine();
}

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_Main_Warmstart(void)
{

    Std_ReturnType stGetPermTxWarmResp_u8;

    if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
    {

       if(Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
       {

           Dcm_DslDsdWarmStart();

           Dcm_ReadyForBoot_b = FALSE;
       }

       else
       {
           if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_GetActiveConnectionIdx_u8()].channel_idx_u8))
           {

               stGetPermTxWarmResp_u8 = DcmAppl_DcmGetPermTxWarmResp();

               switch(stGetPermTxWarmResp_u8)
               {

                   case E_OK :
                   {
                     Dcm_DslDsdWarmStart();
                     \
                     Dcm_ReadyForBoot_b = FALSE;
                   }
                     break;

                   case DCM_E_PENDING:
                     break;

                   default :
                   {

                     Dcm_ProgConditions_st.StoreType = DCM_NOTVALID_TYPE;

                     Dcm_ReadyForBoot_b = FALSE;
                   }
                    break;
               }

           }
       }
    }
    else
    {

     Dcm_ReadyForBoot_b = FALSE;
    }
}
#endif

void Dcm_MainFunction(void)
{

    if(Dcm_acceptRequests_b != FALSE)
    {

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
        if(Dcm_Dsp_SecaGlobaltimer_u32 < 0xFFFFFFFFu)
        {

        Dcm_Dsp_SecaGlobaltimer_u32++;
        }

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if(Dcm_GetattemptCounterWaitCycle_u8 <= DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)
        {

        Dcm_Dsp_RestoreDelayCount();
        }
#endif

#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
        if(Dcm_ReadyForBoot_b != FALSE)
        {
         Dcm_Lok_Main_Warmstart();
        }

        if(Dcm_ReadyForBoot_b == FALSE)
        {

        Dcm_isInitialised_b = TRUE;
        }
#else

        Dcm_isInitialised_b = TRUE;
#endif
        Dcm_Lok_Statemachine_Init();

        Dcm_Lok_UdsMainFunction();

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
        Dcm_Lok_MainVINinit ();
#endif
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

