#ifndef DCM_H
#define DCM_H

#include "ComStack_Types.hpp"
#include "Dcm_Cfg_DslDsd.hpp"
#include "Dcm_Types.hpp"
#include "DcmCore_DslDsd_Pub.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Cfg_DspUds.hpp"
#include "Dcm_Lcfg_DspUds.hpp"
#include "DcmDspUds_Uds_Pub.hpp"
#endif

#include "Dcm_Lcfg_DslDsd.hpp"

#if(DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED==DCM_CFG_OFF)
#ifndef DCM_PRV_EXPORTAPI2LEGACY
#define DCM_PRV_EXPORTAPI2LEGACY
#endif
#endif

#ifndef DCM_PRV_EXPORTAPI2LEGACY
#include "Dcm_Export.hpp"
#endif

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetVin (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveDiagnostic(VAR(boolean, AUTOMATIC) active);
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_SrvOpStatusType Dcm_SrvOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#endif

