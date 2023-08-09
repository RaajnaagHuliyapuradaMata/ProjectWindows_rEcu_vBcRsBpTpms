

#ifndef BFX_H
#define BFX_H

#include "Std_Types.h"
#include "Bfx_Types.h"
#include "Bfx_Cfg.h"

#if (!defined(__QACDF__) || (defined(__QACDF__) && defined(SRVLIBS)))

#include "Bfx_Bit_Inl.h"
#if ((BFX_CFG_OPTIMIZATION == BFX_CFG_TCCOMMON) || (BFX_CFG_OPTIMIZATION == BFX_CFG_TC27XX))
    #include "rba_BfxTCCommon_Bit_Inl.h"
#endif
#if ((BFX_CFG_OPTIMIZATION == BFX_CFG_MPCCOMMON) || (BFX_CFG_OPTIMIZATION == BFX_CFG_MPCCUT2))
    #include "rba_BfxMPCCommon_Bit_Inl.h"
#endif

#endif

#define BFX_MODULE_ID                   205
#define BFX_VENDOR_ID                   6
#define BFX_SW_MAJOR_VERSION            5
#define BFX_SW_MINOR_VERSION            0
#define BFX_SW_PATCH_VERSION            0
#define BFX_AR_RELEASE_MAJOR_VERSION    4
#define BFX_AR_RELEASE_MINOR_VERSION    2
#define BFX_AR_RELEASE_REVISION_VERSION 2

#if (BFX_VERSIONINFOAPI == STD_ON)
    #define BFX_START_SEC_CODE
    #include "Bfx_MemMap.h"
    extern void Bfx_GetVersionInfo(Std_VersionInfoType* versionInfo);
    #define BFX_STOP_SEC_CODE
    #include "Bfx_MemMap.h"
#endif

#endif
