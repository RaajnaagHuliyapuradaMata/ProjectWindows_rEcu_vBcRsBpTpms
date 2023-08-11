#include "EcuM.h"
#include "EcuM_Cfg_Startup.h"

#define ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_MemMap.h"
const Type_CfgSwcServiceEcuM_st EcuM_Config =
{
    OSDEFAULTAPPMODE,
    {          ECUM_SHUTDOWN_TARGET_OFF    ,        0    ,        0    },
    {
            &CanIf_Config,
            NULL_PTR,
            &CanSM_Config,
            &PduR_Config,
            NULL_PTR,
            &CanTp_Config,
            NULL_PTR,
    &BswM_Config
    },
        &EcuM_Cfg_dataWkupPNCRef_cast[0],
    {
        0xD4 , 0x1D , 0x8C , 0xD9 , 0x8F , 0x00 , 0xB2 , 0x04 , 0xE9 , 0x80 , 0x09 , 0x98 , 0xEC , 0xF8 , 0x42 , 0x7E
    }
};

const Type_CfgSwcServiceEcuM_st * const EcuM_EcuMConfigurations_cpcast[ECUM_NO_OF_ECUMCONFIGSETS]=
{
    &EcuM_Config
};
#define ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_MemMap.h"

