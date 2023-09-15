

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
#ifdef COM_TxGrpSigInvalid
   Com_TxSigGrpConstPtrType        TxSigGrpConstPtr;
   Com_TxGrpSigConstPtrType        TxGrpSigConstPtr;
   uint16_least                    idx_GrpSigId_u16;
   uint16_least                    maxTxGrpSigId_u16;

   uint8                           InvalidValueFound;
   uint8                           Status;

    InvalidValueFound = COM_ZERO;
    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP), COMServiceId_InvalidateSignalGroup))
#endif
   {

        SignalGroupId = COM_GET_TXSIGNALGRP_ID(SignalGroupId);

        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

        idx_GrpSigId_u16 = TxSigGrpConstPtr->FirstGrpSig_Index;
        maxTxGrpSigId_u16  = idx_GrpSigId_u16 + TxSigGrpConstPtr->No_Of_GrpSig;

        for( ; idx_GrpSigId_u16 < maxTxGrpSigId_u16; idx_GrpSigId_u16++ )
        {

            if(Com_GetValue(TXGRPSIG,_INVACTION,TxGrpSigConstPtr->txGrpSigFields))
            {
                Com_InternalInvalidateShadowSignal((Com_SignalIdType)idx_GrpSigId_u16);

                InvalidValueFound = COM_ONE;
            }
            TxGrpSigConstPtr++;
        }

        if(InvalidValueFound != COM_ZERO)
        {
#ifdef COM_TP_IPDUTYPE

            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,COM_GET_TXPDURAM_S(TxSigGrpConstPtr->IpduRef).Com_TxFlags) == COM_TRUE)
            {
                Status = COM_BUSY;

            }
            else
#endif
            {

                Status = Com_InternalSendSignalGroup(SignalGroupId);
            }
        }
        else{

        }
   }

    return (Status);
#else
    (void)SignalGroupId;
    return( COM_SERVICE_NOT_AVAILABLE );
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

