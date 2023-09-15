

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)
LOCAL_INLINE void Com_Lok_RxTimeoutProcessing(PduIdType RxPduId, boolean RxIndication_b);
#endif

#ifdef COM_RxIPduTimeout

LOCAL_INLINE boolean Com_Lok_IPduBasedTimeoutMonitoring(PduIdType RxPduId, boolean reloadDmTimer_b);

LOCAL_INLINE boolean Com_Lok_IPduBasedSigTimeoutAction(PduIdType RxPduId);

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE boolean Com_Lok_IPduBasedSigGrpTimeoutAction(PduIdType RxPduId);
#endif

#endif

#ifdef COM_RxSigUpdateTimeout
LOCAL_INLINE boolean Com_Lok_SigBasedTimeoutMonitoring(PduIdType RxPduId);
#endif

#ifdef COM_RxSigGrpUpdateTimeout
LOCAL_INLINE boolean Com_Lok_SigGrpBasedTimeoutMonitoring(PduIdType RxPduId);
#endif

#ifdef COM_RxIPduDeferredProcessing
LOCAL_INLINE void Com_ProcessDeferredRxIpdu(PduIdType PduId);
#endif

#ifdef COM_RXIPDU_TP_INVALIDATION

#ifdef COM_RxSigInvalid
LOCAL_INLINE void Com_ExecuteRxSigInvalidActions(PduIdType PduId);
#endif

#ifdef COM_RxSigGrpInvalid
LOCAL_INLINE void Com_ExecuteRxSigGrpInvalidActions(PduIdType PduId);
#endif

#endif

#ifdef COM_RX_MAINFUNCTION_PROC

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_InternalMainFunctionRx(Com_MainFuncType RxMainFuncId)
{

   if(Com_Uninit_Flag == COM_INIT)
   {
# ifdef COM_RxIPduDeferredProcessing
        Com_RxIpduConstPtrType      RxIpduConstPtr;
# endif
        Com_RxIpduRamPtrType        RxIpduRamPtr;
        uint16_least                idx_IpduId_u16;
        uint16_least                numOfIpdus;
        boolean                     rxIndication_b;

        idx_IpduId_u16  = COM_GET_MAINFUNCTION_CFG( RxMainFuncId ).StartIPduId;
        numOfIpdus      = idx_IpduId_u16 + COM_GET_MAINFUNCTION_CFG( RxMainFuncId ).NumOfIpdus;

# ifdef COM_RxIPduDeferredProcessing
        RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(idx_IpduId_u16);
# endif
        RxIpduRamPtr    = &COM_GET_RXPDURAM_S(idx_IpduId_u16);

        for( ; idx_IpduId_u16 < numOfIpdus; idx_IpduId_u16++)
        {

            if(Com_CheckRxIPduStatus((PduIdType)idx_IpduId_u16))
            {
                Com_Get_SchM_Enter_Com_RxIPduProcess

                rxIndication_b = Com_GetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags);

                if(rxIndication_b != COM_FALSE)
                {

# ifdef COM_RxIPduDeferredProcessing

                    if(Com_GetValue(RXIPDU,_SIGPROC,RxIpduConstPtr->rxIPduFields) == COM_IMMEDIATE)
# endif
                    {
                        Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);
                    }
# ifdef COM_RxIPduDeferredProcessing
                    else
                    {
                        Com_ProcessDeferredRxIpdu((PduIdType)idx_IpduId_u16);
                    }
# endif

                }

# if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)

                Com_Lok_RxTimeoutProcessing((PduIdType)idx_IpduId_u16, rxIndication_b);

# endif

                Com_Get_SchM_Exit_Com_RxIPduProcess
            }

# ifdef COM_RxIPduDeferredProcessing
            RxIpduConstPtr++;
# endif
            RxIpduRamPtr++;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)

