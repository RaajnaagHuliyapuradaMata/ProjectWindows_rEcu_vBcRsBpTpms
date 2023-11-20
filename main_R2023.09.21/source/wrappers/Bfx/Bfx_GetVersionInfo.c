#define SRVLIBS

#include "Std_Types.hpp"

#include "Bfx.hpp"

#if(BFX_VERSIONINFOAPI == STD_ON)

#define BFX_START_SEC_CODE
    #include "Bfx_MemMap.hpp"
   void Bfx_GetVersionInfo(Std_VersionInfoType* versionInfo)
   {
        versionInfo->vendorID = BFX_VENDOR_ID;
        versionInfo->moduleID = BFX_MODULE_ID;
        versionInfo->sw_major_version = BFX_SW_MAJOR_VERSION;
        versionInfo->sw_minor_version = BFX_SW_MINOR_VERSION;
        versionInfo->sw_patch_version = BFX_SW_PATCH_VERSION;
   }
#define BFX_STOP_SEC_CODE
    #include "Bfx_MemMap.hpp"

#endif

