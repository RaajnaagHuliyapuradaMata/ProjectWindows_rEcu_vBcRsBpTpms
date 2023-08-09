

#include "PduR_Prv.h"
#include "PduR.h"
#include "PduR_BufferPool.h"

#if defined(PDUR_BUFFERPOOL_SUPPORT)

P2CONST(PduR_BufferPool_ConfigType, PDUR_VAR, PDUR_APPL_CONST) PduR_Global_BufferPoolPtr;

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_BufferPoolInit(P2CONST( PduR_BufferPool_ConfigType, AUTOMATIC, PDUR_APPL_CONST ) BuffPoolConfigPtr)
{

    PduR_BufferPool_FixedPtr BufferPoolConstPtr;
    uint8 BufferPool_Idx;
    PduRBufferPoolLengthType PoolBuffer_Idx;

    PduR_Global_BufferPoolPtr = BuffPoolConfigPtr;
    BufferPoolConstPtr = PDUR_GW_TP_BASE_BUFFERPOOL_FIXED;

    for(BufferPool_Idx = 0; BufferPool_Idx < PDUR_NUM_BUFFERPOOL; BufferPool_Idx++)
    {

        PduR_BufferPool_DynamicPtr BufferPoolDynPtr;
        PduR_PoolBuffer_DynamicPtr PoolBufferDynPtr;
        PduR_PoolBuffer_FixedPtr PoolBufferFixedPtr;

        BufferPoolDynPtr = BufferPoolConstPtr[BufferPool_Idx].bufferPoolDyn;
        PoolBufferDynPtr = BufferPoolConstPtr[BufferPool_Idx].poolBufferDyn;
        PoolBufferFixedPtr = BufferPoolConstPtr[BufferPool_Idx].poolBufferConst;

        for(PoolBuffer_Idx = 0; PoolBuffer_Idx < BufferPoolConstPtr[BufferPool_Idx].totalBuffersInPool; PoolBuffer_Idx++)
            {

                PoolBufferFixedPtr[PoolBuffer_Idx].poolBufferPtr[0] = (uint8)PoolBuffer_Idx;
                PoolBufferDynPtr[PoolBuffer_Idx].poolBufferStatus = TRUE;
            }

        BufferPoolDynPtr->freeBuffersInPool = BufferPoolConstPtr[BufferPool_Idx].totalBuffersInPool;
    }

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_BufferPoolRequest(VAR(uint16, AUTOMATIC) BuffPoolId, VAR(PduLengthType, AUTOMATIC) TpSduLength, P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) PduRBufferSizePtr, P2VAR( uint8, TYPEDEF, PDUR_VAR ) *bufferPtr)
{

    PduR_BufferPool_FixedPtr BufferPoolConstPtr;
    PduR_BufferPool_DynamicPtr BufferPoolDynPtr;
    PduRBufferPoolLengthType    FreeBuffersInPool;
    VAR(BufReq_ReturnType, AUTOMATIC)  rtn;
    PduRBufferPoolLengthType PoolBuffer_Idx;
    boolean BufferPoolReqFlag;

    BufferPoolConstPtr = PDUR_GW_TP_BASE_BUFFERPOOL_FIXED + BuffPoolId;
    BufferPoolDynPtr = BufferPoolConstPtr->bufferPoolDyn;
    FreeBuffersInPool = BufferPoolDynPtr->freeBuffersInPool;
    rtn = BUFREQ_OK;
    BufferPoolReqFlag = FALSE;

    if(TpSduLength <= BufferPoolConstPtr->maxBufferSize)
    {
        BufferPoolReqFlag = TRUE;
    }
    else
    {
#ifdef PDUR_STORE_AND_FORWARD

        BufferPoolReqFlag = TRUE;
#else
        rtn =  BUFREQ_E_OVFL;
#endif
    }

    if(BufferPoolReqFlag)
    {

        if(FreeBuffersInPool > 0)
        {

            for(PoolBuffer_Idx = 0; PoolBuffer_Idx < BufferPoolConstPtr->totalBuffersInPool; PoolBuffer_Idx++)
            {

                if((BufferPoolConstPtr->poolBufferDyn[PoolBuffer_Idx].poolBufferStatus == TRUE)
			    #ifndef PDUR_STORE_AND_FORWARD

				&& (TpSduLength <= BufferPoolConstPtr->poolBufferConst[PoolBuffer_Idx].poolBufferLength)
				#endif
				 )
                {

                    *PduRBufferSizePtr = BufferPoolConstPtr->poolBufferConst[PoolBuffer_Idx].poolBufferLength;

                    *bufferPtr = &(BufferPoolConstPtr->poolBufferConst[PoolBuffer_Idx].poolBufferPtr[1]);

                    BufferPoolConstPtr->poolBufferDyn[PoolBuffer_Idx].poolBufferStatus = FALSE;

                    FreeBuffersInPool--;
                    BufferPoolDynPtr->freeBuffersInPool = FreeBuffersInPool;

                    rtn = BUFREQ_OK;

                    break;
               }
               else
               {

                   rtn = BUFREQ_E_NOT_OK;
               }
           }
      }
      else
      {

               rtn = BUFREQ_E_NOT_OK;
       }
    }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_BufferPoolRelease(VAR(uint16, AUTOMATIC) BuffPoolId, P2CONST( uint8, TYPEDEF, PDUR_VAR ) bufferPtr)
{

    PduR_BufferPool_FixedPtr BufferPoolConstPtr;
    PduR_BufferPool_DynamicPtr BufferPoolDynPtr;
    PduRBufferPoolLengthType    FreeBuffersInPool;
    PduRBufferPoolLengthType PoolBuffer_Idx;

    BufferPoolConstPtr = PDUR_GW_TP_BASE_BUFFERPOOL_FIXED + BuffPoolId;
    BufferPoolDynPtr = BufferPoolConstPtr->bufferPoolDyn;
    FreeBuffersInPool = BufferPoolDynPtr->freeBuffersInPool;

    if(bufferPtr != NULL_PTR)
        {

            bufferPtr--;
            PoolBuffer_Idx = bufferPtr[0];

            BufferPoolConstPtr->poolBufferDyn[PoolBuffer_Idx].poolBufferStatus = TRUE;

            FreeBuffersInPool++;
            BufferPoolDynPtr->freeBuffersInPool = FreeBuffersInPool;
        }

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

