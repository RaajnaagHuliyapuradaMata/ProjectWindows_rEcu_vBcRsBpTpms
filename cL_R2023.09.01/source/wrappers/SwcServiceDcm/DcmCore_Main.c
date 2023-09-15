#include "Std_Types.hpp"

#include "infSwcServiceDcmSwcServiceSchM.hpp"

#include "DcmCore_Main_Inf.hpp"
#include  "DcmDspUds_Seca_Prv.hpp"
#include "DcmDspUds_Roe_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Dcm_Dsld_connType * Dcm_DsldConnTable_pcst;
const Dcm_Dsld_protocol_tableType * Dcm_DsldProtocol_pcst;
const uint8 * Dcm_DsldRxTable_pcu8;
const uint8 * Dcm_DsldSessionTable_pcu8;
Dcm_MsgContextType Dcm_DsldMsgContext_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_DsldInternalStructureType_tst Dcm_DsldGlobal_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_Dsp_SecaGlobaltimer_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

uint8 Dcm_CurProtocol_u8;
Dcm_SesCtrlType Dcm_CC_ActiveSession_u8;

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
static uint8 s_VinWaitPendingCounter_u8 ;
static Std_ReturnType s_VinBufferInitStatus_u8 = E_OK;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_Dsld_activediagnostic_ten Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_ReadyForBoot_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_isInitialised_b;
boolean Dcm_acceptRequests_b;
boolean Dcm_isCancelTransmitInvoked_b;
boolean Dcm_isStopProtocolInvoked_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
void Dcm_Lok_DSL_Mainfunction(void);

static void Dcm_Lok_Statemachine_Init(void){
   Dcm_Lok_DSL_Mainfunction();
   Dcm_Lok_DsdStateMachine();
}

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
static void Dcm_Lok_MainVINinit (void){
   if(Dcm_VinReceived_b != TRUE){
      if((s_VinBufferInitStatus_u8 == E_OK) || ((s_VinBufferInitStatus_u8 == DCM_E_PENDING) && (s_VinWaitPendingCounter_u8 < DCM_CFG_WAIT_FOR_VIN))){
                  s_VinBufferInitStatus_u8 = Dcm_VinBuffer_Init();
         if(s_VinBufferInitStatus_u8 == DCM_E_PENDING){
                      s_VinWaitPendingCounter_u8++;
                  }
         if(Dcm_VinReceived_b == TRUE){
                      s_VinWaitPendingCounter_u8 = 0x00;
                  }
              }
          }
}
#endif

static void Dcm_Lok_UdsMainFunction(void){
#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
   Dcm_Lok_Cdtcs_Mainfunction();
#endif

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )
   Dcm_Lok_CC_Mainfunction();
#endif
}

void Dcm_Lok_DSL_Mainfunction(void){
   if(Dcm_Lok_GetDsdState() == DSD_SENDTXCONF_APPL){
      Dcm_Lok_DsdSendTxConfirmation();
   }
   Dcm_Lok_ProcessResetToDefaultSession();
   Dcm_Lok_DslStateMachine();
}

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_Main_Warmstart(void){
   Std_ReturnType stGetPermTxWarmResp_u8;
   if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE){
      if(Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE){
         Dcm_DslDsdWarmStart();
         Dcm_ReadyForBoot_b = FALSE;
      }
      else{
         if(
            DCM_CHKFULLCOMM_MODE(
               Dcm_DsldConnTable_pcst[Dcm_GetActiveConnectionIdx_u8()].channel_idx_u8
            )
         ){
            stGetPermTxWarmResp_u8 = DcmAppl_DcmGetPermTxWarmResp();
            switch(stGetPermTxWarmResp_u8){
               case E_OK:{
                     Dcm_DslDsdWarmStart();
                     Dcm_ReadyForBoot_b = FALSE;
                  }
                  break;

               case DCM_E_PENDING:
                  break;

               default:{
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

void infSwcServiceDcmSwcServiceSchM_vMainFunction(void){
   if(Dcm_acceptRequests_b != FALSE){
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
      if(Dcm_Dsp_SecaGlobaltimer_u32 < 0xFFFFFFFFu){
         Dcm_Dsp_SecaGlobaltimer_u32++;
      }
#endif

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
      if(Dcm_ReadyForBoot_b != FALSE){
         Dcm_Lok_Main_Warmstart();
      }
      if(Dcm_ReadyForBoot_b == FALSE){
         Dcm_isInitialised_b = TRUE;
      }
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

