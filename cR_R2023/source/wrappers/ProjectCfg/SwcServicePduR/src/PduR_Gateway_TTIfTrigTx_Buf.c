
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_Buf_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC) gwayId,
                                                               P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) dataPtr )
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST )       gt;
    P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )       dyn;
    P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA )  infoBuf;
    VAR(uint16, AUTOMATIC)  i;
    gt      = PDUR_GW_IF_BASE + gwayId;

    dyn     = (P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )) gt->buffer;
    infoBuf = dyn->gwBuf;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    for(i = 0 ; i < infoBuf->SduLength ; i++)
    {
        *((dataPtr->SduDataPtr)+i) = *((infoBuf->SduDataPtr)+i);
    }

    dataPtr->SduLength = infoBuf->SduLength;
    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

