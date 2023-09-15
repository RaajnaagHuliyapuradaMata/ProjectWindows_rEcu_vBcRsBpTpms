

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

LOCAL_INLINE uint8 Com_Lok_SendDynSignal(Com_SignalIdType SignalId, const void * SignalDataPtr, uint16 Length);
LOCAL_INLINE uint8 Com_Lok_CopyDynSignal(Com_SignalIdType SignalId, const void * SignalDataPtr, uint16 Length);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
uint8 Com_SendDynSignal(Com_SignalIdType SignalId, const void * SignalDataPtr, uint16 Length)
{
#ifdef COM_TP_IPDUTYPE
   Com_TxIpduRamPtrType        TxIpduRamPtr;
#endif
   Com_TxSigConstPtrType       TxSigConstPtr;
   uint8                       Status;
   uint8                       Type;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_TX_SIGNALS), (SignalDataPtr == NULL_PTR)
   ,                                                                        COMServiceId_SendDynSignal ))
#endif
   {

        SignalId = COM_GET_TXSIGNAL_ID(SignalId);

        TxSigConstPtr  = COM_GET_TXSIG_CONSTDATA(SignalId);

        Type           = Com_GetValue(GEN,_TYPE,TxSigConstPtr->General);
#ifdef COM_TP_IPDUTYPE
        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(TxSigConstPtr->IpduRef);
#endif

#ifdef COM_TP_IPDUTYPE
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {
             Status = COM_BUSY;
        }
        else
#endif
        {

            if((Length <= TxSigConstPtr->BitSize) && ((uint8)COM_UINT8_DYN == Type))
            {
                Status = Com_Lok_SendDynSignal(SignalId, SignalDataPtr, Length);
            }
            else{
                Status = E_NOT_OK;
            }
        }
   }
    return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE uint8 Com_Lok_SendDynSignal(Com_SignalIdType SignalId, const void * SignalDataPtr, uint16 Length)
{
   Com_TxSigConstPtrType       TxSigConstPtr;
#if defined(COM_TxFilters) || defined(COM_TxIPduTimeOut) || defined(COM_SigTriggeredWithoutRepetition)
   uint16                      ConstByteValue_u16;
#endif
   uint16_least                IpduId_ui;
   uint8                       Status;
   uint8                       isSigTriggered_u8;

    Status              = E_OK;

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(SignalId);
#if defined(COM_TxFilters) || defined(COM_TxIPduTimeOut) || defined(COM_SigTriggeredWithoutRepetition)

   ConstByteValue_u16  = TxSigConstPtr->txSignalFields;
#endif
    IpduId_ui           = TxSigConstPtr->IpduRef;

   isSigTriggered_u8 = Com_Lok_CopyDynSignal(SignalId, SignalDataPtr, Length);

   if(Com_CheckTxIPduStatus((PduIdType)IpduId_ui))
   {

        Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        sendIpduFlag_u16.isSigTriggered = isSigTriggered_u8;

#ifdef COM_TxFilters

        if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u16) != (uint16)COM_NOTCONFIGURED)
        {

            if(Com_Lok_SigTxChangeMode(SignalId,COM_ZERO))
            {
                sendIpduFlag_u16.isModeChangd = COM_SET;
            }
        }
#endif

#ifdef COM_TxIPduTimeOut

        sendIpduFlag_u16.isTimeoutReq = COM_BOOL_TO_UNSIGNED(Com_GetValue(TXSIG,_TOENABLED,ConstByteValue_u16));
#endif

#ifdef COM_SigTriggeredWithoutRepetition
        if(COM_TRIGGERED_WITHOUT_REPETITION == Com_GetValue(TXSIG,_TP,ConstByteValue_u16))
        {

            sendIpduFlag_u16.ignoreRepetitions = COM_SET;
        }
#endif

        Com_Lok_ProceedToSendIpdu( (Com_IpduIdType)IpduId_ui, sendIpduFlag_u16 );

   }
   else{
        Status = COM_SERVICE_NOT_AVAILABLE;
   }
    return Status;
}

LOCAL_INLINE uint8 Com_Lok_CopyDynSignal(Com_SignalIdType SignalId, const void * SignalDataPtr, uint16 Length)
{

   Com_TxIpduRamPtrType        TxIpduRamPtr;
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
   PduLengthType               ByteNo_u8;

   uint16_least                IpduId_ui;
#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition)

   uint8                       TxSigTP_u8;
#endif
   uint8                       isSigTriggered_u8;

   isSigTriggered_u8   = COM_RESET;

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(SignalId);

    IpduId_ui           = TxSigConstPtr->IpduRef;
    TxIpduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);
    TxIpduRamPtr        = &COM_GET_TXPDURAM_S(IpduId_ui);

    SchM_Enter_Com_TxIpduProtArea(SENDDYNSIGNAL);

#ifdef COM_TxSigUpdateBit

   if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
   {

        ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Update_Bit_Pos >> 3u);

        Com_SetUpdateBitValue(TxIpduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_u8)
   }
#endif
   if(Length != COM_ZERO)
   {

        ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Bit_Pos >> 3u);

        Com_ByteCopy((TxIpduConstPtr->BuffPtr + ByteNo_u8), (const uint8*)SignalDataPtr, (uint32)Length);

   }

    TxIpduRamPtr->Com_DynLength= Length;
    SchM_Exit_Com_TxIpduProtArea(SENDDYNSIGNAL);

#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition)

    TxSigTP_u8 = (uint8)Com_GetValue(TXSIG,_TP,TxSigConstPtr->txSignalFields);

   if(COM_SIG_TP_IS_TRIGGERED(TxSigTP_u8))
   {
        isSigTriggered_u8 = COM_SET;
   }
#endif
    return isSigTriggered_u8;
}
#endif

