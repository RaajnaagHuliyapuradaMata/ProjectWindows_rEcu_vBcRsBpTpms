#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_InvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId)
{
#ifdef COM_TxGrpSigInvalid

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((SignalId >= COM_GET_NUM_TX_GRPSIGNALS), COMServiceId_InvalidateShadowSignal))
#endif
   {

        SignalId = COM_GET_TXGRPSIGNAL_ID(SignalId);

        Com_InternalInvalidateShadowSignal(SignalId);
   }

#else
    (void)SignalId;
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#ifdef COM_TxGrpSigInvalid
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_InternalInvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId)
{
   Com_TxGrpSigConstPtrType            TxGrpSigConstPtr;

   VAR(uint32, AUTOMATIC)              TxGrpSig_NewVal;
   VAR(uint8, AUTOMATIC)               ConstByteValue_u8;
   VAR(uint8, AUTOMATIC)               Type;
   VAR(Com_MainFuncType,AUTOMATIC)     txMainFuncId;

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(SignalId);
    Type = Com_GetValue(TXGRPSIG,_TYPE,TxGrpSigConstPtr->txGrpSigFields);

   ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;

   if(Com_GetValue(TXGRPSIG,_INVACTION,ConstByteValue_u8))
   {
        TxGrpSig_NewVal  = TxGrpSigConstPtr->DataInvalid_Val;

        txMainFuncId = (COM_GET_TX_IPDU_CONSTDATA((COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

        if(Type != (uint8)COM_UINT8_N)
        {
            Com_CopyTxGroupSignalData(SignalId, (Com_SigMaxType)TxGrpSig_NewVal, txMainFuncId);
        }
        else{
            Com_ByteCopyInit(&COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,     TxGrpSig_NewVal, (uint32)TxGrpSigConstPtr->BitSize);
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#endif

