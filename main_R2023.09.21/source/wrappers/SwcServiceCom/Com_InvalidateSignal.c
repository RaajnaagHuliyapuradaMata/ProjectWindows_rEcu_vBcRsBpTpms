#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_InvalidateSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId)
{
#ifdef COM_TxInvalid
   Com_TxSigConstPtrType           TxSigConstPtr;
   Com_TxIpduConstPtrType          TxIPduConstPtr;
   Com_TxIpduRamPtrType            TxIpduRamPtr;
   VAR(uint16_least, AUTOMATIC)    IpduId_ui;
   VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC)   ByteNo_u8;
   VAR(uint8, AUTOMATIC)           Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((SignalId >= COM_GET_NUM_TX_SIGNALS), COMServiceId_InvalidateSignal))
#endif
   {

        SignalId       = COM_GET_TXSIGNAL_ID(SignalId);

        TxSigConstPtr  = COM_GET_TXSIG_CONSTDATA(SignalId);

        IpduId_ui      = TxSigConstPtr->IpduRef;

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);
        TxIpduRamPtr   = &COM_GET_TXPDURAM_S( IpduId_ui );

        if(Com_GetValue(TXSIG,_INVACTION,TxSigConstPtr->txSignalFields))
        {
#ifdef COM_TP_IPDUTYPE

            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
            {

                Status = COM_BUSY;
            }
            else
#endif
            {
                uint8 type_u8;

                type_u8 = Com_GetValue(GEN,_TYPE,TxSigConstPtr->General);

                if(type_u8 != (uint8)COM_UINT8_N)
                {
                    VAR(Com_SigMaxType,AUTOMATIC) txSigInvValue;

                    txSigInvValue = (Com_SigMaxType)TxSigConstPtr->DataInvalid_Val;

                    Status = Com_InternalSendSignal( SignalId, (const void *)&txSigInvValue );
                 }
                 else
                 {

                     ByteNo_u8 = (Type_SwcServiceCom_tLengthPdu)(TxSigConstPtr->Bit_Pos>>3u);

                     SchM_Enter_Com_TxIpduProtArea(INVALIDATESIGNAL);

                     Com_ByteCopyInit((TxIPduConstPtr->BuffPtr + ByteNo_u8)
   ,     TxSigConstPtr->DataInvalid_Val,(uint32)TxSigConstPtr->BitSize);

                     SchM_Exit_Com_TxIpduProtArea(INVALIDATESIGNAL);

                     Status = Com_InternalSendSignal( SignalId, (const void *)(TxIPduConstPtr->BuffPtr + ByteNo_u8) );
                 }
            }
        }
        else{

        }
   }

    return (Status);

#else
    (void)SignalId;
    return( COM_SERVICE_NOT_AVAILABLE );
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

