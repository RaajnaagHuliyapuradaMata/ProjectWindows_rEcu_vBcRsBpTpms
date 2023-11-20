#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#ifdef COM_SIGNALGATEWAY
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_Lok_PackRxSignalGwBufferData(Com_RxSigConstPtrType RxSigConstPtr
   ,     Com_SignalIdType l_TxGwDestId)
{
   Com_TxSigConstPtrType                TxSigConstPtr;
#if defined(COM_TXSIG_FLOAT64SUPP) && defined(COM_RXSIG_FLOAT64SUPP)
   VAR(float64, AUTOMATIC)              TxNewVal_f64;
#endif
   VAR(Com_SigBuffIndexType, AUTOMATIC) RxSigBuff_Index;
   VAR(Com_SigMaxType, AUTOMATIC)       TxNewVal;
   VAR(uint8, AUTOMATIC)                Type;
   VAR(Com_MainFuncType, AUTOMATIC)     rxMainFuncId;

    TxSigConstPtr   = COM_GET_TXSIG_CONSTDATA(l_TxGwDestId);
    Type            = Com_GetValue(GEN,_TYPE,TxSigConstPtr->General);

    rxMainFuncId    = (COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef))->MainFunctionRef;

    RxSigBuff_Index = RxSigConstPtr->SigBuff_Index;
    TxNewVal        = (Com_SigMaxType)0;

   if(Type != (uint8)COM_UINT8_N)
   {

        SchM_Enter_Com_RxSigGwMcLockProtArea();

        switch(Type >> 1u)
        {
        case 0x00u:
        case (COM_BOOLEAN >> 1):

            TxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, RxSigBuff_Index);
            break;

        case 0x01u:

            TxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT16_BUFF(rxMainFuncId, RxSigBuff_Index);
            break;

        case 0x02u:

#ifdef COM_FLOAT32SUPP
        case (COM_FLOAT32 >> 1):
#endif

            TxNewVal = (Com_SigMaxType)COM_GET_SIGTYPEUINT32_BUFF(rxMainFuncId, RxSigBuff_Index);
            break;

#if defined(COM_RXSIG_INT64) && defined(COM_TXSIG_INT64)
        case 0x08u:

            TxNewVal = COM_GET_SIGTYPEUINT64_BUFF(rxMainFuncId, RxSigBuff_Index);
            break;
#endif

#if defined(COM_TXSIG_FLOAT64SUPP) && defined(COM_RXSIG_FLOAT64SUPP)
        case (COM_FLOAT64 >> 1):
            TxNewVal_f64 = COM_GET_SIGTYPEFLOAT64_BUFF(rxMainFuncId, RxSigBuff_Index);
            break;
#endif

        default:

            break;
        }

        SchM_Exit_Com_RxSigGwMcLockProtArea();

#if defined(COM_TXSIG_FLOAT64SUPP) && defined(COM_RXSIG_FLOAT64SUPP)
        if(Type == COM_FLOAT64)
        {

            (void)Com_InternalSendSignal( l_TxGwDestId, (const void *)&TxNewVal_f64 );

        }
        else
#endif

        {

            (void)Com_InternalSendSignal( l_TxGwDestId, (const void *)&TxNewVal );

        }
   }
   else{

        SchM_Enter_Com_RxSigGwMcLockProtArea();

        (void)Com_InternalSendSignal( l_TxGwDestId, (const void *)&COM_GET_SIGTYPEUINT8_BUFF(rxMainFuncId, RxSigBuff_Index) );

        SchM_Exit_Com_RxSigGwMcLockProtArea();
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

FUNC(void, COM_CODE) Com_Lok_PackRxGrpSigGwBufferData( Com_RxGrpSigConstPtrType RxGrpSigConstPtr
   ,     Com_TxIntGrpSignalIdType l_TxGwDestId)
{
   Com_TxGrpSigConstPtrType                TxGrpSigConstPtr;
   Com_TxSigGrpRamPtrType                  TxSigGrpRamPtr;
   VAR(Com_SigMaxType, AUTOMATIC)          TxNewVal;
   VAR(Com_RxGrpSigBuffIndexType, AUTOMATIC) rxGrpSignalBuffIndex;
   VAR(uint8, AUTOMATIC)                   Type;
   VAR(Com_MainFuncType, AUTOMATIC)        rxMainFuncId;
   VAR(Com_MainFuncType,AUTOMATIC)         txMainFuncId;

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(l_TxGwDestId);

    TxSigGrpRamPtr   = &COM_GET_TXSIGGRPFLAG(TxGrpSigConstPtr->SigGrpRef);

    Type = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

    rxMainFuncId = (COM_GET_RX_IPDU_CONSTDATA((COM_GET_RXSIGGRP_CONSTDATA(RxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

    txMainFuncId = (COM_GET_TX_IPDU_CONSTDATA((COM_GET_TXSIGGRP_CONSTDATA(TxGrpSigConstPtr->SigGrpRef))->IpduRef))->MainFunctionRef;

    TxNewVal = 0u;

    rxGrpSignalBuffIndex = RxGrpSigConstPtr->RxGrpSigBuff_Index;

   if(Type != (uint8)COM_UINT8_N)
   {
        SchM_Enter_Com_TxGrpSigBuffer();
        switch(Type >> 1u)
        {
        case 0x00u:
        case (COM_BOOLEAN >> 1):

            TxNewVal = (Com_SigMaxType)COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxMainFuncId, rxGrpSignalBuffIndex);
            COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint8)TxNewVal;
            break;

        case 0x01u:
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigSecBuff();
#endif

            TxNewVal = (Com_SigMaxType)COM_GET_SECRXGRPSIGTYPEU16_BUFF(rxMainFuncId, rxGrpSignalBuffIndex);
#if(CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigSecBuff();
#endif
            COM_GET_TXGRPSIGTYPEU16_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint16)TxNewVal;
            break;

        case 0x02u:

#ifdef COM_GRPSIGFLOAT32SUPP
        case (COM_FLOAT32 >> 1u):
#endif

#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigSecBuff();
#endif

            TxNewVal = (Com_SigMaxType)COM_GET_SECRXGRPSIGTYPEU32_BUFF(rxMainFuncId, rxGrpSignalBuffIndex);
#if(CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigSecBuff();
#endif
            COM_GET_TXGRPSIGTYPEU32_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint32)TxNewVal;
            break;

#if defined(COM_RXGRPSIG_INT64) && defined(COM_TXGRPSIG_INT64)
        case 0x08u:
            SchM_Enter_Com_RxGrpSigSecBuff();

            TxNewVal = COM_GET_SECRXGRPSIGTYPEU64_BUFF(rxMainFuncId, rxGrpSignalBuffIndex);
            SchM_Exit_Com_RxGrpSigSecBuff();
            COM_GET_TXGRPSIGTYPEU64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)  = TxNewVal;
            break;
#endif

#if defined(COM_TXGRPSIG_FLOAT64SUPP) && defined(COM_RXGRPSIG_FLOAT64SUPP)
        case (COM_FLOAT64 >> 1):
            SchM_Enter_Com_RxGrpSigSecBuff();

            COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index) =
                         COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(rxMainFuncId, rxGrpSignalBuffIndex);
            SchM_Exit_Com_RxGrpSigSecBuff();
            break;
#endif

        default:

            break;

        }
        SchM_Exit_Com_TxGrpSigBuffer();

#ifdef COM_EffectiveSigGrpTOC

        if((Com_GetValue(TXGRPSIG,_TP,TxGrpSigConstPtr->txGrpSigFields) != COM_FALSE)  &&
           (COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) != (Com_OldValTrigOnChngType)TxNewVal))
        {

            COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxNewVal;

            Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr->txSigGrpRAMFields,COM_TRUE);
        }
#endif

   }
   else{

        SchM_Enter_Com_TxGrpSigBuffer();
        SchM_Enter_Com_RxGrpSigSecBuff();
        Com_ByteCopy(&COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,     &COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxMainFuncId, rxGrpSignalBuffIndex),(uint32)TxGrpSigConstPtr->BitSize);
        SchM_Exit_Com_RxGrpSigSecBuff();
        SchM_Exit_Com_TxGrpSigBuffer();

   }

   Com_SetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr->txSigGrpRAMFields,COM_TRUE);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

