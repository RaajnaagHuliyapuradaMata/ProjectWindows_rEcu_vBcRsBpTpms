

#include "Com_Prv.hpp"
#include "PduR_Com.hpp"

#if(COM_ENABLE_INTER_MODULE_CHECKS)

#if(!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

LOCAL_INLINE boolean Com_Lok_LoadPeriodicModeInfo(PduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16);

LOCAL_INLINE boolean Com_Lok_LoadEventModeInfo(PduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16);

LOCAL_INLINE PduLengthType Com_Lok_CalculateTxPduLength(PduIdType ComTxPduId);

LOCAL_INLINE void Com_Lok_ProcessTxReqStatus(PduIdType ComTxPduId, Std_ReturnType ipduTransStatus_ui);

LOCAL_INLINE void Com_Lok_LoadMinimumDelayTime(Com_TxIpduRamPtrType TxIpduRamPtr, Com_TxIpduConstPtrType TxIpduConstPtr);

#ifdef COM_TX_IPDUCOUNTER

LOCAL_INLINE void Com_Lok_TxIpduIncrementCounter(PduIdType ComTxPduId);
LOCAL_INLINE void Com_Lok_TxIpduDecrementCounter(PduIdType ComTxPduId);

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_Lok_SendIpdu(PduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   boolean                     SendIpdu_b;

    SendIpdu_b     = COM_FALSE;

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

   Com_Get_SchM_Enter_Com_TxIPdu
   Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS)

   if(sendIpduFlag_u16.isEventTrig != COM_RESET)
   {
        boolean isEventMode;

        TxIpduRamPtr->Com_n_Tick_Tx = COM_ZERO;

        if(sendIpduFlag_u16.isModeChangd == COM_SET)
        {

            isEventMode = Com_Lok_LoadPeriodicModeInfo(ComTxPduId, sendIpduFlag_u16);
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

        Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxIPduTimeOut

        if((COM_TX_MODE_IS_CYCLIC(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode))) &&
           (TxIpduConstPtr->Timeout_Fact != COM_ZERO))
        {
            if(Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) != COM_START)
            {

                Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);

                TxIpduRamPtr->Com_TickTxTimeout = TxIpduConstPtr->Timeout_Fact;
            }
        }
#endif

   }

   Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS)

   if(SendIpdu_b == COM_TRUE)
   {
        PduInfoType         ComTxIPduInfo;
        Std_ReturnType      ipduTransStatus_ui;
#ifdef COM_TxIPduCallOuts
        boolean             isTransmitCallout_b;
        boolean             ipduCalloutStatus;
#endif

        ComTxIPduInfo.SduDataPtr = TxIpduConstPtr->BuffPtr;
        ComTxIPduInfo.SduLength  = Com_Lok_CalculateTxPduLength( ComTxPduId );

#ifdef COM_TxIPduCallOuts

        isTransmitCallout_b = !(Com_GetValue(TXIPDU,_ISCALLOUTFRMTRIGTRANS,TxIpduConstPtr->txIPduFields));

        if((TxIpduConstPtr->CallOut != NULL_PTR) && (isTransmitCallout_b))
        {
            Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA)
            ipduCalloutStatus = TxIpduConstPtr->CallOut(ComTxPduId, &ComTxIPduInfo);
            Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA)
        }
        else{
            ipduCalloutStatus = COM_TRUE;
        }

        if(ipduCalloutStatus == COM_TRUE)
#endif
        {
#ifdef COM_TX_IPDUCOUNTER

            if(TxIpduConstPtr->TxIpduCntr_Index != COM_TXIPDU_CNTR_INV_IDX)
            {
                Com_Lok_TxIpduIncrementCounter( ComTxPduId );
            }
            else{

            }
#endif

#ifdef COM_MULTICORE_SUPPORT
            Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA)
#else
            Com_Get_SchM_Exit_Com_TxIPdu
#endif

            ipduTransStatus_ui = PduR_ComTransmit(TxIpduConstPtr->PdurId, &ComTxIPduInfo);

#ifdef COM_MULTICORE_SUPPORT
            Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA)
#else
            Com_Get_SchM_Enter_Com_TxIPdu
#endif

            Com_Lok_ProcessTxReqStatus(ComTxPduId, ipduTransStatus_ui);
        }
#ifdef COM_TxIPduCallOuts
        else{

        }
