

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
uint8 Com_InvalidateSignal(Com_SignalIdType SignalId)
{
#ifdef COM_TxInvalid
   Com_TxSigConstPtrType       TxSigConstPtr;
   Com_TxIpduConstPtrType      TxIpduConstPtr;
   uint16_least                IpduId_16;
   PduLengthType               ByteNo_uo;
   uint8                       Status;
   Com_SigMaxType   txSigInvValuePerType; //create the longest variable to hold the data to be send to Com_InternalSendSignal
   Com_SigMaxType   txSigInvValue;
   uint32 txSigInvValue_32;
   void *SignalDataPtr = (void *)&txSigInvValuePerType;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((SignalId >= COM_GET_NUM_TX_SIGNALS), COMServiceId_InvalidateSignal))
#endif
   {

        SignalId       = COM_GET_TXSIGNAL_ID(SignalId);

        TxSigConstPtr  = COM_GET_TXSIG_CONSTDATA(SignalId);

        IpduId_16      = TxSigConstPtr->IpduRef;

        TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId_16);

        if(Com_GetValue(TXSIG,_INVACTION,TxSigConstPtr->txSignalFields))
        {
#ifdef COM_TP_IPDUTYPE

            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,COM_GET_TXPDURAM_S(IpduId_16).Com_TxFlags) == COM_TRUE)
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
                    if(type_u8 != (uint8)COM_SINT64)
                    {
                    txSigInvValue = (Com_SigMaxType)TxSigConstPtr->DataInvalid_Val;
                        switch(type_u8) {
                        case COM_UINT8:
                            {
                                *(uint8*) SignalDataPtr = (uint8) txSigInvValue;
                            }
                            break;
                        case COM_UINT16:
                            {
                                *(uint16*) SignalDataPtr = (uint16) txSigInvValue;
                            }
                            break;
                        case COM_UINT32:
                            {
                                *(uint32*) SignalDataPtr = (uint32) txSigInvValue;
                            }
                            break;
#ifdef COM_TXSIG_INT64
                        case COM_UINT64:
                            {
                                *(uint64*)SignalDataPtr = (uint64) txSigInvValue;
                            }
                            break;
#endif
                        case COM_BOOLEAN:
                            {
                                *(boolean*) SignalDataPtr = (boolean) (txSigInvValue != 0u);
                            }
                            break;
                        case COM_SINT8:
                            {
                                *(sint8*)SignalDataPtr =  (sint8)txSigInvValue;
                            }
                            break;
                        case COM_SINT16:
                            {
                                *(sint16*)SignalDataPtr =  (sint16)txSigInvValue;
                            }
                            break;
                        case COM_SINT32:
                            {
                                *(sint32*)SignalDataPtr =  (sint32)txSigInvValue;
                            }
                            break;
#ifdef COM_FLOAT32SUPP
                        case COM_FLOAT32:
                            {
                                txSigInvValue_32 = (uint32)txSigInvValue;
                                (void)rba_BswSrv_MemCopy( SignalDataPtr, (const void *) &txSigInvValue_32, COM_F32_SIZE_IN_BYTES );
                            }
                            break;
#endif
                        case COM_FLOAT64:
                        default:
                            break;
                        }
                    }
                    else
                    {

                        *(sint64*)SignalDataPtr =  (sint64) ((sint32) TxSigConstPtr->DataInvalid_Val);
                    }

                    Status = Com_InternalSendSignal(SignalId, (const void *) SignalDataPtr);
                 }
                 else
                 {

                     ByteNo_uo = (PduLengthType)(TxSigConstPtr->Bit_Pos >> 3u);

                     SchM_Enter_Com_TxIpduProtArea(INVALIDATESIGNAL);

                     Com_ByteCopyInit((TxIpduConstPtr->BuffPtr + ByteNo_uo), TxSigConstPtr->DataInvalid_Val
   ,                                                                            TxSigConstPtr->BitSize);

                     SchM_Exit_Com_TxIpduProtArea(INVALIDATESIGNAL);

                     Status = Com_InternalSendSignal( SignalId, (const void *)(TxIpduConstPtr->BuffPtr + ByteNo_uo) );

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

