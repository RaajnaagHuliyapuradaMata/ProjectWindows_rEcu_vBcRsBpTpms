

#include "PduR_Prv.hpp"
#include "PduR_Mc.hpp"

#if defined(PDUR_MULTICAST_TO_TP_SUPPORT) && (PDUR_MULTICAST_TO_TP_SUPPORT != 0)

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_MF_McTpTx_CanTp_TxConfirmation_Func( PduIdType mcId
   ,                                                                 Std_ReturnType result)
{
   PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_CANTP, mcId, result );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_MF_McTpTx_FrTp_TxConfirmation_Func( PduIdType mcId
   ,                                                                Std_ReturnType result)
{
   PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_FRTP, mcId, result );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_MF_McTpTx_J1939Tp_TxConfirmation_Func( PduIdType mcId
   ,                                                                 Std_ReturnType result)
{
   PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_J1939TP, mcId, result );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_MF_McTpTx_LinTp_TxConfirmation_Func( PduIdType mcId
   ,                                                                 Std_ReturnType result)
{
   PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_LINTP, mcId, result );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

