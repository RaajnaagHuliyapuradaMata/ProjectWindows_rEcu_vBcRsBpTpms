#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_TxIPduStop( VAR(Type_CfgSwcServiceCom_tIdIPdu, AUTOMATIC) IpduId )
{
   Com_TxIpduRamPtrType        TxIpduRamPtr;
#ifdef COM_ERRORNOTIFICATION
   Com_TxIpduConstPtrType      TxIPduConstPtr;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
#endif

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);

#ifdef COM_ERRORNOTIFICATION

   if((Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) == COM_START) || (TxIpduRamPtr->Com_n != 0))
   {
        if((Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) == COM_FALSE) &&
            (TxIPduConstPtr->NotificationError_Cbk != NULL_PTR))
        {
            TxIPduConstPtr->NotificationError_Cbk();
        }
   }
#endif

   Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

#ifdef COM_RETRY_FAILED_TX_REQUESTS

   Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

   Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxIPduTimeOut
    TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif

    TxIpduRamPtr->Com_n = 0;
   Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
    TxIpduRamPtr->Com_MinDelayTick = 0;

   Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

