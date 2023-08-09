

#include "PduR_PBcfg.h"
#include "PduR_UpIf.h"

#include "PduR_LoIf.h"
#include "PduR_LoTp.h"

#include "PduR_UpTp.h"

#include "PduR_Mc.h"
#include "PduR_Gw.h"

#include "PduR_Gw_Cfg.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)
#define PduR_comToLo   NULL_PTR
#else
static CONST(PduR_RT_UpToLo,PDUR_CONST ) PduR_comToLo[] = {
    { CanIfConf_CanIfTxPduCfg_ApplicationCyclic_TPM_Can_Network_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },
    { CanIfConf_CanIfTxPduCfg_ApplicationResponse_TPM_Can_Network_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },
    { CanIfConf_CanIfTxPduCfg_HMIPressure_TPM_Can_Network_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },
    { CanIfConf_CanIfTxPduCfg_HMITempAndRefPress_TPM_Can_Network_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }

};
#endif

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_TPTX_LO)
#define PduR_DcmToLo NULL_PTR
#else
static CONST(PduR_RT_UpToLo,PDUR_CONST ) PduR_DcmToLo[] = {
    { CanTpConf_CanTpTxNSdu_UdsOnCan_Tx_Phy_TP, (PduR_loTransmitFP)PduR_RF_CanTp_Transmit, (PduR_loCancelTransmitFP)PduR_RF_CanTp_CancelTransmit }

};
#endif

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_CanIfRxToUp   NULL_PTR
#else
static CONST( PduR_RT_LoIfRxToUp, PDUR_CONST ) PduR_CanIfRxToUp[] = {
    { ComConf_ComIPdu_ApplicationRequest_TPM_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_BCM_peripheralMasterClock_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_RdcData_TPM_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_TMM_Status_BodyLCAN_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_VehSts_BodyLCAN_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },
    { ComConf_ComIPdu_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication }
 };
#endif

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP )
#define PduR_CanIfTxToUp NULL_PTR
#else

static CONST(PduR_RT_LoIfTxToUp, PDUR_CONST ) PduR_CanIfTxToUp [] = {
{ ComConf_ComIPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,
{ ComConf_ComIPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,
{ ComConf_ComIPdu_HMIPressure_TPM_Can_Network_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,
{ ComConf_ComIPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
};
#endif

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined ( PDUR_CONFIG_SINGLE_TPRX )
#define PduR_CanTpRxToUp   NULL_PTR
#else
static CONST( PduR_RT_LoTpRxToUp, PDUR_CONST ) PduR_CanTpRxToUp[] = {
    {DcmConf_DcmDslProtocolRx_UDS_Rx_Functional_Can_Network_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication },
    {DcmConf_DcmDslProtocolRx_UDS_Rx_Physical_Can_Network_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication }
};
#endif

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_TPTX_UP )
#define PduR_CanTpTxToUp NULL_PTR
#else
static CONST(PduR_RT_LoTpTxToUp, PDUR_CONST ) PduR_CanTpTxToUp [] = {
    { DcmConf_DcmDslProtocolTx_UDS_Tx_Physical_Can_Network_CANNODE_0_Phys_Dcm2PduR, (PduR_upTpProvideTxBufFP) PduR_RF_Dcm_CopyTxData,(PduR_upTpTxConfirmationFP) PduR_RF_Dcm_TpTxConfirmation }
};
#endif

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

static CONST (PduR_RPGInfoType, PDUR_CONST) PduR_RPGInfo[] = {

    {
     NULL_PTR,
     NULL_PTR,
     PDUR_RPGID_NULL,
     0,
     0
    },

};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "PduR_MemMap.h"

CONST(boolean, PDUR_CONST) PduR_RPG_EnRouting[] =
{
  TRUE,

};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "PduR_MemMap.h"

#endif

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_LoTpConfig, PDUR_CONST ) PduR_LoTpCfg[] = {
  {
    PduR_CanTpRxToUp,
    PduR_CanTpTxToUp,
    2,
    1
    }
  };

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_LoIfDConfig, PDUR_CONST ) PduR_LoIfDCfg[] = {
  {
    PduR_CanIfRxToUp,
    PduR_CanIfTxToUp,
    9,
    4
    }
  };

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_UpConfig, PDUR_CONST ) PduR_UpTpCfg[] = {
  {
    PduR_DcmToLo,
    NULL_PTR,
    1
    }
  };

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_UpConfig, PDUR_CONST ) PduR_UpIfCfg[] = {
  {
    PduR_comToLo,
    NULL_PTR,
    4
    }
  };

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

