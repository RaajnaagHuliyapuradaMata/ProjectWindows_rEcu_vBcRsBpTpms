

#ifndef DCM_APP_INTERFACE_X_H
#define DCM_APP_INTERFACE_X_H

#include "types.h"
#include "Rte_Dcm_Type.h"
#include "Dcm.h"              //to get Dcm Types (esp. Dcm_ConfirmationApiType)

#define cMANUFSUPPMODE_BHSENS   0
#define cMANUFSUPPMODE_RIVIAN   1

#define SECA_LEVEL_APPLICATION  3
#define SECA_LEVEL_PROGRAMMING  5

extern Std_ReturnType SecaFBL_GetSeed(Dcm_SecLevelType SecLevel_u8,
	uint32 Seedlen_u32,
	uint32 AccDataRecsize_u32,
	uint8 * SecurityAccessDataRecord,
	uint8 * Seed,
	Dcm_OpStatusType OpStatus,
	Dcm_NegativeResponseCodeType * ErrorCode);

// prototypes for fixed length configuration
extern Std_ReturnType SecaDATA_GetSeed(Dcm_SecLevelType SecLevel_u8,
                                       uint32 Seedlen_u32,
                                       uint32 AccDataRecsize_u32,
                                       uint8 * SecurityAccessDataRecord,
                                       uint8 * Seed,
                                       Dcm_OpStatusType OpStatus,
                                       Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType SecaDATA_CompareKey(uint32 KeyLen_32,
                                          uint8 * Key,
                                          Dcm_OpStatusType OpStatus,
                                          Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType SecaFBL_CompareKey(uint32 KeyLen_32,
	uint8 * Key,
	Dcm_OpStatusType OpStatus,
	Dcm_NegativeResponseCodeType * ErrorCode);

extern void ComputeKeyFromSeed(uint8 ucSecaLevel);

extern Std_ReturnType DcmDsp_RequestResultSelfTest_Callback(
  Dcm_OpStatusType OpStatus,
  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType DcmDsp_RequestResultVehicleEolTestProcedure_Callback(
  Dcm_OpStatusType OpStatus,
  uint8 * dataOut1,
  uint8 * dataOut2,
  uint8 * dataOut3,
  uint8 * dataOut4,
  uint8 * dataOut5,
  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType DcmDsp_StopVehicleEolTestProcedure_Callback(
  uint8  dataIn1,
  Dcm_OpStatusType OpStatus,
  uint8 * dataOut1,
  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType DcmDsp_StartSelfTest_Callback(
  Dcm_OpStatusType OpStatus,
  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType DcmDsp_StartVehicleEolTestProcedure_Callback(
  uint8  dataIn1,
  Dcm_OpStatusType OpStatus,
  uint8 * dataOut1,
  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType DcmDsp_StartResetEepromCallback(
  const uint8 *  dataIn1,
  Dcm_OpStatusType OpStatus,
  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType Active_Diagnostic_Session_Active_Session_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Application_Software_Fingerprint_Application_Software_Fingerprint_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Application_Software_ID_Application_Software_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Application_Software_Version_LMC_SW_Version_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Hardware_Number_ECU_Hardware_Number_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Installation_Date_MM_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Installation_Date_DD_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Installation_Date_YYYY_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Manufacturing_Date_MM_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Manufacturing_Date_DD_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Manufacturing_Date_YYYY_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Programming_Date_MM_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Programming_Date_DD_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Programming_Date_YYYY_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Ecu_Serial_Number_BHSENS_SerialNumber_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType FL_sensor_ID_FL_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType FR_sensor_ID_FR_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Last_received_wheel_sensor_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType RL_sensor_ID_RL_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType RR_sensor_ID_RR_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType System_Supplier_Hardware_Number_Supplier_Hardware_Number_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType System_Supplier_Hardware_Version_Number_Hardware_Version_Number_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType System_Supplier_Identifier_Supplier_Identifier_43_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Front_Axle_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Rear_Axle_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Auto_Learn_WS_parameters_Clear_ZOM_Scaling_Factor_Value_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Auto_Learn_WS_parameters_Set_Min_ER_RSSI_Level_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_Level_Offset_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_level_threshold_for_RF_interference_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Temperature_Warning_Threshold_Temperature_Threshold_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Rx_Time_Stamp_Rx_time_stamp_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Rx_Time_Stamp_Wheel_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Rx_Time_Stamp_RSSI_Level_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType TPMS_Rx_Time_Stamp_Noise_RSSI_Level_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Vehicle_Identification_VIN_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_01_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_02_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_03_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_sensor_number_04_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_Sensor_Parameter_Legislation_Market_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_Sensor_Parameter_Pressure_Placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_Sensor_Parameter_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType Wheel_Sensor_Parameter_Pressure_Minimum_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data);

extern Std_ReturnType Active_Diagnostic_Session_Active_Session_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Application_Software_Fingerprint_Application_Software_Fingerprint_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Application_Software_ID_Application_Software_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Application_Software_Version_LMC_SW_Version_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Hardware_Number_ECU_Hardware_Number_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Installation_Date_MM_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Installation_Date_DD_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Installation_Date_YYYY_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Manufacturing_Date_MM_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Manufacturing_Date_DD_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Manufacturing_Date_YYYY_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Programming_Date_MM_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Programming_Date_DD_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Programming_Date_YYYY_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Ecu_Serial_Number_BHSENS_SerialNumber_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType FL_sensor_ID_FL_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType FR_sensor_ID_FR_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType RL_sensor_ID_RL_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType RR_sensor_ID_RR_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType System_Supplier_Hardware_Number_Supplier_Hardware_Number_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType System_Supplier_Hardware_Version_Number_Hardware_Version_Number_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType System_Supplier_Identifier_Supplier_Identifier_43_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Front_Axle_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Rear_Axle_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_Auto_Learn_WS_parameters_Clear_ZOM_Scaling_Factor_Value_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_Auto_Learn_WS_parameters_Set_Min_ER_RSSI_Level_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_Level_Offset_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_level_threshold_for_RF_interference_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType TPMS_Temperature_Warning_Threshold_Temperature_Threshold_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Vehicle_Identification_VIN_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Wheel_Sensor_Parameter_Legislation_Market_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Wheel_Sensor_Parameter_Pressure_Placard_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Wheel_Sensor_Parameter_Reserved_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Wheel_Sensor_Parameter_Pressure_Minimum_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType Security_key_Encoded_IV_and_key_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);

// extern void DCM_MakeBackwardCompartibleToVers010205(void);

#endif