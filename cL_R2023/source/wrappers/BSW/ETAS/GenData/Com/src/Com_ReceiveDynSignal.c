

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId, void * SignalDataPtr, uint16 * LengthPtr)
{

    Com_RxSigConstPtrType       RxSigConstPtr;
    PduLengthType               StartByteNo;
    uint16                      DynLength;
    Com_SigBuffIndexType        SigBuff_Index;
    uint8                       Type;
    uint8                       Status;

    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

    if (Com_Lok_DETCheck_Param_Ptr((SignalId >= COM_GET_NUM_RX_SIGNALS),
                                  ((SignalDataPtr == NULL_PTR) || (LengthPtr == NULL_PTR)),
                                   COMServiceId_ReceiveDynSignal))
#endif
    {

        SignalId = COM_GET_RXSIGNAL_ID(SignalId);

        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(SignalId);
        SigBuff_Index = RxSigConstPtr->SigBuff_Index;
        Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);

        if (Com_CheckRxIPduStatus((PduIdType)RxSigConstPtr->IpduRef) && (COM_UINT8_DYN == Type))
        {

            StartByteNo = ( RxSigConstPtr->Bit_Pos >> 3u );

            if (COM_GET_RXPDURAM_S(RxSigConstPtr->IpduRef).RxIPduLength > StartByteNo)
            {

                DynLength = (uint16)(COM_GET_RXPDURAM_S(RxSigConstPtr->IpduRef).RxIPduLength - StartByteNo);
            }
            else
            {

                DynLength = COM_ZERO;
            }

            if (*LengthPtr >= DynLength)
            {

                SchM_Enter_Com_RxSigDynBuff();
                * LengthPtr = DynLength;
                if (COM_ZERO != DynLength)
                {
                    Com_MainFuncType rxMainFuncId;

                    rxMainFuncId = (COM_GET_RX_IPDU_CONSTDATA(RxSigConstPtr->IpduRef))->MainFunctionRef;

                    Com_ByteCopy((uint8*)SignalDataPtr,
                                  &COM_GET_SIGTYPEUINT8DYN_BUFF(rxMainFuncId,SigBuff_Index),DynLength);

                }
                SchM_Exit_Com_RxSigDynBuff();

                Status = E_OK;
            }
            else
            {
                Status = E_NOT_OK;
            }
        }
    }
    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

