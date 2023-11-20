#ifndef DCMCORE_DSLDSD_PROT_H
#define DCMCORE_DSLDSD_PROT_H

#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif

#include "Dcm_Dsd.hpp"

#define DCM_ENDIANNESSCONVERSION16(data) ((data) = rba_BswSrv_ByteOrderSwap16((uint16)(data)))

#define DCM_ENDIANNESSCONVERSION32(data) ((data) = rba_BswSrv_ByteOrderSwap32(data))

#define DCM_MEMCOPY(xDest_pv,xSrc_pcv,numBytes_u32)         (void)LibAutosar_vptrMemCopy((xDest_pv),(xSrc_pcv),(uint32)(numBytes_u32))
#define DCM_MEMSET(xDest_pv,xPattern_u32,numBytes_u32)              (void)rba_BswSrv_MemSet((xDest_pv),(xPattern_u32),(uint32)(numBytes_u32))
#define DCM_UNUSED_PARAM(P)   ((void)(P))

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

#define DCM_NOTVALID_TYPE     0x00u
#define DCM_WARMREQUEST_TYPE  0x01u
#define DCM_WARMINIT_TYPE     0x02u
#define DCM_WARMRESPONSE_TYPE 0x03u
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_ProgConditionsType, DCM_VAR) Dcm_ProgConditions_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
typedef enum{
    DCM_BOOT_IDLE = 0
   ,   DCM_BOOT_PROCESS_RESET
   ,   DCM_BOOT_SENDFORCEDRESPPEND
   ,   DCM_BOOT_WAIT
   ,   DCM_BOOT_STORE_WARMREQ
   ,   DCM_BOOT_STORE_WARMINIT
   ,   DCM_BOOT_STORE_WARMRESP
   ,   DCM_BOOT_ERROR
   ,   DCM_BOOT_WAIT_FOR_RESET
   ,   DCM_BOOT_PERFORM_RESET
   ,   DCM_BOOT_PREPARE_RESET
}Dcm_BootLoaderStates_ten;

