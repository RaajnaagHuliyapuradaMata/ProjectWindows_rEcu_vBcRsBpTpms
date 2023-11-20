#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)
LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_RxTimeoutProcessing(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
   ,     VAR(boolean, AUTOMATIC)     RxIndication_b
                                                             );
#endif

#ifdef COM_RxIPduTimeout
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_IPduBasedTimeoutMonitoring(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
   ,     VAR(boolean, AUTOMATIC)     RxIndication_b
                                                                       );

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_IPduBasedSigTimeoutAction(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
                                                                      );

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_IPduBasedSigGrpTimeoutAction(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
                                                                         );
#endif
#endif

#ifdef COM_RxSigUpdateTimeout
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_SigBasedTimeoutMonitoring(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
                                                                      );
#endif

#ifdef COM_RxSigGrpUpdateTimeout
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_SigGrpBasedTimeoutMonitoring(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
                                                                         );
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_InternalMainFunctionRx( VAR(Com_MainFuncType,AUTOMATIC) RxMainFuncId )
{
   Com_RxIpduConstPtrType              RxIPduConstPtr;
   Com_RxIpduRamPtrType                RxIpduRamPtr;
   VAR(uint16_least, AUTOMATIC)        Idx_Pdu_ui;
   VAR(Type_CfgSwcServiceCom_tIdIPdu,AUTOMATIC)       StartIPduId;
   VAR(Type_CfgSwcServiceCom_tIdIPdu,AUTOMATIC)       EndIPduId;

   if(
#if(COM_CONFIGURATION_USE_DET == STD_ON)
        Com_Lok_DETCheck_Void(COMServiceId_MainFunctionRx)
#else
        (Com_Uninit_Flag == COM_INIT)
#endif
        )
   {

        StartIPduId    = COM_GET_MAINFUNCTION_CFG( RxMainFuncId ).StartIPduId;
        EndIPduId      = StartIPduId + COM_GET_MAINFUNCTION_CFG( RxMainFuncId ).NumOfIpdus;

        RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(StartIPduId);
        RxIpduRamPtr   = &COM_GET_RXPDURAM_S(StartIPduId);

        for(Idx_Pdu_ui = (uint16_least)StartIPduId; Idx_Pdu_ui < (uint16_least)EndIPduId; Idx_Pdu_ui++)
        {

            if(Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)Idx_Pdu_ui))
            {
#if defined(COM_RxIPduDeferredProcessing) || \
    defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)
                VAR(boolean,AUTOMATIC)  RxIndication_b;

                RxIndication_b = Com_GetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags);
#endif

#ifdef COM_RxIPduDeferredProcessing

                if(Com_GetValue(RXIPDU,_SIGPROC,RxIPduConstPtr->rxIPduFields) == COM_IMMEDIATE)
#endif
                {
                    Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);
                }
#ifdef COM_RxIPduDeferredProcessing
                else{

                    if(RxIndication_b != COM_FALSE)
                    {
                        VAR(Type_SwcServiceCom_stInfoPdu, COM_VAR)   ComRxIPduInfo;

                        SchM_Enter_Com_RxPduBuffer();

                        ComRxIPduInfo.SduDataPtr = COM_GET_DEFERREDBUFFER(RxMainFuncId);
                        ComRxIPduInfo.SduLength  = RxIpduRamPtr->RxIPduLength;

                        Com_ByteCopy(ComRxIPduInfo.SduDataPtr, RxIPduConstPtr->BuffPtr, ComRxIPduInfo.SduLength);

                        Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_FALSE);

                        SchM_Exit_Com_RxPduBuffer();

                        Com_ProcessRxIPdu((Type_SwcServiceCom_tIdPdu)Idx_Pdu_ui, &ComRxIPduInfo);
                    }
                }
#endif

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)

                Com_Lok_RxTimeoutProcessing((Type_SwcServiceCom_tIdPdu)Idx_Pdu_ui, RxIndication_b);

