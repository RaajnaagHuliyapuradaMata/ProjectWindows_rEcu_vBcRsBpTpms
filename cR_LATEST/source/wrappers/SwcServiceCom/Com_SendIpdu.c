#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "PduR_Com.hpp"

#if(!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadPeriodicModeInfo(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)           ComTxPduId
   ,     VAR(uint8, AUTOMATIC)               isSigTriggered
                                                                 );

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadEventModeInfo(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)           ComTxPduId
   ,     VAR(Com_SendIpduInfo, AUTOMATIC)    sendIpduFlag_u16
                                                              );

LOCAL_INLINE FUNC(Type_SwcServiceCom_tLengthPdu, COM_CODE) Com_Lok_CalculateTxPduLength(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)           ComTxPduId
   ,     VAR(uint8, AUTOMATIC)               isTrigIpduSendWithMetadata
                                                                       );

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessTxReqStatus(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)           ComTxPduId
   ,     VAR(Std_ReturnType, AUTOMATIC)      ipduTransStatus_ui
                                                            );

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_Lok_SendIpdu(
                            VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)           ComTxPduId
   ,     VAR(Com_SendIpduInfo, AUTOMATIC)    sendIpduFlag_u16
                                     )
{
   Com_TxIpduConstPtrType  TxIPduConstPtr;
   Com_TxIpduRamPtrType    TxIpduRamPtr;
   VAR(boolean,AUTOMATIC)  SendIpdu_b;

    SendIpdu_b     = COM_FALSE;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

    SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);

   if(sendIpduFlag_u16.isEventTrig != COM_RESET)
   {
        VAR(boolean,AUTOMATIC) isEventMode;

        TxIpduRamPtr->Com_n_Tick_Tx = 0;

        if(sendIpduFlag_u16.isModeChangd == COM_SET)
        {

            isEventMode = Com_Lok_LoadPeriodicModeInfo(ComTxPduId, sendIpduFlag_u16.sigTransProp);
        }
        else{

            isEventMode = COM_TRUE;
        }

        if(isEventMode == COM_TRUE)
        {
            SendIpdu_b = Com_Lok_LoadEventModeInfo(ComTxPduId, sendIpduFlag_u16);
        }
   }

   else{

        SendIpdu_b = COM_TRUE;

#ifdef COM_TxIPduTimeOut

        if(sendIpduFlag_u16.isTimeoutReq == COM_SET)
        {
            if(Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) != COM_START)
            {

                Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);

                TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
            }
        }
#endif

   }

    SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);

   if(SendIpdu_b == COM_TRUE)
   {
        VAR(Type_SwcServiceCom_stInfoPdu, COM_VAR)       ComTxIPduInfo;
        VAR(Std_ReturnType, AUTOMATIC)  ipduTransStatus_ui;
#ifdef COM_TxIPduCallOuts
        VAR(boolean, AUTOMATIC)         isTransmitCallout_b;
        VAR(boolean, AUTOMATIC)         ipduCalloutStatus;
#endif

        ComTxIPduInfo.SduDataPtr = TxIPduConstPtr->BuffPtr;
        ComTxIPduInfo.SduLength  = Com_Lok_CalculateTxPduLength( ComTxPduId
   ,     sendIpduFlag_u16.isTriggerIpduSendWithMetadata );

#ifdef COM_TxIPduCallOuts

        isTransmitCallout_b = !(Com_GetValue(TXIPDU,_ISCALLOUTFRMTRIGTRANS,TxIPduConstPtr->txIPduFields));

        if((TxIPduConstPtr->CallOut != NULL_PTR) && (isTransmitCallout_b))
        {
            SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);
            ipduCalloutStatus = TxIPduConstPtr->CallOut(ComTxPduId, &ComTxIPduInfo);
            SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
        }
        else{
            ipduCalloutStatus = COM_TRUE;
        }

        if(ipduCalloutStatus == COM_TRUE)
#endif
        {
#ifdef COM_MULTICORE_SUPPORT
            SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);
#endif

            ipduTransStatus_ui = PduR_ComTransmit(TxIPduConstPtr->PdurId, &ComTxIPduInfo);

#ifdef COM_MULTICORE_SUPPORT
            SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
#endif
        }
#ifdef COM_TxIPduCallOuts
        else{

            ipduTransStatus_ui = E_NOT_OK;
        }
