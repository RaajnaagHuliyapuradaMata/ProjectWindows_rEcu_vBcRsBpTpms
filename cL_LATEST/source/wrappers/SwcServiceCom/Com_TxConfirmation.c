

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
#ifdef COM_ECUC_AR_RELEASE_AR45
void Com_TxConfirmation(Type_SwcServiceCom_tIdPdu TxPduId,Std_ReturnType result)
#else
void Com_TxConfirmation(Type_SwcServiceCom_tIdPdu TxPduId)
#endif
{

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((TxPduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TxConfirmation))
#endif
   {

        TxPduId = COM_GET_TX_IPDU_ID(TxPduId);

        if(Com_CheckTxIPduStatus(TxPduId))
        {
            Com_InternalTxConfirmation(TxPduId);
        }
   }
#ifdef COM_ECUC_AR_RELEASE_AR45
    (void)result;
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

void Com_InternalTxConfirmation(Type_SwcServiceCom_tIdPdu TxPduId)
{
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   Com_TxIpduConstPtrType      TxIpduConstPtr;

#if defined(COM_TxIPduTimeOut)  || defined(COM_TxIPduNotification) ||\
    defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)
   uint16 ConstByteValue_u16;
#endif

#ifdef COM_TxIPduNotification
   boolean     notifyFlag_b;

    notifyFlag_b = COM_FALSE;
#endif

    TxIpduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(TxPduId);
    TxIpduRamPtr        = &COM_GET_TXPDURAM_S(TxPduId);

#if defined(COM_TxIPduTimeOut)  || defined(COM_TxIPduNotification) ||\
    defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)
   ConstByteValue_u16  = TxIpduConstPtr->txIPduFields;
#endif

    SchM_Enter_Com_TxIpduProtArea(TXCONFIRMATION);

   if(TxIpduRamPtr->Com_MinDelayTick != COM_ZERO)
   {
#ifdef COM_TXPDU_DEFERREDPROCESSING

        TxIpduRamPtr->Com_MinDelayTick = TxIpduConstPtr->Min_Delay_Time_Fact;
#else

        TxIpduRamPtr->Com_MinDelayTick = TxIpduConstPtr->Min_Delay_Time_Fact +
                                   (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) ? COM_ONE : COM_ZERO);
#endif
   }

   if(TxIpduRamPtr->Com_n != COM_ZERO)
   {
        --TxIpduRamPtr->Com_n;
   }
   if(TxIpduRamPtr->Com_n == COM_ZERO)
   {
        Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

#ifdef COM_TxIPduTimeOut
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,ConstByteValue_u16))
        {

            TxIpduRamPtr->Com_TickTxTimeout = TxIpduConstPtr->Timeout_Fact;
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
        }
        else{

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);
        }
#endif

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u16) == (uint16)COM_CLRUPDATEBIT_CONFIRMATION)
        {
            Com_Lok_ClearUpdateBits(TxIpduConstPtr);
        }
#endif

#ifdef COM_TxIPduNotification

        notifyFlag_b = (Com_GetValue(TXIPDU,_SIGPROC,ConstByteValue_u16) == COM_IMMEDIATE);
#endif
   }
    SchM_Exit_Com_TxIpduProtArea(TXCONFIRMATION);

#ifdef COM_TxIPduNotification
   if((notifyFlag_b == COM_TRUE) && (TxIpduConstPtr->Notification_Cbk != NULL_PTR))
   {

        TxIpduConstPtr->Notification_Cbk();
   }
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

