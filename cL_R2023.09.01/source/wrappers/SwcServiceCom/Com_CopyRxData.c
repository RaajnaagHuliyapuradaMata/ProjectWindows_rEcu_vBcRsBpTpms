

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
BufReq_ReturnType Com_CopyRxData(
                            PduIdType           PduId
   ,                           const PduInfoType*  PduInfoPtr
   ,                           PduLengthType*      RxBufferSizePtr
                                )
{

   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxIpduRamPtrType        RxIpduRamPtr;
    BufReq_ReturnType           return_value;

    return_value = BUFREQ_E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param_Ptr((PduId >= COM_GET_NUM_RX_IPDU), ((PduInfoPtr == NULL_PTR) || (RxBufferSizePtr == NULL_PTR))
   ,                                                                  COMServiceId_CopyRxData))
#endif
   {

        PduId           = COM_GET_RX_IPDU_ID(PduId);

        RxIpduConstPtr  = COM_GET_RX_IPDU_CONSTDATA(PduId);

        RxIpduRamPtr    = &COM_GET_RXPDURAM_S(PduId);

        if(Com_GetRamValue(RXIPDU,_LARGEDATAINPROG,RxIpduRamPtr->RxFlags))
        {

            if((RxIpduRamPtr->RxTPIPduLength + PduInfoPtr->SduLength) <= RxIpduConstPtr->Size)
            {

                if(COM_ZERO != PduInfoPtr->SduLength)
                {

                     Com_ByteCopy((RxIpduConstPtr->BuffPtr + RxIpduRamPtr->RxTPIPduLength)
   ,                                 (uint8*)(PduInfoPtr->SduDataPtr), PduInfoPtr->SduLength);
                     RxIpduRamPtr->RxTPIPduLength += PduInfoPtr->SduLength ;
                }

                *RxBufferSizePtr = RxIpduConstPtr->Size - RxIpduRamPtr->RxTPIPduLength;

                return_value = BUFREQ_OK;

            }
            else{

                return_value = BUFREQ_E_OVFL;
            }
        }
   }

    return return_value;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

