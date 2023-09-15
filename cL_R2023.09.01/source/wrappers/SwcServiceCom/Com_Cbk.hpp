

#ifndef COM_CBK_H
#define COM_CBK_H

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_BCM_PowerMode(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_EPOCHTime(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_ESP_WheelPulses(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_ODO(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_TPMS_ApplicationRequest(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_VCU_Ambient_Info(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_VCU_Powertrain_Info(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_VCU_WheelSpeed_Front(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_VCU_WheelSpeed_Rear(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_CGW_VehicleSpeed(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_TPMS_RdcData(PduIdType id, const PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_TPMS_ApplicationCyclic(PduIdType id, PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_TPMS_Status(PduIdType id, PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_TPMS_TirePT(PduIdType id, PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
boolean Com_IPdu_Callout_TPMS_ApplicationResponse(PduIdType id, PduInfoType * ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

