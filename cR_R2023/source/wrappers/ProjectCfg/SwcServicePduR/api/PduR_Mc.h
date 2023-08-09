

#ifndef PDUR_MC_H
#define PDUR_MC_H

#include "PduR_Cfg_Internal.h"
#include "PduR_Types.h"
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && PDUR_MULTICAST_TO_IF_SUPPORT == 1
#include "PduR_Multicast_TxConfirmation.h"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_UpToLo( P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) upToLoTable,
                                                         VAR(PduIdType,AUTOMATIC) mcId,
                                                         P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_CancelTransmit_UpToLo(P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) upToLoTable,
                                                 VAR(PduIdType, AUTOMATIC) mcId);

extern FUNC( void, PDUR_CODE ) PduR_MF_McIfTx_CanIf_TxConfirmation(VAR(PduIdType,AUTOMATIC) id);

extern FUNC( void, PDUR_CODE ) PduR_MF_McIfTx_FrIf_TxConfirmation( VAR(PduIdType,AUTOMATIC) id);

extern FUNC( void, PDUR_CODE ) PduR_MF_McIfTx_LinIf_TxConfirmation(VAR(PduIdType,AUTOMATIC) id);

extern FUNC( void, PDUR_CODE ) PduR_MF_McIfTx_TriggerTransmit(VAR(PduIdType,AUTOMATIC) id, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr);

#define PduR_MF_McIfTx_FrIf_TriggerTransmit  PduR_MF_McIfTx_TriggerTransmit

#define PduR_MF_McIfTx_LinIf_TriggerTransmit PduR_MF_McIfTx_TriggerTransmit

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_MF_McTpTx_CopyTxData( VAR(PduIdType, AUTOMATIC) mcId,
                                                                             P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                             P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                             P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr );

extern FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_TxConfirmation( VAR(PduR_LayerType,AUTOMATIC) layerId,
                                                              VAR(PduIdType,AUTOMATIC) mcId,
                                                              VAR(Std_ReturnType,AUTOMATIC) result);

extern FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_CanTp_TxConfirmation_Func(VAR(PduIdType,AUTOMATIC) mcId, VAR(Std_ReturnType,AUTOMATIC) result);

extern FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_FrTp_TxConfirmation_Func( VAR(PduIdType,AUTOMATIC) mcId, VAR(Std_ReturnType,AUTOMATIC) result);

extern FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_LinTp_TxConfirmation_Func(VAR(PduIdType,AUTOMATIC) mcId, VAR(Std_ReturnType,AUTOMATIC) result);

extern FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_J1939Tp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) mcId, VAR(Std_ReturnType, AUTOMATIC) result);

#define PduR_MF_McTpTx_CanTp_CopyTxData_Func  PduR_MF_McTpTx_CopyTxData

#define PduR_MF_McTpTx_FrTp_CopyTxData_Func   PduR_MF_McTpTx_CopyTxData

#define PduR_MF_McTpTx_LinTp_CopyTxData_Func  PduR_MF_McTpTx_CopyTxData

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

