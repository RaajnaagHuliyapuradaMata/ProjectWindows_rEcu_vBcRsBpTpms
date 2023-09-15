/******************************************************************************/
/* File   : ComM_PBcfg.c                                                      */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ComStack_Types.hpp"
#include "ComM_Cfg.hpp"
#include "ComM_Priv.hpp"
#include "Std_Types.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"
#if(COMM_INHIBITION_ENABLED)
static const uint8 ComM_DirectUsersPerChannel_ComMChannel_Can_Network_0_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_0_Channel};
#endif

static const uint8 ComM_AllUsersPerChannel_ComMChannel_Can_Network_0_Channel[] = {
   ComMConf_ComMUser_ComMUser_Can_Network_0_Channel    };

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.hpp"

const ComM_ChannelType_tst ComM_ChanelList_acst[] = {
{

#if((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif
#if(COMM_INHIBITION_ENABLED)
   ComM_DirectUsersPerChannel_ComMChannel_Can_Network_0_Channel,
#endif
   ComM_AllUsersPerChannel_ComMChannel_Can_Network_0_Channel
   ,  COMM_BUS_TYPE_CAN
   ,   NONE,
#if(COMM_PNC_GW_ENABLED != STD_OFF)
   COMM_GATEWAY_TYPE_ACTIVE,
#endif
    1000
   ,   1,
#if(COMM_PNC_ENABLED != STD_OFF)
    0xFFFF,
#endif
    0,
#if((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif
#if(COMM_INHIBITION_ENABLED)
    1
   ,   0x3,
#endif
    1,
#if(COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)

   ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel,
#endif
#if(COMM_PNC_ENABLED != STD_OFF)
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
#include "ComM_MemMap.hpp"

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

static const uint8 ComM_DirectChannelsPerUser_ComMUser_Can_Network_0_Channel[] = {
   ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel
};

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

const ComM_UserHandleType ComM_UserId_MappingTable_acst[] =
{

0
};

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.hpp"

const ComM_UsersType_tst ComM_UserList_acst[] =
{
{

   ComM_DirectChannelsPerUser_ComMUser_Can_Network_0_Channel,
#if(COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif
    1
   ,   1,
#if(COMM_PNC_ENABLED != STD_OFF)
    0
#endif
}
};

#define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.hpp"

#if(COMM_PNC_ENABLED == STD_ON)

#define COMM_START_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

#if(COMM_INHIBITION_ENABLED)

#endif

#define COMM_STOP_SEC_CONFIG_DATA_8
#include "ComM_MemMap.hpp"

#if(COMM_PNC_ENABLED != STD_OFF)
#define COMM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.hpp"

const ComM_PncConfigStruct_tst ComM_PncList_acst[] =
{
};

#define COMM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "ComM_MemMap.hpp"
#endif

#endif

#if(COMM_PNC_GW_ENABLED == STD_ON)
#define COMM_START_SEC_CONFIG_DATA_16
#include "ComM_MemMap.hpp"

#define COMM_STOP_SEC_CONFIG_DATA_16
#include "ComM_MemMap.hpp"
#endif

#if(COMM_PNC_ENABLED == STD_ON)
#define COMM_START_SEC_CONFIG_DATA_16
#include "ComM_MemMap.hpp"

const uint16 ComM_EIRA_RxSig_acu16[COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA] =
{

    0xFFFF
};

#define COMM_STOP_SEC_CONFIG_DATA_16
#include "ComM_MemMap.hpp"
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.hpp"

const ComM_GlobalConfigType_tst ComM_GlobalConfigData_cs =
{
   ComM_ChanelList_acst
   ,  ComM_UserList,
#if(COMM_PNC_ENABLED != STD_OFF)
   ComM_PncList
   ,  ComM_EIRA_RxSig_acu16,
#if(COMM_PNC_GW_ENABLED != STD_OFF)
   ComM_ERA_RxSig_acu16,
#endif
    FALSE
#endif
};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.hpp"
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.hpp"
static const Std_VersionInfoType ComM_VersionInfo =
{
    6
   ,   12
   ,   9
   ,   0
   ,   0
};
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.hpp"
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.hpp"

const Type_CfgSwcServiceComM_st ComM_Config =
{

    &ComM_GlobalConfigData_cs
   ,   &ComM_VersionInfo
};
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_MemMap.hpp"
#endif

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