#define DCM_JUMPTOOEMBOOTLOADER            0x00u
#define DCM_JUMPTOSYSSUPPLIERBOOTLOADER 0x01u
#define DCM_JUMPDRIVETODRIVE            0x02u
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_BootLoaderStates_ten, DCM_VAR) Dcm_BootLoaderState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void, DCM_CODE) Dcm_JumpToBootLoader(
       VAR(uint8,     AUTOMATIC                 ) dataBootType_u8
   , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8
);
extern FUNC(void, DCM_CODE) Dcm_ResetBootLoader(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_OBDMODE01_ID    0x81u
#define DCM_OBDMODE02_ID    0x82u
#define DCM_OBDMODE37A_ID   0x83u
#define DCM_OBDMODE04_ID    0x84u
#define DCM_OBDMODE06_ID    0x86u
#define DCM_OBDMODE08_ID    0x88u
#define DCM_OBDMODE09_ID    0x89u

#define DCM_RDBI_ID         0x8Au

#define DCM_WARMSTART_ID        0x8Bu
#define DCM_BOOTLOADER_ID       0x8Cu
#define DCM_COPYRXDATA_ID       0x8Du
#define DCM_KWPTIMING_ID        0x8Eu
#define DCM_PAGEDBUFFER_ID      0x8Fu
#define DCM_RDPI_ID             0x90u
#define DCM_ROE_ID              0x91u
#define DCM_ROEPROCESS_ID       0x92u
#define DCM_TPRXIND_ID          0x93u
#define DCM_SETSRVTABLE_ID      0x94u
#define DCM_SETSESSION_ID       0x95u
#define DCM_PROCESSINGDONE_ID   0x96u
#define DCM_CC_ID               0x97u
#define DCM_CDTCS_ID            0x98u
#define DCM_DDDI_ID             0x99u
#define DCM_DSC_ID              0x9Au
#define DCM_GETP2TIMINGS_ID     0x9Bu
#define DCM_ER_ID               0x9Cu
#define DCM_IOCBI_ID            0x9Du
#define DCM_WDBI_ID             0x9Eu
#define DCM_COPYTXDATA_ID       0x9Fu
#define DCM_CHKUSEDCOREMAIN_ID  0xA0u
#define DCM_TRANSFERDATA_ID     0xA1u
#define DCM_TRANSFEREXIT_ID     0xA2u
#define DCM_STARTOFRECEPTION_ID 0xA3u
#define DCM_TPTXCONFIRMATION_ID 0xA4u
#define DCM_TPRXINDICATION_ID   0xA5u
#define DCM_SETSECURITYLEVEL    0xA6u
#define DCM_SETSESSIONLEVEL     0xA7u
#define DCM_RDTC_ID             0xA8u
#define DCM_TXCONFIRMATION_ID   0xAAu

#define DCM_E_INTERFACE_TIMEOUT                   0x01u
#define DCM_E_INTERFACE_RETURN_VALUE              0x02u
#define DCM_E_INTERFACE_BUFFER_OVERFLOW           0x03u
#define DCM_E_UNINIT                              0x05u
#define DCM_E_PARAM                               0x06u
#define DCM_E_PARAM_POINTER                       0x07u
#define DCM_E_INIT_FAILED                         0x08u
#define DCM_E_SET_PROG_CONDITIONS_FAIL            0x09u
#define DCM_E_MIXED_MODE                          0x0Au
#define DCM_E_WRONG_STATUSVALUE                   0x0Bu
#define DCM_E_PROTOCOL_NOT_FOUND                  0x0Cu
#define DCM_E_NVM_UPDATION_NOT_OK                 0x0Du
#define DCM_E_FULLCOMM_DISABLED                   0x0Eu
#define DCM_E_PROTOCOL_NOT_STARTED                0x10u
#define DCM_E_PSUEDO_RECEPTION                    0x11u
#define DCM_E_SERVICE_TABLE_NOT_SET               0x12u
#define DCM_E_SESSION_NOT_CONFIGURED              0x13u
#define DCM_E_SUBNET_NOT_SUPPORTED                0x14u
#define DCM_E_DDDI_NOT_CONFIGURED                 0x15u
#define DCM_E_EXCEEDED_MAX_RECORDS                0x16u
#define DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION    0x17u
#define DCM_E_INVALID_ADDRLENGTH_FORMAT           0x18u
#define DCM_E_CONTROL_FUNC_NOT_CONFIGURED         0x19u
#define DCM_E_INVALID_CONTROL_PARAM               0x1Au
#define DCM_E_NO_WRITE_ACCESS                     0x1Bu
#define DCM_E_RET_E_INFRASTRUCTURE_ERROR          0x1Cu
#define DCM_E_INVALID_CONTROL_DATA                0x1Du

#define DCM_E_RET_E_NOT_OK                        0x1Eu
#define DCM_E_DCMRXPDUID_RANGE_EXCEED             0x20u
#define DCM_E_DCMTXPDUID_RANGE_EXCEED             0x21u
#define DCM_E_NO_READ_ACCESS                      0x22u
#define DCM_E_SERVICE_TABLE_OUTOFBOUNDS           0x23u
#define DCM_E_SECURITYLEVEL_OUTOFBOUNDS           0x24u
#define DCM_E_RET_E_PENDING                       0x25u
#define DCM_E_INVALID_LENGTH                      0x26u
#define DCM_E_FORCE_RCRRP_IN_SILENT_COMM          0x27u
#define DCM_MAXNUMRESPONSEPENDING                 0xFFu
typedef uint8  Dcm_ReturnClearDTCType_tu8;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Std_ReturnType, DCM_VAR) Dcm_retVal_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_DET_ERROR(DCM_ApiId, DCM_ErrorId) (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_ApiId, DCM_ErrorId);

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSecurityMask_u32 (void);
extern FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSessionMask_u32  (void);

extern FUNC(void, DCM_CODE) Dcm_DsldSetsessionTiming(
      VAR(uint32, AUTOMATIC) nrP2StarMax_u32
   ,  VAR(uint32, AUTOMATIC) nrP2Max_u32
);

extern FUNC(void, DCM_CODE) Dcm_Lok_SetSesCtrlType(
   VAR(Dcm_SesCtrlType, AUTOMATIC) SesCtrlType_u8
);

extern FUNC(void, DCM_CODE) Dcm_Lok_SetSecurityLevel(
   VAR(Dcm_SecLevelType, AUTOMATIC) dataSecurityLevel_u8
);

extern FUNC(void, DCM_CODE) Dcm_Lok_ProcessResetToDefaultSession   (void);
extern FUNC(void, DCM_CODE) Dcm_Lok_ResetDefaultSessionRequestFlag (void);

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
extern FUNC(void, DCM_CODE) Dcm_Lok_ConfirmationRespPendForBootloader(
   VAR(Dcm_ConfirmationStatusType, AUTOMATIC) Status_u8
);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_TimerStop(timer)            ((timer)=0xFFFFFFFFu)
#define DCM_TimerElapsed(timer)         ((timer)==0u)
#define DCM_TimerStopped(timer)         ((timer)==0xFFFFFFFFu)

#define DCM_TimerStart(timer,time,unused,timerStatus)  ((void)(timerStatus));\
                                                       SchM_Enter_Dcm_DsldTimer_NoNest();\
                                                      ((timer) = (uint32)((time) / DCM_CFG_TASK_TIME_US));\
                                                      SchM_Exit_Dcm_DsldTimer_NoNest();

#define DCM_TimerProcess(timer,unused,timerStatus)          \
                                            do                        \
                                            {   \
                                                ((void)(timerStatus));\
                                                SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            if( ((timer)!=0u) && ((timer)!=0xFFFFFFFFuL) ) \
                                            { \
                                                (timer)--; \
                                            }\
                                            SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            }\
                                            while(0);

#define DCM_TimerSetNew(timer,time)        SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            ((timer) = ((time) / DCM_CFG_TASK_TIME_US));\
                                            SchM_Exit_Dcm_DsldTimer_NoNest();

#define DCM_NEGRESPONSE_INDICATOR       0x7Fu
#define DCM_DEFAULT_SESSION_IDX                        0x00u
#define DCM_DSLD_PARALLEL_TPR_BYTE1                    0x3eu
#define DCM_DSLD_PARALLEL_TPR_BYTE2                    0x80u
#define DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH           0x02u
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING 0x78u
#define DCM_IS_KLINEPROT_ACTIVE()    FALSE
#define DCM_CHKFULLCOMM_MODE(idx)  (Dcm_active_commode_e[idx].ComMState == DCM_DSLD_FULL_COM_MODE)
#define DCM_CHKNOCOMM_MODE(idx) (Dcm_active_commode_e[idx].ComMState != DCM_DSLD_NO_COM_MODE)
#define DCM_PROTOCOL_ENDIANNESS (Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].Endianness_ConvEnabled_b)

typedef enum{
    DCM_DSLD_POS_RESPONSE
   ,   DCM_DSLD_NEG_RESPONSE
}Dcm_DsldResponseType_ten;

typedef struct{
   Type_SwcServiceCom_tIdPdu dataActiveRxPduId_u8;
   uint8 nrActiveConn_u8;
   uint8 idxActiveSession_u8;
   boolean flgMonitorP3timer_b;
   uint8 idxCurrentProtocol_u8;
   Type_SwcServiceCom_tIdPdu dataActiveTxPduId_u8;
   uint8 datActiveSrvtable_u8;
   boolean flgCommActive_b;
   uint8 cntrWaitpendCounter_u8;
   Dcm_DsldResponseType_ten stResponseType_en;
   uint8 idxActiveSecurity_u8;
   Std_ReturnType dataResult_u8;
   uint8 idxService_u8;
   boolean dataResponseByDsd_b;
   uint8 dataSid_u8;
   Type_SwcServiceCom_tLengthPdu dataRequestLength_u16;
   Type_SwcServiceCom_tIdPdu dataOldtxPduId_u8;
   Dcm_MsgType adrActiveTxBuffer_tpu8;
   uint32 dataTimeoutMonitor_u32;
   uint8  PreviousSessionIndex;
}Dcm_DsldInternalStructureType_tst;

typedef struct{
   Type_SwcServiceCom_stInfoPdu Dcm_DslRxPduBuffer_st;
   uint8      Dcm_DslServiceId_u8;
   boolean     Dcm_DslFuncTesterPresent_b;
   boolean     Dcm_DslCopyRxData_b;
}Dcm_DslRxPduArray_tst;

typedef struct{
   uint32 dataTimeoutP2StrMax_u32;
   uint32 dataTimeoutP2max_u32;
}Dcm_DsldTimingsType_tst;

typedef struct{
    Dcm_MsgType TxBuffer_tpu8;
    Dcm_MsgLenType TxResponseLength_u32 ;
   boolean  isForceResponsePendRequested_b;
}Dcm_DslTxType_tst;

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void, DCM_CODE) Dcm_CheckActiveDiagnosticStatus(VAR(uint8, AUTOMATIC) dataNetworkId);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint8, DCM_VAR) Dcm_DslWaitPendBuffer_au8[8];
extern VAR(uint8, DCM_VAR) Dcm_CurProtocol_u8;
extern VAR(Dcm_SesCtrlType, DCM_VAR) Dcm_CC_ActiveSession_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2CONST(Dcm_Dsld_protocol_tableType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldProtocol_pcst;
extern P2CONST(uint8,     DCM_VAR, DCM_INTERN_CONST) Dcm_DsldRxTable_pcu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DslRxPduArray_tst, DCM_VAR) Dcm_DslRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(boolean, DCM_VAR) Dcm_isFuncTPOnOtherConnection_b;
extern VAR(boolean, DCM_VAR) Dcm_isInitialised_b;
extern VAR(boolean, DCM_VAR) Dcm_acceptRequests_b;
extern VAR(boolean, DCM_VAR) Dcm_isCancelTransmitInvoked_b;
extern VAR(boolean, DCM_VAR) Dcm_isStopProtocolInvoked_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(boolean, DCM_VAR) Dcm_ReadyForBoot_b;
extern VAR(boolean, DCM_VAR) Dcm_SesChgOnWarmResp_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2CONST(Dcm_Dsld_connType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldConnTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DsldInternalStructureType_tst, DCM_VAR) Dcm_DsldGlobal_st;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DsldTimingsType_tst, DCM_VAR) Dcm_DsldTimer_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(boolean, DCM_VAR) Dcm_isGeneralRejectSent_b;
extern VAR(boolean, DCM_VAR) Dcm_isSessionStored_b;

#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Type_SwcServiceCom_stInfoPdu, DCM_VAR) Dcm_DsldPduInfo_st;
extern VAR(Dcm_DslTxType_tst, DCM_VAR) Dcm_DslTransmit_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2CONST(Dcm_Dsld_ServiceType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSrvTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_MsgContextType, DCM_VAR) Dcm_DsldMsgContext_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSessionTable_pcu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(StatusType, DCM_VAR) Dcm_P2OrS3TimerStatus_uchr;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void, DCM_CODE) Dcm_Lok_TriggerTransmit(void);

