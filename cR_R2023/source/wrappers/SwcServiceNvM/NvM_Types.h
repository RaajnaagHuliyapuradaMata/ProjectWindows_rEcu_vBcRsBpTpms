

#if (!defined NVM_TYPES_H_)
#define NVM_TYPES_H_

#define NVM_TYPES_MAJOR_VERSION       (5u)
#define NVM_TYPES_MINOR_VERSION       (7u)
#define NVM_TYPES_PATCH_VERSION       (0u)

#ifndef Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;
#endif

#ifndef Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;
#endif

#ifndef NVM_REQ_OK
# define NVM_REQ_OK               (0u)
#endif
#ifndef NVM_REQ_NOT_OK
# define NVM_REQ_NOT_OK           (1u)
#endif
#ifndef NVM_REQ_PENDING
# define NVM_REQ_PENDING          (2u)
#endif
#ifndef NVM_REQ_INTEGRITY_FAILED
# define NVM_REQ_INTEGRITY_FAILED (3u)
#endif
#ifndef NVM_REQ_BLOCK_SKIPPED
# define NVM_REQ_BLOCK_SKIPPED    (4u)
#endif
#ifndef NVM_REQ_NV_INVALIDATED
# define NVM_REQ_NV_INVALIDATED   (5u)
#endif
#ifndef NVM_REQ_CANCELED
# define NVM_REQ_CANCELED        (6u)
#endif
#ifndef NVM_REQ_REDUNDANCY_FAILED
# define NVM_REQ_REDUNDANCY_FAILED  (7u)
#endif
#ifndef NVM_REQ_RESTORED_FROM_ROM
# define NVM_REQ_RESTORED_FROM_ROM  (8u)
#endif

#ifndef Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;
#endif

#ifndef NVM_READ_BLOCK
# define NVM_READ_BLOCK             (6u)
#endif
#ifndef NVM_WRITE_BLOCK
# define NVM_WRITE_BLOCK            (7u)
#endif
#ifndef NVM_RESTORE_BLOCK_DEFAULTS
# define NVM_RESTORE_BLOCK_DEFAULTS (8u)
#endif
#ifndef NVM_ERASE_BLOCK
# define NVM_ERASE_BLOCK            (9u)
#endif
#ifndef NVM_INVALIDATE_NV_BLOCK
# define NVM_INVALIDATE_NV_BLOCK   (11u)
#endif
#ifndef NVM_READ_ALL
# define NVM_READ_ALL              (12u)
#endif

#ifndef NVM_INIT
# define NVM_INIT                   (0u)
#endif
#ifndef NVM_SET_DATA_INDEX
# define NVM_SET_DATA_INDEX         (1u)
#endif
#ifndef NVM_GET_DATA_INDEX
# define NVM_GET_DATA_INDEX         (2u)
#endif
#ifndef NVM_SET_BLOCK_PROTECTION
# define NVM_SET_BLOCK_PROTECTION   (3u)
#endif
#ifndef NVM_GET_ERROR_STATUS
# define NVM_GET_ERROR_STATUS       (4u)
#endif
#ifndef NVM_SET_RAM_BLOCK_STATUS
# define NVM_SET_RAM_BLOCK_STATUS   (5u)
#endif

#ifndef NVM_CANCEL_WRITE_ALL
# define NVM_CANCEL_WRITE_ALL      (10u)
#endif

#ifndef NVM_WRITE_ALL
# define NVM_WRITE_ALL             (13u)
#endif
#ifndef NVM_MAINFUNCTION
# define NVM_MAINFUNCTION          (14u)
#endif
#ifndef NVM_GET_VERSION_INFO
# define NVM_GET_VERSION_INFO      (15u)
#endif

#ifndef NVM_CANCEL_JOBS
# define NVM_CANCEL_JOBS           (16u)
#endif
#ifndef NVM_SET_BLOCK_LOCK_STATUS
# define NVM_SET_BLOCK_LOCK_STATUS (19u)
#endif
#ifndef NVM_KILL_WRITE_ALL
# define NVM_KILL_WRITE_ALL        (20u)
#endif

#ifndef NVM_REPAIR_REDUNDANT_BLOCKS
# define NVM_REPAIR_REDUNDANT_BLOCKS (21u)
#endif

#endif

