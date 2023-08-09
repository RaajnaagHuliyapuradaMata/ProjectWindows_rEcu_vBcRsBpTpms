

#ifndef CRC_H
#define CRC_H

#include "Std_Types.h"

#include "Crc_Cfg.h"

#include "Crc_16.h"
#include "Crc_32.h"
#include "Crc_32P4.h"

#define CRC_VENDOR_ID                   6
#define CRC_MODULE_ID                   201
#define CRC_SW_MAJOR_VERSION            2
#define CRC_SW_MINOR_VERSION            0
#define CRC_SW_PATCH_VERSION            0
#define CRC_AR_RELEASE_MAJOR_VERSION    4
#define CRC_AR_RELEASE_MINOR_VERSION    2

#define CRC_START_SEC_CODE
#include "Crc_MemMap.h"
    extern void Crc_GetVersionInfo(Std_VersionInfoType * const VersionInfo);
#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.h"

#endif

