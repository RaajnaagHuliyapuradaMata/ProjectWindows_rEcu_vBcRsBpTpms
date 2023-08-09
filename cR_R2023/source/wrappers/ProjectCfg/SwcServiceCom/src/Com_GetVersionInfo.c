

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"

#if (COM_VERSION_INFO_API == STD_ON)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_DATA) versioninfo)
{

# if(COM_CONFIGURATION_USE_DET == STD_ON)

    if(Com_Lok_DETCheck_Ptr_Only((NULL_PTR == versioninfo), COMServiceId_GetVersionInfo))
#endif
    {
        versioninfo->vendorID = COM_VENDOR_ID;
        versioninfo->moduleID = COM_MODULE_ID;
        versioninfo->sw_major_version = COM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = COM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = COM_SW_PATCH_VERSION;
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

