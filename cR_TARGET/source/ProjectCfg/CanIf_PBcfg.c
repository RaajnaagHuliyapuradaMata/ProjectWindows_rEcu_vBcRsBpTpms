/******************************************************************************/
/* File   : CanIf_PBcfg.c                                                     */
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
#include "Std_Types.hpp"

#include "CfgEcuabCanIf.hpp"
#include "CanIf_Prv.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_1       0
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_2       1
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_3       2
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_4       3
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_5       4
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_6       5
#define CanConf_CanController_Can_Network_CANNODE_0                           0u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.hpp"
static CONST(CanIf_Cfg_CtrlConfig_tst, CANIF_CONST) CanIf_CtrlGen_a[] = {
   {0, CanConf_CanController_Can_Network_CANNODE_0, FALSE}
};

static CONST(CanIf_Cfg_HthConfig_tst, CANIF_CONST) CanIf_HthGen_a[] = {
      {&CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_CANNODE_0], CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_1, CANIF_FULL}
   ,  {&CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_CANNODE_0], CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_2, CANIF_FULL}
   ,  {&CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_CANNODE_0], CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_3, CANIF_FULL}
   ,  {&CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_CANNODE_0], CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_4, CANIF_FULL}
   ,  {&CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_CANNODE_0], CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_5, CANIF_FULL}
   ,  {&CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_CANNODE_0], CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_6, CANIF_FULL}
};

static CONST(CanIf_Cfg_TxBufferConfig_tst, CANIF_CONST) CanIf_TxBufferGen_a[] = {
      {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_1]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_2]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_3]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_4]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_5]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_CANNODE_0_Tx_Std_MailBox_6]}
};

static CONST(CanIf_Cfg_TxPduConfig_tst, CANIF_CONST) CanIf_TxPduGen_a[] = {
      {&CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_1], CfgEcuabCanIf_dPduTx_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x6DA, FALSE, FALSE, 8u}
   ,  {&CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_3], CfgEcuabCanIf_dPduTx_ApplicationResponse_TPM_Can_Network_CANNODE_0, 1,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x67A, FALSE, FALSE, 8u}
   ,  {&CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_5], CfgEcuabCanIf_dPduTx_HMIPressure_TPM_Can_Network_CANNODE_0,         2,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x530, FALSE, FALSE, 8u}
   ,  {&CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_2], CfgEcuabCanIf_dPduTx_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  3,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x541, FALSE, FALSE, 8u}
   ,  {&CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_4], CfgEcuabCanIf_dPduTx_DiagUdsResp_Physical,                          CanTpConf_CanTpTxNPdu_Phys_CanTp2CanIf, CANIF_STATIC, STANDARD_CAN, CAN_TP, &CanTp_TxConfirmation,     0x77A, FALSE, FALSE, 8u}
   ,  {&CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_CANNODE_0_Tx_Std_MailBox_6], CfgEcuabCanIf_dPduTx_TPMS_Software_ID_TPM_Can_Network_CANNODE_0,    5,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x53A, FALSE, FALSE, 8u}
};

static CONST(CanIf_Cfg_Hrhtype_tst, CANIF_CONST) CanIf_Lok_HrhConfig_tacst[11] = {
      {CANIF_PRV_FULL_E, 0u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 1u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 2u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 3u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 4u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 5u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 6u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 7u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 8u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 9u,  1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 10u, 1u, FALSE, 0u}
};

static CONST(CanIf_Cfg_RxPduType_tst, CANIF_CONST) CanIf_Lok_RxPduConfig_tacst[11] = {
      {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 1594u, 0,  PduRConf_PduRSrcPdu_ApplicationRequest_TPM_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 520u,  1,  PduRConf_PduRSrcPdu_BCM_peripheralMasterClock_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 521u,  2,  PduRConf_PduRSrcPdu_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 2u, 0x20u, 1u, 1850u, 3,  CanTpConf_CanTpRxNPdu_Phys_CanIf2CanTp}
   ,  {CANIF_READ_NOTIFSTATUS, 2u, 0x20u, 1u, 2015u, 4,  CanTpConf_CanTpRxNPdu_Func_CanIf2CanTP}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 522u,  5,  PduRConf_PduRSrcPdu_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 523u,  6,  PduRConf_PduRSrcPdu_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 789u,  7,  PduRConf_PduRSrcPdu_TMM_Status_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 768u,  8,  PduRConf_PduRSrcPdu_RdcData_TPM_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 528u,  9,  PduRConf_PduRSrcPdu_VehSts_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR}
   ,  {CANIF_READ_NOTIFSTATUS, 6u, 0x20u, 8u, 816u,  10, PduRConf_PduRSrcPdu_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR}
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.hpp"

static CONST(uint16, CANIF_CONST) CanIf_CFG_HrhIdMapping_au16[]   = {
      0
   ,  1
   ,  2
   ,  3
   ,  4
   ,  5
   ,  6
   ,  7
   ,  8
   ,  9
   ,  10
   ,  INVALID_ID
   ,  INVALID_ID
   ,  INVALID_ID
   ,  INVALID_ID
   ,  INVALID_ID
};

static CONST(uint16, CANIF_CONST) CanIf_CFG_RxPduIdMapping_au16[] = {
      0
   ,  1
   ,  2
   ,  3
   ,  4
   ,  5
   ,  6
   ,  7
   ,  8
   ,  9
   ,  10
};

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.hpp"
static CONST(CanIf_RxCbk_Prototype, CANIF_CONST) CanIf_Lok_ULName_ta__fct[] = {
      {NULL_PTR}
   ,  {NULL_PTR}
   ,  {&CanTp_RxIndication}
   ,  {NULL_PTR}
   ,  {NULL_PTR}
   ,  {NULL_PTR}
   ,  {&PduR_CanIfRxIndication}
   ,  {NULL_PTR},
};

CONST(CanIf_CallbackFuncType, CANIF_CONST) CanIf_Callback = {
      &CanSM_ControllerBusOff
   ,  &CanSM_ControllerModeIndication,
};

static CONST(uint16, CANIF_CONST) CanIf_TxPduId_MappingTable[] = {
      0
   ,  1
   ,  2
   ,  3
   ,  4
   ,  5
};

static CONST(uint8, CANIF_CONST) CanIf_CtrlId_MappingTable[] = {
   0
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "CanIf_MemMap.hpp"
CONST(Type_CfgEcuabCanIf_st, CANIF_CONST) CfgEcuabCanIf_st = {
      CanIf_Lok_HrhConfig_tacst
   ,  CanIf_Lok_RxPduConfig_tacst
   ,  11u
   ,  1
   ,  0
   ,  &CanIf_CFG_RxPduIdMapping_au16[0]
   ,  &CanIf_CFG_HrhIdMapping_au16[0]
   ,  0
   ,  &CanIf_TxPduGen_a[0u]
   ,  &CanIf_TxBufferGen_a[0u]
   ,  &CanIf_CtrlGen_a[0u]
   ,  6
   ,  6
   ,  &CanIf_TxPduId_MappingTable[0]
   ,  &CanIf_CtrlId_MappingTable[0]
   ,  &CanIf_Lok_ULName_ta__fct[0]
};
#define CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "CanIf_MemMap.hpp"

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

