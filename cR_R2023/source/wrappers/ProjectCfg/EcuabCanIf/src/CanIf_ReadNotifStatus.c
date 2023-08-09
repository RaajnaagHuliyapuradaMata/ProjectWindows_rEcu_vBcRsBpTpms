

#include "CanIf_Prv.h"

#if (CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus(
                                                                  VAR(PduIdType,AUTOMATIC) CanIfTxSduId
                                                               )
{

    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;

    P2VAR(CanIf_NotifStatusType, AUTOMATIC,AUTOMATIC) lTxNotifPtr;

    VAR(CanIf_NotifStatusType, AUTOMATIC) NotifStatus = CANIF_NO_NOTIFICATION;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;

    CANIF_DET_REPORT_ERROR_NO_NOTIF((FALSE == CanIf_Lok_InitStatus_b), CANIF_RB_READ_TXPDU_CANID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NO_NOTIF((CanIfTxSduId >= CANIF_TOTAL_TXPDUS), \
                                                        CANIF_READ_TX_NOTIF_STATUS_SID, CANIF_E_INVALID_TXPDUID)

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];

    CANIF_DET_REPORT_ERROR_NO_NOTIF((ltxPduCustId_t == 0xFFFFu), CANIF_READ_TX_NOTIF_STATUS_SID, CANIF_E_INVALID_TXPDUID)

    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

    lTxNotifPtr = (CanIf_Lok_TxNotification_aen + ltxPduCustId_t);

    if( FALSE != lTxPduConfig_pst->TxPduReadNotifyStatus )
    {

        SchM_Enter_CanIf_TxRxNotifNoNest();

        NotifStatus = (CanIf_NotifStatusType)(*lTxNotifPtr);

        *(lTxNotifPtr) = CANIF_NO_NOTIFICATION;

        SchM_Exit_CanIf_TxRxNotifNoNest();

    }

    return(NotifStatus);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadRxNotifStatus(VAR(PduIdType, AUTOMATIC) CanIfRxSduId)
{

    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

    P2VAR(CanIf_NotifStatusType, AUTOMATIC,AUTOMATIC) RxNotifStatus_pen;

    VAR(CanIf_NotifStatusType, AUTOMATIC) NotifStatus_ten = CANIF_NO_NOTIFICATION;

    CANIF_DET_REPORT_ERROR_NO_NOTIF((FALSE == CanIf_Lok_InitStatus_b), CANIF_READ_RX_NOTIF_STATUS_SID,CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NO_NOTIF((CanIfRxSduId>= CANIF_CFG_NUM_CANRXPDUIDS) , \
                                                            CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID)

    CANIF_DET_REPORT_ERROR_NO_NOTIF((CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId]== INVALID_ID) , \
                                                               CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID)

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId];

    CANIF_DET_REPORT_ERROR_NO_NOTIF(((RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_DATA) || (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NONE)), CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID)

   // HrhCfg_pcst = (CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst) + RxPduCfg_pcst->Hrhref_t;

    RxNotifStatus_pen = CanIf_Lok_RxNotification_taen;

    if((RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS_DATA) ||                          \
                                        (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS))
    {

        SchM_Enter_CanIf_TxRxNotifNoNest();

        NotifStatus_ten = *(RxNotifStatus_pen + CanIfRxSduId);

        *(RxNotifStatus_pen + CanIfRxSduId) = CANIF_NO_NOTIFICATION;

        SchM_Exit_CanIf_TxRxNotifNoNest();
    }

    return (NotifStatus_ten);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif
