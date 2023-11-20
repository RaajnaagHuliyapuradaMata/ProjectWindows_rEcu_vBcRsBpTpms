#include "Std_Types.hpp"

#include "PduR_PBcfg.hpp"
#include "PduR_UpIf.hpp"
#include "PduR_LoIf.hpp"
#include "PduR_LoTp.hpp"
#include "PduR_UpTp.hpp"
#include "PduR_Mc.hpp"
#include "PduR_Gw.hpp"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.hpp"
static CONST(PduR_RT_UpToLo,PDUR_CONST) PduR_comToLo[] = {
      {CfgEcuabCanIf_dPduTx_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit}
   ,  {CfgEcuabCanIf_dPduTx_ApplicationResponse_TPM_Can_Network_CANNODE_0, (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit}
   ,  {CfgEcuabCanIf_dPduTx_HMIPressure_TPM_Can_Network_CANNODE_0,         (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit}
   ,  {CfgEcuabCanIf_dPduTx_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit}
   ,  {CfgEcuabCanIf_dPduTx_TPMS_Software_ID_TPM_Can_Network_CANNODE_0,    (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit}
};

static CONST(PduR_RT_UpToLo,PDUR_CONST) PduR_DcmToLo[] = {
   {CanTpConf_CanTpTxNSdu_UdsOnCan_Tx_Phy_PduR2CanTp, (PduR_loTransmitFP)PduR_RF_CanTp_Transmit, (PduR_loCancelTransmitFP)PduR_RF_CanTp_CancelTransmit}
};

static CONST( PduR_RT_LoIfRxToUp, PDUR_CONST) PduR_CanIfRxToUp[] = {
      {ComConf_ComIPdu_ApplicationRequest_TPM_Can_Network_CANNODE_0,    (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_BCM_peripheralMasterClock_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,  (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,   (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_RdcData_TPM_Can_Network_CANNODE_0,               (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,       (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_VehSts_BodyLCAN_Can_Network_CANNODE_0,           (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
   ,  {ComConf_ComIPdu_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,        (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication}
 };

static CONST(PduR_RT_LoIfTxToUp, PDUR_CONST) PduR_CanIfTxToUp [] = {
      {ComConf_ComIPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
   ,  {ComConf_ComIPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0, (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
   ,  {ComConf_ComIPdu_HMIPressure_TPM_Can_Network_CANNODE_0,         (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
   ,  {ComConf_ComIPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
};

static CONST(PduR_RT_LoTpRxToUp, PDUR_CONST) PduR_CanTpRxToUp[] = {
      {DcmConf_DcmDslProtocolRx_UDS_Rx_Functional_Can_Network_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception, (PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData, (PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication}
   ,  {DcmConf_DcmDslProtocolRx_UDS_Rx_Physical_Can_Network_CANNODE_0_PduR2Dcm,   (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception, (PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData, (PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication}
};

static CONST(PduR_RT_LoTpTxToUp, PDUR_CONST) PduR_CanTpTxToUp [] = {
   {DcmConf_DcmDslProtocolTx_UDS_Tx_Physical_Can_Network_CANNODE_0_Phys_Dcm2PduR, (PduR_upTpProvideTxBufFP) PduR_RF_Dcm_CopyTxData, (PduR_upTpTxConfirmationFP) PduR_RF_Dcm_TpTxConfirmation}
};

static CONST(PduR_LoTpConfig, PDUR_CONST) PduR_LoTpCfg[] = {
   {
         PduR_CanTpRxToUp
      ,  PduR_CanTpTxToUp
      ,  2
      ,  1
   }
};

static CONST(PduR_LoIfDConfig, PDUR_CONST) PduR_LoIfDCfg[] = {
   {
         PduR_CanIfRxToUp
      ,  PduR_CanIfTxToUp
      ,  9
      ,  4
   }
};

static CONST(PduR_UpConfig, PDUR_CONST) PduR_UpTpCfg[] = {
   {
         PduR_DcmToLo
      ,  NULL_PTR
      ,  1
   }
};

static CONST(PduR_UpConfig, PDUR_CONST) PduR_UpIfCfg[] = {
   {
         PduR_comToLo
      ,  NULL_PTR
      ,  5
   }
};

CONST(PduR_RPTablesType, PDUR_CONST) PduR_RoutingPathTables = {
      (P2CONST(PduR_loTransmitFuncType,           AUTOMATIC, PDUR_CONST)) PduR_loTransmitTable
   ,  (P2CONST(PduR_loCancelReceiveFuncType,      AUTOMATIC, PDUR_CONST)) PduR_loCancelRxTable
   ,  (P2CONST(PduR_loCancelTransmitFuncType,     AUTOMATIC, PDUR_CONST)) PduR_loCancelTransmitTable
   ,  (P2CONST(PduR_upIfRxIndicationFuncType,     AUTOMATIC, PDUR_CONST)) PduR_upIfRxIndicationTable
   ,  (P2CONST(PduR_upIfTxConfirmationFuncType,   AUTOMATIC, PDUR_CONST)) PduR_upIfTxConfirmationTable
   ,  (P2CONST(PduR_upTpCopyRxDataFuncType,       AUTOMATIC, PDUR_CONST)) PduR_upTpCopyRxDataTable
   ,  (P2CONST(PduR_upTpStartOfReceptionFuncType, AUTOMATIC, PDUR_CONST)) PduR_upTpStartOfReceptionTable
   ,  (P2CONST(PduR_upTpRxIndicationFuncType,     AUTOMATIC, PDUR_CONST)) PduR_upTpRxIndicationTable
   ,  (P2CONST(PduR_upTpCopyTxDataFuncType,       AUTOMATIC, PDUR_CONST)) PduR_upTpCopyTxDataTable
   ,  (P2CONST(PduR_upTpTxConfirmationFuncType,   AUTOMATIC, PDUR_CONST)) PduR_upTpTxConfirmationTable
   ,  (P2CONST(PduR_upIfTriggerTxFuncType,        AUTOMATIC, PDUR_CONST)) PduR_upIfTriggerTxTable
};

CONST(PduR_loTransmitFuncType, PDUR_CONST) PduR_loTransmitTable[] = {
      {&CanIf_Transmit}
   ,  {&CanTp_Transmit}
};

CONST(PduR_loCancelReceiveFuncType, PDUR_CONST) PduR_loCancelRxTable[] = {
   {NULL_PTR}
};

CONST(PduR_loCancelTransmitFuncType, PDUR_CONST) PduR_loCancelTransmitTable[] = {
      {&PduR_invId_UpCancelTransmit}
   ,  {&CanTp_CancelTransmit}
};

CONST(PduR_upIfRxIndicationFuncType, PDUR_CONST) PduR_upIfRxIndicationTable[] = {
   {&Com_RxIndication}
};

CONST(PduR_upIfTxConfirmationFuncType, PDUR_CONST) PduR_upIfTxConfirmationTable[] = {
   {&Com_TxConfirmation}
};

CONST(PduR_upIfTriggerTxFuncType, PDUR_CONST) PduR_upIfTriggerTxTable[] = {
   {NULL_PTR}
};

CONST(PduR_upTpCopyRxDataFuncType, PDUR_CONST) PduR_upTpCopyRxDataTable[] = {
   {&Dcm_CopyRxData}
};

CONST(PduR_upTpStartOfReceptionFuncType, PDUR_CONST) PduR_upTpStartOfReceptionTable[] = {
   {&Dcm_StartOfReception}
};

CONST(PduR_upTpRxIndicationFuncType, PDUR_CONST) PduR_upTpRxIndicationTable[] = {
   {&Dcm_TpRxIndication}
};

CONST(PduR_upTpCopyTxDataFuncType, PDUR_CONST) PduR_upTpCopyTxDataTable[] = {
   {&Dcm_CopyTxData}
};

CONST(PduR_upTpTxConfirmationFuncType, PDUR_CONST) PduR_upTpTxConfirmationTable[] = {
   {&Dcm_TpTxConfirmation}
};

CONST(PduR_PBConfigType, PDUR_CONST) PduR_GlobalPBConfig = {
      (P2CONST(PduR_CddConfig,          AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_LoTpConfig,         AUTOMATIC, PDUR_CONST)) PduR_LoTpCfg
   ,  (P2CONST(PduR_LoIfDConfig,        AUTOMATIC, PDUR_CONST)) PduR_LoIfDCfg
   ,  (P2CONST(PduR_LoIfTTConfig,       AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_UpConfig,           AUTOMATIC, PDUR_CONST)) PduR_UpIfCfg
   ,  (P2CONST(PduR_UpConfig,           AUTOMATIC, PDUR_CONST)) PduR_UpTpCfg
   ,  (P2CONST(PduR_MT_UpToLo,          AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_MT_LoIfTxToUp,      AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_MT_LoTpTxToUp,      AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (  P2VAR(PduR_MS_LoTpTxToUp,      AUTOMATIC, PDUR_VAR  )) NULL_PTR
   ,  (P2CONST(PduR_GT_IfTx,            AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_GT_If,              AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_GT_Tp,              AUTOMATIC, PDUR_CONST)) NULL_PTR
   ,  (P2CONST(PduR_RPTablesType,       AUTOMATIC, PDUR_CONST)) &PduR_RoutingPathTables
   ,  (P2CONST(PduR_UpTpToLoTpRxConfig, TYPEDEF,   PDUR_CONST)) NULL_PTR
   ,  0
   ,  0
   ,  0
   ,  (Type_SwcServiceCom_tIdPdu) 0
};

CONST(Type_CfgSwcServicePduR_st, PDUR_CONST) CfgSwcServicePduR_cst = {
      NULL_PTR
   ,  NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.hpp"

