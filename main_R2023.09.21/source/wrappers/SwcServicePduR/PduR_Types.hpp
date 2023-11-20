#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

#include "PduR.hpp"
#include "PduR_Cfg_Internal.hpp"
#include "ComStack_Types.hpp"

typedef enum{
   PDUR_UNINIT
   ,  PDUR_REDUCED
   ,  PDUR_ONLINE
}PduR_StateType;

#define PDU_CNLDO   0x00u
#define PDU_CNLNB   0x01u
#define PDU_CNLOR   0x02u
#define PDUR_FIFO_IF    0u
#define PDUR_UCFIFO_TP  1u
#define PDUR_UCSEB_TP   2u
#define PDUR_MCSEB_TP   3u

typedef uint8 PduR_CancelReasonType;
typedef uint8 PduR_LayerType;

typedef struct{
   uint8    bufferLock;
   uint8    lowerLayers;
}PduR_LockType;

typedef uint8           PduR_BuffLockType;

typedef struct{
   P2FUNC(Std_ReturnType,  PDUR_APPL_CODE, PduR_loTransmitFunc )         ( Type_SwcServiceCom_tIdPdu, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) );
}PduR_loTransmitFuncType;

typedef struct{
   P2FUNC(Std_ReturnType,  PDUR_APPL_CODE, PduR_loCancelTransmitFunc )   ( Type_SwcServiceCom_tIdPdu );
}PduR_loCancelTransmitFuncType;

typedef struct{
   P2FUNC(Std_ReturnType,  PDUR_APPL_CODE, PduR_loCancelReceiveFunc )   ( Type_SwcServiceCom_tIdPdu );
}PduR_loCancelReceiveFuncType;

typedef struct{
   P2FUNC(void,     PDUR_APPL_CODE, PduR_upIfRxIndicationFunc )   ( Type_SwcServiceCom_tIdPdu, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) );
}PduR_upIfRxIndicationFuncType;

typedef struct{
   P2FUNC(void,     PDUR_APPL_CODE, PduR_upIfTxConfirmationFunc ) ( Type_SwcServiceCom_tIdPdu );
}PduR_upIfTxConfirmationFuncType;

typedef struct{
   P2FUNC(Std_ReturnType,     PDUR_APPL_CODE, PduR_upIfTriggerTxFunc )      ( Type_SwcServiceCom_tIdPdu, P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) );
}PduR_upIfTriggerTxFuncType;

typedef struct{
   P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpCopyRxDataFunc )  ( Type_SwcServiceCom_tIdPdu, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA), Type_SwcServiceCom_tLengthPdu* );
}PduR_upTpCopyRxDataFuncType;

typedef struct{
   P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpStartOfReceptionFunc )  ( Type_SwcServiceCom_tIdPdu,P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA), Type_SwcServiceCom_tLengthPdu, Type_SwcServiceCom_tLengthPdu* );
}PduR_upTpStartOfReceptionFuncType;

typedef struct{
   P2FUNC(void,     PDUR_APPL_CODE, PduR_upTpRxIndicationFunc )   ( Type_SwcServiceCom_tIdPdu, Std_ReturnType );
}PduR_upTpRxIndicationFuncType;

typedef struct{

   P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpCopyTxDataFunc )  ( Type_SwcServiceCom_tIdPdu, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA), RetryInfoType*,Type_SwcServiceCom_tLengthPdu*);
}PduR_upTpCopyTxDataFuncType;

typedef struct{
   P2FUNC(void,     PDUR_APPL_CODE, PduR_upTpTxConfirmationFunc ) ( Type_SwcServiceCom_tIdPdu, Std_ReturnType );
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
   Type_SwcServiceCom_tIdPdu                    loId;
   PduR_loTransmitFP            loTransmitID;
   PduR_loCancelTransmitFP      loCancelTransmitID;
}PduR_RT_UpToLo;

