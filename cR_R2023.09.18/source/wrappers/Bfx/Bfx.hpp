#ifndef BFX_H
#define BFX_H

#include "Bfx_Types.hpp"
#include "Bfx_Cfg.hpp"

#if(!defined(__QACDF__) || (defined(__QACDF__) && defined(SRVLIBS)))
#include "Bfx_Bit_Inl.hpp"
#endif

#define BFX_MODULE_ID                   205
#define BFX_VENDOR_ID                   6
#define BFX_SW_MAJOR_VERSION            5
#define BFX_SW_MINOR_VERSION            0
#define BFX_SW_PATCH_VERSION            0
#define BFX_AR_RELEASE_MAJOR_VERSION    4
#define BFX_AR_RELEASE_MINOR_VERSION    2
#define BFX_AR_RELEASE_REVISION_VERSION 2

#if(BFX_VERSIONINFOAPI == STD_ON)
#define BFX_START_SEC_CODE
    #include "Bfx_MemMap.hpp"
    extern void Bfx_GetVersionInfo(Std_VersionInfoType* versionInfo);
#define BFX_STOP_SEC_CODE
    #include "Bfx_MemMap.hpp"
#endif

#endif
