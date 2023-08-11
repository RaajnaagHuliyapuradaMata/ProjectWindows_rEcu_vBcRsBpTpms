

#include "CanIf_Prv.h"

#if (CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

CanIf_NotifStatusType CanIf_GetTxConfirmationState(
                                       uint8 ControllerId
                                               )
{
    CanIf_NotifStatusType lTxConfmStatus;
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    uint8 lCtrlCustId_u8;
#endif

    CANIF_DET_REPORT_ERROR_NO_NOTIF((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_TX_CONFIRMATION_STATE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NO_NOTIF((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_GET_TX_CONFIRMATION_STATE_SID, \
                                                                                        CANIF_E_PARAM_CONTROLLERID)
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_NO_NOTIF((lCtrlCustId_u8 == 0xFFu), CANIF_GET_TX_CONFIRMATION_STATE_SID, \
                                                                                        CANIF_E_PARAM_CONTROLLERID)

    lTxConfmStatus = (CanIf_Lok_ControllerState_ast + ControllerId)->CanIf_TxCnfmStatus;

    return(lTxConfmStatus);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

