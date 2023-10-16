#ifndef ENV_MANAGER_X_H
#define ENV_MANAGER_X_H

#include "iTpms_Interface.hpp"
#include "Dem.hpp"

#define ENV__AMBIENT_TEMPERATURE_INVALID                         ((uint8) 0xFFU)

typedef enum{
      ENV_E_IGNITION_OFF
   ,  ENV_E_IGNITION_ON
   ,  ENV_E_IGNITION_UNKNOWN
}Env_Enum_IgnitionState;

typedef enum{
      ENV_E_VEHCILE_DIRECTION_FORWARD
   ,  ENV_E_VEHICLE_DIRECTION_BACKWARD
   ,  ENV_E_VEHICLE_DIRECTION_UNKNOWN
}Env_Enum_VehicleDirection;

typedef enum{
      ENV_E_FRONT_LEFT_WHEEL_INDEX
   ,  ENV_E_FRONT_RIGHT_WHEEL_INDEX
   ,  ENV_E_REAR_LEFT_WHEEL_INDEX
   ,  ENV_E_REAR_RIGHT_WHEEL_INDEX
   ,  ENV_E_MAX_WHEEL_INDEX
}Env_Enum_WheelIndex;

extern void                   Env_Init                             (void);
extern Type_SwcApplTpms_stStatusBody*            Env_GetEnvironmentData               (void);
extern void                   Env_SetIgnitionStateFromBus          (Env_Enum_IgnitionState      EN_IgnitionState);
extern void                   Env_SetAmbientTemperature            (uint8                       U8_AmbientTemperature);
extern void                   Env_SetAtmosphericPressure           (uint8                       U8_AtmosphericPressure);
extern void                   Env_SetVehicleDirection              (Env_Enum_VehicleDirection   EN_VehicleDirection);
extern void                   Env_SetEcuFault                      (boolean                     BO_IsEcuDefect);
extern void                   Env_SetNvmBlockConsistency           (uint16                      ushConsistencyFlags);
extern void                   Env_SetNoiseLevel                    (uint16                      U16_NoiseLevel);
extern uint16                 Env_GetNoiseLevel                    (void);
extern void                   Env_SetRoadMode                      (boolean                     BO_RoadMode);
extern void                   Env_SetVehicleMode                   (uint8                       ucVM);
extern uint8                  Env_GetVehicleMode                   (void);
extern boolean                bGetCoastModeActive                  (void);
extern Env_Enum_IgnitionState enGetIgnitionStateFromBus            (void);
extern void                   Env_SetIgnitionOffForMobileTireAlert (void);
extern void                   Env_SetIgnitionOnForMobileTireAlert  (void);

extern void Env_SetWheelInfo(
      Env_Enum_WheelIndex       EN_WheelIndex
   ,  uint16                    U16_WheelSpeed
   ,  Env_Enum_VehicleDirection EN_WheelDirection
);

#endif
