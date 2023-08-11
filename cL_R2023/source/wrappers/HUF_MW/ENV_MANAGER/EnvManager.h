

#ifndef ENV_MANAGER_H
#define ENV_MANAGER_H

#include "EnvManagerX.h"

#define ENV__VEHICLE_SPEED_DEFAULT              ((uint16) 0U)           //!< Startup default value for vehicle speed.
#define ENV__VEHICLE_SPEED_INVALID              ((uint16) 1023U)        //!< Threshold after which vehicle speed is considered invalid.

#define ENV__IGNITION_STATE_INVALID             ((uint8) 0xFFU)         //!< Value used for an invalid ignition state.

#define ENV__AMBIENT_TEMPERATURE_DEFAULT        ((uint8) 80U)           //!< Startup default value for ambient temperature. Corresponds to 0°C.
#define ENV__AMBIENT_TEMPERATURE_MAX_VALID		  ((uint8) 254U)			    //!< Maximum allowed temperature value to be received on CAN. Corresponds to 87°C.
#define ENV__AMBIENT_TEMPERATURE_INVALID        ((uint8) 0xFFU)         //!< Value used for an invalid ambient temperature.

#define ENV__ATMOSPHERIC_PRESSURE_DEFAULT       ((uint8) 0U)            //!< Startup default value for atmospheric pressure.
#define ENV__ATMOSPHERIC_PRESSURE_INVALID       ((uint8) 0xFFU)         //!< Value used for an invalid atmospheric pressure.

#define ENV__NOISE_LEVEL_DEFAULT                ((uint16) 0xFFFFU)      //!< Value used as a default value for the noise level.

typedef struct{
  uint16 U16_WheelSpeed;
  Env_Enum_VehicleDirection EN_WheelDirection;
} Env__Struct_WheelInfo;

static void Env__DetermineVehicleSpeedAndDirection(void);
static void Env_SetIgnitionState(Env_Enum_IgnitionState EN_IgnitionState);

static void Env_SetVehicleSpeed(uint16 U16_VehicleSpeed);

#endif
