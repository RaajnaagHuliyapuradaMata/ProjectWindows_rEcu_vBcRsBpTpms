#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

#include "CanManagerX.hpp"

#define cCAN_COMM_TIMEOUT 300
#define CANMGR__IGNITION_ON_TRESHOLD ((uint8) 2U)
#define ABS_PULSE_SIGNAL_MISSING_VALUE    0xFF
#define ATMOSPHERIC_PRESSURE_SIGNAL_MISSING_VALUE   0xFF
#define MILEAGE_SIGNAL_MISSING_VALUE    0xFF
#define MANUAL_GEAR_POSITION_SIGNAL_MISSING_VALUE    0x00
#define AUTOMATIC_GEAR_POSITION_SIGNAL_MISSING_VALUE    0x0F
#define AUTOMATIC_TRANSMISSION    2
#define MANUAL_TRANSMISSION   0
#define VC_AT   2
#define SECONDS_10_IN_MSEC  10000
#define MILISECONDS_400_VALUE 400
#define CYCLIC_200MS_TASK   200
#define NUMBER_OF_WUPS_FOR_10SEC_IN_200MS_CYCLES    (SECONDS_10_IN_MSEC / CYCLIC_200MS_TASK)
#define NUMBER_OF_WUPS_FOR_400MSEC_IN_200MS_CYCLES  (MILISECONDS_400_VALUE / CYCLIC_200MS_TASK)
#define CANMGR__ESP_WSPEED_FRONT_MESSAGE_COUNTER_INVALID			((uint8) 0x0FU)
#define CANMGR__ESP_WSPEED_REAR_MESSAGE_COUNTER_INVALID				((uint8) 0x0FU)
#define CANMGR__ESP_WHEEL_PULSE_MESSAGE_COUNTER_INVALID				((uint8) 0x0FU)
#define CANMGR__VMS_STS_REQ_MESSAGE_COUNTER_INVALID						((uint8) 0x0FU)
#define CANMGR__WSPEED_QUALIFIER_BIT_NOT_INITIALIZED					((uint8) 0x00U)
#define CANMGR__WSPEED_QUALIFIER_BIT_NORMAL										((uint8) 0x01U)
#define CANMGR__WSPEED_QUALIFIER_BIT_FAULT										((uint8) 0x02U)
#define CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE								((uint8) 0xFFU)
#define CANMGR__TMM_STATUS_INVALID_SIGNAL_THRESHOLD						((uint8) 253U)
#define CANMGR__VEH_STS_INVALID_SIGNAL												((uint8) 0U)

typedef struct{
  uint8 ui8CANGearPositionSignalMissingCnt;
  uint8 ui8CANAtmosphericPressSignalMissingCnt;
  uint8 ui8CANAtmosphericTempSignalMissingCnt;
  uint8 ui8CANMileageSignalMissingCnt;
  uint8 ui8CANABSWheelPulseSignalMissingCnt;
}S_SignalMissingDTCCnt;

static void CANMGR_PduGroupInit(void);
static boolean CANMGR__IsCanControllerActive(void);
static void CANMGR_ResetCommTimeout(void);

#endif
