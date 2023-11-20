

#ifndef DCMDSPUDS_ROE_INF_H
#define DCMDSPUDS_ROE_INF_H

#include "Dcm.hpp"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "Rte_Dcm.hpp"
#endif
#endif
#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) )

#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmDspUds_Uds_Prot.hpp"
#include "Dcm_Dsl_Priv.hpp"
#include "DcmAppl.hpp"
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

#define DCM_RoeTimerStart(timer,time)      ((timer) = (time));
#define DCM_RoeTimerProcess(timer)          do   \
                                            {   \
                                            if( ((timer)!=0u) && ((timer)!=0xFFFFFFFFuL) ) \
                                            { \
                                                (timer)--; \
                                            }\
                                            }\
                                            while(0);
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(boolean,DCM_CODE) Dcm_ChkIfDidServiceIsActive(VAR(uint8, AUTOMATIC) TesterReqSid_u8, VAR(uint8, AUTOMATIC) RoeType2Sid_u8);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
typedef struct{
   uint8 dataEventSID_u8;
   Type_SwcServiceCom_tIdPdu dataRoeRxPduId_u8;
    Dcm_MsgLenType dataEventRespLen_u32;
    Dcm_ConfirmationStatusType stEventConfStatus_u8;
}Dcm_DsldRoeQueueType_tst;

typedef enum{
    DCM_ROE_QUEUE_INIT
   ,   DCM_ROE_QUEUE_WAITFORCONFIRMATION
}Dcm_DsldstRoeQueueState_ten;

typedef struct{
   boolean flgTxQueueActive_b;
   uint8   idxTxResponse_u8;
   uint8   idxTxQueue_u8 ;
    Dcm_DsldstRoeQueueState_ten  stRoeQueueState_st;
   uint32  dataInterMsgTimer_u32;
}Dcm_DsldRoeIntenalType_tst;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DsldRoeIntenalType_tst,DCM_VAR) Dcm_DsldRoeScheduler_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeEventConfirmation(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) dataConfirmResult_u8);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeEventProcess(void);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeProcessConfirm(VAR(Std_ReturnType,AUTOMATIC) dataResult_u8);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeQueueResponse(void);
extern FUNC(void,DCM_CODE) Dcm_DslDsd_ResetROEScheduler(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Roe2ResponseType_en;
extern VAR(Type_SwcServiceCom_stInfoPdu,DCM_VAR) Dcm_DsldRoe2PduInfo_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint8,DCM_VAR) Dcm_DsldSrvIndex_u8;
extern VAR(Std_ReturnType,DCM_VAR) Dcm_Roe2TxResult_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2CONST(Dcm_ProtocolExtendedInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoe2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
extern VAR( uint32, DCM_VAR)     Dcm_Roe2StartTick_u32;
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2CONST(Dcm_ProtocolExtendedInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoe_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_CODE) Dcm_DsldRoe2StateMachine(void);
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Lok_RoeMainFunction (void){
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
        if(Dcm_DsdRoe2State_en != DSD_IDLE)
        {

            Dcm_DsldRoe2StateMachine();
        }
        else{
            Dcm_DsldProcessRoeQueue();
        }
#else
        if(Dcm_Lok_GetDslState() == DSL_STATE_IDLE)
        {
            if(Dcm_Lok_GetDsdState() == DSD_IDLE)
            {
                Dcm_DsldProcessRoeQueue();
            }
        }
#endif
}
#endif

#endif
