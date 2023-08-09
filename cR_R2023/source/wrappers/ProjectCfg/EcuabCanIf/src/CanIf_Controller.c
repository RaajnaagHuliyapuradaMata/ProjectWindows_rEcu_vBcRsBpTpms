

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(
                                                            VAR (uint8,AUTOMATIC) ControllerId,
                                                            VAR(CanIf_ControllerModeType,AUTOMATIC) ControllerMode
                                                        )
{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;

    VAR (Can_ReturnType, AUTOMATIC   ) lCanStatus_en        = CAN_NOT_OK;
    VAR (Std_ReturnType, AUTOMATIC   ) lRetVal_en           = E_NOT_OK;

    VAR(Can_StateTransitionType,AUTOMATIC) lCanMode;

    P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;

    VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_CONTROLLER_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_SET_CONTROLLER_SID, CANIF_E_PARAM_CONTROLLERID)

    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];

    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_SET_CONTROLLER_SID, CANIF_E_PARAM_CONTROLLERID)

    CANIF_DET_REPORT_ERROR_NOT_OK((CANIF_CS_STARTED != ControllerMode) && (CANIF_CS_STOPPED != ControllerMode) && \
                (CANIF_CS_SLEEP != ControllerMode), CANIF_SET_CONTROLLER_SID, CANIF_E_PARAM_CTRLMODE)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    lCtrlConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + lCtrlCustId_u8;

    switch(ControllerMode)
    {

        case CANIF_CS_SLEEP:

            lCanStatus_en = Can_SetControllerMode((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), CAN_T_SLEEP);
            if(lCanStatus_en != CAN_NOT_OK)
            {
                lRetVal_en = E_OK;

                lControllerState_p->ChannelMode = CANIF_OFFLINE;

#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)

                if((lCtrlConfig_pst->PnCtrlEn == TRUE) && (lControllerState_p->BlPnTxFilter != TRUE))
                {

                    lControllerState_p->BlPnTxFilter = TRUE;
                }

#endif
            #if(CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
                lControllerState_p->ValidationSts_b = CANIF_RESET;
            #endif
#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

                SchM_Enter_CanIf_TxBufAccessNoNest();

                CanIf_Lok_ClearTxChannelBuffer(lCtrlCustId_u8);

                SchM_Exit_CanIf_TxBufAccessNoNest();
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

                CanIf_XCore_RxClrPipeFlag_b = TRUE;

                CanIf_XCore_ClearPipes(lCtrlCustId_u8);
#endif

            }

            break;

        case CANIF_CS_STARTED:

            lCanStatus_en = Can_SetControllerMode((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), CAN_T_START);
            if(lCanStatus_en!= CAN_NOT_OK)
            {
               #if (CANIF_LITE_CONFIGURATION == STD_ON)

               //lControllerState_p->ChannelMode = CANIF_ONLINE;
               lControllerState_p->DeviceMode  = ControllerMode;
               #endif
               lRetVal_en = E_OK;
            }

            break;

        case CANIF_CS_STOPPED:

            if(lControllerState_p->DeviceMode == CANIF_CS_SLEEP)
            {
                lCanMode = CAN_T_WAKEUP;
            }
            else
            {
                lCanMode = CAN_T_STOP;
            }

            lCanStatus_en = Can_SetControllerMode((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), lCanMode);
            if(lCanStatus_en != CAN_NOT_OK)
            {
                lRetVal_en = E_OK;

                lControllerState_p->ChannelMode = CANIF_TX_OFFLINE;

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

                SchM_Enter_CanIf_TxBufAccessNoNest();

                CanIf_Lok_ClearTxChannelBuffer(lCtrlCustId_u8);

                SchM_Exit_CanIf_TxBufAccessNoNest();
#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

                CanIf_XCore_ClearPipes(lCtrlCustId_u8);
#endif

            }
            break;
        default:

            break;
    }

