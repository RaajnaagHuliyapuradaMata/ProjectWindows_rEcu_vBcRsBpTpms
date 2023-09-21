#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) TxPduId
   ,     P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{

   Com_TxIpduConstPtrType          TxIPduConstPtr;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
   Com_TxIpduRamPtrType            TxIpduRamPtr;
#endif
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)   Size;
   VAR(Std_ReturnType, AUTOMATIC)  Status;
#if((defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) || defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TxIPduCallOuts))
   VAR(uint16, AUTOMATIC)          ConstByteValue_u16;
#endif

    Status = E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param_Ptr((TxPduId >= CfgSwcServiceCom_dNumIPduTx), (PduInfoPtr == NULL_PTR)
   ,     COMServiceId_TriggerTransmit))
#endif
   {

        TxPduId        = COM_GET_TX_IPDU_ID(TxPduId);

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(TxPduId);
#endif
        Status         = E_OK;

#if((defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) || defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TxIPduCallOuts))
        ConstByteValue_u16 = TxIPduConstPtr->txIPduFields;
#endif

        Size = TxIPduConstPtr->Size;

        if(!(Com_CheckTxIPduStatus((Type_SwcServiceCom_tIdPdu)TxPduId)))
        {

            Status = E_NOT_OK;
        }

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

        if(COM_TRUE == Com_GetRamValue(TXIPDU,_ISDYNIPDU,ConstByteValue_u16))
        {
            Size = (Type_SwcServiceCom_tLengthPdu)(TxIPduConstPtr->Size + TxIpduRamPtr->Com_DynLength);
        }
#endif

        SchM_Enter_Com_TxIpduProtArea(TRIGGERTRANSMIT);
        Com_ByteCopy(PduInfoPtr->SduDataPtr,TxIPduConstPtr->BuffPtr,(uint32)Size);
        PduInfoPtr ->SduLength = Size;

#if(defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u16) == (uint16)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)
        {
            Com_Lok_ClearUpdateBits(TxIPduConstPtr);
        }
#endif
        SchM_Exit_Com_TxIpduProtArea(TRIGGERTRANSMIT);

#ifdef COM_TxIPduCallOuts

        if((Status != E_NOT_OK) && (Com_GetValue(TXIPDU,_ISCALLOUTFRMTRIGTRANS,ConstByteValue_u16) != COM_FALSE))
        {

            (void)TxIPduConstPtr->CallOut(TxPduId, PduInfoPtr);
        }
#endif
   }
    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

