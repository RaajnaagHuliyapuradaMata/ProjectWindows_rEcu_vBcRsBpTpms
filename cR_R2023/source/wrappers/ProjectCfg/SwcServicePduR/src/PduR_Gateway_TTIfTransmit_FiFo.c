

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#include "Dem.h"
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "PduR.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_FIFO_Transmit_Func( VAR(PduIdType, AUTOMATIC) gwayId,
                                                                   P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;

    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr)(fifo->dyn);
    VAR(PduInfoType, AUTOMATIC)    infoBuf;
    VAR(uint8, AUTOMATIC)  callTx   = 0u;
    VAR(uint8, AUTOMATIC)  logError = 0u;

    VAR(uint16, AUTOMATIC)  i;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    if(info->SduLength > fifo->eltSize)
    {
        infoBuf.SduLength = fifo->eltSize;
    }
    else
    {
        infoBuf.SduLength = info->SduLength;
    }

    dyn->actLen = infoBuf.SduLength;

    if( 0 == dyn->txConfPending )
    {

        dyn->txConfPending = 1;
        callTx = 1;

    }

    else
    {
        if( dyn->used == fifo->nrElts )
        {

            dyn->writePtr = dyn->readPtr;
            dyn->used = 0;

            callTx = 1;

            logError = 1;

        }
        else
        {

        }

    }

    for(i = 0 ; i < infoBuf.SduLength ; i++)
    {
        *((dyn->writePtr)+i) = *((info->SduDataPtr)+i);
    }

    PDUR_FIFO_INC_AND_WRAP( fifo, dyn->writePtr );
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

            dyn->writePtr = fifo->begin;
            dyn->readPtr = dyn->writePtr;
            dyn->used = 0;
            dyn->txConfPending = 0;

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

