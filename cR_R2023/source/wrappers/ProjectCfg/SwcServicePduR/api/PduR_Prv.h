

#ifndef PDUR_PRV_H
#define PDUR_PRV_H

#include "PduR.h"
#include "PduR_Cfg_Internal.h"
#include "PduR_Cfg_SchM.h"

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
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
   if ( ptr == NULL_PTR )                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return (ret);                                               \
   }

#define  PDUR_CHECK_PTR_VOID(sid, ptr)                          \
   if ( ptr == NULL_PTR)                                                \
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

extern VAR(PduR_DsmReInitType, PDUR_VAR) PduR_DsmReInitStruct;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern P2CONST( PduR_PBConfigType, PDUR_CONST, PDUR_APPL_CONST ) PduR_Base;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

# define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "PduR_MemMap.h"

extern P2CONST( PduR_RPTablesType, PDUR_CONST, PDUR_APPL_CONST ) PduR_FunctionPtrs;

# define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "PduR_MemMap.h"

#endif

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

extern CONST( PduR_PBConfigType, PDUR_CONST ) PduR_GlobalPBConfig;

extern CONST( PduR_RPTablesType, PDUR_CONST ) PduR_RoutingPathTables;

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
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

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

#define PDUR_RPG_CONFIG_INFO    PDUR_BASE(rpg_ConfigInfo)

#define PDUR_RPG_ENROUTING_INFO(index)  PduR_Base->pduR_Rpg_Status[index]
#endif

#define PDUR_CHANGEPARAM_SUPPORT PDUR_BASE(DcmRxToLoTp)

#define PDUR_NR_VALID_IDS(rt)   PDUR_BASE(rt##_NrEntries)

#if (PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

#define PDUR_GET_RPGID_MAX     (PduR_Base->rpg_NrEntries)
#else

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
#define PDUR_GET_RPGID_MAX     (PDUR_RPGID_MAX)
#endif
#endif

