
#ifndef DCM_LCFG_DSPUDS_H
#define DCM_LCFG_DSPUDS_H

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_DidServices_F186_ReadData(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern FUNC(Std_ReturnType,DCM_APPL_CODE)  DcmAppl_DcmReadDataNRC(VAR(uint16,AUTOMATIC)Did,VAR(uint32,AUTOMATIC)DidSignalPosn,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ApplicationID_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_AppSwFingerprint_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ApplicationProgramInformation_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_BootloaderID_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_BootSwFingerprint_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_BootloaderProgramInformation_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ComponentAndSwType_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_AuxId_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ModeId_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_GenealogyVersionNumber_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_GenealogyCrc32_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_FullGenealogyBlock_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ApplicationSignature_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_EcuSerialNumber_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_BoardSerialNumber_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_EcuPartNumber_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_BoardPartNumber_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ManufacturingSupportMode_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ActiveSessionIndicator_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_Vin_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TpmsAbsTicks_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_FLSensorID_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_FRSensorID_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_RLSensorID_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_RRSensorID_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_WheelSensorParameter_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TpmsRxTimeStamp_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TpmsAutoLearnWsParameters_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_NoiseLevelThreshold_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_WheelSensor01_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_WheelSensor02_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_WheelSensor03_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_WheelSensor04_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_LastReceivedWheelSensor_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_PressureOnKeyConfig_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TemperatureWarningThreshold_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_PressureOnKeyStatus_ReadFunc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_ManufacturingSupportMode_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_Vin_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TpmsAbsTicks_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_FLSensorID_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_FRSensorID_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_RLSensorID_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_RRSensorID_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_WheelSensorParameter_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TpmsAutoLearnWsParameters_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_NoiseLevelThreshold_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_PressureOnKeyConfig_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_TemperatureWarningThreshold_WriteFunc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_RequestResultSelfTest_Callback(
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_RequestResultVehicleEolTestProcedure_Callback(
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut1
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut2
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut3
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut4
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut5
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StopVehicleEolTestProcedure_Callback(
VAR(uint8, AUTOMATIC) dataIn1
   ,     VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut1
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Fbl_ProgM_EraseMemoryCallback_65280(
                         P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) dataIn1
   ,     VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     VAR(uint16, AUTOMATIC) CurrentDataLength
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Fbl_ProgM_VerifyDownloadCallback(
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartEcuEolTestProcedure_Callback(
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartSelfTest_Callback(
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartVehicleEolTestProcedure_Callback(
VAR(uint8, AUTOMATIC) dataIn1
   ,     VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut1
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartResetEeprom_Callback(
P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) dataIn1
   ,     VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartAuthorizeEcuProgram_Callback(
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) SecaFBL_GetSeed(VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8,VAR(uint32,AUTOMATIC) Seedlen_u32,VAR(uint32,AUTOMATIC) AccDataRecsize_u32,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) SecaDATA_GetSeed(VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8,VAR(uint32,AUTOMATIC) Seedlen_u32,VAR(uint32,AUTOMATIC) AccDataRecsize_u32,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) SecaFBL_CompareKey(VAR(uint32,AUTOMATIC) KeyLen_32,P2VAR(uint8,AUTOMATIC,DCM_INTERN_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) SecaDATA_CompareKey(VAR(uint32,AUTOMATIC) KeyLen_32,P2VAR(uint8,AUTOMATIC,DCM_INTERN_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(sint16,DCM_VAR)              Dcm_RCSigInN_as16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(sint32,DCM_VAR)              Dcm_RCSigInN_as32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(sint8,DCM_VAR)               Dcm_RCSigInN_as8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint32,DCM_VAR)              Dcm_RCSigInN_au32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint16,DCM_VAR)              Dcm_RCSigInN_au16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint8,DCM_VAR)               Dcm_RCSigInN_au8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif
