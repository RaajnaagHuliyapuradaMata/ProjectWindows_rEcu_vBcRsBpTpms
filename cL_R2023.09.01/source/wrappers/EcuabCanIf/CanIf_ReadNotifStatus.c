

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
CanIf_NotifStatusType CanIf_ReadTxNotifStatus(
   PduIdType CanIfTxSduId){
   const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
   CanIf_NotifStatusType * lTxNotifPtr;
   CanIf_NotifStatusType NotifStatus = CANIF_NO_NOTIFICATION;
   uint16 ltxPduCustId_t;

   CANIF_DET_REPORT_ERROR_NO_NOTIF((FALSE == CanIf_Lok_InitStatus_b), CANIF_RB_READ_TXPDU_CANID, CANIF_E_UNINIT)
   CANIF_DET_REPORT_ERROR_NO_NOTIF((CanIfTxSduId >= CANIF_TOTAL_TXPDUS), \
                                                        CANIF_READ_TX_NOTIF_STATUS_SID, CANIF_E_INVALID_TXPDUID)

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
   CANIF_DET_REPORT_ERROR_NO_NOTIF((ltxPduCustId_t == 0xFFFFu), CANIF_READ_TX_NOTIF_STATUS_SID, CANIF_E_INVALID_TXPDUID)
    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
    lTxNotifPtr = (CanIf_Lok_TxNotification_aen + CanIfTxSduId);
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
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
CanIf_NotifStatusType CanIf_ReadRxNotifStatus(
   PduIdType CanIfRxSduId){
   const CanIf_Cfg_RxPduType_tst * RxPduCfg_pcst;
   CanIf_NotifStatusType * RxNotifStatus_pen;
   CanIf_NotifStatusType NotifStatus_ten = CANIF_NO_NOTIFICATION;
   CANIF_DET_REPORT_ERROR_NO_NOTIF((FALSE == CanIf_Lok_InitStatus_b), CANIF_READ_RX_NOTIF_STATUS_SID,CANIF_E_UNINIT)

   CANIF_DET_REPORT_ERROR_NO_NOTIF((CanIfRxSduId>= CANIF_CFG_NUM_CANRXPDUIDS) , \
                                                            CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID)

   CANIF_DET_REPORT_ERROR_NO_NOTIF((CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId]== CANIF_INVALID_ID) , \
                                                               CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID)

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId];
   CANIF_DET_REPORT_ERROR_NO_NOTIF(((RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_DATA) || (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NONE)), CANIF_READ_RX_NOTIF_STATUS_SID, CANIF_E_INVALID_RXPDUID)
    RxNotifStatus_pen = CanIf_Lok_RxNotification_taen;
   if((RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS_DATA) ||                          \
                                        (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS)){
        SchM_Enter_CanIf_TxRxNotifNoNest();
        NotifStatus_ten = *(RxNotifStatus_pen + CanIfRxSduId);
        *(RxNotifStatus_pen + CanIfRxSduId) = CANIF_NO_NOTIFICATION;
        SchM_Exit_CanIf_TxRxNotifNoNest();
   }
    return (NotifStatus_ten);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
