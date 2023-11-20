#include "Std_Types.hpp"

#include "CanSM_Prv.hpp"

#if(CANSM_VERSION_INFO_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
FUNC(void, CANSM_CODE) CanSM_GetVersionInfo(
   P2VAR(Std_VersionInfoType, AUTOMATIC, CANSM_APPL_CODE) VersionInfo
){
   VersionInfo->vendorID         = CANSM_VENDOR_ID;
   VersionInfo->moduleID         = CANSM_MODULE_ID;
   VersionInfo->sw_major_version = CANSM_SW_MAJOR_VERSION;
   VersionInfo->sw_minor_version = CANSM_SW_MINOR_VERSION;
   VersionInfo->sw_patch_version = CANSM_SW_PATCH_VERSION;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"
#endif

