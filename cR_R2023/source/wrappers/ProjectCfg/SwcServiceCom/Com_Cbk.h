

#ifndef COM_CBK_H
#define COM_CBK_H

#define COMCallback(CALLBACKROUTINENAME) FUNC(void,COM_CODE)(CALLBACKROUTINENAME)(void)

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_IPdu_NotificationCallback_ApplicationResponse(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationRequest(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_BCM_peripheralMasterClock(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_RdcData_TPM(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TMM_Status_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_VehSts_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_VmsStsReq_BodyLCAN(VAR(PduIdType, AUTOMATIC) id, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationCyclic_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_HMIPressure_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_HMITempAndRefPress_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationResponse_TPM(VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

