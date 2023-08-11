

#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

#include "PduR.h"
#include "PduR_Cfg_Internal.h"
#include "ComStack_Types.h"

typedef enum {
   PDUR_UNINIT,
   PDUR_REDUCED,
   PDUR_ONLINE
} PduR_StateType;

#define PDU_CNLDO   0x00u

#define PDU_CNLNB   0x01u

#define PDU_CNLOR   0x02u

#define PDUR_FIFO_IF    0u

#define PDUR_UCFIFO_TP  1u

#define PDUR_UCSEB_TP   2u

#define PDUR_MCSEB_TP   3u

#define PduR_IH_CancelTransmit_Func    PduR_invId_UpCancelTransmit

#define PduR_IH_CancelReceive_Func    PduR_invId_UpCancelReceive

#define PduR_IH_TriggerTransmit_Func    PduR_invId_IfTriggerTransmit

typedef uint8 PduR_CancelReasonType;

typedef uint8 PduR_LayerType;

typedef struct{
   uint8    bufferLock;
   uint8    lowerLayers;
}PduR_LockType;
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

typedef PduR_LockType   PduR_BuffLockType;
#else

typedef uint8           PduR_BuffLockType;
#endif

typedef struct{
   Std_ReturnType (*PduR_loTransmitFunc) ( PduIdType id, const PduInfoType * info );
}PduR_loTransmitFuncType;

typedef struct{
   Std_ReturnType (*PduR_loCancelTransmitFunc) ( PduIdType id );
}PduR_loCancelTransmitFuncType;

typedef struct{
   Std_ReturnType (*PduR_loCancelReceiveFunc) ( PduIdType id );
}PduR_loCancelReceiveFuncType;

typedef struct{
   void (*PduR_upIfRxIndicationFunc) ( PduIdType gwayId, const PduInfoType * data );
}PduR_upIfRxIndicationFuncType;

typedef struct{
    #if (AUTOSAR_VERSION_AR42 == STD_ON)
    void (*PduR_upIfTxConfirmationFunc) ( PduIdType id );
    #else
    void (*PduR_upIfTxConfirmationFunc) ( PduIdType id, Std_ReturnType result );
    #endif
}PduR_upIfTxConfirmationFuncType;

typedef struct{
   Std_ReturnType (*PduR_upIfTriggerTxFunc) ( PduIdType gwayId, PduInfoType * dataPtr );
}PduR_upIfTriggerTxFuncType;

typedef struct{
   BufReq_ReturnType (*PduR_upTpCopyRxDataFunc) ( PduIdType gwId, const PduInfoType * info, PduLengthType* bufferSizePtr );
}PduR_upTpCopyRxDataFuncType;

