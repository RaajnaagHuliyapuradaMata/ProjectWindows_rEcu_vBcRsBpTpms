#pragma once
/******************************************************************************/
/* File   : CanIf_Cfg.hpp                                                     */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Types_EcuabCanIf.hpp"
#include "CfgEcuabCanIf.hpp"
#include "EcuM_Cbk.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANIF_READRXPDU_NOTIFY_STATUS_API                                STD_ON
#define CANIF_READTXPDU_NOTIFY_STATUS_API                                STD_ON
#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API                         STD_ON
#define CANIF_CFG_UL_RX                                                  STD_ON
#define CANIF_CANSM_ENABLED                                              STD_ON
#define CANIF_CANTP_ENABLED                                              STD_ON
#define CANIF_PDUR_ENABLED                                               STD_ON
#define CANIF_ECUM_ENABLED                                               STD_ON
#define CANIF_METADATA_SUPPORT                                           STD_OFF
#define CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT                           STD_OFF
#define CANIF_TRIGGERTRANSMIT_SUPPORT                                    STD_OFF
#define CANIF_TXOFFLINEACTIVE_SUPPORT                                    STD_OFF
#define CANIF_SET_BAUDRATE_API                                           STD_OFF
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT                             STD_OFF
#define CANIF_PUBLIC_BUSOFF_RECOVERY_FROM_RXINDICATION                   STD_OFF
#define CANIF_DIRECT_HW_WRITE                                            STD_OFF
#define CANIF_PUBLIC_DEV_ERROR_DETECT                                    STD_OFF
#define CANIF_READMSGID_API                                              STD_OFF
#define CANIF_USER_TXBUFCLEARNOTIFY_API                                  STD_OFF
#define CANIF_ERROR_PASSIVE_SUPPORT                                      STD_OFF
#define CANIF_CTRL_WAKEUP_SUPPORT                                        STD_OFF
#define CANIF_TRCV_WAKEUP_SUPPORT                                        STD_OFF
#define CANIF_CFG_TRCV_DRV_SUPPORT                                       STD_OFF
#define CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_API                         STD_OFF
#define CANIF_PUBLIC_VERSIONINFO_API                                     STD_OFF
#define CANIF_PUBLIC_SETDYNAMICTXID_API                                  STD_OFF
#define CANIF_RB_CHANGERXPDUID_API                                       STD_OFF
#define CANIF_PUBLIC_TXBUFFERING                                         STD_OFF
#define CANIF_PUBLIC_READRXPDU_DATA_API                                  STD_OFF
#define CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT                     STD_OFF
#define CANIF_WAKEUP_SUPPORT                                             STD_OFF
#define CANIF_CFG_READRXPDU_DATA_IN_RXPDUS                               STD_OFF
#define CANIF_CFG_USER_RX_ENABLED                                        STD_OFF
#define CANIF_CFG_TRCV_DRV_SUPPORT                                       STD_OFF
#define CANIF_CFG_TRCV_WAKEUP_SUPPORT                                    STD_OFF
#define CANIF_CFG_TRCV_PN_SUPPORT                                        STD_OFF
#define CANIF_CANNM_TXID_FILTER                                          STD_OFF
#define CANIF_RB_READMSGID_API                                           STD_OFF
#define CANIF_RB_ERROR_PASSIVE_SUPPORT                                   STD_OFF
#define CANIF_RB_CALIBRATION                                             STD_OFF
#define CANIF_RB_NODE_CALIBRATION                                        STD_OFF
#define CANIF_CFG_DLC_CHECK                                              STD_OFF
#define CANIF_FD_SUPPORT                                                 STD_OFF
#define CANIF_LITE_CONFIGURATION                                         STD_OFF
#define CANIF_USER_TP_TX_OFFLINE_MODE                                    STD_OFF
#define CANIF_PUBLIC_PN_SUPPORT                                          STD_OFF
#define CANIF_CANNM_TXID_FILTER                                          STD_OFF
#define CANIF_CANNM_ENABLED                                              STD_OFF
#define CANIF_J1939NM_ENABLED                                            STD_OFF
#define CANIF_CANTSYN_ENABLED                                            STD_OFF
#define CANIF_CDD_RX_ENABLED                                             STD_OFF
#define CANIF_USER_RX_ENABLED                                            STD_OFF
#define CANIF_CDD_TX_ENABLED                                             STD_OFF
#define CANIF_USER_TX_ENABLED                                            STD_OFF
#define CANIF_XCP_ENABLED                                                STD_OFF
#define CANIF_J1939TP_ENABLED                                            STD_OFF
#define CANIF_PUBLIC_WAKEUP_CHECK_VALID_BY_NM                            STD_OFF
#define CANIF_BASIC_CAN_SUPPORT                                          STD_OFF
#define CANIF_BASIC_CAN_SUPPORT_LIST                                     STD_OFF
#define CANIF_RXPDU_CANID_RANGE                                          STD_OFF
#define CANIF_VENDOR_ID                                                       1u
#define CANIF_MODULE_ID                                                      60u
#define CANIF_AR_RELEASE_MAJOR_VERSION                                        4u
#define CANIF_AR_RELEASE_MINOR_VERSION                                        2u
#define CANIF_AR_RELEASE_REVISION_VERSION                                     2u
#define CANIF_SW_MAJOR_VERSION                                                6u
#define CANIF_SW_MINOR_VERSION                                                0u
#define CANIF_SW_PATCH_VERSION                                                0u
#define CANIF_CFG_VAR_PC                                                       1
#define CANIF_CFG_VAR_PBS                                                      2
#define CANIF_CONFIGURATION_VARIANT                             CANIF_CFG_VAR_PC
#define CANIF_TOTAL_TXPDUS                                                    5u
#define CANIF_TOTAL_TXBUFFERS                                                 5u
#define CANIF_TOTAL_CTRLS                                                     1u
#define CANIF_TOTAL_DYNAMIC_PDUS                                              0u
#define CANIF_RX_DYNAMIC_PDUS                                                 0u
#define CANIF_NUM_TRANSCEIVERS                                                 0
#define CANIF_MAX_PDU_INDEX                                              0xFFFFu
#define CanIf_CFG_Size_Of_CANID                         sizeof(Type_McalCan_tId)
#define CANIF_CFG_NUM_CANRXPDUIDS                                            11u
#define CANIF_CFG_TOTAL_HRH_NUM                                              11u
#define CANIF_CFG_TOTAL_HOH_NUM                                              16u
#define CANIF_CFG_NUM_HRH                                                    11u
#define CANIF_CFG_NUM_CANRXPDUIDS_NOT_USER                                   11u
#define CANIF_CFG_RX_BUFFER_SIZE                                              0u
#define CANIF_CFG_TOTAL_HOH                                                   16
#define CANIF_CFG_NO_OF_TLV                                                    1
#define CANIF_CFG_NUM_TRCVS                                                    0
#define CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT                                      0u
#define CANIF_NUM_CONTROLLERS                                                  1
#define CANIF_TOTAL_RXPDUS                                                    11
#define CANIF_NUM_CUSTID_ENTRIES                                               5
#define CANIF_INSTANCE_ID                                                      1
#define CANIF_VARIANT_INFO                                                     1

