#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,COMM_CODE) ComM_GetStatus
                                        (
                                        P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_VAR) Status
                                        )
{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(Status == NULL_PTR)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATUS_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }

   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATUS_APIID,COMM_E_NOT_INITED);

        *Status = COMM_UNINIT;
        return E_NOT_INITIALIZED;
   }
#endif

    *Status = ComM_GlobalStruct.ComM_InitStatus;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