typedef struct{
   BufReq_ReturnType (*PduR_upTpStartOfReceptionFunc) ( PduIdType gwId,const PduInfoType * info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
}PduR_upTpStartOfReceptionFuncType;

typedef struct{
   void (*PduR_upTpRxIndicationFunc) ( PduIdType gwId, Std_ReturnType result );
}PduR_upTpRxIndicationFuncType;

typedef struct{

    BufReq_ReturnType (*PduR_upTpCopyTxDataFunc) ( PduIdType gwId, const PduInfoType * info, RetryInfoType* retry, PduLengthType* availableDataPtr);
}PduR_upTpCopyTxDataFuncType;

typedef struct{
   void (*PduR_upTpTxConfirmationFunc) ( PduIdType gwId, Std_ReturnType result);
}PduR_upTpTxConfirmationFuncType;

typedef uint8 PduR_loTransmitFP;

typedef uint8 PduR_loCancelTransmitFP;

typedef uint8 PduR_upIfRxIndicationFP;

typedef uint8 PduR_upIfTxConfirmationFP;

typedef uint8 PduR_upIfTriggerTxFP;

typedef uint8 PduR_upTpStartOfReceptionFP;

typedef uint8 PduR_upTpProvideRxBufFP;

typedef uint8 PduR_upTpRxIndicationFP;

typedef uint8 PduR_upTpProvideTxBufFP;

typedef uint8 PduR_upTpTxConfirmationFP;

typedef struct{
    PduIdType                    loId;
    PduR_loTransmitFP            loTransmitID;
    PduR_loCancelTransmitFP      loCancelTransmitID;
} PduR_RT_UpToLo;

typedef struct{
    PduIdType                    upId;
    PduR_upIfRxIndicationFP      upRxIndicationID;
} PduR_RT_LoIfRxToUp;

typedef struct{
    PduIdType                    upId;
    PduR_upIfTxConfirmationFP    upTxConfirmationID;
} PduR_RT_LoIfTxToUp;

typedef struct{
    PduIdType                    upId;
    PduR_upIfTriggerTxFP         upTriggerTxID;
    PduR_upIfTxConfirmationFP    upTxConfirmationID;
 } PduR_RT_LoTtIfTxToUp;

typedef struct{
   PduIdType                    upId;
   PduR_upTpStartOfReceptionFP  upStartOfReceptionID;
   PduR_upTpProvideRxBufFP      upProvideRxBufID;
   PduR_upTpRxIndicationFP      upRxIndicationID;
} PduR_RT_LoTpRxToUp;

typedef struct{
    PduIdType                    upId;
    PduR_upTpProvideTxBufFP      upProvideTxBufID;
    PduR_upTpTxConfirmationFP    upTxConfirmationID;
} PduR_RT_LoTpTxToUp;

typedef struct{
   PduR_RT_UpToLo               upToLo;
    #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

   PduR_RoutingPathGroupIdType  routingCntrl_Idx;
   #endif
   boolean                      isTpModule;
   PduIdType                    upId;
   PduIdType                    upLayerSymName;
   uint8                        upSrcLayerName;
} PduR_MT_UpToLo;

typedef struct{
    PduR_RT_LoTtIfTxToUp         toUp;
    uint8                        destLowerLayers;
} PduR_MT_LoIfTxToUp;

typedef struct{
   PduInfoType * pduPtr;
   BufReq_ReturnType            allocError;
   Std_ReturnType              txFailure;
   PduR_LayerType               txConf;
  } PduR_MS_LoTpTxToUp;

typedef struct{
    PduR_RT_LoTpTxToUp           toUp;
    uint8                        destLowerLayers;
} PduR_MT_LoTpTxToUp;

typedef struct{
   PduLengthType                length;
   PduIdType                    loId;
   PduR_loTransmitFP            transmitID;
} PduR_GT_IfTx;

typedef struct{
   void * buffer;
   PduIdType                    loId;
   PduR_loTransmitFP            transmitID;
   boolean                      isFifoType;
} PduR_GT_If;

typedef struct{
    uint8 * bufferPtr;
    uint8 * readPtr;
    uint8 * writePtr;
 #if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
    const PduInfoType * infoPtr;
 #endif
    PduLengthType                        numRxLength_auo[PDUR_MAX_QUEUEDEPTH];
    PduLengthType                        numTxLength;
    PduLengthType                        SduLength_auo[PDUR_MAX_QUEUEDEPTH];
    PduLengthType                        bufferLength;
 #ifdef PDUR_STORE_AND_FORWARD
    PduLengthType                        remainingBuffLength;
    PduLengthType                        RxChunkLength;
    PduLengthType                        TxChunkLength;
 #endif
    uint8                                Rx_Status;
    uint8                                Tx_Status;
    uint8                                Tx_E_OK_Count;
    uint8                                Rx_FifoInstanceUsed_u8;
    uint8                                Tx_FifoInstanceUsed_u8;

 } PduR_TpSession_Dynamic;

typedef PduR_TpSession_Dynamic * PduR_TpSessDynPtr;

typedef struct{
    PduR_TpSession_Dynamic * GwTpSessionPtr;
}PduR_GwTp_SessionListType;

typedef const PduR_GwTp_SessionListType * PduR_GwTp_SessionListPtr;

typedef struct{
    uint8 * PduR_UpIfTxConf_ConfigPtr;
}PduR_UpIfTxConf_Config;

typedef struct{
   PduR_TpSession_Dynamic * primarySession;

#ifdef PDUR_QUEUEING_SUPPORT
   PduR_TpSession_Dynamic * secondarySession;
   uint8                                                 activeSessionCount;
#endif
} PduR_TpConnection_Dynamic;

typedef PduR_TpConnection_Dynamic * PduR_TpConnDynPtr;

typedef struct{
   uint8 * begin;
   PduR_TpConnection_Dynamic * connectionTable;
   PduLengthType                     eltSize;
   uint16                            buffPoolId;
} PduR_FIFO_Tp_fixed;

typedef struct{
   const PduR_FIFO_Tp_fixed*   buffer;
   PduLengthType               numOfLowerLayers;

   PduLengthType               TpGwQueueSize;

   PduIdType                   loId;
   PduIdType                   upId;
   uint16                      TpThreshold;
   PduR_loTransmitFP           loTransmitID;
#ifdef PDUR_FIFO_TP_SUPPORT
   uint8                       TpQueueDepth_u8;
#endif
} PduR_GT_Tp;

typedef const PduR_GT_Tp * PduR_GT_TpPtr;

typedef struct{
    PduR_RT_LoTpRxToUp loTpRxToUp;
    PduR_RoutingPathGroupIdType  routingCntrl_Idx;
}PduR_RPG_LoTpRxToUp;

typedef const PduR_RPG_LoTpRxToUp *PduR_RPG_TpRxToUpPtr;

typedef uint8 PduR_loCancelReceiveFP;

typedef struct{
   PduIdType                    LoTpRxId;

   PduR_loCancelReceiveFP       CancelRxFP;
} PduR_RT_UpTpRxToLoTp;

typedef struct{
   const PduR_RT_UpTpRxToLoTp * UpTpToLoTp;
   PduIdType                                                 UpTpToLoTp_NrEntries;
} PduR_UpTpToLoTpRxConfig;

typedef uint8 PduR_ParameterValueType;

typedef struct{
    PduInfoType                       info;
    PduR_BuffLockType * lockPtr;
    PduInfoType * readerPduInfo;
} PduR_SingleEntryBuffer;

typedef const PduR_SingleEntryBuffer * PduR_SingleEntryBufferPtr;

typedef struct{
   uint8*                                  readPtr;
   uint8*                                  writePtr;
   PduLengthType                           actLen[PDUR_FIFO_IF_MAXSIZE];
   uint8                                   used;
   uint8                                   txConfPending;
   uint8                                   readIndex;
   uint8                                   writeIndex;
  } PduR_FIFO_If_dynamic;

typedef struct{
   uint8                    byteDefaultValue;
   uint8                    bytePosition;
} PduR_DefaultValues_fixed;

typedef struct{
    PduInfoType * gwBuf;
    uint8 * begin;
    const PduR_DefaultValues_fixed * defaultValueElement;
    uint8                                   defaultValueSize;
    uint8                                   confLen;
    uint8                                   Tx_Status;
} PduR_Buf_If_dynamic;

typedef PduR_FIFO_If_dynamic * PduR_FifoDynIfPtr;

typedef struct{
   uint8 * begin;
   void * dyn;
   PduLengthType                     eltSize;
   uint8                             nrElts;
} PduR_FIFO_fixed;

typedef const PduR_FIFO_fixed * PduR_FifoType;

typedef struct{
   const PduR_RT_UpToLo * CddToLo;
   const PduR_MT_UpToLo * CddToLoMc;
   PduIdType                                             CddToLo_NrEntries;
} PduR_CddConfig;

typedef struct{
   const PduR_RT_LoTpRxToUp * LoTpRxToUp;
   const PduR_RT_LoTpTxToUp * LoTpTxToUp;
   PduIdType                                                 LoTpRxToUp_NrEntries;
   PduIdType                                                 LoTpTxToUp_NrEntries;
} PduR_LoTpConfig;

typedef struct{
   const PduR_RT_UpToLo * UpToLo;
   const PduR_MT_UpToLo * UpToLoMc;
   PduIdType                                                 UpToLo_NrEntries;
} PduR_UpConfig;

typedef struct{
   const PduR_RT_LoIfRxToUp * LoIfRxToUp;
   const PduR_RT_LoIfTxToUp * LoIfTxToUp;
   PduIdType                                                 LoIfRxToUp_NrEntries;
   PduIdType                                                 LoIfTxToUp_NrEntries;
} PduR_LoIfDConfig;

typedef struct{
    const PduR_RT_LoIfRxToUp * LoIfRxToUp;
    const PduR_RT_LoTtIfTxToUp * LoIfTxToUp;
   PduIdType                                                 LoIfRxToUp_NrEntries;
   PduIdType                                                 LoIfTxToUp_NrEntries;
} PduR_LoIfTTConfig;

typedef void * PduR_RPGVoidPtr;

typedef struct{
    PduR_RPGVoidPtr             destInfo;
    uint8                       pathType;
} PduR_TargetInfoType;

typedef struct{
    uint8 * begin;
    const PduR_DefaultValues_fixed * defaultValueElement;
    uint8                                   defaultValueSize;
}PduR_DefaultValue_Info;

typedef struct{
    const PduR_TargetInfoType * targetInfo;
    const PduR_DefaultValue_Info * defaultValue_info;
    PduR_RoutingPathGroupIdType                         rpg_Idx;
    uint8                                               cntDestOfTypeFIFO;
    uint8                                               cntOfDestWithDefValue;
} PduR_RPGInfoType;

typedef struct{
    const PduR_loTransmitFuncType * loTxTablePtr;
    const PduR_loCancelReceiveFuncType * loCancelRxTable;
    const PduR_loCancelTransmitFuncType * loCnclTxTablePtr;
    const PduR_upIfRxIndicationFuncType * upIfRxIndTablePtr;
    const PduR_upIfTxConfirmationFuncType * upIfTxConfTablePtr;
    const PduR_upTpCopyRxDataFuncType * upTpRxDataTablePtr;
    const PduR_upTpStartOfReceptionFuncType * upTpStartRxTablePtr;
    const PduR_upTpRxIndicationFuncType * upTpRxIndTablePtr;
    const PduR_upTpCopyTxDataFuncType * upTpTxDataTablePtr;
    const PduR_upTpTxConfirmationFuncType * upTpTxConfTablePtr;
    const PduR_upIfTriggerTxFuncType * upIfTrigTxTablePtr;
} PduR_RPTablesType;

typedef struct{
    const PduR_CddConfig * cddConf;
    const PduR_LoTpConfig * LoTpConf;
    const PduR_LoIfDConfig * LoIfDConf;
    const PduR_LoIfTTConfig * LoIfTTConf;
    const PduR_UpConfig * UpIfConf;
    const PduR_UpConfig * UpTpConf;
    const PduR_MT_UpToLo * gwToLoMc;
    const PduR_MT_LoIfTxToUp * loIfTxToUpMc;
    const PduR_MT_LoTpTxToUp * loTpTxToUpMc;
    PduR_MS_LoTpTxToUp * loTpTxToUpMs;

    const PduR_GT_IfTx * gwIfTx;
    const PduR_GT_If * gwIf;
    const PduR_GT_Tp * gwTp;
    const PduR_RPG_LoTpRxToUp * rpgRxTp;
    const PduR_RPTablesType * PduR_RPTablesPtr;
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
    const PduR_GwTp_SessionListType * gwTp_SessionListPtr;
#endif
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT != 0)
    const PduR_UpIfTxConf_Config * UpIfTxConf_Config;
#endif
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
    const PduR_RPGInfoType * rpg_ConfigInfo;
    const boolean * rpg_EnRoutingInfo;
    boolean * pduR_Rpg_Status;
    PduR_RoutingPathGroupIdType                            rpg_NrEntries;
#endif
    const PduR_UpTpToLoTpRxConfig * PduR_UpTpToLoTpRxCfg;
    uint16                                                 configId;
    uint16                                                 totalNoOfGwTpRps;
    uint16                                                 totalNoOfGwIfRps;
    PduIdType                                              loTpTxToUpMc_NrEntries;
} PduR_PBConfigType;

typedef struct{
    Dem_EventStatusType initFailedErrorStatus;
    Dem_EventStatusType instanceLostErrorStatus;
    boolean initFailedErrorFlag;
    boolean instanceLostErrorFlag;
}PduR_DsmReInitType;

typedef uint8 PduR_ReturnType;

#define PduR_GwIfBufType_FIFO TRUE

#define PduR_GwIfBufType_NonFIFO FALSE

#define PduR_TpModule TRUE

#define PduR_NonTpModule FALSE

#endif