return(lRetVal_en);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(
                                           VAR(uint8,AUTOMATIC) ControllerId,
                                           P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr
                                                        )
{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;
#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
    VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_CONTROLLER_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_GET_CONTROLLER_SID, \
                                                                            CANIF_E_PARAM_CONTROLLERID)
#if CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_GET_CONTROLLER_SID, \
                                                                            CANIF_E_PARAM_CONTROLLERID)

    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == ControllerModePtr), CANIF_GET_CONTROLLER_SID,CANIF_E_PARAM_POINTER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    *ControllerModePtr = lControllerState_p->DeviceMode;

    return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(
                                                VAR(uint8,AUTOMATIC) ControllerId
                                             )

{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)||(CANIF_PUBLIC_TXBUFFERING == STD_ON) || (CANIF_XCORE_CFG_ENABLED != STD_OFF))
    VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
#endif

    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) lCallBackPtr_p;

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CONTROLLER_BUSOFF_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET((ControllerId >= CANIF_TOTAL_CTRLS), \
                                                                    CANIF_CONTROLLER_BUSOFF_SID,CANIF_E_PARAM_CONTROLLER)
#if ((CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)||(CANIF_PUBLIC_TXBUFFERING == STD_ON)||(CANIF_XCORE_CFG_ENABLED != STD_OFF))
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((lCtrlCustId_u8 == 0xFFu), CANIF_CONTROLLER_BUSOFF_SID,CANIF_E_PARAM_CONTROLLER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    lCallBackPtr_p = &CanIf_Callback;

    SchM_Enter_CanIf_ControllerState();

    if(lControllerState_p->DeviceMode != CANIF_CS_UNINIT)
    {
        lControllerState_p->DeviceMode = CANIF_CS_STOPPED;
    }

#if CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT!= STD_OFF

    lControllerState_p->CanIf_TxCnfmStatus = CANIF_NO_NOTIFICATION;

#endif

    lControllerState_p->ChannelMode = CANIF_TX_OFFLINE;

    SchM_Exit_CanIf_ControllerState();

#if(CANIF_PUBLIC_TXBUFFERING == STD_ON)

    SchM_Enter_CanIf_TxBufAccessNoNest();

    CanIf_Lok_ClearTxChannelBuffer(lCtrlCustId_u8);

    SchM_Exit_CanIf_TxBufAccessNoNest();

#endif

#if (CANIF_XCORE_CFG_ENABLED != STD_OFF)

    CanIf_XCore_ClearPipes(lCtrlCustId_u8);
#endif

    if(lCallBackPtr_p->User_ControllerBusOff != NULL_PTR)
    {

        lCallBackPtr_p->User_ControllerBusOff(ControllerId);
    }

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication(  VAR(uint8,AUTOMATIC) ControllerId,
                                                        VAR(CanIf_ControllerModeType,AUTOMATIC) ControllerMode
                                                    )
{

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) lControllerState_p;

    P2CONST(CanIf_CallbackFuncType, AUTOMATIC, AUTOMATIC) lCallBackPtr_p;
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_CONTROLLER_MODE_IND_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET((ControllerId >= CANIF_TOTAL_CTRLS), \
                                                                CANIF_CONTROLLER_MODE_IND_SID,CANIF_E_PARAM_CONTROLLER)
#if (CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON)
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((lCtrlCustId_u8 == 0xFFu), CANIF_CONTROLLER_MODE_IND_SID,CANIF_E_PARAM_CONTROLLER)

    lControllerState_p = CanIf_Lok_ControllerState_ast + ControllerId;

    lCallBackPtr_p =  &CanIf_Callback;

    if(ControllerMode != CANIF_CS_UNINIT)
    {

        lControllerState_p->DeviceMode = ControllerMode;

    }

    if(lCallBackPtr_p->User_ControllerModeIndication != NULL_PTR)
    {

        lCallBackPtr_p->User_ControllerModeIndication(ControllerId, ControllerMode);
    }

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
