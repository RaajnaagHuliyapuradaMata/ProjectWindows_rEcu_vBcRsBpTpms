#include "Std_Types.hpp"

#include "ComStack_Types.hpp"
#include "CanTp.hpp"

#define CANTP_START_SEC_FDCALLOUT_CODE
#include "CanTp_MemMap.hpp"
Std_ReturnType CanTp_XX_YY_ExternalFdSupportCallback(Type_SwcServiceCom_tIdPdu RxPduId, const Type_SwcServiceCom_stInfoPdu *PduInfoPtr
   ,     const boolean FdEnabled)
{
    (void)RxPduId;
    (void)PduInfoPtr;
    (void)FdEnabled;

    return E_OK;
}

#define CANTP_STOP_SEC_FDCALLOUT_CODE
#include "CanTp_MemMap.hpp"
