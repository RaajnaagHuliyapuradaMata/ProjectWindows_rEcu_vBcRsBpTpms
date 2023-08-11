

#ifndef FIM_STATUS_H
#define FIM_STATUS_H

#include "FiM_Priv_Data.h"
#include "FiM_Utils.h"
#include "FiM_Det.h"
#include "FiM_Cfg_SchM.h"

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
extern uint8 FiM_FIdStatusBitArray_au8[2][(FIM_CFG_NUMBEROFFIDS + 1 + 7) / 8];
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)

extern uint8 FiM_FIdStatusServ07BitArray_au8[2][(FIM_CFG_NUMBEROFFIDS + 1 + 7) / 8];
#endif
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"
extern uint8 FiM_LastIdx;
extern uint8 FiM_CurrentIdx;
#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"

#else

#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
extern FiM_FIdStatusCounterType FiM_FIdStatusCounter_auo[FIM_CFG_NUMBEROFFIDS+1];
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
extern FiM_FIdStatusCounterType FiM_FIdServ07StatusCounter_auo[FIM_CFG_NUMBEROFFIDS+1];
#endif
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#endif

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"
void FiM_Priv_StatusInit(void);

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)

LOCAL_INLINE FiM_FIdStatusCounterType FiM_Priv_FIdGetInhibitCounter(FiM_FunctionIdType FId)
{
    return (FiM_FIdStatusCounter_auo[FId]);
}
#endif

LOCAL_INLINE boolean FiM_Priv_FIdGetPermission(FiM_FunctionIdType FId)
{
    boolean FiM_PermissionStatus = FALSE;

#if(FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
    FIM_PRIV_ENTERLOCK_MONITOR();
    FiM_PermissionStatus = (((FiM_FIdStatusBitArray_au8[FiM_LastIdx][(FId / 8)]) & ((uint8) (1u << (uint8) (FId % 8))))
            == 0);
    FIM_PRIV_EXITLOCK_MONITOR();
#else
    FIM_PRIV_ENTERLOCK_STATUS();
    FiM_PermissionStatus = ((FiM_FIdStatusCounter_auo[FId])==0);
    FIM_PRIV_EXITLOCK_STATUS();
#endif
    return FiM_PermissionStatus;
}

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)

LOCAL_INLINE void FiM_Priv_FIdCountInc(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    if (FiM_FIdStatusCounter_auo[FId] < FIM_CFG_STATUSCOUNTERMAX )
    {
        FiM_FIdStatusCounter_auo[FId]++;
    }

    FIM_PRIV_EXITLOCK_STATUS();
}

LOCAL_INLINE void FiM_Priv_FIdCountDec(FiM_FunctionIdType FId)
{
#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON)
    boolean FiM_DetErrorFlag = FALSE;
#endif

    FIM_PRIV_ENTERLOCK_STATUS();

    if( FiM_FIdStatusCounter_auo[FId] > 0 )
    {
        FiM_FIdStatusCounter_auo[FId]--;
    }
#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON)
    else
    {

        FiM_DetErrorFlag = TRUE;
    }
#endif

    FIM_PRIV_EXITLOCK_STATUS();

#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON)

    if(FiM_DetErrorFlag == TRUE)
    {
        FIM_PRIV_DET_ERROR(FIM_PRIV_FIDCOUNTDEC_ID,FIM_E_FID_COUNTERNEGATIVE);
    }
#endif
}

LOCAL_INLINE void FiM_Priv_FIdCountReset(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    FiM_FIdStatusCounter_auo[FId] = 0;

    FIM_PRIV_EXITLOCK_STATUS();
}

LOCAL_INLINE void FiM_Priv_FIdCountSet(FiM_FunctionIdType FId, const FiM_FIdStatusCounterType value)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    FiM_FIdStatusCounter_auo[FId] = (FiM_FIdStatusCounterType)FIM_PRIV_MIN(value,FIM_CFG_STATUSCOUNTERMAX);

    FIM_PRIV_EXITLOCK_STATUS();
}

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)

LOCAL_INLINE void FiM_Priv_FIdServ07CountInc(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    if (FiM_FIdServ07StatusCounter_auo[FId] < FIM_CFG_STATUSCOUNTERMAX )
    {
        FiM_FIdServ07StatusCounter_auo[FId]++;
    }

    FIM_PRIV_EXITLOCK_STATUS();
}

LOCAL_INLINE void FiM_Priv_FIdServ07CountDec(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    if( FiM_FIdServ07StatusCounter_auo[FId] > 0 )
    {
        FiM_FIdServ07StatusCounter_auo[FId]--;
    }

    FIM_PRIV_EXITLOCK_STATUS();
}
#endif

#endif

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)

LOCAL_INLINE void FiM_Priv_SetInhStatus(FiM_FunctionIdType FId_uo)
{

    FiM_FIdStatusBitArray_au8[FiM_CurrentIdx][(FId_uo / 8)] |= ((uint8) (1u << (FId_uo % 8)));
}

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)

LOCAL_INLINE void FiM_Priv_SetServ07InhStatus(FiM_FunctionIdType FId_uo)
{

    FiM_FIdStatusServ07BitArray_au8[FiM_CurrentIdx][(FId_uo / 8)] |= ((uint8) (1u << (FId_uo % 8)));
}
#endif
#endif

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif

