

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#if defined(COM_CANCELTRANSMITSUPPORT) && defined(COM_TP_IPDUTYPE)
# include "PduR_Com.h"
#if(COM_ENABLE_INTER_MODULE_CHECKS)

# if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
# if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#  error "AUTOSAR minor version undefined or mismatched"
# endif
#endif
#endif

#ifdef COM_TxIPduTimeOut
LOCAL_INLINE boolean Com_Lok_MainFunctionTx_IPduTimeOut   (uint16_least TxPduId);
#endif

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_Modes         (uint16_least TxPduId);

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_DirectMode    (uint16_least TxPduId);

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_MixedMode     (uint16_least TxPduId);

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_NoneMode      (uint16_least TxPduId);

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_PeriodicMode  (uint16_least TxPduId);

LOCAL_INLINE void Com_Lok_MainFunctionTx_SendIPdu         (uint16_least TxPduId);

#if (COM_ENABLE_PERIODIC_FRAME_SYNC != STD_OFF)
LOCAL_INLINE void Com_Lok_MainFunctionTxModeProcessing  (uint16_least TxPduId);

LOCAL_INLINE void Com_Lok_MainFunctionTxReloadTimePeriod(uint16_least TxPduId);
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_InternalMainFunctionTx(Com_MainFuncType TxMainFuncId)
{

    if (Com_Uninit_Flag == COM_INIT)
    {
#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
        Com_TxIpduConstPtrType      TxIpduConstPtr;
#endif
        Com_TxIpduRamPtrType        TxIpduRamPtr;
        uint16_least                idx_TxIpduId_u16;
        uint16_least                numOfIpdus;
        boolean                     SendIPdu;

#ifdef COM_TxIPduTimeOut
        boolean                     Timeout_Flag;
#endif

#ifdef COM_TxIPduNotification
        boolean                     Notify_Flag;
#endif

#ifdef COM_TxIPduTimeOut
        Timeout_Flag = COM_FALSE;
#endif

#ifdef COM_TxIPduNotification
        Notify_Flag  = COM_FALSE;
#endif

        idx_TxIpduId_u16  = COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)TxMainFuncId).StartIPduId;
        numOfIpdus        = (idx_TxIpduId_u16 + COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (uint16)TxMainFuncId).NumOfIpdus);

#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
        TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(idx_TxIpduId_u16);
#endif
        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(idx_TxIpduId_u16);

        for ( ; idx_TxIpduId_u16 < numOfIpdus; idx_TxIpduId_u16++ )
        {

            if(Com_CheckTxIPduStatus((PduIdType)idx_TxIpduId_u16))
            {
                SchM_Enter_Com_TxIpduProtArea(MAINFUNCTIONTX);

                if (Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
                {
                    Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#ifdef COM_TxIPduNotification

                    Notify_Flag = (Com_GetValue(TXIPDU,_SIGPROC,TxIpduConstPtr->txIPduFields) == COM_DEFERRED);
#endif
                }
#ifdef COM_TxIPduTimeOut
                else
                {

                    Timeout_Flag = Com_Lok_MainFunctionTx_IPduTimeOut(idx_TxIpduId_u16);

# ifndef COM_TxIPduTimeOutNotify
                    (void)Timeout_Flag;
# endif

                }
#endif

                SendIPdu = Com_Lok_MainFunctionTx_Modes(idx_TxIpduId_u16);

                SchM_Exit_Com_TxIpduProtArea(MAINFUNCTIONTX);

#ifdef COM_TxIPduTimeOutNotify

                if(Timeout_Flag == COM_TRUE)
                {
                    Timeout_Flag = COM_FALSE;

                    if(TxIpduConstPtr->TimeOutNotification_Cbk != NULL_PTR)
                    {
                        TxIpduConstPtr->TimeOutNotification_Cbk();
                    }
                }
                else
#endif
#ifdef COM_TxIPduNotification

                if(Notify_Flag == COM_TRUE)
                {
                    Notify_Flag = COM_FALSE;

                    if(TxIpduConstPtr->Notification_Cbk != NULL_PTR)
                    {
                        TxIpduConstPtr->Notification_Cbk();
                    }
                }
                else
#endif
                {

                }

                if (SendIPdu == COM_TRUE)
                {
                    Com_Lok_MainFunctionTx_SendIPdu(idx_TxIpduId_u16);
                }

            }
#if (COM_ENABLE_PERIODIC_FRAME_SYNC != STD_OFF)
            else if (Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIpduRamPtr->Com_TxFlags))
            {
                Com_Lok_MainFunctionTxModeProcessing(idx_TxIpduId_u16);
            }
            else
            {

            }
#endif

#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
            TxIpduConstPtr++ ;
#endif
            TxIpduRamPtr++;
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxIPduTimeOut

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_IPduTimeOut(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
#if defined(COM_CANCELTRANSMITSUPPORT) && defined(COM_TP_IPDUTYPE)

    Com_TxIpduConstPtrType      TxIpduConstPtr;
    boolean                     isCancelTransmitSupported;
#endif
    boolean                     Timeout_Flag;

    Timeout_Flag = COM_FALSE;

#if defined(COM_CANCELTRANSMITSUPPORT) && defined(COM_TP_IPDUTYPE)
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);
#endif
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if((Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) != COM_TRUE) &&
       (Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) == COM_START))
    {

        if (TxIpduRamPtr->Com_TickTxTimeout != COM_ZERO)
        {
            --TxIpduRamPtr->Com_TickTxTimeout;
        }
        if(TxIpduRamPtr->Com_TickTxTimeout == COM_ZERO)
        {
            Timeout_Flag = COM_TRUE;

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

#if (COM_RETRY_FAILED_TX_REQUESTS == STD_ON)

            Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

            TxIpduRamPtr->Com_n = COM_ZERO;

            TxIpduRamPtr->Com_MinDelayTick = COM_ZERO;

#if defined(COM_CANCELTRANSMITSUPPORT) && defined(COM_TP_IPDUTYPE)

            isCancelTransmitSupported = Com_GetValue(TXIPDU,_ISCANCELTRANSMITSUPPORTED,TxIpduConstPtr->txIPduFields);

            if((Com_GetValue(TXIPDU,_ISLARGEDATAPDU,TxIpduConstPtr->txIPduFields) != COM_FALSE) &&
               (isCancelTransmitSupported != COM_FALSE) &&
               (Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE))
            {

                ( void )PduR_ComCancelTransmit(TxIpduConstPtr->PdurId);
            }
#endif
        }
    }
    return Timeout_Flag;
}

#endif

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_Modes(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    boolean                     SendIPdu;

    SendIPdu     = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_MinDelayTick != COM_ZERO)
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

#if (COM_RETRY_FAILED_TX_REQUESTS == STD_ON)

    if ((TxIpduRamPtr->Com_MinDelayTick == COM_ZERO) &&
         Com_GetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags))
    {

        SendIPdu = COM_TRUE;
    }
#endif

    return SendIPdu;
}

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_DirectMode(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    boolean                     SendIPdu;

    SendIPdu     = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_n_Tick_Tx != COM_ZERO)
    {
        --TxIpduRamPtr->Com_n_Tick_Tx;
    }

    if(TxIpduRamPtr->Com_MinDelayTick == COM_ZERO)
    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
        else
        {
#ifdef COM_TXPDU_DEFERREDPROCESSING

            if((TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO) &&
               (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE))
            {

                SendIPdu = COM_TRUE;
            }
            else
#endif
            if((TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO) && (TxIpduRamPtr->Com_n != COM_ZERO))
            {

                SendIPdu = COM_TRUE;
            }
            else
            {

            }
        }
        if (TxIpduRamPtr->Com_n != COM_ZERO)
        {
            if (TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO)
            {
                TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;
            }
        }
    }
    return SendIPdu;
}

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_MixedMode(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    boolean                     SendIPdu;

    SendIPdu     = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_Tick_Tx != COM_ZERO)
    {
        --TxIpduRamPtr->Com_Tick_Tx;
    }
    if (TxIpduRamPtr->Com_n_Tick_Tx != COM_ZERO)
    {
        --TxIpduRamPtr->Com_n_Tick_Tx;
    }
    if(TxIpduRamPtr->Com_MinDelayTick == COM_ZERO)
    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
        else
        {
#ifdef COM_TXPDU_DEFERREDPROCESSING

            if((TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO) &&
               (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE))
            {

                SendIPdu = COM_TRUE;
            }
            else
#endif

            if((TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO) && (TxIpduRamPtr->Com_n != COM_ZERO))
            {
                SendIPdu = COM_TRUE;

            }
            else
            {
                if((TxIpduRamPtr->Com_Tick_Tx == COM_ZERO)&&(TxIpduRamPtr->Com_n == COM_ZERO))
                {
                    SendIPdu = COM_TRUE;

                }
            }
        }
        if ((TxIpduRamPtr->Com_n != COM_ZERO) && (TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO))
        {
            TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;
        }
    }
    else
    {
        if((TxIpduRamPtr->Com_Tick_Tx == COM_ZERO) && (TxIpduRamPtr->Com_n == COM_ZERO))
        {

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
        }
    }
    if(TxIpduRamPtr->Com_Tick_Tx == COM_ZERO)
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxPduId, TxIpduRamPtr->CurrentTxModePtr);
    }
    return SendIPdu;
}

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_NoneMode(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    boolean                     SendIPdu;

    SendIPdu     = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if(TxIpduRamPtr->Com_MinDelayTick == COM_ZERO)
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
                if(TxIpduRamPtr->Com_n_Tick_Tx != COM_ZERO)
                {
                    TxIpduRamPtr->Com_n_Tick_Tx--;
                }
                if(TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO)
                {

                    SendIPdu = COM_TRUE;
                }
            }
