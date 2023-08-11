#ifndef  CANIF_CFG_H
#define  CANIF_CFG_H

#include "EcuM_Cbk.h"
#include "CanIf_Types.h"
#include   "Can.h"

#define CANIF_VENDOR_ID                          6u
#define CANIF_MODULE_ID                          60u
#define CANIF_AR_RELEASE_MAJOR_VERSION           4u
#define CANIF_AR_RELEASE_MINOR_VERSION           2u
#define CANIF_AR_RELEASE_REVISION_VERSION        2u
#define CANIF_SW_MAJOR_VERSION                   9u
#define CANIF_SW_MINOR_VERSION                   0u
#define CANIF_SW_PATCH_VERSION                   0u

#if (!defined(CAN_AR_RELEASE_MAJOR_VERSION) || (CAN_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CAN_AR_RELEASE_MINOR_VERSION) || (CAN_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define CANIF_CFG_VAR_PC                                1
#define CANIF_CFG_VAR_PBS                               2
#define CANIF_CONFIGURATION_VARIANT         CANIF_CFG_VAR_PC
#define CANIF_TOTAL_TXPDUS      5u
#define CANIF_TOTAL_TXBUFFERS   5u
#define CANIF_TOTAL_CTRLS       1u
#define CANIF_TOTAL_DYNAMIC_PDUS 0u
#define CANIF_RX_DYNAMIC_PDUS 0u
#define CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT  STD_OFF
#define CANIF_TXOFFLINEACTIVE_SUPPORT             STD_OFF
#define CANIF_SET_BAUDRATE_API                  STD_OFF
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT        STD_OFF
#define CANIF_PUBLIC_BUSOFF_RECOVERY_FROM_RXINDICATION        STD_OFF
#define CANIF_DIRECT_HW_WRITE               STD_OFF
#define CANIF_PUBLIC_DEV_ERROR_DETECT                        STD_OFF
#define CANIF_NUM_TRANSCEIVERS                        0
#define CANIF_PUBLIC_VERSIONINFO_API                     STD_OFF
#define CANIF_PUBLIC_SETDYNAMICTXID_API                 STD_OFF
#define CANIF_WAKEUP_SUPPORT                    STD_OFF
#define CANIF_CFG_NUM_CANRXPDUIDS                     13u
#define CANIF_CFG_TOTAL_HOH_NUM                     18u
#define CANIF_CFG_RX_BUFFER_SIZE                     0u
#define CANIF_CFG_READRXPDU_DATA_IN_RXPDUS                    STD_OFF
#define CANIF_CFG_UL_RX              STD_ON
#define CANIF_CFG_NO_OF_TLV                    1
#define CANIF_CFG_TRCV_DRV_SUPPORT                    STD_OFF
#define CANIF_CFG_NUM_TRCVS                           0
#define CANIF_CFG_TRCV_WAKEUP_SUPPORT                    STD_OFF
#define CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT                 0u
#define CANIF_CFG_TRCV_PN_SUPPORT                 STD_OFF
#define CANIF_NUM_CONTROLLERS       1
#define CANIF_RB_ERROR_PASSIVE_SUPPORT               STD_OFF
#define CANIF_CFG_DLC_CHECK                         STD_OFF
#define CANIF_FD_SUPPORT                       STD_OFF
#define CANIF_INSTANCE_ID                         0
#define CANIF_LITE_CONFIGURATION                STD_OFF
#define CANIF_USER_TP_TX_OFFLINE_MODE            STD_OFF
#define CANIF_CANNM_ENABLED                     STD_OFF
#define CANIF_CANSM_ENABLED                     STD_ON
#define CANIF_J1939NM_ENABLED                     STD_OFF
#define CANIF_CANTP_ENABLED                     STD_ON
#define CANIF_CANTSYN_ENABLED                    STD_OFF
#define CANIF_PDUR_ENABLED                     STD_ON
#define CANIF_XCP_ENABLED                       STD_OFF
#define CANIF_J1939TP_ENABLED                       STD_OFF
#define CANIF_ECUM_ENABLED                    STD_ON
#define CANIF_PUBLIC_WAKEUP_CHECK_VALID_BY_NM         STD_OFF
#define CANIF_BASIC_CAN_SUPPORT                   STD_OFF
#define CANIF_BASIC_CAN_SUPPORT_LIST            STD_OFF
#define CANIF_RXPDU_CANID_RANGE                    STD_OFF
#define CanIfConf_CanIfTxPduCfg_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0        0
#define CanIfConf_CanIfTxPduCfg_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0        1
#define CanIfConf_CanIfTxPduCfg_TPMS_Diag_Resp_Can_Network_0_CANNODE_0        2
#define CanIfConf_CanIfTxPduCfg_TPMS_Status_Can_Network_0_CANNODE_0        3
#define CanIfConf_CanIfTxPduCfg_TPMS_TirePT_Can_Network_0_CANNODE_0        4
#define CanIfConf_CanIfCtrlCfg_Can_Network_0_CANNODE_0        0
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0        0
#define CanIfConf_CanIfRxPduCfg_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0        1
#define CanIfConf_CanIfRxPduCfg_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0        2
#define CanIfConf_CanIfRxPduCfg_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0        3
#define CanIfConf_CanIfRxPduCfg_CGW_ODO_Can_Network_0_CANNODE_0        4
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0        5
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0        6
#define CanIfConf_CanIfRxPduCfg_CGW_VehicleSpeed_Can_Network_0_CANNODE_0        7
#define CanIfConf_CanIfRxPduCfg_BCM_PowerMode_Can_Network_0_CANNODE_0        8
#define CanIfConf_CanIfRxPduCfg_CGW_EPOCHTime_Can_Network_0_CANNODE_0        9
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0        10
#define CanIfConf_CanIfRxPduCfg_RdcData_TPMS_Can_Network_0_CANNODE_0        11
#define CanIfConf_CanIfRxPduCfg_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0        12

