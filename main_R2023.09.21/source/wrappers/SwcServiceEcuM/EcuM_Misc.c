#include "Std_Types.hpp"

#include "EcuM.hpp"

#include "EcuM_Cfg_SchM.hpp"

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "EcuM_Prv.hpp"

#if(ECUM_VERSION_INFO_API	==	STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
FUNC(void, ECUM_CODE ) EcuM_GetVersionInfo ( P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) versioninfo )
{

   if( versioninfo == NULL_PTR )
   {
#if( ECUM_DEV_ERROR_DETECT==STD_ON )

        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GETVERINFO_APIID, ECUM_E_NULL_POINTER );
#endif
   }
   else{
        versioninfo->vendorID           =   ECUM_VENDOR_ID;
        versioninfo->moduleID           =   ECUM_MODULE_ID;
        versioninfo->sw_major_version   =   ECUM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version   =   ECUM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version   =   ECUM_SW_PATCH_VERSION;
   }

    return;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
#endif//ECUM_VERSION_INFO_API
