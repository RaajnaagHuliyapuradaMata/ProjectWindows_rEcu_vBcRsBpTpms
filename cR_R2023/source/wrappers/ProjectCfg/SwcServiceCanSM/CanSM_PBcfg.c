

 #include "CanSM_PBcfg.h"

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

CONST(uint8, CANSM_CONST) CanSM_NetworkId_LUT[1][CANSM_NUM_CAN_NETWORKS]=
{
    {0}
};

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

CONST(uint8, CANSM_CONST) CanSM_NetworktoCtrl_Config_acu8[] =
{
    0
};

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

static CONST(uint8, CANSM_VAR) CanSM_Ctrl_CanSMManagerNetwork_Can_Network_Config_au8[] =
{
   CanIfConf_CanIfCtrlCfg_Can_Network_CANNODE_0

};

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"

CONST(CanSM_NetworkConf_tst, CANSM_CONST) CanSM_Network_Config_acst[] =
{

{
CanSM_Ctrl_CanSMManagerNetwork_Can_Network_Config_au8,4u,         10u, 2u, DemConf_DemEventParameter_DemEventParameter_CanBusoffError,255,
1, 0,                       0,           FALSE,    FALSE }

};

CONST(Type_CfgSwcServiceCanSM_st, CANSM_CONST) CanSM_ConfigSet[] =
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
