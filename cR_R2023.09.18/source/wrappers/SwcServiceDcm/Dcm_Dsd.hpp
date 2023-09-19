#ifndef DCM_DSD_H
#define DCM_DSD_H

#include "ComStack_Types.hpp"
#include "Dcm_Types.hpp"
#include "Dcm_Cfg_DslDsd.hpp"

typedef enum{
    DSD_IDLE
   ,   DSD_VERIFY_DIAGNOSTIC_DATA
   ,   DSD_CALL_SERVICE
   ,   DSD_WAITFORTXCONF
   ,   DSD_SENDTXCONF_APPL
}Dcm_DsdStatesType_ten;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_DsdStatesType_ten stDsdState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern void Dcm_Lok_DsdStateMachine(void);
extern void Dcm_Dsd_ServiceIni(uint8 ServiceTableIndex_u8);
extern void Dcm_Lok_DsdSendTxConfirmation(void);
extern void Dcm_Lok_ResetDsdSubStateMachine(void);
extern boolean Dcm_Lok_IsVerifyDataProcessing(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE Dcm_DsdStatesType_ten Dcm_Lok_GetDsdState(void){
    return stDsdState_en;
}

LOCAL_INLINE void Dcm_Lok_SetDsdState(
   Dcm_DsdStatesType_ten State){
   stDsdState_en = State;
}

#endif
