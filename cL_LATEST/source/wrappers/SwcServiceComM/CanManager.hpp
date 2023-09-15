#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

#include "Std_Types.hpp"
#include "CanManagerX.hpp"
#include "iTpms_Interface.hpp"

#define cCAN_COMM_TIMEOUT 300
#define cCAN_EXTENDED_COMM_TIMOUT 2000

#define CANMGR__IGNITION_ON_TRESHOLD ((uint8) 1U)

#define ABS_PULSE_SIGNAL_MISSING_VALUE    0xFF
#define ATMOSPHERIC_PRESSURE_SIGNAL_MISSING_VALUE   0xFF
//#define ATMOSPHERIC_TEMPERATURE_SIGNAL_MISSING_VALUE   0xFF -> moved to CanManagerX.h
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

#define CANMGR__WSPEED_QUALIFIER_BIT_NOT_INITIALIZED					((uint8)0x02)
#define CANMGR__WSPEED_QUALIFIER_BIT_NORMAL										((uint8)0x00)
#define CANMGR__WSPEED_QUALIFIER_BIT_FAULT										((uint8)0x01)
#define CANMGR__WPULSE_QUALIFIER_NOT_INITIALIZED              ((uint8) 0x00U)
#define CANMGR__WPULSE_QUALIFIER_OK                           ((uint8) 0x01U)
#define CANMGR__WPULSE_QUALIFIER_RESERVED                     ((uint8) 0x02U)
#define CANMGR__WPULSE_QUALIFIER_INVALID                      ((uint8) 0x03U)

#define CANMGR__WHEEL_PULSE_INVALID_SUBST_VALUE								((uint8) 0xFFFFU)

#define CANMGR__TMM_STATUS_INVALID_SIGNAL_THRESHOLD						((uint8) 255U)
#define CANMGR__TMM_STATUS_VALID                              ((uint8) 1U)

#define CANMGR__VEH_STS_INVALID_SIGNAL												((uint8) 0U)

typedef struct{
  uint8 ui8CANGearPositionSignalMissingCnt;
  uint8 ui8CANAtmosphericPressSignalMissingCnt;
  uint8 ui8CANAtmosphericTempSignalMissingCnt;
  uint8 ui8CANMileageSignalMissingCnt;
  uint8 ui8CANABSWheelPulseSignalMissingCnt;
}S_SignalMissingDTCCnt;

typedef struct{
  uint8 TPMS_TireT_FL;
  uint8 TPMS_TireT_FR;
  uint8 TPMS_TireT_RL;
  uint8 TPMS_TireT_RR;
  uint8 TPMS_TireP_FL;
  uint8 TPMS_TireP_FR;
  uint8 TPMS_TireP_RL;
  uint8 TPMS_TireP_RR;
}sHMI_LMC;

typedef struct{

  bitfield bTPMS_Status_FR : 3;
  bitfield bTPMS_Val_FR : 1;
  bitfield bTPMS_Status_FL : 3;
  bitfield bTPMS_Val_FL : 1;
  bitfield bTPMS_Status_RL : 3;
  bitfield bTPMS_Val_RL : 1;
  bitfield bTPMS_Status_RR : 3;
  bitfield bTPMS_Val_RR : 1;

  bitfield bTMPS_InflationMonitoring_Status : 4;

  bitfield b2Gap1 : 2;

  bitfield bTPMS_TempWarning_FR : 1;
  bitfield bTPMS_TempWarning_RL : 1;
  bitfield bTPMS_TempWarning_FL : 1;
  bitfield bTPMS_TempWarning_RR : 1;

  bitfield bTPMS_Learn_Status : 1;

  bitfield bTPMS_Locate_Status : 1;

  bitfield b4Gap2 : 4;

  uint8 ucTPMS_Tire_Ref_Press_FL;
  uint8 ucTPMS_Tire_Ref_Press_FR;
  uint8 ucTPMS_Tire_Ref_Press_RL;
  uint8 ucTPMS_Tire_Ref_Press_RR;
}sSTATUS_LMC;

typedef struct{
  bitfield bChecksum : 8;
  bitfield bMessageCounter : 4;
  bitfield bWheelSpeedLValid : 2;
  bitfield bWheelSpeedRValid : 2;
  bitfield bWheelSpeedL : 16;
  bitfield bWheelSpeedR : 16;
  bitfield b4Gap1 : 4;
  bitfield bWheelDirR : 2;
  bitfield bWheelDirL : 2;
  bitfield b8Gap2 : 8;
}sWheelSpeed_RIVIAN;

typedef struct{
  bitfield bWheelSpeedL      : 14;
  bitfield bWheelSpeedLValid : 2;
  bitfield bWheelSpeedR      : 14;
  bitfield bWheelSpeedRValid : 2;

  bitfield bWheelDirL        : 3;
  bitfield b1Gap1             : 1;
  bitfield bWheelDirR        : 3;
  bitfield b1Gap2             : 1;

  bitfield bMessageCounter    : 4;
  bitfield b4Gap3             : 4;
  bitfield bChecksum          : 8;
}sWheelSpeed_LMC;

typedef struct{
  bitfield bChecksum : 8;
  bitfield bMessageCounter : 4;
  bitfield bQualifierRR : 1;
  bitfield bQualifierFR : 1;
  bitfield bQualifierRL : 1;
  bitfield bQualifierFL : 1;
  bitfield bWheelPulseFL : 16;
  bitfield bWheelPulseRL : 16;
  bitfield bWheelPulseFR : 16;
  bitfield bWheelPulseRR : 16;
  bitfield bTimestamp : 16;
}sWheelPulses_RIVIAN;

typedef struct{
  bitfield bMillisec : 10;
  bitfield bValid : 1;
  bitfield b5Gap1 : 5;
  uint8 ucSeconds[6];
}sEpochTime_LMC;

static void CANMGR_PduGroupInit(void);
static void CANMGR_ResetCommTimeout(void);

#endif