#endif
        }
    }
    return SendIPdu;
}

LOCAL_INLINE boolean Com_Lok_MainFunctionTx_PeriodicMode(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    boolean                     SendIPdu;

    SendIPdu     = COM_FALSE;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_Tick_Tx != COM_ZERO)
    {
        --TxIpduRamPtr->Com_Tick_Tx;
    }
    if(TxIpduRamPtr->Com_MinDelayTick == COM_ZERO )
    {

        if(Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

            SendIPdu = COM_TRUE;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }

        else
        {
            if(TxIpduRamPtr->Com_Tick_Tx == COM_ZERO)
            {

                SendIPdu = COM_TRUE;
            }
#ifdef COM_TXPDU_DEFERREDPROCESSING

            else if(Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
            {
                if (TxIpduRamPtr->Com_n_Tick_Tx != COM_ZERO)
                {
                    TxIpduRamPtr->Com_n_Tick_Tx--;
                }
                if(TxIpduRamPtr->Com_n_Tick_Tx == COM_ZERO)
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
        if(TxIpduRamPtr->Com_Tick_Tx == COM_ZERO)
        {

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
        }
    }

    if(TxIpduRamPtr->Com_Tick_Tx == COM_ZERO)
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxPduId, TxIpduRamPtr->CurrentTxModePtr);
    }
    return SendIPdu;
}

LOCAL_INLINE void Com_Lok_MainFunctionTx_SendIPdu(uint16_least TxPduId)
{
    Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

#ifdef COM_TP_IPDUTYPE
    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,COM_GET_TXPDURAM_S(TxPduId).Com_TxFlags) != COM_TRUE)
#endif
    {
        Com_Lok_SendIpdu((PduIdType)TxPduId,sendIpduFlag_u16);
    }
}

#if (COM_ENABLE_PERIODIC_FRAME_SYNC != STD_OFF)

LOCAL_INLINE void Com_Lok_MainFunctionTxModeProcessing(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if( COM_TX_MODE_IS_CYCLIC(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode)) )
    {
        Com_Lok_MainFunctionTxReloadTimePeriod(TxPduId);
    }
    else
    {

    }
}

LOCAL_INLINE void Com_Lok_MainFunctionTxReloadTimePeriod(uint16_least TxPduId)
{

    Com_TxIpduRamPtrType        TxIpduRamPtr;
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);

    if (TxIpduRamPtr->Com_Tick_Tx != COM_ZERO)
    {
        --TxIpduRamPtr->Com_Tick_Tx;
    }

    if(TxIpduRamPtr->Com_Tick_Tx == COM_ZERO)
    {

        TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(TxPduId, TxIpduRamPtr->CurrentTxModePtr);
    }
}
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_IsTxScheduled(PduIdType ComTxPduId, uint16 ComCallerTaskCycle)
{
    Com_TxIpduRamPtrType        TxIpduRamPtr;
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    uint32                      ticksinMs_u32;
    Com_TimeBaseType            timeBaseInMs_uo;
#endif
    boolean                     isTxScheduled_b;

    isTxScheduled_b = COM_TRUE;

#ifndef COM_TXSCHEDULED_DIFF_TIMEBASE
    (void)ComCallerTaskCycle;
#endif

    ComTxPduId   = COM_GET_TX_IPDU_ID(ComTxPduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);

    if (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) == COM_TXMODE_PERIODIC)
    {
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE

        timeBaseInMs_uo = COM_GET_MAINFUNCTION_CFG(COM_NUM_OF_RX_MAINFUNCTION + (COM_GET_TX_IPDU_CONSTDATA(ComTxPduId))->MainFunctionRef).TimeBaseInMs;

        if (ComCallerTaskCycle < timeBaseInMs_uo)
#endif
        {

            if (TxIpduRamPtr->Com_Tick_Tx > COM_ONE)
            {
                isTxScheduled_b = COM_FALSE;
            }
            else
            {

            }
        }
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
        else
        {

            ticksinMs_u32 = TxIpduRamPtr->Com_Tick_Tx;

            ticksinMs_u32 = ((ticksinMs_u32 != COM_ZERO) ?
                            ((ticksinMs_u32 - COM_ONE) * timeBaseInMs_uo) : (uint32)COM_ZERO);

            if (ticksinMs_u32 > ComCallerTaskCycle)
            {
                isTxScheduled_b = COM_FALSE;
            }
            else
            {

            }
        }
#endif
    }
    else
    {

    }

    return isTxScheduled_b;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_PROVIDE_IPDU_STATUS

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_ProvideTxIpduStatus(PduIdType PduId)
{
    boolean     pduStatus_b;

    if (PduId < COM_GET_NUM_TX_IPDU)
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        pduStatus_b = Com_CheckTxIPduStatus(PduId);
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