LOCAL_INLINE void Com_Lok_RxTimeoutProcessing(PduIdType RxPduId, boolean RxIndication_b)
{

   if(COM_CheckRxIPduDMStatus(RxPduId))
   {
        Com_RxIpduConstPtrType      RxIpduConstPtr;

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
        Com_RxIpduRamPtrType        RxIpduRamPtr;
#endif

        boolean                     isGwSigUpdated_b;

        isGwSigUpdated_b = COM_FALSE;

        RxIpduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
        RxIpduRamPtr     = &COM_GET_RXPDURAM_S(RxPduId);
#endif

#ifdef COM_RxIPduTimeout

        if(RxIpduConstPtr->Timeout_Fact != COM_ZERO)
        {

            isGwSigUpdated_b = Com_Lok_IPduBasedTimeoutMonitoring( (PduIdType)RxPduId, RxIndication_b );
        }
#else
        (void)RxIndication_b;
#endif

#ifdef COM_RxSigUpdateTimeout

        if(RxIpduConstPtr->SignalTimeout_Ref != NULL_PTR)
        {
            isGwSigUpdated_b = Com_Lok_SigBasedTimeoutMonitoring( (PduIdType)RxPduId ) || isGwSigUpdated_b;
        }
#endif

#ifdef COM_RxSigGrpUpdateTimeout

        if(RxIpduConstPtr->SignalGrpTimeout_Ref != NULL_PTR)
        {
            isGwSigUpdated_b = Com_Lok_SigGrpBasedTimeoutMonitoring( (PduIdType)RxPduId ) || isGwSigUpdated_b;
        }
#endif

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)

        if(isGwSigUpdated_b)
        {

            Com_Get_SchM_Enter_Com_RxPduBuffer

            if(Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags) != COM_TRUE)
            {

                (void)Com_WriteSigGwReceiveQueue((PduIdType)RxPduId);

                Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags,COM_TRUE);
            }
            Com_Get_SchM_Exit_Com_RxPduBuffer
        }
#else
        (void)isGwSigUpdated_b;
#endif

   }
}
#endif

#ifdef COM_RxIPduTimeout

LOCAL_INLINE boolean Com_Lok_IPduBasedTimeoutMonitoring(PduIdType RxPduId, boolean reloadDmTimer_b)
{
   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxIpduRamPtrType        RxIpduRamPtr;
   uint16                      rxTimeoutTicks_u16;
   boolean                     isGwSigUpdated_b;

   isGwSigUpdated_b = COM_FALSE;

    RxIpduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    RxIpduRamPtr     = &COM_GET_RXPDURAM_S(RxPduId);

# ifdef COM_RX_DUAL_CYCLE_SUPPPORT

   if(Com_GetRamValue(RXIPDU,_RELOAD_RXTICKS, RxIpduRamPtr->RxFlags))
   {
        Com_Get_SchM_Enter_Com_RxPduBuffer

        Com_SetRamValue(RXIPDU,_RELOAD_RXTICKS, RxIpduRamPtr->RxFlags, COM_FALSE);

        Com_Get_SchM_Exit_Com_RxPduBuffer

        reloadDmTimer_b = COM_TRUE;
   }

    rxTimeoutTicks_u16 = RxIpduRamPtr->RxDualCycTicks_u16;

   if(rxTimeoutTicks_u16 == COM_ZERO)
# endif
   {

        rxTimeoutTicks_u16 = COM_GET_RXIPDU_TIMEOUT(RxPduId, RxIpduConstPtr);
   }

   if(reloadDmTimer_b)
   {

#if(COM_ENABLE_JITTERFLITER == STD_ON)

        RxIpduRamPtr->RxTicks_u16 = (rxTimeoutTicks_u16 == COM_ZERO) ? COM_RXTIMER_MAX : (rxTimeoutTicks_u16 + 2u);
#else

        RxIpduRamPtr->RxTicks_u16 = (rxTimeoutTicks_u16 == COM_ZERO) ? COM_RXTIMER_MAX : (rxTimeoutTicks_u16 + 1u);

#endif

   }

   if((RxIpduRamPtr->RxTicks_u16 != COM_RXTIMER_MAX) && (RxIpduRamPtr->RxTicks_u16 != COM_ZERO))
   {
        --RxIpduRamPtr->RxTicks_u16;
   }

   if(RxIpduRamPtr->RxTicks_u16 == COM_ZERO)
   {

        RxIpduRamPtr->RxTicks_u16 = rxTimeoutTicks_u16;

        isGwSigUpdated_b = Com_Lok_IPduBasedSigTimeoutAction( RxPduId );

#ifdef COM_RX_SIGNALGROUP

        isGwSigUpdated_b = Com_Lok_IPduBasedSigGrpTimeoutAction( RxPduId ) || isGwSigUpdated_b;
#endif

#ifdef COM_RxIPduTimeoutNotify
        if(RxIpduConstPtr->TimeOutNotification_Cbk != NULL_PTR)
        {
            Com_Get_SchM_Exit_Com_RxIPduProcess

            RxIpduConstPtr->TimeOutNotification_Cbk();

            Com_Get_SchM_Enter_Com_RxIPduProcess
        }
#endif

   }

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_RxIPduTimeout
LOCAL_INLINE boolean Com_Lok_IPduBasedSigTimeoutAction(PduIdType RxPduId)
{
   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxSigConstPtrType       RxSigConstPtr;
#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
   Com_RxSigRamPtrType         RxSigRamPtr;
#endif
   uint16_least                idx_Sig_u16;
   Com_MainFuncType            RxMainFuncId;
   boolean                     isGwSigUpdated_b;

   isGwSigUpdated_b = COM_FALSE;

    RxIpduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxMainFuncId     = RxIpduConstPtr->MainFunctionRef;

    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIpduConstPtr->RxSigId_Index);

#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
    RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIpduConstPtr->RxSigId_Index);
