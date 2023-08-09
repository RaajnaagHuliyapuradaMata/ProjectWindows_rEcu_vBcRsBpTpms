

#define COM_DontUseExternalSymbolicNames
#include "Com_Prv.h"
#include "Com_Cbk.h"
#include "PduR_Com.h"
#include "Com_PBcfg.h"

#include "Com_PBcfg_InternalId.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xTxSigCfg_tst ,COM_CONST) Com_Lok_xTxSigCfg_acst[COM_NUM_TX_SIGNALS] =
{

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        56,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        48,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        40,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        32,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        24,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        16,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        8,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        0,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        48,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        49,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        63,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        62,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        61,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        60,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        56,

        4,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        40,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        32,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        16,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        24,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        11,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        15,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        3,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        7,

        1,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x6

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        8,

        3,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        12,

        3,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        4,

        3,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        0,

        3,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        56,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        48,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        40,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        32,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        24,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        16,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        8,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        0,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        56,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        48,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        40,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        32,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        24,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        16,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        8,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    },

    {
#ifdef COM_TxInvalid
        (uint32)(0uL),
#endif
        (uint32)(0uL),

        0x54,

#ifdef COM_TxSigUpdateBit
        COM_UPDATE_MAX,
#endif

        0,

        8,

#ifdef COM_TxFilters
        0xff,
#endif

#ifdef COM_EffectiveSigTOC
        0xff,
#endif

        (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        0x0

    }

};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xRxSigCfg_tst ,COM_CONST) Com_Lok_xRxSigCfg_acst[COM_NUM_RX_SIGNALS] =
{

    {
#ifdef COM_RxSignalNotify

        NULL_PTR,
#endif
#ifdef COM_RxSigInvalidNotify

        NULL_PTR,
#endif
#ifdef COM_RxSigInvalid
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       56,
       0,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       48,
       1,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40,
       2,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       32,
       3,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24,
       4,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16,
       5,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8,
       6,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       7,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       45,
       8,

      1,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,

        0x26,

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
       (uint32)(0x0uL),
#endif
           (uint32)(0x0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       48,

      5,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       52,
       9,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       54,
       10,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8,
       11,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       12,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       14,
       13,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       12,
       14,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40,
       0,

      16,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x22,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24,
       1,

      16,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        0x22,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8,
       15,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       16,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       14,
       17,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40,
       2,

      16,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x22,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       12,
       18,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24,
       3,

      16,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x22,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       52,
       19,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       54,
       20,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8,
       21,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       22,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       12,
       23,

      1,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x26,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       13,
       24,

      1,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x26,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       14,
       25,

      1,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x26,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       56,
       4,

      16,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x22,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       15,
       26,

      1,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x26,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40,
       27,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       32,
       28,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24,
       29,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16,
       30,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       56,
       31,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       48,
       32,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       40,
       33,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       32,
       34,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8,
       35,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       36,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16,
       37,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       24,
       38,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       39,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16,
       40,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VehSts_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       16,
       41,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       0,
       42,

      8,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       8,
       43,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       28,
       44,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       20,
       45,

      4,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       30,
       46,

      2,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x20,

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
       (uint32)(0uL),
#endif
           (uint32)(0uL),
#ifdef COM_RxSigUpdateBit
       COM_UPDATE_MAX,
#endif
       27,
       47,

      1,

#ifdef COM_RxFilters
        0xff,
#endif

       (Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        0x26,

        0x28
    }

};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

static CONST(Com_TransModeInfo ,COM_CONST) Com_ApplicationCyclic_TPM_Can_Network_CANNODE_0_TransModeInfo[] =
{

    {
        1,

        1,

        0,

        0,

#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC,
        COM_FALSE
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
        COM_TXMODE_PERIODIC,
        COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif

    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

static CONST(Com_TransModeInfo ,COM_CONST) Com_HMIPressure_TPM_Can_Network_CANNODE_0_TransModeInfo[] =
{

    {
        100,

        1,

        0,

        0,

#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC,
        COM_FALSE
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
        COM_TXMODE_PERIODIC,
        COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif

    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

static CONST(Com_TransModeInfo ,COM_CONST) Com_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_TransModeInfo[] =
{

    {
        100,

        1,

        0,

        0,

#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_PERIODIC,
        COM_FALSE
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
        COM_TXMODE_PERIODIC,
        COM_FALSE
#else
        COM_TXMODE_PERIODIC
#endif

    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

static CONST(Com_TransModeInfo ,COM_CONST) Com_ApplicationResponse_TPM_Can_Network_CANNODE_0_TransModeInfo[] =
{

    {
        0,

        1,

        0,

        0,

#ifdef COM_MIXEDPHASESHIFT
        COM_TXMODE_DIRECT,
        COM_FALSE
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
        COM_TXMODE_DIRECT,
        COM_FALSE
#else
        COM_TXMODE_DIRECT
#endif

    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xTxIpduInfoCfg_tst ,COM_CONST) Com_Lok_xTxIpduCfg_acst[COM_NUM_TX_IPDU] =
{
    {

        Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0,

        Com_ApplicationCyclic_TPM_Can_Network_CANNODE_0_TransModeInfo,

        #ifdef COM_TxIPduCallOuts

        &Com_IPdu_Callout_ApplicationCyclic_TPM,

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

        8,
        #ifdef COM_TX_SIGNALGROUP

        0,
        #endif

        (PduIdType)PduRConf_PduRSrcPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0_Com2PduR,

        (Com_TxIntSignalIdType)ComSignal_Internal_AppCyclic_7,
        #ifdef COM_TX_SIGNALGROUP

        0,
        #endif

        0x4000,

        ComMainFunction_Internal_MainFunctionTx,

        0xFF

    },
    {

        Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0,

        Com_HMIPressure_TPM_Can_Network_CANNODE_0_TransModeInfo,

        #ifdef COM_TxIPduCallOuts

        &Com_IPdu_Callout_HMIPressure_TPM,

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

        (PduIdType)PduRConf_PduRSrcPdu_HMIPressure_TPM_Can_Network_CANNODE_0_Com2PduR,

        (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_LOCATE_Status,
        #ifdef COM_TX_SIGNALGROUP

        0,
        #endif

        0x4000,

        ComMainFunction_Internal_MainFunctionTx,

        0xFF

    },
    {

        Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,

        Com_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_TransModeInfo,

        #ifdef COM_TxIPduCallOuts

        &Com_IPdu_Callout_HMITempAndRefPress_TPM,

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

        (PduIdType)PduRConf_PduRSrcPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_Com2PduR,

        (Com_TxIntSignalIdType)ComSignal_Internal_TIRE_REF_PRESS_RR,
        #ifdef COM_TX_SIGNALGROUP

        0,
        #endif

        0x4000,

        ComMainFunction_Internal_MainFunctionTx,

        0xFF

    },
    {

        Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0,

        Com_ApplicationResponse_TPM_Can_Network_CANNODE_0_TransModeInfo,

        #ifdef COM_TxIPduCallOuts

        &Com_IPdu_Callout_ApplicationResponse_TPM,

        #endif
        #ifdef COM_TxIPduNotification

        &Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0,
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

        8,
        #ifdef COM_TX_SIGNALGROUP

        0,
        #endif

        (PduIdType)PduRConf_PduRSrcPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0_Com2PduR,

        (Com_TxIntSignalIdType)ComSignal_Internal_AppResponse_7,
        #ifdef COM_TX_SIGNALGROUP

        0,
        #endif

        0x4000,

        ComMainFunction_Internal_MainFunctionTx,

        0xFF

    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#ifdef COM_RxSigUpdateTimeout
#endif

#ifdef COM_RxSigGrpUpdateTimeout
#endif

#ifdef COM_RxSigUpdateTimeout
#endif

#ifdef COM_RxSigGrpUpdateTimeout
#endif

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xRxIpduInfoCfg_tst ,COM_CONST) Com_Lok_xRxIpduCfg_acst[COM_NUM_RX_IPDU] =
{
    {

        Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_ApplicationRequest,

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

        (Com_RxIntSignalIdType)ComSignal_Internal_AppReqCmd_7,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_BCM_peripheralMasterClock,

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

        2,
        #ifdef COM_RX_SIGNALGROUP

        0,
        #endif

        (Com_RxIntSignalIdType)ComSignal_Internal_BCM_peripherialMasterClockValid,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN,

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

        (Com_RxIntSignalIdType)ComSignal_Internal_ESP_Wheel_Dir_Right_Front,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN,

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

        (Com_RxIntSignalIdType)ComSignal_Internal_ESP_WSpeed_Rear_Message_Counter,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped,

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

        11,
        #ifdef COM_RX_SIGNALGROUP

        0,
        #endif

        (Com_RxIntSignalIdType)ComSignal_Internal_ESP_Wheel_Pulse_Stamped_MC,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_RdcData_TPM,

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

        (Com_RxIntSignalIdType)ComSignal_Internal_User_defined_val_5,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_TMM_Status_BodyLCAN,

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

        (Com_RxIntSignalIdType)ComSignal_Internal_TMM_TempAmb,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_VehSts_BodyLCAN,

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

        (Com_RxIntSignalIdType)ComSignal_Internal_VehModCurr,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    },
    {

        Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

        #ifdef COM_RxSigUpdateTimeout

        NULL_PTR,
        #endif
        #ifdef COM_RxSigGrpUpdateTimeout

        NULL_PTR,
        #endif

        #ifdef COM_RxIPduCallOuts

        &Com_IPdu_Callout_VmsStsReq_BodyLCAN,

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

        7,
        #ifdef COM_RX_SIGNALGROUP

        0,
        #endif

        (Com_RxIntSignalIdType)ComSignal_Internal_VmsStateFdbk,
         #ifdef COM_RX_SIGNALGROUP

        0,
        #endif
#ifdef COM_SIGNALGATEWAY
        0,
#endif
#ifdef COM_SIGNALGROUPGATEWAY
        0,
#endif

        ComMainFunction_Internal_MainFunctionRx,

        0x0

    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xIpduGrpInfoCfg_tst ,COM_CONST) Com_Lok_xIpduGrpCfg_acst[4] =
{
{

    0,

    9
}
,{

    9,

    0
}
,{

    13,

    0
}
,{

    14,

    0
}

};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_IpduIdType ,COM_CONST) Com_Lok_xIPduGrp_IpduRefCfg_au8[15] =
{

    ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_VehSts_BodyLCAN_Can_Network_CANNODE_0,
    ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,

    (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0),
    (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0),
    (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0),
    (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0),

    (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0),

    (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0)
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#if defined ( COM_TX_SIGNALGROUP_ARRAY )

# define Com_Lok_xTxSigGrpArrayCfg_acst      ( NULL_PTR )
#endif

#if defined ( COM_RX_SIGNALGROUP_ARRAY )

# define Com_Lok_xRxSigGrpArrayCfg_acst      ( NULL_PTR )
#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

    VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0[8];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

    VAR(uint8,COM_VAR) Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0[8];

    VAR(uint8,COM_VAR) Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0[8];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
VAR(uint32,COM_VAR) Com_F_OldVal[1];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
#endif

#if defined(COM_EffectiveSigTOC) || defined(COM_EffectiveSigGrpTOC)

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_OldValTrigOnChngType,COM_VAR) Com_OldValTrigOnChng[1];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#ifdef COM_F_ONEEVERYN

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
CONST(Com_OneEveryNType,COM_CONST) Com_OneEveryN_Const[1] =
{

{    1,    5, 1    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_OneEveryNType,COM_VAR) Com_OneEveryN[1];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#ifdef COM_TP_IPDUTYPE
VAR(PduLengthType,COM_VAR)          Com_TpTxIpduLength_auo[COM_NUM_TX_IPDU];
#endif

VAR(Com_TxIpduRamData,COM_VAR)      Com_TxIpduRam_s[COM_NUM_TX_IPDU];

VAR(Com_RxIpduRamData,COM_VAR)      Com_RxIpduRam_s[COM_NUM_RX_IPDU];

VAR(Com_TxSignalFlagType,COM_VAR)   Com_TxSignalFlag[COM_NUM_TX_SIGNALS];

VAR(Com_RxSignalFlagType,COM_VAR)   Com_RxSignalFlag[COM_NUM_RX_SIGNALS];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

VAR(uint8,COM_VAR)    Com_IpduCounter_s[COM_NUM_TX_IPDU + COM_NUM_RX_IPDU];

VAR(uint8,COM_VAR)    Com_IpduCounter_DM[COM_NUM_RX_IPDU];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
VAR(PduIdType,COM_VAR)    Com_RxGwQueue_aux[COM_NUM_GWSRC_IPDUS+1u];

VAR(Com_RxGwQueueRAMType,COM_VAR)   Com_RxGwQueue_S;

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_RxSignalGrpFlagType,COM_VAR) Com_RxSignalGrpFlag[1u];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#ifdef COM_TX_SIGNALGROUP
#if defined(COM_EffectiveSigGrpTOC) || defined(COM_SIGNALGROUPGATEWAY)

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_TxSignalGrpFlagType,COM_VAR) Com_TxSignalGrpFlag[1u];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_TxGrpSignalFlagType,COM_VAR) Com_TxGrpSignalFlag[1u];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif

#ifdef COM_RxIPduDeferredProcessing

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

    VAR(uint8,COM_VAR) Com_DeferredBuffer[ 8 ];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
#include "Com_MemMap.h"

    VAR(boolean, AUTOMATIC) Com_IsGwSignalsUpdated_ab[ COM_NUM_GWSRC_IPDUS ];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
#include "Com_MemMap.h"

#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_MaskXType ,COM_CONST) Com_MaskX[1] =
{

{    1,    5    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "Com_MemMap.h"

CONST(uint32 ,COM_CONST) Com_Mask[1] =
{

    1
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "Com_MemMap.h"

#endif

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_POSMinMaxType ,COM_CONST) Com_POSMinMax[1]=
{

{    1,    5    }

};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_NEGMinMaxType ,COM_CONST) Com_NEGMinMax[1] =
{

{    1,    5    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

VAR(uint8,COM_VAR) Com_SigType_u8[53];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"

VAR(uint16,COM_VAR) Com_SigType_u16[5];

#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"

#define Com_SigType_u32          ( NULL_PTR )

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

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xRxRamBuf_tst, COM_CONST) Com_Lok_xRxRamBuf_acst[ 1u ] =
{
    {
        (P2VAR(uint8, TYPEDEF, COM_APPL_DATA))              Com_SigType_u8

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
        ,(P2VAR(uint8, TYPEDEF, COM_APPL_DATA))             Com_SigType_dyn
#endif

        ,(P2VAR(uint16, TYPEDEF, COM_APPL_DATA))            Com_SigType_u16

        ,(P2VAR(uint32, TYPEDEF, COM_APPL_DATA))            Com_SigType_u32

#ifdef COM_RXSIG_INT64
        ,(P2VAR(uint64, TYPEDEF, COM_APPL_DATA))            Com_SigType_u64
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
        ,(P2VAR(float64, TYPEDEF, COM_APPL_DATA))           Com_SigType_f64
#endif

#ifdef COM_RX_SIGNALGROUP
        ,(P2VAR(uint8, TYPEDEF, COM_APPL_DATA))             Com_RxGrpSigType_u8

        ,(P2VAR(uint16, TYPEDEF, COM_APPL_DATA))            Com_RxGrpSigType_u16

        ,(P2VAR(uint32, TYPEDEF, COM_APPL_DATA))            Com_RxGrpSigType_u32

#ifdef COM_RXGRPSIG_INT64
        ,(P2VAR(uint64, TYPEDEF, COM_APPL_DATA))            Com_RxGrpSigType_u64
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        ,(P2VAR(float64, TYPEDEF, COM_APPL_DATA))           Com_RxGrpSigType_f64
#endif

        ,(P2VAR(uint8, TYPEDEF, COM_APPL_DATA))             Com_SecondRxGrpSigType_u8

        ,(P2VAR(uint16, TYPEDEF, COM_APPL_DATA))            Com_SecondRxGrpSigType_u16

        ,(P2VAR(uint32, TYPEDEF, COM_APPL_DATA))            Com_SecondRxGrpSigType_u32

#ifdef COM_RXGRPSIG_INT64
        ,(P2VAR(uint64, TYPEDEF, COM_APPL_DATA))            Com_SecondRxGrpSigType_u64
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        ,(P2VAR(float64, TYPEDEF, COM_APPL_DATA))           Com_SecondRxGrpSigType_f64
#endif

#ifdef COM_RX_SIGNALGROUP_ARRAY
        ,(P2VAR(uint8, TYPEDEF, COM_APPL_DATA))             Com_RxSigGrpArrayBuf_u8
#endif

#endif

#ifdef COM_RxIPduDeferredProcessing
        ,(P2VAR(uint8, TYPEDEF, COM_APPL_DATA))             Com_DeferredBuffer
#endif
    }

};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

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

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_Lok_xTxSigGrpRamBuf_tst, COM_CONST) Com_Lok_xTxSigGrpRamBuf_acst[ 1u ] =
{
    {
        (P2VAR(uint8, TYPEDEF, COM_APPL_DATA))              Com_TxGrpSigType_u8,

        (P2VAR(uint16, TYPEDEF, COM_APPL_DATA))             Com_TxGrpSigType_u16,

        (P2VAR(uint32, TYPEDEF, COM_APPL_DATA))             Com_TxGrpSigType_u32

#ifdef COM_TXGRPSIG_INT64
        ,(P2VAR(uint64, TYPEDEF, COM_APPL_DATA))            Com_TxGrpSigType_u64
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
        ,(P2VAR(float64, TYPEDEF, COM_APPL_DATA))           Com_TxGrpSigType_f64
#endif

    }

};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Com_MainFunctionCfgType, COM_CONST) Com_MainFunctionCfg[ COM_NUM_OF_MAINFUNCTION ] =
{
    {

        0u,
        9u,
        10u
    }
    ,{

        0u,
        4u,
        10u
    }
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

