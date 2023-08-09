

#ifndef DCM_H
#define DCM_H

#include "ComStack_Types.h"

#include "Dcm_Cfg_DslDsd.h"
#include "Dcm_Types.h"
#include "DcmCore_DslDsd_Pub.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Cfg_DspUds.h"
#include "Dcm_Lcfg_DspUds.h"
#include "DcmDspUds_Uds_Pub.h"
#endif

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspObd.h"
#include "DcmDspObd_Obd_Pub.h"
#endif

#include "Dcm_Lcfg_DslDsd.h"

#if(DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED==DCM_CFG_OFF)
#ifndef DCM_PRV_EXPORTAPI2LEGACY
#define DCM_PRV_EXPORTAPI2LEGACY
#endif
#endif
#ifndef DCM_PRV_EXPORTAPI2LEGACY
#include "Dcm_Export.h"
#endif

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetVin (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveDiagnostic(VAR(boolean, AUTOMATIC) active);
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
extern Dcm_SrvOpStatusType Dcm_SrvOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"

#endif

