#include "PduR_Prv.hpp"
#include "PduR_Cfg.hpp"
#include "PduR_UpTp.hpp"
#include "PduR_Dcm.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
Std_ReturnType PduR_DcmTransmit(
   PduIdType id,
   const PduInfoType* ptr){
    return (PduR_rDcmTransmit( (id) , (ptr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