#endif

            }

            RxIPduConstPtr++;
            RxIpduRamPtr++;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_RxTimeoutProcessing( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
   ,     VAR(boolean, AUTOMATIC)     RxIndication_b )
{
   Com_RxIpduConstPtrType  RxIPduConstPtr;
#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
   Com_RxIpduRamPtrType    RxIpduRamPtr;
#endif

   VAR(boolean, AUTOMATIC) isGwSigUpdated_b;

   if(COM_CheckRxIPduDMStatus(RxPduId))
   {
        RxIPduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
        RxIpduRamPtr     = &COM_GET_RXPDURAM_S(RxPduId);
#endif

#ifdef COM_RxIPduTimeout

        isGwSigUpdated_b = Com_Lok_IPduBasedTimeoutMonitoring( (Type_SwcServiceCom_tIdPdu)RxPduId, RxIndication_b );

#else
        isGwSigUpdated_b = COM_FALSE;

#endif

#ifdef COM_RxSigUpdateTimeout

        if(RxIPduConstPtr->SignalTimeout_Ref != NULL_PTR)
        {
            isGwSigUpdated_b = Com_Lok_SigBasedTimeoutMonitoring( (Type_SwcServiceCom_tIdPdu)RxPduId ) || isGwSigUpdated_b;
        }
#endif

#ifdef COM_RxSigGrpUpdateTimeout

        if(RxIPduConstPtr->SignalGrpTimeout_Ref != NULL_PTR)
        {
            isGwSigUpdated_b = Com_Lok_SigGrpBasedTimeoutMonitoring( (Type_SwcServiceCom_tIdPdu)RxPduId ) || isGwSigUpdated_b;
        }
#endif

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)

        if((isGwSigUpdated_b) &&
            (Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags) != COM_TRUE))
        {

            SchM_Enter_Com_RxSigGwQueueProtArea();

            (void)Com_WriteSigGwReceiveQueue((Type_SwcServiceCom_tIdPdu)RxPduId);

            Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags,COM_TRUE);
            SchM_Exit_Com_RxSigGwQueueProtArea();
        }
#else
        (void)isGwSigUpdated_b;
#endif

   }
}
#endif

#ifdef COM_RxIPduTimeout

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_IPduBasedTimeoutMonitoring(
                                                            VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId
   ,     VAR(boolean, AUTOMATIC)     RxIndication_b
                                                                       )
{
   Com_RxIpduConstPtrType      RxIPduConstPtr;
   Com_RxIpduRamPtrType        RxIpduRamPtr;
   VAR(uint16, AUTOMATIC)      rxTimeOutVal_u16;
   VAR(boolean, AUTOMATIC)     isGwSigUpdated_b;
#ifdef COM_RxIPduTimeoutNotify
   VAR(boolean, AUTOMATIC)     CallTONotify_b;

   CallTONotify_b   = COM_FALSE;
#endif

   isGwSigUpdated_b = COM_FALSE;

    RxIPduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    RxIpduRamPtr     = &COM_GET_RXPDURAM_S(RxPduId);

    rxTimeOutVal_u16 = COM_GET_RXIPDU_TIMEOUT(RxPduId, RxIPduConstPtr);

   if(RxIndication_b != COM_FALSE)
   {

#if(COM_ENABLE_JITTERFLITER == STD_ON)

        RxIpduRamPtr->RxTicks_u16 =
                (rxTimeOutVal_u16 == 0) ? COM_RXTIMER_MAX : (rxTimeOutVal_u16 + 2u);
#else

        RxIpduRamPtr->RxTicks_u16 =
                (rxTimeOutVal_u16 == 0) ? COM_RXTIMER_MAX : (rxTimeOutVal_u16 + 1u);

#endif

   }

    SchM_Enter_Com_RxSigBuff(MAINFUNCTIONRX);

   if((RxIpduRamPtr->RxTicks_u16 != COM_RXTIMER_MAX) && (RxIpduRamPtr->RxTicks_u16 != 0))
   {
        --RxIpduRamPtr->RxTicks_u16;
   }

   if(RxIpduRamPtr->RxTicks_u16 == 0x00)
   {

        RxIpduRamPtr->RxTicks_u16 = rxTimeOutVal_u16;

        isGwSigUpdated_b = Com_Lok_IPduBasedSigTimeoutAction( RxPduId );

#ifdef COM_RX_SIGNALGROUP

        isGwSigUpdated_b = Com_Lok_IPduBasedSigGrpTimeoutAction( RxPduId ) || isGwSigUpdated_b;
#endif

#ifdef COM_RxIPduTimeoutNotify

        CallTONotify_b = COM_TRUE;
#endif

   }
    SchM_Exit_Com_RxSigBuff(MAINFUNCTIONRX);

#ifdef COM_RxIPduTimeoutNotify

   if((CallTONotify_b != COM_FALSE) &&
        (RxIPduConstPtr->TimeOutNotification_Cbk != NULL_PTR))
   {

        RxIPduConstPtr->TimeOutNotification_Cbk();
   }
#endif

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_RxIPduTimeout
LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_IPduBasedSigTimeoutAction( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId )
{
   Com_RxIpduConstPtrType                  RxIPduConstPtr;
   Com_RxSigConstPtrType                   RxSigConstPtr;
#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
   Com_RxSigRamPtrType                     RxSigRamPtr;
#endif
   VAR(uint16_least, AUTOMATIC)            Idx_Sig_ui;
   VAR(Com_MainFuncType,AUTOMATIC)         RxMainFuncId;

   VAR(boolean, AUTOMATIC)                 isGwSigUpdated_b;

   isGwSigUpdated_b = COM_FALSE;

    RxIPduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxMainFuncId     = RxIPduConstPtr->MainFunctionRef;

    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
    RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
#endif
   for(Idx_Sig_ui = RxIPduConstPtr->No_Of_Sig_Ref; Idx_Sig_ui != 0u; Idx_Sig_ui--)
   {

#ifdef COM_RxSigUpdateBit
        if(Com_GetValue(GEN,_UPDBITCONF,RxSigConstPtr->General) == COM_FALSE)
#endif
        {

            if(Com_GetValue(RXSIG,_TOACTION,RxSigConstPtr->rxSignalFields))
            {
                VAR(Com_SigMaxType, AUTOMATIC) RxSigVal;
#if(defined(COM_RXSIG_INT64) || defined(COM_RXSIG_FLOAT64SUPP))
                VAR(uint8,AUTOMATIC)           Type;

                Type     = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif
                RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

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
LOCAL_INLINE FUNC(boolean,COM_CODE) Com_Lok_IPduBasedSigGrpTimeoutAction( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   RxPduId )
{
   Com_RxIpduConstPtrType                  RxIPduConstPtr;
#ifdef COM_RX_SIGNALGROUP
   Com_RxSigGrpConstPtrType                RxSigGrpConstPtr;
#if defined(COM_SIGNALGROUPGATEWAY) || (defined(COM_RxFilters) && defined(COM_F_MASKEDNEWDIFFERSOLD))
   Com_RxSigGrpRamPtrType                  RxSigGrpRamPtr;
#endif
#endif
   VAR(uint16_least, AUTOMATIC)            Idx_SigGrp_ui;

   VAR(boolean, AUTOMATIC)                 isGwSigUpdated_b;

   isGwSigUpdated_b = COM_FALSE;

    RxIPduConstPtr   = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

#if defined(COM_SIGNALGROUPGATEWAY) || (defined COM_RxFilters && defined COM_F_MASKEDNEWDIFFERSOLD)
    RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);
#endif
   for(Idx_SigGrp_ui = RxIPduConstPtr->No_Of_SigGrp_Ref; Idx_SigGrp_ui != 0u; Idx_SigGrp_ui--)
   {

#ifdef COM_RxSigGrpUpdateBit
        if(Com_GetValue(RXSIGGRP,_UPDBITCONF,RxSigGrpConstPtr->rxSignalGrpFields) == COM_FALSE)
#endif
        {

            if(Com_GetValue(RXSIGGRP,_TOACTION,RxSigGrpConstPtr->rxSignalGrpFields))
            {

                Com_Lok_SigGrpReplaceToInit( RxSigGrpConstPtr, RxIPduConstPtr->MainFunctionRef );
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

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_SigBasedTimeoutMonitoring( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)  RxPduId )
{
   Com_RxIpduConstPtrType                                      RxIPduConstPtr;
   Com_RxSigConstPtrType                                       RxSigConstPtr;
#if(defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)))
   Com_RxSigRamPtrType                                         RxSigRamPtr;
#endif
   P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST)   SigTimeOutConfigPtr;
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)                     SigTimeOutTicksPtr;
   VAR(uint16_least, AUTOMATIC)                                NoOfSigOrSigGrp_ui;
   VAR(uint16_least, AUTOMATIC)                                Idx_Sig_ui;
   VAR(Com_MainFuncType,AUTOMATIC)                             RxMainFuncId;
#ifdef COM_RxUpdateTimeoutNotify
   VAR(boolean, AUTOMATIC)                                     CallTOSigNotify_b;
#endif

   VAR(boolean, AUTOMATIC)                                     isGwSigUpdated_b;

   isGwSigUpdated_b    = COM_FALSE;

    RxIPduConstPtr      = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxMainFuncId        = RxIPduConstPtr->MainFunctionRef;

    NoOfSigOrSigGrp_ui  = RxIPduConstPtr->SignalTimeout_Ref->numWithUpdateBit;

    SigTimeOutConfigPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;

    SigTimeOutTicksPtr  = RxIPduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;

   for(Idx_Sig_ui = NoOfSigOrSigGrp_ui; Idx_Sig_ui != 0u; Idx_Sig_ui--)
   {
#ifdef COM_RxUpdateTimeoutNotify

        CallTOSigNotify_b = COM_FALSE;
#endif
        RxSigConstPtr     = COM_GET_RXSIG_CONSTDATA(SigTimeOutConfigPtr->SigId);

#if(defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)))
        RxSigRamPtr       = &COM_GET_RXSIGNALFLAG(SigTimeOutConfigPtr->SigId);
#endif

        SchM_Enter_Com_RxSigToTicks();
        if(((*SigTimeOutTicksPtr) != COM_RXTIMER_MAX) && ((*SigTimeOutTicksPtr) != 0u))
        {
            --(*SigTimeOutTicksPtr);
        }

        if((*SigTimeOutTicksPtr) == 0x00)
        {

            (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout;

            if(Com_GetValue(RXSIG,_TOACTION,RxSigConstPtr->rxSignalFields))
            {
                VAR(Com_SigMaxType, AUTOMATIC) RxSigVal;
#if(defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP ))
                VAR(uint8,AUTOMATIC)           Type;

                Type     = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif
                RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

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
        SchM_Exit_Com_RxSigToTicks();

#ifdef COM_RxUpdateTimeoutNotify

        if((CallTOSigNotify_b != COM_FALSE) &&
            (SigTimeOutConfigPtr->TimeOutNotification_Cbk != NULL_PTR))
        {
            SigTimeOutConfigPtr->TimeOutNotification_Cbk();
        }
#endif

        SigTimeOutConfigPtr++;
        SigTimeOutTicksPtr++;
   }

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_RxSigGrpUpdateTimeout

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_SigGrpBasedTimeoutMonitoring( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) RxPduId )
{
   Com_RxIpduConstPtrType                                      RxIPduConstPtr;
   Com_RxSigGrpConstPtrType                                    RxSigGrpConstPtr;
#if defined (COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
   Com_RxSigGrpRamPtrType                                      RxSigGrpRamPtr;
#endif
   P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST)   SigTimeOutConfigPtr;
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)                     SigTimeOutTicksPtr;
   VAR(uint16_least, AUTOMATIC)                                NoOfSigOrSigGrp_ui;
   VAR(uint16_least, AUTOMATIC)                                Idx_Sig_ui;
   VAR(Com_MainFuncType,AUTOMATIC)                             RxMainFuncId;
#ifdef COM_RxUpdateTimeoutNotify

   VAR(boolean, AUTOMATIC)                                     CallTOSigGrpNotify_b;
#endif

   VAR(boolean, AUTOMATIC)                                     isGwSigUpdated_b;

   isGwSigUpdated_b    = COM_FALSE;

    RxIPduConstPtr      = COM_GET_RX_IPDU_CONSTDATA(RxPduId);
    RxMainFuncId        = RxIPduConstPtr->MainFunctionRef;

    NoOfSigOrSigGrp_ui  = RxIPduConstPtr->SignalGrpTimeout_Ref->numWithUpdateBit;

    SigTimeOutConfigPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;

    SigTimeOutTicksPtr  = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;

   for(Idx_Sig_ui = NoOfSigOrSigGrp_ui; Idx_Sig_ui != 0u; Idx_Sig_ui--)
   {
#ifdef COM_RxUpdateTimeoutNotify

        CallTOSigGrpNotify_b = COM_FALSE;
#endif

#if defined(COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
        RxSigGrpRamPtr       = &COM_GET_RXSIGGRPFLAG(SigTimeOutConfigPtr->SigId);
#endif

        SchM_Enter_Com_RxSigGrpToTicks();
        if(((*SigTimeOutTicksPtr) != COM_RXTIMER_MAX) && ((*SigTimeOutTicksPtr) != 0u))
        {
            --(*SigTimeOutTicksPtr);
        }

        if((*SigTimeOutTicksPtr) == 0x00)
        {

            (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout;

            RxSigGrpConstPtr      = COM_GET_RXSIGGRP_CONSTDATA(SigTimeOutConfigPtr->SigId);

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
        SchM_Exit_Com_RxSigGrpToTicks();

#ifdef COM_RxUpdateTimeoutNotify

        if((CallTOSigGrpNotify_b != COM_FALSE) &&
            (SigTimeOutConfigPtr->TimeOutNotification_Cbk != NULL_PTR))
        {
            SigTimeOutConfigPtr->TimeOutNotification_Cbk();
        }
#endif

        SigTimeOutConfigPtr++;
        SigTimeOutTicksPtr++;
   }

    return isGwSigUpdated_b;
}
#endif

#ifdef COM_PROVIDE_IPDU_STATUS

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_ProvideRxIpduStatus(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId)
{
   VAR(boolean, AUTOMATIC) pduStatus_b;

   if(PduId < CfgSwcServiceCom_dNumIPduRx)
   {

        PduId = COM_GET_RX_IPDU_ID(PduId);

        pduStatus_b = Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)PduId);
   }
   else{
        pduStatus_b  = COM_FALSE;
   }

    return(pduStatus_b);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif
