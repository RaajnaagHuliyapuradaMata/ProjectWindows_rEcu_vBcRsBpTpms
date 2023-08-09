

#if !defined MEMIF_H
# define MEMIF_H

# include "MemIf_Types.h"
# include "MemIf_Cfg.h"

# define MEMIF_MODULE_ID                    (22u)
# define MEMIF_VENDOR_ID                    (30u)
# define MEMIF_INSTANCE_ID                  (0u)

# define MEMIF_AR_RELEASE_MAJOR_VERSION     (4u)
# define MEMIF_AR_RELEASE_MINOR_VERSION     (0u)
# define MEMIF_AR_RELEASE_REVISION_VERSION  (3u)

# define MEMIF_SW_MAJOR_VERSION             (3u)
# define MEMIF_SW_MINOR_VERSION             (3u)
# define MEMIF_SW_PATCH_VERSION             (1u)

# define MEMIF_BROADCAST_ID                 (0xFFu)

# define MEMIF_SID_SETMODE                  (0x01U)
# define MEMIF_SID_READ                     (0x02U)
# define MEMIF_SID_WRITE                    (0x03U)
# define MEMIF_SID_CANCEL                   (0x04U)
# define MEMIF_SID_GET_STATUS               (0x05U)
# define MEMIF_SID_GET_JOB_RESULT           (0x06U)
# define MEMIF_SID_INVALIDATE               (0x07U)
# define MEMIF_SID_VERSION_INFO             (0x08u)
# define MEMIF_SID_ERASE                    (0x09u)

# if ( MEMIF_NUMBER_OF_DEVICES == 0 )
#  error "No Memory Hardware Abstraction Devices (EA/FEE) defined!"
# endif

# define MEMIF_START_SEC_CODE
# include "MemMap.h"

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(uint8 DeviceIndex, uint16 BlockNumber, uint16 BlockOffset, MemIf_DataPtr_pu8 DataBufferPtr, uint16 Length);

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(uint8 DeviceIndex, uint16 BlockNumber, MemIf_DataPtr_pu8 DataBufferPtr);

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(uint8  DeviceIndex, uint16 BlockNumber);

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(uint8 DeviceIndex, uint16 BlockNumber);

FUNC(void, MEMIF_CODE) MemIf_Cancel(uint8 DeviceIndex);

FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(uint8 DeviceIndex);

FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(uint8 DeviceIndex);

# if (MEMIF_VERSION_INFO_API == STD_ON)

void MemIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr);
# endif

FUNC(void, MEMIF_CODE) MemIf_SetMode(MemIf_ModeType Mode);

# define MEMIF_STOP_SEC_CODE
# include "MemMap.h"

#endif

