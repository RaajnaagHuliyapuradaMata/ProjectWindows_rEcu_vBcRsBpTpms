

#include "Com_Prv.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
void Com_DeInit(void)
{
    Com_TxIpduRamPtrType        TxIpduRamPtr;
    Com_RxIpduRamPtrType        RxIpduRamPtr;
    uint16_least                index_u16;

    if(Com_Uninit_Flag == COM_INIT)
    {

        Com_Uninit_Flag = COM_UNINIT;

        for (index_u16 = COM_ZERO; index_u16 < COM_NUM_ARR_IPDUGRPVECT ; index_u16++)
        {
            Com_IpduGrpVector[index_u16]    = COM_ZERO;

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
            Com_IpduGrpVector_DM[index_u16] = COM_ZERO;
#endif
        }

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);

        for (index_u16 = COM_ZERO; index_u16 < COM_GET_NUM_TX_IPDU; index_u16++)
        {
            TxIpduRamPtr->Com_TxFlags = COM_ZERO;

            COM_GET_IPDUCOUNTER_S(index_u16 + COM_GET_NUM_RX_IPDU) = COM_ZERO;

#ifdef COM_TxIPduTimeOut
            TxIpduRamPtr->Com_TickTxTimeout = COM_ZERO;
#endif
            TxIpduRamPtr->Com_n             = COM_ZERO;
            TxIpduRamPtr->Com_MinDelayTick  = COM_ZERO;

            TxIpduRamPtr++;
        }

        RxIpduRamPtr = &COM_GET_RXPDURAM_S(0);

        for (index_u16 = COM_ZERO; index_u16 < COM_GET_NUM_RX_IPDU; index_u16++)
        {
            RxIpduRamPtr->RxFlags = COM_ZERO;

            COM_GET_IPDUCOUNTER_S(index_u16)  = COM_ZERO;
# if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
            COM_GET_IPDUCOUNTER_DM(index_u16) = COM_ZERO;
# endif

            RxIpduRamPtr++;
        }

    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

