

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_TriggerIPDUSend(PduIdType PduId)
{
#ifdef COM_TxIPduTimeOut
    Com_TxIpduConstPtrType      TxIpduConstPtr;
#endif

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if ( Com_Lok_DETCheck_Param( (PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TriggerIpduSend) )
#endif
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

#ifdef COM_TxIPduTimeOut

        TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);
#endif

        if (Com_CheckTxIPduStatus(PduId))
        {
#ifdef COM_TP_IPDUTYPE

            if (Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,COM_GET_TXPDURAM_S(PduId).Com_TxFlags) != COM_TRUE)
#endif
            {
                Com_SendIpduInfo sendIpduFlag_u16  = COM_CLEAR_SENDIPDU_FLAGS;

                sendIpduFlag_u16.isEventTrig       = COM_SET;

                sendIpduFlag_u16.ignoreRepetitions = COM_SET;

# ifdef COM_TxIPduTimeOut

                sendIpduFlag_u16.isTimeoutReq = COM_BOOL_TO_UNSIGNED(TxIpduConstPtr->Timeout_Fact != COM_ZERO);
# endif

                Com_Lok_SendIpdu((PduIdType) PduId, sendIpduFlag_u16);
            }
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

