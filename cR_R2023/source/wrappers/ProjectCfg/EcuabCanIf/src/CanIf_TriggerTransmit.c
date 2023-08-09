#include "CanIf_Prv.h"

#if (CANIF_TRIGGERTRANSMIT_SUPPORT == STD_ON)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
    VAR (Std_ReturnType, AUTOMATIC   ) lRetVal_en = E_NOT_OK;
    P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst;
    VAR(uint16, AUTOMATIC)          ltxPduCustId_t;
    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_TRIGGER_TRANSMIT_SID, CANIF_E_UNINIT)
    ltxPduCustId_t = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[TxPduId];
    lTxPduConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;

    if(lTxPduConfig_pst->TxPduTriggerTransmit == TRUE)
    {
         if(NULL_PTR != lTxPduConfig_pst->UserTriggerTransmit)
         {
             lRetVal_en = lTxPduConfig_pst->UserTriggerTransmit(TxPduId, PduInfoPtr);
         }
    }

    return lRetVal_en;
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif
