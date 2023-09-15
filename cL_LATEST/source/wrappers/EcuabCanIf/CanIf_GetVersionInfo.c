#include "CanIf_Prv.hpp"

#if(CANIF_PUBLIC_VERSIONINFO_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_GetVersionInfo(
   P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA) VersionInfo
){
   VersionInfo->vendorID         = CANIF_VENDOR_ID;
   VersionInfo->moduleID         = CANIF_MODULE_ID;
   VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION;
   VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION;
   VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif
