#pragma once
/******************************************************************************/
/* File   : Com_Cfg_Internal.hpp                                              */
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
#define COM_VARIANT_PRE_COMPILE                   0
#define COM_VARIANT_LINK_TIME                     1
#define COM_VARIANT_POSTBUILD_LOADABLE            2
#define COM_VARIANT_POSTBUILD_SELECTABLE          3
#define COM_CONFIGURATION_VARIANT                 COM_VARIANT_PRE_COMPILE
#define COM_MAX_U8_VALUE                        (0xFFu)
#define COM_MAX_U16_VALUE                       (0xFFFFu)
#define COM_MAX_U32_VALUE                       (0xFFFFFFFFuL)
#define COM_MAX_U64_VALUE                       (0xFFFFFFFFFFFFFFFFuLL)
#define COM_TX_TIME_BASE         ( 0.01f )
#define COM_RX_TIME_BASE         ( 0.01f )
#define COM_GW_TIME_BASE         ( 0.005f )
#if(defined(COM_RxSigUpdateBit) || defined(COM_TxSigUpdateBit) || defined(COM_RxSigGrpUpdateBit) || defined(COM_TxSigGrpUpdateBit))
#define COM_UPDATEBIT
#endif

#define COM_TxIPduTimeOut

#if(defined(COM_RxFilters) || defined(COM_TxFilters))
#define COM_FILTERS
#endif

#define COM_RxIPduCallOuts
#define COM_TxIPduCallOuts
#define COM_CONFIGURATION_USE_DET           STD_OFF
#define COM_VERSION_INFO_API                STD_OFF
#define COM_COMMON_TX_PERIOD                STD_OFF
#define COM_ENABLE_JITTERFLITER             STD_OFF
#define COM_TXPDU_DEFERREDPROCESSING
#define COM_ARSRVLIB_SUPPORT
#define COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION   STD_ON
#define COM_RETRY_FAILED_TX_REQUESTS             STD_OFF
#define COM_ENABLE_PERIODIC_FRAME_SYNC           STD_OFF
#define COM_RXTIMER_MAX                         (COM_MAX_U16_VALUE)
#define COM_SigTriggered

#if defined(COM_SigTriggeredOnChange) || defined(COM_SigTriggeredOnChangeWithoutRepetition)
#define COM_EffectiveSigTOC
#endif

#if defined(COM_SigGrpTriggeredOnChange) || defined(COM_SigGrpTriggeredOnChangeWithoutRepetition)
#define COM_EffectiveSigGrpTOC
#endif

#define COM_NUM_OF_RX_MAINFUNCTION          1u
#define COM_NUM_OF_TX_MAINFUNCTION          1u
#define COM_NUM_OF_MAINFUNCTION             (COM_NUM_OF_RX_MAINFUNCTION + COM_NUM_OF_TX_MAINFUNCTION)
#define COM_TXIPDU_CNTR_INV_IDX             COM_MAX_U8_VALUE
#define COM_RXIPDU_CNTR_INV_IDX             COM_MAX_U8_VALUE
#define COM_NUM_TOTAL_IPDU_GRP              4u
#define COM_RxIPduDeferredProcessing

#if defined(COM_RxIPduDeferredProcessing) || defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)
#define COM_RX_MAINFUNCTION_PROC
#endif

#ifdef COM_TP_IPDUTYPE
#if defined(COM_RxSigInvalid) || defined(COM_RxSigGrpInvalid)
#define COM_RXIPDU_TP_INVALIDATION
#endif
#endif

#define COM_MAX_U32_INDEX                       (COM_MAX_U32_VALUE)
#define COM_SIGN_EXT_MASK                       (COM_MAX_U32_VALUE)
#define COM_SIG_MAX_NO_OF_BITS                  (32u)
#define COM_SIG_MAX_DATA                        (COM_MAX_U32_VALUE)
#define ComMainFunction_Internal_MainFunctionRx               0
#define ComMainFunction_Internal_MainFunctionTx               0

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
#if defined(COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX)
typedef struct{
   uint32 Mask;
   uint32 X_Val;
}Com_MaskXType;
#endif

