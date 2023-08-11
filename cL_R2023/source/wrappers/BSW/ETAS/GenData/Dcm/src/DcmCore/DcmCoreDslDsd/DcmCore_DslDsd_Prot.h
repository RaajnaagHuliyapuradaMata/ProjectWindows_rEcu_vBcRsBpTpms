

#ifndef DCMCORE_DSLDSD_PROT_H
#define DCMCORE_DSLDSD_PROT_H

#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
#include "NvM.h"
#endif
 #if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif
#include "Dcm_Dsd.h"

#define DCM_ENDIANNESSCONVERSION16(data) ((data) = rba_BswSrv_ByteOrderSwap16((uint16)(data)))

#define DCM_ENDIANNESSCONVERSION32(data) ((data) = rba_BswSrv_ByteOrderSwap32(data))

#define DCM_MEMCOPY(xDest_pv,xSrc_pcv,numBytes_u32)         (void)rba_BswSrv_MemCopy((xDest_pv),(xSrc_pcv),(uint32)(numBytes_u32))
#define DCM_MEMSET(xDest_pv,xPattern_u32,numBytes_u32)              (void)rba_BswSrv_MemSet((xDest_pv),(xPattern_u32),(uint32)(numBytes_u32))
#define DCM_UNUSED_PARAM(P)   ((void)(P))

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

#define DCM_NOTVALID_TYPE     0x00u
#define DCM_WARMREQUEST_TYPE  0x01u
#define DCM_WARMINIT_TYPE     0x02u
#define DCM_WARMRESPONSE_TYPE 0x03u
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_ProgConditionsType Dcm_ProgConditions_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
typedef enum
{
    DCM_BOOT_IDLE = 0,
    DCM_BOOT_PROCESS_RESET,
    DCM_BOOT_SENDFORCEDRESPPEND,
    DCM_BOOT_WAIT,
    DCM_BOOT_STORE_WARMREQ,
    DCM_BOOT_STORE_WARMINIT,
    DCM_BOOT_STORE_WARMRESP,
    DCM_BOOT_ERROR,
    DCM_BOOT_WAIT_FOR_RESET,
    DCM_BOOT_PERFORM_RESET,
    DCM_BOOT_PREPARE_RESET
}Dcm_BootLoaderStates_ten;

#define DCM_JUMPTOOEMBOOTLOADER            0x00u
#define DCM_JUMPTOSYSSUPPLIERBOOTLOADER 0x01u
#define DCM_JUMPDRIVETODRIVE            0x02u
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_BootLoaderStates_ten Dcm_BootLoaderState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_JumpToBootLoader(uint8 dataBootType_u8,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern void Dcm_ResetBootLoader(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
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
#define DCM_SECURITYACCESS_ID   0xA9u
#define DCM_TXCONFIRMATION_ID   0xAAu
#define DCM_SUPPLIERNOTIFICATION_ID 0xABu
#define DCM_MANUFACTURENOTIFICATION_ID 0xACu

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
#define DCM_E_ENABLEDTCRECORD_FAILED              0x28U
#define DCM_MAXNUMRESPONSEPENDING                 0xFFu
typedef uint8  Dcm_ReturnClearDTCType_tu8;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern Std_ReturnType Dcm_retVal_u8;
extern Dcm_SrvOpStatusType Dcm_SrvOpstatus_u8;
extern Dcm_OpStatusType    Dcm_ExtSrvOpStatus_u8;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern Dcm_SrvOpStatusType Dcm_OBDSrvOpstatus_u8;
extern Dcm_SrvOpStatusType Dcm_OBDExtSrvOpStatus_u8;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#define     DCM_DET_ERROR(DCM_ApiId, DCM_ErrorId)                                 \
                                        (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_ApiId, DCM_ErrorId);
#else
#define     DCM_DET_ERROR(DCM_ApiId, DCM_ErrorId)
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern uint32 Dcm_DsldGetActiveSecurityMask_u32 (void);
extern uint32 Dcm_DsldGetActiveSessionMask_u32 (void);
extern void Dcm_DsldSetsessionTiming(uint32 nrP2StarMax_u32,
                                                      uint32 nrP2Max_u32);
extern void Dcm_Lok_SetSesCtrlType ( Dcm_SesCtrlType SesCtrlType_u8);
extern void Dcm_Lok_SetSecurityLevel (Dcm_SecLevelType dataSecurityLevel_u8);
extern void Dcm_Lok_ProcessResetToDefaultSession(void);
extern void Dcm_Lok_ResetDefaultSessionRequestFlag(void);
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
extern void Dcm_Lok_ConfirmationRespPendForBootloader(Dcm_ConfirmationStatusType Status_u8);
#endif
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern boolean Dcm_Lok_IsTxPduIdOBD(PduIdType DcmTxPduId);
extern boolean Dcm_Lok_IsRxPduIdOBD(PduIdType DcmRxPduId);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_TimerStop(timer)            ((timer)=0xFFFFFFFFu)

#define DCM_TimerElapsed(timer)         ((timer)==0u)

#define DCM_TimerStopped(timer)         ((timer)==0xFFFFFFFFu)

#if ( DCM_CFG_OSTIMER_USE != FALSE )
#define DCM_TimerStart(timer,time,starttime,timerStatus) do                       \
                                            { \
                                            (timerStatus = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&(starttime)))); \
                                            SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            if( timerStatus == E_OK ) \
                                            { \
                                                ((timer) = (time)); \
                                            } \
                                            else \
                                            { \
                                                ((timer) = ((time) / DCM_CFG_TASK_TIME_US)); \
                                            } \
                                            SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            }while(0);

