#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.hpp"
Type_EcuabCanIf_eStatusNotification CanIf_Lok_RxNotification_taen[CANIF_CFG_NUM_CANRXPDUIDS];
#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.hpp"

#if(CANIF_CFG_TRCV_DRV_SUPPORT != STD_OFF)
#define CANIF_START_SEC_CONST_8
#include "CanIf_MemMap.hpp"
const uint8 CanIf_Trcv_LUT[CANIF_NUM_TRANSCEIVERS] = {0};
#define CANIF_STOP_SEC_CONST_8
#include "CanIf_MemMap.hpp"
#endif

#if(CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)
uint32 CanIf_DynTxPduCanId_au32[CANIF_TOTAL_DYNAMIC_PDUS];
#endif

Type_EcuabCanIf_eStatusNotification CanIf_Lok_TxNotification_aen[CANIF_TOTAL_TXPDUS];
