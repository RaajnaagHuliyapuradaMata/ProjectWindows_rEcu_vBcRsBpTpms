#ifndef PDUR_PRV_H
#define PDUR_PRV_H

#include "PduR.hpp"
#include "PduR_Cfg_Internal.hpp"
#include "PduR_Cfg_SchM.hpp"
#include "PduR_Types.hpp"

#define PDUR_CONFIGTYPE_MAGIC      (0x025fe8a7uL)
#define PDUR_LAYER_CANTP           ((uint8)0x01)
#define PDUR_LAYER_FRTP            ((uint8)0x02)
#define PDUR_LAYER_LINTP           ((uint8)0x04)
#define PDUR_LAYER_CANIF           ((uint8)0x10)
#define PDUR_LAYER_FRIF            ((uint8)0x20)
#define PDUR_LAYER_LINIF           ((uint8)0x40)
#define PDUR_MULTICAST             ((uint8)0x80)
#define PDUR_LAYER_IPDUMLO         ((uint8)0x08)
#define PDUR_LAYER_J1939TP         ((uint8)0x08)

typedef enum{
      PDUR_EVENT_RXINDICATION = 0x01
   ,  PDUR_EVENT_TRANSMITCONFIRMATION 
   ,  PDUR_EVENT_COPYTXDATA
   ,  PDUR_EVENT_COPYRXDATA 
   ,  PDUR_EVENT_TRANSMIT
   ,  PDUR_EVENT_CANCELTRANSMIT
   ,  PDUR_EVENT_TRIGGERTRANSMIT
}PduR_EventType;

#define PDUR_CHECK_STATE_VOID(sid)                     \
   if( PduR_State == PDUR_UNINIT )                     \
   {                                                    \
      PDUR_REPORT_ERROR((sid), PDUR_E_INVALID_REQUEST); \
      return;                                           \
   }

#define PDUR_CHECK_STATE_RET(sid,ret)                  \
   if( PduR_State == PDUR_UNINIT )                     \
   {                                                    \
      PDUR_REPORT_ERROR((sid), PDUR_E_INVALID_REQUEST); \
      return (ret);                                       \
   }

#define PDUR_CHECK_PTR_RET(sid, ptr, ret)                      \
   if( ptr == NULL_PTR )                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return (ret);                                               \
   }

#define PDUR_CHECK_PTR_VOID(sid, ptr)                          \
   if( ptr == NULL_PTR)                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return;                                                   \
   }

#define PDUR_REPORT_ERROR(serviceId, errorId) do {}while(0)

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.hpp"
extern     VAR(PduR_DsmReInitType, PDUR_VAR                   ) PduR_DsmReInitStruct;
extern P2CONST(PduR_PBConfigType,  PDUR_CONST, PDUR_APPL_CONST) PduR_Base;
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.hpp"
extern CONST(PduR_PBConfigType, PDUR_CONST) PduR_GlobalPBConfig;
extern CONST(PduR_RPTablesType, PDUR_CONST) PduR_RoutingPathTables;
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.hpp"

#define PDUR_BASE(s)                (PduR_Base->s)
#define PDUR_BASE_LOTP(n,s)         (PduR_Base->LoTpConf[n].s)
#define PDUR_BASE_LOIFD(n,s)        (PduR_Base->LoIfDConf[n].s)
#define PDUR_BASE_LOIFTT(n,s)       (PduR_Base->LoIfTTConf[n].s)
#define PDUR_BASE_UPTP(n,s)         (PduR_Base->UpTpConf[n].s)
#define PDUR_BASE_UPIF(n,s)         (PduR_Base->UpIfConf[n].s)
#define PDUR_BASE_UPTPCANCELRX(n,s) (PduR_Base->PduR_UpTpToLoTpRxCfg[n].s)
#define PDUR_BASE_RPTBL(s)          (PduR_FunctionPtrs->s)
#define PDUR_GW_MC_TX_BASE          PDUR_BASE(gwToLoMc)
#define PDUR_LOIF_TX_MC_BASE        PDUR_BASE(loIfTxToUpMc)
#define PDUR_LOTP_TX_MC_BASE        PDUR_BASE(loTpTxToUpMc)
#define PDUR_LOTP_TX_STATE_BASE     PDUR_BASE(loTpTxToUpMs)
#define PDUR_GW_IF_TX_BASE          PDUR_BASE(gwIfTx)
#define PDUR_GW_IF_BASE             PDUR_BASE(gwIf)
#define PDUR_GW_TP_BASE             PDUR_BASE(gwTp)
#define PDUR_RX_TP_RPG_BASE         PDUR_BASE(rpgRxTp)
#define PDUR_NR_VALID_IDS(rt)       PDUR_BASE(rt##_NrEntries)