typedef struct{
   Type_SwcServiceCom_tIdPdu                    upId;
   PduR_upIfRxIndicationFP      upRxIndicationID;
}PduR_RT_LoIfRxToUp;

typedef struct{
   Type_SwcServiceCom_tIdPdu                    upId;
   PduR_upIfTxConfirmationFP    upTxConfirmationID;
}PduR_RT_LoIfTxToUp;

typedef struct{
   Type_SwcServiceCom_tIdPdu                    upId;
   PduR_upIfTriggerTxFP         upTriggerTxID;
   PduR_upIfTxConfirmationFP    upTxConfirmationID;
 }PduR_RT_LoTtIfTxToUp;

typedef struct{
   Type_SwcServiceCom_tIdPdu                    upId;
   PduR_upTpStartOfReceptionFP  upStartOfReceptionID;
   PduR_upTpProvideRxBufFP      upProvideRxBufID;
   PduR_upTpRxIndicationFP      upRxIndicationID;
}PduR_RT_LoTpRxToUp;

typedef struct{
   Type_SwcServiceCom_tIdPdu                    upId;
   PduR_upTpProvideTxBufFP      upProvideTxBufID;
   PduR_upTpTxConfirmationFP    upTxConfirmationID;
}PduR_RT_LoTpTxToUp;

typedef struct{
   PduR_RT_UpToLo               upToLo;
   boolean                      isTpModule;
   Type_SwcServiceCom_tIdPdu                    upId;
   Type_SwcServiceCom_tIdPdu                    upLayerSymName;
   uint8                        upSrcLayerName;
}PduR_MT_UpToLo;

typedef struct{
   PduR_RT_LoTtIfTxToUp         toUp;
   uint8                        destLowerLayers;
}PduR_MT_LoIfTxToUp;

typedef struct{
   P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) pduPtr;
   BufReq_ReturnType            allocError;
   Std_ReturnType              txFailure;
   PduR_LayerType               txConf;
  }PduR_MS_LoTpTxToUp;

typedef struct{
   PduR_RT_LoTpTxToUp           toUp;
   uint8                        destLowerLayers;
}PduR_MT_LoTpTxToUp;

typedef struct{
   Type_SwcServiceCom_tLengthPdu                length;
   Type_SwcServiceCom_tIdPdu                    loId;
   PduR_loTransmitFP            transmitID;
}PduR_GT_IfTx;

typedef struct{
   P2CONST(void, TYPEDEF, PDUR_CONST) buffer;
   Type_SwcServiceCom_tIdPdu                    loId;
   PduR_loTransmitFP            transmitID;
   boolean                      isFifoType;
}PduR_GT_If;

typedef struct{
   P2VAR(uint8, TYPEDEF, PDUR_VAR) bufferPtr;
   P2VAR(uint8, TYPEDEF, PDUR_VAR) readPtr;
   P2VAR(uint8, TYPEDEF, PDUR_VAR) writePtr;
   Type_SwcServiceCom_tLengthPdu                        numRxLength;
   Type_SwcServiceCom_tLengthPdu                        numTxLength;
   Type_SwcServiceCom_tLengthPdu                        SduLength;
   Type_SwcServiceCom_tLengthPdu                        bufferLength;
   Type_SwcServiceCom_tLengthPdu                        remainingBuffLength;
   Type_SwcServiceCom_tLengthPdu                        RxChunkLength;
   Type_SwcServiceCom_tLengthPdu                        TxChunkLength;
   uint8                                Rx_Status;
   uint8                                Tx_Status;
   uint8                                Tx_E_OK_Count;
}PduR_TpSession_Dynamic;

typedef P2VAR(PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR) PduR_TpSessDynPtr;

typedef struct{
   P2VAR(PduR_TpSession_Dynamic, AUTOMATIC, PDUR_VAR) GwTpSessionPtr;
}PduR_GwTp_SessionListType;

typedef P2CONST(PduR_GwTp_SessionListType, TYPEDEF, PDUR_CONST) PduR_GwTp_SessionListPtr;

typedef struct{
   P2VAR(uint8,AUTOMATIC, PDUR_VAR) PduR_UpIfTxConf_ConfigPtr;
}PduR_UpIfTxConf_Config;

typedef struct{
   P2VAR(PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR)     primarySession;
}PduR_TpConnection_Dynamic;

typedef P2VAR(PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR) PduR_TpConnDynPtr;

typedef struct{
   P2VAR(uint8,                     TYPEDEF, PDUR_VAR) begin;
   P2VAR(PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR) connectionTable;
   Type_SwcServiceCom_tLengthPdu                     eltSize;
   uint16                            buffPoolId;
}PduR_FIFO_Tp_fixed;

typedef struct{
   P2CONST(PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST) buffer;
           Type_SwcServiceCom_tLengthPdu            numOfLowerLayers;
           Type_SwcServiceCom_tLengthPdu            TpGwQueueSize;
           Type_SwcServiceCom_tIdPdu                loId;
           Type_SwcServiceCom_tIdPdu                upId;
           uint16                                   TpThreshold;
           PduR_loTransmitFP                        loTransmitID;
}PduR_GT_Tp;

typedef P2CONST(PduR_GT_Tp, TYPEDEF, PDUR_CONST) PduR_GT_TpPtr;
typedef uint8 PduR_LowerTpModuleName;
typedef uint8 PduR_loCancelReceiveFP;

typedef struct{
   Type_SwcServiceCom_tIdPdu LoTpRxId;
   PduR_loCancelReceiveFP    CancelRxFP;
}PduR_RT_UpTpRxToLoTp;

typedef struct{
   P2CONST(PduR_RT_UpTpRxToLoTp, TYPEDEF, PDUR_CONST) UpTpToLoTp;
   Type_SwcServiceCom_tIdPdu                          UpTpToLoTp_NrEntries;
}PduR_UpTpToLoTpRxConfig;

typedef uint8 PduR_ParameterValueType;

typedef struct{
   Type_SwcServiceCom_stInfoPdu                           info;
   P2VAR(PduR_BuffLockType,            TYPEDEF, PDUR_VAR) lockPtr;
   P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_VAR) readerPduInfo;
}PduR_SingleEntryBuffer;

typedef P2CONST(PduR_SingleEntryBuffer, TYPEDEF, PDUR_CONST) PduR_SingleEntryBufferPtr;

typedef struct{
   P2VAR(uint8, TYPEDEF, PDUR_VAR) readPtr;
   P2VAR(uint8, TYPEDEF, PDUR_VAR) writePtr;
   Type_SwcServiceCom_tLengthPdu   actLen;
   uint8                           used;
   uint8                           txConfPending;
}PduR_FIFO_If_dynamic;

typedef struct{
   uint8                    byteDefaultValue;
   uint8                    bytePosition;
}PduR_DefaultValues_fixed;

typedef struct{
   P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_VAR)   gwBuf;
   P2VAR(uint8,                        TYPEDEF, PDUR_VAR)   begin;
   P2CONST(PduR_DefaultValues_fixed,   TYPEDEF, PDUR_CONST) defaultValueElement;
   uint8                                                    defaultValueSize;
   uint8                                                    confLen;
}PduR_Buf_If_dynamic;

typedef P2VAR(PduR_FIFO_If_dynamic, TYPEDEF, PDUR_VAR) PduR_FifoDynIfPtr;

typedef struct{
   P2VAR(uint8, TYPEDEF, PDUR_VAR) begin;
   P2VAR(void,  TYPEDEF, PDUR_VAR) dyn;
   Type_SwcServiceCom_tLengthPdu                     eltSize;
   uint8                             nrElts;
}PduR_FIFO_fixed;

