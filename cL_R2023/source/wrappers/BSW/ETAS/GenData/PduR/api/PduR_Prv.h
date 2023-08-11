

#ifndef PDUR_PRV_H
#define PDUR_PRV_H

#include "PduR.h"
#include "PduR_Cfg_Internal.h"
#include "PduR_Cfg_SchM.h"

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#include "Det.h"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)

#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif
#endif

#include "PduR_Types.h"

#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION != STD_OFF)
#include "PduR_ZeroCost_Cfg.h"
#endif

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

typedef enum {
    PDUR_EVENT_RXINDICATION = 0x01,
    PDUR_EVENT_TRANSMITCONFIRMATION ,
    PDUR_EVENT_COPYTXDATA,
    PDUR_EVENT_COPYRXDATA ,
    PDUR_EVENT_TRANSMIT,
    PDUR_EVENT_CANCELTRANSMIT,
    PDUR_EVENT_TRIGGERTRANSMIT
} PduR_EventType;

#define  PDUR_CHECK_STATE_VOID(sid)                     \
   if ( PduR_State == PDUR_UNINIT )                     \
   {                                                    \
      PDUR_REPORT_ERROR((sid), PDUR_E_INVALID_REQUEST); \
      return;                                           \
   }

#define  PDUR_CHECK_STATE_RET(sid,ret)                  \
   if ( PduR_State == PDUR_UNINIT )                     \
   {                                                    \
      PDUR_REPORT_ERROR((sid), PDUR_E_INVALID_REQUEST); \
      return (ret);                                       \
   }

#define  PDUR_CHECK_PTR_RET(sid, ptr, ret)                      \
   if ( (ptr) == NULL_PTR )                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return (ret);                                               \
   }

#define  PDUR_CHECK_PTR_VOID(sid, ptr)                          \
   if ( (ptr) == NULL_PTR)                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return;                                                   \
   }

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

#define PDUR_REPORT_ERROR(serviceId, errorId) (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID  , serviceId, errorId)
#else

#define PDUR_REPORT_ERROR(serviceId, errorId) do {} while(0)
#endif

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern PduR_DsmReInitType PduR_DsmReInitStruct;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern const PduR_PBConfigType * PduR_Base;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

# define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "PduR_MemMap.h"

extern const PduR_RPTablesType * PduR_FunctionPtrs;

# define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "PduR_MemMap.h"

#endif

#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "PduR_MemMap.h"

extern const PduR_PBConfigType PduR_GlobalPBConfig;

extern const PduR_RPTablesType PduR_RoutingPathTables;

#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "PduR_MemMap.h"

#define PDUR_BASE(s)          (PduR_Base->s)

#define PDUR_BASE_LOTP(n,s)       (PduR_Base->LoTpConf[n].s)

#define PDUR_BASE_LOIFD(n,s)      (PduR_Base->LoIfDConf[n].s)

#define PDUR_BASE_LOIFTT(n,s)     (PduR_Base->LoIfTTConf[n].s)

#define PDUR_BASE_UPTP(n,s)        (PduR_Base->UpTpConf[n].s)

#define PDUR_BASE_UPIF(n,s)        (PduR_Base->UpIfConf[n].s)

#define PDUR_BASE_UPTPCANCELRX(n,s)        (PduR_Base->PduR_UpTpToLoTpRxCfg[n].s)

#define PDUR_BASE_RPTBL(s)        (PduR_FunctionPtrs->s)

#define PDUR_GW_MC_TX_BASE      PDUR_BASE(gwToLoMc)

#define PDUR_LOIF_TX_MC_BASE    PDUR_BASE(loIfTxToUpMc)

#define PDUR_LOTP_TX_MC_BASE    PDUR_BASE(loTpTxToUpMc)

#define PDUR_LOTP_TX_STATE_BASE PDUR_BASE(loTpTxToUpMs)

#define PDUR_GW_IF_TX_BASE      PDUR_BASE(gwIfTx)

#define PDUR_GW_IF_BASE         PDUR_BASE(gwIf)

#define PDUR_GW_TP_BASE         PDUR_BASE(gwTp)

#define PDUR_RX_TP_RPG_BASE         PDUR_BASE(rpgRxTp)

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

#define PDUR_RPG_CONFIG_INFO    PDUR_BASE(rpg_ConfigInfo)

#define PDUR_RPG_ENROUTING_INFO(index)  PduR_Base->pduR_Rpg_Status[index]
#endif

#define PDUR_NR_VALID_IDS(rt)   PDUR_BASE(rt##_NrEntries)

#if (PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

#define PDUR_GET_RPGID_MAX     (PduR_Base->rpg_NrEntries)
#else

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
#define PDUR_GET_RPGID_MAX     (PDUR_RPGID_MAX)
#endif
#endif

#define PDUR_FIFO_WRITE_INC_WRAP(fifo, val)                         \
   do {                                                           \
      ((val)->writePtr) = ((val)->writePtr) + (fifo)->eltSize;       \
      (val)->writeIndex += 1;                                              \
      if ((val)->writePtr >= ((fifo)->begin + ((fifo)->eltSize * (fifo)->nrElts))) {  \
         (val)->writePtr = (fifo)->begin;                                  \
          (val)->writeIndex = 0u;                                \
      }                                                           \
   } while (0)

#define PDUR_FIFO_READ_INC_WRAP(fifo, val)                         \
   do {                                                           \
      ((val)->readPtr) = ((val)->readPtr) + (fifo)->eltSize;        \
      (val)->readIndex += 1;                                              \
      if ((val)->readPtr >= ((fifo)->begin + ((fifo)->eltSize * (fifo)->nrElts))) {  \
         (val)->readPtr = (fifo)->begin;                                    \
          (val)->readIndex = 0u;                                \
      }                                                           \
   } while (0)

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern PduR_StateType PduR_State;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

 #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

  #define PDUR_DET_API(name)                      (NULL_PTR)
 #else

  #define PDUR_DET_API(name)                      (name)
 #endif

 extern void PduR_iInit_multicast(PduR_MS_LoTpTxToUp * state);

 extern void PduR_GF_Tp_Buf_TxConfirmation( PduR_LayerType layer,
                                                               PduIdType gwId,
                                                               Std_ReturnType result );

 extern void PduR_GF_Tp_FIFO_TxConfirmation( PduR_LayerType layer,
                                                                PduIdType gwId,
                                                                Std_ReturnType result);

 extern BufReq_ReturnType PduR_RPG_Tp_StartOfReception_Func ( PduIdType rpgId,
                                                                         const PduInfoType * info,
                                                                         PduLengthType TpSduLength,
                                                                         PduLengthType * bufferSizePtr);

 extern BufReq_ReturnType PduR_RPG_Tp_CopyRxData_Func ( PduIdType rpgId,
                                                                 const PduInfoType * info,
                                                                 PduLengthType * bufferSizePtr);

 extern void PduR_RPG_Tp_RxIndication_Func ( PduIdType rpgId,
                                                        Std_ReturnType result);

 extern void PduR_iInit( const Type_CfgSwcServicePduR_st * ConfigPtr );

 #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

 extern void PduR_dInit( const Type_CfgSwcServicePduR_st * ConfigPtr );

 extern uint16 PduR_dGetConfigurationId( void );
#endif

 extern uint16 PduR_iGetConfigurationId( void );

 extern Std_ReturnType PduR_NF_TriggerTransmit_Func( PduIdType id, PduInfoType * data);

 extern BufReq_ReturnType PduR_invId_TpCopyRxData( PduIdType id,
                                                                     const PduInfoType * info,
                                                                     PduLengthType * bufferSizePtr);

 extern BufReq_ReturnType PduR_invId_TpStartOfReception(PduIdType id,
                                                                     PduLengthType TpSduLength,
                                                                     PduLengthType * bufferSizePtr);

 extern void PduR_invId_TpRxIndication( PduIdType id,   \
                                                                        Std_ReturnType result);

 extern BufReq_ReturnType PduR_invId_TpCopyTxData( PduIdType id, \
                                                                     const PduInfoType * info, \
                                                                     RetryInfoType * retry, \
                                                                     PduLengthType * availableDataPtr );

 extern void PduR_invId_TpTxConfirmation( PduIdType id,      \
                                                             Std_ReturnType result);

 extern void PduR_invId_IfRxIndication( PduIdType id,  \
                                                           const PduInfoType * ptr );

#if (AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_invId_IfTxConfirmation( PduIdType id );
#else
extern void PduR_invId_IfTxConfirmation( PduIdType id,Std_ReturnType result);
#endif

 extern Std_ReturnType PduR_invId_IfTriggerTransmit( PduIdType id,  \
                                                              PduInfoType * data );

 extern Std_ReturnType PduR_invId_UpTransmit( PduIdType id, \
                                                                   const PduInfoType * ptr);

 extern Std_ReturnType PduR_invId_UpCancelTransmit( PduIdType id);

 extern Std_ReturnType PduR_invId_UpCancelReceive( PduIdType id);

#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "PduR_MemMap.h"

 extern const PduR_upIfRxIndicationFuncType PduR_upIfRxIndicationTable[];

 extern const PduR_upIfTxConfirmationFuncType PduR_upIfTxConfirmationTable[];

 extern const PduR_upTpCopyRxDataFuncType PduR_upTpCopyRxDataTable[];

 extern const PduR_upTpStartOfReceptionFuncType PduR_upTpStartOfReceptionTable[];

 extern const PduR_upTpRxIndicationFuncType PduR_upTpRxIndicationTable[];

 extern const PduR_upTpCopyTxDataFuncType PduR_upTpCopyTxDataTable[];

 extern const PduR_upTpTxConfirmationFuncType PduR_upTpTxConfirmationTable[];

 extern const PduR_upIfTriggerTxFuncType PduR_upIfTriggerTxTable[];

 extern const PduR_loTransmitFuncType PduR_loTransmitTable[];

 extern const PduR_loCancelTransmitFuncType PduR_loCancelTransmitTable[];

 extern const PduR_loCancelReceiveFuncType PduR_loCancelRxTable[];

#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "PduR_MemMap.h"

extern void PduRAppl_IncompatibleGenerator(void);

#define PDUR_GW_TP_NEED_TX    ((uint8)0x40)

#define PDUR_GW_TP_TX_CALLED  ((uint8)0x20)

#define PDUR_GW_TP_TX_FAILED  ((uint8)0x80)

#endif