#if defined(COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
typedef struct{
    uint32 Min;
    uint32 Max;
}Com_POSMinMaxType;
#endif

#if defined(COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
typedef struct{
    sint32 Min;
    sint32 Max;
}Com_NEGMinMaxType;
#endif

#ifdef COM_F_ONEEVERYN
typedef struct{
    uint32 Period;
    uint32 Offset;
    uint8  Occurrence;
}Com_OneEveryNType;
#endif

typedef uint16    Com_NoOfTxGrpSignalType;
typedef uint16    Com_NoOfRxGrpSignalType;

#ifdef COM_TX_SIGNALGROUP
typedef uint8    Com_TxIntGrpSignalIdType;
#endif

#ifdef COM_RX_SIGNALGROUP
typedef uint8    Com_RxIntGrpSignalIdType;
#endif

typedef uint8    Com_TxIntSignalIdType;
typedef uint8    Com_RxIntSignalIdType;

#ifdef COM_TX_SIGNALGROUP
 typedef uint8 Com_TxIntSignalGroupIdType;
#endif

#ifdef COM_RX_SIGNALGROUP
 typedef uint8 Com_RxIntSignalGroupIdType;
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)
typedef uint8   Com_OldValType;
typedef uint32 Com_OldValTrigOnChngType;
#endif

typedef uint8   Com_BitsizeType;
typedef uint8 Com_BitpositionType;
#if defined(COM_TxFilters) || defined (COM_RxFilters)
typedef uint8   Com_FilterType;
#endif

typedef uint8 Com_RxGwQueueIndexType;
typedef uint8 Com_SigBuffIndexType;
typedef uint8 Com_RxGrpSigBuffIndexType;
typedef uint8 Com_TxGrpSigBuffIndexType;

#ifdef COM_TX_SIGNALGROUP_ARRAY
typedef uint8 Com_TxSigGrpArrayIndexType;
# endif

#ifdef COM_RX_SIGNALGROUP_ARRAY
typedef uint8 Com_RxSigGrpArrayIndexType;
typedef uint8 Com_RxSigGrpBuffIndexType;
#endif

typedef uint32 Com_SigMaxType;

#ifdef COM_METADATA_SUPPORT
#define COM_MAX_METADATA_LENGTH_IN_BYTES     ( 4U )
typedef struct{
   uint8 MetaDataLength;
   uint8 MetaDataDefaultValue[ COM_MAX_METADATA_LENGTH_IN_BYTES ];
}Com_MetaDataInfo;

typedef const Com_MetaDataInfo * Com_MetaDataInfoPtr;
#endif

typedef uint8  Com_MainFuncType;
typedef uint8 Com_NumOfIpdusType;
typedef uint8 Com_TimeBaseType;

#ifdef COM_TX_IPDUCOUNTER
    typedef uint8  Com_TxCntrIdxType;
#endif

#ifdef COM_RX_IPDUCOUNTER
    typedef uint8  Com_RxCntrIdxType;
#endif

#if defined (COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
extern  const Com_MaskXType Com_MaskX[];
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
#define COM_START_SEC_CONFIG_DATA_32
#include "Com_MemMap.hpp"
extern const uint32 Com_Mask[];
#define COM_STOP_SEC_CONFIG_DATA_32
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_32
#include "Com_MemMap.hpp"
extern uint32 Com_F_OldVal[];
#define COM_STOP_SEC_VAR_CLEARED_32
#include "Com_MemMap.hpp"
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
extern Com_OldValTrigOnChngType Com_OldValTrigOnChng[];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#if defined(COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
extern const Com_POSMinMaxType Com_POSMinMax[];
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#if defined(COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
extern const Com_NEGMinMaxType Com_NEGMinMax[];
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#ifdef COM_F_ONEEVERYN
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"
extern const Com_OneEveryNType Com_OneEveryN_Const[];
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
extern Com_OneEveryNType Com_OneEveryN[];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
#endif

#define Com_getfloat64InitValue(val) ((float64)0)


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

