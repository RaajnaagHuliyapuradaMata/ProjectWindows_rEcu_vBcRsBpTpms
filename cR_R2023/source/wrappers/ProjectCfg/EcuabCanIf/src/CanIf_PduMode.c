

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode(
                                                    VAR(uint8,AUTOMATIC) ControllerId,
                                                    VAR(CanIf_PduModeType,AUTOMATIC) PduModeRequest
                                                 )
{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;
#endif
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)||(CANIF_PUBLIC_TXBUFFERING == STD_ON)||(CANIF_PUBLIC_PN_SUPPORT == STD_ON) || (CANIF_XCORE_CFG_ENABLED != STD_OFF))
    VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
#endif
    VAR (Std_ReturnType, AUTOMATIC   ) lRetVal_en           = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_PDU_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_SET_PDU_MODE_SID, \
            CANIF_E_PARAM_CONTROLLERID)
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)||(CANIF_PUBLIC_TXBUFFERING == STD_ON)||(CANIF_PUBLIC_PN_SUPPORT == STD_ON)||(CANIF_XCORE_CFG_ENABLED != STD_OFF))
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_SET_PDU_MODE_SID, \
            CANIF_E_PARAM_CONTROLLERID)

    CANIF_DET_REPORT_ERROR_NOT_OK((CANIF_OFFLINE != PduModeRequest) && (CANIF_TX_OFFLINE != PduModeRequest) \
            && (CANIF_ONLINE != PduModeRequest)

#if(CANIF_TXOFFLINEACTIVE_SUPPORT == STD_ON)
            && (CANIF_TX_OFFLINE_ACTIVE != PduModeRequest)

#endif

#if(CANIF_USER_TP_TX_OFFLINE_MODE == STD_ON)
            && (CANIF_TX_TP_ONLINE != PduModeRequest) && (CANIF_TX_USER_TP_ONLINE != PduModeRequest)

#endif
            , CANIF_SET_PDU_MODE_SID, CANIF_E_PARAM_PDU_MODE)

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
    lCtrlConfig_pst           = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + lCtrlCustId_u8;
#endif
    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    if(lControllerState_p->DeviceMode!= CANIF_CS_STARTED)
    {
        lRetVal_en = E_NOT_OK;
    }
    else
    {

        switch(PduModeRequest)
        {
            case CANIF_OFFLINE:
#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

                SchM_Enter_CanIf_TxBufAccessNoNest();

                CanIf_Lok_ClearTxChannelBuffer(lCtrlCustId_u8);

                SchM_Exit_CanIf_TxBufAccessNoNest();
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

                CanIf_XCore_RxClrPipeFlag_b = TRUE;

                CanIf_XCore_ClearPipes(lCtrlCustId_u8);
#endif

                break;

            case CANIF_TX_OFFLINE:
#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

                SchM_Enter_CanIf_TxBufAccessNoNest();

                CanIf_Lok_ClearTxChannelBuffer(lCtrlCustId_u8);

                SchM_Exit_CanIf_TxBufAccessNoNest();
#endif

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)

                if((lCtrlConfig_pst->PnCtrlEn == TRUE) && (lControllerState_p->BlPnTxFilter != TRUE))
                {
                    lControllerState_p->BlPnTxFilter = TRUE;
                }

#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

                CanIf_XCore_ClearPipes(lCtrlCustId_u8);
#endif

                break;

            case CANIF_ONLINE:
#if(CANIF_TXOFFLINEACTIVE_SUPPORT == STD_ON)
            case CANIF_TX_OFFLINE_ACTIVE:
#endif

#if(CANIF_USER_TP_TX_OFFLINE_MODE != STD_OFF)
            case CANIF_TX_TP_ONLINE:
            case CANIF_TX_USER_TP_ONLINE:
#endif
                break;

            default:

                break;

        }

        lControllerState_p->ChannelMode = PduModeRequest;

        lRetVal_en = E_OK;
    }
    return(lRetVal_en);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetPduMode(
                                                    VAR(uint8,AUTOMATIC) ControllerId,
                                                    P2VAR(CanIf_PduModeType, AUTOMATIC,CANIF_APPL_DATA) PduModePtr
                                                 )
{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;
#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_PDU_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_GET_PDU_MODE_SID, \
            CANIF_E_PARAM_CONTROLLERID)
#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_GET_PDU_MODE_SID, \
            CANIF_E_PARAM_CONTROLLERID)

    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == PduModePtr), CANIF_GET_PDU_MODE_SID, CANIF_E_PARAM_POINTER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    *PduModePtr = lControllerState_p->ChannelMode;

    return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
