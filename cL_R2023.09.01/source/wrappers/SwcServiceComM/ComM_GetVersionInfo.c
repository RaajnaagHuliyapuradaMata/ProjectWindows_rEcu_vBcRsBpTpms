

#include "ComM_Priv.hpp"

#if(COMM_VERSION_INFO_API == STD_ON)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_GetVersionInfo(Std_VersionInfoType * versioninfo)
{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
    Std_ReturnType   ret_Val;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
    ret_Val = E_OK;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
   if(versioninfo == NULL_PTR)
   {

        ret_Val = Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GETVERINFO_APIID,COMM_E_WRONG_PARAMETERS);
        return;
   }
    (void) (ret_Val);
#endif

   versioninfo->vendorID = COMM_VENDOR_ID;
   versioninfo->moduleID = COMM_MODULE_ID;
   versioninfo->sw_major_version = COMM_SW_MAJOR_VERSION;
   versioninfo->sw_minor_version = COMM_SW_MINOR_VERSION;
   versioninfo->sw_patch_version = COMM_SW_PATCH_VERSION;
    return;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

