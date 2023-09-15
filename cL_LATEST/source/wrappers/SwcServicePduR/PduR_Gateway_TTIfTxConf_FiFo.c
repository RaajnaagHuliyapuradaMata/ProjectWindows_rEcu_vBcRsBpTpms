
#include "PduR_Prv.hpp"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

#if(AUTOSAR_VERSION_AR42 == STD_ON)
void PduR_GF_TTIf_FIFO_TxConfirmation_Func( Type_SwcServiceCom_tIdPdu gwayId )
#else

void PduR_GF_TTIf_FIFO_TxConfirmation_Func( Type_SwcServiceCom_tIdPdu gwayId,Std_ReturnType result)
#endif
{
   const PduR_GT_If * gt = PDUR_GW_IF_BASE + gwayId;

   PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
   PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr) fifo->dyn;
   Type_SwcServiceCom_stInfoPdu info;

    SchM_Enter_PduR_LockIFGatewayTriggerTxConf();

   if( 0 != dyn->txConfPending )
   {
        uint8 BreakFlag = 0;

        while( BreakFlag == 0 )
        {
            if( 1 == dyn->used )
            {

                PduR_InitializePduR_Gw_If_DynStruct(dyn,fifo);
                BreakFlag = 1;
            }
            else{

                PDUR_FIFO_READ_INC_WRAP( fifo, dyn);
                dyn->used--;

                info.SduDataPtr = dyn->readPtr;
                info.SduLength = dyn->actLen[dyn->readIndex];

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                if( E_OK == PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &info ))
#else
                if( E_OK == PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &info ))
#endif
                {
                    BreakFlag = 1;
                }
            }
        }

   }

    SchM_Exit_PduR_LockIFGatewayTriggerTxConf();

#if(AUTOSAR_VERSION_AR42 == STD_OFF)
    (void)result;
#endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