typedef struct{
   uint8*        SduDataPtr;
   PduLengthType SduLength;
   Can_IdType    SduCanId;
}CanIf_PduInfoType;

typedef struct{
   Can_IdType CanId;
   PduIdType  swPduHandle;
   uint8      SduLength;
   uint8      BufferIndex;
}CanIf_Cfg_CanIdBuffer_tst;

typedef enum{
      CanIf_Buffer_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1_e
   ,  CanIf_Buffer_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2_e
   ,  CanIf_Buffer_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3_e
   ,  CanIf_Buffer_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4_e
   ,  CanIf_Buffer_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5_e
}CanIf_BufferIdx;

typedef enum{
   CANIF_DLC_OK = 0,
   CANIF_DLC_E_FAILED
}CanIf_DlcErrorReturnType;

typedef struct{
    #if CANIF_CFG_TRCV_DRV_SUPPORT == STD_ON
    void (*User_TransceiverModeIndication) (uint8 TransceiverId ,CanTrcv_TrcvModeType TransceiverMode);
    #endif

    void (*User_ControllerBusOff) (uint8 ControllerId);
    void (*User_ControllerModeIndication) (uint8 ControllerId,
            CanIf_ControllerModeType ControllerMode);

    #if (CANIF_RB_ERROR_PASSIVE_SUPPORT != STD_OFF)
    void (*User_ControllerErrorPassive) (uint8 ControllerId);
    #endif

    #if (CANIF_CFG_DLC_CHECK != STD_OFF)
    CanIf_DlcErrorReturnType (*Dlc_Error_Notification) (PduIdType PduId_qu8 ,uint8 SduLength);
    #endif
}CanIf_CallbackFuncType;

#if(CANIF_CFG_TRCV_WAKEUP_SUPPORT == STD_ON)
typedef struct{
    uint8 TransceiverId;
    uint8 ControllerId;
    Type_SwcServiceEcuM_tSourceWakeup WakeupSourceId;
}CanIf_Wakeup;
#endif

typedef struct{
    void (*CanIfRxPduUserRxIndicationUser) (PduIdType RxPduTargetId_t , const CanIf_PduInfoType * ULPduInfoTypUSER_tst);
}CanIf_RxUSERCbk_Prototype;

typedef struct{
    void (*UserTxConfirmation) (PduIdType TxPduTargetPduId);
} CanIf_TxCbk_Prototype;

#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1       0u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2       1u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3       2u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4       3u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5       4u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1   0u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2   1u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3   2u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4   3u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5   4u
#define CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0       0u

#endif