#endif

   for(idx_Sig_u16 = RxIpduConstPtr->No_Of_Sig_Ref; idx_Sig_u16 != COM_ZERO; idx_Sig_u16--)
   {

#ifdef COM_RxSigUpdateBit
        if(Com_GetValue(GEN,_UPDBITCONF,RxSigConstPtr->General) == COM_FALSE)
#endif
        {

            if(Com_GetValue(RXSIG,_TOACTION,RxSigConstPtr->rxSignalFields))
            {
                Com_SigMaxType RxSigVal;
#if(defined(COM_RXSIG_INT64) || defined(COM_RXSIG_FLOAT64SUPP))
                uint8          Type;

                Type     = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif
                RxSigVal = RxSigConstPtr->Init_Val;

                Com_Get_SchM_Enter_Com_RxSigBuff(MAINFUNCTIONRX)

#ifdef COM_RXSIG_FLOAT64SUPP
                if(Type == COM_FLOAT64)
                {

                    COM_GET_SIGTYPEFLOAT64_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) =
                                                         Com_getfloat64InitValue(RxSigVal);
                }
                else
#endif

                {

#ifdef COM_RXSIG_INT64

                    RxSigVal = (Type == COM_SINT64) ? (Com_SigMaxType)((sint64)((sint32)RxSigVal)) : RxSigVal;
#endif
                    Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigVal, RxMainFuncId);
                }

                Com_Get_SchM_Exit_Com_RxSigBuff(MAINFUNCTIONRX)

            }
#ifdef COM_SIGNALGATEWAY

            if(Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields) != COM_FALSE)
            {

                Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr->rxSigRAMFields,COM_TRUE);

                isGwSigUpdated_b = COM_TRUE;
            }
#endif

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)

            Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_TRUE);
#endif
        }

        RxSigConstPtr++;
#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
        RxSigRamPtr++;
#endif
   }

    return isGwSigUpdated_b;
}
#endif

#if defined(COM_RX_SIGNALGROUP) && defined(COM_RxIPduTimeout)
LOCAL_INLINE boolean Com_Lok_IPduBasedSigGrpTimeoutAction(PduIdType RxPduId)
{
   Com_RxIpduConstPtrType          RxIpduConstPtr;
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
#if defined(COM_SIGNALGROUPGATEWAY) || (defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD))
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
#endif
   uint16_least                    idx_SigGrp_u16;
   boolean                         isGwSigUpdated_b;

   isGwSigUpdated_b = COM_FALSE;

    RxIpduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIpduConstPtr->FirstRxSigGrp_Index);

#if defined(COM_SIGNALGROUPGATEWAY) || (defined COM_RxFilters && defined COM_F_MASKEDNEWDIFFERSOLD)
    RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(RxIpduConstPtr->FirstRxSigGrp_Index);
#endif
   for(idx_SigGrp_u16 = RxIpduConstPtr->No_Of_SigGrp_Ref; idx_SigGrp_u16 != COM_ZERO; idx_SigGrp_u16--)
   {

#ifdef COM_RxSigGrpUpdateBit
        if(Com_GetValue(RXSIGGRP,_UPDBITCONF,RxSigGrpConstPtr->rxSignalGrpFields) == COM_FALSE)
#endif
        {

            if(Com_GetValue(RXSIGGRP,_TOACTION,RxSigGrpConstPtr->rxSignalGrpFields))
            {

                Com_Lok_SigGrpReplaceToInit( RxSigGrpConstPtr, RxIpduConstPtr->MainFunctionRef );
            }
#ifdef COM_SIGNALGROUPGATEWAY

            if(Com_GetValue(RXSIGGRP,_ISGWSIGGRP,RxSigGrpConstPtr->rxSignalGrpFields) != COM_FALSE)
            {

                Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);

                isGwSigUpdated_b = COM_TRUE;
            }
#endif

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)

            Com_SetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
#endif
        }

        RxSigGrpConstPtr++;
#if defined(COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
        RxSigGrpRamPtr++;
#endif
   }

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_RxSigUpdateTimeout

LOCAL_INLINE boolean Com_Lok_SigBasedTimeoutMonitoring(PduIdType RxPduId)
{
   Com_RxIpduConstPtrType              RxIpduConstPtr;
   Com_RxSigConstPtrType               RxSigConstPtr;
#if(defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)))
   Com_RxSigRamPtrType                 RxSigRamPtr;
#endif
   const Com_SignalTimeoutInfo *       SigTimeOutConstPtr;
   uint16 *                            SigTimeOutRamPtr;
   uint16_least                        numOfSig_u16;
   uint16_least                        idx_Sig_u16;
   Com_MainFuncType                    RxMainFuncId;
#ifdef COM_RxUpdateTimeoutNotify
   boolean                             CallTOSigNotify_b;
#endif
   boolean                             isGwSigUpdated_b;

   isGwSigUpdated_b    = COM_FALSE;

    RxIpduConstPtr      = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxMainFuncId        = RxIpduConstPtr->MainFunctionRef;

    numOfSig_u16        = RxIpduConstPtr->SignalTimeout_Ref->numWithUpdateBit;

    SigTimeOutConstPtr  = RxIpduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;

    SigTimeOutRamPtr    = RxIpduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;

   for(idx_Sig_u16 = numOfSig_u16; idx_Sig_u16 != COM_ZERO; idx_Sig_u16--)
   {
#ifdef COM_RxUpdateTimeoutNotify

        CallTOSigNotify_b = COM_FALSE;
#endif
        RxSigConstPtr     = COM_GET_RXSIG_CONSTDATA(SigTimeOutConstPtr->SigId);

#if(defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)))
        RxSigRamPtr       = &COM_GET_RXSIGNALFLAG(SigTimeOutConstPtr->SigId);
#endif

        Com_Get_SchM_Enter_Com_RxSigToTicks
        if(((*SigTimeOutRamPtr) != COM_RXTIMER_MAX) && ((*SigTimeOutRamPtr) != COM_ZERO))
        {
            --(*SigTimeOutRamPtr);
        }

        if((*SigTimeOutRamPtr) == COM_ZERO)
        {

            (*SigTimeOutRamPtr) = SigTimeOutConstPtr->Timeout;

            if(Com_GetValue(RXSIG,_TOACTION,RxSigConstPtr->rxSignalFields))
            {
                Com_SigMaxType RxSigVal;
#if(defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP ))
                uint8          Type;

                Type     = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif
                RxSigVal = RxSigConstPtr->Init_Val;

#ifdef COM_RXSIG_FLOAT64SUPP
                if(Type == COM_FLOAT64)
                {

                    COM_GET_SIGTYPEFLOAT64_BUFF(RxMainFuncId,RxSigConstPtr->SigBuff_Index) =
                                                         Com_getfloat64InitValue(RxSigVal);
                }
                else
#endif

                {

#ifdef COM_RXSIG_INT64

                    RxSigVal = (Type == COM_SINT64) ? (Com_SigMaxType)((sint64)((sint32)RxSigVal)) : RxSigVal;
#endif

                    Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigVal, RxMainFuncId);
                }
            }

#ifdef COM_RxUpdateTimeoutNotify

            CallTOSigNotify_b = COM_TRUE;
#endif

#ifdef COM_SIGNALGATEWAY

            if(Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields) != COM_FALSE)
            {

                Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr->rxSigRAMFields,COM_TRUE);

                isGwSigUpdated_b = COM_TRUE;
            }
#endif

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)

            Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_TRUE);
#endif
        }
        Com_Get_SchM_Exit_Com_RxSigToTicks

#ifdef COM_RxUpdateTimeoutNotify

        if((CallTOSigNotify_b != COM_FALSE) &&
            (SigTimeOutConstPtr->TimeOutNotification_Cbk != NULL_PTR))
        {
            Com_Get_SchM_Exit_Com_RxIPduProcess

            SigTimeOutConstPtr->TimeOutNotification_Cbk();

            Com_Get_SchM_Enter_Com_RxIPduProcess
        }
#endif

        SigTimeOutConstPtr++;
        SigTimeOutRamPtr++;
   }

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_RxSigGrpUpdateTimeout

LOCAL_INLINE boolean Com_Lok_SigGrpBasedTimeoutMonitoring(PduIdType RxPduId)
{
   Com_RxIpduConstPtrType              RxIpduConstPtr;
   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;
#if defined (COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
   Com_RxSigGrpRamPtrType              RxSigGrpRamPtr;
#endif
   const Com_SignalTimeoutInfo *       SigTimeOutConstPtr;
   uint16 *                            SigTimeOutRamPtr;
   uint16_least                        numOfSigGrp_u16;
   uint16_least                        idx_SigGrp_u16;
   Com_MainFuncType                    RxMainFuncId;
#ifdef COM_RxUpdateTimeoutNotify

   boolean                             CallTOSigGrpNotify_b;
#endif
   boolean                             isGwSigUpdated_b;

   isGwSigUpdated_b    = COM_FALSE;

    RxIpduConstPtr      = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    RxMainFuncId        = RxIpduConstPtr->MainFunctionRef;

    numOfSigGrp_u16     = RxIpduConstPtr->SignalGrpTimeout_Ref->numWithUpdateBit;

    SigTimeOutConstPtr  = RxIpduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;

    SigTimeOutRamPtr    = RxIpduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;

   for(idx_SigGrp_u16 = numOfSigGrp_u16; idx_SigGrp_u16 != COM_ZERO; idx_SigGrp_u16--)
   {
#ifdef COM_RxUpdateTimeoutNotify

        CallTOSigGrpNotify_b = COM_FALSE;
#endif

#if defined(COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
        RxSigGrpRamPtr       = &COM_GET_RXSIGGRPFLAG(SigTimeOutConstPtr->SigId);
#endif

        Com_Get_SchM_Enter_Com_RxSigGrpToTicks
        if(((*SigTimeOutRamPtr) != COM_RXTIMER_MAX) && ((*SigTimeOutRamPtr) != COM_ZERO))
        {
            --(*SigTimeOutRamPtr);
        }

        if((*SigTimeOutRamPtr) == COM_ZERO)
        {

            (*SigTimeOutRamPtr) = SigTimeOutConstPtr->Timeout;

            RxSigGrpConstPtr    = COM_GET_RXSIGGRP_CONSTDATA(SigTimeOutConstPtr->SigId);

            if(Com_GetValue(RXSIGGRP,_TOACTION,RxSigGrpConstPtr->rxSignalGrpFields))
            {

                Com_Lok_SigGrpReplaceToInit( RxSigGrpConstPtr, RxMainFuncId );
            }

#ifdef COM_RxUpdateTimeoutNotify

            CallTOSigGrpNotify_b = COM_TRUE;
#endif

#ifdef COM_SIGNALGROUPGATEWAY

            if(Com_GetValue(RXSIGGRP,_ISGWSIGGRP,RxSigGrpConstPtr->rxSignalGrpFields) != COM_FALSE)
            {

                Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);

                isGwSigUpdated_b = COM_TRUE;
            }
#endif

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)

            Com_SetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
#endif
        }
        Com_Get_SchM_Exit_Com_RxSigGrpToTicks

