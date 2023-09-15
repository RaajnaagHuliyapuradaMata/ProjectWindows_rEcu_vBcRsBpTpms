

#ifndef DCM_EXPORT_H
#define DCM_EXPORT_H

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF))

extern Std_ReturnType Dcm_GetActiveProtocol(Dcm_ProtocolType * ActiveProtocol);

extern Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType * SesCtrlType);

extern Std_ReturnType Dcm_GetSecurityLevel(Dcm_SecLevelType * SecLevel);

extern Std_ReturnType Dcm_ResetToDefaultSession(void);

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

