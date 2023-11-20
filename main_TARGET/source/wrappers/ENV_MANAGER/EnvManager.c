#include "Std_Types.hpp"

#include "Types_SwcServiceEcuM.hpp"

#include "EnvManager.hpp"
#include "CanManagerX.hpp"
#include "Rte_NvM_Type.hpp"

static Env__Struct_WheelInfo  Env__S_WheelInfo[ENV_E_MAX_WHEEL_INDEX];
static Env_Enum_IgnitionState EN_IgnitionStateFromBus;
static Type_SwcApplTpms_stStatusBody             Env__EnvironmentData;
static uint8                  ucVehicleMode;
static boolean                bCoastModeActive = FALSE;

void Env_Init(void){
   uint8 U8_Counter;
   Env__EnvironmentData.uiVehSpeed            = ENV__VEHICLE_SPEED_DEFAULT;
   Env__EnvironmentData.ucIgnition            = ((uint8_t) ENV_E_IGNITION_OFF);
   Env__EnvironmentData.ucAmbTemperature      = ENV__AMBIENT_TEMPERATURE_DEFAULT;
   Env__EnvironmentData.ucAthmosPressure      = ENV__ATMOSPHERIC_PRESSURE_DEFAULT;
   Env__EnvironmentData.ucVehDirection        = ((uint8) ENV_E_VEHCILE_DIRECTION_FORWARD);
   Env__EnvironmentData.bECU_Fault            = FALSE;
   Env__EnvironmentData.uiNvmBlockConsistence = 0x0000U;
   Env__EnvironmentData.uiNoiseRSSI           = ENV__NOISE_LEVEL_DEFAULT;
   bCoastModeActive                           = FALSE;
   for(
      U8_Counter = 0U;
      U8_Counter < NVM_MAX_CATEGORYS;
      U8_Counter ++
   ){
      Env__EnvironmentData.uiNvmBlockConsistence |= (((uint16) 1U)<<U8_Counter);
   }
   for(
      U8_Counter = 0U;
      U8_Counter < ENV_E_MAX_WHEEL_INDEX;
      U8_Counter ++
   ){
      Env__S_WheelInfo[U8_Counter].U16_WheelSpeed    = ENV__VEHICLE_SPEED_DEFAULT;
      Env__S_WheelInfo[U8_Counter].EN_WheelDirection = ENV_E_VEHCILE_DIRECTION_FORWARD;
   }
}

Type_SwcApplTpms_stStatusBody* Env_GetEnvironmentData(void){
   Env__DetermineVehicleSpeedAndDirection();
   return &Env__EnvironmentData;
}

boolean bGetCoastModeActive(void){
   return bCoastModeActive;
}

Env_Enum_IgnitionState enGetIgnitionStateFromBus(void){
   return EN_IgnitionStateFromBus;
}

void Env_SetIgnitionStateFromBus(
   Env_Enum_IgnitionState EN_IgnitionState
){
   if(EN_IgnitionStateFromBus != EN_IgnitionState){
      EN_IgnitionStateFromBus = EN_IgnitionState;
      if(
            (ENV_E_IGNITION_OFF     == EN_IgnitionStateFromBus)
         || (ENV_E_IGNITION_UNKNOWN == EN_IgnitionStateFromBus)
      )    {infSwcServiceEcuM_vSetEventEcu(SwcServiceEcuM_eEventEcu_IgnitionOff);}
      else {infSwcServiceEcuM_vSetEventEcu(SwcServiceEcuM_eEventEcu_IgnitionOn);}
   }
   if(FALSE == bCoastModeActive){
      Env_SetIgnitionState(EN_IgnitionStateFromBus);
   }
}

void Env_SetIgnitionOnForMobileTireAlert(void){
   Env_SetIgnitionState(ENV_E_IGNITION_ON);
}

void Env_SetIgnitionOffForMobileTireAlert(void){
   Env_SetIgnitionState(ENV_E_IGNITION_OFF);
}

void Env_ControlIgnitionByCoastmode(
   Type_SwcApplEcuM_eModeCoast leModeCoast
){
        if(leModeCoast == SwcApplEcuM_eModeCoast_Start){bCoastModeActive = TRUE;  Env_SetIgnitionState(ENV_E_IGNITION_ON);}
   else if(leModeCoast == SwcApplEcuM_eModeCoast_Stop ){bCoastModeActive = FALSE; Env_SetIgnitionState(EN_IgnitionStateFromBus);}
   else if(leModeCoast == SwcApplEcuM_eModeCoast_Over ){bCoastModeActive = FALSE; Env_SetIgnitionState(ENV_E_IGNITION_OFF);}
   else{}
}

void Env_SetVehicleMode(
   uint8 ucVM
){
  ucVehicleMode = ucVM;
}

extern uint8 Env_GetVehicleMode(void){
   return ucVehicleMode;
}

void Env_SetAmbientTemperature(
   uint8 U8_AmbientTemperature
){
   if(
         (ENV__AMBIENT_TEMPERATURE_INVALID != U8_AmbientTemperature)
      && (U8_AmbientTemperature < ENV__AMBIENT_TEMPERATURE_MAX_VALID)
   ){
      Env__EnvironmentData.ucAmbTemperature = U8_AmbientTemperature << 1;
   }
  else{
      Env__EnvironmentData.ucAmbTemperature = ENV__AMBIENT_TEMPERATURE_INVALID;
   }
}

void Env_SetAtmosphericPressure(
   uint8 U8_AtmosphericPressure
){
   Env__EnvironmentData.ucAthmosPressure = U8_AtmosphericPressure;
}

