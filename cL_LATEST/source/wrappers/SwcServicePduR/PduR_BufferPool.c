

#include "PduR_Prv.hpp"
#include "PduR.hpp"
#include "PduR_Cfg_Internal.hpp"

#if defined(PDUR_BUFFERPOOL_SUPPORT)

const PduR_BufferPool_ConfigType * PduR_Global_BufferPoolPtr;

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_BufferPoolInit(const PduR_BufferPool_ConfigType * BuffPoolConfigPtr)
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
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

BufReq_ReturnType PduR_BufferPoolRequest(uint16 BuffPoolId, Type_SwcServiceCom_tLengthPdu TpSduLength, Type_SwcServiceCom_tLengthPdu * PduRBufferSizePtr, uint8 * *bufferPtr)
{

   PduR_BufferPool_FixedPtr BufferPoolConstPtr;
   PduR_BufferPool_DynamicPtr BufferPoolDynPtr;
   PduRBufferPoolLengthType    FreeBuffersInPool;
    BufReq_ReturnType rtn;
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
   else{
#ifdef PDUR_STORE_AND_FORWARD

        BufferPoolReqFlag = TRUE;
#else
        rtn =  BUFREQ_E_OVFL;
#endif
   }

   if(BufferPoolReqFlag != FALSE)
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
               else{

                   rtn = BUFREQ_E_NOT_OK;
               }
           }
      }
      else{

               rtn = BUFREQ_E_NOT_OK;
       }
   }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_BufferPoolRelease(uint16 BuffPoolId, const uint8 * bufferPtr)
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
#include "PduR_MemMap.hpp"

#endif

