

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_TxIPduStop(Com_IpduIdType IpduId)
{
   Com_TxIpduRamPtrType        TxIpduRamPtr;
#ifdef COM_ERRORNOTIFICATION
   Com_TxIpduConstPtrType      TxIpduConstPtr;

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);
#endif

    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(IpduId);

#ifdef COM_ERRORNOTIFICATION

   if(   (Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) == COM_START)
        || (TxIpduRamPtr->Com_n != COM_ZERO)
#ifdef COM_TP_IPDUTYPE
        || (Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
#endif
       )

   {

        if((Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) == COM_FALSE) &&
            (TxIpduConstPtr->NotificationError_Cbk != NULL_PTR))
        {
            TxIpduConstPtr->NotificationError_Cbk();
        }
   }
#endif

#ifdef COM_TxIPduTimeOut

   Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);
#endif

#if(COM_RETRY_FAILED_TX_REQUESTS == STD_ON)

   Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

   Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxIPduTimeOut
    TxIpduRamPtr->Com_TickTxTimeout = COM_ZERO;
#endif

    TxIpduRamPtr->Com_n = COM_ZERO;
   Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
    TxIpduRamPtr->Com_MinDelayTick = COM_ZERO;

#ifdef COM_TP_IPDUTYPE

   Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

