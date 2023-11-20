#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_TxConfirmation(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) TxPduId)
{

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((TxPduId >= CfgSwcServiceCom_dNumIPduTx), COMServiceId_TxConfirmation))
#endif
   {

        TxPduId = COM_GET_TX_IPDU_ID(TxPduId);

        if(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)TxPduId))
        {

            Com_InternalProcessTxConfirmation(TxPduId);
        }

   }
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_InternalProcessTxConfirmation(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) TxPduId)
{

   Com_TxIpduRamPtrType TxIpduRamPtr;
   Com_TxIpduConstPtrType TxIPduConstPtr;
   VAR(uint16, AUTOMATIC) ConstByteValue_u16;
#ifdef COM_TxIPduNotification
   VAR(boolean, AUTOMATIC) notifyFlag_b;

    notifyFlag_b = COM_FALSE;
#endif

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
   ConstByteValue_u16 = TxIPduConstPtr->txIPduFields;

    SchM_Enter_Com_TxIpduProtArea(TXCONFIRMATION);

   if((TxIPduConstPtr->Min_Delay_Time_Fact != 0) && (TxIpduRamPtr ->Com_MinDelayTick != 0))
   {

        TxIpduRamPtr ->Com_MinDelayTick = (TxIPduConstPtr->Min_Delay_Time_Fact) +
                                          (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) ? 1u : 0u);
   }

   if(TxIpduRamPtr->Com_n != 0)
   {
        --TxIpduRamPtr->Com_n;
   }
   if(TxIpduRamPtr->Com_n == 0)
   {

        Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

#ifdef COM_TxIPduTimeOut

        if(Com_GetValue(TXIPDU,_NONETOSTATUS,ConstByteValue_u16) != COM_FALSE)
        {

            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
        }
        else
#endif
        {

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);
        }

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u16) == (uint16)COM_CLRUPDATEBIT_CONFIRMATION)
        {
            Com_Lok_ClearUpdateBits(TxIPduConstPtr);
        }
#endif
#ifdef COM_TxIPduNotification
        notifyFlag_b = (Com_GetValue(TXIPDU,_SIGPROC,ConstByteValue_u16) == COM_IMMEDIATE);
#endif
   }
    SchM_Exit_Com_TxIpduProtArea(TXCONFIRMATION);

#ifdef COM_TxIPduNotification
   if((notifyFlag_b == COM_TRUE) && (TxIPduConstPtr->Notification_Cbk != NULL_PTR))
   {

        TxIPduConstPtr->Notification_Cbk();
   }
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

