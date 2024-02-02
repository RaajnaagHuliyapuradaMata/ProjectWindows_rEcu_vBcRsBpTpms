#include "Std_Types.hpp"

#include "EnvManager.hpp"
#include "SysManagerX.hpp"
#include "CanManagerX.hpp"
#include "Rte_NvM_Type.hpp"

static tsEnv_Data Env__EnvironmentData;
static boolean bCoastModeActive = FALSE;
static Env__Struct_WheelInfo Env__S_WheelInfo[ENV_E_MAX_WHEEL_INDEX];
static uint8 ucVehicleMode;
static Env_Enum_IgnitionState EN_IgnitionStateFromBus;

extern void Env_Init(void){
  uint8 U8_Counter;

  Env__EnvironmentData.uiVehSpeed = ENV__VEHICLE_SPEED_DEFAULT;
  Env__EnvironmentData.ucIgnition = ((uint8_t) ENV_E_IGNITION_OFF);
  Env__EnvironmentData.ucAmbTemperature = ENV__AMBIENT_TEMPERATURE_DEFAULT;
  Env__EnvironmentData.ucAthmosPressure = ENV__ATMOSPHERIC_PRESSURE_DEFAULT;
  Env__EnvironmentData.ucVehDirection = ((uint8) ENV_E_VEHCILE_DIRECTION_FORWARD);
  Env__EnvironmentData.bECU_Fault = FALSE;

  bCoastModeActive = FALSE;

  Env__EnvironmentData.uiNvmBlockConsistence = 0x0000U;

  for(U8_Counter = 0U; U8_Counter < NVM_MAX_CATEGORYS; U8_Counter++)
  {

    Env__EnvironmentData.uiNvmBlockConsistence |= (((uint16) 1U)<<U8_Counter);
  }

  Env__EnvironmentData.uiNoiseRSSI = ENV__NOISE_LEVEL_DEFAULT;

  for(U8_Counter = 0U; U8_Counter < ENV_E_MAX_WHEEL_INDEX; U8_Counter++)
  {
    Env__S_WheelInfo[U8_Counter].U16_WheelSpeed = ENV__VEHICLE_SPEED_DEFAULT;
    Env__S_WheelInfo[U8_Counter].EN_WheelDirection = ENV_E_VEHCILE_DIRECTION_FORWARD;
  }
}

extern tsEnv_Data *Env_GetEnvironmentData(void){
  Env__DetermineVehicleSpeedAndDirection();
  return &Env__EnvironmentData;
}

extern boolean bGetCoastModeActive(void){
  return bCoastModeActive;
}

 //RST Debug: for debugging only
extern Env_Enum_IgnitionState enGetIgnitionStateFromBus(void){
  return EN_IgnitionStateFromBus;
}

extern void Env_SetIgnitionStateFromBus(Env_Enum_IgnitionState EN_IgnitionState)
{

  if(EN_IgnitionStateFromBus != (uint8)EN_IgnitionState)
  {

    EN_IgnitionStateFromBus = EN_IgnitionState;

   if((EN_IgnitionStateFromBus == ENV_E_IGNITION_OFF) ||
        (EN_IgnitionStateFromBus == ENV_E_IGNITION_UNKNOWN))  // in case ignition signal is missing (timeout) CAN TX shall be stopped (OIL 123)
   {
      SYSMGR_SetEcuEvent(cECUEVENT_IGN_OFF);
   }
   else{
      SYSMGR_SetEcuEvent(cECUEVENT_IGN_ON);
   }
  }

  if(bCoastModeActive == FALSE)
  {
    Env_SetIgnitionState(EN_IgnitionStateFromBus);
  }
}

extern void Env_SetIgnitionOnForMobileTireAlert(void){
   Env_SetIgnitionState(ENV_E_IGNITION_ON);
}

extern void Env_SetIgnitionOffForMobileTireAlert(void){
   Env_SetIgnitionState(ENV_E_IGNITION_OFF);
}

extern void Env_ControlIgnitionByCoastmode(eCoastModeType enCMState)
{
  if(enCMState == cCOASTMODE_START)
  {
   bCoastModeActive = TRUE;
    Env_SetIgnitionState(ENV_E_IGNITION_ON);
  }

  else if(enCMState == cCOASTMODE_STOP)
  {
   bCoastModeActive = FALSE;
    Env_SetIgnitionState(EN_IgnitionStateFromBus);
  }

  else if(enCMState == cCOASTMODE_OVER)
  {
   bCoastModeActive = FALSE;
    Env_SetIgnitionState(ENV_E_IGNITION_OFF);
  }
}

extern void Env_SetVehicleMode(uint8 ucVM)
{
  ucVehicleMode = ucVM;
}

extern uint8 Env_GetVehicleMode(void){
  return ucVehicleMode;
}

extern void Env_SetAmbientTemperature(uint8 U8_AmbientTemperature)
{
  if((ENV__AMBIENT_TEMPERATURE_INVALID != U8_AmbientTemperature) && (U8_AmbientTemperature < ENV__AMBIENT_TEMPERATURE_MAX_VALID))
  {
     Env__EnvironmentData.ucAmbTemperature = U8_AmbientTemperature << 1;
  }
  else{
     Env__EnvironmentData.ucAmbTemperature = ENV__AMBIENT_TEMPERATURE_INVALID;
  }
}

extern void Env_SetAtmosphericPressure(uint8 U8_AtmosphericPressure)
{
  Env__EnvironmentData.ucAthmosPressure = U8_AtmosphericPressure;
}

extern void Env_SetVehicleDirection(Env_Enum_VehicleDirection EN_VehicleDirection)
{

  if(EN_VehicleDirection > ENV_E_VEHICLE_DIRECTION_BACKWARD)
  {

    Env__EnvironmentData.ucVehDirection = ((uint8) ENV_E_VEHICLE_DIRECTION_UNKNOWN);
  }
  else{

    Env__EnvironmentData.ucVehDirection = ((uint8) EN_VehicleDirection);
  }
}

extern void Env_SetEcuFault(boolean BO_IsEcuDefect)
{
  Env__EnvironmentData.bECU_Fault = BO_IsEcuDefect;
}

extern void Env_SetNvmBlockConsistency(uint16 ushConsistencyFlags)
{
  Env__EnvironmentData.uiNvmBlockConsistence = ushConsistencyFlags;
}

//extern void Env_SetNvmBlockConsistency(uint8 U8_NvmCategory, boolean BO_IsNvmBlockConsistent)
//{
//  if((U8_NvmCategory == 0U) || (U8_NvmCategory > NVM_MAX_CATEGORYS))
//  {
//
//  }
//  else
//  {
//
//    uint16 U16_PreviousNvmBlockConsistency = Env__EnvironmentData.uiNvmBlockConsistence;
//
//    if(BO_IsNvmBlockConsistent != FALSE)
//    {
//
//      Env__EnvironmentData.uiNvmBlockConsistence |= (((uint16) 1U)<<(U8_NvmCategory - 1U));
//    }
//    else
//    {
//
//      Env__EnvironmentData.uiNvmBlockConsistence &= (~(((uint16) 1U)<<(U8_NvmCategory - 1U)));
//    }
//
//
//    if(Env__EnvironmentData.uiNvmBlockConsistence != U16_PreviousNvmBlockConsistency)
//    {
//
//      HufIf_RCtSaEnvData(&Env__EnvironmentData);
//    }
//    else
//    {
//
//    }
//  }
//}

extern void Env_SetNoiseLevel(uint16 U16_NoiseLevel)
{
  Env__EnvironmentData.uiNoiseRSSI = U16_NoiseLevel;
}

extern uint16 Env_GetNoiseLevel(void){
  return Env__EnvironmentData.uiNoiseRSSI;
}

extern void Env_SetRoadMode(boolean BO_RoadMode)
{
  Env__EnvironmentData.bRoadMode = BO_RoadMode;
}

