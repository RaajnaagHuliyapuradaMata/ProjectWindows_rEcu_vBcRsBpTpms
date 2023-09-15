

#include "PduR_Prv.hpp"

#if defined(PDUR_VERSION_INFO_API) && (PDUR_VERSION_INFO_API != STD_OFF)

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduR_GetVersionInfo( Std_VersionInfoType * versionInfo )
{

   PDUR_CHECK_PTR_VOID(PDUR_SID_GETVERINFO, versionInfo)

    (versionInfo)->vendorID = PDUR_VENDOR_ID;
    (versionInfo)->moduleID = PDUR_MODULE_ID;
    (versionInfo)->sw_major_version = PDUR_SW_MAJOR_VERSION;
    (versionInfo)->sw_minor_version = PDUR_SW_MINOR_VERSION;
    (versionInfo)->sw_patch_version = PDUR_SW_PATCH_VERSION;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

