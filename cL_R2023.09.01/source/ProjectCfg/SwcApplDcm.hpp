#pragma once
/******************************************************************************/
/* File   : SwcApplDcm.hpp                                                    */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "types.hpp"
#include "Rte_Dcm_Type.hpp"
#include "Dcm.hpp"              //to get Dcm Types (esp. Dcm_ConfirmationApiType)

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cMANUFSUPPMODE_BHSENS   0
#define cMANUFSUPPMODE_RIVIAN   1

#define SECA_LEVEL_APPLICATION  3
#define SECA_LEVEL_PROGRAMMING  5

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern Std_ReturnType SecaFBL_GetSeed(Dcm_SecLevelType SecLevel_u8
   ,  uint32 Seedlen_u32
   ,  uint32 AccDataRecsize_u32
   ,  uint8 * SecurityAccessDataRecord
   ,  uint8 * Seed
   ,  Dcm_OpStatusType OpStatus
   ,  Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType SecaDATA_GetSeed(Dcm_SecLevelType SecLevel_u8
   ,                                      uint32 Seedlen_u32
   ,                                      uint32 AccDataRecsize_u32
   ,                                      uint8 * SecurityAccessDataRecord
   ,                                      uint8 * Seed
   ,                                      Dcm_OpStatusType OpStatus
   ,                                      Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType SecaDATA_CompareKey(uint32 KeyLen_32
   ,                                         uint8 * Key
   ,                                         Dcm_OpStatusType OpStatus
   ,                                         Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType SecaFBL_CompareKey(uint32 KeyLen_32
   ,  uint8 * Key
   ,  Dcm_OpStatusType OpStatus
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern void ComputeKeyFromSeed(uint8 ucSecaLevel);

extern Std_ReturnType DcmDsp_RequestResultSelfTest_Callback(
  Dcm_OpStatusType OpStatus
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType DcmDsp_RequestResultVehicleEolTestProcedure_Callback(
  Dcm_OpStatusType OpStatus
   ,  uint8 * dataOut1
   ,  uint8 * dataOut2
   ,  uint8 * dataOut3
   ,  uint8 * dataOut4
   ,  uint8 * dataOut5
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType DcmDsp_StopVehicleEolTestProcedure_Callback(
  uint8  dataIn1
   ,  Dcm_OpStatusType OpStatus
   ,  uint8 * dataOut1
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType DcmDsp_StartSelfTest_Callback(
  Dcm_OpStatusType OpStatus
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType DcmDsp_StartVehicleEolTestProcedure_Callback(
  uint8  dataIn1
   ,  Dcm_OpStatusType OpStatus
   ,  uint8 * dataOut1
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType DcmDsp_StartResetEepromCallback(
  const uint8 *  dataIn1
   ,  Dcm_OpStatusType OpStatus
   ,  Dcm_NegativeResponseCodeType * ErrorCode
);

extern Std_ReturnType SwcApplDcm_FuncDidRead_SessionDiagnosticActive(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_SwApplFingerprint(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_SwApplId(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_SwApplVersion_cL(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumEcuHw(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuInstallation_MM(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuInstallation_DD(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuInstallation_YYYY(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuManufacturing_MM(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuManufacturing_DD(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuManufacturing_YYYY(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuProgramming_MM(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuProgramming_DD(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuProgramming_YYYY(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumEcuSerial_Supplier1(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_FL(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_FR(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastIdSensor(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastPosition(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastReserved(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastPressure(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastTemperature(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_PressurePlacard(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastCounterLifeTime(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_RL(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_RR(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumHw_Supplier1(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumHwVersionSys_Supplier1(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_IdSupplierSys(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_TicksAbsAxle_Front(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_TicksAbsAxle_Rear(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelAutolearnClearScaleZom(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelAutolearnErRssiLvl_Min(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_LvlNoiseRfOffset_Threshold(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_LvlNoiseRfOffset_ThresholdInterference(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_WarningTemperature_Threshold(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRx(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRxIdWheel(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRxRssiLvl(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRxRssiLvlNoise(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumIdVehicle(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_IdSensor(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Position(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Reserved(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Pressure_ReceivedLast(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Temperature(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_PressurePlacard(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_CounterLifeTime(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_IdSensor(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Position(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Reserved(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Pressure_ReceivedLast(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Temperature(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_PressurePlacard(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_CounterLifeTime(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_IdSensor(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Position(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Reserved(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Pressure_ReceivedLast(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Temperature(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_PressurePlacard(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_CounterLifeTime(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_IdSensor(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Position(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Reserved(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Pressure_ReceivedLast(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Temperature(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_PressurePlacard(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_CounterLifeTime(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelLegislation(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelPressurePlacard(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelReserved(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelPressureMin(Dcm_OpStatusType OpStatus, uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_SessionDiagnosticActive(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_SwApplFingerprint(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_SwApplId(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_SwApplVersion_cL(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_NumEcuHw(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuInstallation_MM(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuInstallation_DD(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuInstallation_YYYY(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuManufacturing_MM(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuManufacturing_DD(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuManufacturing_YYYY(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuProgramming_MM(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuProgramming_DD(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuProgramming_YYYY(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_NumEcuSerial_Supplier1(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_FL(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_FR(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_RL(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_RR(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_NumHw_Supplier1(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_NumHwVersionSys_Supplier1(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_IdSupplierSys(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_TicksAbsAxle_Front(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_TicksAbsAxle_Rear(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelAutolearnClearScaleZom(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelAutolearnErRssiLvl_Min(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_LvlNoiseRfOffset_Threshold(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_LvlNoiseRfOffset_ThresholdInterference(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_WarningTemperature_Threshold(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_NumIdVehicle(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelLegislation(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelPressurePlacard(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelReserved(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelPressureMin(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);
extern Std_ReturnType SwcApplDcm_FuncDidWrite_SecurityKeyEncodedIV(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