#define DCM_NUMBER_OF_DSL_STATES                  (0x06u)
#define DSL_STATE_IDLE                            (0x00u)
#define DSL_STATE_WAITING_FOR_RXINDICATION        (0x01u)
#define DSL_STATE_REQUEST_RECEIVED                (0x02u)
#define DSL_STATE_RESPONSE_TRANSMISSION           (0x03u)
#define DSL_STATE_WAITING_FOR_TXCONFIRMATION      (0x04u)
#define DSL_STATE_ROETYPE1_RECEIVED               (0x05u)
#define DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING      (0x00u)
#define DSL_SUBSTATE_S3_OR_P3_TIMEOUT             (0x01u)
#define DSL_SUBSTATE_STOP_PROTOCOL                (0x02u)
#define DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING      (0x03u)
#define DSL_SUBSTATE_STOP_ROE                     (0x04u)
#define DSL_SUBSTATE_START_PROTOCOL               (0x05u)
#define DSL_SUBSTATE_P2MAX_TIMEMONITORING         (0x06u)
#define DSL_SUBSTATE_SEND_PENDING_RESPONSE        (0x07u)
#define DSL_SUBSTATE_SEND_GENERAL_REJECT          (0x08u)
#define DSL_SUBSTATE_SEND_FINAL_RESPONSE          (0x09u)
#define DSL_SUBSTATE_DATA_READY                   (0x0Au)
#define DSL_SUBSTATE_WAIT_FOR_DATA                (0x0Bu)
#define DSL_SUBSTATE_WAIT_PAGE_TXCONFIRM          (0x0Cu)

extern FUNC(void, DCM_CODE) Dcm_Lok_DslStateMachine(void);

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )
extern FUNC(void, DCM_CODE) Dcm_Lok_CC_Mainfunction(void);
#endif
extern FUNC(void, DCM_CODE) Dcm_Lok_CC_TxConfirmation(void);
extern FUNC(void, DCM_CODE) Dcm_Lok_SendResponse(P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_INTERN_DATA) adrPduStrucutre_pcst);
extern FUNC(void, DCM_CODE) Dcm_DslDsdRestoreSecaTimer(void);
extern FUNC(P2VAR(Dcm_MsgItemType,AUTOMATIC, DCM_INTERN_DATA), DCM_CODE) Dcm_GetActiveBuffer(void);

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
extern FUNC(uint8, DCM_CODE) Dcm_GetActiveConnectionIdx_u8 (void);
extern FUNC(void, DCM_CODE) Dcm_DslDsdWarmStart(void);
#endif

extern FUNC(void, DCM_CODE) Dcm_Lok_ResetCopyRxDataStatus ( VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) RxPduId );

#if(((DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF ))   ||     \
     (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF))
extern FUNC(uint32, DCM_CODE) Dcm_GetSignal_u32(VAR(uint8,AUTOMATIC) xDataType_u8
   ,     VAR(uint16,AUTOMATIC) posnStart_u16
   ,     P2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) adrReqBuffer_u8
   ,     VAR(uint8,AUTOMATIC) dataEndianness_u8);
#endif

#if( \
\
((DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_OBDMODE1_SR_ENABLED!=DCM_CFG_OFF)) ||            \
 \
     ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)) ||  \
     ((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)) || \
     (DCM_CFG_RBA_DEM_SR_ENABLED != DCM_CFG_OFF))
extern FUNC(void, DCM_CODE) Dcm_StoreSignal(
        VAR(uint8,  AUTOMATIC                 ) xDataType_u8
   ,    VAR(uint16, AUTOMATIC                 ) posnStart_u16
   ,  P2VAR(uint8,  AUTOMATIC, DCM_INTERN_DATA) adrRespBuffer_u8
   ,    VAR(uint32, AUTOMATIC                 ) dataSignalValue_u32
   ,    VAR(uint8,  AUTOMATIC                 ) dataEndianness_u8
);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"


LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspConfirmation(
      VAR(Dcm_IdContextType,     AUTOMATIC) dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC) dataRxPduId_u8
   ,  VAR(uint16,     AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType, AUTOMATIC) status_u8
){
   if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].Dcm_ConfirmationService !=((Dcm_ConfirmationApiType)NULL_PTR)
   ){
        (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].Dcm_ConfirmationService)(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,status_u8);
   }
}

LOCAL_INLINE FUNC(boolean, DCM_CODE) DCM_IS_KWPPROT_ACTIVE(void){
   boolean retval_b = FALSE;
    return retval_b;
}

#endif