#define DCM_TimerProcess(timer,starttime,timerStatus)   do                     \
                                            { \
                                            if ( timerStatus == E_OK ) \
                                            { \
                                                timerStatus = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&Dcm_CurrTick_u32)); \
                                                SchM_Enter_Dcm_DsldTimer_NoNest();\
                                                if ( timerStatus == E_OK ) \
                                                { \
                                                    if ( (DCM_CFG_TICKS2US_COUNTER(Dcm_CurrTick_u32 - (starttime))) >= (timer) ) \
                                                    { \
                                                        ((timer) = 0u); \
                                                    } \
                                                } \
                                                else \
                                                { \
                                                     \
                                                } \
                                                SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            } \
                                            else  \
                                            { \
                                                SchM_Enter_Dcm_DsldTimer_NoNest();\
                                                if( ((timer)!=0u) && ((timer)!=0xFFFFFFFFu) ) \
                                                { \
                                                    (timer)--; \
                                                } \
                                                SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            } \
                                            }while(0);

#define DCM_TimerSetNew(timer,time)   SchM_Enter_Dcm_DsldTimer_NoNest();\
                                    if((timer)!=0u)           \
                                    {                         \
                                        (timer) = (time);     \
                                    }\
                                      SchM_Exit_Dcm_DsldTimer_NoNest();

#else

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
                                            } \
                                            SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            }\
                                            while(0);

#define DCM_TimerSetNew(timer,time)        SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            ((timer) = ((time) / DCM_CFG_TASK_TIME_US));\
                                            SchM_Exit_Dcm_DsldTimer_NoNest();
#endif

#define DCM_NEGRESPONSE_INDICATOR       0x7Fu

#define DCM_DEFAULT_SESSION_IDX                        0x00u

#define DCM_DSLD_PARALLEL_TPR_BYTE1                    0x3eu
#define DCM_DSLD_PARALLEL_TPR_BYTE2                    0x80u
#define DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH           0x02u

#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING 0x78u

#if( DCM_CFG_KLINE_ENABLED != DCM_CFG_OFF )
    #define DCM_IS_KLINEPROT_ACTIVE() \
    (((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) == DCM_CARB_ON_KLINE)\
\
    ||((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) == DCM_OBD_ON_KLINE)\
\
    ||((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) == DCM_KWP_ON_KLINE))
#else
#define DCM_IS_KLINEPROT_ACTIVE()    FALSE
#endif

#define DCM_CHKFULLCOMM_MODE(idx)  (Dcm_active_commode_e[idx].ComMState == DCM_DSLD_FULL_COM_MODE)

#define DCM_CHKNOCOMM_MODE(idx) (Dcm_active_commode_e[idx].ComMState != DCM_DSLD_NO_COM_MODE)

