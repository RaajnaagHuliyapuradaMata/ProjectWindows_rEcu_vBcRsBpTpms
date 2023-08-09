

#include "CanIf_Prv.h"

#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON && CANIF_CFG_READRXPDU_DATA_IN_RXPDUS == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData(VAR(PduIdType, AUTOMATIC) CanIfRxSduId,
        P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) CanIfRxInfoPtr)
{

    P2CONST(CanIf_Cfg_Hrhtype_tst, AUTOMATIC, CANIF_CFG_CONST) HrhCfg_pcst;

    P2CONST(CanIf_Cfg_RxPduType_tst, AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;

    P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC) ControllerState_ps;

    VAR(uint8_least, AUTOMATIC) Status;

    VAR (CanIf_ControllerModeType, AUTOMATIC) DeviceMode_Temp;

    VAR (CanIf_PduModeType, AUTOMATIC) ChannelMode_Temp;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_READ_RX_PDU_DATA_SID, CANIF_E_UNINIT)

    Status = E_NOT_OK;

    CANIF_DET_REPORT_ERROR_NOT_OK((CanIfRxSduId>= CANIF_CFG_NUM_CANRXPDUIDS), \
                                                                CANIF_READ_RX_PDU_DATA_SID, CANIF_E_INVALID_RXPDUID)
    CANIF_DET_REPORT_ERROR_NOT_OK((CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId]== INVALID_ID), \
                                                                   CANIF_READ_RX_PDU_DATA_SID, CANIF_E_INVALID_RXPDUID)

    RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + CanIf_Lok_ConfigSet_tpst->RxPduIdTable_Ptr[CanIfRxSduId];

    CANIF_DET_REPORT_ERROR_NOT_OK(((RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NOTIFSTATUS)  || \
                                (RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8 == CANIF_READ_NONE)), \
                                            CANIF_READ_RX_PDU_DATA_SID, CANIF_E_INVALID_RXPDUID)

    CANIF_DET_REPORT_ERROR_NOT_OK((NULL_PTR == CanIfRxInfoPtr), CANIF_READ_RX_PDU_DATA_SID, CANIF_E_PARAM_POINTER)

    HrhCfg_pcst = (CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst) + RxPduCfg_pcst->Hrhref_t;

    SchM_Enter_CanIf_ControllerState();

    ControllerState_ps = CanIf_Lok_ControllerState_ast + (HrhCfg_pcst->ControllerId_u8);

    DeviceMode_Temp = ControllerState_ps->DeviceMode;
    ChannelMode_Temp = ControllerState_ps->ChannelMode;

    SchM_Exit_CanIf_ControllerState();

    if((CANIF_CS_STARTED == DeviceMode_Temp) && ((CANIF_ONLINE == ChannelMode_Temp) ||
            (CANIF_TX_OFFLINE == ChannelMode_Temp)))
    {

        CanIf_Lok_ReadRxBuffer(CanIfRxInfoPtr, RxPduCfg_pcst);

        Status = E_OK;
    }

    return((Std_ReturnType)Status);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif

