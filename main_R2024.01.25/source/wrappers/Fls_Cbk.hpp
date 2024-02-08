

#ifndef FLS_CBK_H
#define FLS_CBK_H

#define FLS_CBK_AR_MAJOR_VERSION  2U
#define FLS_CBK_AR_MINOR_VERSION  4U
#define FLS_CBK_AR_PATCH_VERSION  0U

#define FLS_CBK_SW_MAJOR_VERSION  1U
#define FLS_CBK_SW_MINOR_VERSION  3U

#define FLS_START_SEC_APPL_CODE
#include "MemMap.hpp"

extern FUNC(void, FLS_APPL_CODE) EcuabFee_JobEndNotification(void);
extern FUNC(void, FLS_APPL_CODE) EcuabFee_JobErrorNotification(void);

#define FLS_STOP_SEC_APPL_CODE
#include "MemMap.hpp"

#endif

