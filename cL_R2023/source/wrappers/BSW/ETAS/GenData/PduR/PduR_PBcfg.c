

#include "PduR_PBcfg.h"
#include "PduR_UpIf.h"

#include "PduR_LoIf.h"
#include "PduR_LoTp.h"

#include "PduR_UpTp.h"

#include "PduR_Mc.h"
#include "PduR_Gw.h"

#include "PduR_Gw_Cfg.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)
#define PduR_comToLo   NULL_PTR
#else
static const PduR_RT_UpToLo PduR_comToLo[] = {
    { CanIfConf_CanIfTxPduCfg_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },
    { CanIfConf_CanIfTxPduCfg_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },
    { CanIfConf_CanIfTxPduCfg_TPMS_Status_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },
    { CanIfConf_CanIfTxPduCfg_TPMS_TirePT_Can_Network_0_CANNODE_0 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
};
#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_TPTX_LO)
#define PduR_DcmToLo NULL_PTR
#else
static const PduR_RT_UpToLo PduR_DcmToLo[] = {
    { CanTpConf_CanTpTxNSdu_UdsOnCan_Tx_Phy_PduR2CanTp, (PduR_loTransmitFP)PduR_RF_CanTp_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }
};
#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
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

    { ComConf_ComIPdu_RdcData_TPMS_Can_Network_0_CANNODE_0, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication }
 };
#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP )
#define PduR_CanIfTxToUp NULL_PTR
#else

