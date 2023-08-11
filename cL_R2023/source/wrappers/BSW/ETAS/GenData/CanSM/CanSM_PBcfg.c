

 #include "CanSM_PBcfg.h"

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

const uint8 CanSM_NetworktoCtrl_Config_acu8[] =
{
0};

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

static const uint8 CanSM_Ctrl_CanSMManagerNetwork_Can_Network_Config_au8[] =
{
   CanIfConf_CanIfCtrlCfg_Can_Network_0_CANNODE_0
};

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"

const CanSM_NetworkConf_tst CanSM_Network_Config_acst[] =
{

{
CanSM_Ctrl_CanSMManagerNetwork_Can_Network_Config_au8,4u,         10u, 2u, DemConf_DemEventParameter_EventParameter_DTC_0xd60188_Event,255,
1, 0,                       0,           FALSE,    FALSE }
};

const Type_CfgSwcServiceCanSM_st CanSM_ConfigSet[] =
{

    {
        CanSM_Network_Config_acst,
        CanSM_NetworktoCtrl_Config_acu8,

        7,
        5,
        CANSM_NUM_CAN_NETWORKS,
        0

    }
};

#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"
