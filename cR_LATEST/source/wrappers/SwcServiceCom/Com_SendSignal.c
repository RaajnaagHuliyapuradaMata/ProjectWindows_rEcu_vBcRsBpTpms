#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

LOCAL_INLINE FUNC(Com_SigMaxType, COM_CODE) Com_Lok_SigBufftoIpduBuff(
                                                            VAR(Com_SignalIdType, AUTOMATIC)        SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
                                                                     );

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_SendSignal( VAR(Com_SignalIdType, AUTOMATIC)        SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr )
{
   Com_TxSigConstPtrType TxSigConstPtr;
#ifdef COM_TP_IPDUTYPE
   Com_TxIpduRamPtrType  TxIpduRamPtr;
#endif
   VAR(uint8, AUTOMATIC) Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_TX_SIGNALS), (SignalDataPtr == NULL_PTR)
   ,     COMServiceId_SendSignal))
#endif
   {

        SignalId      = COM_GET_TXSIGNAL_ID(SignalId);

        TxSigConstPtr = COM_GET_TXSIG_CONSTDATA( SignalId );
#ifdef COM_TP_IPDUTYPE
        TxIpduRamPtr  = &COM_GET_TXPDURAM_S( TxSigConstPtr->IpduRef );
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

FUNC(uint8, COM_CODE) Com_InternalSendSignal(
                                    VAR(Com_SignalIdType, AUTOMATIC)        SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
                                            )
{
#ifdef COM_TxSigUpdateBit
   Com_TxIpduConstPtrType          TxIPduConstPtr;
#endif
   Com_TxSigConstPtrType           TxSigConstPtr;
   VAR(Com_SigMaxType, AUTOMATIC)  TxSigNewVal;
   VAR(uint16_least, AUTOMATIC)    IpduId_ui;
   VAR(uint16, AUTOMATIC)          ConstTxSignalFields_u16;
   VAR(uint8, AUTOMATIC)           TxSigTP_u8;
   VAR(uint8, AUTOMATIC)           isSigTriggered_u8;
   VAR(uint8, AUTOMATIC)           Status;

    Status                  = E_OK;

    TxSigConstPtr           = COM_GET_TXSIG_CONSTDATA(SignalId);
    IpduId_ui               = TxSigConstPtr->IpduRef;
   ConstTxSignalFields_u16 = TxSigConstPtr->txSignalFields;

    TxSigTP_u8              = (uint8)Com_GetValue(TXSIG,_TP,ConstTxSignalFields_u16);

    SchM_Enter_Com_TxIpduProtArea(SENDSIGNAL);

#ifdef COM_TxSigUpdateBit

    TxIPduConstPtr          = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

   if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
   {
        VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) ByteNo_uo;

        ByteNo_uo = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Update_Bit_Pos >> 3u);

        Com_SetUpdateBitValue(TxIPduConstPtr, TxSigConstPtr->Update_Bit_Pos, ByteNo_uo)
   }
#endif

    TxSigNewVal = Com_Lok_SigBufftoIpduBuff(SignalId, SignalDataPtr);

    SchM_Exit_Com_TxIpduProtArea(SENDSIGNAL);

#if defined(COM_SigTriggered) || defined(COM_SigTriggeredWithoutRepetition)

   if(COM_SIG_TP_IS_TRIGGERED(TxSigTP_u8))
   {
        isSigTriggered_u8 = COM_SET;
   }
   else
#endif
#ifdef COM_EffectiveSigTOC

   if(COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(TxSigTP_u8) &&
       (COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) != (Com_OldValTrigOnChngType)TxSigNewVal))
   {
        isSigTriggered_u8 = COM_SET;
        COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxSigNewVal;
   }
   else
#endif
   {

        isSigTriggered_u8 = COM_RESET;
   }

   if(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)IpduId_ui))
   {

        VAR(Com_SendIpduInfo,AUTOMATIC) sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        sendIpduFlag_u16.sigTransProp = isSigTriggered_u8;

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

        Com_Lok_ProceedToSendIpdu( (Type_CfgSwcServiceCom_tIdIPdu)IpduId_ui, sendIpduFlag_u16 );

   }
   else{

        Status = COM_SERVICE_NOT_AVAILABLE;
   }

    return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

LOCAL_INLINE FUNC(Com_SigMaxType, COM_CODE) Com_Lok_SigBufftoIpduBuff(
                                                            VAR(Com_SignalIdType, AUTOMATIC)        SignalId
   ,     P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
                                                                     )
{
   Com_TxIpduConstPtrType          TxIPduConstPtr;
   Com_TxSigConstPtrType           TxSigConstPtr;
   VAR(uint16_least, AUTOMATIC)    IpduId_ui;
   VAR(Com_SigMaxType, AUTOMATIC)  TxSigNewVal;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)   ByteNo_uo;
   VAR(uint8, AUTOMATIC)           Type;
   VAR(uint8, AUTOMATIC)           ConstGeneral_u8;

    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(SignalId);
    IpduId_ui       = TxSigConstPtr->IpduRef;
   ConstGeneral_u8 = TxSigConstPtr->General;

    TxIPduConstPtr  = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

    TxSigNewVal     = (Com_SigMaxType)0;
    Type            = Com_GetValue(GEN,_TYPE,ConstGeneral_u8);

   if(Type != (uint8)COM_UINT8_N)
   {
        VAR(uint8, AUTOMATIC) SigEndianess;

        SigEndianess = Com_GetValue(GEN,_ENDIANESS,ConstGeneral_u8);

        switch(Type)
        {
        case COM_SINT8:
        case COM_UINT8:

            TxSigNewVal = (Com_SigMaxType)(*(P2CONST(uint8,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            break;
        case COM_SINT16:
        case COM_UINT16:

            TxSigNewVal = (Com_SigMaxType)(*(P2CONST(uint16,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            break;
        case COM_BOOLEAN:

            TxSigNewVal = (Com_SigMaxType)COM_BOOL_TO_UNSIGNED(*(P2CONST(boolean,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            break;
        case COM_SINT32:
        case COM_UINT32:

            TxSigNewVal = (Com_SigMaxType)(*(P2CONST(uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr);
            break;
#ifdef COM_TXSIG_INT64
        case COM_UINT64:
        case COM_SINT64:

            TxSigNewVal = *(P2CONST(uint64, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;
            break;
#endif

#ifdef COM_FLOAT32SUPP
        case COM_FLOAT32:

            (void)LibAutosar_vptrMemCopy( (void *)&TxSigNewVal, SignalDataPtr, 4 );
            break;
#endif

        default:

            break;
        }

#ifdef COM_TXSIG_FLOAT64SUPP
        if(Type == COM_FLOAT64)
        {
            VAR(float64, AUTOMATIC) TxSigNewVal_f64;

            TxSigNewVal_f64 = *(P2CONST(float64, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

            Com_PackFloatSignal(SigEndianess, TxSigConstPtr->Bit_Pos, TxSigNewVal_f64, TxIPduConstPtr->BuffPtr);
        }
        else
#endif

        {
            Com_PackSignal(SigEndianess, TxSigConstPtr->Bit_Pos, TxSigConstPtr->BitSize, TxSigNewVal
   ,     TxIPduConstPtr->BuffPtr);
        }
   }
   else{

        ByteNo_uo = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Bit_Pos >> 3u);

        Com_ByteCopy((TxIPduConstPtr->BuffPtr + ByteNo_uo),(const uint8*)SignalDataPtr,(uint32)TxSigConstPtr->BitSize);

   }

    return TxSigNewVal;
}

