#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
LOCAL_INLINE FUNC(uint8, COM_CODE) Com_Lok_SendDynSignal(   VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(uint16, AUTOMATIC) Length);
LOCAL_INLINE FUNC(uint8, COM_CODE) Com_Lok_CopyDynSignal(   VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(uint16, AUTOMATIC) Length);
#endif

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_SendDynSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(uint16, AUTOMATIC) Length)
{

   Com_TxIpduRamPtrType            TxIpduRamPtr;
   Com_TxSigConstPtrType           TxSigConstPtr;
   VAR(uint16_least, AUTOMATIC)    IpduId_ui;
   VAR(uint8, AUTOMATIC)           ConstByteValue_u8;
   VAR(uint8, AUTOMATIC)           Status;
   VAR(uint8, AUTOMATIC)           Type;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_TX_SIGNALS), (SignalDataPtr == NULL_PTR)
   ,     COMServiceId_SendDynSignal ))
#endif
   {

        SignalId = COM_GET_TXSIGNAL_ID(SignalId);

        TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(SignalId);
        ConstByteValue_u8   = TxSigConstPtr->General;

        Type                = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
        IpduId_ui           = TxSigConstPtr->IpduRef;
        TxIpduRamPtr        = &COM_GET_TXPDURAM_S(IpduId_ui);

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

#endif

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

LOCAL_INLINE FUNC(uint8, COM_CODE) Com_Lok_SendDynSignal(   VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(uint16, AUTOMATIC) Length)
{

   Com_TxSigConstPtrType           TxSigConstPtr;
#if defined(COM_TxFilters) || defined(COM_TxIPduTimeOut) || defined(COM_SigTriggeredWithoutRepetition)

   VAR(uint16, AUTOMAIC)           ConstByteValue_u16;
#endif
   VAR(uint16_least, AUTOMATIC)    IpduId_ui;
   VAR(uint8, AUTOMATIC)           Status;
   VAR(uint8, AUTOMATIC)           isSigTriggered_u8;

    Status              = E_OK;

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(SignalId);
#if defined(COM_TxFilters) || defined(COM_TxIPduTimeOut) || defined(COM_SigTriggeredWithoutRepetition)

   ConstByteValue_u16  = TxSigConstPtr->txSignalFields;
#endif
    IpduId_ui           = TxSigConstPtr->IpduRef;

   isSigTriggered_u8 = Com_Lok_CopyDynSignal(SignalId, SignalDataPtr, Length);

   if(Com_CheckTxIPduStatus((Type_CfgSwcServiceCom_tIdIPdu)IpduId_ui))
   {

        VAR(Com_SendIpduInfo,AUTOMATIC) sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        sendIpduFlag_u16.sigTransProp = isSigTriggered_u8;

#ifdef COM_TxFilters

        if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u16) != (uint16)COM_NOTCONFIGURED)
        {

            if(Com_Lok_SigTxChangeMode(SignalId,0))
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

        Com_Lok_ProceedToSendIpdu( (Type_CfgSwcServiceCom_tIdIPdu)IpduId_ui, sendIpduFlag_u16 );

   }
   else{
        Status = COM_SERVICE_NOT_AVAILABLE;
   }
    return Status;
}

#endif

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

LOCAL_INLINE FUNC(uint8, COM_CODE) Com_Lok_CopyDynSignal(   VAR(Com_SignalIdType, AUTOMATIC) SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(uint16, AUTOMATIC) Length)
{

   Com_TxIpduRamPtrType            TxIpduRamPtr;
   Com_TxIpduConstPtrType          TxIPduConstPtr;
   Com_TxSigConstPtrType           TxSigConstPtr;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)   ByteNo_u8;

   VAR(uint16, AUTOMAIC)           ConstByteValue_u16;
   VAR(uint16_least, AUTOMATIC)    IpduId_ui;
#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition)

   VAR(uint8, AUTOMATIC)           TxSigTP_u8;
#endif
   VAR(uint8, AUTOMATIC)           isSigTriggered_u8;

   isSigTriggered_u8   = COM_RESET;

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(SignalId);

   ConstByteValue_u16  = TxSigConstPtr->txSignalFields;

    IpduId_ui           = TxSigConstPtr->IpduRef;
    TxIPduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);
    TxIpduRamPtr        = &COM_GET_TXPDURAM_S(IpduId_ui);

    SchM_Enter_Com_TxIpduProtArea(SENDDYNSIGNAL);

#ifdef COM_TxSigUpdateBit

   if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
   {

        ByteNo_u8 = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Update_Bit_Pos >> 3u);

        Com_SetUpdateBitValue(TxIPduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_u8)
   }
#endif
   if(Length != 0)
   {

        ByteNo_u8 = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Bit_Pos >> 3u);

        Com_ByteCopy((TxIPduConstPtr->BuffPtr + ByteNo_u8),(const uint8*)SignalDataPtr,(uint32)Length);
   }

    TxIpduRamPtr->Com_DynLength= Length;
    SchM_Exit_Com_TxIpduProtArea(SENDDYNSIGNAL);

#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition)

    TxSigTP_u8 = (uint8)Com_GetValue(TXSIG,_TP,ConstByteValue_u16);

   if(COM_SIG_TP_IS_TRIGGERED(TxSigTP_u8))
   {
        isSigTriggered_u8 = COM_SET;
   }
#endif
    return isSigTriggered_u8;
}

#endif

