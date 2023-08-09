

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData( PduIdType PduId, const PduInfoType* PduInfoPointer,
                                                  PduLengthType* RxBufferSizePtr )
{

    Com_RxIpduConstPtrType  RxIPduConstPtr;
    Com_RxIpduRamPtrType    RxIPduRamPtr;
    VAR(BufReq_ReturnType, AUTOMATIC) return_value;

    return_value = BUFREQ_E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

    if(Com_Lok_DETCheck_Param_Ptr((PduId >= COM_GET_NUM_RX_IPDU), (PduInfoPointer == NULL_PTR),
                                                                   COMServiceId_CopyRxData))
#endif
    {

        PduId           = COM_GET_RX_IPDU_ID(PduId);

        RxIPduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(PduId);

        RxIPduRamPtr    = &COM_GET_RXPDURAM_S(PduId);

        if(Com_GetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr->RxFlags))
        {

            if((RxIPduRamPtr->RxTPIPduLength + PduInfoPointer->SduLength) <= RxIPduConstPtr->Size)
            {

                if(COM_ZERO != PduInfoPointer->SduLength)
                {

                     Com_ByteCopy((RxIPduConstPtr->BuffPtr + RxIPduRamPtr->RxTPIPduLength),
                                   (uint8*)(PduInfoPointer ->SduDataPtr),PduInfoPointer->SduLength);
                     RxIPduRamPtr->RxTPIPduLength += PduInfoPointer->SduLength ;
                }

                *RxBufferSizePtr = RxIPduConstPtr->Size - RxIPduRamPtr->RxTPIPduLength;

                return_value = BUFREQ_OK;

            }
            else
            {

                return_value = BUFREQ_E_OVFL;
            }
        }
    }

    return return_value;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