#define CfgEcuabCanIf_dPduTx_ApplicationCyclic_TPM_Can_Network_CANNODE_0       0
#define CfgEcuabCanIf_dPduTx_ApplicationResponse_TPM_Can_Network_CANNODE_0     1
#define CfgEcuabCanIf_dPduTx_HMIPressure_TPM_Can_Network_CANNODE_0             2
#define CfgEcuabCanIf_dPduTx_HMITempAndRefPress_TPM_Can_Network_CANNODE_0      3
#define CfgEcuabCanIf_dPduTx_DiagUdsResp_Physical                              4
#define CfgEcuabCanIf_dPduTx_TPMS_Software_ID_TPM_Can_Network_CANNODE_0        5
#define CanIfConf_CanIfCtrlCfg_Can_Network_CANNODE_0                             0
#define CanIfConf_CanIfRxPduCfg_ApplicationRequest_TPM_Can_Network_CANNODE_0     0
#define CanIfConf_CanIfRxPduCfg_BCM_peripheralMasterClock_Can_Network_CANNODE_0  1
#define CanIfConf_CanIfRxPduCfg_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0  2
#define CanIfConf_CanIfRxPduCfg_UDS_Rx_Physical_Can_Network_CANNODE_0            3
#define CanIfConf_CanIfRxPduCfg_UDS_Rx_Functional_Can_Network_CANNODE_0          4
#define CanIfConf_CanIfRxPduCfg_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0   5
#define CanIfConf_CanIfRxPduCfg_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0    6
#define CanIfConf_CanIfRxPduCfg_TMM_Status_BodyLCAN_Can_Network_CANNODE_0        7
#define CanIfConf_CanIfRxPduCfg_RdcData_TPM_Can_Network_CANNODE_0                8
#define CanIfConf_CanIfRxPduCfg_VehSts_BodyLCAN_Can_Network_CANNODE_0            9
#define CanIfConf_CanIfRxPduCfg_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0        10
#define CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_1       0u
#define CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_2       1u
#define CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_3       2u
#define CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_4       3u
#define CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_5       4u
#define CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_6       5u
#define CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_1                 0u
#define CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_2                 1u
#define CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_3                 2u
#define CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_4                 3u
#define CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_5                 4u
#define CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_6                 5u
#define CanIf_Ctrl_CustId_Can_Network_CANNODE_0                                 0u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   P2VAR(uint8, TYPEDEF, CANIF_APPL_DATA) SduDataPtr;
   Type_SwcServiceCom_tLengthPdu          SduLength;
   Type_McalCan_tId                       SduCanId;
}CanIf_Type_SwcServiceCom_stInfoPdu;