extern void Env_SetWheelInfo(Env_Enum_WheelIndex EN_WheelIndex, uint16 U16_WheelSpeed, Env_Enum_VehicleDirection EN_WheelDirection)
{

  if(EN_WheelIndex < ENV_E_MAX_WHEEL_INDEX)
  {

    Env__S_WheelInfo[EN_WheelIndex].U16_WheelSpeed = U16_WheelSpeed;

   if(EN_WheelDirection > ENV_E_VEHICLE_DIRECTION_UNKNOWN)
   {
      Env__S_WheelInfo[EN_WheelIndex].EN_WheelDirection = ENV_E_VEHICLE_DIRECTION_UNKNOWN;
   }
   else{
      Env__S_WheelInfo[EN_WheelIndex].EN_WheelDirection = EN_WheelDirection;
   }
  }
  else{

  }
}

static void Env__DetermineVehicleSpeedAndDirection(void){
  uint8 U8_Counter;
  uint32 U32_Divider = 0;
  uint32 U32_WheelSpeedSum = 0U;
  boolean BO_SameDirection = TRUE;
  uint16 ushVehSpeed;

  for(U8_Counter = 0U; U8_Counter < ENV_E_MAX_WHEEL_INDEX; U8_Counter++)
  {
   if(Env__S_WheelInfo[U8_Counter].U16_WheelSpeed != CANMGR__WSPEED_SPEED_INVALID)
   {
      U32_WheelSpeedSum += ((uint32) Env__S_WheelInfo[U8_Counter].U16_WheelSpeed);
      U32_Divider++;
   }
  }

  //ushVehSpeed = (U32_WheelSpeedSum + (ENV_E_MAX_WHEEL_INDEX * 50U)) / (ENV_E_MAX_WHEEL_INDEX * 100);

  if(U32_Divider > 0)
  {
   ushVehSpeed = (U32_WheelSpeedSum + (U32_Divider * 50U)) / (U32_Divider * 100);
  }
  else{
   ushVehSpeed = ENV__VEHICLE_SPEED_INVALID;
  }

  Env_SetVehicleSpeed(ushVehSpeed);

  for(U8_Counter = 0U; U8_Counter < (ENV_E_MAX_WHEEL_INDEX - 1); U8_Counter++)
  {
   if(Env__S_WheelInfo[U8_Counter].EN_WheelDirection != Env__S_WheelInfo[U8_Counter + 1U].EN_WheelDirection)
   {
      BO_SameDirection = FALSE;
   }
   else{

   }
  }

  if(FALSE != BO_SameDirection)
  {
    Env__EnvironmentData.ucVehDirection = Env__S_WheelInfo[0].EN_WheelDirection;
  }
  else{
    Env__EnvironmentData.ucVehDirection = ((uint8) ENV_E_VEHICLE_DIRECTION_UNKNOWN);
  }
}

static void Env_SetVehicleSpeed(uint16 U16_VehicleSpeed)
{
  static uint16 U16_LastVehicleSpeed = 0;

  if(U16_VehicleSpeed < ENV__VEHICLE_SPEED_INVALID)
  {
    Env__EnvironmentData.uiVehSpeed = U16_VehicleSpeed;

   if((U16_LastVehicleSpeed == 0) && (U16_VehicleSpeed > 4))
   {
      SYSMGR_SetEcuEvent(cECUEVENT_VEH_DRIVE);
      U16_LastVehicleSpeed = U16_VehicleSpeed;
   }

   else if((U16_LastVehicleSpeed > 4) && (U16_VehicleSpeed == 0))
   {
      SYSMGR_SetEcuEvent(cECUEVENT_VEH_STOP);
      U16_LastVehicleSpeed = U16_VehicleSpeed;
   }
   else {}
  }
  else{
    Env__EnvironmentData.uiVehSpeed = ENV__VEHICLE_SPEED_INVALID;
  }
}

static void Env_SetIgnitionState(Env_Enum_IgnitionState EN_IgnitionState)
{

  if(EN_IgnitionState > ENV_E_IGNITION_ON)
  {
    Env__EnvironmentData.ucIgnition = ENV__IGNITION_STATE_INVALID;
  }

  else{
   if(Env__EnvironmentData.ucIgnition != (uint8)EN_IgnitionState)
   {
      Env__EnvironmentData.ucIgnition = ((uint8) EN_IgnitionState);
      HufIf_RCtSaEnvData(&Env__EnvironmentData);
   }
  }
}