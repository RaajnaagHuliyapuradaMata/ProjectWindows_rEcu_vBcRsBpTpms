#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,COMM_CODE) ComM_GetMaxComMode
                                            (
                                            VAR(ComM_UserHandleType, COMM_VAR) User
   ,     P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                            )
{

#if(COMM_INHIBITION_ENABLED)
   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
#endif

#if(COMM_INHIBITION_ENABLED)
   userRamPtr_ps = &ComM_UserStruct[User];
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_MAX_COMMODE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
   }

   if(ComMode == NULL_PTR)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_MAX_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }

   if(User >= COMM_NO_OF_USERS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_MAX_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }
#endif

#if(COMM_INHIBITION_ENABLED)
   if(((userRamPtr_ps->WakeUpInhibitionCtr_u16) != C_ZERO) || ((userRamPtr_ps->LimitToNoComCtr_u16) != C_ZERO))
   {
        *ComMode = COMM_NO_COMMUNICATION;
   }
   else
#endif
   {
    *ComMode = COMM_FULL_COMMUNICATION;
   }
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

