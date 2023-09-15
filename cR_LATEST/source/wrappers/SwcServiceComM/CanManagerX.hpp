
#ifndef CAN_MANAGER_X_H
#define CAN_MANAGER_X_H

#include "Com_Cfg.hpp"

#define CANMGR__WSPEED_SPEED_INVALID                   ((uint16) 0xFFFFU)
#define ATMOSPHERIC_TEMPERATURE_SIGNAL_MISSING_VALUE   (uint8) 0xFFU

extern void CANMGR_ApplicationRequest_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_RdcDataTPM_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_ClockSynchronization_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_ESP_WSpeed_Front_BodyLCAN_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_ESP_WSpeed_Rear_BodyLCAN_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_ESP_Wheel_Pulse_Stamped_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_TMM_Status_BodyLCAN_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_VehSts_BodyLCAN_UpdateValues(uint8* PU8_DataPointer);
extern void CANMGR_VmsStsReq_BodyLCAN_UpdateValues(uint8* PU8_DataPointer);

extern void CANMGR_PduGroupStart(Com_IpduGroupIdType tGroupId);
extern void CANMGR_PduGroupStop(Com_IpduGroupIdType tGroupId);
extern void CANMGR_CommControlStatus(uint8 ucControlType);
extern void CANMGR_ControlCyclicApplicationPdu(void);
extern void CANMGR_SetNoCommunicationMode(void);
extern void CANMGR_SetFullCommunicationMode(void);
extern void CANMGR_Init(void);

extern void CANMGR_TickCommTimeout(void);
extern void CANMGR_StopCommTimeout(void);
extern void CANMGR_StartCommTimeout(void);
extern void CANMGR_ElongateCommTimeout(uint16 ushAddTime);

//extern void Com_IPdu_TrigTransm_Callout_ApplicationCyclic(void);
//extern void Com_IPdu_TrigTransm_Callout_HMIPressure_TPM(void);
//extern void Com_IPdu_TrigTransm_Callout_HMITempAndRefPress_TPM(void);
//extern void Com_IPdu_TrigTransm_Callout_ApplicationResponse(void);

extern void DIAG_CheckCANSignalMissingDTC(void);

#endif
