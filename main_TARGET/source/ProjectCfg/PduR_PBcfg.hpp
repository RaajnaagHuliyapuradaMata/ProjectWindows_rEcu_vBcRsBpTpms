#ifndef PDUR_PBCFG_H
#define PDUR_PBCFG_H
#include "PduR_Types.hpp"

#if !defined(PduR_RF_CanIf_Transmit)
#define PduR_RF_CanIf_Transmit    (0)
#endif

#if !defined(PduR_RF_CanTp_Transmit)
#define PduR_RF_CanTp_Transmit    (1)
#endif

#define MAX_NO_OF_LO_TXTABLE_ENTRIES 1

#if !defined(PduR_IH_CancelTransmit)
#define PduR_IH_CancelTransmit    (0)
#endif

#if !defined(PduR_RF_CanTp_CancelTransmit)
#define PduR_RF_CanTp_CancelTransmit    (1)
#endif

#define MAX_NO_OF_LO_CANCEL_TXTABLE_ENTRIES 1

#if !defined(PduR_RF_Com_RxIndication)
#define PduR_RF_Com_RxIndication    (0)
#endif

#define MAX_NO_OF_UPIF_RXINDICATION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Com_TxConfirmation)
#define PduR_RF_Com_TxConfirmation    (0)
#endif

#define MAX_NO_OF_UPIF_TXCONFIRMATION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_CopyRxData)
#define PduR_RF_Dcm_CopyRxData    (0)
#endif

#define MAX_NO_OF_UPTP_COPYRXDATA_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_StartOfReception)
#define PduR_RF_Dcm_StartOfReception    (0)
#endif

#define MAX_NO_OF_UPTP_STARTOFRECEPTION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_TpRxIndication)
#define PduR_RF_Dcm_TpRxIndication    (0)
#endif

#define MAX_NO_OF_UPTP_RXINDICATION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_CopyTxData)
#define PduR_RF_Dcm_CopyTxData    (0)
#endif

#define MAX_NO_OF_UPTP_COPYTXDATA_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_TpTxConfirmation)
#define PduR_RF_Dcm_TpTxConfirmation    (0)
#endif

#define MAX_NO_OF_UPTP_TXCONFIRMATION_TABLE_ENTRIES 0

#endif
