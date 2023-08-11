

#if (!defined NVM_H_)
#define NVM_H_

#define NVM_VENDOR_ID              (30u)
#define NVM_MODULE_ID              (20u)

// RST Debug - Etas EcuM_ShutdownServices expects Autosar version 4.2.2 -> NVM has 4.0.3.
// Patch the numbers, but will this really work....? :-(
#define NVM_AR_RELEASE_MAJOR_VERSION       (4u)
#define NVM_AR_RELEASE_MINOR_VERSION       (2u)
#define NVM_AR_RELEASE_REVISION_VERSION    (2u)
//#define NVM_AR_RELEASE_MINOR_VERSION       (0u)
//#define NVM_AR_RELEASE_REVISION_VERSION    (3u)

#define NVM_SW_MAJOR_VERSION       (5u)
#define NVM_SW_MINOR_VERSION       (7u)
#define NVM_SW_PATCH_VERSION       (0u)

#include "NvM_Cfg.h"

#define NVM_E_NO_ERROR                  (0x00u)
#define NVM_E_PARAM_BLOCK_ID            (0x0Au)
#define NVM_E_PARAM_BLOCK_TYPE          (0x0Bu)
#define NVM_E_PARAM_BLOCK_DATA_IDX      (0x0Cu)
#define NVM_E_PARAM_ADDRESS             (0x0Du)

#define NVM_E_PARAM_DATA                (0x0Eu)

#define NVM_E_NOT_INITIALIZED           (0x14u)
#define NVM_E_BLOCK_PENDING             (0x15u)
#define NVM_E_BLOCK_CONFIG              (0x18u)

#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_PUBLIC_CODE) NvM_Init(void);

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetDataIndex
    (
        NvM_BlockIdType BlockId,
        uint8 DataIndex
    );

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetDataIndex
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr
    );

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetBlockProtection
    (
        NvM_BlockIdType BlockId,
        boolean ProtectionEnabled
    );
#endif

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetErrorStatus
    (
        NvM_BlockIdType BlockId,
        P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr
    );

#if (NVM_VERSION_INFO_API == STD_ON)

extern FUNC(void, NVM_PUBLIC_CODE) NvM_GetVersionInfo
    (
        P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) Versioninfo
    );
#endif

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetRamBlockStatus
    (
        NvM_BlockIdType BlockId,
        boolean BlockChanged
    );
#endif

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_ReadBlock
    (
        NvM_BlockIdType BlockId,
        P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    );

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock
    (
        NvM_BlockIdType BlockId,
        P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
    );

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_RestoreBlockDefaults
    (
        NvM_BlockIdType BlockId,
        P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    );
#endif

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_EraseNvBlock
    (
        NvM_BlockIdType BlockId
    );

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_InvalidateNvBlock
    (
        NvM_BlockIdType BlockId
    );
#endif

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_CancelJobs
    (
        NvM_BlockIdType BlockId
    );
#endif

extern FUNC(void, NVM_PUBLIC_CODE) NvM_ReadAll(void);

extern FUNC(void, NVM_PUBLIC_CODE) NvM_WriteAll(void);

extern FUNC(void, NVM_PUBLIC_CODE) NvM_CancelWriteAll(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)

extern FUNC(void, NVM_PUBLIC_CODE) NvM_KillWriteAll(void);
#endif

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)

FUNC(void, NVM_PUBLIC_CODE) NvM_RepairRedundantBlocks(void);
#endif

extern FUNC(void, NVM_PUBLIC_CODE) NvM_MainFunction(void);

extern FUNC(void, NVM_PUBLIC_CODE) NvM_SetBlockLockStatus
    (
        NvM_BlockIdType BlockId,
        boolean BlockLocked
    );

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif

