#include "Std_Types.h"

#include "CfgEcuabCanIf.h"
#include "CanIf_Prv.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_Cfg_CtrlConfig_tst CanIf_CtrlGen_a[] = {
   { 0,   CanConf_CanController_Can_Network_0_CANNODE_0,   FALSE  }
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_Cfg_HthConfig_tst CanIf_HthGen_a[] = {
      { &CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0],  CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1, }
   ,  { &CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0],  CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2, }
   ,  { &CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0],  CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3, }
   ,  { &CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0],  CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4, }
   ,  { &CanIf_CtrlGen_a[CanIf_Ctrl_CustId_Can_Network_0_CANNODE_0],  CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5, }
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_Cfg_TxBufferConfig_tst CanIf_TxBufferGen_a[] = {
      {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4]}
   ,  {&CanIf_HthGen_a[CanIf_Hth_CustId_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5]}
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_Cfg_TxPduConfig_tst CanIf_TxPduGen_a[] = {
      { &CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3], CanIfConf_CanIfTxPduCfg_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0,   0,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x600, FALSE, FALSE, 8u}
   ,  { &CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2], CanIfConf_CanIfTxPduCfg_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0, 1,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x610, FALSE, FALSE, 8u}
   ,  { &CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1], CanIfConf_CanIfTxPduCfg_TPMS_Diag_Resp_Can_Network_0_CANNODE_0,           CanTpConf_CanTpTxNPdu_Phys_CanTp2CanIf, CANIF_STATIC, STANDARD_CAN, CAN_TP, &CanTp_TxConfirmation,     0x77A, FALSE, FALSE, 8u}
   ,  { &CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5], CanIfConf_CanIfTxPduCfg_TPMS_Status_Can_Network_0_CANNODE_0,              2,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x530, FALSE, FALSE, 8u}
   ,  { &CanIf_TxBufferGen_a[CanIf_Buffer_CustId_Buffer_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4], CanIfConf_CanIfTxPduCfg_TPMS_TirePT_Can_Network_0_CANNODE_0,              3,                                      CANIF_STATIC, STANDARD_CAN, PDUR,   &PduR_CanIfTxConfirmation, 0x76,  FALSE, FALSE, 8u}
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_Cfg_Hrhtype_tst CanIf_Lok_HrhConfig_tacst[13] = {
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
   ,  {CANIF_PRV_FULL_E, 11u, 1u, FALSE, 0u}
   ,  {CANIF_PRV_FULL_E, 12u, 1u, FALSE, 0u}
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_Cfg_RxPduType_tst CanIf_Lok_RxPduConfig_tacst[13] = {
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            7u,         192u,       0,         PduRConf_PduRSrcPdu_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            8u,         1568u,       1,         PduRConf_PduRSrcPdu_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            8u,         112u,       2,         PduRConf_PduRSrcPdu_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     2u,           0x20u,            1u,         1850u,       3,         CanTpConf_CanTpRxNPdu_Phys_CanIf2CanTp            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            8u,         849u,       4,         PduRConf_PduRSrcPdu_CGW_ODO_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            3u,         768u,       5,         PduRConf_PduRSrcPdu_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            7u,         833u,       6,         PduRConf_PduRSrcPdu_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            4u,         1040u,       7,         PduRConf_PduRSrcPdu_CGW_VehicleSpeed_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            3u,         263u,       8,         PduRConf_PduRSrcPdu_BCM_PowerMode_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            8u,         96u,       9,         PduRConf_PduRSrcPdu_CGW_EPOCHTime_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            7u,         834u,       10,         PduRConf_PduRSrcPdu_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     6u,           0x20u,            8u,         1024u,       11,         PduRConf_PduRSrcPdu_RdcData_TPMS_Can_Network_0_CANNODE_0_CanIf2PduR            },
    {CANIF_READ_NOTIFSTATUS,     2u,           0x20u,            1u,         2015u,       12,         CanTpConf_CanTpRxNPdu_Func_CanIf2CanTP            }
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

static const uint16 CanIf_CFG_HrhIdMapping_au16[] = {
   0,
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12,
   CANIF_INVALID_ID,
   CANIF_INVALID_ID,
   CANIF_INVALID_ID,
   CANIF_INVALID_ID,
   CANIF_INVALID_ID
};

static const uint16 CanIf_CFG_RxPduIdMapping_au16[] = {
   0,
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12
};

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const CanIf_RxCbk_Prototype CanIf_Lok_ULName_ta__fct[] = {
   {NULL_PTR},
   {NULL_PTR},
   {&CanTp_RxIndication},
   {NULL_PTR},
   {NULL_PTR},
   {NULL_PTR},
   {&PduR_CanIfRxIndication},
   {NULL_PTR},
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
const CanIf_CallbackFuncType CanIf_Callback = {
   &CanSM_ControllerBusOff,
   &CanSM_ControllerModeIndication,
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const uint16 CanIf_TxPduId_MappingTable[] = {
   0,	
   1,	
   2,	
   3,	
   4
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"
static const uint8 CanIf_CtrlId_MappingTable[] = {
   0
};

#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "CanIf_MemMap.h"
const Type_CfgEcuabCanIf_st CanIf_Config = {
      CanIf_Lok_HrhConfig_tacst
   ,  CanIf_Lok_RxPduConfig_tacst
   ,  13u
   ,  1
   ,  0
   ,  &CanIf_CFG_RxPduIdMapping_au16[0]
   ,  &CanIf_CFG_HrhIdMapping_au16[0]
   ,  0
   ,  &CanIf_TxPduGen_a[0u]
   ,  &CanIf_TxBufferGen_a[0u]
   ,  &CanIf_CtrlGen_a[0u]
   ,  5
   ,  5
   ,  &CanIf_TxPduId_MappingTable[0]
   ,  &CanIf_CtrlId_MappingTable[0]
   ,  &CanIf_Lok_ULName_ta__fct[0]
};
#define CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "CanIf_MemMap.h"

