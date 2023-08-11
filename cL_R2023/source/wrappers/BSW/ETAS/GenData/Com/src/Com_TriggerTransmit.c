

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType * PduInfoPtr)
{

    Com_TxIpduConstPtrType      TxIpduConstPtr;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
    Com_TxIpduRamPtrType        TxIpduRamPtr;
#endif
    PduLengthType               Size;
#if ((defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) || \
      defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TxIPduCallOuts))
    uint16                      ConstByteValue_u16;
#endif
    Std_ReturnType              Status;

    Status = E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

    if(Com_Lok_DETCheck_Param_Ptr((TxPduId >= COM_GET_NUM_TX_IPDU), (PduInfoPtr == NULL_PTR),
                                                                    COMServiceId_TriggerTransmit))
#endif
    {

        TxPduId        = COM_GET_TX_IPDU_ID(TxPduId);

        TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
        TxIpduRamPtr   = &COM_GET_TXPDURAM_S(TxPduId);
#endif

#if ((defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) || \
      defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TxIPduCallOuts))
        ConstByteValue_u16 = TxIpduConstPtr->txIPduFields;
#endif

        Size = TxIpduConstPtr->Size;

        if (Com_CheckTxIPduStatus(TxPduId))
        {
            Status = E_OK;
        }
        else
        {

        }

        SchM_Enter_Com_TxIpduProtArea(TRIGGERTRANSMIT);

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT

        if (Com_GetValue(TXIPDU,_ISDYNIPDU,ConstByteValue_u16))
        {
            Size += (PduLengthType)(TxIpduRamPtr->Com_DynLength);
        }
#endif

        Com_ByteCopy(PduInfoPtr->SduDataPtr, TxIpduConstPtr->BuffPtr, Size);

        PduInfoPtr->SduLength = Size;

#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        if (Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u16) == (uint16)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)
        {
            Com_Lok_ClearUpdateBits(TxIpduConstPtr);
        }
#endif
        SchM_Exit_Com_TxIpduProtArea(TRIGGERTRANSMIT);

#ifdef COM_TxIPduCallOuts

        if (Status != E_NOT_OK)
        {
            if (Com_GetValue(TXIPDU,_ISCALLOUTFRMTRIGTRANS,ConstByteValue_u16) != COM_FALSE)
            {

                (void)TxIpduConstPtr->CallOut(TxPduId, PduInfoPtr);
            }
        }
#endif
    }
    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

