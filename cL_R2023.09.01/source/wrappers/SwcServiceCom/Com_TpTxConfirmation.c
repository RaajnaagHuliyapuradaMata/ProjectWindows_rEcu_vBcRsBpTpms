

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

void Com_TpTxConfirmation(PduIdType PduId, Std_ReturnType Result)
{

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TpTxConfirmation))
#endif
   {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        if(Com_CheckTxIPduStatus(PduId))
        {
            Com_TxIpduRamPtrType TxIpduRamPtr;

            TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);

            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags))
            {
                if(E_OK == Result)
                {

                    Com_InternalTxConfirmation(PduId);
                }

                Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
            }
        }
   }
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

