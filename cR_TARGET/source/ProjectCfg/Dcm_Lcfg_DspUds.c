/******************************************************************************/
/* File   : Dcm_Lcfg_DspUds.c                                                 */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "Dcm.hpp"
#include "DcmDspUds_Uds_Prot.hpp"
#include "ComM_Dcm.hpp"
#include "DcmDspUds_Rc_Prot.hpp"
#include "DcmDspUds_Rdtc_Priv.hpp"
#include "DcmDspUds_Er_Prot.hpp"
#include "DcmDspUds_Cdtcs_Prot.hpp"
#include "DcmDspUds_RequestDownload_Prot.hpp"
#include "DcmAppl.hpp"
#include "DcmCore_DslDsd_Prot.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define RoutineControl_ResetEeprom_DcmDspStartRoutineInSignal_StrtIn          0u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      RoutineControl_VehicleEolTestProcedure_DcmDspStopRoutineOut_Status_StpOut
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspStartRoutineOut_Status_StrtOut
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_TestStatus_ReqRsltOut
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureFL_ReqRsltOut
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureFR_ReqRsltOut
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureRL_ReqRsltOut
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureRR_ReqRsltOut
   ,  DCM_RC_SIGOUTUINT8MAX
}Dcm_DspRoutineSigOutUInt8Idx_ten;

typedef enum{
      RoutineControl_VehicleEolTestProcedure_DcmDspStopRoutineIn_TestProcedureActive_StpIn
   ,  RoutineControl_VehicleEolTestProcedure_DcmDspStartRoutineIn_Timeout_StrtIn
   ,  DCM_RC_SIGINUINT8MAX
}Dcm_DspRoutineSigInUInt8Idx_ten;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
FUNC(uint32,DCM_CODE) Dcm_RCGetSigVal_u32(
      VAR(uint8,  AUTOMATIC) dataSigType_en
   ,  VAR(uint16, AUTOMATIC) idxSignalIndex_u16
);

FUNC(void,DCM_CODE) Dcm_RCSetSigVal(
      VAR(uint8,  AUTOMATIC) dataSigType_en
   ,  VAR(uint16, AUTOMATIC) idxSignalIndex_u16
   ,  VAR(uint32, AUTOMATIC) dataSigVal_u32
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_Fbl_RoutineControl_EraseMemory_65280_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_Fbl_RoutineControl_VerifyDownload_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_EcuEolTestProcedure_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_SelfTest_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_VehicleEolTestProcedure_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_ResetEeprom_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_AuthorizeEcuProgram_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
);

FUNC(uint16,DCM_CODE) Dcm_DIDcalculateTableSize_u16(void);

FUNC(uint16,DCM_CODE) Dcm_RequestDownloadCalculateTableSize_u16(void);

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
CONST(Dcm_Dsp_Session_t, DCM_CONST) Dcm_Dsp_Session[DCM_CFG_DSP_NUMSESSIONS] = {
      {50000, 2000000, 0x01, DCM_NO_BOOT}
   ,  {50000, 2000000, 0x02, DCM_NO_BOOT}
   ,  {50000, 2000000, 0x03, DCM_NO_BOOT}
   ,  {50000, 2000000, 0x04, DCM_NO_BOOT}
   ,  {50000, 2000000, 0x60, DCM_SYS_BOOT}
};

CONST(Dcm_Dsp_Security_t, DCM_CONST) Dcm_Dsp_Security[DCM_CFG_DSP_NUMSECURITY] = {
      {0x00u, 1000, (void*)&SecaFBL_GetSeed,  (void*)&SecaFBL_CompareKey,  0x1, 16, 16, 3, 5, 0, USE_ASYNCH_FNC}
   ,  {0x00u, 1000, (void*)&SecaDATA_GetSeed, (void*)&SecaDATA_CompareKey, 0x2, 16, 16, 3, 5, 0, USE_ASYNCH_FNC}
};

static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST)DcmDspRc_Fbl_RoutineControl_EraseMemory_65280_StrtInSig[]       = {    { 0, 64, DCM_RC_INVLDSIGINDEX,                                                                     DCM_BIG_ENDIAN, DCM_VARIABLE_LENGTH}};
static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST)DcmDspRc_RoutineControl_VehicleEolTestProcedure_StpInSig[]      = {    { 0,  8, RoutineControl_VehicleEolTestProcedure_DcmDspStopRoutineIn_TestProcedureActive_StpIn,     DCM_BIG_ENDIAN, DCM_UINT8}};
static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST)DcmDspRc_RoutineControl_VehicleEolTestProcedure_StrtInSig[]     = {    { 0,  8, RoutineControl_VehicleEolTestProcedure_DcmDspStartRoutineIn_Timeout_StrtIn,               DCM_BIG_ENDIAN, DCM_UINT8}};
static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST)DcmDspRc_RoutineControl_VehicleEolTestProcedure_StrtOutSig[]    = {    { 0,  8, RoutineControl_VehicleEolTestProcedure_DcmDspStartRoutineOut_Status_StrtOut,              DCM_BIG_ENDIAN, DCM_UINT8}};
static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST)DcmDspRc_RoutineControl_VehicleEolTestProcedure_StopOutSig[]    = {    { 0,  8, RoutineControl_VehicleEolTestProcedure_DcmDspStopRoutineOut_Status_StpOut,                DCM_BIG_ENDIAN, DCM_UINT8}};
static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST)DcmDspRc_RoutineControl_VehicleEolTestProcedure_ReqRsltOutSig[] = {
                                                                                                                           { 0,  8, RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_TestStatus_ReqRsltOut, DCM_BIG_ENDIAN, DCM_UINT8}
                                                                                                                        ,  { 8,  8, RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureFL_ReqRsltOut, DCM_BIG_ENDIAN, DCM_UINT8}
                                                                                                                        ,  {16,  8, RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureFR_ReqRsltOut, DCM_BIG_ENDIAN, DCM_UINT8}
                                                                                                                        ,  {24,  8, RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureRL_ReqRsltOut, DCM_BIG_ENDIAN, DCM_UINT8}
                                                                                                                        ,  {32,  8, RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureRR_ReqRsltOut, DCM_BIG_ENDIAN, DCM_UINT8}
};
static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST) DcmDspRc_RoutineControl_ResetEeprom_StrtInSig[]                = {   { 0, 80, RoutineControl_ResetEeprom_DcmDspStartRoutineInSignal_StrtIn,                             DCM_BIG_ENDIAN, DCM_UINT8_N}};

static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_Fbl_RoutineControl_EraseMemory_65280   = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, DcmDspRc_Fbl_RoutineControl_EraseMemory_65280_StrtInSig,   NULL_PTR,                                                 NULL_PTR, NULL_PTR,                                                   NULL_PTR,                                                   NULL_PTR,                                                       8, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_Fbl_RoutineControl_VerifyDownload      = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, NULL_PTR,                                                  NULL_PTR,                                                 NULL_PTR, NULL_PTR,                                                   NULL_PTR,                                                   NULL_PTR,                                                       0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_RoutineControl_EcuEolTestProcedure     = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, NULL_PTR,                                                  NULL_PTR,                                                 NULL_PTR, NULL_PTR,                                                   NULL_PTR,                                                   NULL_PTR,                                                       0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_RoutineControl_SelfTest                = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, NULL_PTR,                                                  NULL_PTR,                                                 NULL_PTR, NULL_PTR,                                                   NULL_PTR,                                                   NULL_PTR,                                                       0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_RoutineControl_VehicleEolTestProcedure = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, DcmDspRc_RoutineControl_VehicleEolTestProcedure_StrtInSig, DcmDspRc_RoutineControl_VehicleEolTestProcedure_StpInSig, NULL_PTR, DcmDspRc_RoutineControl_VehicleEolTestProcedure_StrtOutSig, DcmDspRc_RoutineControl_VehicleEolTestProcedure_StopOutSig, DcmDspRc_RoutineControl_VehicleEolTestProcedure_ReqRsltOutSig,  1, 1, 0, 1, 1, 5,  1, 1, 0, 1, 1, 5, 1, 1, 0, 1, 1, 5};
static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_RoutineControl_ResetEeprom             = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, DcmDspRc_RoutineControl_ResetEeprom_StrtInSig,             NULL_PTR,                                                 NULL_PTR, NULL_PTR,                                                   NULL_PTR,                                                   NULL_PTR,                                                      10, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST)DcmDspRc_RoutineControl_AuthorizeEcuProgram     = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, NULL_PTR,                                                  NULL_PTR,                                                 NULL_PTR, NULL_PTR,                                                   NULL_PTR,                                                   NULL_PTR,                                                       0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

CONST(Dcm_DspRoutineType_tst, DCM_CONST) Dcm_DspRoutine_cast[DCM_CFG_RC_NUMRIDS] = {
      {0x0203,  TRUE, FALSE, &DcmDspRc_RoutineControl_AuthorizeEcuProgram,     &Dcm_Dsp_RC_RoutineControl_AuthorizeEcuProgram_Func,     TRUE, FALSE, FALSE, TRUE, FALSE}
   ,  {0x1248,  TRUE, FALSE, &DcmDspRc_RoutineControl_ResetEeprom,             &Dcm_Dsp_RC_RoutineControl_ResetEeprom_Func,             TRUE, FALSE, FALSE, TRUE, FALSE}
   ,  {0xf200,  TRUE, FALSE, &DcmDspRc_RoutineControl_SelfTest,                &Dcm_Dsp_RC_RoutineControl_SelfTest_Func,                TRUE, FALSE, FALSE, TRUE,  TRUE}
   ,  {0xfdc2,  TRUE, FALSE, &DcmDspRc_RoutineControl_VehicleEolTestProcedure, &Dcm_Dsp_RC_RoutineControl_VehicleEolTestProcedure_Func, TRUE,  TRUE,  TRUE, TRUE,  TRUE}
   ,  {0xfdc3,  TRUE, FALSE, &DcmDspRc_RoutineControl_EcuEolTestProcedure,     &Dcm_Dsp_RC_RoutineControl_EcuEolTestProcedure_Func,     TRUE, FALSE, FALSE, TRUE, FALSE}
   ,  {0xff00, FALSE, FALSE, &DcmDspRc_Fbl_RoutineControl_EraseMemory_65280,   &Dcm_Dsp_RC_Fbl_RoutineControl_EraseMemory_65280_Func,   TRUE, FALSE, FALSE, TRUE, FALSE}
   ,  {0xff01,  TRUE, FALSE, &DcmDspRc_Fbl_RoutineControl_VerifyDownload,      &Dcm_Dsp_RC_Fbl_RoutineControl_VerifyDownload_Func,      TRUE, FALSE, FALSE, TRUE, FALSE}
};

CONST(Dcm_SignalDIDSubStructConfig_tst, DCM_CONST) Dcm_DspDid_ControlInfo_st[13] = {
      {NULL_PTR, NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_ManufacturingSupportMode_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_Vin_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_FLSensorID_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_FRSensorID_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_RRSensorID_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_RLSensorID_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_WheelSensorParameter_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_TpmsAutoLearnWsParameters_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_TemperatureWarningThreshold_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_PressureOnKeyConfig_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_TpmsAbsTicks_WriteFunc}
   ,  {NULL_PTR, NULL_PTR, (void*)&DcmDspData_NoiseLevelThreshold_WriteFunc}
};

CONST(Dcm_DataInfoConfig_tst, DCM_CONST) Dcm_DspDataInfo_st [37] = {
      {(void*)&DcmDspData_ActiveSessionIndicator_ReadFunc,           8, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_AppSwFingerprint_ReadFunc,               192, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_ApplicationID_ReadFunc,                  144, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_ApplicationProgramInformation_ReadFunc,  632, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_ApplicationSignature_ReadFunc,           128, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_AuxId_ReadFunc,                            8, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_BoardPartNumber_ReadFunc,                280, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_BoardSerialNumber_ReadFunc,              144, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_BootSwFingerprint_ReadFunc,              192, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_BootloaderID_ReadFunc,                   144, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_BootloaderProgramInformation_ReadFunc,   632, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_ComponentAndSwType_ReadFunc,              24, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_EcuPartNumber_ReadFunc,                  280, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_EcuSerialNumber_ReadFunc,                144, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_FLSensorID_ReadFunc,                      32, DCM_INVALID_NVDBLOCK,  3, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_FRSensorID_ReadFunc,                      32, DCM_INVALID_NVDBLOCK,  4, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_FullGenealogyBlock_ReadFunc,            1064, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_GenealogyCrc32_ReadFunc,                  32, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_GenealogyVersionNumber_ReadFunc,           8, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_LastReceivedWheelSensor_ReadFunc,         80, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_ManufacturingSupportMode_ReadFunc,         8, DCM_INVALID_NVDBLOCK,  1, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_ModeId_ReadFunc,                          16, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_NoiseLevelThreshold_ReadFunc,             16, DCM_INVALID_NVDBLOCK, 12, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_PressureOnKeyConfig_ReadFunc,             40, DCM_INVALID_NVDBLOCK, 10, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_PressureOnKeyStatus_ReadFunc,            256, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_RLSensorID_ReadFunc,                      32, DCM_INVALID_NVDBLOCK,  6, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_RRSensorID_ReadFunc,                      32, DCM_INVALID_NVDBLOCK,  5, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_TemperatureWarningThreshold_ReadFunc,      8, DCM_INVALID_NVDBLOCK,  9, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_TpmsAbsTicks_ReadFunc,                    16, DCM_INVALID_NVDBLOCK, 11, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_TpmsAutoLearnWsParameters_ReadFunc,       16, DCM_INVALID_NVDBLOCK,  8, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_TpmsRxTimeStamp_ReadFunc,                 96, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_Vin_ReadFunc,                            136, DCM_INVALID_NVDBLOCK,  2, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_WheelSensor01_ReadFunc,                   80, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_WheelSensor02_ReadFunc,                   80, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_WheelSensor03_ReadFunc,                   80, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_WheelSensor04_ReadFunc,                   80, DCM_INVALID_NVDBLOCK,  0, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
   ,  {(void*)&DcmDspData_WheelSensorParameter_ReadFunc,            32, DCM_INVALID_NVDBLOCK,  7, DCM_UINT8, USE_DATA_ASYNCH_FNC, DCM_BIG_ENDIAN, TRUE}
};

static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F181_SigConf[1] = {{0,  2}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F184_SigConf[1] = {{0,  1}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F014_SigConf[1] = {{0,  3}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F180_SigConf[1] = {{0,  9}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F183_SigConf[1] = {{0,  8}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F011_SigConf[1] = {{0, 10}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_101_SigConf[1]  = {{0, 11}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F11C_SigConf[1] = {{0,  5}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F11D_SigConf[1] = {{0, 21}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F110_SigConf[1] = {{0, 18}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F116_SigConf[1] = {{0, 17}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F117_SigConf[1] = {{0, 16}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F200_SigConf[1] = {{0,  4}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F18C_SigConf[1] = {{0, 13}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F113_SigConf[1] = {{0,  7}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F191_SigConf[1] = {{0, 12}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F112_SigConf[1] = {{0,  6}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F018_SigConf[1] = {{0, 20}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F186_SigConf[1] = {{0,  0}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F190_SigConf[1] = {{0, 31}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD23_SigConf[1] = {{0, 28}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD01_SigConf[1] = {{0, 14}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD02_SigConf[1] = {{0, 15}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD04_SigConf[1] = {{0, 25}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD03_SigConf[1] = {{0, 26}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD0C_SigConf[1] = {{0, 36}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD14_SigConf[1] = {{0, 30}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD15_SigConf[1] = {{0, 29}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD24_SigConf[1] = {{0, 22}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FDA1_SigConf[1] = {{0, 32}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FDA2_SigConf[1] = {{0, 33}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FDA3_SigConf[1] = {{0, 34}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FDA4_SigConf[1] = {{0, 35}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FDA5_SigConf[1] = {{0, 19}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD17_SigConf[1] = {{0, 23}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD16_SigConf[1] = {{0, 27}};
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_FD18_SigConf[1] = {{0, 24}};

static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ApplicationID                 = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadApplicationId_UserSpecificCheck,                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_AppSwFingerprint              = {0x04uL, 0xFFFFFFFFuL, &Dcm_ReadAppSwFingerprint_UserSpecificCheck,              0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ApplicationProgramInformation = {0x04uL, 0xFFFFFFFFuL, &Dcm_ReadApplicationProgramInformation_UserSpecificCheck, 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_BootloaderID                  = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadBootloaderId_UserSpecificCheck,                  0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_BootSwFingerprint             = {0x04uL, 0xFFFFFFFFuL, &Dcm_ReadBootSwFingerprint_UserSpecificCheck,             0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_BootloaderProgramInformation  = {0x04uL, 0xFFFFFFFFuL, &Dcm_ReadBootloaderProgramInformation_UserSpecificCheck,  0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ComponentAndSwType            = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadComponentAndSwType_UserSpecificCheck,            0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_AuxId                         = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadAuxId_UserSpecificCheck,                         0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ModeId                        = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadModeId_UserSpecificCheck,                        0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_GenealogyVersionNumber        = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadGenealogyVersionNumber_UserSpecificCheck,        0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_GenealogyCrc32                = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadGenealogyCrc32_UserSpecificCheck,                0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_FullGenealogyBlock            = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadFullGenealogyBlock_UserSpecificCheck,            0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ApplicationSignature          = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadApplicationSignature_UserSpecificCheck,          0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_EcuSerialNumber               = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadEcuSerialNumber_UserSpecificCheck,               0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_BoardSerialNumber             = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadBoardSerialNumber_UserSpecificCheck,             0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_EcuPartNumber                 = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadEcuPartNumber_UserSpecificCheck,                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_BoardPartNumber               = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadBoardPartNumber_UserSpecificCheck,               0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ManufacturingSupportMode      = {0x05uL, 0xFFFFFFFFuL, &Dcm_ManufacturingSupportMode_UserSpecificCheck,          0x4uL, 0x4uL, &Dcm_ManufacturingSupportMode_UserSpecificCheck,};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_ActiveSessionIndicator        = {0x05uL, 0xFFFFFFFFuL, &Dcm_ReadActiveSessionIndicator_UserSpecificCheck,        0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_Vin                           = {0x05uL, 0xFFFFFFFFuL, &Dcm_Vin_UserSpecificCheck,                               0x4uL, 0x4uL, &Dcm_Vin_UserSpecificCheck,};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_TpmsAbsTicks                  = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_FLSensorID                    = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_FRSensorID                    = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_RLSensorID                    = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_RRSensorID                    = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_WheelSensorParameter          = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_TpmsRxTimeStamp               = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_TpmsAutoLearnWsParameters     = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_NoiseLevelThreshold           = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_WheelSensor01                 = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_WheelSensor02                 = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_WheelSensor03                 = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_WheelSensor04                 = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_LastReceivedWheelSensor       = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_PressureOnKeyConfig           = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_TemperatureWarningThreshold   = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x5uL, 0x4uL, NULL_PTR};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_PressureOnKeyStatus           = {0x05uL, 0xFFFFFFFFuL, NULL_PTR,                                                 0x0uL, 0x0uL, NULL_PTR};

CONST(Dcm_DIDConfig_tst, DCM_CONST) Dcm_DIDConfig[] = {
      {0x101,  1,   3, TRUE, FALSE, DcmDspDid_101_SigConf,  &Did_extendedConfig_DcmDspDidInfo_ComponentAndSwType}
   ,  {0xF011, 1,  79, TRUE, FALSE, DcmDspDid_F011_SigConf, &Did_extendedConfig_DcmDspDidInfo_BootloaderProgramInformation}
   ,  {0xF014, 1,  79, TRUE, FALSE, DcmDspDid_F014_SigConf, &Did_extendedConfig_DcmDspDidInfo_ApplicationProgramInformation}
   ,  {0xF018, 1,   1, TRUE, FALSE, DcmDspDid_F018_SigConf, &Did_extendedConfig_DcmDspDidInfo_ManufacturingSupportMode}
   ,  {0xF110, 1,   1, TRUE, FALSE, DcmDspDid_F110_SigConf, &Did_extendedConfig_DcmDspDidInfo_GenealogyVersionNumber}
   ,  {0xF112, 1,  35, TRUE, FALSE, DcmDspDid_F112_SigConf, &Did_extendedConfig_DcmDspDidInfo_BoardPartNumber}
   ,  {0xF113, 1,  18, TRUE, FALSE, DcmDspDid_F113_SigConf, &Did_extendedConfig_DcmDspDidInfo_BoardSerialNumber}
   ,  {0xF116, 1,   4, TRUE, FALSE, DcmDspDid_F116_SigConf, &Did_extendedConfig_DcmDspDidInfo_GenealogyCrc32}
   ,  {0xF117, 1, 133, TRUE, FALSE, DcmDspDid_F117_SigConf, &Did_extendedConfig_DcmDspDidInfo_FullGenealogyBlock}
   ,  {0xF11C, 1,   1, TRUE, FALSE, DcmDspDid_F11C_SigConf, &Did_extendedConfig_DcmDspDidInfo_AuxId}
   ,  {0xF11D, 1,   2, TRUE, FALSE, DcmDspDid_F11D_SigConf, &Did_extendedConfig_DcmDspDidInfo_ModeId}
   ,  {0xF180, 1,  18, TRUE, FALSE, DcmDspDid_F180_SigConf, &Did_extendedConfig_DcmDspDidInfo_BootloaderID}
   ,  {0xF181, 1,  18, TRUE, FALSE, DcmDspDid_F181_SigConf, &Did_extendedConfig_DcmDspDidInfo_ApplicationID}
   ,  {0xF183, 1,  24, TRUE, FALSE, DcmDspDid_F183_SigConf, &Did_extendedConfig_DcmDspDidInfo_BootSwFingerprint}
   ,  {0xF184, 1,  24, TRUE, FALSE, DcmDspDid_F184_SigConf, &Did_extendedConfig_DcmDspDidInfo_AppSwFingerprint}
   ,  {0xF186, 1,   1, TRUE, FALSE, DcmDspDid_F186_SigConf, &Did_extendedConfig_DcmDspDidInfo_ActiveSessionIndicator}
   ,  {0xF18C, 1,  18, TRUE, FALSE, DcmDspDid_F18C_SigConf, &Did_extendedConfig_DcmDspDidInfo_EcuSerialNumber}
   ,  {0xF190, 1,  17, TRUE, FALSE, DcmDspDid_F190_SigConf, &Did_extendedConfig_DcmDspDidInfo_Vin}
   ,  {0xF191, 1,  35, TRUE, FALSE, DcmDspDid_F191_SigConf, &Did_extendedConfig_DcmDspDidInfo_EcuPartNumber}
   ,  {0xF200, 1,  16, TRUE, FALSE, DcmDspDid_F200_SigConf, &Did_extendedConfig_DcmDspDidInfo_ApplicationSignature}
   ,  {0xFD01, 1,   4, TRUE, FALSE, DcmDspDid_FD01_SigConf, &Did_extendedConfig_DcmDspDidInfo_FLSensorID}
   ,  {0xFD02, 1,   4, TRUE, FALSE, DcmDspDid_FD02_SigConf, &Did_extendedConfig_DcmDspDidInfo_FRSensorID}
   ,  {0xFD03, 1,   4, TRUE, FALSE, DcmDspDid_FD03_SigConf, &Did_extendedConfig_DcmDspDidInfo_RRSensorID}
   ,  {0xFD04, 1,   4, TRUE, FALSE, DcmDspDid_FD04_SigConf, &Did_extendedConfig_DcmDspDidInfo_RLSensorID}
   ,  {0xFD0C, 1,   4, TRUE, FALSE, DcmDspDid_FD0C_SigConf, &Did_extendedConfig_DcmDspDidInfo_WheelSensorParameter}
   ,  {0xFD14, 1,  12, TRUE, FALSE, DcmDspDid_FD14_SigConf, &Did_extendedConfig_DcmDspDidInfo_TpmsRxTimeStamp}
   ,  {0xFD15, 1,   2, TRUE, FALSE, DcmDspDid_FD15_SigConf, &Did_extendedConfig_DcmDspDidInfo_TpmsAutoLearnWsParameters}
   ,  {0xFD16, 1,   1, TRUE, FALSE, DcmDspDid_FD16_SigConf, &Did_extendedConfig_DcmDspDidInfo_TemperatureWarningThreshold}
   ,  {0xFD17, 1,   5, TRUE, FALSE, DcmDspDid_FD17_SigConf, &Did_extendedConfig_DcmDspDidInfo_PressureOnKeyConfig}
   ,  {0xFD18, 1,  32, TRUE, FALSE, DcmDspDid_FD18_SigConf, &Did_extendedConfig_DcmDspDidInfo_PressureOnKeyStatus}
   ,  {0xFD23, 1,   2, TRUE, FALSE, DcmDspDid_FD23_SigConf, &Did_extendedConfig_DcmDspDidInfo_TpmsAbsTicks}
   ,  {0xFD24, 1,   2, TRUE, FALSE, DcmDspDid_FD24_SigConf, &Did_extendedConfig_DcmDspDidInfo_NoiseLevelThreshold}
   ,  {0xFDA1, 1,  10, TRUE, FALSE, DcmDspDid_FDA1_SigConf, &Did_extendedConfig_DcmDspDidInfo_WheelSensor01}
   ,  {0xFDA2, 1,  10, TRUE, FALSE, DcmDspDid_FDA2_SigConf, &Did_extendedConfig_DcmDspDidInfo_WheelSensor02}
   ,  {0xFDA3, 1,  10, TRUE, FALSE, DcmDspDid_FDA3_SigConf, &Did_extendedConfig_DcmDspDidInfo_WheelSensor03}
   ,  {0xFDA4, 1,  10, TRUE, FALSE, DcmDspDid_FDA4_SigConf, &Did_extendedConfig_DcmDspDidInfo_WheelSensor04}
   ,  {0xFDA5, 1,  10, TRUE, FALSE, DcmDspDid_FDA5_SigConf, &Did_extendedConfig_DcmDspDidInfo_LastReceivedWheelSensor}
};

CONST(Dcm_DspEcuReset_tst, DCM_CONST) Dcm_DspEcuResetType_cast[DCM_CFG_DSP_NUMRESETTYPE] = {
      {0x01, DCM_RESET_NO_BOOT}
   ,  {0x03, DCM_RESET_NO_BOOT}
   ,  {0x4C, DCM_RESET_OEM_BOOT}
};

CONST(Dcm_Dsld_AllChannelsInfoType, DCM_CONST) Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO] = {{ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel}};
CONST (Dcm_RequestDownloadConfig_tst, DCM_CONST) Dcm_RequestDownloadConfig_cast[] = {
      {0xA0080000, 0xA00FFFFF, 0xFFFFFFFFuL, 0}
   ,  {0xA0048000, 0xA005FFFF, 0xFFFFFFFFuL, 0}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(sint16, DCM_VAR)              Dcm_RCSigOutN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(sint32, DCM_VAR)              Dcm_RCSigOutN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(sint8, DCM_VAR)               Dcm_RCSigOutN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint32, DCM_VAR)              Dcm_RCSigOutN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint16, DCM_VAR)              Dcm_RCSigOutN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint8, DCM_VAR) Dcm_RCSigOut_au8[7];
       VAR(uint8, DCM_VAR) Dcm_RCSigOutN_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(sint16, DCM_VAR)              Dcm_RCSigInN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(sint32, DCM_VAR)              Dcm_RCSigInN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(sint8, DCM_VAR)               Dcm_RCSigInN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint32, DCM_VAR)              Dcm_RCSigInN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint16, DCM_VAR)              Dcm_RCSigInN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint8, DCM_VAR)               Dcm_RCSigIn_au8[2];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8, DCM_VAR)               Dcm_RCSigInN_au8[10];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_DspRoutineStatusType_ten, DCM_VAR) Dcm_RoutineStatus_aen[DCM_CFG_RC_NUMRIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
P2FUNC(Std_ReturnType,DCM_APPL_CODE,Dcm_ComMUserReEnableModeRuleRef)(void) = &DcmAppl_UserCommCtrlReEnableModeRuleService;
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(uint32,DCM_CODE) Dcm_RCGetSigVal_u32(
      VAR(uint8,  AUTOMATIC) dataSigType_en
   ,  VAR(uint16, AUTOMATIC) idxSignalIndex_u16
){
   VAR(uint32, AUTOMATIC)       dataSigVal_u32;
   dataSigVal_u32 = 0;
   switch(
      dataSigType_en
   ){
      case DCM_UINT8:
         dataSigVal_u32 = (uint32)Dcm_RCSigOut_au8[idxSignalIndex_u16];
         break;

       default:
         (void)idxSignalIndex_u16;
         break;
   }
   return dataSigVal_u32;
}

FUNC(void,DCM_CODE) Dcm_RCSetSigVal(
      VAR(uint8,  AUTOMATIC) dataSigType_en
   ,  VAR(uint16, AUTOMATIC) idxSignalIndex_u16
   ,  VAR(uint32, AUTOMATIC) dataSigVal_u32
){
   switch(
      dataSigType_en
   ){
      case DCM_UINT8:
         Dcm_RCSigIn_au8[idxSignalIndex_u16]=(uint8)dataSigVal_u32;
         break;

      default:
         (void)dataSigVal_u32;
         (void)idxSignalIndex_u16;
         break;
   }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_Fbl_RoutineControl_EraseMemory_65280_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
      dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = Fbl_ProgM_EraseMemoryCallback_65280(
               &Dcm_InParameterBuf_au8[0]
            ,  Dcm_RCOpStatus_u8
            ,  Dcm_RCCurrDataLength_u16
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_Fbl_RoutineControl_VerifyDownload_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
      dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = Fbl_ProgM_VerifyDownloadCallback(
               Dcm_RCOpStatus_u8
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_EcuEolTestProcedure_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
   dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = DcmDsp_StartEcuEolTestProcedure_Callback(
               Dcm_RCOpStatus_u8
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_SelfTest_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
      dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = DcmDsp_StartSelfTest_Callback(
               Dcm_RCOpStatus_u8
            ,  &Dcm_RCNegResCode_u8
         );

         break;

      case 3u:
         dataRetVal_u8 = DcmDsp_RequestResultSelfTest_Callback(
            Dcm_RCOpStatus_u8,
            &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_VehicleEolTestProcedure_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
      dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = DcmDsp_StartVehicleEolTestProcedure_Callback(
               Dcm_RCSigIn_au8[RoutineControl_VehicleEolTestProcedure_DcmDspStartRoutineIn_Timeout_StrtIn]
            ,  Dcm_RCOpStatus_u8
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspStartRoutineOut_Status_StrtOut]
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      case 2u:
         dataRetVal_u8 = DcmDsp_StopVehicleEolTestProcedure_Callback(
               Dcm_RCSigIn_au8[RoutineControl_VehicleEolTestProcedure_DcmDspStopRoutineIn_TestProcedureActive_StpIn]
            ,  Dcm_RCOpStatus_u8
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspStopRoutineOut_Status_StpOut]
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      case 3u:
         dataRetVal_u8 = DcmDsp_RequestResultVehicleEolTestProcedure_Callback(
               Dcm_RCOpStatus_u8
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_TestStatus_ReqRsltOut]
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureFL_ReqRsltOut]
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureFR_ReqRsltOut]
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureRL_ReqRsltOut]
            ,  &Dcm_RCSigOut_au8[RoutineControl_VehicleEolTestProcedure_DcmDspRequestRoutineResults_PressureRR_ReqRsltOut]
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_ResetEeprom_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
      dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = DcmDsp_StartResetEeprom_Callback(
               &Dcm_RCSigInN_au8[RoutineControl_ResetEeprom_DcmDspStartRoutineInSignal_StrtIn]
            ,  Dcm_RCOpStatus_u8
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_RoutineControl_AuthorizeEcuProgram_Func(
   VAR(uint8, AUTOMATIC) dataSubFunc_u8
){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   switch(
      dataSubFunc_u8
   ){
      case 1u:
         dataRetVal_u8 = DcmDsp_StartAuthorizeEcuProgram_Callback(
               Dcm_RCOpStatus_u8
            ,  &Dcm_RCNegResCode_u8
         );
         break;

      default:
         Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         break;
   }
   return dataRetVal_u8;
}

FUNC(uint16,DCM_CODE) Dcm_DIDcalculateTableSize_u16(void){
   return ((uint16)(sizeof(Dcm_DIDConfig)) / (uint16)(sizeof(Dcm_DIDConfig_tst)));
}

FUNC(uint16,DCM_CODE) Dcm_RequestDownloadCalculateTableSize_u16(void){
  return ((uint16)(sizeof(Dcm_RequestDownloadConfig_cast))/(uint16)(sizeof(Dcm_RequestDownloadConfig_tst)));
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

