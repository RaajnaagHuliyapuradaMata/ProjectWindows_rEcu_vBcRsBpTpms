

#include "Com_Prv.hpp"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
void Com_ShadowBuffToIpduBuff(Com_SignalGroupIdType SignalGrpId)
{
   Com_TxIpduConstPtrType          TxIpduConstPtr;
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
   Com_SigMaxType                  TxGrpSig_NewVal;
   uint16_least                    idx_TxGrpSig_u16;
   uint8                           SigType_u8;
   uint8                           ConstByteValue_u8;
   Com_MainFuncType                txMainFuncId;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGrpId);

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr ->FirstGrpSig_Index);

    TxIpduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxSigGrpConstPtr->IpduRef);

    txMainFuncId     = TxIpduConstPtr->MainFunctionRef;

    TxGrpSig_NewVal  = COM_ZERO;

   for(idx_TxGrpSig_u16 = TxSigGrpConstPtr->No_Of_GrpSig; idx_TxGrpSig_u16 > COM_ZERO; idx_TxGrpSig_u16--)
   {
        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;

        SigType_u8 = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
        if(SigType_u8 != (uint8)COM_UINT8_N)
        {
            uint8 SigEndianess;

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

#ifdef COM_GRPSIGFLOAT32SUPP
            case (COM_FLOAT32 >> 1u):

#endif

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
   ,                           COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,                           TxIpduConstPtr->BuffPtr
                                   );
            }
            else
#endif

            {

                Com_PackSignal(SigEndianess,TxGrpSigConstPtr->Bit_Pos,TxGrpSigConstPtr->BitSize
   ,                              TxGrpSig_NewVal,TxIpduConstPtr->BuffPtr);
            }
        }
        else{

            Type_SwcServiceCom_tLengthPdu ByteNo_uo;

            ByteNo_uo = ( Type_SwcServiceCom_tLengthPdu )( TxGrpSigConstPtr->Bit_Pos >> 3 );

            Com_ByteCopy( ( TxIpduConstPtr->BuffPtr + ByteNo_uo )
   ,                           &COM_GET_TXGRPSIGTYPEU8_BUFF(txMainFuncId, TxGrpSigConstPtr->TxGrpSigBuff_Index)
   ,                           TxGrpSigConstPtr->BitSize );
        }

        TxGrpSigConstPtr++;
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

