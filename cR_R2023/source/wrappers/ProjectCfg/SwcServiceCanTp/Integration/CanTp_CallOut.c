#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "CanTp.h"

#define CANTP_START_SEC_FDCALLOUT_CODE
#include "CanTp_MemMap.h"

Std_ReturnType CanTp_XX_YY_ExternalFdSupportCallback(PduIdType RxPduId, const PduInfoType *PduInfoPtr,
                                                     const boolean FdEnabled)
{
    (void)RxPduId;
    (void)PduInfoPtr;
    (void)FdEnabled;

    return E_OK;
}

#define CANTP_STOP_SEC_FDCALLOUT_CODE
#include "CanTp_MemMap.h"