#ifdef COM_RxUpdateTimeoutNotify

        if((CallTOSigGrpNotify_b != COM_FALSE) &&
            (SigTimeOutConstPtr->TimeOutNotification_Cbk != NULL_PTR))
        {
            Com_Get_SchM_Exit_Com_RxIPduProcess

            SigTimeOutConstPtr->TimeOutNotification_Cbk();

            Com_Get_SchM_Enter_Com_RxIPduProcess
        }
#endif

        SigTimeOutConstPtr++;
        SigTimeOutRamPtr++;
   }

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_PROVIDE_IPDU_STATUS

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_ProvideRxIpduStatus(PduIdType PduId)
{
   boolean     pduStatus_b;

   if(PduId < COM_GET_NUM_RX_IPDU)
   {

        PduId = COM_GET_RX_IPDU_ID(PduId);

        pduStatus_b = Com_CheckRxIPduStatus(PduId);
   }
   else{
        pduStatus_b  = COM_FALSE;
   }

    return(pduStatus_b);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#ifdef COM_RxIPduDeferredProcessing

LOCAL_INLINE void Com_ProcessDeferredRxIpdu(PduIdType PduId)
{
   Com_RxIpduConstPtrType  RxIpduConstPtr;
   Com_RxIpduRamPtrType    RxIpduRamPtr;
   PduInfoType             comRxPduInfo;

    RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(PduId);
    RxIpduRamPtr    = &COM_GET_RXPDURAM_S(PduId);

   comRxPduInfo.SduDataPtr = COM_GET_DEFERREDBUFFER(RxIpduConstPtr->MainFunctionRef);

#ifdef COM_TP_IPDUTYPE
   if(Com_GetValue(RXIPDU,_IS_TP_TYPE,RxIpduConstPtr->rxIPduFields) == COM_FALSE)
#endif
   {
        Com_Get_SchM_Enter_Com_RxPduBuffer

        comRxPduInfo.SduLength = RxIpduRamPtr->RxIPduLength;

        Com_ByteCopy(comRxPduInfo.SduDataPtr, RxIpduConstPtr->BuffPtr, comRxPduInfo.SduLength);

        Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);

        Com_Get_SchM_Exit_Com_RxPduBuffer

#if defined(COM_RxIPduCallOuts) || defined(COM_RX_IPDUCOUNTER)
        if(Com_IsValidRxIpdu(PduId, &comRxPduInfo))
#endif
        {
            Com_ProcessRxIPdu(PduId, &comRxPduInfo);
        }
   }
#ifdef COM_TP_IPDUTYPE
   else{
        if(Com_GetRamValue(RXIPDU,_IS_INVALID,RxIpduRamPtr->RxFlags) == COM_FALSE)
        {
            Com_Get_SchM_Enter_Com_RxPduBuffer

            comRxPduInfo.SduLength = RxIpduRamPtr->RxIPduLength;

            Com_ByteCopy(comRxPduInfo.SduDataPtr, RxIpduConstPtr->BuffPtr, comRxPduInfo.SduLength);

            Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);

            Com_Get_SchM_Exit_Com_RxPduBuffer

            Com_ProcessRxIPdu(PduId, &comRxPduInfo);
        }
        else{
            Com_Get_SchM_Enter_Com_RxPduBuffer

            Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);

            Com_SetRamValue(RXIPDU,_IS_INVALID,RxIpduRamPtr->RxFlags,COM_FALSE);

            Com_Get_SchM_Exit_Com_RxPduBuffer

# ifdef COM_RXIPDU_TP_INVALIDATION
            if(Com_GetValue(RXIPDU,_TP_INV_CFG,RxIpduConstPtr->rxIPduFields))
            {
                Com_ExecuteRxInvalidActions(PduId);
            }
# endif
        }
   }
