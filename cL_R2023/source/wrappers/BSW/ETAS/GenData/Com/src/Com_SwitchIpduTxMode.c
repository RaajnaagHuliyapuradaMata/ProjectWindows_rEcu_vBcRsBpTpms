

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode)
{

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_SwitchIpduTxMode))
#endif
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        if (Com_CheckTxIPduStatus(PduId))
        {
            Com_TxIpduConstPtrType      TxIpduConstPtr;
            Com_TxIpduRamPtrType        TxIpduRamPtr;

            TxIpduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);
            TxIpduRamPtr   = &COM_GET_TXPDURAM_S(PduId);

#ifdef COM_TP_IPDUTYPE

            if (Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
#endif
            {

                if (Com_GetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode) != Mode)
                {

                    Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                    SchM_Enter_Com_TxIpduProtArea(SWITCHTXIPDU);

                    Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);

                    Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIpduConstPtr,Mode);

                    Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);

# ifdef COM_MIXEDPHASESHIFT

                    Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,
                                    TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
# endif

                    SchM_Exit_Com_TxIpduProtArea(SWITCHTXIPDU);

                    sendIpduFlag_u16.isEventTrig     = COM_SET;

                    sendIpduFlag_u16.isModeChangd    = COM_SET;

                    sendIpduFlag_u16.isSwtIpduTxMode = COM_SET;

                    Com_Lok_SendIpdu(PduId, sendIpduFlag_u16);
                }
                else
                {

                }
            }
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

