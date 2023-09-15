

#ifndef DCM_H
#define DCM_H

#include "ComStack_Types.hpp"

#include "Dcm_Cfg_Version.hpp"
#include "Dcm_Cfg_DslDsd.hpp"
#include "Dcm_Types.hpp"
#include "CfgSwcServiceDcm_DslDsd.hpp"
#include "Dcm_Cfg_DspUds.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspUds.hpp"
#include "DcmDspUds_Uds_Pub.hpp"
#endif

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspObd.hpp"
#include "DcmDspObd_Obd_Pub.hpp"
#endif

#include "Dcm_Lcfg_DslDsd.hpp"

#if(DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern Std_ReturnType Dcm_GetVin (uint8 * Data);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)

extern Std_ReturnType Dcm_SetActiveDiagnostic(boolean active);
#endif

#endif