#endif
}

#endif

#ifdef COM_RXIPDU_TP_INVALIDATION

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

void Com_ExecuteRxInvalidActions(PduIdType PduId)
{
#ifdef COM_RxSigInvalid
   Com_ExecuteRxSigInvalidActions(PduId);
#endif

#ifdef COM_RxSigGrpInvalid
   Com_ExecuteRxSigGrpInvalidActions(PduId);
#endif

#if defined(COM_RxIPduNotification) || defined(COM_RxSignalNotify) || defined(COM_RxSignalGrpNotify)
   Com_InvokeRxNotifications(PduId);
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_RxSigInvalid

LOCAL_INLINE void Com_ExecuteRxSigInvalidActions(PduIdType PduId)
{
   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxSigConstPtrType       RxSigConstPtr;
#ifdef COM_RxSignalNotify
   Com_RxSigRamPtrType         RxSigRamPtr;
#endif
   uint16_least                idx_SigId_u16;
   uint16_least                maxRxSigId_u16;
   Com_SigMaxType              RxSigNewVal;
#ifdef COM_RxSigUpdateTimeout
   uint16_least                Idx_SigTout;
   uint8                       IpduUpdateBitStatus;
   uint8                       SigUpdateBitStatus;
#endif
   Com_MainFuncType            rxMainFuncId;

    RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(PduId);

#ifdef COM_RxSigUpdateTimeout

   if((RxIpduConstPtr->SignalTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(PduId)))
   {

        IpduUpdateBitStatus = COM_UPDATEBIT_APPLICABLE;
   }
   else{
        IpduUpdateBitStatus = COM_UPDATEBIT_NOT_APPLICABLE;
   }

    Idx_SigTout = COM_ZERO;
#endif

    rxMainFuncId    = RxIpduConstPtr->MainFunctionRef;

   idx_SigId_u16   = RxIpduConstPtr->RxSigId_Index;
    maxRxSigId_u16  = idx_SigId_u16 + RxIpduConstPtr->No_Of_Sig_Ref;

    RxSigConstPtr   = COM_GET_RXSIG_CONSTDATA(idx_SigId_u16);
#ifdef COM_RxSignalNotify
    RxSigRamPtr     = &COM_GET_RXSIGNALFLAG(idx_SigId_u16);
#endif

   for( ; idx_SigId_u16 < maxRxSigId_u16; idx_SigId_u16++ )
   {

#ifdef COM_RxSigUpdateTimeout
        SigUpdateBitStatus = IpduUpdateBitStatus;
#endif

        if(Com_GetValue(RXSIG,_INVACTION,RxSigConstPtr->rxSignalFields) != COM_NONE)
        {
            RxSigNewVal = RxSigConstPtr->DataInvalid_Val;

            if(Com_Lok_ValidateRxSignal((Com_SignalIdType)idx_SigId_u16, &RxSigNewVal))
            {

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
                if(Com_GetValue(GEN,_TYPE,RxSigConstPtr->General) == COM_UINT8_DYN)
                {
                    Com_Get_SchM_Enter_Com_RxSigDynBuff

                    Com_ByteCopyInit( &COM_GET_SIGTYPEUINT8DYN_BUFF(rxMainFuncId,RxSigConstPtr->SigBuff_Index)
   ,                                     (uint32)RxSigNewVal, RxSigConstPtr->BitSize );

                    Com_Get_SchM_Exit_Com_RxSigDynBuff
                }
                else
#endif
                {
                    Com_Get_SchM_Enter_Com_RxSigBuff(MAINFUNCTIONRX)

                    Com_UpdateRxSignalBuffer(RxSigConstPtr, RxSigNewVal, rxMainFuncId);

                    Com_Get_SchM_Exit_Com_RxSigBuff(MAINFUNCTIONRX)
                }

#ifdef COM_RxSigUpdateTimeout
                SigUpdateBitStatus <<= COM_ONE;
#endif

#ifdef COM_RxSignalNotify
                Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,COM_TRUE);
#endif
            }
        }

#ifdef COM_RxSigUpdateTimeout
        if(SigUpdateBitStatus != COM_UPDATEBIT_NOT_APPLICABLE)
        {
            Com_Lok_LoadSigTimeoutValue((Com_SignalIdType)idx_SigId_u16, SigUpdateBitStatus, &Idx_SigTout);
        }
#endif

        RxSigConstPtr++;
#ifdef COM_RxSignalNotify
        RxSigRamPtr++;
#endif

   }
}
#endif

