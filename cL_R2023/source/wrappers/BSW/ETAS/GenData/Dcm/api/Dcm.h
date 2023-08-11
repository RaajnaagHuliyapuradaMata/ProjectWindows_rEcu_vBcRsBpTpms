

#ifndef DCM_H
#define DCM_H

#include "ComStack_Types.h"

#include "Dcm_Cfg_Version.h"
#include "Dcm_Cfg_DslDsd.h"
#include "Dcm_Types.h"
#include "DcmCore_DslDsd_Pub.h"
#include "Dcm_Cfg_DspUds.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspUds.h"
#include "DcmDspUds_Uds_Pub.h"
#endif

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspObd.h"
#include "DcmDspObd_Obd_Pub.h"
#endif

#include "Dcm_Lcfg_DslDsd.h"

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"	
extern Std_ReturnType Dcm_GetVin (uint8 * Data);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)

extern Std_ReturnType Dcm_SetActiveDiagnostic(boolean active);
#endif

#endif

