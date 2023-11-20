#ifndef COM_CBK_H
#define COM_CBK_H

#define COMCallback(CALLBACKROUTINENAME) FUNC(void,COM_CODE)(CALLBACKROUTINENAME)(void)

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationRequest        (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_BCM_peripheralMasterClock (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN  (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped   (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_RdcData_TPM               (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TMM_Status_BodyLCAN       (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_VehSts_BodyLCAN           (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_VmsStsReq_BodyLCAN        (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_CONST) ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationCyclic_TPM     (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,   P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_HMIPressure_TPM           (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,   P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_HMITempAndRefPress_TPM    (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,   P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_ApplicationResponse_TPM   (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,   P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  ptr);
FUNC(boolean,COM_CODE) Com_IPdu_Callout_TPMS_Software_ID_TPM      (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,   P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA)  ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