#ifdef COM_RxSigGrpInvalid

LOCAL_INLINE void Com_ExecuteRxSigGrpInvalidActions(PduIdType PduId)
{
   Com_RxIpduConstPtrType          RxIpduConstPtr;
   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
#ifdef COM_RxSignalGrpNotify
   Com_RxSigGrpRamPtrType          RxSigGrpRamPtr;
#endif
   uint16_least                    idx_SigGrpId_u16;
   uint16_least                    maxSigGrpId_u16;
#ifdef COM_RxSigGrpUpdateTimeout
   uint16_least                    Idx_SigTout;
   uint8                           IpduUpdateBitStatus;
   uint8                           SigUpdateBitStatus;
#endif
   uint8                           invalidAction_u8;
   Com_MainFuncType                rxMainFuncId;

    RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(PduId);

#ifdef COM_RxSigGrpUpdateTimeout

   if((RxIpduConstPtr->SignalGrpTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(PduId)))
   {

        IpduUpdateBitStatus = COM_UPDATEBIT_APPLICABLE;
   }
   else{
        IpduUpdateBitStatus = COM_UPDATEBIT_NOT_APPLICABLE;
   }

    Idx_SigTout = COM_ZERO;

#endif

    rxMainFuncId      = RxIpduConstPtr->MainFunctionRef;

   idx_SigGrpId_u16  = RxIpduConstPtr->FirstRxSigGrp_Index;
    maxSigGrpId_u16   = idx_SigGrpId_u16 + RxIpduConstPtr->No_Of_SigGrp_Ref;

    RxSigGrpConstPtr  = COM_GET_RXSIGGRP_CONSTDATA(idx_SigGrpId_u16);

#ifdef COM_RxSignalGrpNotify
    RxSigGrpRamPtr    = &COM_GET_RXSIGGRPFLAG(idx_SigGrpId_u16);
#endif

   for( ; idx_SigGrpId_u16 < maxSigGrpId_u16; idx_SigGrpId_u16++)
   {
#ifdef COM_RxSigGrpUpdateTimeout
        SigUpdateBitStatus = IpduUpdateBitStatus;
#endif

        invalidAction_u8 = Com_GetValue(RXSIGGRP,_INVACTION,RxSigGrpConstPtr->rxSignalGrpFields);

        if(invalidAction_u8 == COM_REPLACE)
        {

            Com_Lok_SigGrpReplaceToInit(RxSigGrpConstPtr, rxMainFuncId);

#ifdef COM_RxSigGrpUpdateTimeout
            SigUpdateBitStatus <<= COM_ONE;
#endif

#ifdef COM_RxSignalGrpNotify
            Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
#endif
        }
#ifdef COM_RxSigGrpInvalidNotify
        else if(invalidAction_u8 == COM_NOTIFY)
        {

            if(RxSigGrpConstPtr->DataInvalid_Indication_Cbk != NULL_PTR)
            {
                RxSigGrpConstPtr->DataInvalid_Indication_Cbk();
            }
        }
#endif
        else{

        }

#ifdef COM_RxSigGrpUpdateTimeout
        if(SigUpdateBitStatus != COM_UPDATEBIT_NOT_APPLICABLE)
        {
            Com_Lok_LoadSigGrpTimeoutValue((Com_SignalGroupIdType)idx_SigGrpId_u16, SigUpdateBitStatus, &Idx_SigTout);
        }
#endif

        RxSigGrpConstPtr++;
#ifdef COM_RxSignalGrpNotify
        RxSigGrpRamPtr++;
#endif
   }
}
#endif

#endif

