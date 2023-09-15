

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
BufReq_ReturnType Com_StartOfReception(
                                PduIdType               ComRxPduId
   ,                               const PduInfoType*      PduInfoPtr
   ,                               PduLengthType           TpSduLength
   ,                               PduLengthType*          RxBufferSizePtr
                                      )
{

   Com_RxIpduConstPtrType      RxIpduConstPtr;
   Com_RxIpduRamPtrType        RxIpduRamPtr;
    BufReq_ReturnType           return_value;

    return_value = BUFREQ_E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param_Ptr((ComRxPduId>= COM_GET_NUM_RX_IPDU), (RxBufferSizePtr == NULL_PTR)
   ,                                                                      COMServiceId_StartOfReception))
#endif
   {

        ComRxPduId     = COM_GET_RX_IPDU_ID(ComRxPduId);

        RxIpduConstPtr = COM_GET_RX_IPDU_CONSTDATA(ComRxPduId);

        RxIpduRamPtr   = &COM_GET_RXPDURAM_S(ComRxPduId);

        (void)PduInfoPtr;

        if(Com_CheckRxIPduStatus(ComRxPduId))
        {

            if(TpSduLength <= RxIpduConstPtr->Size)
            {

                Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIpduRamPtr->RxFlags,COM_TRUE);

                RxIpduRamPtr->RxTPIPduLength = COM_ZERO;

                *RxBufferSizePtr = RxIpduConstPtr->Size;

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

