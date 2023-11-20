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

#define BOOT_TARGET_NOT_INITIALIZED 0
#define BOOT_TARGET_INITIALIZED 1

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetBootTarget( P2VAR(EcuM_BootTargetType, AUTOMATIC, ECUM_APPL_DATA)target )
{

   VAR(Std_ReturnType, AUTOMATIC) return_value_u8;

   if(target == NULL_PTR)
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)

        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_BOOT_APIID, ECUM_E_NULL_POINTER);
#endif
        return_value_u8 =  E_NOT_OK;
   }

   else{
        SchM_Enter_EcuM();

        if(EcuM_Lok_dataSelectedBootTargetInit_u8 == BOOT_TARGET_NOT_INITIALIZED)
        {

            *target = ECUM_BOOT_TARGET_OEM_BOOTLOADER;
        }
        else{

            *target = EcuM_Lok_dataSelectedBootTarget_u8;
        }

        SchM_Exit_EcuM();
        return_value_u8 =  E_OK;
   }

    return return_value_u8;
}

FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectBootTarget( VAR(EcuM_BootTargetType, AUTOMATIC) target )
{

   VAR(Std_ReturnType, AUTOMATIC) return_value_u8;

   if((target!=ECUM_BOOT_TARGET_APP)&&(target!=ECUM_BOOT_TARGET_OEM_BOOTLOADER)&&(target!=ECUM_BOOT_TARGET_SYS_BOOTLOADER))
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)

        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SEL_BOOT_APIID , ECUM_E_INVALID_PAR);
#endif
        return_value_u8 = E_NOT_OK;
   }
   else{
        SchM_Enter_EcuM();

        EcuM_Lok_dataSelectedBootTarget_u8 = target;

        EcuM_Lok_dataSelectedBootTargetInit_u8 = BOOT_TARGET_INITIALIZED;

        SchM_Exit_EcuM();
        return_value_u8 = E_OK;
   }

    return return_value_u8;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
