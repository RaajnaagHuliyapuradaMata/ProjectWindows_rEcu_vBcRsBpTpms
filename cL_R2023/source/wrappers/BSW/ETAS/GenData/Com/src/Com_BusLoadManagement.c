

#include "Com_Prv.h"

#if (COM_COMMON_TX_PERIOD == STD_ON)

#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
uint16 Com_ReducedPeriod_u16;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_ReduceBusload(uint16 CommonPeriod)
{

    if (Com_Uninit_Flag != COM_UNINIT)
    {
        Com_ReducedPeriod_u16 = CommonPeriod;
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_RestoreBusload (void)
{
    Com_TxIpduRamPtrType        TxIpduRamPtr;
    uint16_least                idx_TxIpduId_u16;

    if ((Com_Uninit_Flag != COM_UNINIT) && (Com_ReducedPeriod_u16 != COM_ZERO))
    {
        Com_ReducedPeriod_u16 = COM_ZERO;

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);

        for (idx_TxIpduId_u16 = COM_ZERO; idx_TxIpduId_u16 < COM_GET_NUM_TX_IPDU; idx_TxIpduId_u16++)
        {

            if (COM_TX_MODE_IS_CYCLIC(TxIpduRamPtr->CurrentTxModePtr->Mode))
            {
                TxIpduRamPtr->Com_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->TimePeriodFact;
            }

            TxIpduRamPtr++;
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

