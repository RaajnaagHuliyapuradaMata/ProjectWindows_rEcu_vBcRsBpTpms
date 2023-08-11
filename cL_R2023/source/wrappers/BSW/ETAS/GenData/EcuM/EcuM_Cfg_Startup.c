#include "EcuM.h"

#include "EcuM_Callout.h"
#include "EcuM_RunTime.h"

#if (ECUM_INCLUDE_DET == STD_ON)
#include "Det.h"
#endif

#include "Dem.h"
#include "Can.h"
#include "CanIf.h"
#include "ComM.h"
#include "CanSM.h"
#include "PduR.h"
#include "Com.h"
#include "Dcm.h"
#include "CanTp.h"
#include "FiM.h"
#include "EcuM_Cfg_Startup.h"
#include "EcuM_Prv.h"

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_MemMap.h"
#if  (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
void EcuM_AL_DriverRestart( const Type_CfgSwcServiceEcuM_st * ConfigPtr )
{
	(void)ConfigPtr;
}
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_MemMap.h"

	

