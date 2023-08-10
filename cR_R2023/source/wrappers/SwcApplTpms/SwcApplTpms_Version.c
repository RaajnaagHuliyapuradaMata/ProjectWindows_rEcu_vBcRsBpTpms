

#include "iTpms_Interface.h"
#include "SwcApplTpms_Rte.h"
#pragma PRQA_MESSAGES_OFF 1290,3408

#define APPL_VERSION                    "RIVIAN01"
#define APPL_VERSION_CST                  "000003"
#define APPL_BUILD_NUMBER                  "00911"
#define APPL_BUILD_TIME_DATE "07.04.2022-08:14:11"
#define APPL_BUILD_CW                          14
#define APPL_BUILD_YEAR                        22
#define APPL_VERSION_CDD                     "21"
#define COMPILER_NAME                       "GHS"
#define COMPILER_VERSION                 "201517"

const struct struct_Version g_sHufVersion =
{
  APPL_VERSION,
  APPL_VERSION_CST,
  APPL_VERSION_CDD,
  COMPILER_NAME,
  COMPILER_VERSION,
  APPL_BUILD_TIME_DATE,
};

#define BCM_VERSION                        "Vx.x"
#define BCM_DATE                           "10-Jan-2018"

const struct struct_BCM_Version g_sBCMVersion =
{
  BCM_VERSION,
  BCM_DATE
};

void HufIf_GetVersion(struct struct_Version *sVersion)
{
#if 1
  *sVersion = g_sHufVersion;
#else
  sVersion->ucaApplVersion     = g_sHufVersion.ucaApplVersion;
  sVersion->ucBuild_Cw         = g_sHufVersion.ucBuild_Cw;
  sVersion->ucBuild_Date       = g_sHufVersion.ucBuild_Date;
  sVersion->ucaBuild_Nr        = g_sHufVersion.ucaBuild_Nr;
  sVersion->ucaBuild_Year      = g_sHufVersion.ucaBuild_Year;
  sVersion->ucaCompilerName    = g_sHufVersion.ucaCompilerName;
  sVersion->ucaCompilerVersion = g_sHufVersion.ucaCompilerVersion;
#endif

  ClientIf_Debug_GetVersion(sVersion);
}

