

#include "CanIf_Prv.h"

#if (CANIF_PUBLIC_VERSIONINFO_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
FUNC(void, CANIF_CODE) CanIf_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA) VersionInfo)
{

    CANIF_DET_REPORT_ERROR_VOID_RET(VersionInfo == NULL_PTR, CANIF_GET_VERSION_INFO_SID, CANIF_E_PARAM_POINTER)

    VersionInfo->vendorID = CANIF_VENDOR_ID;
    VersionInfo->moduleID = CANIF_MODULE_ID;
    VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION;

}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif
