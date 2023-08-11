

#include "ComM_Priv.h"

#if (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

Std_ReturnType ComM_LimitChannelToNoComMode(NetworkHandleType Channel, boolean Status)
{

    ComM_GlobalVarType_tst *    globalRamPtr_pst;
    Std_ReturnType              retVal_u8;

    globalRamPtr_pst = &ComM_GlobalStruct;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {
       (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_LIMIT_CHNLTO_NOCOMMODE_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
    }

    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_LIMIT_CHNLTO_NOCOMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif

     ComM_Lok_ProcessLimitToNoCom(Channel,Status);

     if((Status == TRUE) && (COMM_GET_LIMIT_TO_NO_COM(globalRamPtr_pst->ComM_EcuGroupClassification_u8) == FALSE))
     {
         retVal_u8 = E_NOT_OK;
     }
     else
     {
         retVal_u8 = E_OK;
     }

     return retVal_u8;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

