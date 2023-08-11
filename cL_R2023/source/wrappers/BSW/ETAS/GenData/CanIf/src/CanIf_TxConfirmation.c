#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
    uint16 ltxPduCustId_t;
    const CanIf_Cfg_CtrlConfig_tst * lCtrlConfig_pst;
    CanIf_ControllerStateType * lControllerState_p;
    uint8 lControllerId_u8;
    CanIf_NotifStatusType * lTxNotifPtr;

#if(CANIF_RB_NODE_CALIBRATION == STD_ON)

    uint8 lCalibCtrlId;
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_TX_CONFIRMATION_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_VOID_RET(CanTxPduId >= CANIF_TOTAL_TXPDUS, CANIF_TX_CONFIRMATION_SID,CANIF_E_PARAM_LPDU)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];
    CANIF_DET_REPORT_ERROR_VOID_RET((ltxPduCustId_t == 0xFFFFu), CANIF_TX_CONFIRMATION_SID, CANIF_E_PARAM_LPDU)
    lTxPduConfig_pst   = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
#if (CANIF_RB_NODE_CALIBRATION == STD_OFF)
    lCtrlConfig_pst    = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr;
#else
    lCalibCtrlId = CanIf_CanCtrl_CanIfCtrl_MappingTable_acst[lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->getCtrlCfg()];
    lCtrlConfig_pst = &(CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr[lCalibCtrlId]);
#endif
    lControllerId_u8   = lCtrlConfig_pst->CtrlId;
    lControllerState_p = CanIf_Lok_ControllerState_ast + lControllerId_u8;
    lTxNotifPtr = CanIf_Lok_TxNotification_aen;

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
if( ((lControllerState_p->CanIf_TxCnfmStatus) != CANIF_TX_RX_NOTIFICATION) && ((((lControllerState_p->Ctrl_Pdu_mode)& BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT) == (uint8)CANIF_CS_STARTED))
{
    lControllerState_p->CanIf_TxCnfmStatus = CANIF_TX_RX_NOTIFICATION;
}
#endif

if( FALSE != lTxPduConfig_pst->TxPduReadNotifyStatus )
{
    *(lTxNotifPtr + CanTxPduId) = CANIF_TX_RX_NOTIFICATION;
}

if((NULL_PTR != lTxPduConfig_pst->UserTxConfirmation) && (((lControllerState_p->Ctrl_Pdu_mode)& BIT_MASK_CTRL_MODE) == (uint8)CANIF_ONLINE))
{

      if((lTxPduConfig_pst->TxPduTxUserUL == PDUR) || (lTxPduConfig_pst->TxPduTxUserUL == USER))
    {
        (void)CanIf_XCore_LocalCore_TxConfirmation(lTxPduConfig_pst);
    }
      else{
      }
}
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_XCore_LocalCore_TxConfirmation(const CanIf_Cfg_TxPduConfig_tst * CanIf_TxPduConfig_pst)
{
   Std_ReturnType lretval = E_OK;
   const CanIf_Cfg_TxPduConfig_tst * lTxPduConfig_pst;
   CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_TxPduConfig_pst == NULL_PTR), CANIF_INIT_SID, CANIF_E_PARAM_POINTER)
   lTxPduConfig_pst = CanIf_TxPduConfig_pst;
   lTxPduConfig_pst->UserTxConfirmation(lTxPduConfig_pst->TxPduTargetPduId);

   return lretval;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
