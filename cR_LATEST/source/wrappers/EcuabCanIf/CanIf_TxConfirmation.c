#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_TxConfirmation(Type_SwcServiceCom_tIdPdu CanTxPduId){
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
   VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
   P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;
   P2VAR( CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC    ) lControllerState_p;
   VAR (uint8, AUTOMATIC           ) lControllerId_u8      = 0;
   VAR (   CanIf_PduModeType, AUTOMATIC                        ) lChannelMode_en;

#if(CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
   P2VAR(CanIf_NotifStatusType, AUTOMATIC, AUTOMATIC) lTxNotifPtr;
#endif

    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];
    lTxPduConfig_pst   = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
    lCtrlConfig_pst    = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr;
    lControllerId_u8   = lCtrlConfig_pst->CtrlId;

    lControllerState_p = CanIf_Lok_ControllerState_ast + lControllerId_u8;
    lChannelMode_en    = lControllerState_p->ChannelMode;

#if(CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
    lTxNotifPtr = CanIf_Lok_TxNotification_aen;
#endif

#if(CANIF_READTXPDU_NOTIFY_STATUS_API != STD_OFF)
if( FALSE != lTxPduConfig_pst->TxPduReadNotifyStatus ){
    *(lTxNotifPtr + CanTxPduId) = CANIF_TX_RX_NOTIFICATION;
}
#endif

if((NULL_PTR != lTxPduConfig_pst->UserTxConfirmation) && (lChannelMode_en == CANIF_ONLINE)){
   if((lTxPduConfig_pst->TxPduTxUserUL == PDUR ) || (lTxPduConfig_pst->TxPduTxUserUL == USER ) || (CANIF_XCORE_CFG_ENABLED == STD_OFF)){
        (void)CanIf_XCore_LocalCore_TxConfirmation(lTxPduConfig_pst);
   }
   else{
   }
}
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_TxConfirmation(P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_TxPduConfig_pst){
   Std_ReturnType lretval = E_OK;
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
   lTxPduConfig_pst = CanIf_TxPduConfig_pst;
   lTxPduConfig_pst->UserTxConfirmation(lTxPduConfig_pst->TxPduTargetPduId);
   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
