#pragma once
/******************************************************************************/
/* File   : CfgEcuabCanIf.h                                                   */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
//   P2CONST(CanIf_Cfg_Hrhtype_tst,   TYPEDEF,CANIF_CFG_CONST) HrhConfig_pcst;
//   P2CONST(CanIf_Cfg_RxPduType_tst, TYPEDEF,CANIF_CFG_CONST) RxPduConfig_pcst;
//   VAR(PduIdType,                   TYPEDEF)                 NumCanRxPduId_t;
   VAR(uint8,                       TYPEDEF)                 NumCanCtrl_u8;
//   VAR(PduIdType,                   TYPEDEF)                 NumCddRxPdus_t;
   const uint16*                                             RxPduIdTable_Ptr;
   const uint16*                                             HrhPduIdTable_Ptr;
   VAR(uint8,                       TYPEDEF)                 CfgSetIndex_u8;
//   const CanIf_Cfg_TxPduConfig_tst*                          CanIf_TxPduConfigPtr;
//   const CanIf_Cfg_TxBufferConfig_tst*                       CanIf_TxBufferConfigPtr;
//   const CanIf_Cfg_CtrlConfig_tst*                           CanIf_CtrlConfigPtr;
         uint32                                              NumOfTxPdus;
         uint32                                              NumOfTxBuffers;
   const uint16*                                             TxPduIdTable_Ptr;
   const uint8*                                              CtrlIdTable_Ptr;
#if CANIF_CFG_USER_RX_ENABLED == STD_ON
//   const CanIf_RxUSERCbk_Prototype*                          RxUSER_Ptr;
#endif
//   const CanIf_RxCbk_Prototype*                              RxAutosarUL_Ptr;
#if(CANIF_CANNM_TXID_FILTER != STD_OFF)
//    P2CONST(Can_IdType,TYPEDEF,CANIF_CFG_CONST)              NmtxIdPtr;
#endif
#if(CANIF_XCORE_CFG_ENABLED != STD_OFF)
//   P2CONST(CanIf_XCore_ConfigType, TYPEDEF, CANIF_CFG_CONST) CanIf_XCoreConfigPtr;
#endif
}Type_CfgEcuabCanIf_st;

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