typedef struct{
   Type_McalCan_tId           CanId;
   Type_SwcServiceCom_tIdPdu  swPduHandle;
   uint8                      SduLength;
   uint8                      BufferIndex;
}CanIf_Cfg_CanIdBuffer_tst;

enum BufferIdx{
      CanIf_Buffer_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_1_e
   ,  CanIf_Buffer_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_2_e
   ,  CanIf_Buffer_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_3_e
   ,  CanIf_Buffer_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_4_e
   ,  CanIf_Buffer_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_5_e
};

enum HthIdx{
      CanIf_Hth_Can_Network_CANNODE_0_Tx_Std_MailBox_1_e
   ,  CanIf_Hth_Can_Network_CANNODE_0_Tx_Std_MailBox_2_e
   ,  CanIf_Hth_Can_Network_CANNODE_0_Tx_Std_MailBox_3_e
   ,  CanIf_Hth_Can_Network_CANNODE_0_Tx_Std_MailBox_4_e
   ,  CanIf_Hth_Can_Network_CANNODE_0_Tx_Std_MailBox_5_e
};

enum CtrlIdx{
   CanIf_Ctrl_Can_Network_CANNODE_0_e
};

typedef enum{
      CANIF_DLC_OK
   ,  CANIF_DLC_E_FAILED
}CanIf_DlcErrorReturnType;

typedef struct{
   P2FUNC(void, TYPEDEF, User_ControllerBusOff        )(VAR(uint8, AUTOMATIC) ControllerId);
   P2FUNC(void, TYPEDEF, User_ControllerModeIndication)(
         VAR(uint8,     AUTOMATIC) ControllerId
      ,  VAR(Type_EcuabCanIf_eModesController, AUTOMATIC) ControllerMode
   );
}CanIf_CallbackFuncType;

typedef struct{
   P2FUNC(void, TYPEDEF, CddRxIndication)(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC),P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC,CANIF_APPL_CONST));
}CanIf_CddRxCbk_Prototype;

typedef struct{
   P2FUNC(void, TYPEDEF, CanIfRxPduUserRxIndicationUser)(
             VAR(Type_SwcServiceCom_tIdPdu,          AUTOMATIC               ) RxPduTargetId_t
      ,  P2CONST(CanIf_Type_SwcServiceCom_stInfoPdu, TYPEDEF, CANIF_APPL_DATA) ULPduInfoTypUSER_tst
   );
}CanIf_RxUSERCbk_Prototype;

typedef struct{
   P2FUNC(void, CANIF_APPL_CODE, UserTxConfirmation)(Type_SwcServiceCom_tIdPdu TxPduTargetPduId);
}CanIf_TxCbk_Prototype;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
extern CONST(Type_CfgEcuabCanIf_st, CANIF_CONST) CfgEcuabCanIf_st;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR(uint32, CANIF_VAR) CanIf_CustId_Table[];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

