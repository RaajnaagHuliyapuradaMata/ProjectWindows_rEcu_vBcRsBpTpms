

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_SetPduMode(
                                                    uint8 ControllerId,
                                                    CanIf_PduModeType PduModeRequest
                                                 )
{

    CanIf_ControllerStateType * lControllerState_p;

#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON))
    uint8 lCtrlCustId_u8;
#endif
    Std_ReturnType lRetVal_en           = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_PDU_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_SET_PDU_MODE_SID, \
            CANIF_E_PARAM_CONTROLLERID)
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON))
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_SET_PDU_MODE_SID, \
            CANIF_E_PARAM_CONTROLLERID)

    if((CANIF_OFFLINE != PduModeRequest) && (CANIF_TX_OFFLINE != PduModeRequest) \
                && (CANIF_ONLINE != PduModeRequest)

    #if(CANIF_TXOFFLINEACTIVE_SUPPORT == STD_ON)
                && (CANIF_TX_OFFLINE_ACTIVE != PduModeRequest)

    #endif

    #if(CANIF_USER_TP_TX_OFFLINE_MODE == STD_ON)
                && (CANIF_TX_TP_ONLINE != PduModeRequest) && (CANIF_TX_USER_TP_ONLINE != PduModeRequest)

    #endif
         )
        {
             CANIF_DET_REPORT_ERROR_NO_CONDITON((CANIF_SET_PDU_MODE_SID), (CANIF_E_PARAM_PDU_MODE))
        }

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;
    if((((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE)>>CANIF_Ctrl_BIT_SHIFT)!= (uint8)CANIF_CS_STARTED)
    {
        lRetVal_en = E_NOT_OK;
    }
    else
    {
   switch(PduModeRequest){
            case CANIF_OFFLINE:
                break;

            case CANIF_TX_OFFLINE:
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

        lControllerState_p->Ctrl_Pdu_mode = ((uint8)PduModeRequest)|((lControllerState_p->Ctrl_Pdu_mode)&BIT_MASK_PDU_MODE);

        lRetVal_en = E_OK;
    }
    return(lRetVal_en);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_GetPduMode(
                                                    uint8 ControllerId,
                                                    CanIf_PduModeType * PduModePtr
                                                 )
{

    CanIf_ControllerStateType * lControllerState_p;

#if(CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    uint8 lCtrlCustId_u8;
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

    *PduModePtr = (CanIf_PduModeType)((lControllerState_p->Ctrl_Pdu_mode)& BIT_MASK_CTRL_MODE);

    return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
