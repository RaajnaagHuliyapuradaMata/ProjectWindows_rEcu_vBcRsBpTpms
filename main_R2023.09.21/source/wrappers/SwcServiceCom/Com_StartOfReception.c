#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TP_IPDUTYPE
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(BufReq_ReturnType, COM_CODE) Com_StartOfReception( Type_SwcServiceCom_tIdPdu ComRxPduId, const Type_SwcServiceCom_stInfoPdu* TpSduInfoPtr
   ,     Type_SwcServiceCom_tLengthPdu TpSduLength, Type_SwcServiceCom_tLengthPdu* RxBufferSizePtr )
{

   Com_RxIpduConstPtrType RxIPduConstPtr;
   Com_RxIpduRamPtrType   RxIPduRamPtr;
   VAR(BufReq_ReturnType, AUTOMATIC) return_value;

    return_value = BUFREQ_E_NOT_OK;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param((ComRxPduId >= CfgSwcServiceCom_dNumIPduRx), COMServiceId_StartOfReception))
#endif
   {

        ComRxPduId     = COM_GET_RX_IPDU_ID(ComRxPduId);

        RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(ComRxPduId);

        RxIPduRamPtr   = &COM_GET_RXPDURAM_S(ComRxPduId);

        (void)TpSduInfoPtr;

        if(Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)ComRxPduId))
        {

            if(TpSduLength <= RxIPduConstPtr->Size)
            {

                Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr ->RxFlags,COM_TRUE);

                RxIPduRamPtr->RxTPIPduLength = 0;

                *RxBufferSizePtr = RxIPduConstPtr->Size;

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

