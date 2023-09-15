

#include "PduR_Prv.hpp"

#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"
#include "Dem.hpp"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if(!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_DDIf_FIFO_Transmit_Func(PduIdType id, const PduInfoType * info)
{
    Std_ReturnType RetVal;
   PduInfoType infoBuf;
   const PduR_GT_If * gt = PDUR_GW_IF_BASE + id;

   PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
   PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr)(fifo->dyn);

   uint16_least i;

    SchM_Enter_PduR_LockIFGatewayTx();

   if(info->SduLength > fifo->eltSize)
   {
        infoBuf.SduLength = fifo->eltSize;
   }
   else{
        infoBuf.SduLength = info->SduLength;
   }

   infoBuf.SduDataPtr = info->SduDataPtr;

   if( 0 == dyn->txConfPending )
   {

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        RetVal = PDUR_BASE_RPTBL(loTxTablePtr)[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
#else
        RetVal = PduR_loTransmitTable[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
#endif

        if(RetVal == E_OK)
        {
            dyn->txConfPending = 1;
        }
        else{

#if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
             Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
#if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
#endif
#endif
        }
   }

   else if( dyn->used != fifo->nrElts )
   {

        dyn->actLen[dyn->writeIndex] = infoBuf.SduLength;

        for(i = 0 ; i < infoBuf.SduLength ; i++)
        {
            *( (dyn->writePtr) + i) = *( (info->SduDataPtr) + i );

        }

        PDUR_FIFO_WRITE_INC_WRAP( fifo, dyn );
        dyn->used++;
   }

   else{

        PduR_InitializePduR_Gw_If_DynStruct(dyn,fifo);

#if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
         Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
#if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
         PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
#endif
#endif

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        (void)PDUR_BASE_RPTBL(loTxTablePtr)[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
#else
        (void)PduR_loTransmitTable[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
#endif
   }

    SchM_Exit_PduR_LockIFGatewayTx();

    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