void Env_SetVehicleDirection(
   Env_Enum_VehicleDirection EN_VehicleDirection
){
  if(EN_VehicleDirection > ENV_E_VEHICLE_DIRECTION_BACKWARD){Env__EnvironmentData.ucVehDirection = ((uint8) ENV_E_VEHICLE_DIRECTION_UNKNOWN);}
  else                                                      {Env__EnvironmentData.ucVehDirection = ((uint8) EN_VehicleDirection);}
}

void Env_SetEcuFault(
   boolean BO_IsEcuDefect
){
   Env__EnvironmentData.bECU_Fault = BO_IsEcuDefect;
}

void Env_SetNvmBlockConsistency(
   uint16 ushConsistencyFlags
){
   Env__EnvironmentData.uiNvmBlockConsistence = ushConsistencyFlags;
}

void Env_SetNoiseLevel(
   uint16 U16_NoiseLevel
){
   Env__EnvironmentData.uiNoiseRSSI = U16_NoiseLevel;
}

uint16 Env_GetNoiseLevel(void){
   return Env__EnvironmentData.uiNoiseRSSI;
}

void Env_SetRoadMode(
   boolean BO_RoadMode
){
   Env__EnvironmentData.bRoadMode = BO_RoadMode;
}

void Env_SetWheelInfo(
      Env_Enum_WheelIndex       EN_WheelIndex
   ,  uint16                    U16_WheelSpeed
   ,  Env_Enum_VehicleDirection EN_WheelDirection
){
   if(EN_WheelIndex < ENV_E_MAX_WHEEL_INDEX){
      Env__S_WheelInfo[EN_WheelIndex].U16_WheelSpeed = U16_WheelSpeed;
      if(EN_WheelDirection > ENV_E_VEHICLE_DIRECTION_UNKNOWN){Env__S_WheelInfo[EN_WheelIndex].EN_WheelDirection = ENV_E_VEHICLE_DIRECTION_UNKNOWN;}
      else                                                   {Env__S_WheelInfo[EN_WheelIndex].EN_WheelDirection = EN_WheelDirection;}
   }
   else{
   }
}

static void Env__DetermineVehicleSpeedAndDirection(void){
   uint32  U32_Divider       = 0;
   uint32  U32_WheelSpeedSum = 0U;
   boolean BO_SameDirection  = TRUE;
   uint16  ushVehSpeed;
   uint8   U8_Counter;
   for(
      U8_Counter = 0U;
      U8_Counter < ENV_E_MAX_WHEEL_INDEX;
      U8_Counter ++
   ){
      if(CANMGR__WSPEED_SPEED_INVALID != Env__S_WheelInfo[U8_Counter].U16_WheelSpeed){
         U32_WheelSpeedSum += ((uint32) Env__S_WheelInfo[U8_Counter].U16_WheelSpeed);
         U32_Divider++;
      }
   }
   if(U32_Divider > 0){ushVehSpeed = (U32_WheelSpeedSum + (U32_Divider * 50U)) / (U32_Divider * 100);}
   else               {ushVehSpeed = ENV__VEHICLE_SPEED_INVALID;}
   Env_SetVehicleSpeed(ushVehSpeed);
   for(
      U8_Counter = 0U;
      U8_Counter < (ENV_E_MAX_WHEEL_INDEX - 1);
      U8_Counter ++
   ){
      if(
            Env__S_WheelInfo[U8_Counter     ].EN_WheelDirection
         != Env__S_WheelInfo[U8_Counter + 1U].EN_WheelDirection
      ){
         BO_SameDirection = FALSE;
      }
      else{
      }
   }
   if(FALSE != BO_SameDirection){Env__EnvironmentData.ucVehDirection = Env__S_WheelInfo[0].EN_WheelDirection;}
   else                         {Env__EnvironmentData.ucVehDirection = ((uint8) ENV_E_VEHICLE_DIRECTION_UNKNOWN);}
}

static void Env_SetVehicleSpeed(uint16 U16_VehicleSpeed){
   static uint16 U16_LastVehicleSpeed = 0;
   if(U16_VehicleSpeed < ENV__VEHICLE_SPEED_INVALID){
      Env__EnvironmentData.uiVehSpeed = U16_VehicleSpeed;
           if((U16_LastVehicleSpeed == 0) && (U16_VehicleSpeed  > 4)){infSwcServiceEcuM_vSetEventEcu(SwcServiceEcuM_eEventEcu_VehicleDrive); U16_LastVehicleSpeed = U16_VehicleSpeed;}
      else if((U16_LastVehicleSpeed  > 4) && (U16_VehicleSpeed == 0)){infSwcServiceEcuM_vSetEventEcu(SwcServiceEcuM_eEventEcu_VehicleStop);  U16_LastVehicleSpeed = U16_VehicleSpeed;}
      else{}
   }
   else{
      Env__EnvironmentData.uiVehSpeed = ENV__VEHICLE_SPEED_INVALID;
   }
}

static void Env_SetIgnitionState(
   Env_Enum_IgnitionState EN_IgnitionState
){
        if(       EN_IgnitionState  > ENV_E_IGNITION_ON)              {Env__EnvironmentData.ucIgnition = ENV__IGNITION_STATE_INVALID;}
   else if((uint8)EN_IgnitionState != Env__EnvironmentData.ucIgnition){Env__EnvironmentData.ucIgnition = ((uint8) EN_IgnitionState); HufIf_RCtSaEnvData(&Env__EnvironmentData);}
   else{}
}
