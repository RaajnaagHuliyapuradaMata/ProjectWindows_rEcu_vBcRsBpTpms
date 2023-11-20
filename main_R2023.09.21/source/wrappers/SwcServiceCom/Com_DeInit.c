#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) Com_DeInit(void){

   VAR(uint16_least, AUTOMATIC) Idx_ui;
   Com_TxIpduRamPtrType TxIpduRamPtr;
   Com_RxIpduRamPtrType RxIPduRamPtr;

   if(Com_Uninit_Flag == COM_INIT)
   {

        Com_Uninit_Flag = COM_UNINIT;

        for(Idx_ui=0;Idx_ui < COM_NUM_ARR_IPDUGRPVECT ;Idx_ui++ )
        {
            Com_IpduGrpVector[Idx_ui] = (uint8)0;
            Com_IpduGrpVector_DM[Idx_ui] = (uint8)0;
        }

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);

        for(Idx_ui=0 ; Idx_ui < CfgSwcServiceCom_dNumIPduTx;Idx_ui++)
        {
            COM_GET_IPDUCOUNTER_S(Idx_ui + CfgSwcServiceCom_dNumIPduRx) = 0;

            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

            Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,COM_FALSE);

            Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxIPduTimeOut
            TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif
            TxIpduRamPtr->Com_n = 0;

            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
            TxIpduRamPtr->Com_MinDelayTick = 0;
            TxIpduRamPtr++;

        }

        RxIPduRamPtr = &COM_GET_RXPDURAM_S(0);
        for(Idx_ui=0 ; Idx_ui < CfgSwcServiceCom_dNumIPduRx;Idx_ui++)
        {

            Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr ->RxFlags,COM_FALSE);
            RxIPduRamPtr++;
            COM_GET_IPDUCOUNTER_S(Idx_ui) = 0;
            COM_GET_IPDUCOUNTER_DM(Idx_ui) = 0;
        }

   }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