#define DCM_PROTOCOL_ENDIANNESS (Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].Endianness_ConvEnabled_b)

typedef enum
{
    DCM_DSLD_POS_RESPONSE,
    DCM_DSLD_NEG_RESPONSE
}Dcm_DsldResponseType_ten;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
typedef enum
{
    DCM_QUEUE_IDLE,
    DCM_QUEUE_RUNNING,
    DCM_QUEUE_COMPLETED
}Dcm_DsldQueHandling_ten;
#endif
typedef struct{
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_MsgType  adrBufferPtr_pu8;
#endif
    PduIdType dataActiveRxPduId_u8;
    uint8 nrActiveConn_u8;
    uint8 idxActiveSession_u8;
    boolean flgMonitorP3timer_b;
    uint8 idxCurrentProtocol_u8;
    PduIdType dataActiveTxPduId_u8;
    uint8 datActiveSrvtable_u8;
    boolean flgCommActive_b;
    uint8 cntrWaitpendCounter_u8;
    Dcm_DsldResponseType_ten stResponseType_en;
    uint8 idxActiveSecurity_u8;
    Std_ReturnType dataResult_u8;
    uint8 idxService_u8;
    boolean dataResponseByDsd_b;
    uint8 dataSid_u8;
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    uint8  dataOldSrvtable_u8;
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    boolean flgPagedBufferTxOn_b;
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    PduIdType dataNewRxPduId_u8;
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    PduIdType dataPassRxPduId_u8;
#endif
#endif
    PduLengthType dataRequestLength_u16;
    PduIdType dataOldtxPduId_u8;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_MsgLenType dataCurrentPageRespLength_u32;
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    PduLengthType dataNewdataRequestLength_u16;
#endif
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    PduLengthType dataPassdataRequestLength_u16;
#endif
    uint32 dataTimerTimeout_u32;
#endif
    Dcm_MsgType adrActiveTxBuffer_tpu8;
    uint32 dataTimeoutMonitor_u32;
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    uint32 datRoeType2Timeout_u32;
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    uint32 dataPagedBufferTimeout_u32;
#endif
    uint8  PreviousSessionIndex;
}Dcm_DsldInternalStructureType_tst;

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)

typedef struct{
    PduIdType dataActiveRxPduId_u8;
    uint8 nrActiveConn_u8;
    uint8 idxCurrentProtocol_u8;
    PduIdType dataActiveTxPduId_u8;
    uint8 datActiveSrvtable_u8;
    boolean flgCommActive_b;
    uint8 cntrWaitpendCounter_u8;
    Dcm_DsldResponseType_ten stResponseType_en;
    Std_ReturnType dataResult_u8;
    uint8 idxService_u8;
    boolean dataResponseByDsd_b;
    uint8 dataSid_u8;
    PduLengthType dataRequestLength_u16;
    PduIdType dataOldtxPduId_u8;
    Dcm_MsgType adrActiveTxBuffer_tpu8;
    uint32 dataTimeoutMonitor_u32;
}Dcm_OBDInternalStructureType_tst;

// State Machine definition for OBD in case of parallel UDS/OBD handling
typedef enum
{
    DCM_OBD_IDLE,
    DCM_OBD_REQUESTRECEIVING,
    DCM_OBD_REQUESTRECEIVED,
    DCM_OBD_VERIFYDATA,
    DCM_OBD_PROCESSSERVICE,
    DCM_OBD_WAITFORTXCONF
} Dcm_OBDStateMachine_tst;

typedef struct{
    PduInfoType Dcm_DslRxPduBuffer_st;
    uint8       Dcm_DslServiceId_u8;
    boolean     Dcm_DslCopyRxData_b;
}Dcm_DslOBDRxPduArray_tst;

#endif

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)

typedef struct{
    Dcm_DsldQueHandling_ten Dcm_QueHandling_en;
    Dcm_MsgType  adrBufferPtr_pu8;
    PduLengthType dataQueueReqLength_u16;
    PduIdType dataQueueRxPduId_u8;
    uint8 idxBufferIndex_u8;
}Dcm_QueueStructure_tst;
#endif

typedef struct{
    PduInfoType Dcm_DslRxPduBuffer_st;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_MsgType  Dcm_DslBufferPtr_pu8;
#endif
    uint8      Dcm_DslServiceId_u8;
    boolean     Dcm_DslFuncTesterPresent_b;
    boolean     Dcm_DslCopyRxData_b;
}Dcm_DslRxPduArray_tst;

typedef struct{
    uint32 dataTimeoutP2StrMax_u32;
    uint32 dataTimeoutP2max_u32;
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    uint32 dataTimeoutP3max_u32;
#endif
}Dcm_DsldTimingsType_tst;

typedef struct{
    Dcm_MsgType TxBuffer_tpu8;
    Dcm_MsgLenType TxResponseLength_u32 ;
    boolean  isForceResponsePendRequested_b;
}Dcm_DslTxType_tst;

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
typedef struct{
    Dcm_MsgType TxBuffer_tpu8;
    Dcm_MsgLenType TxResponseLength_u32 ;
}Dcm_OBDTxType_tst;
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

typedef struct{
    uint8   EventId_u8;
    boolean Is_Queued;
    boolean Is_Processed;
    PduIdType   RxPduId_u8;
} Dcm_DcmDspEventWaitlist_t;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsld_RoeRxToTestSrcMappingType Dcm_Dsld_RoeRxToTestSrcMappingTable[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if( (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEEVENT_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DcmDspEventWaitlist_t Dcm_DcmDspEventQueue [DCM_MAX_SETUPROEEVENTS];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 DcmRoeQueueIndex_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_CheckActiveDiagnosticStatus(uint8 dataNetworkId);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 Dcm_DslWaitPendBuffer_au8[8];
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern uint8 Dcm_OBDWaitPendBuffer_au8[8];
#endif
extern uint8 Dcm_CurProtocol_u8;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern uint8 Dcm_CurOBDProtocol_u8;
#endif
extern Dcm_SesCtrlType Dcm_CC_ActiveSession_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsld_protocol_tableType * Dcm_DsldProtocol_pcst;
extern const uint8 * Dcm_DsldRxTable_pcu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern Dcm_DslOBDRxPduArray_tst Dcm_DslOBDRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#endif
extern Dcm_DslRxPduArray_tst Dcm_DslRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_isFuncTPOnOtherConnection_b;
extern boolean Dcm_isInitialised_b;
extern boolean Dcm_acceptRequests_b;
extern boolean Dcm_isCancelTransmitInvoked_b;
extern boolean Dcm_isStopProtocolInvoked_b;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern boolean Dcm_ObdSendTxConfirmation_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_ReadyForBoot_b;
extern boolean Dcm_SesChgOnWarmResp_b;

#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsld_connType * Dcm_DsldConnTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DsldInternalStructureType_tst Dcm_DsldGlobal_st;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern Dcm_OBDInternalStructureType_tst Dcm_OBDGlobal_st;
#endif
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
extern Dcm_QueueStructure_tst Dcm_QueueStructure_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DsldTimingsType_tst Dcm_DsldTimer_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_isGeneralRejectSent_b;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern boolean Dcm_OBDisGeneralRejectSent_b;
#endif
extern boolean Dcm_isSessionStored_b;
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
extern boolean Dcm_isFirstReponseSent_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern PduInfoType Dcm_DsldPduInfo_st ;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern PduInfoType Dcm_OBDPduInfo_st;
extern Dcm_OBDTxType_tst Dcm_OBDTransmit_st;
#endif
extern Dcm_DslTxType_tst Dcm_DslTransmit_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsld_ServiceType * Dcm_DsldSrvTable_pcst;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern const Dcm_Dsld_ServiceType* Dcm_OBDSrvTable_pcst;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_MsgContextType Dcm_DsldMsgContext_st;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern Dcm_MsgContextType Dcm_OBDMsgContext_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const uint8 * Dcm_DsldSessionTable_pcu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DsdStatesType_ten Dcm_DsdRoe2State_en;
extern Dcm_MsgContextType Dcm_Roe2MesContext_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_MsgContextType Dcm_Rdpi2MesContext_st;
extern Dcm_DsldResponseType_ten Dcm_Rdpi2ResponseType_en;
extern PduInfoType Dcm_DsldRdpi2pduinfo_ast[DCM_CFG_NUM_RDPITYPE2_TXPDU];
extern const Dcm_ProtocolExtendedInfo_type * Dcm_DsldRdpi2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if (DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_Dsld_KwpTimerServerType Dcm_DsldKwpReqTiming_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if (DCM_CFG_OSTIMER_USE != FALSE)
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dcm_P2OrS3StartTick_u32;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern uint32 Dcm_OBDP2OrS3StartTick_u32;
#endif
extern uint32 Dcm_CurrTick_u32;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern uint32 Dcm_PagedBufferStartTick_u32;
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
extern uint32 Dcm_TimerStartTick_u32;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#if ((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dcm_SysPrevTick_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dcm_SysCurrTick_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#endif
#endif

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_isObdRequestReceived_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern StatusType Dcm_P2OrS3TimerStatus_uchr;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern StatusType Dcm_OBDP2OrS3TimerStatus_uchr;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern StatusType Dcm_PagedBufferTimerStatus_uchr;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern StatusType Dcm_CounterValueTimerStatus_uchr;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern StatusType Dcm_RoeType2TimerStatus_uchr ;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern void Dcm_Lok_TriggerTransmit(void);

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF))
#define DCM_NUMBER_OF_DSL_STATES                  (0x08u)
#elif((DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF) && (DCM_PAGEDBUFFER_ENABLED == DCM_CFG_OFF))
#define DCM_NUMBER_OF_DSL_STATES                  (0x06u)
#elif((DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF) || (DCM_PAGEDBUFFER_ENABLED == DCM_CFG_OFF))
#define DCM_NUMBER_OF_DSL_STATES                  (0x07u)
#endif

#define DSL_STATE_IDLE                            (0x00u)
#define DSL_STATE_WAITING_FOR_RXINDICATION        (0x01u)
#define DSL_STATE_REQUEST_RECEIVED                (0x02u)
#define DSL_STATE_RESPONSE_TRANSMISSION           (0x03u)
#define DSL_STATE_WAITING_FOR_TXCONFIRMATION      (0x04u)
#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF))
#define DSL_STATE_PROTOCOL_PREEMPTION             (0x05u)
#define DSL_STATE_PAGEDBUFFER_TRANSMISSION        (0x06u)
#define DSL_STATE_ROETYPE1_RECEIVED               (0x07u)
#elif((DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF) && (DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF))
#define DSL_STATE_PAGEDBUFFER_TRANSMISSION        (0x05u)
#define DSL_STATE_ROETYPE1_RECEIVED               (0x06u)
#elif((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_PAGEDBUFFER_ENABLED == DCM_CFG_OFF))
#define DSL_STATE_PROTOCOL_PREEMPTION             (0x05u)
#define DSL_STATE_ROETYPE1_RECEIVED               (0x06u)
#elif((DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF) && (DCM_PAGEDBUFFER_ENABLED == DCM_CFG_OFF))
#define DSL_STATE_ROETYPE1_RECEIVED               (0x05u)
#endif

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

extern void Dcm_Lok_DslStateMachine(void);

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern void Dcm_Lok_OBDStateMachine(void);
extern void Dcm_Lok_OBDTimerProcessing(void);
extern void Dcm_Lok_ConfirmationToOBDApl(void);
#endif

#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )
extern void Dcm_Lok_CC_Mainfunction (void);
#endif
extern void Dcm_Lok_CC_TxConfirmation (void);
extern void Dcm_Lok_SendResponse(const PduInfoType * adrPduStrucutre_pcst);
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern void Dcm_Lok_OBDSendResponse(const PduInfoType* adrPduStrucutre_pcst);
#endif
extern void Dcm_DslDsdRestoreSecaTimer(void);
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
extern Dcm_MsgItemType * Dcm_Lok_ProvideFreeBuffer(uint8 idxProtocolIndex_u8,boolean isQueuedReq_b);
#endif
extern Dcm_MsgItemType * Dcm_GetActiveBuffer(void);
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern boolean Dcm_Lok_CheckTotalResponseLength(Dcm_MsgLenType TotalResLen_u32 );
#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
extern uint8 Dcm_GetActiveConnectionIdx_u8 (void);
extern void Dcm_DslDsdWarmStart(void);
#endif

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern void Dcm_Lok_ResetOBDCopyRxDataStatus(PduIdType id);
#endif

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern void Dcm_Lok_PagedBufferTimeout(void);
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
extern void Dcm_DsldRoeTimeOut(void);
extern void Dcm_Lok_ROEResetOnConfirmation(void);
#endif

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) || (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF))
Std_ReturnType Dcm_Lok_CancelTransmit(void);
#endif

