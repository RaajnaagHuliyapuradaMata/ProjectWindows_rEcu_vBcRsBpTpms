

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_InvalidateShadowSignal(Com_SignalIdType SignalId)
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

void Com_InternalInvalidateShadowSignal(Com_SignalIdType SignalId)
{
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;

   uint32                          TxGrpSig_NewVal;
   uint8                           ConstByteValue_u8;
   uint8                           Type;
   Com_MainFuncType                txMainFuncId;

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(SignalId);
    Type = Com_GetValue(TXGRPSIG,_TYPE,TxGrpSigConstPtr->txGrpSigFields);

   ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;

   if(Com_GetValue(TXGRPSIG,_INVACTION,ConstByteValue_u8))
   {
        TxGrpSig_NewVal  = TxGrpSigConstPtr->DataInvalid_Val;

        txMainFuncId = (COM_GET_TX_IPDU_CONSTDATA((COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

        if(Type != (uint8)COM_UINT8_N)
        {
            Com_CopyTxGroupSignalData(SignalId, TxGrpSig_NewVal, txMainFuncId);
        }
        else{
            Com_ByteCopyInit(&COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,                            TxGrpSig_NewVal, (uint32)TxGrpSigConstPtr->BitSize);
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

#endif

