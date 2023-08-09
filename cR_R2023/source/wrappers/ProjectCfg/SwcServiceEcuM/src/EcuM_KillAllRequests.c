

#include "EcuM.h"

#if (ECUM_CFG_MODE_HANDLING == STD_ON)

#include "EcuM_Prv.h"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

FUNC( void, ECUM_CODE ) EcuM_KillAllRUNRequests( void )
{
    VAR(EcuM_UserType, AUTOMATIC) cntrLoop_u16;

    EcuM_Lok_KillAllRUNRequests_b = TRUE;

    for(cntrLoop_u16 = 0;cntrLoop_u16 < ECUM_CFG_NUM_FLEX_USERS;cntrLoop_u16++)
    {
        EcuM_Lok_userRUNReqStatus_ab[cntrLoop_u16] = FALSE;
    }

}

FUNC( void, ECUM_CODE ) EcuM_KillAllPostRUNRequests( void )
{
    VAR(EcuM_UserType, AUTOMATIC) cntrLoop_u16;

    EcuM_Lok_KillAllPostRUNRequests_b = TRUE;

    for(cntrLoop_u16 = 0;cntrLoop_u16 < ECUM_CFG_NUM_FLEX_USERS;cntrLoop_u16++)
    {
       EcuM_Lok_userPostRUNReqStatus_ab[cntrLoop_u16] = FALSE;
    }

}

FUNC( void, ECUM_CODE ) EcuM_Rn_KillAllRequests( void )
{

    EcuM_KillAllRUNRequests();

    EcuM_KillAllPostRUNRequests();
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#else

#endif

