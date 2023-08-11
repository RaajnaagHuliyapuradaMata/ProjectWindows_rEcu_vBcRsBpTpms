

#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

#include "Std_Types.h"

#define MEMIF_TYPES_AR_RELEASE_MAJOR_VERSION     (4u)
#define MEMIF_TYPES_AR_RELEASE_MINOR_VERSION     (0u)
#define MEMIF_TYPES_AR_RELEASE_REVISION_VERSION  (3u)

#define MEMIF_TYPES_SW_MAJOR_VERSION             (3u)
#define MEMIF_TYPES_SW_MINOR_VERSION             (3u)
#define MEMIF_TYPES_SW_PATCH_VERSION             (1u)

#define MEMIF_E_NO_ERROR               (0x00u)
#define MEMIF_E_PARAM_DEVICE           (0x01u)
#define MEMIF_E_PARAM_POINTER          (0x02u)

typedef enum
{
  MEMIF_UNINIT = 0,
  MEMIF_IDLE,
  MEMIF_BUSY,
  MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

typedef enum
{
  MEMIF_JOB_OK = 0,
  MEMIF_JOB_FAILED,
  MEMIF_JOB_PENDING,
  MEMIF_JOB_CANCELED,
  MEMIF_BLOCK_INCONSISTENT,
  MEMIF_BLOCK_INVALID
} MemIf_JobResultType;

typedef enum
{
    MEMIF_MODE_SLOW = 0,
    MEMIF_MODE_FAST
} MemIf_ModeType;

typedef P2VAR(uint8, AUTOMATIC, MEMIF_APPL_DATA) MemIf_DataPtr_pu8;
typedef P2CONST(uint8, AUTOMATIC, MEMIF_APPL_DATA) MemIf_ConstDataPtr_pu8;

typedef uint32 MemIf_AddressType;
typedef uint32 MemIf_LengthType;

#define MEMIF_JOB_CANCELLED     MEMIF_JOB_CANCELED

#endif