CONST( PduR_RPTablesType, PDUR_CONST ) PduR_RoutingPathTables = {
    (P2CONST( PduR_loTransmitFuncType, AUTOMATIC, PDUR_CONST ))             PduR_loTransmitTable,
    (P2CONST( PduR_loCancelReceiveFuncType, AUTOMATIC,  PDUR_CONST))        PduR_loCancelRxTable,
    (P2CONST( PduR_loCancelTransmitFuncType, AUTOMATIC, PDUR_CONST ))       PduR_loCancelTransmitTable,
    (P2CONST( PduR_upIfRxIndicationFuncType, AUTOMATIC, PDUR_CONST ))       PduR_upIfRxIndicationTable,
    (P2CONST( PduR_upIfTxConfirmationFuncType, AUTOMATIC, PDUR_CONST ))     PduR_upIfTxConfirmationTable,
    (P2CONST( PduR_upTpCopyRxDataFuncType, AUTOMATIC, PDUR_CONST ))         PduR_upTpCopyRxDataTable,
    (P2CONST( PduR_upTpStartOfReceptionFuncType, AUTOMATIC, PDUR_CONST ))   PduR_upTpStartOfReceptionTable,
    (P2CONST( PduR_upTpRxIndicationFuncType, AUTOMATIC, PDUR_CONST ))       PduR_upTpRxIndicationTable,
    (P2CONST( PduR_upTpCopyTxDataFuncType, AUTOMATIC, PDUR_CONST ))         PduR_upTpCopyTxDataTable,
    (P2CONST( PduR_upTpTxConfirmationFuncType, AUTOMATIC, PDUR_CONST ))     PduR_upTpTxConfirmationTable,
    (P2CONST( PduR_upIfTriggerTxFuncType, AUTOMATIC, PDUR_CONST ))          PduR_upIfTriggerTxTable

};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

CONST(PduR_loTransmitFuncType, PDUR_CONST) PduR_loTransmitTable[] =
{
    {&PduR_RF_CanIf_Transmit_Func},
    {&PduR_RF_CanTp_Transmit_Func}
};

CONST(PduR_loCancelReceiveFuncType, PDUR_CONST) PduR_loCancelRxTable[] =
{
    {NULL_PTR}
};

CONST(PduR_loCancelTransmitFuncType, PDUR_CONST) PduR_loCancelTransmitTable[] =
{
    {&PduR_IH_CancelTransmit_Func},
    {&PduR_RF_CanTp_CancelTransmit_Func}
};

CONST(PduR_upIfRxIndicationFuncType, PDUR_CONST) PduR_upIfRxIndicationTable[] =
{
    {&PduR_RF_Com_RxIndication_Func}
};

CONST(PduR_upIfTxConfirmationFuncType, PDUR_CONST) PduR_upIfTxConfirmationTable[] =
{
    {&PduR_RF_Com_TxConfirmation_Func}
};

CONST(PduR_upIfTriggerTxFuncType, PDUR_CONST) PduR_upIfTriggerTxTable[] =
{
    {NULL_PTR}
};

CONST(PduR_upTpCopyRxDataFuncType, PDUR_CONST) PduR_upTpCopyRxDataTable[] =
{
    {&PduR_RF_Dcm_CopyRxData_Func}
};

CONST(PduR_upTpStartOfReceptionFuncType, PDUR_CONST) PduR_upTpStartOfReceptionTable[] =
{
    {&PduR_RF_Dcm_StartOfReception_Func}
};

CONST(PduR_upTpRxIndicationFuncType, PDUR_CONST) PduR_upTpRxIndicationTable[] =
{
    {&PduR_RF_Dcm_TpRxIndication_Func}
};

CONST(PduR_upTpCopyTxDataFuncType, PDUR_CONST) PduR_upTpCopyTxDataTable[] =
{
    {&PduR_RF_Dcm_CopyTxData_Func}
};

CONST(PduR_upTpTxConfirmationFuncType, PDUR_CONST) PduR_upTpTxConfirmationTable[] =
{
    {&PduR_RF_Dcm_TpTxConfirmation_Func}
};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
CONST( PduR_PBConfigType, PDUR_CONST ) PduR_GlobalPBConfig = {
  (P2CONST( PduR_CddConfig, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_LoTpConfig, AUTOMATIC, PDUR_CONST )) PduR_LoTpCfg,
     (P2CONST( PduR_LoIfDConfig, AUTOMATIC, PDUR_CONST )) PduR_LoIfDCfg,
     (P2CONST( PduR_LoIfTTConfig, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_UpConfig, AUTOMATIC, PDUR_CONST )) PduR_UpIfCfg,
     (P2CONST( PduR_UpConfig, AUTOMATIC, PDUR_CONST )) PduR_UpTpCfg,
     (P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_MT_LoIfTxToUp, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_MT_LoTpTxToUp, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2VAR(   PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR )) NULL_PTR,
     (P2CONST( PduR_GT_IfTx, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_GT_Tp, AUTOMATIC, PDUR_CONST )) NULL_PTR,
     (P2CONST( PduR_RPTablesType, AUTOMATIC, PDUR_CONST )) &PduR_RoutingPathTables,
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
    (P2CONST(PduR_GwTp_SessionListType, AUTOMATIC, PDUR_CONST )) NULL_PTR,
#endif
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT != 0)
     (P2CONST(PduR_UpIfTxConf_Config, AUTOMATIC, PDUR_CONST)) PduR_UpIfTxConf_ConfigList,
#endif
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
     (P2CONST (PduR_RPGInfoType, AUTOMATIC, PDUR_CONST))        PduR_RPGInfo,
     (P2CONST (boolean, AUTOMATIC, PDUR_CONST))   PduR_RPG_EnRouting,
     (P2VAR  (boolean , TYPEDEF , PDUR_VAR))  PduR_RPG_Status,
     (PduR_RoutingPathGroupIdType)                              0,
#endif
     (P2CONST (PduR_UpTpToLoTpRxConfig, TYPEDEF, PDUR_CONST)) NULL_PTR,
0,
0,
0,
     (PduIdType) 0
};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(Type_CfgSwcServicePduR_st, PDUR_CONST) PduR_Config = {
    NULL_PTR,
    NULL_PTR
};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

