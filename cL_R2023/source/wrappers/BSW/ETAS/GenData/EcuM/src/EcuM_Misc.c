

#include "EcuM.h"

#include "EcuM_Cfg_SchM.h"

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
// #if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
// #error "AUTOSAR major version undefined or mismatched"
// #endif
// #if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
// #error "AUTOSAR minor version undefined or mismatched"
// #endif
#endif

#include "EcuM_Prv.h"

#if(ECUM_VERSION_INFO_API	==	STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"
void EcuM_GetVersionInfo ( Std_VersionInfoType * versioninfo )
{

    if ( versioninfo == NULL_PTR )
    {
#if ( ECUM_DEV_ERROR_DETECT==STD_ON )

        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GETVERINFO_APIID, ECUM_E_NULL_POINTER );
#endif
    }
    else
    {
        versioninfo->vendorID           =   ECUM_VENDOR_ID;
        versioninfo->moduleID           =   ECUM_MODULE_ID;
        versioninfo->sw_major_version   =   ECUM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version   =   ECUM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version   =   ECUM_SW_PATCH_VERSION;
    }

    return;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"
#endif//ECUM_VERSION_INFO_API