#endif

        Com_Lok_ProcessTxReqStatus(ComTxPduId, ipduTransStatus_ui);
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadPeriodicModeInfo(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   ComTxPduId
   ,     VAR(uint8, AUTOMATIC)       isSigTriggered
                                                                 )
{
   Com_TxIpduRamPtrType    TxIpduRamPtr;
   VAR(boolean,AUTOMATIC)  isEventMode;

   isEventMode  = COM_FALSE;

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);

    TxIpduRamPtr->Com_n = 0;

   switch(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode))
   {
        case COM_TXMODE_PERIODIC:
        {

            TxIpduRamPtr->Com_Tick_Tx = 1;
        }
        break;

        case COM_TXMODE_DIRECT:
        {

            isEventMode = COM_TRUE;
        }
        break;

        case COM_TXMODE_MIXED:
        {

            if(isSigTriggered != COM_SET)
            {

                TxIpduRamPtr->Com_Tick_Tx = 1;
            }
            else{

                TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(((Type_SwcServiceCom_tIdPdu)ComTxPduId)
   ,     (TxIpduRamPtr->CurrentTxModePtr));

                TxIpduRamPtr->Com_Tick_Tx++;

                isEventMode = COM_TRUE;
            }
        }
        break;

        case COM_TXMODE_NONE:
        {

        }
        break;

        default:
        {

        }
        break;
   }

    return isEventMode;
}

LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Lok_LoadEventModeInfo(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)           ComTxPduId
   ,     VAR(Com_SendIpduInfo, AUTOMATIC)    sendIpduFlag_u16
                                                              )
{
#ifdef COM_TxIPduTimeOut
   Com_TxIpduConstPtrType  TxIPduConstPtr;
#endif
   Com_TxIpduRamPtrType    TxIpduRamPtr;
   VAR(boolean,AUTOMATIC)  SendIpdu_b;

    SendIpdu_b     = COM_FALSE;

#ifdef COM_TxIPduTimeOut
    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
#endif
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

   if(sendIpduFlag_u16.ignoreRepetitions != COM_SET)
   {

#ifdef COM_TXPDU_NUMOFREPETITION_VIA_CALIBRATION
        TxIpduRamPtr->Com_n = Com_GetTxIPduNumberOfRepetitionCalibration((Type_SwcServiceCom_tIdPdu)ComTxPduId);
#else

        TxIpduRamPtr->Com_n = TxIpduRamPtr->CurrentTxModePtr->NumOfRepetitions;

#endif

   }
   else{

        TxIpduRamPtr->Com_n = 0;
   }

#ifdef COM_TxIPduTimeOut

   if(sendIpduFlag_u16.isTimeoutReq == COM_SET)
   {

        Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);

        TxIpduRamPtr->Com_TickTxTimeout = (TxIPduConstPtr->Timeout_Fact + 1);
   }
#endif

   if((TxIpduRamPtr->Com_MinDelayTick == 0u) &&
        (Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_FALSE))
   {

        if(TxIpduRamPtr->Com_n == 0)
        {

#ifdef COM_MIXEDPHASESHIFT

            if(Com_GetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode))
            {
                TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(((Type_SwcServiceCom_tIdPdu)ComTxPduId)
   ,     (TxIpduRamPtr->CurrentTxModePtr));

                TxIpduRamPtr->Com_Tick_Tx++;
            }
#endif

            Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
            if(sendIpduFlag_u16.isGwIpduSend != COM_RESET)
            {

                SendIpdu_b = COM_TRUE;
            }
            else
#endif
            {

#ifdef COM_TXPDU_DEFERREDPROCESSING

                TxIpduRamPtr->Com_n_Tick_Tx = 1;

#else

                SendIpdu_b = COM_TRUE;

#endif

            }
        }
        else{

            TxIpduRamPtr->Com_n_Tick_Tx = 1;

        }
   }
   else{

        Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

#ifdef COM_MIXEDPHASESHIFT
        if(Com_GetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode))
        {
            TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(((Type_SwcServiceCom_tIdPdu)ComTxPduId)
   ,     (TxIpduRamPtr->CurrentTxModePtr));
        }
#endif

   }

    return SendIpdu_b;
}

LOCAL_INLINE FUNC(Type_SwcServiceCom_tLengthPdu, COM_CODE) Com_Lok_CalculateTxPduLength(
                                                        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)   ComTxPduId
   ,     VAR(uint8, AUTOMATIC)       isTrigIpduSendWithMetadata
                                                                       )
{
   Com_TxIpduConstPtrType          TxIPduConstPtr;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
   Com_TxIpduRamPtrType            TxIpduRamPtr;
#endif
   VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC)    comTxPduLength;

#ifndef COM_METADATA_SUPPORT
    (void)isTrigIpduSendWithMetadata;
#endif

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);
#endif
   comTxPduLength = TxIPduConstPtr->Size;

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

        if(Com_GetRamValue(TXIPDU,_ISDYNIPDU,TxIPduConstPtr->txIPduFields))
        {
            comTxPduLength += (Type_SwcServiceCom_tLengthPdu)TxIpduRamPtr->Com_DynLength;
        }
        else
#endif
        {
#ifdef COM_METADATA_SUPPORT

            if(Com_GetValue(TXIPDU,_ISMETADATASUPPORTED,TxIPduConstPtr->txIPduFields))
            {
                Com_MetaDataInfoPtr MetaDataInfoPtr;

                MetaDataInfoPtr = TxIPduConstPtr->MetaDataPtr;

                comTxPduLength += MetaDataInfoPtr->MetaDataLength;

                if(isTrigIpduSendWithMetadata != COM_SET)
                {
                    SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);

                    Com_ByteCopy( (TxIPduConstPtr->BuffPtr + TxIPduConstPtr->Size)
   ,     (&MetaDataInfoPtr->MetaDataDefaultValue[0])
   ,     ( MetaDataInfoPtr->MetaDataLength) );

                    SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
                }
            }
            else
#endif
            {

            }
        }

#ifdef COM_TP_IPDUTYPE

        COM_GET_TPTXIPDULENGTH_AUO(ComTxPduId) = comTxPduLength;
#endif

    return comTxPduLength;
}

LOCAL_INLINE FUNC(void, COM_CODE) Com_Lok_ProcessTxReqStatus(
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)       ComTxPduId
   ,     VAR(Std_ReturnType, AUTOMATIC)  ipduTransStatus_ui
                                                            )
{
   Com_TxIpduConstPtrType  TxIPduConstPtr;
   Com_TxIpduRamPtrType    TxIpduRamPtr;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

    SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);

   if(ipduTransStatus_ui == E_OK)
   {
#ifdef COM_RETRY_FAILED_TX_REQUESTS

        Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

        if((TxIPduConstPtr->Min_Delay_Time_Fact != 0u) && (TxIpduRamPtr->Com_MinDelayTick == 0u))
        {
            TxIpduRamPtr->Com_MinDelayTick = TxIPduConstPtr->Min_Delay_Time_Fact +
                                             (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) ? 1u : 0u);
        }

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        if(Com_GetValue(TXIPDU,_CLRUPDBIT,TxIPduConstPtr->txIPduFields) == (uint16)COM_CLRUPDATEBIT_TRANSMIT)
        {
            Com_Lok_ClearUpdateBits(TxIPduConstPtr);
        }
#endif

#ifdef COM_TP_IPDUTYPE
        if(Com_GetValue(TXIPDU,_ISLARGEDATAPDU,TxIPduConstPtr->txIPduFields))
        {

            Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
            TxIpduRamPtr->TxTPIPduLength = 0;
        }
#endif

   }
#ifdef COM_RETRY_FAILED_TX_REQUESTS
   else{

        Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
   }
#endif
    SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
}

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void,COM_CODE) Com_Lok_ClearUpdateBits( Com_TxIpduConstPtrType TxIPduConstPtr )
{
#ifdef COM_TxSigUpdateBit
   Com_TxSigConstPtrType           TxSigConstPtr;
#endif
#ifdef COM_TxSigGrpUpdateBit
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
#endif
   VAR(uint16_least, AUTOMATIC)    index_ui;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)   ByteNo_uo;

#ifdef COM_TxSigUpdateBit

    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

   for(index_ui = TxIPduConstPtr->No_Of_Sig_Ref; index_ui != 0u; index_ui--)
   {

        if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
        {

            ByteNo_uo = (Type_SwcServiceCom_tLengthPdu)((TxSigConstPtr->Update_Bit_Pos) >> 3u);

            Com_ClearUpdateBitValue(TxIPduConstPtr, TxSigConstPtr->Update_Bit_Pos, ByteNo_uo)
        }
        TxSigConstPtr++;
   }
#endif

#ifdef COM_TxSigGrpUpdateBit

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

   for(index_ui = TxIPduConstPtr->No_Of_SigGrp_Ref; index_ui != 0u; index_ui--)
   {

        if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
        {

            ByteNo_uo = (Type_SwcServiceCom_tLengthPdu)((TxSigGrpConstPtr->Update_Bit_Pos) >> 3u);

            Com_ClearUpdateBitValue(TxIPduConstPtr, TxSigGrpConstPtr->Update_Bit_Pos, ByteNo_uo)
        }
        TxSigGrpConstPtr++;
   }
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