typedef P2CONST(PduR_FIFO_fixed, TYPEDEF, PDUR_CONST) PduR_FifoType;

typedef struct{
   P2CONST(PduR_RT_UpToLo, TYPEDEF, PDUR_CONST) CddToLo;
   P2CONST(PduR_MT_UpToLo, TYPEDEF, PDUR_CONST) CddToLoMc;
   Type_SwcServiceCom_tIdPdu                    CddToLo_NrEntries;
}PduR_CddConfig;

typedef struct{
   P2CONST(PduR_RT_LoTpRxToUp, TYPEDEF, PDUR_CONST) LoTpRxToUp;
   P2CONST(PduR_RT_LoTpTxToUp, TYPEDEF, PDUR_CONST) LoTpTxToUp;
   Type_SwcServiceCom_tIdPdu                        LoTpRxToUp_NrEntries;
   Type_SwcServiceCom_tIdPdu                        LoTpTxToUp_NrEntries;
}PduR_LoTpConfig;

typedef struct{
   P2CONST(PduR_RT_UpToLo, TYPEDEF, PDUR_CONST) UpToLo;
   P2CONST(PduR_MT_UpToLo, TYPEDEF, PDUR_CONST) UpToLoMc;
   Type_SwcServiceCom_tIdPdu                    UpToLo_NrEntries;
}PduR_UpConfig;

typedef struct{
   P2CONST(PduR_RT_LoIfRxToUp, TYPEDEF, PDUR_CONST) LoIfRxToUp;
   P2CONST(PduR_RT_LoIfTxToUp, TYPEDEF, PDUR_CONST) LoIfTxToUp;
   Type_SwcServiceCom_tIdPdu                        LoIfRxToUp_NrEntries;
   Type_SwcServiceCom_tIdPdu                        LoIfTxToUp_NrEntries;
}PduR_LoIfDConfig;

typedef struct{
   P2CONST(PduR_RT_LoIfRxToUp,   TYPEDEF, PDUR_CONST) LoIfRxToUp;
   P2CONST(PduR_RT_LoTtIfTxToUp, TYPEDEF, PDUR_CONST) LoIfTxToUp;
   Type_SwcServiceCom_tIdPdu                          LoIfRxToUp_NrEntries;
   Type_SwcServiceCom_tIdPdu                          LoIfTxToUp_NrEntries;
}PduR_LoIfTTConfig;

typedef P2VAR(void, TYPEDEF, PDUR_VAR) PduR_RPGVoidPtr;

typedef struct{
   PduR_RPGVoidPtr             destInfo;
   uint8                       pathType;
}PduR_TargetInfoType;

typedef struct{
   P2VAR(uint8, TYPEDEF, PDUR_VAR)       begin;
   P2CONST(PduR_DefaultValues_fixed, TYPEDEF, PDUR_CONST)            defaultValueElement;
   uint8                                   defaultValueSize;
}PduR_DefaultValue_Info;

typedef struct{
   P2CONST(PduR_TargetInfoType, TYPEDEF, PDUR_CONST) targetInfo;
   P2CONST(PduR_DefaultValue_Info, TYPEDEF, PDUR_CONST) defaultValue_info;
   PduR_RoutingPathGroupIdType                         rpg_Idx;
   uint8                                               cntDestOfTypeFIFO;
   uint8                                               cntOfDestWithDefValue;
}PduR_RPGInfoType;

typedef struct{
   P2CONST(PduR_loTransmitFuncType,           TYPEDEF, PDUR_CONST) loTxTablePtr;
   P2CONST(PduR_loCancelReceiveFuncType,      TYPEDEF, PDUR_CONST) loCancelRxTable;
   P2CONST(PduR_loCancelTransmitFuncType,     TYPEDEF, PDUR_CONST) loCnclTxTablePtr;
   P2CONST(PduR_upIfRxIndicationFuncType,     TYPEDEF, PDUR_CONST) upIfRxIndTablePtr;
   P2CONST(PduR_upIfTxConfirmationFuncType,   TYPEDEF, PDUR_CONST) upIfTxConfTablePtr;
   P2CONST(PduR_upTpCopyRxDataFuncType,       TYPEDEF, PDUR_CONST) upTpRxDataTablePtr;
   P2CONST(PduR_upTpStartOfReceptionFuncType, TYPEDEF, PDUR_CONST) upTpStartRxTablePtr;
   P2CONST(PduR_upTpRxIndicationFuncType,     TYPEDEF, PDUR_CONST) upTpRxIndTablePtr;
   P2CONST(PduR_upTpCopyTxDataFuncType,       TYPEDEF, PDUR_CONST) upTpTxDataTablePtr;
   P2CONST(PduR_upTpTxConfirmationFuncType,   TYPEDEF, PDUR_CONST) upTpTxConfTablePtr;
   P2CONST(PduR_upIfTriggerTxFuncType,        TYPEDEF, PDUR_CONST) upIfTrigTxTablePtr;
}PduR_RPTablesType;

typedef struct{
   P2CONST(PduR_CddConfig,          TYPEDEF, PDUR_CONST) cddConf;
   P2CONST(PduR_LoTpConfig,         TYPEDEF, PDUR_CONST) LoTpConf;
   P2CONST(PduR_LoIfDConfig,        TYPEDEF, PDUR_CONST) LoIfDConf;
   P2CONST(PduR_LoIfTTConfig,       TYPEDEF, PDUR_CONST) LoIfTTConf;
   P2CONST(PduR_UpConfig,           TYPEDEF, PDUR_CONST) UpIfConf;
   P2CONST(PduR_UpConfig,           TYPEDEF, PDUR_CONST) UpTpConf;
   P2CONST(PduR_MT_UpToLo,          TYPEDEF, PDUR_CONST) gwToLoMc;
   P2CONST(PduR_MT_LoIfTxToUp,      TYPEDEF, PDUR_CONST) loIfTxToUpMc;
   P2CONST(PduR_MT_LoTpTxToUp,      TYPEDEF, PDUR_CONST) loTpTxToUpMc;
     P2VAR(PduR_MS_LoTpTxToUp,      TYPEDEF, PDUR_VAR)   loTpTxToUpMs;
   P2CONST(PduR_GT_IfTx,            TYPEDEF, PDUR_CONST) gwIfTx;
   P2CONST(PduR_GT_If,              TYPEDEF, PDUR_CONST) gwIf;
   P2CONST(PduR_GT_Tp,              TYPEDEF, PDUR_CONST) gwTp;
   P2CONST(PduR_RPTablesType,       TYPEDEF, PDUR_CONST) PduR_RPTablesPtr;
   P2CONST(PduR_UpTpToLoTpRxConfig, TYPEDEF, PDUR_CONST) PduR_UpTpToLoTpRxCfg;
   uint16                                                configId;
   uint16                                                totalNoOfGwTpRps;
   uint16                                                totalNoOfGwIfRps;
   Type_SwcServiceCom_tIdPdu                             loTpTxToUpMc_NrEntries;
}PduR_PBConfigType;

typedef struct{
   VAR(Dem_EventStatusType, PDUR_VAR) initFailedErrorStatus;
   VAR(Dem_EventStatusType, PDUR_VAR) instanceLostErrorStatus;
   VAR(boolean, PDUR_VAR) initFailedErrorFlag;
   VAR(boolean, PDUR_VAR) instanceLostErrorFlag;
}PduR_DsmReInitType;

typedef uint8 PduR_ReturnType;

#define PduR_GwIfBufType_FIFO                                              TRUE
#define PduR_GwIfBufType_NonFIFO                                           FALSE
#define PduR_TpModule                                                      TRUE
#define PduR_NonTpModule                                                   FALSE

#endif

