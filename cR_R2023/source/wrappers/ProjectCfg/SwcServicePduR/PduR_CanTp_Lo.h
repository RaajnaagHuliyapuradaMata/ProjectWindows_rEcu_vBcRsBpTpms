
#ifndef PDUR_CANTP_LO_H
#define PDUR_CANTP_LO_H

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CONFIG_SINGLE_TPRX)
#define PduR_iCanTpCopyRxDataID(id)        (id)
#define PduR_iCanTpCopyRxDataFunc(id)        (PDUR_CONFIG_SINGLE_TPRX(CopyRxData))
#else
#define PduR_iCanTpCopyRxDataID(id)        (PDUR_CANTP_RXIND_BASE[(id)].upId)
#define PduR_iCanTpCopyRxDataFunc(id)      (PduR_upTpCopyRxDataTable[(PDUR_CANTP_RXIND_BASE[(id)].upProvideRxBufID)].PduR_upTpCopyRxDataFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanTpCopyRxData(id,info,bufSizePtr)   PduR_dCanTpCopyRxData((id),(info),(bufSizePtr))
#else
#define PduR_aCanTpCopyRxData(id,info,bufSizePtr)   PduR_iCanTpCopyRxDataFunc(id)(PduR_iCanTpCopyRxDataID(id),(info),(bufSizePtr))
#endif

#define PduR_rCanTpCopyRxData(id,info,bufSizePtr)   PduR_aCanTpCopyRxData((id),(info),(bufSizePtr))

#if defined(PDUR_CONFIG_SINGLE_TPRX)
#define PduR_iCanTpStartOfReceptionID(id)        (id)
#define PduR_iCanTpStartOfReceptionFunc(id)        (PDUR_CONFIG_SINGLE_TPRX(StartOfReception))
#else
#define PduR_iCanTpStartOfReceptionID(id)        (PDUR_CANTP_RXIND_BASE[(id)].upId)
#define PduR_iCanTpStartOfReceptionFunc(id)      (PduR_upTpStartOfReceptionTable[(PDUR_CANTP_RXIND_BASE[(id)].upStartOfReceptionID)].PduR_upTpStartOfReceptionFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanTpStartOfReception(id,info,TpSduLength,bufSizePtr)   PduR_dCanTpStartOfReception((id),(info),(TpSduLength),(bufSizePtr))
#else
#define PduR_aCanTpStartOfReception(id,info,TpSduLength,bufSizePtr)   PduR_iCanTpStartOfReceptionFunc(id)(PduR_iCanTpStartOfReceptionID(id),(info),(TpSduLength),(bufSizePtr))
#endif

#define PduR_rCanTpStartOfReception(id,info,TpSduLength,bufSizePtr)   PduR_aCanTpStartOfReception((id),(info),(TpSduLength),(bufSizePtr))

#if defined(PDUR_CONFIG_SINGLE_TPRX)
#define PduR_iCanTpRxIndicationID(id)           (id)
#define PduR_iCanTpRxIndicationFunc(id)           (PDUR_CONFIG_SINGLE_TPRX(TpRxIndication))
#else
#define PduR_iCanTpRxIndicationID(id)           (PDUR_CANTP_RXIND_BASE[(id)].upId)

#define PduR_iCanTpRxIndicationFunc(id)         (PduR_upTpRxIndicationTable[(PDUR_CANTP_RXIND_BASE[(id)].upRxIndicationID)].PduR_upTpRxIndicationFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanTpRxIndication(id,result)      PduR_dCanTpRxIndication((id), (result))
#else
#define PduR_aCanTpRxIndication(id,result)      PduR_iCanTpRxIndicationFunc(id)(PduR_iCanTpRxIndicationID(id), (result))
#endif

#define PduR_rCanTpRxIndication(id,result)       PduR_aCanTpRxIndication((id),(result))

#if defined(PDUR_CONFIG_SINGLE_TPTX_UP)
#define PduR_iCanTpCopyTxDataID(id)        (id)
#define PduR_iCanTpCopyTxDataFunc(id)        (PDUR_CONFIG_SINGLE_TPTX_UP(CopyTxData))
#else
#define PduR_iCanTpCopyTxDataID(id)        (PDUR_CANTP_TXCONF_BASE[(id)].upId)
#define PduR_iCanTpCopyTxDataFunc(id)      (PduR_upTpCopyTxDataTable[(PDUR_CANTP_TXCONF_BASE[(id)].upProvideTxBufID)].PduR_upTpCopyTxDataFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanTpCopyTxData(id,info,retry,avdataptr)    PduR_dCanTpCopyTxData((id),(info),(retry),(avdataptr))
#else
#define PduR_aCanTpCopyTxData(id,info,retry,avdataptr)    PduR_iCanTpCopyTxDataFunc(id)(PduR_iCanTpCopyTxDataID(id), (info),(retry),(avdataptr))
#endif

#define PduR_rCanTpCopyTxData(id,info,retry,avdataptr)     PduR_aCanTpCopyTxData((id),(info),(retry),(avdataptr))

#if defined(PDUR_CONFIG_SINGLE_TPTX_UP)
#define PduR_iCanTpTxConfirmationID(id)         (id)
#define PduR_iCanTpTxConfirmationFunc(id)         (PDUR_CONFIG_SINGLE_TPTX_UP(TpTxConfirmation))
#else
#define PduR_iCanTpTxConfirmationID(id)         (PDUR_CANTP_TXCONF_BASE[(id)].upId)

#define PduR_iCanTpTxConfirmationFunc(id)       (PduR_upTpTxConfirmationTable[(PDUR_CANTP_TXCONF_BASE[(id)].upTxConfirmationID)].PduR_upTpTxConfirmationFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanTpTxConfirmation(id,result)    PduR_dCanTpTxConfirmation((id), (result))
#else
#define PduR_aCanTpTxConfirmation(id,result)    PduR_iCanTpTxConfirmationFunc(id)(PduR_iCanTpTxConfirmationID(id), (result))
#endif

#define PduR_rCanTpTxConfirmation(id, result)    PduR_aCanTpTxConfirmation((id),(result))

#define PDUR_IH_CanTpRx_StartOfReception_Func   PDUR_DET_API(PduR_invId_TpStartOfReception)
#define PDUR_IH_CanTpRx_CopyRxData_Func            PDUR_DET_API(PduR_invId_TpCopyRxData)
#define PDUR_IH_CanTpRx_RxIndication_Func       PDUR_DET_API(PduR_invId_TpRxIndication)
#define PDUR_IH_CanTpTx_CopyTxData_Func            PDUR_DET_API(PduR_invId_TpCopyTxData)
#define PDUR_IH_CanTpTx_TxConfirmation_Func     PDUR_DET_API(PduR_invId_TpTxConfirmation)

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

