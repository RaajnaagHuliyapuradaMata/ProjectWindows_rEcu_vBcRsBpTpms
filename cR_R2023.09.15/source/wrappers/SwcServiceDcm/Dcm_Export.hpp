

#ifndef DCM_EXPORT_H
#define DCM_EXPORT_H

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF))

extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocol);

extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);

extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);

extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void);

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

