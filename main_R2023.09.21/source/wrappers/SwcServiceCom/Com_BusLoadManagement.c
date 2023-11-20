#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#if(COM_COMMON_TX_PERIOD == STD_ON)
#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.hpp"
VAR(uint16,COM_VAR) Com_ReducedPeriod_u16;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_ReduceBusload(VAR(uint16, AUTOMATIC) CommonPeriod)
{

  if(Com_Uninit_Flag != COM_UNINIT)
  {
      Com_ReducedPeriod_u16 = CommonPeriod;
  }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_RestoreBusload (void){
   Com_TxIpduRamPtrType TxIpduRamPtr;
   VAR( uint32_least, AUTOMATIC )   BufIdx;

   if((Com_Uninit_Flag != COM_UNINIT) && (Com_ReducedPeriod_u16 != 0))
   {
        Com_ReducedPeriod_u16 = 0;

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);
        for(BufIdx = 0; BufIdx < CfgSwcServiceCom_dNumIPduTx; BufIdx++)
        {

            if((TxIpduRamPtr->CurrentTxModePtr->Mode == (uint8)COM_TXMODE_PERIODIC)
                || (TxIpduRamPtr->CurrentTxModePtr->Mode == (uint8)COM_TXMODE_MIXED))
            {
                TxIpduRamPtr ->Com_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->TimePeriodFact;
            }

            TxIpduRamPtr++;
        }
   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

