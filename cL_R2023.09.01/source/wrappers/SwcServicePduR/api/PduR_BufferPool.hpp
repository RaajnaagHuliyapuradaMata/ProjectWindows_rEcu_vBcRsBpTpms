

#ifndef PDUR_BUFFERPOOL_H_
#define PDUR_BUFFERPOOL_H_

#include "PduR_Cfg_Internal.hpp"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_Types.hpp"
#include "PduR_BufferPool_Cfg.hpp"

#define PDUR_GLOBAL_BUFFERPOOL(s)                (PduR_Global_BufferPoolPtr->s)
#define PDUR_GW_TP_BASE_BUFFERPOOL_FIXED       PDUR_GLOBAL_BUFFERPOOL(bufferPoolConst)

typedef uint16 PduRBufferPoolLengthType;

typedef struct{
   boolean                                 poolBufferStatus;
}PduR_PoolBuffer_Dynamic;

typedef PduR_PoolBuffer_Dynamic * PduR_PoolBuffer_DynamicPtr;

typedef struct{
   uint8 * poolBufferPtr;
   PduRBufferPoolLengthType              poolBufferLength;
}PduR_PoolBuffer_Fixed;

typedef const PduR_PoolBuffer_Fixed * PduR_PoolBuffer_FixedPtr;

typedef struct{
   PduRBufferPoolLengthType            freeBuffersInPool;
}PduR_BufferPool_Dynamic;

typedef PduR_BufferPool_Dynamic * PduR_BufferPool_DynamicPtr;

typedef struct{
   PduR_BufferPool_Dynamic * bufferPoolDyn;
   const PduR_PoolBuffer_Fixed * poolBufferConst;
   PduR_PoolBuffer_Dynamic * poolBufferDyn;
   PduRBufferPoolLengthType                                 maxBufferSize;
   PduRBufferPoolLengthType                                 totalBuffersInPool;
}PduR_BufferPool_Fixed;

typedef const PduR_BufferPool_Fixed * PduR_BufferPool_FixedPtr;

typedef struct{
   const PduR_BufferPool_Fixed * bufferPoolConst;
}PduR_BufferPool_ConfigType;

extern void PduR_BufferPoolInit(const PduR_BufferPool_ConfigType * BuffPoolConfigPtr);

extern BufReq_ReturnType PduR_BufferPoolRequest(  uint16 BuffPoolId
   ,                                                              PduLengthType TpSduLength
   ,                                                              PduLengthType * PduRBufferSizePtr
   ,                                                              uint8 * *bufferPtr);

extern void PduR_BufferPoolRelease(uint16 BuffPoolId, const uint8 * bufferPtr);

extern const PduR_BufferPool_ConfigType * PduR_Global_BufferPoolPtr;

extern const PduR_BufferPool_ConfigType PduR_BufferPool_Config;

#endif
#endif

