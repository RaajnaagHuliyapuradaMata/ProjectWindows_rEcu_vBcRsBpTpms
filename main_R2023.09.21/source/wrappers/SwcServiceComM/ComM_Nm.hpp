

#ifndef COMM_NM_H
#define COMM_NM_H

#include "ComM_Cfg.hpp"
#include "ComStack_Types.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

extern FUNC(void,COMM_CODE) ComM_Nm_NetworkStartIndication
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_BusSleepMode
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_NetworkMode
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_RestartIndication
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_PrepareBusSleepMode
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_TransmissionFailure
(
         VAR (NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_NetworkTimeoutException
(
         VAR(NetworkHandleType,AUTOMATIC) Channel
);

extern FUNC(void,COMM_CODE) ComM_Nm_RxIndication
(
       VAR(NetworkHandleType,AUTOMATIC) Channel
);

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

