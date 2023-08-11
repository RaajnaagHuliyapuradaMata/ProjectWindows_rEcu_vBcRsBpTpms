

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#ifdef COM_TP_IPDUTYPE

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

void Com_TpRxIndication(PduIdType PduId, Std_ReturnType Result)
{

#if(COM_CONFIGURATION_USE_DET == STD_ON)

    if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_RX_IPDU), COMServiceId_TpRxIndication))
#endif
    {
        Com_RxIpduConstPtrType  RxIpduConstPtr;
        Com_RxIpduRamPtrType    RxIpduRamPtr;

        PduId = COM_GET_RX_IPDU_ID(PduId);

        RxIpduConstPtr    = COM_GET_RX_IPDU_CONSTDATA(PduId);
        RxIpduRamPtr      = &COM_GET_RXPDURAM_S(PduId);

        if (Com_GetRamValue(RXIPDU,_LARGEDATAINPROG,RxIpduRamPtr->RxFlags))
        {
            PduInfoType     comRxPduInfo;
            boolean         isValidRxIpdu;

            comRxPduInfo.SduDataPtr = RxIpduConstPtr->BuffPtr;

            comRxPduInfo.SduLength  = RxIpduRamPtr->RxTPIPduLength;

            isValidRxIpdu =    (E_OK == Result)
#if defined(COM_RxIPduCallOuts) || defined(COM_RX_IPDUCOUNTER)
                            && (Com_IsValidRxIpdu(PduId, &comRxPduInfo))
#endif
                            ;

#ifdef COM_RxIPduDeferredProcessing
            if (Com_GetValue(RXIPDU,_SIGPROC,RxIpduConstPtr->rxIPduFields) == COM_IMMEDIATE)
#endif
            {
                if (isValidRxIpdu)
                {

                    RxIpduRamPtr->RxIPduLength = comRxPduInfo.SduLength;

                    Com_ProcessRxIPdu(PduId,&comRxPduInfo);
                }
#ifdef COM_RXIPDU_TP_INVALIDATION
                else
                {

                    if (Com_GetValue(RXIPDU,_TP_INV_CFG,RxIpduConstPtr->rxIPduFields))
                    {
                        Com_ExecuteRxInvalidActions(PduId);
                    }
                    else
                    {

                    }
                }
#endif
            }
#ifdef COM_RxIPduDeferredProcessing
            else
            {
                if (isValidRxIpdu)
                {

                    RxIpduRamPtr->RxIPduLength = comRxPduInfo.SduLength;
                }
                else
                {
                    Com_SetRamValue(RXIPDU,_IS_INVALID,RxIpduRamPtr->RxFlags,COM_TRUE);
                }
            }
#endif

#ifdef COM_RX_MAINFUNCTION_PROC
            Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr->RxFlags,COM_TRUE);
#endif

            Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIpduRamPtr->RxFlags,COM_FALSE);
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

