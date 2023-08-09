

#ifndef COMM_DCM_H
#define COMM_DCM_H

#include "ComM_Cfg.h"
#include "ComStack_Types.h"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

extern FUNC(void,COMM_CODE) ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel);

extern FUNC(void,COMM_CODE) ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

