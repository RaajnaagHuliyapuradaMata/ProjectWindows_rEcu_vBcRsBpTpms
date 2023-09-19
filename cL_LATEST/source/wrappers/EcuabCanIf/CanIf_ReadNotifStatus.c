#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus(
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanIfTxSduId
){
       VAR(uint16,                    AUTOMATIC                 ) ltxPduCustId_t   = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanIfTxSduId];
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst = CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr + ltxPduCustId_t;
     P2VAR(CanIf_NotifStatusType,     AUTOMATIC, AUTOMATIC      ) lTxNotifPtr      = (CanIf_Lok_TxNotification_aen + CanIfTxSduId);
       VAR(CanIf_NotifStatusType,     AUTOMATIC                 ) NotifStatus      = CANIF_NO_NOTIFICATION;
   if(
         FALSE
      != lTxPduConfig_pst->TxPduReadNotifyStatus
   ){
      SchM_Enter_CanIf_TxRxNotifNoNest();
      NotifStatus    = (CanIf_NotifStatusType)(*lTxNotifPtr);
      *(lTxNotifPtr) = CANIF_NO_NOTIFICATION;
      SchM_Exit_CanIf_TxRxNotifNoNest();
   }
   return NotifStatus;
}

FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadRxNotifStatus(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanIfRxSduId
){
   P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst     = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId];
   P2VAR(CanIf_NotifStatusType,     AUTOMATIC, AUTOMATIC      ) RxNotifStatus_pen = CanIf_Lok_RxNotification_taen;
   VAR(CanIf_NotifStatusType,       AUTOMATIC                 ) NotifStatus_ten   = CANIF_NO_NOTIFICATION;
   if(
         (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS_DATA)
      || (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS)
   ){
      SchM_Enter_CanIf_TxRxNotifNoNest();
      NotifStatus_ten = *(RxNotifStatus_pen + CanIfRxSduId);
      *(RxNotifStatus_pen + CanIfRxSduId) = CANIF_NO_NOTIFICATION;
      SchM_Exit_CanIf_TxRxNotifNoNest();
   }
   return NotifStatus_ten;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
