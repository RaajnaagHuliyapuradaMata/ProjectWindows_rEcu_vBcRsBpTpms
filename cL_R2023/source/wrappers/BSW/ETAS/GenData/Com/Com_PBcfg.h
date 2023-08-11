

#ifndef COM_PBCFG_H
#define COM_PBCFG_H

#define COM_NUM_RX_SIGNALS        56u
#define COM_NUM_TX_SIGNALS        29u
#define COM_NUM_TX_IPDU         4u
#define COM_NUM_RX_IPDU         11u
#define COM_NUM_GWSRC_SIGNALS  0u
#define COM_NUM_GWSRC_GRPSIGNALS  0u
#define COM_NUM_GWSRC_IPDUS     0u
#define COM_NUM_GRPSIG_NOGW     0u

#ifdef COM_F_ONEEVERYN
#define COM_NUM_OF_SIG_GRPSIG_WITH_ONE_EVERY_N 0u
#endif

#define COM_NUM_IPDUS_IN_LAST_IPDUGRP 1u

#define COM_UPDATE_MAX      COM_MAX_U8_VALUE

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#ifdef COM_TP_IPDUTYPE

extern PduLengthType                                        Com_TpTxIpduLength_auo[];
#endif

#ifdef COM_RX_SIGNALGROUP

extern Com_RxSignalGrpFlagType                              Com_RxSignalGrpFlag[];
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

extern Com_TxSignalGrpFlagType                              Com_TxSignalGrpFlag[];
#endif

extern Com_TxGrpSignalFlagType                              Com_TxGrpSignalFlag[];
#endif

extern Com_RxIpduRamData                                    Com_RxIpduRam_s[];

extern Com_TxIpduRamData                                    Com_TxIpduRam_s[];

extern Com_TxSignalFlagType                                 Com_TxSignalFlag[];

extern Com_RxSignalFlagType                                 Com_RxSignalFlag[];

extern PduIdType                                            Com_RxGwQueue_aux[];

extern Com_RxGwQueueRAMType                                 Com_RxGwQueue_S;

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
extern boolean                                              Com_IsGwSignalsUpdated_ab[];
#endif

#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.h"

#ifdef COM_SIGNALGATEWAY

extern const Com_Lok_xGwMapSigCfg_tst                       Com_Lok_xGwMapSigCfg_acst[];

extern const Com_Lok_xGwMapSigIdCfg_tst                     Com_Lok_xGwMapSigIdCfg_acst[];
#endif

#ifdef COM_SIGNALGROUPGATEWAY

extern const Com_Lok_xGwMapGrpSigCfg_tst                    Com_Lok_xGwMapGrpSigCfg_acst[];

extern const Com_Lok_xGwMapGrpSigIdCfg_tst                  Com_Lok_xGwMapGrpSigIdCfg_acst[];
#endif

extern const Com_Lok_xTxSigCfg_tst                          Com_Lok_xTxSigCfg_acst[];

extern const Com_Lok_xRxSigCfg_tst                          Com_Lok_xRxSigCfg_acst[];

extern const Com_Lok_xTxIpduInfoCfg_tst                     Com_Lok_xTxIpduCfg_acst[];

extern const Com_Lok_xRxIpduInfoCfg_tst                     Com_Lok_xRxIpduCfg_acst[];

#ifdef COM_TX_IPDUCOUNTER

extern const Com_Lok_xTxIpduCntrCfg_tst                     Com_Lok_xTxIpduCntrCfg_acst[];
#endif

#ifdef COM_RX_IPDUCOUNTER

extern const Com_Lok_xRxIpduCntrCfg_tst                     Com_Lok_xRxIpduCntrCfg_acst[];
#endif

extern const Com_Lok_xIpduGrpInfoCfg_tst                    Com_Lok_xIpduGrpCfg_acst[];

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
extern const Com_ConfigData_tst                             Com_Lok_Config_cst;
#endif

extern const Com_IpduIdType                                 Com_Lok_xIPduGrp_IpduRefCfg_au8[];

#ifdef COM_TX_SIGNALGROUP

extern const Com_Lok_xTxSigGrpCfg_tst                       Com_Lok_xTxSigGrpCfg_acst[];

#ifdef COM_TX_SIGNALGROUP_ARRAY

extern const Com_Lok_xTxSigGrpArrayCfg_tst                  Com_Lok_xTxSigGrpArrayCfg_acst[];
#endif

#endif

#ifdef COM_RX_SIGNALGROUP

extern const Com_Lok_xRxSigGrpCfg_tst                       Com_Lok_xRxSigGrpCfg_acst[];

#ifdef COM_RX_SIGNALGROUP_ARRAY

extern const Com_Lok_xRxSigGrpArrayCfg_tst                  Com_Lok_xRxSigGrpArrayCfg_acst[];
#endif

#endif

#ifdef COM_TX_SIGNALGROUP

extern const Com_Lok_xTxGrpSigCfg_tst                       Com_Lok_xTxGrpSigCfg_acst[];
#endif

#ifdef COM_RX_SIGNALGROUP

extern const Com_Lok_xRxGrpSigCfg_tst                       Com_Lok_xRxGrpSigCfg_acst[];
#endif

extern const Com_MainFunctionCfgType                        Com_MainFunctionCfg[];

extern const Com_Lok_xRxRamBuf_tst                          Com_Lok_xRxRamBuf_acst[];

#ifdef COM_TX_SIGNALGROUP

extern const Com_Lok_xTxSigGrpRamBuf_tst                    Com_Lok_xTxSigGrpRamBuf_acst[];
#endif

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

extern uint8 Com_IpduCounter_s[];

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)

extern uint8 Com_IpduCounter_DM[];
#endif

#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

#ifdef COM_RxIPduDeferredProcessing

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

extern uint8 Com_DeferredBuffer[];

#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

extern uint8 Com_dTPMS_ApplicationCyclic_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dTPMS_Status_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dTPMS_TirePT_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dTPMS_ApplicationResponse_Can_Network_0_CANNODE_0Byte[];

#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

extern uint8 Com_dBCM_PowerMode_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_EPOCHTime_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_ESP_WheelPulses_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_ODO_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_TPMS_Application_Req_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dCGW_VehicleSpeed_Can_Network_0_CANNODE_0Byte[];
extern uint8 Com_dRdcData_TPMS_Can_Network_0_CANNODE_0Byte[];

#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

#ifdef COM_TX_SIGNALGROUP

#endif

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"
extern uint8 Com_SigType_u8[];

#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
extern uint16 Com_SigType_u16[];

#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_32
#include "Com_MemMap.h"
extern uint32 Com_SigType_u32[];

#define COM_STOP_SEC_VAR_CLEARED_32
#include "Com_MemMap.h"

#ifdef COM_RX_SIGNALGROUP

#endif

#ifdef COM_RxSigUpdateTimeout
#endif

#ifdef COM_RxSigGrpUpdateTimeout
#endif

#endif
