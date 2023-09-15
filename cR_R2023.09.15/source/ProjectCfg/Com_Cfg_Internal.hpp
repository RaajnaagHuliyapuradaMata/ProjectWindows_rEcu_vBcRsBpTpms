#ifndef COM_CFG_INTERNAL_H
#define COM_CFG_INTERNAL_H

#define COM_CONFIGURATION_USE_DET           STD_OFF
#define COM_VERSION_INFO_API                STD_OFF
#define COM_COMMON_TX_PERIOD                STD_OFF
#define COM_ENABLE_JITTERFLITER             STD_OFF

#define COM_TxIPduTimeOut
#define COM_RxIPduCallOuts
#define COM_TxIPduCallOuts
#define COM_TxIPduNotification
#define COM_TXPDU_DEFERREDPROCESSING
#define COM_ARSRVLIB_SUPPORT
#define COM_SigTriggered

#define COM_TX_TIME_BASE                                                 (0.01f)
#define COM_RX_TIME_BASE                                                 (0.01f)
#define COM_GW_TIME_BASE                                                (0.005f)
#define COM_RXTIMER_MAX                                                  0xFFFFu
#define COM_NUM_OF_RX_MAINFUNCTION                                            1u
#define COM_NUM_OF_TX_MAINFUNCTION                                            1u
#define COM_NUM_OF_MAINFUNCTION (COM_NUM_OF_RX_MAINFUNCTION + COM_NUM_OF_TX_MAINFUNCTION)
#define COM_NUM_TOTAL_IPDU_GRP                                                5u
#define COM_MAX_U32_VALUE                                 (uint32)(0xFFFFFFFFUL)
#define COM_MAX_U64_VALUE                        (uint64)(0xFFFFFFFFFFFFFFFFULL)
#define COM_MAX_U32_INDEX                                    (COM_MAX_U32_VALUE)
#define COM_SIGN_EXT_MASK                                    (COM_MAX_U32_VALUE)
#define COM_SIG_MAX_NO_OF_BITS                                             (32u)
#define COM_SIG_MAX_DATA                                     (COM_MAX_U32_VALUE)
#define ComMainFunction_Internal_MainFunctionRx                                0
#define ComMainFunction_Internal_MainFunctionTx                                0
#define Com_getfloat64InitValue(val)                                ((float64)0)

typedef uint16    Com_NoOfTxGrpSignalType;
typedef uint16    Com_NoOfRxGrpSignalType;
typedef uint8    Com_TxIntSignalIdType;
typedef uint8    Com_RxIntSignalIdType;
typedef uint8   Com_BitsizeType;
typedef uint8 Com_BitpositionType;
typedef uint8 Com_RxGwQueueIndexType;
typedef uint8 Com_SigBuffIndexType;
typedef uint8 Com_RxGrpSigBuffIndexType;
typedef uint8 Com_TxGrpSigBuffIndexType;
typedef uint32 Com_SigMaxType;
typedef uint8  Com_MainFuncType;
typedef uint8 Com_NumOfIpdusType;
typedef uint8 Com_TimeBaseType;


FUNC(void,COM_CODE) Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0(void);

#endif

