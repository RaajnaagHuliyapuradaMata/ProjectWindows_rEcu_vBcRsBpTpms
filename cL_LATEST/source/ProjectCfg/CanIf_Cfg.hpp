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
#include "EcuM_Cbk.hpp"
#include "CanIf_Types.hpp"
#include "Can.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANIF_CFG_UL_RX                                                  STD_ON
#define CANIF_CANSM_ENABLED                                              STD_ON
#define CANIF_CANTP_ENABLED                                              STD_ON
#define CANIF_PDUR_ENABLED                                               STD_ON
#define CANIF_ECUM_ENABLED                                               STD_ON
#define CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT                           STD_OFF
#define CANIF_TXOFFLINEACTIVE_SUPPORT                                    STD_OFF
#define CANIF_SET_BAUDRATE_API                                           STD_OFF
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT                             STD_OFF
#define CANIF_PUBLIC_BUSOFF_RECOVERY_FROM_RXINDICATION                   STD_OFF
#define CANIF_DIRECT_HW_WRITE                                            STD_OFF
#define CANIF_PUBLIC_DEV_ERROR_DETECT                                    STD_OFF
#define CANIF_PUBLIC_VERSIONINFO_API                                     STD_OFF
#define CANIF_PUBLIC_SETDYNAMICTXID_API                                  STD_OFF
#define CANIF_WAKEUP_SUPPORT                                             STD_OFF
#define CANIF_CFG_READRXPDU_DATA_IN_RXPDUS                               STD_OFF
#define CANIF_CFG_TRCV_DRV_SUPPORT                                       STD_OFF
#define CANIF_CFG_TRCV_WAKEUP_SUPPORT                                    STD_OFF
#define CANIF_CFG_TRCV_PN_SUPPORT                                        STD_OFF
#define CANIF_RB_ERROR_PASSIVE_SUPPORT                                   STD_OFF
#define CANIF_CFG_DLC_CHECK                                              STD_OFF
#define CANIF_FD_SUPPORT                                                 STD_OFF
#define CANIF_LITE_CONFIGURATION                                         STD_OFF
#define CANIF_USER_TP_TX_OFFLINE_MODE                                    STD_OFF
#define CANIF_CANNM_ENABLED                                              STD_OFF
#define CANIF_J1939NM_ENABLED                                            STD_OFF
#define CANIF_CANTSYN_ENABLED                                            STD_OFF
#define CANIF_XCP_ENABLED                                                STD_OFF
#define CANIF_J1939TP_ENABLED                                            STD_OFF
#define CANIF_PUBLIC_WAKEUP_CHECK_VALID_BY_NM                            STD_OFF
#define CANIF_BASIC_CAN_SUPPORT                                          STD_OFF
#define CANIF_BASIC_CAN_SUPPORT_LIST                                     STD_OFF
#define CANIF_RXPDU_CANID_RANGE                                          STD_OFF

#define CANIF_VENDOR_ID                                                       6u
#define CANIF_MODULE_ID                                                      60u
#define CANIF_AR_RELEASE_MAJOR_VERSION                                        4u
#define CANIF_AR_RELEASE_MINOR_VERSION                                        2u
#define CANIF_AR_RELEASE_REVISION_VERSION                                     2u
#define CANIF_SW_MAJOR_VERSION                                                9u
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
#define CANIF_CFG_NUM_CANRXPDUIDS                                            13u
#define CANIF_CFG_TOTAL_HOH_NUM                                              18u
#define CANIF_CFG_RX_BUFFER_SIZE                                              0u
#define CANIF_CFG_NO_OF_TLV                                                    1
#define CANIF_CFG_NUM_TRCVS                                                    0
#define CANIF_CFG_NO_TRCV_WAKEUP_SUPPORT                                      0u
#define CANIF_NUM_CONTROLLERS                                                  1
#define CANIF_INSTANCE_ID                                                      0
#define CanIfConf_CanIfTxPduCfg_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0              0
#define CanIfConf_CanIfTxPduCfg_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0            1
#define CfgEcuabCanIf_PduTxDiagUdsResp_Physical                                             2
#define CanIfConf_CanIfTxPduCfg_TPMS_Status_Can_Network_0_CANNODE_0                         3
#define CanIfConf_CanIfTxPduCfg_TPMS_TirePT_Can_Network_0_CANNODE_0                         4
#define CanIfConf_CanIfCtrlCfg_Can_Network_0_CANNODE_0                                      0
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0             0
#define CanIfConf_CanIfRxPduCfg_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0            1
#define CanIfConf_CanIfRxPduCfg_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0                 2
#define CanIfConf_CanIfRxPduCfg_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0                   3
#define CanIfConf_CanIfRxPduCfg_CGW_ODO_Can_Network_0_CANNODE_0                             4
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0                5
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0                    6
#define CanIfConf_CanIfRxPduCfg_CGW_VehicleSpeed_Can_Network_0_CANNODE_0                    7
#define CanIfConf_CanIfRxPduCfg_BCM_PowerMode_Can_Network_0_CANNODE_0                       8
#define CanIfConf_CanIfRxPduCfg_CGW_EPOCHTime_Can_Network_0_CANNODE_0                       9
#define CanIfConf_CanIfRxPduCfg_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0                   10
#define CanIfConf_CanIfRxPduCfg_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0 11
#define CanIfConf_CanIfRxPduCfg_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0                  12

#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1   0u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2   1u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3   2u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4   3u
#define CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5   4u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1             0u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2             1u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3             2u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4             3u
#define CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5             4u
#define CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0                             0u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   P2VAR(uint8, TYPEDEF, CANIF_APPL_DATA) SduDataPtr;
   Type_SwcServiceCom_tLengthPdu                          SduLength;
   Can_IdType                             SduCanId;
}CanIf_Type_SwcServiceCom_stInfoPdu;

typedef struct{
   Can_IdType CanId;
   Type_SwcServiceCom_tIdPdu  swPduHandle;
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
   CANIF_DLC_OK = 0
   ,  CANIF_DLC_E_FAILED
}CanIf_DlcErrorReturnType;

typedef struct{
   P2FUNC(void, TYPEDEF, User_ControllerBusOff        )(VAR(uint8, AUTOMATIC) ControllerId);
   P2FUNC(void, TYPEDEF, User_ControllerModeIndication)(
         VAR(uint8,     AUTOMATIC) ControllerId
      ,  VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
   );
}CanIf_CallbackFuncType;

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

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

