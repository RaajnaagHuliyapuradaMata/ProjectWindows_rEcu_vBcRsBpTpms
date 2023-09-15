#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_ShadowBuffToIpduBuff(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGrpId)
{

   Com_TxIpduConstPtrType              TxIPduConstPtr;
   Com_TxGrpSigConstPtrType            TxGrpSigConstPtr;
   Com_TxSigGrpConstPtrType            TxSigGrpConstPtr;
   VAR(Com_SigMaxType,AUTOMATIC)       TxGrpSig_NewVal;
   VAR(uint16_least, AUTOMATIC)        index_ui;
   VAR(uint8, AUTOMATIC)               SigType_u8;
   VAR(uint8, AUTOMATIC)               ConstByteValue_u8;
   VAR(Com_MainFuncType,AUTOMATIC)     txMainFuncId;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGrpId);

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr ->FirstGrpSig_Index);

    TxIPduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxSigGrpConstPtr->IpduRef);

    txMainFuncId     = TxIPduConstPtr->MainFunctionRef;

    TxGrpSig_NewVal  = 0;

   for(index_ui = TxSigGrpConstPtr->No_Of_GrpSig; index_ui != 0u; index_ui--)
   {
        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;

        SigType_u8 = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
        if(SigType_u8 != (uint8)COM_UINT8_N)
        {
            VAR(uint8, AUTOMATIC) SigEndianess;

            SigEndianess = Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8);

            switch(SigType_u8 >> 1u)
            {
            case 0x00u:
            case 0x03u:
                TxGrpSig_NewVal = COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

            case 0x01u:

                TxGrpSig_NewVal = COM_GET_TXGRPSIGTYPEU16_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

            case 0x02u:

            case (COM_FLOAT32 >> 1u):

                TxGrpSig_NewVal = COM_GET_TXGRPSIGTYPEU32_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

#ifdef COM_TXGRPSIG_INT64
            case 0x08u:

                TxGrpSig_NewVal = COM_GET_TXGRPSIGTYPEU64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;
#endif

            default:

                break;

            }

#ifdef COM_TXGRPSIG_FLOAT64SUPP
            if(SigType_u8 == COM_FLOAT64)
            {

                Com_PackFloatSignal(
                            SigEndianess, TxGrpSigConstPtr->Bit_Pos
   ,     COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,     TxIPduConstPtr->BuffPtr
                                   );
            }
            else
#endif

            {

                Com_PackSignal(SigEndianess,TxGrpSigConstPtr->Bit_Pos,TxGrpSigConstPtr->BitSize
   ,     TxGrpSig_NewVal,TxIPduConstPtr->BuffPtr);
            }
        }
        else{

            Type_SwcServiceCom_tLengthPdu ByteNo_uo;

            ByteNo_uo = ( Type_SwcServiceCom_tLengthPdu )( TxGrpSigConstPtr->Bit_Pos >> 3 );

            Com_ByteCopy( ( TxIPduConstPtr->BuffPtr + ByteNo_uo )
   ,     &COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,     TxGrpSigConstPtr->BitSize );
        }

        TxGrpSigConstPtr++;
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

