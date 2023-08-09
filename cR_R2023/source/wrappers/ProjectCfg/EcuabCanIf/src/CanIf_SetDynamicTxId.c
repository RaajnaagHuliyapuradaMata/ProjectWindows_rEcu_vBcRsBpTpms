

#include "CanIf_Prv.h"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
#if (CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)
void CanIf_SetDynamicTxId(VAR(PduIdType,AUTOMATIC) CanTxPduId, VAR(Can_IdType,AUTOMATIC) CanId)
{
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
    P2VAR(Can_IdType,AUTOMATIC,AUTOMATIC) DynIdPtr_Temp;

#if CANIF_PUBLIC_DEV_ERROR_DETECT != STD_OFF
     VAR(uint8, AUTOMATIC)canifMSBbits_u8;
#endif

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_DYNAMIC_TXID_SID, CANIF_E_UNINIT)
     CANIF_DET_REPORT_ERROR_VOID_RET(CanTxPduId>=CANIF_TOTAL_TXPDUS, CANIF_SET_DYNAMIC_TXID_SID,CANIF_E_INVALID_TXPDUID)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];
    CANIF_DET_REPORT_ERROR_VOID_RET((ltxPduCustId_t == 0xFFFFu), CANIF_SET_DYNAMIC_TXID_SID,CANIF_E_INVALID_TXPDUID)
    lTxPduConfig_pst = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
    CANIF_DET_REPORT_ERROR_VOID_RET((CANIF_STATIC == (lTxPduConfig_pst->TxPduType)), CANIF_SET_DYNAMIC_TXID_SID,CANIF_E_INVALID_TXPDUID)
    DynIdPtr_Temp = CanIf_DynTxPduCanId_au32;

#if CANIF_PUBLIC_DEV_ERROR_DETECT != STD_OFF
    canifMSBbits_u8= (uint8)(CanId>>30u);
    CANIF_DET_REPORT_ERROR_VOID_RET((((canifMSBbits_u8 == CANIF_ZERO)|| \
            (canifMSBbits_u8 == CANIF_ONE)) && ((CanId & CANIF_MSB_BIT_RESET) > CANIF_CAN_STD_VAL)),
            CANIF_SET_DYNAMIC_TXID_SID, CANIF_E_PARAM_CANID)

    CANIF_DET_REPORT_ERROR_VOID_RET((((canifMSBbits_u8 == CANIF_TWO)||(canifMSBbits_u8 == CANIF_THREE)) && \
            ((CanId & CANIF_MSB_BIT_RESET)  > CANIF_CAN_XTD_VAL)), CANIF_SET_DYNAMIC_TXID_SID, CANIF_E_PARAM_CANID)
#endif

    if(lTxPduConfig_pst->TxPduType != CANIF_STATIC)
    {
        *(DynIdPtr_Temp + (lTxPduConfig_pst->TxPduType)) = CanId;
    }
}
#endif
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
