#ifndef DCM_MANAGER_X_H
#define DCM_MANAGER_X_H

typedef struct{
   uint8 FrontLeftReceived:1;
   uint8 FrontRightReceived:1;
   uint8 RearLeftReceived:1;
   uint8 RearRightReceived:1;
   uint8 dummy:4;
   uint8 ucPressureFL;
   uint8 ucPressureFR;
   uint8 ucPressureRL;
   uint8 ucPressureRR;
}tVehicleEndOfLineData;

extern void DCMMGR_MainFunction(void);
extern void DCMMGR_TriggerDiagRoutineSelfCheck(void);
extern boolean DCMMGR_GetDiagRoutineSelfCheckResult(void);
extern void DCMMGR_TriggerPositiveResponse(void);
extern boolean DCMMGR_GetPositiveResponseTrigger(void);
extern void DCMMGR_IncNonceCounter(void);
extern uint64 DCMMGR_GetNonceCounter(void);

#endif