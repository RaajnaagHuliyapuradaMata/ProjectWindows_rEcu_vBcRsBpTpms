

#include "FiM_Cfg_PbCfg.h"
#include "FiM_Priv_Data.h"

#define FIM_START_SEC_ROM_CONST
#include "FiM_MemMap.h"

static const FiM_NumOffsetEventType FiM_Cfg_NumOffsetEvent_auo[FIM_CFG_NUMBEROFDEMEVENTIDS+2] =
{
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     1
};

static const FiM_NumOffsetComponentType FiM_Cfg_NumOffsetComponent_auo[FIM_CFG_NUMBEROFDEMCOMPONENTIDS+2] =
{
     0  ,
     0  ,
     0  ,
     0  ,
     0  ,
     1  ,
     1  ,
     1
};

#define FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC    (1)
static const FiM_FunctionIdType FiM_CfgInhibitSourceMatrix_au16[FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC] =
{

   // DemConf_DemEventParameter_Event_NoVin 0 - 0
FiMConf_FiMFID_FiMFID_0
};

static const FiM_InhibitionMaskType FiM_CfgInhibitMaskMatrix_au16[FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC] =
{

   // Event_NoVin 0 - 0
FIM_CFG_LAST_FAILED
};

static const FiM_FunctionIdType FiM_CfgInhibitSourceMatrixComponent_au16[FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC] =
{

   // DemConf_DemComponent_DemComponent_TpmsEcu 0 - 0
FiMConf_FiMFID_FiMFID_0

};

const Type_CfgSwcServiceFiM_st FiMConfigSet =
{
   FiM_Cfg_NumOffsetEvent_auo,
   FiM_CfgInhibitSourceMatrix_au16,
   FiM_CfgInhibitMaskMatrix_au16,
   FiM_Cfg_NumOffsetComponent_auo,
   FiM_CfgInhibitSourceMatrixComponent_au16
};

#define FIM_STOP_SEC_ROM_CONST
#include "FiM_MemMap.h"

