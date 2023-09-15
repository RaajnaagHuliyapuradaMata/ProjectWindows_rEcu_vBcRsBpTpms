

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

LOCAL_INLINE Com_SigMaxType Com_Lok_SigBufftoIpduBuff(Com_SignalIdType SignalId, const void * SignalDataPtr);

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
uint8 Com_SendSignal(Com_SignalIdType SignalId, const void * SignalDataPtr )
{
#ifdef COM_TP_IPDUTYPE
   Com_TxIpduRamPtrType        TxIpduRamPtr;
#endif
   uint8                       Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_TX_SIGNALS), (SignalDataPtr == NULL_PTR)
   ,                                                                           COMServiceId_SendSignal))
#endif
   {

        SignalId      = COM_GET_TXSIGNAL_ID(SignalId);

#ifdef COM_TP_IPDUTYPE
        TxIpduRamPtr  = &COM_GET_TXPDURAM_S( COM_GET_TXSIG_CONSTDATA( SignalId )->IpduRef );
#endif

#ifdef COM_TP_IPDUTYPE
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {

             Status = COM_BUSY;
        }
        else
#endif
        {
            Status = Com_InternalSendSignal(SignalId,SignalDataPtr);
        }
   }
    return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
uint8 Com_InternalSendSignal(Com_SignalIdType SignalId, const void * SignalDataPtr)
{
#ifdef COM_TxSigUpdateBit
   Com_TxIpduConstPtrType      TxIpduConstPtr;
#endif
   Com_TxSigConstPtrType       TxSigConstPtr;
   Com_SigMaxType              TxSigNewVal;
   uint16_least                IpduId_ui;
#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition) || defined(COM_EffectiveSigTOC) ||\
    defined(COM_TxFilters)    || defined(COM_TxIPduTimeOut)
   uint16                      ConstTxSignalFields_u16;
#endif
#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition) || defined(COM_EffectiveSigTOC)
   uint8                       TxSigTP_u8;
#endif
   uint8                       isSigTriggered_u8;
   uint8                       Status;

    Status                  = E_OK;
   isSigTriggered_u8       = COM_RESET;

    TxSigConstPtr           = COM_GET_TXSIG_CONSTDATA(SignalId);
    IpduId_ui               = TxSigConstPtr->IpduRef;
#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition) || defined(COM_EffectiveSigTOC) ||\
    defined(COM_TxFilters)    || defined(COM_TxIPduTimeOut)
   ConstTxSignalFields_u16 = TxSigConstPtr->txSignalFields;
#endif

#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition) || defined(COM_EffectiveSigTOC)

    TxSigTP_u8              = (uint8)Com_GetValue(TXSIG,_TP,ConstTxSignalFields_u16);
#endif

    SchM_Enter_Com_TxIpduProtArea(SENDSIGNAL);

#ifdef COM_TxSigUpdateBit

    TxIpduConstPtr          = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

   if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
   {
        Type_SwcServiceCom_tLengthPdu       ByteNo_uo;

        ByteNo_uo = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Update_Bit_Pos >> 3u);

        Com_SetUpdateBitValue(TxIpduConstPtr, TxSigConstPtr->Update_Bit_Pos, ByteNo_uo)
   }
#endif

    TxSigNewVal = Com_Lok_SigBufftoIpduBuff(SignalId, SignalDataPtr);

#if(!defined(COM_EffectiveSigTOC) && !defined(COM_TxFilters))
    (void)TxSigNewVal;
#endif

    SchM_Exit_Com_TxIpduProtArea(SENDSIGNAL);

#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition)

   if(COM_SIG_TP_IS_TRIGGERED(TxSigTP_u8))
   {
        isSigTriggered_u8 = COM_SET;
   }
   else
#endif
#ifdef COM_EffectiveSigTOC

   if(COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TxSigTP_u8))
   {
        if(Com_GetValue(GEN,_TYPE,TxSigConstPtr->General) == COM_UINT8_N)
        {
            isSigTriggered_u8 = (uint8)TxSigNewVal;
        }
        else if(COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) != TxSigNewVal)
        {
            isSigTriggered_u8 = COM_SET;
            COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) = TxSigNewVal;
        }
        else{

        }
   }
   else
#endif
   {

   }

   if(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)IpduId_ui))
   {

        Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        sendIpduFlag_u16.isSigTriggered = isSigTriggered_u8;

#ifdef COM_TxFilters

        if(Com_GetValue(TXSIG,_FILTRALG,ConstTxSignalFields_u16) != (uint16)COM_NOTCONFIGURED)
        {

            if(Com_Lok_SigTxChangeMode(SignalId, (uint32)TxSigNewVal))
            {
                sendIpduFlag_u16.isModeChangd = COM_SET;
            }
        }
#endif

#ifdef COM_TxIPduTimeOut

        if(Com_GetValue(TXSIG,_TOENABLED,ConstTxSignalFields_u16))
        {
            sendIpduFlag_u16.isTimeoutReq = COM_SET;
        }
#endif

#if defined(COM_SigTriggeredWithoutRepetition) || defined(COM_SigTriggeredOnChangeWithoutRepetition)

        if(COM_SIG_TP_IS_WITHOUT_REPETITION(TxSigTP_u8))
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
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE Com_SigMaxType Com_Lok_SigBufftoIpduBuff(Com_SignalIdType SignalId, const void * SignalDataPtr)
{
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   Com_TxSigConstPtrType       TxSigConstPtr;
   uint16_least                IpduId_ui;
   Com_SigMaxType              TxSigNewVal;
   Type_SwcServiceCom_tLengthPdu               ByteNo_uo;
   uint8                       Type;
   uint8                       ConstGeneral_u8;

    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(SignalId);
    IpduId_ui       = TxSigConstPtr->IpduRef;
   ConstGeneral_u8 = TxSigConstPtr->General;

    TxIpduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);
    Type            = Com_GetValue(GEN,_TYPE,ConstGeneral_u8);
    TxSigNewVal     = COM_ZERO;

   if(Type != (uint8)COM_UINT8_N)
   {
        uint8       SigEndianess;

        SigEndianess = Com_GetValue(GEN,_ENDIANESS,ConstGeneral_u8);

        switch(Type)
        {
        case COM_SINT8:
        case COM_UINT8:

            TxSigNewVal = (*(const uint8 * )SignalDataPtr);
            break;
        case COM_SINT16:
        case COM_UINT16:

            TxSigNewVal = (*(const uint16 * )SignalDataPtr);
            break;
        case COM_BOOLEAN:

            TxSigNewVal = COM_BOOL_TO_UNSIGNED(*(const boolean * )SignalDataPtr);
            break;
        case COM_SINT32:
        case COM_UINT32:

            TxSigNewVal = (*(const uint32 * )SignalDataPtr);
            break;
#ifdef COM_TXSIG_INT64
        case COM_UINT64:
        case COM_SINT64:

            TxSigNewVal = *(const uint64 * )SignalDataPtr;
            break;
#endif

#ifdef COM_FLOAT32SUPP
        case COM_FLOAT32:
        {
            uint32 TxSigNewVal_u32;
            TxSigNewVal_u32 = COM_ZERO;

            (void)rba_BswSrv_MemCopy( (void *)&TxSigNewVal_u32, SignalDataPtr, COM_F32_SIZE_IN_BYTES );

            TxSigNewVal = TxSigNewVal_u32;
        }
            break;
#endif

        default:

            break;
        }

#ifdef COM_TXSIG_FLOAT64SUPP
        if(Type == COM_FLOAT64)
        {
            float64 TxSigNewVal_f64;

            TxSigNewVal_f64 = *(const float64 * )SignalDataPtr;

            Com_PackFloatSignal(SigEndianess, TxSigConstPtr->Bit_Pos, TxSigNewVal_f64, TxIpduConstPtr->BuffPtr);
        }
        else
#endif

        {
            Com_PackSignal(SigEndianess, TxSigConstPtr->Bit_Pos, TxSigConstPtr->BitSize, TxSigNewVal
   ,                          TxIpduConstPtr->BuffPtr);
        }
   }
   else{
#ifdef COM_EffectiveSigTOC

        uint8                       TxSigTP_u8;
#endif

        ByteNo_uo = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Bit_Pos >> 3u);

#ifdef COM_EffectiveSigTOC

        TxSigTP_u8      = (uint8)Com_GetValue(TXSIG,_TP,TxSigConstPtr->txSignalFields);

        if(COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TxSigTP_u8))
        {

            if((COM_MEMCOMPARE((TxIpduConstPtr->BuffPtr + ByteNo_uo),SignalDataPtr,(uint32)TxSigConstPtr->BitSize)) != 0x00)
            {

                Com_ByteCopy((TxIpduConstPtr->BuffPtr + ByteNo_uo),(const uint8*)SignalDataPtr,(uint32)TxSigConstPtr->BitSize);

                TxSigNewVal = COM_ONE;
            }
        }
        else
#endif
        {

            Com_ByteCopy((TxIpduConstPtr->BuffPtr + ByteNo_uo),(const uint8*)SignalDataPtr,(uint32)TxSigConstPtr->BitSize);

        }
   }

    return TxSigNewVal;
}