#if (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF )
extern void Dcm_DsldResetRDPI(void);
#endif

extern void Dcm_Lok_ResetCopyRxDataStatus ( PduIdType RxPduId );

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF))

extern BufReq_ReturnType Dcm_DsldPersistentRoeHandling_en(
                                         const Dcm_Dsld_protocol_tableType * adrArrivedProt_pcst,
                                         PduLengthType nrTpSduLength_u16,
                                         PduIdType dataRxpduId_u8
                                                     );
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if (((DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF ))   ||     \
     (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEVARLENGTH==DCM_CFG_OFF)))

extern uint32 Dcm_GetSignal_u32(uint8 xDataType_u8,
                                           uint16 posnStart_u16,
                                           const uint8 * adrReqBuffer_u8,
                                           uint8 dataEndianness_u8);
#endif

#if (\
 \
((DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_OBDMODE1_SR_ENABLED!=DCM_CFG_OFF)) ||            \
 \
     ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)) ||     \
     ((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEVARLENGTH==DCM_CFG_OFF)))||\
     (DCM_CFG_RBA_DEM_SR_ENABLED != DCM_CFG_OFF))
extern void Dcm_StoreSignal(uint8 xDataType_u8,
                                           uint16 posnStart_u16,
                                           uint8 * adrRespBuffer_u8,
                                           uint32 dataSignalValue_u32,
                                           uint8 dataEndianness_u8);
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#if(DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
typedef enum
{
    DCM_RDPI_NO_TRANMISSION,
    DCM_RDPI_SLOW_RATE,
    DCM_RDPI_MEDIUM_RATE,
    DCM_RDPI_FAST_RATE
}Dcm_RdpiTxModeType_ten;

