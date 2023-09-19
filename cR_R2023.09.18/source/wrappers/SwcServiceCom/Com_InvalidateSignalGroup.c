#include "Std_Types.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
#ifdef COM_TxGrpSigInvalid
   Com_TxSigGrpConstPtrType     TxSigGrpConstPtr;
   Com_TxGrpSigConstPtrType     TxGrpSigConstPtr;
   Com_TxIpduRamPtrType         TxIpduRamPtr;
   VAR(uint16_least, AUTOMATIC) Index_ui;

   VAR(uint16_least, AUTOMATIC) No_Of_GrpSig_ui;

   VAR(uint8, AUTOMATIC)        InvalidValueFound;
   VAR(uint8, AUTOMATIC)        Status;

    InvalidValueFound = COM_ZERO;
    Status = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP), COMServiceId_InvalidateSignalGroup))
#endif
   {

        SignalGroupId = COM_GET_TXSIGNALGRP_ID(SignalGroupId);

        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

        TxIpduRamPtr     = &COM_GET_TXPDURAM_S( TxSigGrpConstPtr->IpduRef );

        No_Of_GrpSig_ui  = (uint32)TxSigGrpConstPtr->FirstGrpSig_Index + (uint32)TxSigGrpConstPtr->No_Of_GrpSig;
        for(Index_ui = (uint16_least)TxSigGrpConstPtr->FirstGrpSig_Index; Index_ui < No_Of_GrpSig_ui; Index_ui++)
        {

            if(Com_GetValue(TXGRPSIG,_INVACTION,TxGrpSigConstPtr->txGrpSigFields))
            {
                Com_InternalInvalidateShadowSignal((Com_SignalIdType)Index_ui);

                InvalidValueFound = COM_ONE;
            }
            TxGrpSigConstPtr++;
        }

        if(InvalidValueFound != COM_ZERO)
        {
#ifdef COM_TP_IPDUTYPE

            if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
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

