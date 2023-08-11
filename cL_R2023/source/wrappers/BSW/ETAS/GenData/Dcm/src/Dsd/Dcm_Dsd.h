

#ifndef DCM_DSD_H

#define DCM_DSD_H

#include "ComStack_Types.h"
#include "Dcm_Types.h"
#include "Dcm_Cfg_DslDsd.h"

typedef enum
{
    DSD_IDLE,
    DSD_VERIFY_DIAGNOSTIC_DATA,
    DSD_CALL_SERVICE,
    DSD_WAITFORTXCONF,
    DSD_SENDTXCONF_APPL
}Dcm_DsdStatesType_ten;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DsdStatesType_ten stDsdState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern void Dcm_Lok_DsdStateMachine(void);
extern void Dcm_Dsd_ServiceIni(uint8 ServiceTableIndex_u8);
extern void Dcm_Lok_DsdSendTxConfirmation(void);
#if ((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0u) || (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0u))
extern void Dcm_Dsd_CallRTEConfirmation(Dcm_ConfirmationStatusType ConfirmationStatus_u8,boolean context);
#endif
extern void Dcm_Lok_ResetDsdSubStateMachine(void);
extern boolean Dcm_Lok_IsVerifyDataProcessing(void);

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

LOCAL_INLINE Dcm_DsdStatesType_ten Dcm_Lok_GetDsdState(void)
{
    return stDsdState_en;
}

LOCAL_INLINE void Dcm_Lok_SetDsdState(Dcm_DsdStatesType_ten State)
{
    stDsdState_en = State;
}

#endif
