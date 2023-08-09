

#ifndef COMM_ECUMBSWM_H
#define COMM_ECUMBSWM_H

#include "ComStack_Types.h"
#include "ComM_Cfg.h"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

extern FUNC (void,COMM_CODE) ComM_EcuM_WakeUpIndication
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC (void,COMM_CODE) ComM_EcuM_PNCWakeUpIndication
                                            (
                                            VAR(PNCHandleType,AUTOMATIC) PNCid
                                            );

extern FUNC(void,COMM_CODE) ComM_CommunicationAllowed
(
        VAR(NetworkHandleType,AUTOMATIC) Channel,
        VAR(boolean,AUTOMATIC) Allowed
);

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

