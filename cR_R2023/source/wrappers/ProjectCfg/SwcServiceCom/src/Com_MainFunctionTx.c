

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"
#if defined(COM_CANCELTRANSMITSUPPORT) && defined(COM_TP_IPDUTYPE)
#include "PduR_Com.h"

#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#ifdef COM_TxIPduTimeOut
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_IPduTimeOut (VAR(uint16_least, AUTOMATIC) TxPduId);
#endif

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_Modes       (VAR(uint16_least, AUTOMATIC) TxPduId);

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_DirectMode  (VAR(uint16_least, AUTOMATIC) TxPduId);

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_MixedMode   (VAR(uint16_least, AUTOMATIC) TxPduId);

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_NoneMode    (VAR(uint16_least, AUTOMATIC) TxPduId);

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_PeriodicMode(VAR(uint16_least, AUTOMATIC) TxPduId);

LOCAL_INLINE FUNC(void, COM_CODE)    Com_Lok_MainFunctionTx_SendIPdu    (VAR(uint16_least, AUTOMATIC) TxPduId,
                                                                         VAR(boolean, AUTOMATIC) SendIPdu);

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void, COM_CODE) Com_InternalMainFunctionTx( VAR(Com_MainFuncType,AUTOMATIC) TxMainFuncId )
{
#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)

    Com_TxIpduConstPtrType                  TxIPduConstPtr;

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
#endif
    VAR(uint16_least, AUTOMATIC)            Idx_Pdu_ui;
    VAR(Com_IpduIdType,AUTOMATIC)           StartIPduId;
    VAR(Com_IpduIdType,AUTOMATIC)           EndIPduId;
    VAR(boolean, AUTOMATIC)                 SendIPdu;

#ifdef COM_TxIPduTimeOut
    VAR(boolean, AUTOMATIC)                 Timeout_Flag;
#endif

#ifdef COM_TxIPduNotification
    VAR(boolean, AUTOMATIC)                 Notify_Flag;
#endif

#ifdef COM_TxIPduTimeOut

    Timeout_Flag = COM_FALSE;
#endif

#ifdef COM_TxIPduNotification

    Notify_Flag = COM_FALSE;
#endif

    if (
#if(COM_CONFIGURATION_USE_DET == STD_ON)
        Com_Lok_DETCheck_Void(COMServiceId_MainFunctionTx)
#else
        (Com_Uninit_Flag == COM_INIT)
#endif
        )
    {

        StartIPduId = COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)TxMainFuncId).StartIPduId;
        EndIPduId   = StartIPduId + COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)TxMainFuncId).NumOfIpdus;

#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(StartIPduId);
        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(StartIPduId);
#endif

        for ( Idx_Pdu_ui = StartIPduId; Idx_Pdu_ui < EndIPduId; Idx_Pdu_ui++ )
        {

            if(Com_CheckTxIPduStatus((PduIdType)Idx_Pdu_ui))
            {
                SchM_Enter_Com_TxIpduProtArea(MAINFUNCTIONTX);

#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)

                if (Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
                {
                    Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#ifdef COM_TxIPduNotification
                    Notify_Flag = (Com_GetValue(TXIPDU,_SIGPROC,TxIPduConstPtr->txIPduFields) == COM_DEFERRED);
#endif
                }

#ifdef COM_TxIPduTimeOut
                else
                {
                    Timeout_Flag = Com_Lok_MainFunctionTx_IPduTimeOut(Idx_Pdu_ui);
                }
#endif

#endif

                SendIPdu = Com_Lok_MainFunctionTx_Modes(Idx_Pdu_ui);

                SchM_Exit_Com_TxIpduProtArea(MAINFUNCTIONTX);

#ifdef COM_TxIPduTimeOutNotify

                if(Timeout_Flag == COM_TRUE)
                {

                    if(TxIPduConstPtr->TimeOutNotification_Cbk != NULL_PTR)
                    {
                        TxIPduConstPtr->TimeOutNotification_Cbk();
                    }
                }
#else
# ifdef COM_TxIPduTimeOut
                (void)Timeout_Flag;
# endif
#endif

#ifdef COM_TxIPduNotification

                if(Notify_Flag == COM_TRUE)
                {

                    if(TxIPduConstPtr->Notification_Cbk != NULL_PTR)
                    {
                        TxIPduConstPtr->Notification_Cbk();
                    }
                }
#endif

            Com_Lok_MainFunctionTx_SendIPdu(Idx_Pdu_ui, SendIPdu);
            }
#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
            TxIPduConstPtr++ ;
            TxIpduRamPtr++;
#endif
        }
    }
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxIPduTimeOut

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_IPduTimeOut(VAR(uint16_least, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
#ifdef COM_CANCELTRANSMITSUPPORT

    Com_TxIpduConstPtrType                  TxIPduConstPtr;
    VAR( boolean, AUTOMATIC )               isCancelTransmitSupported;
#endif
    VAR(boolean, AUTOMATIC)                 Timeout_Flag;

    Timeout_Flag = COM_FALSE;

#ifdef COM_CANCELTRANSMITSUPPORT
    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);
#endif
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if((Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
       &&
       (Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) == COM_START))
    {

        if (TxIpduRamPtr->Com_TickTxTimeout != 0)
        {
            --TxIpduRamPtr->Com_TickTxTimeout;
        }
        if(TxIpduRamPtr->Com_TickTxTimeout == 0)
        {
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

#ifdef COM_RETRY_FAILED_TX_REQUESTS

            Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

            TxIpduRamPtr->Com_n = 0;

            TxIpduRamPtr->Com_MinDelayTick = 0;

            Timeout_Flag = COM_TRUE;

#if defined(COM_CANCELTRANSMITSUPPORT) && defined(COM_TP_IPDUTYPE)
            {
                isCancelTransmitSupported = Com_GetValue(TXIPDU,_ISCANCELTRANSMITSUPPORTED,TxIPduConstPtr->txIPduFields);

                if((Com_GetValue(TXIPDU,_ISLARGEDATAPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE)
                   &&
                   (isCancelTransmitSupported != COM_FALSE)
                   &&

                   (Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
                   )
                {

                    ( void )PduR_ComCancelTransmit(TxIPduConstPtr->PdurId);
                }
            }
#endif
        }
    }
    return Timeout_Flag;
}

#endif

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_Modes(VAR(uint16_least, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
    VAR(boolean, AUTOMATIC)                 SendIPdu;

    SendIPdu = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_MinDelayTick != 0)
    {

        --TxIpduRamPtr->Com_MinDelayTick;
    }

    switch(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode))
    {
    case COM_TXMODE_DIRECT:
        SendIPdu = Com_Lok_MainFunctionTx_DirectMode(TxPduId);
        break;

    case COM_TXMODE_MIXED:
        SendIPdu = Com_Lok_MainFunctionTx_MixedMode(TxPduId);
        break;

    case COM_TXMODE_NONE:
        SendIPdu = Com_Lok_MainFunctionTx_NoneMode(TxPduId);
        break;

    case COM_TXMODE_PERIODIC:
        SendIPdu = Com_Lok_MainFunctionTx_PeriodicMode(TxPduId);
        break;

    default:

        break;
    }
    return SendIPdu;
}

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_DirectMode(VAR(uint16_least, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
    VAR(boolean, AUTOMATIC)                 SendIPdu;

    SendIPdu = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_n_Tick_Tx != 0)
    {
        --TxIpduRamPtr->Com_n_Tick_Tx;
    }
    if(TxIpduRamPtr->Com_MinDelayTick == 0)

    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
        else
        {
#ifdef COM_TXPDU_DEFERREDPROCESSING

            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) &&
                                    (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE))
            {

                SendIPdu = COM_TRUE;
            }
            else
#endif
            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (TxIpduRamPtr->Com_n != 0))
            {
                SendIPdu = COM_TRUE;

            }
            else
            {

            }
        }
        if (TxIpduRamPtr->Com_n != 0)
        {
            if (TxIpduRamPtr->Com_n_Tick_Tx == 0)
            {
                TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;
            }
        }
    }
    return SendIPdu;
}

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_MixedMode( VAR(uint16_least, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
    VAR(boolean, AUTOMATIC)                 SendIPdu;

    SendIPdu = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_Tick_Tx != 0)
    {
        --TxIpduRamPtr->Com_Tick_Tx;
    }
    if (TxIpduRamPtr->Com_n_Tick_Tx != 0)
    {
        --TxIpduRamPtr ->Com_n_Tick_Tx;
    }
    if(TxIpduRamPtr->Com_MinDelayTick == 0)
    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
        else
        {
#ifdef COM_TXPDU_DEFERREDPROCESSING

            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) &&
                            (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE))
            {

                SendIPdu = COM_TRUE;
            }
            else
#endif

            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (TxIpduRamPtr->Com_n != 0))
            {
                SendIPdu = COM_TRUE;

            }
            else
            {
                if((TxIpduRamPtr->Com_Tick_Tx == 0)&&(TxIpduRamPtr->Com_n == 0))
                {
                    SendIPdu = COM_TRUE;

                }
            }
        }
        if ((TxIpduRamPtr->Com_n != 0) && (TxIpduRamPtr->Com_n_Tick_Tx == 0))
        {
            TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;
        }
    }
    else
    {
        if((TxIpduRamPtr->Com_Tick_Tx == 0) && (TxIpduRamPtr->Com_n == 0))
        {

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
        }
    }
    if(TxIpduRamPtr->Com_Tick_Tx == 0)
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxPduId, (TxIpduRamPtr->CurrentTxModePtr));
    }
    return SendIPdu;
}

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_NoneMode(  VAR(uint16_least, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
    VAR(boolean, AUTOMATIC)                 SendIPdu;

    SendIPdu = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if(TxIpduRamPtr->Com_MinDelayTick == 0)
    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
        else
        {
#ifdef COM_TXPDU_DEFERREDPROCESSING

            if(Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
            {
                if(TxIpduRamPtr->Com_n_Tick_Tx != 0)
                {
                    TxIpduRamPtr->Com_n_Tick_Tx--;
                }
                if(TxIpduRamPtr->Com_n_Tick_Tx == 0)
                {

                    SendIPdu = COM_TRUE;
                }
            }
#endif
        }
    }
    return SendIPdu;
}

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_MainFunctionTx_PeriodicMode(  VAR(uint16_least, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
    VAR(boolean, AUTOMATIC)                 SendIPdu;

    SendIPdu = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_Tick_Tx != 0)
    {
        --TxIpduRamPtr->Com_Tick_Tx;
    }
    if(TxIpduRamPtr->Com_MinDelayTick == 0 )
    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }

        else
        {
            if(TxIpduRamPtr->Com_Tick_Tx == 0)
            {
                SendIPdu = COM_TRUE;

            }
#ifdef COM_TXPDU_DEFERREDPROCESSING

            else if(Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
            {
                if (TxIpduRamPtr->Com_n_Tick_Tx != 0)
                {
                    TxIpduRamPtr->Com_n_Tick_Tx--;
                }
                if(TxIpduRamPtr->Com_n_Tick_Tx == 0)
                {

                    SendIPdu = COM_TRUE;
                }
            }
            else
            {

            }
#endif
        }
    }
    else
    {
        if(TxIpduRamPtr->Com_Tick_Tx == 0)
        {

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
        }
    }

    if(TxIpduRamPtr->Com_Tick_Tx == 0)
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxPduId, (TxIpduRamPtr->CurrentTxModePtr));
    }
    return SendIPdu;
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_MainFunctionTx_SendIPdu(  VAR(uint16_least, AUTOMATIC) TxPduId,
                                                                    VAR(boolean, AUTOMATIC) SendIPdu)
{

    Com_TxIpduRamPtrType                    TxIpduRamPtr;
#ifdef COM_TxIPduTimeOut

    Com_TxIpduConstPtrType                  TxIPduConstPtr;
    VAR(uint8, AUTOMATIC)                   LatestTransMode_u8;

    TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(TxPduId);
#endif
    TxIpduRamPtr    = &COM_GET_TXPDURAM_S(TxPduId);

    if ( ( SendIPdu == COM_TRUE )
#ifdef COM_RETRY_FAILED_TX_REQUESTS
       || ( Com_GetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags) != COM_FALSE )
#endif
     )
    {

        Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

        sendIpduFlag_u16.isEventTrig      =  COM_RESET;
#ifdef COM_TxIPduTimeOut
        LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);

        if(((LatestTransMode_u8 & COM_TXMODE_MIXED) > (uint8)0) && (TxIPduConstPtr->Timeout_Fact != 0u ))
        {
            sendIpduFlag_u16.isTimeoutReq = COM_SET;
        }
#endif

#ifdef COM_TP_IPDUTYPE
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
#endif
        {
            Com_Lok_SendIpdu((PduIdType)TxPduId,sendIpduFlag_u16);
        }
    }
}

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean, COM_CODE) Com_IsTxScheduled( VAR(PduIdType, AUTOMATIC) ComTxPduId,
                                           VAR(uint16, AUTOMATIC)    ComCallerTaskCycle)
{
    Com_TxIpduRamPtrType                TxIpduRamPtr;
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    VAR(uint16, AUTOMATIC)              ticksinMs_u16;
    VAR(Com_TimeBaseType, AUTOMATIC)    timeBaseInMs;
#endif
    VAR(boolean, AUTOMATIC)             IsTxScheduled;

    ComTxPduId   = COM_GET_TX_IPDU_ID(ComTxPduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);

#ifndef COM_TXSCHEDULED_DIFF_TIMEBASE
    (void)ComCallerTaskCycle;
#endif

#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE

    timeBaseInMs  = COM_GET_MAINFUNCTION_CFG( COM_NUM_OF_RX_MAINFUNCTION + (COM_GET_TX_IPDU_CONSTDATA(ComTxPduId))->MainFunctionRef ).TimeBaseInMs;

    ticksinMs_u16 = ((TxIpduRamPtr->Com_Tick_Tx) * timeBaseInMs);

#endif

#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE

    if (ComCallerTaskCycle < timeBaseInMs)
#endif
    {
        if((Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) == (uint8)COM_TXMODE_PERIODIC) &&
           (TxIpduRamPtr->Com_Tick_Tx > 1u) )
        {
            IsTxScheduled = COM_FALSE;
        }
        else
        {
            IsTxScheduled = COM_TRUE;
        }
    }
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    else
    {
        if((Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) == (uint8)COM_TXMODE_PERIODIC) &&
           (ticksinMs_u16 > ComCallerTaskCycle) )

        {
            IsTxScheduled = COM_FALSE;
        }
        else
        {
            IsTxScheduled = COM_TRUE;
        }
    }
#endif

    return IsTxScheduled;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_PROVIDE_IPDU_STATUS
#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(boolean,COM_CODE) Com_ProvideTxIpduStatus(VAR(PduIdType, AUTOMATIC) PduId)
{
    VAR(boolean, AUTOMATIC) pduStatus_b;

    if (PduId < COM_GET_NUM_TX_IPDU)
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        pduStatus_b = (Com_CheckTxIPduStatus((PduIdType)PduId));
    }
    else
    {
        pduStatus_b = COM_FALSE;
    }

    return(pduStatus_b);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

