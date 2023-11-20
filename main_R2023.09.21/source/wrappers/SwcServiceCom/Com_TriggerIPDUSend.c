#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_TriggerIPDUSend(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId)
{
#ifdef COM_TxIPduTimeOut
   Com_TxIpduConstPtrType TxIPduConstPtr;
#endif
   Com_TxIpduRamPtrType TxIpduRamPtr;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if( Com_Lok_DETCheck_Param( (PduId >= CfgSwcServiceCom_dNumIPduTx), COMServiceId_TriggerIpduSend) )
#endif

   {
        PduId = COM_GET_TX_IPDU_ID(PduId);

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);

#ifdef COM_TxIPduTimeOut

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);

#endif

   if(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)PduId))
        {

#ifdef COM_TP_IPDUTYPE
            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
#endif
            {

                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;
                sendIpduFlag_u16.isEventTrig = COM_SET;

                sendIpduFlag_u16.isModeChangd = COM_RESET;

#ifdef COM_TxIPduTimeOut

                sendIpduFlag_u16.isTimeoutReq = (0u != TxIPduConstPtr->Timeout_Fact)? COM_SET : COM_RESET;

#endif

                sendIpduFlag_u16.ignoreRepetitions = COM_SET;

                Com_Lok_SendIpdu((Type_SwcServiceCom_tIdPdu) PduId, sendIpduFlag_u16);
            }

        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

