

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#include "Dem.h"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "PduR.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_GF_TTIf_FIFO_Transmit_Func( PduIdType gwayId,
                                                                   const PduInfoType * info)
{
    const PduR_GT_If * gt = PDUR_GW_IF_BASE + gwayId;

    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr)(fifo->dyn);
    PduInfoType infoBuf;
    uint8 callTx   = 0u;
    uint8 logError = 0u;

    uint16 i;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    if(info->SduLength > fifo->eltSize)
    {
        infoBuf.SduLength = fifo->eltSize;
    }
    else
    {
        infoBuf.SduLength = info->SduLength;
    }

    if( 0 == dyn->txConfPending )
    {

        dyn->txConfPending = 1;
        callTx = 1;

    }

    else
    {
        if( dyn->used == fifo->nrElts )
        {

            PduR_InitializePduR_Gw_If_DynStruct(dyn,fifo);

            callTx = 1;

            logError = 1;

        }
        else
        {

        }

    }

    dyn->actLen[dyn->writeIndex] = infoBuf.SduLength;
    for(i = 0 ; i < infoBuf.SduLength ; i++)
    {
        *((dyn->writePtr)+i) = *((info->SduDataPtr)+i);
    }

    PDUR_FIFO_WRITE_INC_WRAP( fifo, dyn);
    dyn->used++;

    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();

    if( 1 == logError )
    {
        #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
         Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
        #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
         PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
        #endif
        #endif
    }

    if( 1 == callTx )
    {

        infoBuf.SduDataPtr = info->SduDataPtr;

        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        if( E_OK != PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &infoBuf ))
        #else
        if( E_OK != PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &infoBuf ))
        #endif
        {

            PduR_InitializePduR_Gw_If_DynStruct(dyn,fifo);

            #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
             Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
            #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
            #endif
            #endif

        }
    }

    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

