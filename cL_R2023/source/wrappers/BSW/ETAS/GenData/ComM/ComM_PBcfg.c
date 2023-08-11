

#include "ComStack_Types.h"
#include "ComM_Cfg.h"
#include "ComM_PBcfg.h"
#include "ComM_Priv.h"
#include "Std_Types.h"

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
#endif
#if (COMM_INHIBITION_ENABLED)

static const uint8 ComM_DirectUsersPerChannel_ComMChannel_Can_Network_0_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_0_Channel};

#endif

static const uint8 ComM_AllUsersPerChannel_ComMChannel_Can_Network_0_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_0_Channel    };

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"

const ComM_ChannelType_tst ComM_ChanelList_acst[] = {
{

#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_0_Channel,
#endif
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_0_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif
    1000,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0xFFFF,
#endif
    0,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif
    1,
#if (COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)

    ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel,
#endif
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif
#if(COMM_NVM_ENABLED != STD_OFF)
    FALSE,
#endif
#if(COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
    FALSE,

#endif
    FALSE
}
};

#define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

static const uint8 ComM_DirectChannelsPerUser_ComMUser_Can_Network_0_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel
};

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

const ComM_UserHandleType ComM_UserId_MappingTable_acst[] =
{

0
};

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"

const ComM_UsersType_tst ComM_UserList_acst[] =
{
{

    ComM_DirectChannelsPerUser_ComMUser_Can_Network_0_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif
}
};

#define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"

#if (COMM_PNC_ENABLED == STD_ON)

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

#if(COMM_INHIBITION_ENABLED)

#endif

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.h"

#if (COMM_PNC_ENABLED != STD_OFF)
#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"

const ComM_PncConfigStruct_tst ComM_PncList_acst[] =
{
};

#define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.h"
#endif

#endif

#if (COMM_PNC_GW_ENABLED == STD_ON)
#define COMM_START_SEC_CONFIG_DATA_16
#include "ComM_MemMap.h"

#define COMM_STOP_SEC_CONFIG_DATA_16
#include "ComM_MemMap.h"
#endif

#if (COMM_PNC_ENABLED == STD_ON)
#define COMM_START_SEC_CONFIG_DATA_16
#include "ComM_MemMap.h"

const uint16 ComM_EIRA_RxSig_acu16[COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA] =
{

    0xFFFF
};

#define COMM_STOP_SEC_CONFIG_DATA_16
#include "ComM_MemMap.h"
#endif

#if (COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.h"

const ComM_GlobalConfigType_tst ComM_GlobalConfigData_cs =
{
    ComM_ChanelList_acst,
    ComM_UserList,
#if(COMM_PNC_ENABLED != STD_OFF)
    ComM_PncList,
    ComM_EIRA_RxSig_acu16,
#if(COMM_PNC_GW_ENABLED != STD_OFF)
    ComM_ERA_RxSig_acu16,
#endif
    FALSE
#endif
};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.h"
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.h"
static const Std_VersionInfoType ComM_VersionInfo =
{
    6,
    12,
    9,
    0,
    0
};
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.h"
#endif

#if (COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.h"

const Type_CfgSwcServiceComM_st ComM_Config =
{

    &ComM_GlobalConfigData_cs,
    &ComM_VersionInfo
};
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.h"
#endif