typedef struct{
  uint32 cntrTime_u32;
  uint16 dataId_u16;
  uint16 idxPeriodicId_u16;
  Dcm_RdpiTxModeType_ten dataOverflowValue_en;
  boolean dataRange_b;
} Dcm_PeriodicInfoType_tst;

#if(DCM_CFG_MAX_DID_SCHEDULER>0)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_PeriodicInfoType_tst Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 Dcm_NumOfActivePeriodicId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_DsldPeriodicScheduler(void);
extern void Dcm_RdpiMainFunction(void);
extern void Dcm_DsldPeriodicSchedulerIni(void);
extern void Dcm_GetRdpiType2Index(uint8 * idxRdpi2TxPduId_u8);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#if (DCM_ROE_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_DsldProcessRoeQueue(void);
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
extern void Dcm_RestoreROEDtcEvents(void);
#endif
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
extern void Dcm_RestoreROEDidEvents(void);
#endif
extern void Dcm_ResetROEEvents(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_KWPConfirmationForSplitResp(Dcm_ConfirmationStatusType status);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

LOCAL_INLINE void Dcm_DspConfirmation
                                       (
                             Dcm_IdContextType dataIdContext_u8,
                             PduIdType dataRxPduId_u8,
                             uint16 dataSourceAddress_u16,
                             Dcm_ConfirmationStatusType status_u8
                                       )

{    if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].Dcm_ConfirmationService !=((Dcm_ConfirmationApiType)NULL_PTR))
    {
        (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].Dcm_ConfirmationService)(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,status_u8);
    }
}

LOCAL_INLINE boolean DCM_IS_KWPPROT_ACTIVE(void)
{
    boolean retval_b = FALSE;
#if( DCM_CFG_KWP_ENABLED != DCM_CFG_OFF )
    retval_b = (((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) & 0xF0u) == 0x80u);
#endif
    return retval_b;
}

#endif

