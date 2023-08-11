

#include "PduR_Prv.h"

#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)

#if defined(PDUR_DCM_SUPPORT) && (PDUR_DCM_SUPPORT != 0)
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)

#include "PduR_Dcm.h"
#include "PduR_Gw.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TP_Dcm_Transmit_Func( VAR(PduIdType, AUTOMATIC) id,
                                                             P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{

    PduLengthType bufferSizePtr;
    VAR(PduLengthType, AUTOMATIC) TpSduLength;
    BufReq_ReturnType bufReq_rtn;
    Std_ReturnType Ret_Val;
    PduR_GT_TpPtr      gt;

    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;

    PduR_TpSessDynPtr  SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE;
    while(id != gt->upId)
    {
        gt++;
    }
     fifo = (gt->buffer);
     ConnectionPtr = fifo->connectionTable;
     SessionPtr = ConnectionPtr->primarySession;
     TpSduLength = SessionPtr->SduLength;
     bufReq_rtn = BUFREQ_E_NOT_OK;
     Ret_Val = E_NOT_OK;

    bufReq_rtn = Dcm_StartOfReception(id, SessionPtr->infoPtr, TpSduLength, &bufferSizePtr);
    if(bufReq_rtn != BUFREQ_OK)
    {

        Ret_Val = E_NOT_OK;
    }
    else if(bufferSizePtr < TpSduLength)
    {

        Dcm_TpRxIndication(id,E_NOT_OK);
    }
    else
    {

        bufReq_rtn = Dcm_CopyRxData(id, info, &bufferSizePtr);
        if(bufReq_rtn != BUFREQ_OK)
        {

            Dcm_TpRxIndication(id,E_NOT_OK);
        }
        else
        {

            Dcm_TpRxIndication(id,E_OK);
            Ret_Val = E_OK;
        }
    }
    return Ret_Val;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif
#endif

#endif
