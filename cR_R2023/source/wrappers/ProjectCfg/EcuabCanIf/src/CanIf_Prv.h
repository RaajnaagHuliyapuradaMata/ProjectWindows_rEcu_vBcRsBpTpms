

#ifndef CANIF_PRV_H
#define CANIF_PRV_H

#include "CanIf.h"

#include "CanIf_Cbk.h"

#include "Can.h"
#if (!defined(CAN_AR_RELEASE_MAJOR_VERSION) || (CAN_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CAN_AR_RELEASE_MINOR_VERSION) || (CAN_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if (CANIF_J1939NM_ENABLED != STD_OFF)
#include "J1939Nm.h"
#include "J1939Nm_Cbk.h"
#if (!defined(J1939NM_AR_RELEASE_MAJOR_VERSION) || (J1939NM_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(J1939NM_AR_RELEASE_MINOR_VERSION) || (J1939NM_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_PDUR_ENABLED != STD_OFF)
#include "PduR.h"
#include "PduR_CanIf.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_CANNM_ENABLED != STD_OFF)
#include "CanNm.h"
#include "CanNm_Cbk.h"
#if (!defined(CANNM_AR_RELEASE_MAJOR_VERSION) || (CANNM_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANNM_AR_RELEASE_MINOR_VERSION) || (CANNM_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_CANTP_ENABLED != STD_OFF)
#include "CanTp.h"
#include "CanTp_Cbk.h"
#if (!defined(CANTP_AR_RELEASE_MAJOR_VERSION) || (CANTP_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANTP_AR_RELEASE_MINOR_VERSION) || (CANTP_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_CANTSYN_ENABLED != STD_OFF)
#include "CanTSyn.h"
#include "CanTSyn_Cbk.h"
#if (!defined(CANTSYN_AR_RELEASE_MAJOR_VERSION) || (CANTSYN_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANTSYN_AR_RELEASE_MINOR_VERSION) || (CANTSYN_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_J1939TP_ENABLED != STD_OFF)
#include "J1939Tp.h"
#include "J1939Tp_Cbk.h"
#if (!defined(J1939TP_AR_RELEASE_MAJOR_VERSION) || (J1939TP_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(J1939TP_AR_RELEASE_MINOR_VERSION) || (J1939TP_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_XCP_ENABLED != STD_OFF)
#include "Xcp.h"
#include "XcpOnCan_Cbk.h"
#if (!defined(XCP_AR_RELEASE_MAJOR_VERSION) || (XCP_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(XCP_AR_RELEASE_MINOR_VERSION) || (XCP_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT == STD_ON
#include "CanTrcv.h"
#if (!defined(CANTRCV_AR_RELEASE_MAJOR_VERSION) || (CANTRCV_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANTRCV_AR_RELEASE_MINOR_VERSION) || (CANTRCV_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_ECUM_ENABLED == STD_ON)

#include "EcuM.h"
#if (!defined(ECUM_AR_RELEASE_MAJOR_VERSION) || (ECUM_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ECUM_AR_RELEASE_MINOR_VERSION) || (ECUM_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if (CANIF_PUBLIC_DEV_ERROR_DETECT != STD_OFF)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif
//T: SchM_CanIf.h

#include "CanIf_Cfg_SchM.h"
#if (!defined(SCHM_AR_RELEASE_MAJOR_VERSION) || (SCHM_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(SCHM_AR_RELEASE_MINOR_VERSION) || (SCHM_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if (CANIF_CANSM_ENABLED != STD_OFF)

#include "CanSM_Cbk.h"
#if (!defined(CANSM_AR_RELEASE_MAJOR_VERSION) || (CANSM_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANSM_AR_RELEASE_MINOR_VERSION) || (CANSM_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

#define CANIF_XCORE_INVALID_PIPE_ID (0xFFu)
#define CANIF_XCORE_RXINDICATION_INVALID_USER_TYPE  (0xFFu)
#define CANIF_XCORE_RXINDICATION_INVALID_CB_IDX     (0xFFu)
#define CANIF_XCORE_RXINDICATION_INVALID_CANID      (0xFFFFFFFFu)

#define CANIF_XCORE_PIPE_FLAG_PROC_POLLING  (0x0u)
#define CANIF_XCORE_PIPE_FLAG_PROC_TASK (0x1u)
#define CANIF_XCORE_PIPE_FLAG_PROC_SWI      (0x2u)
#define CANIF_XCORE_PIPE_GET_FLAG_PROC(x) (x & 0x3u)

#define CANIF_XCORE_PIPE_FLAG_TYPE_TX  (0x0u << 2u)
#define CANIF_XCORE_PIPE_FLAG_TYPE_RX  (0x1u << 2u)
#define CANIF_XCORE_PIPE_FLAG_TYPE_TXCONF  (0x2u << 2u)
#define CANIF_XCORE_PIPE_GET_FLAG_TYPE(x) (x & (0x3u << 2u))

#define CANIF_XCORE_PIPE_FLAG_VARBUFALLOC (0x1 << 4u)
#define CANIF_XCORE_PIPE_GET_FLAG_ALLOC(x) (x & (0x1u << 4u))

#define CANIF_XCORE_PKT_FLAG_INVALID_ENDBUF_PDU  (0x80000000u)
#define CANIF_XCORE_PKT_FLAG_INVALID_PDU  (0x40000000u)
#define CANIF_XCORE_PKT_FLAG_VALID_PDU  (0x0u)
#define CANIF_XCORE_PKT_PDUID_MASK  (0xFFFFu)
#define CANIF_XCORE_PKT_CALLBACKIDX_MASK  (0xFF0000u)
#define CANIF_XCORE_PKT_CALLBACKIDX_SHIFT  (16u)
#define CANIF_XCORE_PKT_USERTYPE_MASK  (0xF000000u)
#define CANIF_XCORE_PKT_USERTYPE_SHIFT  (24u)
#define CANIF_XCORE_PKT_HDR_CALC(pduId, callbackIdx, userType)  (CANIF_XCORE_PKT_FLAG_VALID_PDU | \
                                                                ((pduId) & CANIF_XCORE_PKT_PDUID_MASK) | \
                                                                (((callbackIdx) << CANIF_XCORE_PKT_CALLBACKIDX_SHIFT) & CANIF_XCORE_PKT_CALLBACKIDX_MASK) | \
                                                                (((uint32)(userType) << CANIF_XCORE_PKT_USERTYPE_SHIFT) & CANIF_XCORE_PKT_USERTYPE_MASK) )
#define CANIF_XCORE_PTK_HDR_SIZE_U32W (sizeof(CanIf_XCore_PipePktHdrType_st) / sizeof(uint32))
#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

typedef enum
{
    CANIF_TXBUFFER_EMPTY,
    CANIF_TXBUFFER_READY,
    CANIF_TXBUFFER_FULL
}CanIf_Lok_BuffStatus_ten;

typedef struct
{
    uint8 last_index;
    CanIf_Lok_BuffStatus_ten bufferstatus;
}CanIf_Lok_TxBufferStatus_tst;

typedef struct
{
    boolean pdu_buffered_flag;

}CanIf_Lok_TxPduStatus_tst;

#endif

typedef struct
{
    CanIf_ControllerModeType    DeviceMode;
    CanIf_PduModeType           ChannelMode;
#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
    CanIf_NotifStatusType       CanIf_TxCnfmStatus;
#endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    boolean BlPnTxFilter;
#endif
#if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
    boolean ValidationSts_b;
#endif
}CanIf_ControllerStateType;

 #if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

#if (CANIF_XCORE_DEBUG_ACTIVE != STD_OFF)

typedef struct
{
    uint32 NumSendCalls_u32;
    uint32 NumSendCallsNotOk_u32;
    uint32 NumBytesSendOk_u32;
    uint32 NumReceiveCalls_u32;
    uint32 NumReceiveCallsOk_u32;
    uint32 NumBytesReceiveOk_u32;
    PduIdType SendLastAttemptedPduId;
    PduInfoType SendLastAttemptedPduInfo;
    PduIdType ReceiveLastPduId;
    PduInfoType ReceiveLastPduInfo;

} CanIf_XCore_PipeDbgInfoType_st;

#endif

typedef struct {
    const CanIf_XCore_PipeConfigType_st *PipeConfig_pcst;
    void *FifoBaseAddr_pv;
    void *FifoEndAddr_pv;
    volatile uint32 PktCnt_u32;
    volatile uint32 PktCntAck_u32;
    volatile void *WritePtr_pv;
    volatile void *ReadPtr_pv;
    #if (CANIF_XCORE_DEBUG_ACTIVE == STD_ON)
    CanIf_XCore_PipeDbgInfoType_st  Dbg_st;
    #endif
} CanIf_XCore_PipeRuntimeInfoType_st;

