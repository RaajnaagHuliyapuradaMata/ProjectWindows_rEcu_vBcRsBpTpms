

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_Buf_Transmit_Func(VAR(PduIdType, AUTOMATIC) gwayId,
                                                                 P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST )       gt;
    P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )       dyn;
    P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA )  infoBuf;

    VAR(uint16, AUTOMATIC)  i;
    gt      = PDUR_GW_IF_BASE + gwayId;

    dyn     = (P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )) gt->buffer;
    infoBuf = dyn->gwBuf;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    if(info->SduLength > dyn->confLen)
    {
        infoBuf->SduLength = dyn->confLen;
    }
    else
    {
        infoBuf->SduLength = info->SduLength;
    }

    for(i = 0 ; i < infoBuf->SduLength ; i++)
    {
        *((infoBuf->SduDataPtr)+i) = *((info->SduDataPtr)+i);
    }

    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();

    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    (void)PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, infoBuf );
    #else
    (void)PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, infoBuf );
    #endif

    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

