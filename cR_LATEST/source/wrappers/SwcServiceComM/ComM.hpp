#ifndef COMM_H
#define COMM_H

#include "ComM_Cfg.hpp"
#include "ComM_Dcm.hpp"
#include "ComM_BusSM.hpp"
#include "ComM_EcuMBswM.hpp"
#include "ComM_Nm.hpp"
#include "ComM_Main.hpp"
#include "CfgSwcServiceComM.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

extern FUNC(void,COMM_CODE) ComM_Init(
                                    P2CONST(Type_CfgSwcServiceComM_st,AUTOMATIC,COMM_APPL_CONST) config
                                    );

extern FUNC(void,COMM_CODE) ComM_DeInit(void);

extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetState(
                                                        VAR(NetworkHandleType, COMM_VAR) Channel
   ,     P2VAR(ComM_StateType, AUTOMATIC, COMM_VAR) State
                                                    );

extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetStatus
                                                (
                                                 P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_VAR) Status
                                                );

extern FUNC(void,COMM_CODE) ComM_GetVersionInfo
                                        (
                                          P2VAR(Std_VersionInfoType, AUTOMATIC, COMM_VAR) versioninfo
                                        );

extern FUNC(Std_ReturnType,COMM_CODE) ComM_RequestComMode
                                             (
                                              VAR(ComM_UserHandleType, COMM_VAR) User
   ,     VAR(ComM_ModeType, COMM_VAR) ComMode
                                             );

extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetMaxComMode
                                            (
                                               VAR(ComM_UserHandleType, COMM_VAR) User
   ,     P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                            );

extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetRequestedComMode
                                                (
                                                   VAR(ComM_UserHandleType, COMM_VAR) User
   ,     P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                                );

extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetCurrentComMode
                                                (
                                                   VAR(ComM_UserHandleType, COMM_VAR) User
   ,     P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                                );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel
   ,     VAR(boolean, COMM_VAR) Status
                                        );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode
                                        (
                                        VAR(boolean, COMM_VAR) Status
                                        );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_PreventWakeUp
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel
   ,     VAR(boolean, COMM_VAR) Status
                                        );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_SetECUGroupClassification
                                        (
                                        VAR(ComM_InhibitionStatusType,COMM_VAR) Status
                                        );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter
                                        (
                                          P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
                                        );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter
                                        (
                                        void
                                        );

extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetInhibitionStatus
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel
   ,     P2VAR(ComM_InhibitionStatusType, AUTOMATIC, COMM_VAR) Status
                                        );

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"

extern CONST(Type_CfgSwcServiceComM_st,COMM_CONST) ComM_Config;

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"

#endif

