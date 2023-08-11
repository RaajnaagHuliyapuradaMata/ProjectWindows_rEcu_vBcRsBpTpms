

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_RX_IPDUCOUNTER
LOCAL_INLINE boolean Com_ProcessRxIPduCounter(PduIdType RxPduId, const PduInfoType * PduInfoPtr);
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_RxIndication(PduIdType RxPduId, const PduInfoType * PduInfoPtr)
{
    Com_RxIpduConstPtrType      RxIpduConstPtr;
    Com_RxIpduRamPtrType        RxIpduRamPtr;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

    if(Com_Lok_DETCheck_Param_Ptr((RxPduId >= COM_GET_NUM_RX_IPDU),(PduInfoPtr == NULL_PTR),COMServiceId_RxIndication))
#endif
    {

        RxPduId             = COM_GET_RX_IPDU_ID(RxPduId);

        RxIpduConstPtr      = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
        RxIpduRamPtr        = &COM_GET_RXPDURAM_S(RxPduId);

        if(Com_CheckRxIPduStatus(RxPduId))
        {
            boolean sigProcessing_b;

            sigProcessing_b = Com_GetValue(RXIPDU,_SIGPROC,RxIpduConstPtr->rxIPduFields);

            Com_Get_SchM_Enter_Com_RxIndication
            Com_Get_SchM_Enter_Com_RxPduBuffer

            RxIpduRamPtr->RxIPduLength = ((PduInfoPtr->SduLength > RxIpduConstPtr->Size) ?
                                          (RxIpduConstPtr->Size) : (PduInfoPtr->SduLength));

#if defined (COM_RxIPduDeferredProcessing) || defined (COM_COPY_IMMEDIATE_RXIPDU)
#ifndef COM_COPY_IMMEDIATE_RXIPDU
            if (COM_DEFERRED == sigProcessing_b)
#endif
            {

                Com_ByteCopy(RxIpduConstPtr->BuffPtr, (uint8*)(PduInfoPtr->SduDataPtr), RxIpduRamPtr->RxIPduLength);
            }
#endif

#ifdef COM_RX_MAINFUNCTION_PROC
            Com_SetRamValue(RXIPDU,_INDICATION, RxIpduRamPtr->RxFlags, COM_TRUE);
#endif

            Com_Get_SchM_Exit_Com_RxPduBuffer
            Com_Get_SchM_Exit_Com_RxIndication

            if (COM_IMMEDIATE == sigProcessing_b)
            {
#if defined(COM_RxIPduCallOuts) || defined(COM_RX_IPDUCOUNTER)

                if (Com_IsValidRxIpdu(RxPduId, PduInfoPtr))
#endif
                {
                    Com_ProcessRxIPdu(RxPduId, PduInfoPtr);
                }
            }
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_ProcessRxIPdu(PduIdType RxPduId, const PduInfoType * PduInfoPtr)
{
    Com_RxIpduConstPtrType      RxIpduConstPtr;
#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
    Com_RxIpduRamPtrType        RxIpduRamPtr;
    boolean                     isGwRxIpdu;
#endif

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
    RxIpduRamPtr   = &COM_GET_RXPDURAM_S(RxPduId);

    isGwRxIpdu = Com_GetValue(RXIPDU,_ISGWPDU,RxIpduConstPtr->rxIPduFields);

    if (isGwRxIpdu)
    {
        COM_GET_IS_GWSIG_UPDATED(RxPduId) = COM_FALSE;
    }
#endif

    Com_Get_SchM_Enter_Com_RxIndication

    if (RxIpduConstPtr->No_Of_Sig_Ref > COM_ZERO)
    {
        Com_Lok_ProcessSignal(RxPduId, PduInfoPtr);
    }

#ifdef COM_RX_SIGNALGROUP

    if (RxIpduConstPtr->No_Of_SigGrp_Ref > COM_ZERO)
    {
        Com_Lok_ProcessSignalGroup(RxPduId, PduInfoPtr);
    }
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

    if ((isGwRxIpdu) && (COM_GET_IS_GWSIG_UPDATED(RxPduId)))
    {

        Com_Get_SchM_Enter_Com_RxPduBuffer

        if (Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags) != COM_TRUE)
        {

            (void)Com_WriteSigGwReceiveQueue(RxPduId);

            Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags,COM_TRUE);
        }
        Com_Get_SchM_Exit_Com_RxPduBuffer
    }
#endif

    Com_Get_SchM_Exit_Com_RxIndication

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)

    Com_InvokeRxNotifications( RxPduId );

#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if defined(COM_RxIPduCallOuts) || defined(COM_RX_IPDUCOUNTER)

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_IsValidRxIpdu(PduIdType PduId, const PduInfoType * PduInfoPtr)
{
    Com_RxIpduConstPtrType  RxIpduConstPtr;
    boolean                 isValidRxIpdu;

    isValidRxIpdu   = COM_TRUE;

    RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(PduId);

#ifdef COM_RX_IPDUCOUNTER

    if (RxIpduConstPtr->RxIpduCntr_Index != COM_RXIPDU_CNTR_INV_IDX)
    {

        isValidRxIpdu = Com_ProcessRxIPduCounter(PduId, PduInfoPtr);
    }
    else
    {

    }

#endif

#ifdef COM_RxIPduCallOuts

    if (
# ifdef COM_RX_IPDUCOUNTER
            (isValidRxIpdu) &&
# endif
            (RxIpduConstPtr->CallOut != NULL_PTR)
       )
    {
        isValidRxIpdu = RxIpduConstPtr->CallOut(PduId, PduInfoPtr);
    }
    else
    {

    }

#endif

    return isValidRxIpdu;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_RX_IPDUCOUNTER

LOCAL_INLINE boolean Com_ProcessRxIPduCounter(PduIdType RxPduId, const PduInfoType * PduInfoPtr)
{
    Com_RxIpduConstPtrType          RxIpduConstPtr;
    Com_RxIpduRamPtrType            RxIpduRamPtr;
    Com_RxIpduCntrConstPtrType      RxIpduCntrConstPtr;
    uint8 *                         counterBytePtr;
    PduLengthType                   counterByteNo_uo;
    uint16                          counterMaxValue_u16;
    uint8                           rxCounterValue_u8;
    uint8                           counterMinExpValue_u8;
    uint8                           counterMaxExpValue_u8;
    boolean                         counterStatus_b;

    counterStatus_b    = COM_ACCEPT;

    RxIpduConstPtr     = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    RxIpduCntrConstPtr = COM_GET_RX_IPDU_CNTR_CONSTDATA(RxIpduConstPtr->RxIpduCntr_Index);

    counterByteNo_uo   = (PduLengthType)(RxIpduCntrConstPtr->CntrBitPos / 8u);

    if (counterByteNo_uo < PduInfoPtr->SduLength)
    {
        RxIpduRamPtr      = &COM_GET_RXPDURAM_S(RxPduId);

        counterBytePtr    = (uint8 *)(PduInfoPtr->SduDataPtr + counterByteNo_uo);

        rxCounterValue_u8 = COM_UNPACK_CNTR_FROM_IPDU_BUFF(
                                                    (*counterBytePtr),
                                             (uint8)(RxIpduCntrConstPtr->CntrBitPos % 8u),
                                                     RxIpduCntrConstPtr->CntrBitSize
                                                          );

        if (!(Com_GetRamValue(RXIPDU,_IS_FIRST_RECEPTION,RxIpduRamPtr->RxFlags)))
        {

            counterMaxValue_u16   = (uint16)COM_GET_BASE_2_POWER_X(RxIpduCntrConstPtr->CntrBitSize);

            counterMinExpValue_u8 = COM_GET_CNTR_WRAP_AROUND_VALUE(
                 ((uint16)COM_GET_RXIPDU_LAST_CNTR_VAL(RxIpduConstPtr->RxIpduCntr_Index) + COM_ONE), counterMaxValue_u16
                                                                  );
            counterMaxExpValue_u8 = COM_GET_CNTR_WRAP_AROUND_VALUE(
                 ((uint16)counterMinExpValue_u8 + (uint16)RxIpduCntrConstPtr->CntrThreshold), counterMaxValue_u16
                                                                  );

            if (counterMinExpValue_u8 <= counterMaxExpValue_u8)
            {

                if (!((rxCounterValue_u8 < counterMinExpValue_u8) || (rxCounterValue_u8 > counterMaxExpValue_u8)))
                {

                }
                else
                {

                    counterStatus_b = COM_REJECT;
                }
            }

            else if (!((rxCounterValue_u8 < counterMinExpValue_u8) && (rxCounterValue_u8 > counterMaxExpValue_u8)))
            {

            }
            else
            {

                counterStatus_b = COM_REJECT;
            }

            if ((rxCounterValue_u8 != counterMinExpValue_u8) && (RxIpduCntrConstPtr->CntrErrNotif_Cbk != NULL_PTR))
            {
                RxIpduCntrConstPtr->CntrErrNotif_Cbk(RxPduId, counterMinExpValue_u8, rxCounterValue_u8);
            }
            else
            {

            }
        }
        else
        {

            Com_SetRamValue(RXIPDU,_IS_FIRST_RECEPTION,RxIpduRamPtr->RxFlags,COM_FALSE);
        }

        COM_GET_RXIPDU_LAST_CNTR_VAL(RxIpduConstPtr->RxIpduCntr_Index) = rxCounterValue_u8;
    }
    else
    {

    }

    return counterStatus_b;
}

#endif

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

void Com_InvokeRxNotifications(PduIdType RxPduId)
{
    Com_RxIpduConstPtrType          RxIpduConstPtr;
#ifdef COM_RxSignalNotify
    Com_RxSigConstPtrType           RxSigConstPtr;
    Com_RxSigRamPtrType             RxSigRamPtr;
#endif
#ifdef COM_RxSignalGrpNotify
    Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
    Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
#endif
#if defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)
    uint16_least                    index_u16;
#endif

    RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#ifdef COM_RxIPduNotification

    if (RxIpduConstPtr->RxNotification_Cbk != NULL_PTR)
    {
        RxIpduConstPtr->RxNotification_Cbk();
    }
#endif

#if defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)

    if (Com_GetValue(RXIPDU,_NOTIFCBK,RxIpduConstPtr->rxIPduFields))
    {

#ifdef COM_RxSignalNotify

        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIpduConstPtr->RxSigId_Index);
        RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIpduConstPtr->RxSigId_Index);

        for (index_u16 = RxIpduConstPtr->No_Of_Sig_Ref; index_u16 != COM_ZERO; index_u16--)
        {
            if (RxSigConstPtr->Notification_Cbk != NULL_PTR)
            {
                if (Com_GetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields))
                {
                    Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,COM_FALSE);
                    RxSigConstPtr->Notification_Cbk();
                }
            }
            RxSigConstPtr++;
            RxSigRamPtr++;
        }
#endif

#ifdef COM_RxSignalGrpNotify

        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIpduConstPtr->FirstRxSigGrp_Index);
        RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(RxIpduConstPtr->FirstRxSigGrp_Index);

        for (index_u16 = RxIpduConstPtr->No_Of_SigGrp_Ref; index_u16 != COM_ZERO; index_u16--)
        {
            if (RxSigGrpConstPtr->Notification_Cbk != NULL_PTR)
            {
                if (Com_GetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields))
                {
                    Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_FALSE);
                    RxSigGrpConstPtr->Notification_Cbk();
                }
            }
            RxSigGrpConstPtr++;
            RxSigGrpRamPtr++;
        }
#endif

    }

#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

#ifdef COM_ENABLE_READRXIPDULENGTH
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
uint8 Com_ReadRxIPduLength(PduIdType RxPduId, PduLengthType * RxIPduLengthPtr)
{
    uint8       Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if (Com_Lok_DETCheck_Param_Ptr( (RxPduId >= COM_GET_NUM_RX_IPDU), (RxIPduLengthPtr == NULL_PTR),
                                     COMServiceId_ReadRxIPduLength ))
#endif
    {

        RxPduId  = COM_GET_RX_IPDU_ID(RxPduId);

        if(Com_CheckRxIPduStatus(RxPduId))
        {
            *RxIPduLengthPtr = COM_GET_RXPDURAM_S(RxPduId).RxIPduLength;
            Status           = E_OK;
        }
        else
        {

            *RxIPduLengthPtr = COM_ZERO;
        }
    }

    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

