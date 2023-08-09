

#ifndef COM_CFG_INTERNAL_H
#define COM_CFG_INTERNAL_H

#define COM_TX_TIME_BASE         ( 0.01f )

#define COM_RX_TIME_BASE         ( 0.01f )

#define COM_GW_TIME_BASE         ( 0.005f )

#if (defined(COM_RxSigUpdateBit) || defined(COM_TxSigUpdateBit) || defined(COM_RxSigGrpUpdateBit) || defined(COM_TxSigGrpUpdateBit))
#define COM_UPDATEBIT
#endif

#define COM_TxIPduTimeOut

#if (defined(COM_RxFilters) || defined(COM_TxFilters))
#define COM_FILTERS
#endif

#define COM_RxIPduCallOuts

#define COM_TxIPduCallOuts

#define COM_TxIPduNotification

#define COM_CONFIGURATION_USE_DET           STD_OFF

#define COM_VERSION_INFO_API                STD_OFF

#define COM_COMMON_TX_PERIOD                STD_OFF
#define COM_ENABLE_JITTERFLITER             STD_OFF

#define  COM_TXPDU_DEFERREDPROCESSING

#define COM_ARSRVLIB_SUPPORT

#define COM_RXTIMER_MAX            0xFFFFu

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

#define COM_NUM_TOTAL_IPDU_GRP              4u

#define COM_MAX_U32_VALUE                       (uint32)(0xFFFFFFFFUL)

#define COM_MAX_U64_VALUE                       (uint64)(0xFFFFFFFFFFFFFFFFULL)

#define COM_MAX_U32_INDEX                       (COM_MAX_U32_VALUE)

#define COM_SIGN_EXT_MASK                       (COM_MAX_U32_VALUE)

#define COM_SIG_MAX_NO_OF_BITS                  (32u)

#define COM_SIG_MAX_DATA                        (COM_MAX_U32_VALUE)

#define     ComMainFunction_Internal_MainFunctionRx               0

#define     ComMainFunction_Internal_MainFunctionTx               0

#if defined(COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX)
    typedef struct
    {
        uint32 Mask;
        uint32 X_Val;
    }Com_MaskXType;
#endif
#if defined(COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
    typedef struct
    {
        uint32 Min;
        uint32 Max;
    }Com_POSMinMaxType;
#endif
#if defined(COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
    typedef struct
    {
        sint32 Min;
        sint32 Max;
    }Com_NEGMinMaxType;
#endif
#ifdef COM_F_ONEEVERYN
    typedef struct
    {
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

# ifdef COM_RX_SIGNALGROUP_ARRAY

    typedef uint8 Com_RxSigGrpArrayIndexType;

    typedef uint8 Com_RxSigGrpBuffIndexType;

# endif

typedef uint32 Com_SigMaxType;

#ifdef COM_METADATA_SUPPORT

# define COM_MAX_METADATA_LENGTH_IN_BYTES     ( 4U )

typedef struct
{
    uint8 MetaDataLength;
    uint8 MetaDataDefaultValue[ COM_MAX_METADATA_LENGTH_IN_BYTES ];
} Com_MetaDataInfo;

typedef P2CONST( Com_MetaDataInfo, AUTOMATIC, COM_APPL_CONST ) Com_MetaDataInfoPtr;

#endif

typedef uint8  Com_MainFuncType;

typedef uint8 Com_NumOfIpdusType;

typedef uint8 Com_TimeBaseType;

#if defined (COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX)

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern  CONST(Com_MaskXType ,COM_CONST) Com_MaskX[];

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "Com_MemMap.h"
extern CONST(uint32 ,COM_CONST)  Com_Mask[];

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
extern VAR(uint32,COM_VAR)  Com_F_OldVal[];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"

#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_OldValTrigOnChngType,COM_VAR) Com_OldValTrigOnChng[];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#if defined(COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_POSMinMaxType ,COM_CONST) Com_POSMinMax[];

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#if defined(COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_NEGMinMaxType ,COM_CONST) Com_NEGMinMax[];

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#ifdef COM_F_ONEEVERYN

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_OneEveryNType,COM_CONST) Com_OneEveryN_Const[];

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_OneEveryNType,COM_VAR) Com_OneEveryN[];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#define Com_getfloat64InitValue(val) ((float64)0)

#ifdef COM_TxIPduNotification
#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void,COM_CODE) Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TxIPduTimeOutNotify
#endif

#ifdef COM_RxIPduTimeoutNotify

#endif

#endif

