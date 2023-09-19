#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TP_IPDUTYPE
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_TpRxIndication( Type_SwcServiceCom_tIdPdu PduId, Std_ReturnType Result )
{

   Com_RxIpduConstPtrType RxIPduConstPtr;
   Com_RxIpduRamPtrType   RxIPduRamPtr;
   VAR(uint8, AUTOMATIC)  ConstByteValue_u8;

#if(COM_CONFIGURATION_USE_DET == STD_ON)

   if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_RX_IPDU), COMServiceId_TpRxIndication))
#endif
   {

        PduId = COM_GET_RX_IPDU_ID(PduId);

        RxIPduConstPtr    = COM_GET_RX_IPDU_CONSTDATA(PduId);
        RxIPduRamPtr      = &COM_GET_RXPDURAM_S(PduId);

        ConstByteValue_u8 = RxIPduConstPtr->rxIPduFields;

        if((Com_GetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr ->RxFlags)) && (Result == E_OK))
        {

            Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr ->RxFlags,COM_FALSE);

            Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr ->RxFlags,COM_TRUE);

            RxIPduRamPtr->RxIPduLength = RxIPduRamPtr->RxTPIPduLength;

            if(Com_GetValue(RXIPDU,_SIGPROC,ConstByteValue_u8) == COM_IMMEDIATE)
            {
                VAR(Type_SwcServiceCom_stInfoPdu, COM_VAR) TPRxIPduInfo;

                TPRxIPduInfo.SduDataPtr = RxIPduConstPtr->BuffPtr;
                TPRxIPduInfo.SduLength  = RxIPduRamPtr->RxIPduLength;

                Com_ProcessRxIPdu(PduId,&TPRxIPduInfo);
            }
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