static const PduR_RT_LoIfTxToUp PduR_CanIfTxToUp [] = {
{ ComConf_ComIPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,
{ ComConf_ComIPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,
{ ComConf_ComIPdu_TPMS_Status_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,
{ ComConf_ComIPdu_TPMS_TirePT_Can_Network_0_CANNODE_0 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}
};
#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
#if defined ( PDUR_CONFIG_SINGLE_TPRX )
#define PduR_CanTpRxToUp   NULL_PTR
#else
static const PduR_RT_LoTpRxToUp PduR_CanTpRxToUp[] = {
    {DcmConf_DcmDslProtocolRx_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication },
    {DcmConf_DcmDslProtocolRx_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication }
};
#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_TPTX_UP )
#define PduR_CanTpTxToUp NULL_PTR
#else
static const PduR_RT_LoTpTxToUp PduR_CanTpTxToUp [] = {
    { DcmConf_DcmDslProtocolTx_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_Dcm2PduR, (PduR_upTpProvideTxBufFP) PduR_RF_Dcm_CopyTxData,(PduR_upTpTxConfirmationFP) PduR_RF_Dcm_TpTxConfirmation }
};
#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

static const PduR_RPGInfoType PduR_RPGInfo[] = {

    {
     NULL_PTR,
     NULL_PTR,
     PDUR_RPGID_NULL,
     0,
     0
    },
};

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
#else
#define PDUR_START_SEC_CONFIG_DATA_8
#endif

#include "PduR_MemMap.h"

const boolean PduR_RPG_EnRouting[] =
{
  TRUE,
};

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#else
#define PDUR_STOP_SEC_CONFIG_DATA_8
#endif
#include "PduR_MemMap.h"

#endif

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
static const PduR_LoTpConfig PduR_LoTpCfg[] = {
  {
    PduR_CanTpRxToUp,
    PduR_CanTpTxToUp,
    2,
    1
    }
  };

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
static const PduR_LoIfDConfig PduR_LoIfDCfg[] = {
  {
    PduR_CanIfRxToUp,
    PduR_CanIfTxToUp,
    11,
    4
    }
  };

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
static const PduR_UpConfig PduR_UpTpCfg[] = {
  {
    PduR_DcmToLo,
    NULL_PTR,
    1
    }
  };

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
static const PduR_UpConfig PduR_UpIfCfg[] = {
  {
    PduR_comToLo,
    NULL_PTR,
    4
    }
  };

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

const PduR_RPTablesType PduR_RoutingPathTables = {
    (const PduR_loTransmitFuncType * )             PduR_loTransmitTable,
    (const PduR_loCancelReceiveFuncType * )        PduR_loCancelRxTable,
    (const PduR_loCancelTransmitFuncType * )       PduR_loCancelTransmitTable,
    (const PduR_upIfRxIndicationFuncType * )       PduR_upIfRxIndicationTable,
    (const PduR_upIfTxConfirmationFuncType * )     PduR_upIfTxConfirmationTable,
    (const PduR_upTpCopyRxDataFuncType * )         PduR_upTpCopyRxDataTable,
    (const PduR_upTpStartOfReceptionFuncType * )   PduR_upTpStartOfReceptionTable,
    (const PduR_upTpRxIndicationFuncType * )       PduR_upTpRxIndicationTable,
    (const PduR_upTpCopyTxDataFuncType * )         PduR_upTpCopyTxDataTable,
    (const PduR_upTpTxConfirmationFuncType * )     PduR_upTpTxConfirmationTable,
    (const PduR_upIfTriggerTxFuncType * )          PduR_upIfTriggerTxTable
};

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

const PduR_loTransmitFuncType PduR_loTransmitTable[] =
{
    {&PduR_RF_CanIf_Transmit_Func},
    {&PduR_RF_CanTp_Transmit_Func}
};

const PduR_loCancelReceiveFuncType PduR_loCancelRxTable[] =
{
    {NULL_PTR}
};

const PduR_loCancelTransmitFuncType PduR_loCancelTransmitTable[] =
{
    {&PduR_IH_CancelTransmit_Func}
};

const PduR_upIfRxIndicationFuncType PduR_upIfRxIndicationTable[] =
{
    {&PduR_RF_Com_RxIndication_Func}
};

const PduR_upIfTxConfirmationFuncType PduR_upIfTxConfirmationTable[] =
{
    {&PduR_RF_Com_TxConfirmation_Func}
};

const PduR_upIfTriggerTxFuncType PduR_upIfTriggerTxTable[] =
{
    {NULL_PTR}
};

const PduR_upTpCopyRxDataFuncType PduR_upTpCopyRxDataTable[] =
{
    {&PduR_RF_Dcm_CopyRxData_Func}
};

const PduR_upTpStartOfReceptionFuncType PduR_upTpStartOfReceptionTable[] =
{
    {&PduR_RF_Dcm_StartOfReception_Func}
};

const PduR_upTpRxIndicationFuncType PduR_upTpRxIndicationTable[] =
{
    {&PduR_RF_Dcm_TpRxIndication_Func}
};

const PduR_upTpCopyTxDataFuncType PduR_upTpCopyTxDataTable[] =
{
    {&PduR_RF_Dcm_CopyTxData_Func}
};

const PduR_upTpTxConfirmationFuncType PduR_upTpTxConfirmationTable[] =
{
    {&PduR_RF_Dcm_TpTxConfirmation_Func}
};

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
const PduR_PBConfigType PduR_GlobalPBConfig = {
  (const PduR_CddConfig *) NULL_PTR,
     (const PduR_LoTpConfig *) PduR_LoTpCfg,
     (const PduR_LoIfDConfig *) PduR_LoIfDCfg,
     (const PduR_LoIfTTConfig *) NULL_PTR,
     (const PduR_UpConfig *) PduR_UpIfCfg,
     (const PduR_UpConfig *) PduR_UpTpCfg,
     (const PduR_MT_UpToLo *) NULL_PTR,
     (const PduR_MT_LoIfTxToUp *) NULL_PTR,
     (const PduR_MT_LoTpTxToUp *) NULL_PTR,
     (PduR_MS_LoTpTxToUp *) NULL_PTR,
     (const PduR_GT_IfTx *) NULL_PTR,
     (const PduR_GT_If *) NULL_PTR,
     (const PduR_GT_Tp *) NULL_PTR,
     (const PduR_RPG_LoTpRxToUp *) NULL_PTR,
     (const PduR_RPTablesType * ) &PduR_RoutingPathTables,
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
    (const PduR_GwTp_SessionListType * ) NULL_PTR,
#endif
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT != 0)
     (const PduR_UpIfTxConf_Config * ) PduR_UpIfTxConf_ConfigList,
#endif
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
     (const PduR_RPGInfoType * )        PduR_RPGInfo,
     (const boolean * )   PduR_RPG_EnRouting,
     (boolean * )  PduR_RPG_Status,
     (PduR_RoutingPathGroupIdType)                              0,
#endif
     (const PduR_UpTpToLoTpRxConfig *) NULL_PTR,
0,
0,
0,
     (PduIdType) 0
};

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
const Type_CfgSwcServicePduR_st PduR_Config = {
    NULL_PTR,
    NULL_PTR
};

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

