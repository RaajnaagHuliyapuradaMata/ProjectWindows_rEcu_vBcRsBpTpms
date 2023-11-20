#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
# include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_SendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
   Com_TxSigGrpConstPtrType TxSigGrpConstPtr;
   Com_TxIpduRamPtrType     TxIpduRamPtr;
   VAR(uint8, AUTOMATIC)    Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP), COMServiceId_SendSignalGroup))
#endif
   {

        SignalGroupId    = COM_GET_TXSIGNALGRP_ID(SignalGroupId);

        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA( SignalGroupId );
        TxIpduRamPtr     = &COM_GET_TXPDURAM_S( TxSigGrpConstPtr->IpduRef );

#ifdef COM_TP_IPDUTYPE
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
        {
            Status = COM_BUSY;
        }
        else
#endif
        {
            Status = Com_InternalSendSignalGroup(SignalGroupId);
        }

   }
    return Status;
}
#define COM_STOP_SEC_CODE
# include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
# include "Com_MemMap.hpp"

FUNC(uint8, COM_CODE) Com_InternalSendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
#ifdef COM_EffectiveSigGrpTOC

   Com_TxSigGrpRamPtrType              TxSigGrpRamPtr;
#endif

   Com_TxSigGrpConstPtrType            TxSigGrpConstPtr;
#if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY)

   Com_TxIpduConstPtrType              TxIPduConstPtr;
#endif

   Com_TxIpduRamPtrType                TxIpduRamPtr;
   VAR(uint16_least, AUTOMATIC)        IpduId_ui;
   VAR(uint8, AUTOMATIC)               ConstByteValue_u8;
   VAR(uint8, AUTOMATIC)               Status;
   VAR(uint8, AUTOMATIC)               isSigTriggered_u8;
#if(defined(COM_SigGrpTriggered) || defined(COM_SigGrpTriggeredWithoutRepetition) || defined(COM_EffectiveSigGrpTOC))
   VAR(uint8, AUTOMATIC)               transferProperty_u8;
#endif
   VAR(boolean, AUTOMATIC)             TransProp_bool;
#ifdef COM_TX_SIGNALGROUP_ARRAY
   VAR(boolean, AUTOMATIC)             ConstIsSigGrpOfArrayType_b;
#endif

    Status              = E_OK;
   isSigTriggered_u8   = COM_RESET;
    TransProp_bool      = COM_FALSE;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);

    IpduId_ui = TxSigGrpConstPtr->IpduRef;
#if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY)

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

#endif
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId_ui);
   ConstByteValue_u8 = TxSigGrpConstPtr->txSignalGrpFields;

#ifdef COM_EffectiveSigGrpTOC
    TxSigGrpRamPtr = &COM_GET_TXSIGGRPFLAG(SignalGroupId);
#endif

#ifdef COM_TX_SIGNALGROUP_ARRAY
   ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

    SchM_Enter_Com_TxIpduProtArea(SENDSIGNALGRP);

#ifdef COM_TX_SIGNALGROUP_ARRAY
   if( ConstIsSigGrpOfArrayType_b == COM_FALSE )
#endif
   {
        Com_ShadowBuffToIpduBuff(SignalGroupId);
   }
#ifdef COM_TX_SIGNALGROUP_ARRAY
   else{

   }
#endif

#ifdef COM_TxSigGrpUpdateBit

   if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
   {
        VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) ByteNo_u8;

        ByteNo_u8 = (Type_SwcServiceCom_tLengthPdu)((TxSigGrpConstPtr->Update_Bit_Pos)>>3u);

        Com_SetUpdateBitValue(TxIPduConstPtr,TxSigGrpConstPtr->Update_Bit_Pos,ByteNo_u8)
   }
#endif
    SchM_Exit_Com_TxIpduProtArea(SENDSIGNALGRP);
#if(defined(COM_SigGrpTriggered) || defined(COM_SigGrpTriggeredWithoutRepetition) || defined(COM_EffectiveSigGrpTOC))
    transferProperty_u8 = Com_GetValue(TXSIGGRP,_TP,ConstByteValue_u8);
#endif
#if defined(COM_SigGrpTriggered) || defined(COM_SigGrpTriggeredWithoutRepetition)

   if(COM_SIG_TP_IS_TRIGGERED(transferProperty_u8))
   {
        isSigTriggered_u8 = COM_SET;
   }
   else
#endif
   {
#ifdef COM_EffectiveSigGrpTOC

        if(COM_SIG_TP_IS_TRIGGERED_ON_CHANGE(transferProperty_u8) &&
           (Com_GetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr ->txSigGrpRAMFields) != COM_FALSE))
        {
            isSigTriggered_u8 = COM_SET;

            Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr->txSigGrpRAMFields,COM_FALSE);
        }
#endif
   }

   if(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)IpduId_ui))
   {

        VAR(Com_SendIpduInfo,AUTOMATIC) sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

        sendIpduFlag_u16.sigTransProp = isSigTriggered_u8;

#ifdef COM_TxFilters

        if(Com_GetValue(TXSIGGRP,_FILTEREVALREQ,TxSigGrpConstPtr->txSignalGrpFields) != COM_FALSE)
        {

            sendIpduFlag_u16.isModeChangd = COM_BOOL_TO_UNSIGNED(Com_Lok_SigGrpTxChangeMode(SignalGroupId));
        }
#endif

#ifdef COM_TxIPduTimeOut
        sendIpduFlag_u16.isTimeoutReq = COM_BOOL_TO_UNSIGNED(Com_GetValue(TXSIGGRP,_TOENABLED,ConstByteValue_u8));
#endif

#if defined(COM_SigGrpTriggeredOnChangeWithoutRepetition) || defined(COM_SigGrpTriggeredWithoutRepetition)
        if(COM_SIG_TP_IS_WITHOUT_REPETITION(transferProperty_u8))
        {

            sendIpduFlag_u16.ignoreRepetitions = COM_SET;
        }
#endif

        Com_Lok_ProceedToSendIpdu( (Type_CfgSwcServiceCom_tIdIPdu)IpduId_ui, sendIpduFlag_u16 );

   }
   else{
        Status = COM_SERVICE_NOT_AVAILABLE;
   }

    return (Status);
}
#define COM_STOP_SEC_CODE
# include "Com_MemMap.hpp"

#endif