#define PDUR_FIFO_WRITE_INC_WRAP(fifo, val)                         \
   do {                                                           \
      ((val)->writePtr) = ((val)->writePtr) + (fifo)->eltSize;       \
      (val)->writeIndex += 1;                                              \
      if((val)->writePtr >= ((fifo)->begin + ((fifo)->eltSize * (fifo)->nrElts))) {  \
         (val)->writePtr = (fifo)->begin;                                  \
          (val)->writeIndex = 0u;                                \
      }                                      \
   }while(0)

#define PDUR_FIFO_READ_INC_WRAP(fifo, val)                         \
   do {                                                           \
      ((val)->readPtr) = ((val)->readPtr) + (fifo)->eltSize;        \
      (val)->readIndex += 1;                                              \
      if((val)->readPtr >= ((fifo)->begin + ((fifo)->eltSize * (fifo)->nrElts))) {  \
         (val)->readPtr = (fifo)->begin;                                    \
          (val)->readIndex = 0u;                                \
      }                                      \
   }while(0)

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.hpp"
extern VAR( PduR_StateType, PDUR_VAR) PduR_State;
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.hpp"

#define PDUR_DET_API(name)                      (name)

extern FUNC(void, PDUR_CODE) PduR_iInit_multicast(
   P2VAR(PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state
);

extern FUNC(void, PDUR_CODE) PduR_GF_Tp_Buf_TxConfirmation(
      VAR(PduR_LayerType,            AUTOMATIC) layer
   ,  VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwId
   ,  VAR(Std_ReturnType,            AUTOMATIC) result
);

extern FUNC(void, PDUR_CODE) PduR_GF_Tp_FIFO_TxConfirmation(
      VAR(PduR_LayerType,            AUTOMATIC) layer
   ,  VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwId
   ,  VAR(Std_ReturnType,            AUTOMATIC) result
);

extern FUNC(void, PDUR_CODE) PduR_iInit(
   P2CONST(Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr
);

extern FUNC(uint16, PDUR_CODE) PduR_iGetConfigurationId(void);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_NF_TriggerTransmit_Func(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC                ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, PDUR_APPL_DATA) data
);

extern FUNC( BufReq_ReturnType, PDUR_CODE) PduR_invId_TpCopyRxData(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
);

extern FUNC( BufReq_ReturnType, PDUR_CODE) PduR_invId_TpStartOfReception(
        VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,    VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC              ) TpSduLength
   ,  P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
);

extern FUNC(void, PDUR_CODE) PduR_invId_TpRxIndication(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC ) id
   ,  VAR(Std_ReturnType, AUTOMATIC) result
);

extern FUNC( BufReq_ReturnType, PDUR_CODE) PduR_invId_TpCopyTxData(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(RetryInfoType,                 TYPEDEF, PDUR_APPL_DATA) retry
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) availableDataPtr
);

extern FUNC(void, PDUR_CODE) PduR_invId_TpTxConfirmation(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC ) id
   ,  VAR(Std_ReturnType, AUTOMATIC) result
);

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_IfTriggerTransmit(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) data
);

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_UpTransmit(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr
);

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_UpCancelTransmit(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
);

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_UpCancelReceive(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
);

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.hpp"
extern CONST(PduR_upIfRxIndicationFuncType,     PDUR_CONST) PduR_upIfRxIndicationTable[];
extern CONST(PduR_upIfTxConfirmationFuncType,   PDUR_CONST) PduR_upIfTxConfirmationTable[];
extern CONST(PduR_upTpCopyRxDataFuncType,       PDUR_CONST) PduR_upTpCopyRxDataTable[];
extern CONST(PduR_upTpStartOfReceptionFuncType, PDUR_CONST) PduR_upTpStartOfReceptionTable[];
extern CONST(PduR_upTpRxIndicationFuncType,     PDUR_CONST) PduR_upTpRxIndicationTable[];
extern CONST(PduR_upTpCopyTxDataFuncType,       PDUR_CONST) PduR_upTpCopyTxDataTable[];
extern CONST(PduR_upTpTxConfirmationFuncType,   PDUR_CONST) PduR_upTpTxConfirmationTable[];
extern CONST(PduR_upIfTriggerTxFuncType,        PDUR_CONST) PduR_upIfTriggerTxTable[];
extern CONST(PduR_loTransmitFuncType,           PDUR_CONST) PduR_loTransmitTable[];
extern CONST(PduR_loCancelTransmitFuncType,     PDUR_CONST) PduR_loCancelTransmitTable[];
extern CONST(PduR_loCancelReceiveFuncType,      PDUR_CONST) PduR_loCancelRxTable[];
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.hpp"

#define PDUR_GW_TP_NEED_TX    ((uint8)0x40)
#define PDUR_GW_TP_TX_CALLED  ((uint8)0x20)
#define PDUR_GW_TP_TX_FAILED  ((uint8)0x80)

#endif

