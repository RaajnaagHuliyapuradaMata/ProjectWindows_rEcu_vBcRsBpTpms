

#ifndef PDUR_MC_H
#define PDUR_MC_H

#include "PduR_Cfg_Internal.hpp"
#include "PduR_Types.hpp"
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && PDUR_MULTICAST_TO_IF_SUPPORT == 1
#include "PduR_Multicast_TxConfirmation.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

extern Std_ReturnType PduR_MF_UpToLo( const PduR_MT_UpToLo * upToLoTable
   ,                                                        PduIdType mcId
   ,                                                        const PduInfoType * info);

extern Std_ReturnType PduR_MF_CancelTransmit_UpToLo(const PduR_MT_UpToLo * upToLoTable
   ,                                                PduIdType mcId);

#if(AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_MF_McIfTx_CanIf_TxConfirmation(PduIdType id);
#else
extern void PduR_MF_McIfTx_CanIf_TxConfirmation(PduIdType id,Std_ReturnType result);
#endif

#if(AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_MF_McIfTx_FrIf_TxConfirmation( PduIdType id);
#else
extern void PduR_MF_McIfTx_FrIf_TxConfirmation( PduIdType id,Std_ReturnType result);
#endif

#if(AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_MF_McIfTx_LinIf_TxConfirmation(PduIdType id);
#else
extern void PduR_MF_McIfTx_LinIf_TxConfirmation(PduIdType id,Std_ReturnType result);
#endif

extern void PduR_MF_McIfTx_TriggerTransmit(PduIdType id, PduInfoType * ptr);

#define PduR_MF_McIfTx_FrIf_TriggerTransmit  PduR_MF_McIfTx_TriggerTransmit

#define PduR_MF_McIfTx_LinIf_TriggerTransmit PduR_MF_McIfTx_TriggerTransmit

extern BufReq_ReturnType PduR_MF_McTpTx_CopyTxData( PduIdType mcId
   ,                                                                            const PduInfoType * info
   ,                                                                            RetryInfoType * retry
   ,                                                                            PduLengthType * availableDataPtr );

extern void PduR_MF_McTpTx_TxConfirmation( PduR_LayerType layerId
   ,                                                             PduIdType mcId
   ,                                                             Std_ReturnType result);

extern void PduR_MF_McTpTx_CanTp_TxConfirmation_Func(PduIdType mcId, Std_ReturnType result);

extern void PduR_MF_McTpTx_FrTp_TxConfirmation_Func( PduIdType mcId, Std_ReturnType result);

extern void PduR_MF_McTpTx_LinTp_TxConfirmation_Func(PduIdType mcId, Std_ReturnType result);

extern void PduR_MF_McTpTx_J1939Tp_TxConfirmation_Func( PduIdType mcId, Std_ReturnType result);

#define PduR_MF_McTpTx_CanTp_CopyTxData_Func  PduR_MF_McTpTx_CopyTxData

#define PduR_MF_McTpTx_FrTp_CopyTxData_Func   PduR_MF_McTpTx_CopyTxData

#define PduR_MF_McTpTx_LinTp_CopyTxData_Func  PduR_MF_McTpTx_CopyTxData

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

