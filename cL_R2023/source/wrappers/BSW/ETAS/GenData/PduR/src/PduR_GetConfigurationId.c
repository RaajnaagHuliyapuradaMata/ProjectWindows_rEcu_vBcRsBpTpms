

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

uint16 PduR_GetConfigurationId( void )
{
    uint16 return_val;
#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION!= STD_OFF)
    return_val = (uint16)0;
#elif defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
    return_val=  PduR_dGetConfigurationId();
#else
    return_val= PduR_iGetConfigurationId();
#endif
    return return_val;
}

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
uint16 PduR_dGetConfigurationId( void )
{
    PDUR_CHECK_STATE_RET( PDUR_SID_GETCFGID, 0 )
    return PduR_iGetConfigurationId();
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

uint16 PduR_iGetConfigurationId( void )
{
    uint16 return_val;
#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    return_val = PduR_Base->configId;
#else
    return_val = PDUR_CONFIGURATION_ID;
#endif

    return return_val;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

