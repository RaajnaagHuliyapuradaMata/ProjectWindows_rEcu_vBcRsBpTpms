#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#if defined ( COM_RX_SIGNALGROUP_ARRAY )
#define COM_START_SEC_CODE
# include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray( Com_SignalGroupIdType SignalGroupId, uint8 * SignalGroupArrayPtr )
{
   Com_RxSigGrpConstPtrType            RxSigGrpConstPtr;
   VAR(uint8,AUTOMATIC)                returnValue_u8;
   VAR(Com_MainFuncType,AUTOMATIC)     rxMainFuncId;
   VAR(Type_CfgSwcServiceCom_tIdIPdu,AUTOMATIC)       IpduId_ui;

    returnValue_u8 = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalGroupId >= COM_GET_NUM_RX_SIGNALGRP),(SignalGroupArrayPtr == NULL_PTR)
   ,     COMServiceId_ReceiveSignalGroupArray))
#endif
   {

        SignalGroupId    = COM_GET_RXSIGNALGRP_ID( SignalGroupId );

        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA( SignalGroupId );

        IpduId_ui        = RxSigGrpConstPtr->IpduRef;

        rxMainFuncId     = (COM_GET_RX_IPDU_CONSTDATA(IpduId_ui))->MainFunctionRef;

        if( Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields) )
        {
            Com_RxSigGrpArrayConstPtrType        RxSigGrpArrayConstPtr;
            P2VAR(uint8,AUTOMATIC,COM_APPL_DATA) RxSigGrpArrayBufRamPtr;

            RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

            RxSigGrpArrayBufRamPtr =
                                &COM_GET_RXSIGGRP_ARRAY_BUFF( rxMainFuncId,RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

            if( Com_CheckRxIPduStatus((Type_SwcServiceCom_tIdPdu)IpduId_ui ) )
            {
                returnValue_u8 = E_OK;
            }

            SchM_Enter_Com_RxSigGrpArrayBuff();

            Com_ByteCopy(   ( P2VAR(uint8,AUTOMATIC,COM_APPL_DATA) )( SignalGroupArrayPtr    )
   ,     ( P2CONST(uint8,AUTOMATIC,COM_APPL_DATA) )( RxSigGrpArrayBufRamPtr )
   ,     ( uint32 )( RxSigGrpConstPtr->lastByte_u8 - RxSigGrpArrayConstPtr->FirstByteNo ) );

            SchM_Exit_Com_RxSigGrpArrayBuff();
        }
   }
    return returnValue_u8;
}
#define COM_STOP_SEC_CODE
# include "Com_MemMap.hpp"

#endif
