#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#pragma PRQA_MESSAGES_OFF 1290,3408

#define APPL_VERSION                                                  "RIVIAN01"
#define APPL_VERSION_CST                                                "000003"
#define APPL_BUILD_NUMBER                                                "00911"
#define APPL_BUILD_TIME_DATE                               "07.04.2022-08:14:11"
#define APPL_BUILD_CW                                                         14
#define APPL_BUILD_YEAR                                                       22
#define APPL_VERSION_CDD                                                    "21"
#define COMPILER_NAME                                                      "GHS"
#define COMPILER_VERSION                                                "201517"
#define BCM_VERSION                                                       "Vx.x"
#define BCM_DATE                                                   "10-Jan-2018"

const Type_SwcApplTpms_stVersion g_sHufVersion = {
      APPL_VERSION
   ,  APPL_VERSION_CST
   ,  APPL_VERSION_CDD
   ,  COMPILER_NAME
   ,  COMPILER_VERSION
   ,  APPL_BUILD_TIME_DATE,
};

const struct_BCM_Version g_sBCMVersion = {
      BCM_VERSION
   ,  BCM_DATE
};

void HufIf_GetVersion(Type_SwcApplTpms_stVersion *sVersion){*sVersion = g_sHufVersion;}

