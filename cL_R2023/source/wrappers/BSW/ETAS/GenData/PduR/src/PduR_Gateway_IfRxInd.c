
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_GF_If_RxIndication_Func( PduIdType gwayId, const PduInfoType * data)
{
    const PduR_GT_IfTx * gt = PDUR_GW_IF_TX_BASE + gwayId;

    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    (void)PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc(gt->loId, data);
    #else
    (void)PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc(gt->loId, data);
    #endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

