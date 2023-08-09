

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_SwitchIpduTxMode(VAR(PduIdType, AUTOMATIC) PduId, VAR(boolean, AUTOMATIC) Mode)
{
    Com_TxIpduConstPtrType TxIPduConstPtr;
    Com_TxIpduRamPtrType TxIpduRamPtr;
    VAR(uint8, AUTOMATIC) LatestTransMode_u8;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
    if(Com_Lok_DETCheck_Param((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_SwitchIpduTxMode))
#endif
    {

        PduId = COM_GET_TX_IPDU_ID(PduId);

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);

        if((Com_GetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode) != Mode))

        {

            Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);

            Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),Mode);

            Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);
            LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;

    #ifdef COM_MIXEDPHASESHIFT

            Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
    #endif

            if (LatestTransMode_u8 != COM_TXMODE_NONE)
            {

                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;
                sendIpduFlag_u16.isEventTrig      =  COM_SET;

                sendIpduFlag_u16.isModeChangd     =  COM_SET;

                Com_Lok_SendIpdu((PduIdType)PduId, sendIpduFlag_u16);
            }
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