typedef struct {
    uint8  CtrlID_u8;
    uint32 PktFlags_u32;
    uint32 PktPayloadLenBytes_u32;
} CanIf_XCore_PipePktHdrType_st;

typedef struct {
    const PduInfoType* PduInfoPtr;
    CanIf_Cfg_UserType_ten userType_e;
    PduIdType PduId;
    uint8 callbackIndex_u8;
    uint8 ControllerId_u8;
} CanIf_XCore_PipeTxRxParams_st;

#endif

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern VAR(CanIf_Lok_TxBufferStatus_tst, CANIF_VAR) CanIf_Lok_TxBufferRam_ast[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern VAR(CanIf_Lok_TxPduStatus_tst, CANIF_VAR) CanIf_Lok_TxPduRam_ast[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#endif

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)

#define CANIF_START_SEC_VAR_CLEARED_32
#include "CanIf_MemMap.h"
extern VAR(uint32, CANIF_VAR) CanIf_DynTxPduCanId_au32[];
#define CANIF_STOP_SEC_VAR_CLEARED_32
#include "CanIf_MemMap.h"

#endif

#if(CANIF_TRCV_WAKEUP_SUPPORT== STD_ON)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
extern CONST (CanIf_Wakeup, CANIF_CONST) CanIf_WakeupList_tacst[CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern VAR(CanIf_ControllerStateType, CANIF_VAR) CanIf_Lok_ControllerState_ast[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanIf_MemMap.h"
extern VAR(boolean, CANIF_VAR) CanIf_Lok_InitStatus_b;
#define CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
extern CONST(CanIf_RxCbk_Prototype, CANIF_CONST) CanIf_Lok_ULName_ta_fct[];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#if (CANIF_RB_CHANGERXPDUID_API != STD_OFF)

#define CANIF_START_SEC_VAR_CLEARED_32
#include "CanIf_MemMap.h"
extern VAR(uint32, CANIF_VAR) CanIf_DynRxPduCanId_au32[];
#define CANIF_STOP_SEC_VAR_CLEARED_32
#include "CanIf_MemMap.h"

#endif

#if(CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#else
#define CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#endif
#include "CanIf_MemMap.h"
extern CONST(CanIf_CallbackFuncType, CANIF_CONST) CanIf_Callback;
#if(CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC)
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#else
#define CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#endif
#include "CanIf_MemMap.h"

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern VAR(CanIf_NotifStatusType, CANIF_VAR) CanIf_Lok_TxNotification_aen[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
#endif

#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API != STD_OFF)

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern VAR(CanIf_NotifStatusType, CANIF_VAR) CanIf_Lok_RxNotification_taen[CANIF_CFG_NUM_CANRXPDUIDS];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
#endif

#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)

#define CANIF_START_SEC_VAR_CLEARED_8
#include "CanIf_MemMap.h"
extern VAR(uint8, CANIF_VAR) CanIf_Lok_RxBuffer_tau8[CANIF_CFG_RX_BUFFER_SIZE];
#define CANIF_STOP_SEC_VAR_CLEARED_8
#include "CanIf_MemMap.h"
#endif

//T:Check memmap
#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern P2CONST(Type_CfgEcuabCanIf_st, AUTOMATIC, AUTOMATIC) CanIf_Lok_ConfigSet_pcst;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
#define CANIF_START_SEC_VAR_FAST_CLEARED_8
#include "CanIf_MemMap.h"
extern VAR(uint8, AUTOMATIC) CanIf_ActiveCfgSet;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_8
#include "CanIf_MemMap.h"

 #if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern P2CONST(CanIf_XCore_ConfigType, AUTOMATIC, AUTOMATIC) CanIf_XCore_Config_pcst;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanIf_MemMap.h"
extern VAR(boolean, CANIF_VAR) CanIf_XCore_RxClrPipeFlag_b;
#define CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanIf_MemMap.h"

#endif

#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)

#define CANIF_INIT_SID                           0x01

#define CANIF_DEINIT_SID                         0x02

#define CANIF_SET_CONTROLLER_SID                 0x03

#define CANIF_GET_CONTROLLER_SID                 0x04

#define CANIF_TRANSMIT_SID                       0x05

#define CANIF_READ_RX_PDU_DATA_SID               0x06

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)

#define CANIF_READ_TX_NOTIF_STATUS_SID           0x07
#endif

#define CANIF_READ_RX_NOTIF_STATUS_SID           0x08

#define CANIF_SET_PDU_MODE_SID                   0x09

#define CANIF_GET_PDU_MODE_SID                   0x0A

#if (CANIF_PUBLIC_VERSIONINFO_API != STD_OFF)

#define CANIF_GET_VERSION_INFO_SID               0x0B
#endif

#if (CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)

#define CANIF_SET_DYNAMIC_TXID_SID               0x0C
#endif

#define CANIF_SET_TRCV_MODE_SID                  0x0D

#define CANIF_GET_TRCV_MODE_SID                  0x0E

#define CANIF_GET_TRCV_WUMODE_REASON_SID         0x0F

#define CANIF_SET_TRCV_WAKEUPMODE_SID            0x10

#define CANIF_CHECKWAKEUP_SID                    0x11

#define CANIF_CHECKVALIDATION_SID                0x12

#define CANIF_TX_CONFIRMATION_SID                0x13

#define CANIF_RX_INDICATION_SID                  0x14

#define CANIF_CONTROLLER_BUSOFF_SID              0x16

#define CANIF_CONTROLLER_MODE_IND_SID            0x17

#define CANIF_TRCVMODEINDICATION_SID             0x18

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)

#define CANIF_GET_TX_CONFIRMATION_STATE_SID      0x19
#endif

#define  CANIF_TRIGGER_TRANSMIT_SID              0x41

#define CANIF_RESET_DYNAMIC_TXID_SID             0x23

#define CANIF_CHECKBAUDRATE_SID                  0x35

#define CANIF_CHANGEBAUDRATE_SID                 0x1B

#define CANIF_SETBAUDRATE_SID                    0x27

#define CANIF_CLEARTRCVWUFFLAG_SID               0x1E

#define CANIF_CHECKTRCVWAKEFLAG_SID              0x1F

#define CANIF_CLEARTRCVWAKEFLAGIND_SID           0x20

#define CANIF_CHECKTRCVWAKEFLAGIND_SID           0x21

#define CANIF_CONFIRMPNAVAILABILITY_SID          0x1a

#define CANIF_CANCELTRANSMIT_SID                 0x25

#define CANIF_CONTROLLER_ERRORPASSIVE_SID        0x29

#define CANIF_RETURN_TX_PDU_ID_SID               0x1C

#define CANIF_RETURN_RX_PDU_ID_SID               0x2D

#define CANIF_READ_RX_MSG_ID_SID                 0x2F

#define CANIF_RB_READ_TXPDU_CANID               0x30

#define CANIF_RB_READRXPDUCANID_SID              0x31

#define CANIF_READ_TX_MSG_ID_SID                 0x32

#if (CANIF_RB_CHANGERXPDUID_API != STD_OFF)

#define CANIF_RB_CHANGERXPDUID_SID               0x34
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
#define CANIF_XCORE_APIID_INIT_SID                 0x81

#define CANIF_XCORE_APIID_PIPEWRITE_SID            0x82

#define CANIF_XCORE_APIID_PIPEREAD_SID             0x83
#endif

#define CANIF_E_PARAM_CANID                     10u

#define CANIF_E_PARAM_HOH                       12u

#define CANIF_E_PARAM_HRH                       81u

#define CANIF_E_PARAM_LPDU                      13u

#define CANIF_E_PARAM_CONTROLLER                14u

#define CANIF_E_PARAM_CONTROLLERID              15u

#define CANIF_E_PARAM_WAKEUPSOURCE              16u

#define CANIF_E_PARAM_TRCV                      17u

#define CANIF_E_PARAM_TRCVMODE                  18u

#define CANIF_E_PARAM_TRCVWAKEUPMODE            19u

#define CANIF_E_PARAM_POINTER                   20u

#define CANIF_E_PARAM_CTRLMODE                  21u

#define CANIF_E_PARAM_PDU_MODE                  22u

#define CANIF_E_UNINIT                          30u

#define CANIF_E_INVALID_RXPDUID                 60u

#define CANIF_E_INVALID_TXPDUID                 50u

#define CANIF_E_DATA_LENGTH_MISMATCH            62u

#define CANIF_E_INVALID_DLC                     61u

#define CANIF_E_STOPPED                         70u

#define CANIF_E_NOT_SLEEP                         71u

#define CANIF_E_TXPDU_LENGTH_EXCEEDED           90u

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)
#define CANIF_XCORE_E_PARAM                 81u

#define CANIF_XCORE_E_WRONGCORE            82u

#endif

#endif

#define CANIF_PRV_INVALID_CHANNEL_MODE                0u

#define CANIF_PRV_VALID_CHANNEL_MODE                1u

#define CANIF_PRV_WAKEUP_MODE                       2u

#define CANIF_PRV_CANID_TYPE_MASK                0x0fu

#define CANIF_PRV_FOUR                           4u

#define CANIF_PRV_SIX                             6u

#define CANIF_PRV_SEVEN                           7u

#define CANIF_PRV_EIGHT                           8u

#define INVALID_ID      0xffffu

#define CANIF_CAN_STD_VAL                       0x7FFu

#define CANIF_CAN_XTD_VAL                       0x1FFFFFFFu

#define CANIF_SET                               TRUE

#define CANIF_PRV_NO_UL                 0u

#if CANIF_FD_SUPPORT == STD_ON
#define CANIF_PRV_MAX_BUFFER_SIZE       64u
#else
#define CANIF_PRV_MAX_BUFFER_SIZE       8u
#endif

#define CANIF_RESET                             FALSE

#define CANIF_READ_NOTIFSTATUS                  0x10

#define CANIF_READ_DATA                         0x01

#define CANIF_READ_NOTIFSTATUS_DATA             0x11

#define CANIF_READ_NONE                         0x00

#define CANIF_STATIC                           (PduIdType)(((uint32)1u << (uint8)((uint8)8u * (uint8)sizeof(PduIdType)))-1u)

#define CANIF_MSB_BIT_RESET                 0x3FFFFFFFu

#define CANIF_CANID_BIT_SHIFT                           30u

#define CANIF_ZERO                 0u

#define CANIF_ONE                 1u

#define CANIF_TWO                 2u

#define CANIF_THREE                 3u

#define CANIF_FOUR                  4u

//T:#define DLC_8                       8u

//T:#define DLC_64                      64u

#if (CANIF_METADATA_SUPPORT != STD_OFF)

#define SHIFT_8                     8u

#define CANID_SIZE_STD              2u

#define CANID_SIZE_XTD              4u

#define CANIF_CANID_MASK         0x0000FFFFU

#define SDU_DATA_BUFF_SIZE       68u

#endif

#define CANID_MASK_DEFAULT       0x1FFFFFFFU

#define CANIF_PRV_CANIF_2MSB_MASK                0xC0000000u

#define CANIF_PRV_MSB_BIT_RESET                  0x3FFFFFFFu

#define CANIF_MSB_BIT_RESET_STD                 0x3FFFu

#define CANIF_GET_ONE_BYTE                 0x00ffu

#if CANIF_PUBLIC_DEV_ERROR_DETECT != STD_OFF

    #define CANIF_DET_REPORT_ERROR(CONDITION, API, ERROR)                                                       \
                                   if(CONDITION)                                                                \
                                   {                                                                            \
                                        (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                   }

    #define CANIF_DET_REPORT_ERROR_NOT_OK(CONDITION, API, ERROR)                                                   \
                                   if(CONDITION)                                                                \
                                   {                                                                            \
                                       (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                        return E_NOT_OK;                                                        \
                                   }

#if ((CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF) || (CANIF_READRXPDU_NOTIFY_STATUS_API != STD_OFF)          \
                                                                       ||(CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF))
        #define CANIF_DET_REPORT_ERROR_NO_NOTIF(CONDITION, API, ERROR)                                          \
                                   if(CONDITION)                                                                \
                                   {                                                                            \
                                       (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                        return CANIF_NO_NOTIFICATION;                                           \
                                   }
    #endif

       #define CANIF_DET_REPORT_ERROR_VOID_RET(CONDITION, API, ERROR)                                                  \
                                   if(CONDITION)                                                                \
                                   {                                                                            \
                                       (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                       return;                                                                       \
                                   }

    #define CANIF_DET_REPORT_ERROR_SCHM_EXIT_NOK(CONDITION, API, ERROR, SCHM_EXIT_FUNC)                               \
                                    if(CONDITION)                                                                     \
                                    {                                                                                 \
                                        (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                         \
                                        SCHM_EXIT_FUNC();                                                             \
                                        return E_NOT_OK;                                                              \
                                    }

#define CANIF_DET_REPORT_ERROR_NOR(API, ERROR)  (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));

#else

#define CANIF_DET_REPORT_ERROR_NOT_OK(CONDITION, API, ERROR)

 #define CANIF_DET_REPORT_ERROR_VOID_RET(CONDITION, API, ERROR)

#define CANIF_DET_REPORT_ERROR(CONDITION, API, ERROR)

    #define CANIF_DET_REPORT_ERROR_NOK(CONDITION, API, ERROR)

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF || CANIF_READRXPDU_NOTIFY_STATUS_API != STD_OFF          \
                                                            || CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
        #define CANIF_DET_REPORT_ERROR_NO_NOTIF(CONDITION, API, ERROR)
    #endif

    #define CANIF_DET_REPORT_ERROR_SCHM_EXIT_NOK(CONDITION, API, ERROR, SCHM_EXIT_FUNC)
#endif

#if (CANIF_CFG_TRCV_DRV_SUPPORT != STD_OFF)

#define CANIF_START_SEC_CONST_8
#include "CanIf_MemMap.h"
extern CONST (uint8, CANIF_CONST) CanIf_Trcv_LUT[CANIF_NUM_TRANSCEIVERS];
#define CANIF_STOP_SEC_CONST_8
#include "CanIf_MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_Lok_ReadRxBuffer(P2VAR (PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr,
        P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfgPtr);

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_Lok_BufferInit(void);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Lok_WriteTxBuffer
                                        (VAR(PduIdType, AUTOMATIC) CanIfTxSduId,
                                         VAR(Can_PduType, AUTOMATIC) Pdu);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Lok_ReadTxBuffer(
                                    P2CONST(CanIf_Cfg_TxBufferConfig_tst, AUTOMATIC, CANIF_APPL_CONST) CanIf_TxBufferConfig,
                                    P2VAR(Can_PduType,AUTOMATIC, CANIF_APPL_DATA) Pdu);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(void , CANIF_CODE) CanIf_Lok_ClearTxChannelBuffer(VAR(uint8, AUTOMATIC)ControllerId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif

#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

extern FUNC(void, CANIF_CODE) CanIf_Lok_WriteRxBuffer(P2CONST (uint8, AUTOMATIC, CANIF_APPL_CONST) CanSduPtr,
                                                P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_APPL_CONST) RxPduCfg_pcst,
                                                CONST(PduLengthType,AUTOMATIC)CanDlc, CONST(Can_IdType,AUTOMATIC)CanId
                                                );

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

//T:remove comment

#if (CANIF_VARIANT_INFO ==3)

LOCAL_INLINE VAR(boolean, AUTOMATIC) CanIf_CompareVersionInfo(
                                                               P2CONST(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_CONST) srcVersionInfo,
                                                               P2CONST(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_CONST) destVersionInfo
                                                              );

LOCAL_INLINE VAR(boolean, AUTOMATIC) CanIf_CompareVersionInfo(
                                                                P2CONST(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_CONST) srcVersionInfo,
                                                                P2CONST(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_CONST) destVersionInfo
                                                              )
{
    VAR(boolean, AUTOMATIC)   stEqual_b;
    stEqual_b = TRUE;
    if ((srcVersionInfo->vendorID == destVersionInfo->vendorID) &&
        (srcVersionInfo->moduleID == destVersionInfo->moduleID) &&
        (srcVersionInfo->sw_major_version == destVersionInfo->sw_major_version) &&
        (srcVersionInfo->sw_minor_version == destVersionInfo->sw_minor_version) &&
        (srcVersionInfo->sw_patch_version == destVersionInfo->sw_patch_version)
    )
    {
        stEqual_b = FALSE;
    }
    return stEqual_b;
}

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

extern FUNC(void, CANIF_CODE)  CanIfAppl_IncompatibleGenerator(void);

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_XCore_Init(P2CONST (CanIf_XCore_ConfigType, AUTOMATIC, CANIF_APPL_CONST) Config_pcst);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_XCore_PipeWrite(uint16 PipeId, CanIf_XCore_PipeTxRxParams_st* params_pst);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_XCore_PipeRead(uint16 PipeId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(void , CANIF_CODE) CanIf_XCore_ClearPipes(VAR(uint8, AUTOMATIC)ControllerId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_XCore_LocalCore_Transmit(
                                                           VAR(PduIdType,AUTOMATIC) CanIfTxSduId,
                                                           P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr
                                                          );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_TxConfirmation(P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_TxPduConfig_pst);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_RxIndication(P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_RXPduConfig_pst,
                                                                    P2CONST(PduInfoType, AUTOMATIC, CANIF_CFG_CONST) CanIf_ULPduinfo_pst);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern P2CONST(Type_CfgEcuabCanIf_st, AUTOMATIC, AUTOMATIC) CanIf_Lok_ConfigSet_tpst;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#endif
