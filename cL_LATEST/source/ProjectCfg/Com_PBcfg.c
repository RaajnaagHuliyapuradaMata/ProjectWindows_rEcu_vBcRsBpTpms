/******************************************************************************/
/* File   : Com_PBcfg.c                                                       */
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
#define COM_DontUseExternalSymbolicNames
#include "Com_Prv.hpp"
#include "Com_Cbk.hpp"
#include "PduR_Com.hpp"
#include "Com_PBcfg.hpp"

#include "Com_PBcfg_InternalId.hpp"

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
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xTxSigCfg_tst Com_Lok_xTxSigCfg_acst[COM_NUM_TX_SIGNALS] = {
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        0,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0,
        0x8
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        56,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        23,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        22,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        3,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        12,
        3,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        48,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        40,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        32,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        27,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        26,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        25,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        24,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        16,
        4,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        11,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        15,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        7,
        1,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x6
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        8,
        3,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        4,
        3,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        0,
        3,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x28uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        24,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x28uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        8,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x28uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        0,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        56,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        48,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        32,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x28uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        16,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        40,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0,
        0x0
   },
   {
#ifdef COM_TxInvalid
        0x0uL,
#endif
        0x0uL,
        0x54,
#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif
        0,
        8,
#ifdef COM_TxFilters
        COM_MAX_U8_VALUE,
#endif
#ifdef COM_EffectiveSigTOC
        COM_MAX_U8_VALUE,
#endif
        (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0,
        0x8
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xRxSigCfg_tst Com_Lok_xRxSigCfg_acst[COM_NUM_RX_SIGNALS] =
{
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      0,
      3,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_PowerMode_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       6
   ,      1,
      1,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_PowerMode_Can_Network_0_CANNODE_0,
        0x6,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       7
   ,      2,
      1,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_PowerMode_Can_Network_0_CANNODE_0,
        0x6,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       4
   ,      3,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_PowerMode_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       12
   ,      4,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_PowerMode_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       10
   ,      5,
      1,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_EPOCHTime_Can_Network_0_CANNODE_0,
        0x6,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      0,
      10,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_EPOCHTime_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       12
   ,      6,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_EPOCHTime_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16
   ,      43,
      6,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_EPOCHTime_Can_Network_0_CANNODE_0,
        0x8,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       52
   ,      7,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       10
   ,      1,
      10,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       30
   ,      2,
      10,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      3,
      10,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       46
   ,      8,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       44
   ,      9,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       42
   ,      10,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40
   ,      11,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       56
   ,      12,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       20
   ,      4,
      10,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      0,
      32,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_ODO_Can_Network_0_CANNODE_0,
        0x4,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      49,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0,
        0x8,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8
   ,      13,
      1,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0,
        0x6,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16
   ,      14,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      15,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       48
   ,      16,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       26
   ,      17,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       28
   ,      18,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24
   ,      19,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       14
   ,      20,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16
   ,      5,
      14,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      6,
      14,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       36
   ,      21,
      3,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       32
   ,      22,
      3,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       30
   ,      23,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40
   ,      24,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       48
   ,      25,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16
   ,      7,
      14,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       14
   ,      26,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      8,
      14,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       36
   ,      27,
      3,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       32
   ,      28,
      3,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       30
   ,      29,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40
   ,      30,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       48
   ,      31,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      9,
      16,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VehicleSpeed_Can_Network_0_CANNODE_0,
        0x2,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24
   ,      32,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VehicleSpeed_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       20
   ,      33,
      4,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VehicleSpeed_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16
   ,      34,
      2,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CGW_VehicleSpeed_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       56
   ,      35,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40
   ,      36,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       32
   ,      37,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0
   ,      38,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       48
   ,      39,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24
   ,      40,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16
   ,      41,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
   ,
   {
#ifdef COM_RxSignalNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify
        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       0x0uL,
#endif
       0x0uL,
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8
   ,      42,
      8,
#ifdef COM_RxFilters
        COM_MAX_U8_VALUE,
#endif
       (Com_IpduIdType)ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0,
        0x0,
        0x28
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
static const Com_TransModeInfo Com_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_TransModeInfo[] =
{
   {
        1,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC
   ,       COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif
   }
,
   {
        1,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC
   ,       COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
static const Com_TransModeInfo Com_TPMS_Status_Can_Network_0_CANNODE_0_TransModeInfo[] =
{
   {
        100,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC
   ,       COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif
   }
,
   {
        100,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC
   ,       COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
static const Com_TransModeInfo Com_TPMS_TirePT_Can_Network_0_CANNODE_0_TransModeInfo[] =
{
   {
        100,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC
   ,       COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif
   }
,
   {
        100,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC
   ,       COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
static const Com_TransModeInfo Com_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_TransModeInfo[] =
{
   {
        0,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_DIRECT
   ,       COM_FALSE
#else
        COM_TXMODE_DIRECT
#endif
   }
,
   {
        0,
        1,
        0,
        0,
#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_DIRECT
   ,       COM_FALSE
#else
        COM_TXMODE_DIRECT
#endif
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xTxIpduInfoCfg_tst Com_Lok_xTxIpduCfg_acst[COM_NUM_TX_IPDU] =
{
   {
        Com_dTPMS_ApplicationCyclic_Can_Network_0_CANNODE_0Byte,
        Com_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_TransModeInfo,
#ifdef COM_TxIPduCallOuts
        &Com_IPdu_Callout_TPMS_ApplicationCyclic,
#endif
#ifdef COM_TxIPduNotification
        NULL_PTR,
#endif
#ifdef COM_ERRORNOTIFICATION
        NULL_PTR,
#endif
#ifdef COM_TxIPduTimeOutNotify
        NULL_PTR,
#endif
#ifdef COM_METADATA_SUPPORT
        NULL_PTR,
#endif
        8,
#ifdef COM_TxIPduTimeOut
        1,
#endif
        0,
        1,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_Com2PduR,
        (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_AppCyclic,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        0x1001,
#ifdef COM_TX_IPDUCOUNTER
        COM_TXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionTx,
        0xFF
   }
   ,  {
        Com_dTPMS_Status_Can_Network_0_CANNODE_0Byte,
        Com_TPMS_Status_Can_Network_0_CANNODE_0_TransModeInfo,
#ifdef COM_TxIPduCallOuts
        &Com_IPdu_Callout_TPMS_Status,
#endif
#ifdef COM_TxIPduNotification
        NULL_PTR,
#endif
#ifdef COM_ERRORNOTIFICATION
        NULL_PTR,
#endif
#ifdef COM_TxIPduTimeOutNotify
        NULL_PTR,
#endif
#ifdef COM_METADATA_SUPPORT
        NULL_PTR,
#endif
        8,
#ifdef COM_TxIPduTimeOut
        100,
#endif
        0,
        19,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_TPMS_Status_Can_Network_0_CANNODE_0_Com2PduR,
        (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_Tire_Ref_Press_RR,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        0x1001,
#ifdef COM_TX_IPDUCOUNTER
        COM_TXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionTx,
        0xFF
   }
   ,  {
        Com_dTPMS_TirePT_Can_Network_0_CANNODE_0Byte,
        Com_TPMS_TirePT_Can_Network_0_CANNODE_0_TransModeInfo,
#ifdef COM_TxIPduCallOuts
        &Com_IPdu_Callout_TPMS_TirePT,
#endif
#ifdef COM_TxIPduNotification
        NULL_PTR,
#endif
#ifdef COM_ERRORNOTIFICATION
        NULL_PTR,
#endif
#ifdef COM_TxIPduTimeOutNotify
        NULL_PTR,
#endif
#ifdef COM_METADATA_SUPPORT
        NULL_PTR,
#endif
        8,
#ifdef COM_TxIPduTimeOut
        100,
#endif
        0,
        8,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_TPMS_TirePT_Can_Network_0_CANNODE_0_Com2PduR,
        (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_TireT_RR,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        0x1001,
#ifdef COM_TX_IPDUCOUNTER
        COM_TXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionTx,
        0xFF
   }
   ,  {
        Com_dTPMS_ApplicationResponse_Can_Network_0_CANNODE_0Byte,
        Com_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_TransModeInfo,
#ifdef COM_TxIPduCallOuts
        &Com_IPdu_Callout_TPMS_ApplicationResponse,
#endif
#ifdef COM_TxIPduNotification
        NULL_PTR,
#endif
#ifdef COM_ERRORNOTIFICATION
        NULL_PTR,
#endif
#ifdef COM_TxIPduTimeOutNotify
        NULL_PTR,
#endif
#ifdef COM_METADATA_SUPPORT
        NULL_PTR,
#endif
        8,
#ifdef COM_TxIPduTimeOut
        0,
#endif
        0,
        1,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_Com2PduR,
        (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_AppResponse,
#ifdef COM_TX_SIGNALGROUP
        0,
#endif
        0x1001,
#ifdef COM_TX_IPDUCOUNTER
        COM_TXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionTx,
        0xFF
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#ifdef COM_RxSigUpdateTimeout
#endif
#ifdef COM_RxSigGrpUpdateTimeout
#endif
#ifdef COM_RxSigUpdateTimeout
#endif
#ifdef COM_RxSigGrpUpdateTimeout
#endif
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xRxIpduInfoCfg_tst Com_Lok_xRxIpduCfg_acst[COM_NUM_RX_IPDU] =
{
   {
        Com_dBCM_PowerMode_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_BCM_PowerMode,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        3,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        5,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_BCM_PowerMode_Status,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_EPOCHTime_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_EPOCHTime,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        8,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        4,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_TCU_EPOCHTime_Valid,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_ESP_WheelPulses_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_ESP_WheelPulses,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        8,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        10,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_ESP_WheelPulses_Ctr,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_ODO_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_ODO,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        8,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        1,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_Odometer,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_TPMS_Application_Req_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_TPMS_ApplicationRequest,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        8,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        1,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_TPMS_Application_Req_Cmd,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_VCU_Ambient_Info,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        3,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        3,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_VCU_AmbientTemp_Qualifier,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_VCU_Powertrain_Info,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        7,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        4,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_VCU_Powertrain_Info_CSum,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_VCU_WheelSpeed_Front,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        7,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        8,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_VCU_WhlSpd_FL_Valid,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_VCU_WheelSpeed_Rear,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        7,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        8,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_VCU_WhlSpd_RR,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCGW_VehicleSpeed_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_CGW_VehicleSpeed,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        4,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        4,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_CGW_VehSpeed,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
   ,  {
        Com_dCfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0Byte,
#ifdef COM_RxSigUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxSigGrpUpdateTimeout
        NULL_PTR,
#endif
#ifdef COM_RxIPduCallOuts
        &Com_IPdu_Callout_TPMS_RdcData,
#endif
#ifdef COM_RxIPduTimeoutNotify
        NULL_PTR,
#endif
#ifdef COM_RxIPduNotification
        NULL_PTR,
#endif
        8,
#ifdef COM_RxIPduTimeout
        0,
        0,
#endif
        8,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
        (Com_RxIntSignalIdType)ComSignal_Internal_User_Defined_Val5,
#ifdef COM_RX_SIGNALGROUP
        0,
#endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif
#ifdef COM_RX_IPDUCOUNTER
        COM_RXIPDU_CNTR_INV_IDX,
#endif
        ComMainFunction_Internal_MainFunctionRx,
        0x9
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xIpduGrpInfoCfg_tst Com_Lok_xIpduGrpCfg_acst[4] =
{
{
    0,
    11
}
,{
    11,
    0
}
,{
    15,
    0
}
,{
    16,
    0
}
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_IpduIdType Com_Lok_xIPduGrp_IpduRefCfg_au8[17] = {
      ComConf_ComIPdu_Internal_BCM_PowerMode_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_EPOCHTime_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_ODO_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CGW_VehicleSpeed_Can_Network_0_CANNODE_0
   ,  ComConf_ComIPdu_Internal_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Status_Can_Network_0_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_TirePT_Can_Network_0_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0)
};

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"
uint8 Com_dTPMS_ApplicationCyclic_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dTPMS_Status_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dTPMS_TirePT_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dTPMS_ApplicationResponse_Can_Network_0_CANNODE_0Byte[8];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"
uint8 Com_dBCM_PowerMode_Can_Network_0_CANNODE_0Byte[3];
uint8 Com_dCGW_EPOCHTime_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dCGW_ESP_WheelPulses_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dCGW_ODO_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dCGW_TPMS_Application_Req_Can_Network_0_CANNODE_0Byte[8];
uint8 Com_dCGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0Byte[3];
uint8 Com_dCGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0Byte[7];
uint8 Com_dCGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0Byte[7];
uint8 Com_dCGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0Byte[7];
uint8 Com_dCGW_VehicleSpeed_Can_Network_0_CANNODE_0Byte[4];
uint8 Com_dCfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0Byte[8];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"

#ifdef COM_F_MASKEDNEWDIFFERSOLD
#define COM_START_SEC_VAR_CLEARED_32
#include "Com_MemMap.hpp"
uint32 Com_F_OldVal[1];
#define COM_STOP_SEC_VAR_CLEARED_32
#include "Com_MemMap.hpp"
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Com_OldValTrigOnChngType Com_OldValTrigOnChng[1];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_F_ONEEVERYN
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_OneEveryNType Com_OneEveryN_Const[1] = {
   {    1,    5, 1    }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Com_OneEveryNType Com_OneEveryN[1];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#ifdef COM_TP_IPDUTYPE
Type_SwcServiceCom_tLengthPdu Com_TpTxIpduLength_auo[COM_NUM_TX_IPDU];
#endif

Com_TxIpduRamData Com_TxIpduRam_s[COM_NUM_TX_IPDU];
Com_RxIpduRamData Com_RxIpduRam_s[COM_NUM_RX_IPDU];
Com_TxSignalFlagType Com_TxSignalFlag[COM_NUM_TX_SIGNALS];
Com_RxSignalFlagType Com_RxSignalFlag[COM_NUM_RX_SIGNALS];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"
uint8 Com_IpduCounter_s[COM_NUM_TX_IPDU + COM_NUM_RX_IPDU];

# if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
uint8 Com_IpduCounter_DM[COM_NUM_RX_IPDU];
# endif
#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Type_SwcServiceCom_tIdPdu Com_RxGwQueue_aux[COM_NUM_GWSRC_IPDUS+1u];
Com_RxGwQueueRAMType Com_RxGwQueue_S;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_RX_SIGNALGROUP
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Com_RxSignalGrpFlagType Com_RxSignalGrpFlag[1u];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Com_TxSignalGrpFlagType Com_TxSignalGrpFlag[1u];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Com_TxGrpSignalFlagType Com_TxGrpSignalFlag[1u];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_RxIPduDeferredProcessing
#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"
   uint8 Com_DeferredBuffer[ 8 ];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"

#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
   boolean Com_IsGwSignalsUpdated_ab[ COM_NUM_GWSRC_IPDUS ];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_MaskXType Com_MaskX[1] = {
   {    1,    5    }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
#define COM_START_SEC_CONFIG_DATA_32
#include "Com_MemMap.hpp"
const uint32 Com_Mask[1] = {
    1
};
#define COM_STOP_SEC_CONFIG_DATA_32
#include "Com_MemMap.hpp"
#endif

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_POSMinMaxType Com_POSMinMax[1] = {
   {    1,    5    }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_NEGMinMaxType Com_NEGMinMax[1] = {
   {    1,    5    }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"
uint8 Com_SigType_u8[57];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.hpp"
uint16 Com_SigType_u16[10];
#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_32
#include "Com_MemMap.hpp"
uint32 Com_SigType_u32[1];
#define COM_STOP_SEC_VAR_CLEARED_32
#include "Com_MemMap.hpp"

#ifdef COM_RXSIG_INT64
#define Com_SigType_u64          ( NULL_PTR )
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
#define Com_SigType_f64          ( NULL_PTR )
#endif

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
#define Com_SigType_dyn          ( NULL_PTR )
#endif

#ifdef COM_RX_SIGNALGROUP_ARRAY
#define Com_RxSigGrpArrayBuf_u8  ( NULL_PTR )
#endif

#ifdef COM_RX_SIGNALGROUP
#define Com_RxGrpSigType_u8      ( NULL_PTR )
#define Com_RxGrpSigType_u16     ( NULL_PTR )
#define Com_RxGrpSigType_u32     ( NULL_PTR )

#ifdef COM_RXGRPSIG_INT64
#define Com_RxGrpSigType_u64     ( NULL_PTR )
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
#define Com_RxGrpSigType_f64     ( NULL_PTR )
#endif

#define Com_SecondRxGrpSigType_u8        ( NULL_PTR )
#define Com_SecondRxGrpSigType_u16       ( NULL_PTR )
#define Com_SecondRxGrpSigType_u32       ( NULL_PTR )

#ifdef COM_RXGRPSIG_INT64
#define Com_SecondRxGrpSigType_u64       ( NULL_PTR )
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
#define Com_SecondRxGrpSigType_f64       ( NULL_PTR )
#endif
#endif

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xRxRamBuf_tst Com_Lok_xRxRamBuf_acst[ 1u ] = {
   {
    (uint8 * )              Com_SigType_u8
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
   ,(uint8 * )             Com_SigType_dyn
#endif
   ,(uint16 * )            Com_SigType_u16
   ,(uint32 * )            Com_SigType_u32
#ifdef COM_RXSIG_INT64
   ,(uint64 * )            Com_SigType_u64
#endif
#ifdef COM_RXSIG_FLOAT64SUPP
   ,(float64 * )           Com_SigType_f64
#endif
#ifdef COM_RX_SIGNALGROUP
   ,(uint8 * )             Com_RxGrpSigType_u8
   ,(uint16 * )            Com_RxGrpSigType_u16
   ,(uint32 * )            Com_RxGrpSigType_u32
#ifdef COM_RXGRPSIG_INT64
   ,(uint64 * )            Com_RxGrpSigType_u64
#endif
#ifdef COM_RXGRPSIG_FLOAT64SUPP
   ,(float64 * )           Com_RxGrpSigType_f64
#endif
   ,(uint8 * )             Com_SecondRxGrpSigType_u8
   ,(uint16 * )            Com_SecondRxGrpSigType_u16
   ,(uint32 * )            Com_SecondRxGrpSigType_u32
#ifdef COM_RXGRPSIG_INT64
   ,(uint64 * )            Com_SecondRxGrpSigType_u64
#endif
#ifdef COM_RXGRPSIG_FLOAT64SUPP
   ,(float64 * )           Com_SecondRxGrpSigType_f64
#endif
#ifdef COM_RX_SIGNALGROUP_ARRAY
   ,(uint8 * )             Com_RxSigGrpArrayBuf_u8
#endif
#endif
#ifdef COM_RxIPduDeferredProcessing
   ,(uint8 * )             Com_DeferredBuffer
#endif
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

#ifdef COM_TX_SIGNALGROUP
#define Com_TxGrpSigType_u8          ( NULL_PTR )
#define Com_TxGrpSigType_u16         ( NULL_PTR )
#define Com_TxGrpSigType_u32         ( NULL_PTR )

#ifdef COM_TXGRPSIG_INT64
#define Com_TxGrpSigType_u64         ( NULL_PTR )
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
#define Com_TxGrpSigType_f64         ( NULL_PTR )
#endif

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_Lok_xTxSigGrpRamBuf_tst Com_Lok_xTxSigGrpRamBuf_acst[ 1u ] = {
   {
    (uint8 * )              Com_TxGrpSigType_u8,
    (uint16 * )             Com_TxGrpSigType_u16,
    (uint32 * )             Com_TxGrpSigType_u32
#ifdef COM_TXGRPSIG_INT64
   ,(uint64 * )            Com_TxGrpSigType_u64
#endif
#ifdef COM_TXGRPSIG_FLOAT64SUPP
   ,(float64 * )           Com_TxGrpSigType_f64
#endif
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

#endif

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_MainFunctionCfgType Com_MainFunctionCfg[ COM_NUM_OF_MAINFUNCTION ] = {
   {
        0u
   ,       11u
   ,       10u
   }
   ,{
        0u
   ,       4u
   ,       10u
   }
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

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

