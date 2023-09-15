

#ifndef DCMDSPUDS_ER_PROT_H
#define DCMDSPUDS_ER_PROT_H

#define DCM_NO_RESET                           0x00u
#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET  0x04u
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET 0x05u

#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)

typedef enum{
    DCM_ECURESET_IDLE=1
   ,   DCM_ECURESET_REQPERMISSION,
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
    DCM_ECURESET_WAIT,
#endif
    DCM_ECURESET_SENDRESPONSE
   ,   DCM_ECURESET_ERROR
}Dcm_EcuResetStateType_ten;

typedef enum{
    DCM_RESET_NO_BOOT = 0
   ,   DCM_RESET_OEM_BOOT
   ,   DCM_RESET_SYS_BOOT
   ,   DCM_RESET_DRIVE_TO_DRIVE
}Dcm_ResetForBootType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_EcuResetStateType_ten Dcm_stEcuResetState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern uint8 Dcm_dataEcuRType_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
typedef struct{
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   uint8 dataResetMode_u8;
#endif
   uint8 dataResetLevel_u8;
    Dcm_ResetForBootType  resetForBoot;
}
Dcm_DspEcuReset_tst;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern const Dcm_DspEcuReset_tst Dcm_DspEcuResetType_cast[DCM_CFG_DSP_NUMRESETTYPE];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern void Dcm_Lok_DspEcuResetConfirmation(
   Dcm_IdContextType dataIdContext_u8
   ,  Type_SwcServiceCom_tIdPdu dataRxPduId_u8
   ,  uint16 dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8
   													);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

