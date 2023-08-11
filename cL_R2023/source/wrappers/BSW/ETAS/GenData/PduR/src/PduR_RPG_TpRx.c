

#include "PduR_Prv.h"

#ifdef PDUR_RPG_FOR_RXTP_SUPPORT

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_RPG_Tp_StartOfReception_Func(PduIdType rpgId, const PduInfoType* info,PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{

    PduR_RPG_TpRxToUpPtr rpgt;
    BufReq_ReturnType rtn;

    rpgt = PDUR_RX_TP_RPG_BASE+rpgId;
    rtn = BUFREQ_E_NOT_OK;

    if (PDUR_RPG_ENROUTING_INFO(rpgt->routingCntrl_Idx) != FALSE )
    {
       rtn = PduR_upTpStartOfReceptionTable[(rpgt->loTpRxToUp.upStartOfReceptionID)].PduR_upTpStartOfReceptionFunc(rpgt->loTpRxToUp.upId,info, TpSduLength, bufferSizePtr);
    }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_RPG_Tp_CopyRxData_Func( PduIdType rpgId, const PduInfoType* info, PduLengthType* bufferSizePtr)
{

    PduR_RPG_TpRxToUpPtr rpgt;
    BufReq_ReturnType rtn;

    rpgt = PDUR_RX_TP_RPG_BASE+rpgId;
    rtn = BUFREQ_E_NOT_OK;

    if (PDUR_RPG_ENROUTING_INFO(rpgt->routingCntrl_Idx) != FALSE )
    {
       rtn = PduR_upTpCopyRxDataTable[(rpgt->loTpRxToUp.upProvideRxBufID)].PduR_upTpCopyRxDataFunc(rpgt->loTpRxToUp.upId,info, bufferSizePtr);
    }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_RPG_Tp_RxIndication_Func( PduIdType rpgId, Std_ReturnType result)
{

    PduR_RPG_TpRxToUpPtr rpgt;

    rpgt = PDUR_RX_TP_RPG_BASE+rpgId;

    PduR_upTpRxIndicationTable[(rpgt->loTpRxToUp.upRxIndicationID)].PduR_upTpRxIndicationFunc(rpgt->loTpRxToUp.upId,result);
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif
