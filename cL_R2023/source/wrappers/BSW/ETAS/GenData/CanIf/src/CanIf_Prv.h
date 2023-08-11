

#ifndef CANIF_PRV_H
#define CANIF_PRV_H

#include "CanIf.h"

#include "CanIf_Cbk.h"

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

typedef struct{
    uint8 Ctrl_Pdu_mode;
#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
    CanIf_NotifStatusType       CanIf_TxCnfmStatus;
#endif
}CanIf_ControllerStateType;

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)

#define CANIF_START_SEC_VAR_CLEARED_32
#include "CanIf_MemMap.h"
extern uint32 CanIf_DynTxPduCanId_au32[];
#define CANIF_STOP_SEC_VAR_CLEARED_32
#include "CanIf_MemMap.h"

#endif

#if(CANIF_CFG_TRCV_WAKEUP_SUPPORT== STD_ON)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
extern const CanIf_Wakeup CanIf_WakeupList_tacst[CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
#endif

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern CanIf_ControllerStateType CanIf_Lok_ControllerState_ast[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern boolean CanIf_Lok_InitStatus_b;
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#if(CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC)
#define CANIF_START_SEC_CONST_UNSPECIFIED
#else
#define CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#endif
#include "CanIf_MemMap.h"
extern const CanIf_CallbackFuncType CanIf_Callback;
#if(CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PC)
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#else
#define CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#endif
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern CanIf_NotifStatusType CanIf_Lok_TxNotification_aen[];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"
extern CanIf_NotifStatusType CanIf_Lok_RxNotification_taen[CANIF_CFG_NUM_CANRXPDUIDS];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.h"


#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
#define CANIF_INIT_SID                           0x01
#define CANIF_DEINIT_SID                         0x02
#define CANIF_SET_CONTROLLER_SID                 0x03
#define CANIF_GET_CONTROLLER_SID                 0x04
#define CANIF_TRANSMIT_SID                       0x05
#define CANIF_READ_RX_PDU_DATA_SID               0x06
#define CANIF_READ_TX_NOTIF_STATUS_SID           0x07
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
#endif

#define CANIF_PRV_INVALID_CHANNEL_MODE                0u
#define CANIF_PRV_VALID_CHANNEL_MODE                1u
#define CANIF_PRV_WAKEUP_MODE                       2u
#define CANIF_PRV_CANID_TYPE_MASK                0x0fu
#define CANIF_PRV_FOUR                           4u
#define CANIF_PRV_SIX                             6u
#define CANIF_PRV_SEVEN                           7u
#define CANIF_PRV_EIGHT                           8u
#define CANIF_INVALID_ID      0xffffu
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
#define CANIF_Ctrl_BIT_SHIFT                            4u
#define BIT_MASK_CTRL_MODE                              0X0Fu
#define BIT_MASK_PDU_MODE                               0XF0u
#define CANIF_ZERO                 0u
#define CANIF_ONE                 1u
#define CANIF_TWO                 2u
#define CANIF_THREE                 3u
#define CANIF_FOUR                  4u

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

#define CANIF_DET_REPORT_ERROR_NO_CONDITON(API, ERROR)                                                       \
                                   {                                                                        \
                                    (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));     \
                                        return E_NOT_OK;                                                             \
                                   }

    #define CANIF_DET_REPORT_ERROR_NOT_OK(CONDITION, API, ERROR)                                                   \
                                   if(CONDITION)                                                                \
                                   {                                                                            \
                                       (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                        return E_NOT_OK;                                                        \
                                   }

        #define CANIF_DET_REPORT_ERROR_NO_NOTIF(CONDITION, API, ERROR)                                          \
                                   if(CONDITION)                                                                \
                                   {                                                                            \
                                       (void)Det_ReportError((CANIF_MODULE_ID), (CANIF_INSTANCE_ID), (API), (ERROR));\
                                        return CANIF_NO_NOTIFICATION;                                           \
                                   }

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
#define CANIF_DET_REPORT_ERROR_NO_CONDITON(API, ERROR)
#define CANIF_DET_REPORT_ERROR_NO_NOTIF(CONDITION, API, ERROR)
#define CANIF_DET_REPORT_ERROR_SCHM_EXIT_NOK(CONDITION, API, ERROR, SCHM_EXIT_FUNC)
#endif

#if (CANIF_CFG_TRCV_DRV_SUPPORT != STD_OFF)

#define CANIF_START_SEC_CONST_8
#include "CanIf_MemMap.h"
extern const uint8 CanIf_Trcv_LUT[CANIF_NUM_TRANSCEIVERS];
#define CANIF_STOP_SEC_CONST_8
#include "CanIf_MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
void CanIf_Lok_ReadRxBuffer(PduInfoType * PduInfoPtr,
        const CanIf_Cfg_RxPduType_tst * RxPduCfgPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"


#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_XCore_LocalCore_Transmit(
                                                           PduIdType CanIfTxSduId,
                                                           const PduInfoType * CanIfTxInfoPtr
                                                          );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern Std_ReturnType CanIf_XCore_LocalCore_TxConfirmation(const CanIf_Cfg_TxPduConfig_tst * CanIf_TxPduConfig_pst);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
extern Std_ReturnType CanIf_XCore_LocalCore_RxIndication(const CanIf_Cfg_RxPduType_tst * CanIf_RXPduConfig_pst,
                                                                    const PduInfoType * CanIf_ULPduinfo_pst);

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif
