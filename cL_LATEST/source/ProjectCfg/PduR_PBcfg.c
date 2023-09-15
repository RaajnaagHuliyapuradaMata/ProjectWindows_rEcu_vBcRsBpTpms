#pragma once
/******************************************************************************/
/* File   : PduR_PBcfg.c                                                      */
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
#include "PduR_PBcfg.hpp"
#include "PduR_UpIf.hpp"
#include "PduR_LoIf.hpp"
#include "PduR_LoTp.hpp"
#include "PduR_UpTp.hpp"
#include "PduR_Mc.hpp"
#include "PduR_Gw.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)
#define PduR_comToLo   NULL_PTR
#else
static const PduR_RT_UpToLo PduR_comToLo[] = {
      { CanIfConf_CanIfTxPduCfg_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
   ,  { CanIfConf_CanIfTxPduCfg_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
   ,  { CanIfConf_CanIfTxPduCfg_TPMS_Status_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
   ,  { CanIfConf_CanIfTxPduCfg_TPMS_TirePT_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
};
#endif
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
#if defined(PDUR_CONFIG_SINGLE_TPTX_LO)
#define PduR_DcmToLo NULL_PTR
#else
static const PduR_RT_UpToLo PduR_DcmToLo[] = {
   { CanTpConf_CanTpTxNSdu_UdsOnCan_Tx_Phy_PduR2CanTp, (PduR_loTransmitFP)PduR_RF_CanTp_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
};
#endif
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_CanIfRxToUp   NULL_PTR
#else
static const PduR_RT_LoIfRxToUp PduR_CanIfRxToUp[] = {
   { ComConf_ComIPdu_BCM_PowerMode_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_EPOCHTime_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_ODO_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CGW_VehicleSpeed_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
   { ComConf_ComIPdu_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication }
};
#endif
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP )
#define PduR_CanIfTxToUp NULL_PTR
#else
static const PduR_RT_LoIfTxToUp PduR_CanIfTxToUp [] = {
   { ComConf_ComIPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation},
   { ComConf_ComIPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation},
   { ComConf_ComIPdu_TPMS_Status_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation},
   { ComConf_ComIPdu_TPMS_TirePT_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
};
#endif
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
#if defined ( PDUR_CONFIG_SINGLE_TPRX )
#define PduR_CanTpRxToUp   NULL_PTR
#else
static const PduR_RT_LoTpRxToUp PduR_CanTpRxToUp[] = {
   {DcmConf_DcmDslProtocolRx_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication }
   ,  {DcmConf_DcmDslProtocolRx_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication }
};
#endif
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
#if defined(PDUR_CONFIG_SINGLE_TPTX_UP )
#define PduR_CanTpTxToUp NULL_PTR
#else
static const PduR_RT_LoTpTxToUp PduR_CanTpTxToUp [] = {
   { DcmConf_DcmDslProtocolTx_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_Dcm2PduR, (PduR_upTpProvideTxBufFP) PduR_RF_Dcm_CopyTxData,(PduR_upTpTxConfirmationFP) PduR_RF_Dcm_TpTxConfirmation }
};
#endif
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
static const PduR_RPGInfoType PduR_RPGInfo[] = {
   {
     NULL_PTR
   ,    NULL_PTR
   ,    PDUR_RPGID_NULL
   ,    0
   ,    0
   },
};
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
#else
#define PDUR_START_SEC_CONFIG_DATA_8
#endif
#include "PduR_MemMap.hpp"
const boolean PduR_RPG_EnRouting[] =
{
  TRUE,
};
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#else
#define PDUR_STOP_SEC_CONFIG_DATA_8
#endif
#include "PduR_MemMap.hpp"
#endif

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
static const PduR_LoTpConfig PduR_LoTpCfg[] = {
  {
   PduR_CanTpRxToUp
   ,  PduR_CanTpTxToUp
   ,   2
   ,   1
   }
  };
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
static const PduR_LoIfDConfig PduR_LoIfDCfg[] = {
  {
   PduR_CanIfRxToUp
   ,  PduR_CanIfTxToUp
   ,   11
   ,   4
   }
  };
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
static const PduR_UpConfig PduR_UpTpCfg[] = {
  {
   PduR_DcmToLo
   ,   NULL_PTR
   ,   1
   }
  };
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
static const PduR_UpConfig PduR_UpIfCfg[] = {
  {
   PduR_comToLo
   ,   NULL_PTR
   ,   4
   }
  };
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
const PduR_RPTablesType PduR_RoutingPathTables = {
       (const PduR_loTransmitFuncType * )             PduR_loTransmitTable
   ,   (const PduR_loCancelReceiveFuncType * )        PduR_loCancelRxTable
   ,   (const PduR_loCancelTransmitFuncType * )       PduR_loCancelTransmitTable
   ,   (const PduR_upIfRxIndicationFuncType * )       PduR_upIfRxIndicationTable
   ,   (const PduR_upIfTxConfirmationFuncType * )     PduR_upIfTxConfirmationTable
   ,   (const PduR_upTpCopyRxDataFuncType * )         PduR_upTpCopyRxDataTable
   ,   (const PduR_upTpStartOfReceptionFuncType * )   PduR_upTpStartOfReceptionTable
   ,   (const PduR_upTpRxIndicationFuncType * )       PduR_upTpRxIndicationTable
   ,   (const PduR_upTpCopyTxDataFuncType * )         PduR_upTpCopyTxDataTable
   ,   (const PduR_upTpTxConfirmationFuncType * )     PduR_upTpTxConfirmationTable
   ,   (const PduR_upIfTriggerTxFuncType * )          PduR_upIfTriggerTxTable
};
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
const PduR_loTransmitFuncType PduR_loTransmitTable[] = {
   {&CanIf_Transmit}
   ,  {&CanTp_Transmit}
};

const PduR_loCancelReceiveFuncType PduR_loCancelRxTable[] = {
   {NULL_PTR}
};

const PduR_loCancelTransmitFuncType PduR_loCancelTransmitTable[] = {
   {&PduR_invId_UpCancelTransmit}
};

const PduR_upIfRxIndicationFuncType PduR_upIfRxIndicationTable[] = {
   {&Com_RxIndication}
};

const PduR_upIfTxConfirmationFuncType PduR_upIfTxConfirmationTable[] = {
   {&Com_TxConfirmation}
};

const PduR_upIfTriggerTxFuncType PduR_upIfTriggerTxTable[] = {
   {NULL_PTR}
};

const PduR_upTpCopyRxDataFuncType PduR_upTpCopyRxDataTable[] = {
   {&Dcm_CopyRxData}
};

const PduR_upTpStartOfReceptionFuncType PduR_upTpStartOfReceptionTable[] = {
   {&Dcm_StartOfReception}
};

const PduR_upTpRxIndicationFuncType PduR_upTpRxIndicationTable[] = {
   {&Dcm_TpRxIndication}
};

const PduR_upTpCopyTxDataFuncType PduR_upTpCopyTxDataTable[] = {
   {&Dcm_CopyTxData}
};

const PduR_upTpTxConfirmationFuncType PduR_upTpTxConfirmationTable[] = {
   {&Dcm_TpTxConfirmation}
};
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
const PduR_PBConfigType PduR_GlobalPBConfig = {
      (const PduR_CddConfig *) NULL_PTR
   ,  (const PduR_LoTpConfig *) PduR_LoTpCfg
   ,  (const PduR_LoIfDConfig *) PduR_LoIfDCfg
   ,  (const PduR_LoIfTTConfig *) NULL_PTR
   ,  (const PduR_UpConfig *) PduR_UpIfCfg
   ,  (const PduR_UpConfig *) PduR_UpTpCfg
   ,  (const PduR_MT_UpToLo *) NULL_PTR
   ,  (const PduR_MT_LoIfTxToUp *) NULL_PTR
   ,  (const PduR_MT_LoTpTxToUp *) NULL_PTR
   ,  (PduR_MS_LoTpTxToUp *) NULL_PTR
   ,  (const PduR_GT_IfTx *) NULL_PTR
   ,  (const PduR_GT_If *) NULL_PTR
   ,  (const PduR_GT_Tp *) NULL_PTR
   ,  (const PduR_RPG_LoTpRxToUp *) NULL_PTR
   ,  (const PduR_RPTablesType * ) &PduR_RoutingPathTables
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
   ,  (const PduR_GwTp_SessionListType * ) NULL_PTR
#endif
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT != 0)
   ,  (const PduR_UpIfTxConf_Config * ) PduR_UpIfTxConf_ConfigList
#endif
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
   ,  (const PduR_RPGInfoType * )        PduR_RPGInfo
   ,  (const boolean * )   PduR_RPG_EnRouting
   ,  (boolean * )  PduR_RPG_Status
   ,  (PduR_RoutingPathGroupIdType) 0
#endif
   ,  (const PduR_UpTpToLoTpRxConfig *) NULL_PTR
   ,  0
   ,  0
   ,  0
   ,  (Type_SwcServiceCom_tIdPdu) 0
};
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"
const Type_CfgSwcServicePduR_st CfgSwcServicePduR_cst = {
   NULL_PTR
   ,   NULL_PTR
};
#if( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif
#include "PduR_MemMap.hpp"

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

