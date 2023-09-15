#ifndef ENV_MANAGER_X_H
#define ENV_MANAGER_X_H

#include "types.hpp"
#include "iTpms_Interface.hpp"
#include "Dem.hpp"
#include "SysManagerX.hpp"

typedef enum{
  ENV_E_IGNITION_OFF = 0x00U
   ,  ENV_E_IGNITION_ON = 0x01U
   ,  ENV_E_IGNITION_UNKNOWN = 0x02U
}Env_Enum_IgnitionState;

typedef enum{
  ENV_E_VEHCILE_DIRECTION_FORWARD = 0x00U
   ,  ENV_E_VEHICLE_DIRECTION_BACKWARD = 0x01U
   ,  ENV_E_VEHICLE_DIRECTION_UNKNOWN = 0x02U
}Env_Enum_VehicleDirection;

typedef enum{
  ENV_E_FRONT_LEFT_WHEEL_INDEX = 0U
   ,  ENV_E_FRONT_RIGHT_WHEEL_INDEX
   ,  ENV_E_REAR_LEFT_WHEEL_INDEX
   ,  ENV_E_REAR_RIGHT_WHEEL_INDEX
   ,  ENV_E_MAX_WHEEL_INDEX
}Env_Enum_WheelIndex;

extern void Env_Init(void);

extern tsEnv_Data *Env_GetEnvironmentData(void);

extern void Env_SetIgnitionStateFromBus(Env_Enum_IgnitionState EN_IgnitionState);

extern void Env_ControlIgnitionByCoastmode(eCoastModeType enCMState);

extern void Env_SetAmbientTemperature(uint8 U8_AmbientTemperature);

extern void Env_SetAtmosphericPressure(uint8 U8_AtmosphericPressure);

extern void Env_SetVehicleDirection(Env_Enum_VehicleDirection EN_VehicleDirection);

extern void Env_SetEcuFault(boolean BO_IsEcuDefect);

//extern void Env_SetNvmBlockConsistency(uint8 U8_NvmCategory, boolean BO_IsNvmBlockConsistent);
extern void Env_SetNvmBlockConsistency(uint16 ushConsistencyFlags);

extern void Env_SetNoiseLevel(uint16 U16_NoiseLevel);

extern uint16 Env_GetNoiseLevel(void);

extern void Env_SetRoadMode(boolean BO_RoadMode);

extern void Env_SetWheelInfo(Env_Enum_WheelIndex EN_WheelIndex, uint16 U16_WheelSpeed, Env_Enum_VehicleDirection EN_WheelDirection);

extern void Env_SetVehicleMode(uint8 ucVM);
extern uint8 Env_GetVehicleMode(void);

extern boolean bGetCoastModeActive(void);
extern Env_Enum_IgnitionState enGetIgnitionStateFromBus(void);
#endif
