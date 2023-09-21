#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)
LOCAL_INLINE FUNC(void, COM_CODE) Com_ProcessRxIPduNotification( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) RxPduId );
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_RxIndication(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) RxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{

   Com_RxIpduConstPtrType RxIPduConstPtr;
   Com_RxIpduRamPtrType   RxIPduRamPtr;
   VAR(uint8, AUTOMATIC)  ConstByteValue_u8;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param_Ptr((RxPduId >= CfgSwcServiceCom_dNumIPduRx), (PduInfoPtr == NULL_PTR)
   ,     COMServiceId_RxIndication))
#endif
   {

        RxPduId             = COM_GET_RX_IPDU_ID(RxPduId);

        RxIPduConstPtr      = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

        RxIPduRamPtr        = &COM_GET_RXPDURAM_S(RxPduId);
        ConstByteValue_u8   = RxIPduConstPtr->rxIPduFields;

        if(Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)RxPduId))
        {
            VAR(boolean, AUTOMATIC) IPduSigProcessing_b;

            IPduSigProcessing_b = Com_GetValue(RXIPDU,_SIGPROC,ConstByteValue_u8);

            SchM_Enter_Com_RxPduBuffer();

            RxIPduRamPtr->RxIPduLength = ((PduInfoPtr->SduLength <= RxIPduConstPtr->Size) ?
                                           (PduInfoPtr->SduLength) : (RxIPduConstPtr->Size));

            Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr ->RxFlags,COM_TRUE);
            SchM_Exit_Com_RxPduBuffer();

            if(COM_IMMEDIATE == IPduSigProcessing_b)
            {
                Com_ProcessRxIPdu(RxPduId,PduInfoPtr);
            }
#ifdef COM_RxIPduDeferredProcessing
            else{
               SchM_Enter_Com_RxPduBuffer();

               Com_ByteCopy(RxIPduConstPtr->BuffPtr,(uint8*)(PduInfoPtr ->SduDataPtr),RxIPduRamPtr->RxIPduLength);
               SchM_Exit_Com_RxPduBuffer();
           }
#endif
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_ProcessRxIPdu(
                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)                       RxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  PduInfoPtr
                                      )
{
   Com_RxIpduConstPtrType   RxIPduConstPtr;
#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
   VAR(boolean, AUTOMATIC)  isGwRxIpdu;
#endif
#ifdef COM_RxIPduCallOuts
   VAR(boolean, AUTOMATIC)  rxIpduCalloutStatus;
#endif

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxIPduCallOuts

   if(RxIPduConstPtr->CallOut != NULL_PTR)
   {
        rxIpduCalloutStatus = RxIPduConstPtr->CallOut(RxPduId, PduInfoPtr);
   }
   else{

        rxIpduCalloutStatus = COM_TRUE;
   }

   if(COM_TRUE == rxIpduCalloutStatus)
#endif
   {
#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)

        isGwRxIpdu = Com_GetValue(RXIPDU,_ISGWPDU,RxIPduConstPtr->rxIPduFields);

        if(isGwRxIpdu)
        {
            COM_GET_IS_GWSIG_UPDATED(RxPduId) = COM_FALSE;
        }
#endif

        if(RxIPduConstPtr->No_Of_Sig_Ref > 0u)
        {
            Com_Lok_ProcessSignal(RxPduId, PduInfoPtr);
        }

#ifdef COM_RX_SIGNALGROUP

        if(RxIPduConstPtr->No_Of_SigGrp_Ref > 0u)
        {
            Com_Lok_ProcessSignalGroup(RxPduId, PduInfoPtr);
        }
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

        if((isGwRxIpdu) && (COM_GET_IS_GWSIG_UPDATED(RxPduId)))
        {
            if(Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(RxPduId).RxFlags) != COM_TRUE)
            {
                SchM_Enter_Com_RxSigGwQueueProtArea();

                (void)Com_WriteSigGwReceiveQueue(RxPduId);

                Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(RxPduId).RxFlags,COM_TRUE);
                SchM_Exit_Com_RxSigGwQueueProtArea();
            }
        }
#endif

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)

        Com_ProcessRxIPduNotification( RxPduId );
#endif
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)

LOCAL_INLINE FUNC(void, COM_CODE) Com_ProcessRxIPduNotification( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) RxPduId )
{
   Com_RxIpduConstPtrType          RxIPduConstPtr;
#ifdef COM_RxSignalNotify
   Com_RxSigConstPtrType           RxSigConstPtr;
   Com_RxSigRamPtrType             RxSigRamPtr;
#endif
#ifdef COM_RxSignalGrpNotify
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
#endif
#if defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)
   VAR(uint16_least, AUTOMATIC)    SigOrSigGrpId;
#endif

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxIPduNotification

   if(RxIPduConstPtr->RxNotification_Cbk != NULL_PTR)
   {
        RxIPduConstPtr->RxNotification_Cbk();
   }
#endif

#if defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)

   if(Com_GetValue(RXIPDU,_NOTIFCBK,RxIPduConstPtr->rxIPduFields))
   {
#ifdef COM_RxSignalNotify

        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);
        RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);

        for(SigOrSigGrpId = (uint16_least)RxIPduConstPtr->No_Of_Sig_Ref; SigOrSigGrpId != 0u; SigOrSigGrpId--)
        {
            if(RxSigConstPtr->Notification_Cbk != NULL_PTR)
            {
                if(Com_GetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields))
                {
                    RxSigConstPtr->Notification_Cbk();
                    Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,COM_FALSE);
                }
            }
            RxSigConstPtr++;
            RxSigRamPtr++;
        }
#endif

#ifdef COM_RxSignalGrpNotify

        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);
        RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);

        for(SigOrSigGrpId = (uint16_least)RxIPduConstPtr->No_Of_SigGrp_Ref; SigOrSigGrpId != 0u; SigOrSigGrpId--)
        {
            if(RxSigGrpConstPtr->Notification_Cbk != NULL_PTR)
            {
                if(Com_GetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields))
                {
                    RxSigGrpConstPtr->Notification_Cbk();
                    Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_FALSE);
                }
            }
            RxSigGrpConstPtr++;
            RxSigGrpRamPtr++;
        }
#endif

   }

#endif
}
#endif

#ifdef COM_ENABLE_READRXIPDULENGTH
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_ReadRxIPduLength(
                                VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)                     RxPduId
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC,COM_APPL_DATA) RxIPduLengthPtr
                                           )
{
   VAR(uint8,AUTOMATIC)  Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr( (RxPduId >= CfgSwcServiceCom_dNumIPduRx), (RxIPduLengthPtr == NULL_PTR)
   ,     COMServiceId_ReadRxIPduLength ))
#endif
   {
        VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC)  RxIPduLength;

        RxPduId       = COM_GET_RX_IPDU_ID(RxPduId);
        RxIPduLength  = 0u;

        if(Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)RxPduId))
        {
            RxIPduLength = COM_GET_RXPDURAM_S(RxPduId).RxIPduLength;
            Status       = E_OK;
        }
        else{

        }

        *RxIPduLengthPtr = RxIPduLength;
   }

    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

