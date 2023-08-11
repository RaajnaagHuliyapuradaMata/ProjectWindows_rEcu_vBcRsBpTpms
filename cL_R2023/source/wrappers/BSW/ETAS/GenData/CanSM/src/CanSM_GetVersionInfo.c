

#include "CanSM_Prv.h"

#if (CANSM_VERSION_INFO_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
void CanSM_GetVersionInfo( Std_VersionInfoType * VersionInfo )
{
    CANSM_REPORT_ERROR((VersionInfo==NULL_PTR),
                       (uint8)CANSM_GETVERSIONINFO_SID,
                       (uint8)CANSM_E_PARAM_POINTER)

    VersionInfo->vendorID = CANSM_VENDOR_ID;
    VersionInfo->moduleID = CANSM_MODULE_ID;
    VersionInfo->sw_major_version = CANSM_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = CANSM_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = CANSM_SW_PATCH_VERSION;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