#endif

   }
   Com_Get_SchM_Exit_Com_TxIPdu
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE boolean Com_Lok_LoadPeriodicModeInfo(PduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16)
{
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   boolean                     isEventMode;

   isEventMode  = COM_FALSE;

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);

    TxIpduRamPtr->Com_n = COM_ZERO;

   switch(Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode))
   {
        case COM_TXMODE_PERIODIC:
        {
            if(sendIpduFlag_u16.isSwtIpduTxMode != COM_SET)
            {

                TxIpduRamPtr->Com_Tick_Tx = COM_ONE;
            }
            else{

                TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, TxIpduRamPtr->CurrentTxModePtr);
            }
        }
        break;

        case COM_TXMODE_DIRECT:
        {

            isEventMode = COM_TRUE;
        }
        break;

        case COM_TXMODE_MIXED:
        {

            if(sendIpduFlag_u16.isSigTriggered != COM_SET)
            {
                if(sendIpduFlag_u16.isSwtIpduTxMode != COM_SET)
                {

                    TxIpduRamPtr->Com_Tick_Tx = COM_ONE;
                }
                else{

                    TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEOFFSET(ComTxPduId, TxIpduRamPtr->CurrentTxModePtr);
                }
            }
            else{

                TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, TxIpduRamPtr->CurrentTxModePtr);

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

LOCAL_INLINE boolean Com_Lok_LoadEventModeInfo(PduIdType ComTxPduId, Com_SendIpduInfo sendIpduFlag_u16)
{
#ifdef COM_TxIPduTimeOut
   Com_TxIpduConstPtrType      TxIpduConstPtr;
#endif
   Com_TxIpduRamPtrType        TxIpduRamPtr;
   boolean                     SendIpdu_b;

    SendIpdu_b     = COM_FALSE;

#ifdef COM_TxIPduTimeOut
    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
#endif
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

   if(sendIpduFlag_u16.ignoreRepetitions != COM_SET)
   {

        TxIpduRamPtr->Com_n = COM_GET_TXIPDU_NUMOFREPETITION(ComTxPduId, TxIpduRamPtr->CurrentTxModePtr);
   }
   else{

        TxIpduRamPtr->Com_n = COM_ZERO;
   }

#ifdef COM_TxIPduTimeOut

   if(sendIpduFlag_u16.isTimeoutReq == COM_SET)
   {

        Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);

        TxIpduRamPtr->Com_TickTxTimeout = (TxIpduConstPtr->Timeout_Fact + COM_ONE);
   }
#endif

   if((TxIpduRamPtr->Com_MinDelayTick == COM_ZERO) &&
        (Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_FALSE))
   {

        if(TxIpduRamPtr->Com_n == COM_ZERO)
        {

#ifdef COM_MIXEDPHASESHIFT

            if(Com_GetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode))
            {
                TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, TxIpduRamPtr->CurrentTxModePtr);

                TxIpduRamPtr->Com_Tick_Tx++;
            }
#endif

            Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

#ifdef COM_TXPDU_DEFERREDPROCESSING

            TxIpduRamPtr->Com_n_Tick_Tx = COM_ONE;
#else

            SendIpdu_b = COM_TRUE;

#endif

        }
        else{

            TxIpduRamPtr->Com_n_Tick_Tx = COM_ONE;

        }
   }
   else{

        Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);

#ifdef COM_MIXEDPHASESHIFT
        if(Com_GetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode))
        {
            TxIpduRamPtr->Com_Tick_Tx = COM_GET_TXIPDU_TIMEPERIOD(ComTxPduId, TxIpduRamPtr->CurrentTxModePtr);
        }
#endif

   }

#if(COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION == STD_OFF)

   Com_SetRamValue(TXIPDU,_MDTLOAD,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
#endif

    return SendIpdu_b;
}

LOCAL_INLINE PduLengthType Com_Lok_CalculateTxPduLength(PduIdType ComTxPduId)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
#if defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_METADATA_SUPPORT)
   Com_TxIpduRamPtrType        TxIpduRamPtr;
#endif
   PduLengthType               comTxPduLength;

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
#if defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_METADATA_SUPPORT)
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);
#endif
   comTxPduLength = TxIpduConstPtr->Size;

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

   if(Com_GetValue(TXIPDU,_ISDYNIPDU,TxIpduConstPtr->txIPduFields))
   {
        Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA)

        comTxPduLength += (PduLengthType)TxIpduRamPtr->Com_DynLength;

        Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA)
   }
   else
