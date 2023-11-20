#include "Std_Types.hpp"

#include "DcmCore_Main_Inf.hpp"
#include  "DcmDspUds_Seca_Prv.hpp"
#include "DcmDspUds_Roe_Inf.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

P2CONST(Dcm_Dsld_connType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldConnTable_pcst;
P2CONST(Dcm_Dsld_protocol_tableType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldProtocol_pcst;
P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldRxTable_pcu8;
P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSessionTable_pcu8;
VAR(Dcm_MsgContextType,DCM_VAR) Dcm_DsldMsgContext_st;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
P2CONST(Type_CfgSwcServiceDcm_st, DCM_VAR, DCM_INTERN_CONST) Dcm_ActiveConfigSet_Ptr;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_DsldInternalStructureType_tst,DCM_VAR) Dcm_DsldGlobal_st;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_OSTIMER_USE != FALSE)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR( uint32, DCM_VAR)     Dcm_P2OrS3StartTick_u32;
VAR( uint32, DCM_VAR)     Dcm_CurrTick_u32;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
VAR( uint32, DCM_VAR)     Dcm_PagedBufferStartTick_u32;
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
VAR( uint32, DCM_VAR)     Dcm_TimerStartTick_u32;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR( uint32, DCM_VAR) Dcm_SysPrevTick_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR( uint32, DCM_VAR) Dcm_SysCurrTick_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint32, DCM_VAR) Dcm_Dsp_SecaGlobaltimer_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
VAR(uint8, DCM_VAR) Dcm_ActiveConfiguration_u8;
#endif

VAR(uint8,DCM_VAR) Dcm_CurProtocol_u8;
VAR(Dcm_SesCtrlType,DCM_VAR) Dcm_CC_ActiveSession_u8;

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
static VAR(uint8,DCM_VAR) s_VinWaitPendingCounter_u8 ;
static VAR(Std_ReturnType, AUTOMATIC) s_VinBufferInitStatus_u8 = E_OK;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_Dsld_activediagnostic_ten, DCM_VAR) Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR(boolean,DCM_VAR) Dcm_ReadyForBoot_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR(boolean,DCM_VAR) Dcm_isInitialised_b;
VAR(boolean,DCM_VAR) Dcm_acceptRequests_b;
VAR(boolean,DCM_VAR) Dcm_isCancelTransmitInvoked_b;
VAR(boolean,DCM_VAR) Dcm_isStopProtocolInvoked_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Lok_DSL_Mainfunction(void);

static FUNC(void,DCM_CODE) Dcm_Lok_Statemachine_Init (void){
    Dcm_Lok_DSL_Mainfunction();
    Dcm_Lok_DsdStateMachine();
}

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_MainVINinit (void){

          if(Dcm_VinReceived_b != TRUE)
          {

              if((s_VinBufferInitStatus_u8 == E_OK) || ((s_VinBufferInitStatus_u8 == DCM_E_PENDING) && ( s_VinWaitPendingCounter_u8 < DCM_CFG_MAX_WAITPEND)))
              {
                  s_VinBufferInitStatus_u8 = Dcm_VinBuffer_Init();

                  if(s_VinBufferInitStatus_u8 == DCM_E_PENDING)
                  {
                      s_VinWaitPendingCounter_u8++;
                  }
              }
          }
}
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_UdsMainFunction(void){
#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)

            Dcm_CDTCModeStatusCheck();
#endif

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )

              Dcm_Lok_CC_Mainfunction();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

              Dcm_Lok_RoeMainFunction();
#endif
}

FUNC(void,DCM_CODE) Dcm_Lok_DSL_Mainfunction(void){

        Dcm_Lok_ProcessResetToDefaultSession();

       if(Dcm_Lok_GetDsdState() == DSD_SENDTXCONF_APPL )
       {

           Dcm_Lok_DsdSendTxConfirmation();
       }
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
       Dcm_RdpiMainFunction();
#endif

       Dcm_Lok_DslStateMachine();
}

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_Main_Warmstart(void){

   VAR(Std_ReturnType, AUTOMATIC) stGetPermTxWarmResp_u8;

   if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
   {

       if(Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
       {

           Dcm_DslDsdWarmStart();

           Dcm_ReadyForBoot_b = FALSE;
       }

       else{
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
   else{

     Dcm_ReadyForBoot_b = FALSE;
   }
}
#endif

FUNC(void,DCM_CODE) infSwcServiceDcmSwcServiceSchM_vMainFunction(void){

   if(Dcm_acceptRequests_b != FALSE)
   {

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
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

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
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
#include "Dcm_Cfg_MemMap.hpp"

