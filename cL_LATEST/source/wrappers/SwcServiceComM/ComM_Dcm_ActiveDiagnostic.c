

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel)

{

   ComM_ChannelVarType_tst *  channelRamPtr_pst;

   channelRamPtr_pst = &ComM_ChannelStruct[Channel];

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {

       (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_DCM_ACTIVEDIAG,COMM_E_NOT_INITED);
        return;
   }
#endif

   channelRamPtr_pst->DiagnosticRequestState_b = COMM_ACTIVE_DIAGNOSTICS;
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