#define PDUR_FIFO_INC_AND_WRAP(fifo, val)                         \
   do {                                                           \
      (val) = (val) + (fifo)->eltSize;                              \
      if ((val) >= ((fifo)->begin + ((fifo)->eltSize * (fifo)->nrElts))) {  \
         (val) = (fifo)->begin;                                     \
      }                                                           \
   } while (0)

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern VAR( PduR_StateType, PDUR_VAR ) PduR_State;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

 #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

  #define PDUR_DET_API(name)                      (NULL_PTR)
 #else

  #define PDUR_DET_API(name)                      (name)
 #endif

 extern FUNC( void, PDUR_CODE ) PduR_iInit_multicast(P2VAR( PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state);

 extern FUNC( void, PDUR_CODE ) PduR_GF_Tp_Buf_TxConfirmation( VAR(PduR_LayerType,AUTOMATIC) layer,
                                                               VAR(PduIdType,AUTOMATIC) gwId,
                                                               VAR(Std_ReturnType,AUTOMATIC) result );

 extern FUNC( void, PDUR_CODE ) PduR_GF_Tp_FIFO_TxConfirmation( VAR(PduR_LayerType, AUTOMATIC) layer,
                                                                VAR(PduIdType, AUTOMATIC) gwId,
                                                                VAR(Std_ReturnType, AUTOMATIC) result);

 extern FUNC( void, PDUR_CODE ) PduR_iInit( P2CONST( Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr );

 #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

 extern FUNC( void, PDUR_CODE ) PduR_dInit( P2CONST( Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr );

 extern FUNC( uint16, PDUR_CODE ) PduR_dGetConfigurationId( void );
#endif

 extern FUNC( uint16, PDUR_CODE ) PduR_iGetConfigurationId( void );

 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_NF_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC ) id, P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA ) data);

 extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyRxData( VAR(PduIdType, AUTOMATIC) id,
                                                                     P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

 extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpStartOfReception(VAR(PduIdType, AUTOMATIC) id,
                                                                     VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

 extern FUNC( void, PDUR_CODE )              PduR_invId_TpRxIndication( VAR(PduIdType, AUTOMATIC ) id,   \
                                                                        VAR(Std_ReturnType, AUTOMATIC) result);

 extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyTxData( VAR(PduIdType, AUTOMATIC) id, \
                                                                     P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info, \
                                                                     P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry, \
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr );

 extern FUNC( void, PDUR_CODE ) PduR_invId_TpTxConfirmation( VAR(PduIdType, AUTOMATIC ) id,      \
                                                             VAR(Std_ReturnType, AUTOMATIC) result);

 extern FUNC( void, PDUR_CODE ) PduR_invId_IfRxIndication( VAR(PduIdType, AUTOMATIC ) id,  \
                                                           P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );

 extern FUNC( void, PDUR_CODE ) PduR_invId_IfTxConfirmation( VAR(PduIdType, AUTOMATIC ) id );

 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_IfTriggerTransmit( VAR(PduIdType, AUTOMATIC ) id,  \
                                                              P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) data );

 extern FUNC( Std_ReturnType, PDUR_CODE )   PduR_invId_UpTransmit( VAR(PduIdType, AUTOMATIC ) id, \
                                                                   P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr);

 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelTransmit( VAR(PduIdType, AUTOMATIC ) id);

 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelReceive( VAR(PduIdType, AUTOMATIC ) id);

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

 extern CONST(PduR_upIfRxIndicationFuncType, PDUR_CONST) PduR_upIfRxIndicationTable[];

 extern CONST(PduR_upIfTxConfirmationFuncType, PDUR_CONST) PduR_upIfTxConfirmationTable[];

 extern CONST(PduR_upTpCopyRxDataFuncType, PDUR_CONST) PduR_upTpCopyRxDataTable[];

 extern CONST(PduR_upTpStartOfReceptionFuncType, PDUR_CONST) PduR_upTpStartOfReceptionTable[];

 extern CONST(PduR_upTpRxIndicationFuncType, PDUR_CONST) PduR_upTpRxIndicationTable[];

 extern CONST(PduR_upTpCopyTxDataFuncType, PDUR_CONST) PduR_upTpCopyTxDataTable[];

 extern CONST(PduR_upTpTxConfirmationFuncType, PDUR_CONST) PduR_upTpTxConfirmationTable[];

 extern CONST(PduR_upIfTriggerTxFuncType, PDUR_CONST) PduR_upIfTriggerTxTable[];

 extern CONST(PduR_loTransmitFuncType, PDUR_CONST) PduR_loTransmitTable[];

 extern CONST(PduR_loCancelTransmitFuncType, PDUR_CONST) PduR_loCancelTransmitTable[];

 extern CONST(PduR_loCancelReceiveFuncType, PDUR_CONST) PduR_loCancelRxTable[];

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

 #define PDUR_MIN_ROUTING_CANIF_ENABLED (0x01)

 #define PDUR_MIN_ROUTING_CANTP_ENABLED (0x02)

 #define PDUR_MIN_ROUTING_FRIF_ENABLED  (0x04)

 #define PDUR_MIN_ROUTING_FRTP_ENABLED  (0x08)

 #define PDUR_MIN_ROUTING_LINIF_ENABLED (0x10)

 #define PDUR_MIN_ROUTING_LINTP_ENABLED (0x20)

 #define PDUR_MIN_ROUTING_COM_ENABLED   (0x40)

 #define PDUR_MIN_ROUTING_DCM_ENABLED   (0x80)

 #define PDUR_ROUTINGFN_0ARG( srcLayer, fromUpOrLo, toUpOrLo, txOrRx, operation, fullRouteFn, srcId )  \
                                     \
    ( ( ( PDUR_MIN_ROUTING_LINKTIME_ ## srcLayer ) &&                         \
    ( (srcId) == PDUR_MIN_ROUTING_ ## fromUpOrLo ## _ ## txOrRx ## PDUID ) ) ?   \
                                                               \
       ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## operation ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## txOrRx ## PDUID ) ) :  \
                                                                 \
                                                                 \
      ( fullRouteFn( (srcId) ) )                                                                         \
    )

 #define PDUR_ROUTINGFN_1ARG( srcLayer, fromUpOrLo, toUpOrLo, txOrRx, operation, fullRouteFn, srcId, arg1 )  \
                                           \
   ( ( ( PDUR_MIN_ROUTING_LINKTIME_ ## srcLayer ) &&                         \
   ( (srcId) == PDUR_MIN_ROUTING_ ## fromUpOrLo ## _ ## txOrRx ## PDUID ) ) ?   \
                                                                     \
   ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## operation ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## txOrRx ## PDUID, arg1 ) ): \
                                                                  \
                                                                       \
      ( fullRouteFn( (srcId), (arg1) ) )                                                                         \
    )

 #define PDUR_ROUTINGFN_2ARG( srcLayer, fromUpOrLo, toUpOrLo, txOrRx, operation, fullRouteFn, srcId, arg1, arg2 )  \
                                               \
    ( ( ( PDUR_MIN_ROUTING_LINKTIME_ ## srcLayer ) && ( (srcId) == PDUR_MIN_ROUTING_##fromUpOrLo## _ ##txOrRx## PDUID)) ? \
                                                                           \
   (PDUR_MIN_ROUTING_ ##toUpOrLo##_##operation( PDUR_MIN_ROUTING_ ##toUpOrLo ## _ ## txOrRx ## PDUID, arg1, arg2 ) ) : \
                                                                 \
                                                                             \
      ( fullRouteFn( (srcId), (arg1), (arg2) ) )                                                                          \
    )

extern FUNC( void, PDUR_CODE ) PduRAppl_IncompatibleGenerator(void);

#define PDUR_GW_TP_NEED_TX    ((uint8)0x40)

#define PDUR_GW_TP_TX_CALLED  ((uint8)0x20)

#define PDUR_GW_TP_TX_FAILED  ((uint8)0x80)

#endif

