

#include "ComM_Priv.hpp"
#include "EcuM.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_BusSM_ModeIndication(NetworkHandleType Channel, ComM_ModeType * ComMode)
{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_BUSSM_MODEINDICATION,COMM_E_NOT_INITED);
        return;
   }

   if(ComMode == NULL_PTR)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_BUSSM_MODEINDICATION,COMM_E_WRONG_PARAMETERS);
        return;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_BUSSM_MODEINDICATION,COMM_E_WRONG_PARAMETERS);
        return;
   }
#endif

    (void) Channel;
    (void) ComMode;
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

