

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void, COM_CODE) Com_TpTxConfirmation( PduIdType PduId, Std_ReturnType Result )
{

    Com_TxIpduRamPtrType TxIPduRamPtr;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TpTxConfirmation))
#endif
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        TxIPduRamPtr = &COM_GET_TXPDURAM_S(PduId);

        if(Com_CheckTxIPduStatus((PduIdType)PduId))
        {

            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIPduRamPtr->Com_TxFlags) && (E_OK == Result))
            {
                Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIPduRamPtr->Com_TxFlags,COM_FALSE);

                Com_InternalProcessTxConfirmation(PduId);
            }
        }
    }
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

