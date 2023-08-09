

#ifndef PDUR_BUFFERPOOL_H_
#define PDUR_BUFFERPOOL_H_

#include "PduR_Cfg_Internal.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_Types.h"
#include "PduR_BufferPool_Cfg.h"

#define PDUR_GLOBAL_BUFFERPOOL(s)                (PduR_Global_BufferPoolPtr->s)
#define PDUR_GW_TP_BASE_BUFFERPOOL_FIXED       PDUR_GLOBAL_BUFFERPOOL(bufferPoolConst)

typedef uint16 PduRBufferPoolLengthType;

typedef struct
{
   boolean                                 poolBufferStatus;
} PduR_PoolBuffer_Dynamic;

typedef P2VAR( PduR_PoolBuffer_Dynamic, TYPEDEF, PDUR_VAR ) PduR_PoolBuffer_DynamicPtr;

typedef struct
{
   P2VAR( uint8, TYPEDEF, PDUR_VAR )     poolBufferPtr;
   PduRBufferPoolLengthType              poolBufferLength;
} PduR_PoolBuffer_Fixed;

typedef P2CONST( PduR_PoolBuffer_Fixed, TYPEDEF, PDUR_CONST ) PduR_PoolBuffer_FixedPtr;

typedef struct
{
    PduRBufferPoolLengthType            freeBuffersInPool;
} PduR_BufferPool_Dynamic;

typedef P2VAR( PduR_BufferPool_Dynamic, TYPEDEF, PDUR_VAR ) PduR_BufferPool_DynamicPtr;

typedef struct
{
   P2VAR( PduR_BufferPool_Dynamic, TYPEDEF, PDUR_VAR )      bufferPoolDyn;
   P2CONST( PduR_PoolBuffer_Fixed, TYPEDEF, PDUR_CONST )    poolBufferConst;
   P2VAR( PduR_PoolBuffer_Dynamic, TYPEDEF, PDUR_VAR )      poolBufferDyn;
   PduRBufferPoolLengthType                                 maxBufferSize;
   PduRBufferPoolLengthType                                 totalBuffersInPool;
} PduR_BufferPool_Fixed;

typedef P2CONST( PduR_BufferPool_Fixed, TYPEDEF, PDUR_CONST ) PduR_BufferPool_FixedPtr;

typedef struct
{
   P2CONST( PduR_BufferPool_Fixed, TYPEDEF, PDUR_CONST )     bufferPoolConst;

} PduR_BufferPool_ConfigType;

extern FUNC( void, PDUR_CODE ) PduR_BufferPoolInit(P2CONST( PduR_BufferPool_ConfigType, AUTOMATIC, PDUR_APPL_CONST ) BuffPoolConfigPtr);

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_BufferPoolRequest(  VAR(uint16, AUTOMATIC) BuffPoolId,
                                                               VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                               P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) PduRBufferSizePtr,
                                                               P2VAR( uint8, TYPEDEF, PDUR_VAR ) *bufferPtr);

extern FUNC( void, PDUR_CODE ) PduR_BufferPoolRelease(VAR(uint16, AUTOMATIC) BuffPoolId, P2CONST( uint8, TYPEDEF, PDUR_VAR ) bufferPtr);

extern P2CONST(PduR_BufferPool_ConfigType, PDUR_VAR, PDUR_APPL_CONST) PduR_Global_BufferPoolPtr;

extern CONST( PduR_BufferPool_ConfigType, PDUR_CONST )  PduR_BufferPool_Config;

#endif
#endif

