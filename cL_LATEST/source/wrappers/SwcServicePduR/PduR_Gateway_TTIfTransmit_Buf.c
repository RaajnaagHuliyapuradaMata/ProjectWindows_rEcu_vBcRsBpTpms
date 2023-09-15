

#include "PduR_Prv.hpp"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"
#include "PduR.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_TTIf_Buf_Transmit_Func(Type_SwcServiceCom_tIdPdu gwayId
   ,                                                                const Type_SwcServiceCom_stInfoPdu * info)
{
   const PduR_GT_If * gt;
   PduR_Buf_If_dynamic   *dyn;
   Type_SwcServiceCom_stInfoPdu * infoBuf;
    Std_ReturnType rtn;

   uint16 i;
    gt      = PDUR_GW_IF_BASE + gwayId;

    dyn     = (PduR_Buf_If_dynamic *) gt->buffer;
   infoBuf = dyn->gwBuf;
    rtn = E_NOT_OK;

    SchM_Enter_PduR_LockIFGatewayTriggerTx();

   if(dyn->Tx_Status == PDUR_TX_IDLE)
   {
        if(info->SduLength > dyn->confLen)
        {
            infoBuf->SduLength = dyn->confLen;
        }
        else{
            infoBuf->SduLength = info->SduLength;
        }

        for(i = 0 ; i < infoBuf->SduLength ; i++)
        {
            *((infoBuf->SduDataPtr)+i) = *((info->SduDataPtr)+i);
        }

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        (void)PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, infoBuf );
#else
        (void)PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, infoBuf );
#endif

        dyn->Tx_Status = PDUR_TX_INPROGRESS;
        rtn = E_OK;
   }
   else{
        rtn = E_NOT_OK;
   }

    SchM_Exit_PduR_LockIFGatewayTriggerTx();

    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

