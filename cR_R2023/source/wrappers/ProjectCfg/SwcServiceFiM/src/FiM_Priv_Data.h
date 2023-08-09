

#ifndef FIM_PRIV_DATA_H
#define FIM_PRIV_DATA_H

#include "FiM_Cfg_Fids.h"
#include "FiM_Cfg.h"

#define FIM_RB_NO_INHIBITS              0u
#define FIM_CFG_LAST_FAILED             1u
#define FIM_CFG_NOT_TESTED              2u
#define FIM_CFG_TESTED                  3u
#define FIM_CFG_TESTED_AND_FAILED       4u
#define FIM_CFG_FAILED_OR_NOT_TESTED    5u

#if (FIM_CFG_MAXIMUM_LINKS_PER_FID_CALC <= 0xFF)
typedef uint8 FiM_FIdStatusCounterType;
#define FIM_CFG_STATUSCOUNTERMAX 0xFF
#else
typedef uint16 FiM_FIdStatusCounterType;
#define FIM_CFG_STATUSCOUNTERMAX 0xFFFF
#endif

#endif
