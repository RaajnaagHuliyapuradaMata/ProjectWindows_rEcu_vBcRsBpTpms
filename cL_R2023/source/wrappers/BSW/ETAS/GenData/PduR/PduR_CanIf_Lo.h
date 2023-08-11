
#ifndef PDUR_CANIF_LO_H
#define PDUR_CANIF_LO_H

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#define PduR_CanIf_upIfRxIndicationFuncId(id)       (PDUR_CANIF_RXIND_BASE[(id)].upRxIndicationID)

#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_iCanIfRxIndicationID(id)        (id)
#define PduR_iCanIfRxIndicationFunc(id)        (PDUR_CONFIG_SINGLE_IFRX(RxIndication))
#else
#define PduR_iCanIfRxIndicationID(id)        (PDUR_CANIF_RXIND_BASE[(id)].upId)
#define PduR_iCanIfRxIndicationFunc(id)        (PduR_upIfRxIndicationTable[(PDUR_CANIF_RXIND_BASE[(id)].upRxIndicationID)].PduR_upIfRxIndicationFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanIfRxIndication(id, ptr)     PduR_dCanIfRxIndication((id), (ptr))
#else
#define PduR_aCanIfRxIndication(id, ptr)     PduR_iCanIfRxIndicationFunc(id)(PduR_iCanIfRxIndicationID(id), (ptr))
#endif

#define PduR_rCanIfRxIndication(id, ptr)      PduR_aCanIfRxIndication((id), (ptr))

#if defined(PDUR_CONFIG_SINGLE_IFTX_UP)
#define PduR_iCanIfTxConfirmationID(id)      (id)
#define PduR_iCanIfTxConfirmationFunc(id)      (PDUR_CONFIG_SINGLE_IFTX_UP(TxConfirmation))
#else
#define PduR_iCanIfTxConfirmationID(id)      (PDUR_CANIF_TXCONF_BASE[(id)].upId)
#define PduR_iCanIfTxConfirmationFunc(id)    (PduR_upIfTxConfirmationTable[(PDUR_CANIF_TXCONF_BASE[(id)].upTxConfirmationID)].PduR_upIfTxConfirmationFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aCanIfTxConfirmation(id)        PduR_dCanIfTxConfirmation(id)
#else
#define PduR_aCanIfTxConfirmation(id)        PduR_iCanIfTxConfirmationFunc(id)(PduR_iCanIfTxConfirmationID(id))
#endif

#define PduR_rCanIfTxConfirmation(id)         PduR_aCanIfTxConfirmation(id)

#define PDUR_IH_CanIfRx_RxIndication_Func     PDUR_DET_API(PduR_invId_IfRxIndication)
#define PDUR_IH_CanIfTx_TxConfirmation_Func   PDUR_DET_API(PduR_invId_IfTxConfirmation)

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