#endif
#ifdef COM_METADATA_SUPPORT

   if(TxIpduConstPtr->MetaDataPtr != NULL_PTR)
   {
        Com_MetaDataInfoPtr MetaDataInfoPtr;

        MetaDataInfoPtr = TxIpduConstPtr->MetaDataPtr;

        comTxPduLength += MetaDataInfoPtr->MetaDataLength;

        Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA)

        if(Com_GetRamValue(TXIPDU,_METADATA_REQUEST,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
        {

            Com_ByteCopy( (TxIpduConstPtr->BuffPtr + TxIpduConstPtr->Size)
   ,                         (&MetaDataInfoPtr->MetaDataDefaultValue[0])
   ,                         ( MetaDataInfoPtr->MetaDataLength) );
        }
        else{

            Com_SetRamValue(TXIPDU,_METADATA_REQUEST,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }

        Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA)
   }
   else
#endif
   {

   }

#ifdef COM_TP_IPDUTYPE

   COM_GET_TPTXIPDULENGTH_AUO(ComTxPduId) = comTxPduLength;
#endif

    return comTxPduLength;
}

LOCAL_INLINE void Com_Lok_ProcessTxReqStatus(PduIdType ComTxPduId, Std_ReturnType ipduTransStatus_ui)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxIpduRamPtrType        TxIpduRamPtr;

    TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(ComTxPduId);

   Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS)
#if(COM_RETRY_FAILED_TX_REQUESTS == STD_OFF)

   Com_Lok_LoadMinimumDelayTime(TxIpduRamPtr, TxIpduConstPtr);
#endif
   if(ipduTransStatus_ui == E_OK)
   {

#if(COM_RETRY_FAILED_TX_REQUESTS == STD_ON)

        Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

        Com_Lok_LoadMinimumDelayTime(TxIpduRamPtr, TxIpduConstPtr);
#endif

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        if(Com_GetValue(TXIPDU,_CLRUPDBIT,TxIpduConstPtr->txIPduFields) == (uint16)COM_CLRUPDATEBIT_TRANSMIT)
        {
            Com_Lok_ClearUpdateBits(TxIpduConstPtr);
        }
#endif

#ifdef COM_TP_IPDUTYPE
        if(Com_GetValue(TXIPDU,_ISLARGEDATAPDU,TxIpduConstPtr->txIPduFields))
        {

            Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
            TxIpduRamPtr->TxTPIPduLength = COM_ZERO;
        }
#endif
   }
   else{

#ifdef COM_TX_IPDUCOUNTER

        if(TxIpduConstPtr->TxIpduCntr_Index != COM_TXIPDU_CNTR_INV_IDX)
        {
            Com_Lok_TxIpduDecrementCounter( ComTxPduId );
        }
#endif

#if(COM_RETRY_FAILED_TX_REQUESTS == STD_ON)

        Com_SetRamValue(TXIPDU,_RETRYFAILEDTXREQ,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
#endif

   }

   Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS)
}

LOCAL_INLINE void Com_Lok_LoadMinimumDelayTime(Com_TxIpduRamPtrType TxIpduRamPtr, Com_TxIpduConstPtrType TxIpduConstPtr)
{

   if((TxIpduConstPtr->Min_Delay_Time_Fact != COM_ZERO) && (TxIpduRamPtr->Com_MinDelayTick == COM_ZERO))
   {
#if(COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION == STD_OFF)
        if(Com_GetRamValue(TXIPDU,_MDTLOAD,TxIpduRamPtr->Com_TxFlags))
        {

            Com_SetRamValue(TXIPDU,_MDTLOAD,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

#ifdef COM_TXPDU_DEFERREDPROCESSING

            TxIpduRamPtr->Com_MinDelayTick = TxIpduConstPtr->Min_Delay_Time_Fact;
#else

            TxIpduRamPtr->Com_MinDelayTick = TxIpduConstPtr->Min_Delay_Time_Fact +
                                (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) ? COM_ONE : COM_ZERO);
#endif

#if(COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION == STD_OFF)
        }
#endif
   }
}

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_Lok_ClearUpdateBits(Com_TxIpduConstPtrType TxIpduConstPtr)
{
#ifdef COM_TxSigUpdateBit
   Com_TxSigConstPtrType           TxSigConstPtr;
#endif
#ifdef COM_TxSigGrpUpdateBit
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
#endif
   uint16_least                    index_u16;
   PduLengthType                   byteNo_uo;

#ifdef COM_TxSigUpdateBit

    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIpduConstPtr->TxSigId_Index);

   for(index_u16 = TxIpduConstPtr->No_Of_Sig_Ref; index_u16 != COM_ZERO; index_u16--)
   {

        if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
        {

            byteNo_uo = (PduLengthType)((TxSigConstPtr->Update_Bit_Pos) >> 3u);

            Com_ClearUpdateBitValue(TxIpduConstPtr, TxSigConstPtr->Update_Bit_Pos, byteNo_uo)
        }
        TxSigConstPtr++;
   }
#endif

#ifdef COM_TxSigGrpUpdateBit

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIpduConstPtr->FirstTxSigGrp_Index);

   for(index_u16 = TxIpduConstPtr->No_Of_SigGrp_Ref; index_u16 != COM_ZERO; index_u16--)
   {

        if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
        {

            byteNo_uo = (PduLengthType)((TxSigGrpConstPtr->Update_Bit_Pos) >> 3u);

            Com_ClearUpdateBitValue(TxIpduConstPtr, TxSigGrpConstPtr->Update_Bit_Pos, byteNo_uo)
        }
        TxSigGrpConstPtr++;
   }
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#ifdef COM_TX_IPDUCOUNTER

LOCAL_INLINE void Com_Lok_TxIpduIncrementCounter(PduIdType ComTxPduId)
{
   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxIpduCntrConstPtrType      TxIpduCntrConstPtr;
   uint8 *                         counterBytePtr;
   uint8                           counterValue_u8;
   uint8                           counterBitOffset_u8;

    TxIpduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduCntrConstPtr  = COM_GET_TX_IPDU_CNTR_CONSTDATA(TxIpduConstPtr->TxIpduCntr_Index);

   counterBytePtr      = (uint8 *)(TxIpduConstPtr->BuffPtr + (TxIpduCntrConstPtr->CntrBitPos / 8u));
   counterBitOffset_u8 = (uint8)(TxIpduCntrConstPtr->CntrBitPos % 8u);

   Com_Get_SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA)

   counterValue_u8 = (uint8)((uint16)COM_GET_TXIPDU_CNTR_VAL(TxIpduConstPtr->TxIpduCntr_Index) + COM_ONE);

   if((uint16)counterValue_u8 < COM_GET_BASE_2_POWER_X(TxIpduCntrConstPtr->CntrBitSize))
   {

   }
   else{

        counterValue_u8 = COM_ZERO;
   }

   COM_PACK_CNTR_INTO_IPDU_BUFF((uint8 *)(counterBytePtr), counterBitOffset_u8
   ,                                          TxIpduCntrConstPtr->CntrBitSize, counterValue_u8);

   COM_GET_TXIPDU_CNTR_VAL(TxIpduConstPtr->TxIpduCntr_Index) = counterValue_u8;

   Com_Get_SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA)
}

LOCAL_INLINE void Com_Lok_TxIpduDecrementCounter(PduIdType ComTxPduId)
{
   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxIpduCntrConstPtrType      TxIpduCntrConstPtr;
   uint8 *                         counterBytePtr;
   uint8                           counterValue_u8;
   uint8                           counterBitOffset_u8;

    TxIpduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);
    TxIpduCntrConstPtr  = COM_GET_TX_IPDU_CNTR_CONSTDATA(TxIpduConstPtr->TxIpduCntr_Index);

   counterBytePtr      = (uint8 *)(TxIpduConstPtr->BuffPtr + (TxIpduCntrConstPtr->CntrBitPos / 8u));
   counterBitOffset_u8 = (uint8)(TxIpduCntrConstPtr->CntrBitPos % 8u);

   counterValue_u8 = COM_GET_TXIPDU_CNTR_VAL(TxIpduConstPtr->TxIpduCntr_Index);

   if(counterValue_u8 != COM_ZERO)
   {
        counterValue_u8--;
   }
   else{

        counterValue_u8 = (uint8)COM_MAX_U_VALUE_OF_X_BITS(TxIpduCntrConstPtr->CntrBitSize);
   }

   COM_PACK_CNTR_INTO_IPDU_BUFF((uint8 *)(counterBytePtr), counterBitOffset_u8
   ,                                TxIpduCntrConstPtr->CntrBitSize, counterValue_u8);

   COM_GET_TXIPDU_CNTR_VAL(TxIpduConstPtr->TxIpduCntr_Index) = counterValue_u8;
}

#endif

