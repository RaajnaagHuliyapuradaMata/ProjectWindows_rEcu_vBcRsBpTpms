#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_TxConfirmation(
   Type_SwcServiceCom_tIdPdu CanTxPduId
){
   const CanIf_Cfg_TxPduConfig_tst* lTxPduConfig_pst;
         uint16                     ltxPduCustId_t;
   const CanIf_Cfg_CtrlConfig_tst*  lCtrlConfig_pst;
         CanIf_ControllerStateType* lControllerState_p;
         uint8                      lControllerId_u8;
         CanIf_NotifStatusType*     lTxNotifPtr;

   ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];
   lTxPduConfig_pst   = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
#if(CANIF_RB_NODE_CALIBRATION == STD_OFF)
   lCtrlConfig_pst    = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr;
#endif
   lControllerId_u8   = lCtrlConfig_pst->CtrlId;
   lControllerState_p = CanIf_Lok_ControllerState_ast + lControllerId_u8;
   lTxNotifPtr        = CanIf_Lok_TxNotification_aen;

   if(
         FALSE
      != lTxPduConfig_pst->TxPduReadNotifyStatus
   ){
      *(lTxNotifPtr + CanTxPduId) = CANIF_TX_RX_NOTIFICATION;
   }

   if(
         (
               NULL_PTR
            != lTxPduConfig_pst->UserTxConfirmation
         )
      && (
               (
                     lControllerState_p->Ctrl_Pdu_mode
                  &  BIT_MASK_CTRL_MODE
               )
            == (uint8)CANIF_ONLINE
         )
   ){
      if(
            (lTxPduConfig_pst->TxPduTxUserUL == PDUR)
         || (lTxPduConfig_pst->TxPduTxUserUL == USER)
         || (CANIF_XCORE_CFG_ENABLED == STD_OFF)
      ){
         (void)CanIf_XCore_LocalCore_TxConfirmation(
            lTxPduConfig_pst
         );
      }
      else{
      }
   }
}

Std_ReturnType CanIf_XCore_LocalCore_TxConfirmation(
   const CanIf_Cfg_TxPduConfig_tst * CanIf_TxPduConfig_pst
){
         Std_ReturnType             lretval = E_OK;
   const CanIf_Cfg_TxPduConfig_tst* lTxPduConfig_pst = CanIf_TxPduConfig_pst;

   lTxPduConfig_pst->UserTxConfirmation(
      lTxPduConfig_pst->TxPduTargetPduId
   );

   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
