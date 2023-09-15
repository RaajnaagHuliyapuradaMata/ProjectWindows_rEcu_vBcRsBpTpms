#pragma once
/******************************************************************************/
/* File   : SwcApplDcm.c                                                      */
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
#include "SwcApplDcm.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cCHECKARRAYSIZE 1
#define cCREATESEED 2
#define cCALCULATEKEY 3
#define EOL_ROUT_NEVER_STARTED            0x00U
#define EOL_ROUT_RUNNING                  0x01U
#define EOL_ROUT_FINISHED_SUCCESSFULLY    0x02U
#define EOL_ROUT_RESERVED                 0x03U
#define EOL_ROUT_STOPPED_ON_REQUEST       0x04U
#define EOL_ROUT_START_WRONG_PARAM        0x05U
#define EOL_ROUT_ENDED_WITH_ERROR         0x07U

static void CalculateSeed(uint8* Seed);
static void DecryptAes256CbcMessage(uint8* Message, uint16 ucSizeMessage);

#include "DemAppInterfaceX.hpp"
#include "DemManagerX.hpp"
#include "version.hpp"
#include "iTpms_Interface.hpp"
#include "DcmAppl.hpp"
#include "rba_DiagLib_MemUtils.hpp"
#include "Rte_Nvm_Type.hpp"
#include "SysManagerX.hpp"
#include "DcmManagerX.hpp"
#include "FeeFblBlockInterfaceX.hpp"
#include "ProductionFlashInterfaceX.hpp"
#include "RdcStandstillX.hpp"
#include "DcmMsgAuthenticationX.hpp"

#include "version.hpp"
#include "crc.hpp"
#include "hmac_sha2.hpp"
#include "aes.hpp"

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
static uint8 aucSecurityKeyApplication[16];
static uint8 aucCurrentSeed[16];
static uint8 aucGlobalDataTemp[10];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void DecryptAes256CbcMessage(
   uint8* Message,
   uint16 ucSizeMessage){
  struct AES_ctx tAesInput;
  uint8 aucVector[16];
  uint8 aucSymKey[32];

  (void)FEEFBL_GetInitialVector(aucVector);
  (void)FEEFBL_GetSymmetricKey(aucSymKey);
  AES_init_ctx_iv(&tAesInput, aucSymKey, aucVector);
  AES_CBC_decrypt_buffer(&tAesInput, Message, ucSizeMessage); //decrypted clear text is in Message now
}

static void CalculateSeed(uint8* Seed){
   uint8 i;
  uint64 ullRandom;

  ullRandom = DCMMGR_GetNonceCounter();
  ullRandom = ullRandom*ullRandom; // make it bigger

   for(i = 0; i < 16; i++){
    Seed[i] = (ullRandom >> i) & 0xff;
  }

  rba_DiagLib_MemUtils_MemCpy(aucCurrentSeed, (const uint8*)Seed, sizeof(aucCurrentSeed));
}

extern Std_ReturnType DcmDsp_StartSelfTest_Callback(Dcm_OpStatusType OpStatus
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
   DCMMGR_TriggerDiagRoutineSelfCheck();
  *ErrorCode = DCM_E_OK;
  return E_OK;
}

extern Std_ReturnType DcmDsp_RequestResultSelfTest_Callback(Dcm_OpStatusType OpStatus
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
   if(DCMMGR_GetDiagRoutineSelfCheckResult() == FALSE){
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    return E_NOT_OK;
  }
  else{
    *ErrorCode = DCM_E_OK;
    return E_OK;
  }
}

extern Std_ReturnType DcmDsp_StartVehicleEolTestProcedure_Callback(uint8  dataIn1
   ,                                                                  Dcm_OpStatusType OpStatus
   ,                                                                  uint8 * dataOut1
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
  tsTPMSDiag_Data S_DiagData;
  uint16 ushRespDataLength;
  uint8 ucCounter;
  S_DiagData.pucReqData = &dataIn1;
  S_DiagData.uiReqDataLen = 1;  //1 byte start command
  S_DiagData.puiResDataLen = &ushRespDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_START_TPMS_EOL, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
      for(ucCounter = 0; ucCounter < (*S_DiagData.puiResDataLen); ucCounter++){
      dataOut1[ucCounter] = S_DiagData.pucResData[ucCounter];
   }
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}

extern Std_ReturnType DcmDsp_RequestResultVehicleEolTestProcedure_Callback( Dcm_OpStatusType OpStatus
   ,                                                                           uint8 * dataOut1
   ,                                                                           uint8 * dataOut2
   ,                                                                           uint8 * dataOut3
   ,                                                                           uint8 * dataOut4
   ,                                                                           uint8 * dataOut5
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
  tsTPMSDiag_Data S_DiagData;
  uint16 ushRespDataLength;
  S_DiagData.pucReqData = (uint8*)NULL;
  S_DiagData.uiReqDataLen = 0;  //routine request result has no data byte
  S_DiagData.puiResDataLen = &ushRespDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_RESULT_TPMS_EOL, &S_DiagData);
   if((*ErrorCode == DCM_E_OK) && (*S_DiagData.puiResDataLen == 5)){
    *dataOut1 = S_DiagData.pucResData[0];
    *dataOut2 = S_DiagData.pucResData[1];
    *dataOut3 = S_DiagData.pucResData[2];
    *dataOut4 = S_DiagData.pucResData[3];
    *dataOut5 = S_DiagData.pucResData[4];
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}

extern Std_ReturnType DcmDsp_StopVehicleEolTestProcedure_Callback(uint8  dataIn1
   ,                                                                 Dcm_OpStatusType OpStatus
   ,                                                                 uint8 * dataOut1
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
  tsTPMSDiag_Data S_DiagData;
  uint16 ushRespDataLength;
  uint8 ucCounter;
  S_DiagData.pucReqData = &dataIn1;
  S_DiagData.uiReqDataLen = 1;  //1 byte stop command
  S_DiagData.puiResDataLen = &ushRespDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_STOP_TPMS_EOL, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
      for(ucCounter = 0; ucCounter < (*S_DiagData.puiResDataLen); ucCounter++){
      dataOut1[ucCounter] = S_DiagData.pucResData[ucCounter];
   }
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}

extern Std_ReturnType DcmDsp_StartResetEepromCallback(const uint8 *  dataIn1
   ,                                                     Dcm_OpStatusType OpStatus
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 ucPassword[10] = {'M','S','P','P','D','P','2','0','2','0'};
  uint8 i;
  uint8 clearMem[32];
  Std_ReturnType RetVal = E_OK;
   for(i = 0; i < 8; i++){
      if(dataIn1[i] != ucPassword[i]){
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
      RetVal = E_NOT_OK;
   }
  }
   if(RetVal == E_OK){
    *ErrorCode = DCM_E_OK;
   for(i=0; i<sizeof(clearMem); i++)
   {
      clearMem[i] = 0xff;
   }
#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_AES256_CBC)
    (void)FEEFBL_PutAesInitialVector(clearMem);
    (void)FEEFBL_PutAesSymmetricKey(clearMem);
#endif
   PRODFLASH_PutVin(clearMem);
   PRODFLASH_PutManufacturingSupportMode(clearMem);
    Memstack_ClearCurrentNvMConsistence();
  }
  return RetVal;
}

Std_ReturnType SwcApplDcm_FuncDidRead_SessionDiagnosticActive(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  Dcm_SesCtrlType ActiveSession;
  (void)Dcm_GetSesCtrlType(&ActiveSession);
  *Data = ActiveSession;
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_SwApplFingerprint(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)FEEFBL_GetFingerprint(Data);
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_SwApplId(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[8];
   if(VERSION_GetLmcSwVersion(
      tempData,
      cSTRING_SIZ_LMCSWV,
      cMETADATA_APP) == FALSE){
    return E_NOT_OK;
  }
  else{
    Data[0] = tempData[0];
   Data[1] = tempData[1];
   Data[2] = tempData[2];
    return E_OK;
  }
}

Std_ReturnType SwcApplDcm_FuncDidRead_SwApplVersion_cL(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[8];
   if(VERSION_GetBhsensSwVersionString(
      tempData,
      cSTRING_BHSENS_SW_VERSION_LENGTH,
      cMETADATA_APP) == FALSE){
    return E_NOT_OK;
  }
  else{
      Data[0] = tempData[0] / 10 + 0x30;
   Data[1] = tempData[0]%10 +0x30;
   Data[2] = tempData[1]/10 +0x30;
   Data[3] = tempData[1]%10 +0x30;
   Data[4] = tempData[3]/10 +0x30;
   Data[5] = tempData[3]%10 +0x30;
    return E_OK;
  }
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumEcuHw(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
   Data += PRODFLASH_GetCustomerHwPartNumber(Data);
   return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuInstallation_MM(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[6];
  (void)FEEFBL_GetEcuInstallationDate(tempData);
   if((tempData[0] < 10) && (tempData[1] < 10)){
    Data[0] = 10*tempData[0] + tempData[1];
  }
  else{
    Data[0] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuInstallation_DD(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[6];
  (void)FEEFBL_GetEcuInstallationDate(tempData);
   if((tempData[2] < 10) && (tempData[3] < 10)){
    Data[0] = 10*tempData[2] + tempData[3];
  }
  else{
    Data[0] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuInstallation_YYYY(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[6];
  (void)FEEFBL_GetEcuInstallationDate(tempData);
   if((tempData[4] < 10) && (tempData[5] < 10)){
   Data[0] = 0x20;
    Data[1] = 10*tempData[4] + tempData[5];
  }
  else{
    Data[0] = 0xFF;
   Data[1] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuManufacturing_MM(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[6];
  (void)PRODFLASH_GetBhsensProductionDate(tempData);
   if((tempData[2] >= 0x30) && (tempData[2] <= 0x39) && (tempData[3] >= 0x30) && (tempData[3] <= 0x39)){
  Data[0] = 16*(tempData[2]-0x30) + (tempData[3]-0x30);
  }
  else{
    Data[0] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuManufacturing_DD(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[6];
  (void)PRODFLASH_GetBhsensProductionDate(tempData);
   if((tempData[4] >= 0x30) && (tempData[4] <= 0x39) && (tempData[5] >= 0x30) && (tempData[5] <= 0x39)){
  Data[0] = 16*(tempData[4]-0x30) + (tempData[5]-0x30);
  }
  else{
    Data[0] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuManufacturing_YYYY(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 tempData[6];
  (void)PRODFLASH_GetBhsensProductionDate(tempData);
   if((tempData[0] >= 0x30) && (tempData[0] <= 0x39) && (tempData[1] >= 0x30) && (tempData[1] <= 0x39)){
   Data[0] = 0x20;
    Data[1] = 16*(tempData[0]-0x30) + (tempData[1]-0x30);
  }
  else{
    Data[0] = 0xFF;
   Data[1] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuProgramming_MM(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
   uint8 tempData[6];
   (void)FEEFBL_GetProgrammingDate(tempData, cMETADATA_APP);
   if((tempData[0] < 10) && (tempData[1] < 10)){
   	Data[0] = 10 * tempData[0] + tempData[1];
   }
   else{
   	Data[0] = 0xFF;
   }
   return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuProgramming_DD(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
   uint8 tempData[6];
   (void)FEEFBL_GetProgrammingDate(tempData, cMETADATA_APP);
   if((tempData[2] < 10) && (tempData[3] < 10)){
   	Data[0] = 10 * tempData[2] + tempData[3];
   }
   else{
   	Data[0] = 0xFF;
   }
   return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DateEcuProgramming_YYYY(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
   uint8 tempData[6];
   (void)FEEFBL_GetProgrammingDate(tempData, cMETADATA_APP);
   if((tempData[4] < 10) && (tempData[5] < 10)){
   	Data[0] = 0x20;
   	Data[1] = 10 * tempData[4] + tempData[5];
   }
   else{
   	Data[0] = 0xFF;
   	Data[1] = 0xFF;
   }
   return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumEcuSerial_Supplier1(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)PRODFLASH_GetCustomerEcuSerialNumber(Data);
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumHw_Supplier1(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)PRODFLASH_GetBhsensHardwareNumber(Data);
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumHwVersionSys_Supplier1(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 ucHwVersion[3];
  uint8 ucCalWeek;
  uint8 ucMonth;
  (void)PRODFLASH_GetBhsensHwVersionInfo(ucHwVersion);
  ucCalWeek = ucHwVersion[1] - 1;
  ucMonth = (ucCalWeek / 4) + 1;
   if(ucMonth > 12){
   ucMonth = 12;
  }
  Data[0] = ucHwVersion[0];
  Data[1] = ucMonth;
  Data[2] = 1;
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_IdSupplierSys(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  Data[0] = 'B';
  Data[1] = 'H';
  Data[2] = 'S';
  Data[3] = 'E';
  Data[4] = 'N';
  Data[5] = 'S';
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumIdVehicle(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
   (void)PRODFLASH_GetVin(Data);
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_FL(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_FL, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4U; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_FR(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_FR, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4U; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_RL(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_RL, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4U; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_IdSensor_RR(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_RR, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4U; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_TicksAbsAxle_Front(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ABS_TICKS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[0];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_TicksAbsAxle_Rear(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ABS_TICKS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[1];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelAutolearnClearScaleZom(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[0];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelAutolearnErRssiLvl_Min(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[1];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_LvlNoiseRfOffset_Threshold(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_NOISE_LEVEL, &S_DiagData);
  Data[0] = S_DiagData.pucResData[0];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_LvlNoiseRfOffset_ThresholdInterference(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_NOISE_LEVEL, &S_DiagData);
  Data[0] = S_DiagData.pucResData[1];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_WarningTemperature_Threshold(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_TEMPERATURE_WARNING_THR, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelLegislation(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[0];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelPressurePlacard(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[1];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelReserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[2];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ParamSensorWheelPressureMin(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);
  Data[0] = S_DiagData.pucResData[3];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastIdSensor(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastPosition(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);
    Data[0] = S_DiagData.pucResData[4];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastReserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);
    Data[0] = S_DiagData.pucResData[5];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastPressure(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);
    Data[0] = S_DiagData.pucResData[6];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastTemperature(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);
    Data[0] = S_DiagData.pucResData[7];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_PressurePlacard(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  Data[0] = 0xFF; //Todo GL
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_ReceivedLastCounterLifeTime(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  Data[0] = 0xFF; //Todo GL
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRx(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRxIdWheel(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRxRssiLvl(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_TimeStampRxRssiLvlNoise(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_IdSensor(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Position(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
    Data[0] = S_DiagData.pucResData[4];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Reserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
    Data[0] = S_DiagData.pucResData[5];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Pressure_ReceivedLast(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
    Data[0] = S_DiagData.pucResData[6];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_Temperature(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
    Data[0] = S_DiagData.pucResData[7];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_PressurePlacard(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
    Data[0] = S_DiagData.pucResData[8];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor1_CounterLifeTime(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
    Data[0] = S_DiagData.pucResData[9];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_IdSensor(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Position(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
    Data[0] = S_DiagData.pucResData[4];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Reserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
    Data[0] = S_DiagData.pucResData[5];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Pressure_ReceivedLast(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
    Data[0] = S_DiagData.pucResData[6];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_Temperature(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
    Data[0] = S_DiagData.pucResData[7];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_PressurePlacard(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
    Data[0] = S_DiagData.pucResData[8];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor2_CounterLifeTime(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
    Data[0] = S_DiagData.pucResData[9];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_IdSensor(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Position(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
    Data[0] = S_DiagData.pucResData[4];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Reserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
    Data[0] = S_DiagData.pucResData[5];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Pressure_ReceivedLast(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
    Data[0] = S_DiagData.pucResData[6];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_Temperature(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
    Data[0] = S_DiagData.pucResData[7];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_PressurePlacard(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
    Data[0] = S_DiagData.pucResData[8];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor3_CounterLifeTime(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
    Data[0] = S_DiagData.pucResData[9];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_IdSensor(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
   for(U8_Counter = 0; U8_Counter < 4; U8_Counter++){
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Position(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
    Data[0] = S_DiagData.pucResData[4];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Reserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
    Data[0] = S_DiagData.pucResData[5];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Pressure_ReceivedLast(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
    Data[0] = S_DiagData.pucResData[6];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_Temperature(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
    Data[0] = S_DiagData.pucResData[7];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_PressurePlacard(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
    Data[0] = S_DiagData.pucResData[8];
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidRead_NumSensor4_CounterLifeTime(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  tsTPMSDiag_Data S_DiagData;
  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
    Data[0] = S_DiagData.pucResData[9];
  return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Bootloader_ID_UserSpecificCheck(
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8,
   VAR(uint16, AUTOMATIC) did_u16,
   VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){
   Std_ReturnType result;
   result = E_OK;
   if(dataDirection_en == DCM_SUPPORT_WRITE){
   	result = E_NOT_OK;
   	*Nrc_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   }
   return result;
}

Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B001_VoltageBattery(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_LVBatteryVoltage(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B002_SpeedVehicle(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_VehicleSpeed(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B003_TemperatureAmbient(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_AmbientTemperature(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B004_Reserved(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_Reserved(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B006_OccurenceDate(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_OccDate(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B006_OccurenceTime(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_OccTime(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B007_TirePressures(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_TirePressures(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B008_TireTemperatures(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_TireTemperatures(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B009_ModesAndStatusEcu(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_EcuMode_LLStatus(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_F103_ModePowerVehicle(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
 (void) Dem_GetData_VehicleMode(Data);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_F104_Mileage(
   Dcm_OpStatusType OpStatus,
   uint8* Data){
  (void)Dem_GetData_Mileage(Data);
  return E_OK;
}

Std_ReturnType SwcApplDcm_FuncDidWrite_SessionDiagnosticActive(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_SwApplFingerprint(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){

   (void)FEEFBL_PutFingerprint(Data);

   return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_SwApplId(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_SwApplVersion_cL(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_NumEcuHw(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuInstallation_MM(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 i;
   for(i = 0; i < 10; i++){
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0]/10;
  aucGlobalDataTemp[1] = Data[0]%10;
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuInstallation_DD(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  aucGlobalDataTemp[2] = Data[0]/10;
  aucGlobalDataTemp[3] = Data[0]%10;
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuInstallation_YYYY(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  aucGlobalDataTemp[4] = Data[1]/10;
  aucGlobalDataTemp[5] = Data[1]%10;
  (void)FEEFBL_PutEcuInstallationDate(aucGlobalDataTemp);
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuManufacturing_MM(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuManufacturing_DD(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuManufacturing_YYYY(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuProgramming_MM(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
   Std_ReturnType tRetVal = E_OK;
   uint8 i;
   for(i = 0; i < 10; i++){
   	aucGlobalDataTemp[i] = 0;
   }
   aucGlobalDataTemp[0] = Data[0] / 10;
   aucGlobalDataTemp[1] = Data[0] % 10;
   return tRetVal;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuProgramming_DD(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
   Std_ReturnType tRetVal = E_OK;
   aucGlobalDataTemp[2] = Data[0] / 10;
   aucGlobalDataTemp[3] = Data[0] % 10;
   return tRetVal;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_DateEcuProgramming_YYYY(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
   Std_ReturnType tRetVal = E_OK;
   aucGlobalDataTemp[4] = Data[1] / 10;
   aucGlobalDataTemp[5] = Data[1] % 10;
   (void)FEEFBL_PutProgrammingDate(aucGlobalDataTemp, 0);
   return tRetVal;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_NumEcuSerial_Supplier1(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
   *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
   return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_NumHw_Supplier1(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_NumHwVersionSys_Supplier1(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType SwcApplDcm_FuncDidWrite_IdSupplierSys(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Vin_UserSpecificCheck(
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8,
   VAR(uint16, AUTOMATIC) did_u16,
   VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){
   Std_ReturnType result = E_OK;
   return result;
}

Std_ReturnType SwcApplDcm_FuncDidWrite_NumIdVehicle(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  PRODFLASH_PutVin(Data);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Programming_Date_UserSpecificCheck(
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8,
   VAR(uint16, AUTOMATIC) did_u16,
   VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){
   Std_ReturnType result = E_OK;
   boolean bIsInitialized = TRUE;
   if(bIsInitialized == FALSE){
   	result = E_NOT_OK;
   	*Nrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
   return result;
}

Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_FL(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID1, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}
Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_FR(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID2, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}
Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_RL(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID3, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}
Std_ReturnType SwcApplDcm_FuncDidWrite_IdSensor_RR(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID4, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}

Std_ReturnType SwcApplDcm_FuncDidWrite_TicksAbsAxle_Front(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 i;
   for(i = 0; i < 10; i++){
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_TicksAbsAxle_Rear(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  aucGlobalDataTemp[1] = Data[0];
  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_ABS_TICKS, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}
Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelAutolearnClearScaleZom(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 i;
   for(i = 0; i < 10; i++){
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelAutolearnErRssiLvl_Min(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  aucGlobalDataTemp[1] = Data[0];
  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}
Std_ReturnType SwcApplDcm_FuncDidWrite_LvlNoiseRfOffset_Threshold(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 i;
   for(i = 0; i < 10; i++){
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_LvlNoiseRfOffset_ThresholdInterference(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  aucGlobalDataTemp[1] = Data[0];
  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_NOISE_LEVEL, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}
Std_ReturnType SwcApplDcm_FuncDidWrite_WarningTemperature_Threshold(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_TEMPERATURE_WARNING_THR, &S_DiagData);
   if(*ErrorCode == DCM_E_OK){
    return E_OK;
  }
  else{
    return E_NOT_OK;
  }
}

Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelLegislation(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 i;
   for(i = 0; i < 10; i++){
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelPressurePlacard(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  aucGlobalDataTemp[1] = Data[0];
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelReserved(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  aucGlobalDataTemp[2] = Data[0];
  return E_OK;
}
Std_ReturnType SwcApplDcm_FuncDidWrite_ParamSensorWheelPressureMin(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  aucGlobalDataTemp[3] = Data[0];
  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_SPECIFIC_PARAMETERS, &S_DiagData);
   if(*ErrorCode != 0){
    return E_NOT_OK;
  }
  else{
    return E_OK;
  }
}

Std_ReturnType SwcApplDcm_FuncDidWrite_SecurityKeyEncodedIV(
   const uint8* Data,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
   uint8 aucCipherText[64];
   uint8 aucHmac[32];
   uint8 aucHmacCalculated[32];
   uint8 aucSymmetricKey[kEepSizeSecKey_AES_SYMMETRIC_KEY];
   uint8 i;
   boolean bHmacMatch = TRUE;
   Std_ReturnType retVal = E_OK;
   uint8 ucCheckerByte;
   rba_DiagLib_MemUtils_MemCpy(aucCipherText, Data, sizeof(aucCipherText));
   rba_DiagLib_MemUtils_MemCpy(aucHmac, &Data[sizeof(aucCipherText)], sizeof(aucHmac));
   (void)FEEFBL_GetSymmetricKey(aucSymmetricKey);
   hmac_sha256((const uint8*)aucSymmetricKey, sizeof(aucSymmetricKey), (const uint8*)aucCipherText, sizeof(aucCipherText), aucHmacCalculated, sizeof(aucHmacCalculated));
   for(i = 0; i < sizeof(aucHmac); i++){
      if(aucHmacCalculated[i] != aucHmac[i]){
   		bHmacMatch = FALSE;
   		*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
   		retVal = E_NOT_OK;

   	}
   }
   if(bHmacMatch == TRUE){
   	DecryptAes256CbcMessage(aucCipherText, sizeof(aucCipherText));
   	(void)FEEFBL_PutAesSymmetricKey((const uint8*)aucCipherText);
   	(void)FEEFBL_PutAesInitialVector((const uint8*)&aucCipherText[sizeof(aucSymmetricKey)]);
   	(void)PRODFLASH_GetEolCheckerByte(&ucCheckerByte);
      if(ucCheckerByte == cPART_HAD_FIRST_STARTUP){
   		ucCheckerByte = cPART_PASSED_LMC_EOL;
   		PRODFLASH_PutEolCheckerByte((const uint8*)&ucCheckerByte);
   	}
   	DemMGR_CheckModuleProvisioning();
   	*ErrorCode = DCM_E_OK;
   }
   return retVal;
}

Std_ReturnType DcmAppl_RequestSeedLevel3ModeRuleCheck(
   Dcm_NegativeResponseCodeType* Nrc_u8,
   uint8 Sid_u8,
   uint8 Subfunc_u8){
  *Nrc_u8 = DCM_E_OK;
  return E_OK;
}

Std_ReturnType SecaFBL_GetSeed(Dcm_SecLevelType SecLevel_u8
   ,  uint32 Seedlen_u32
   ,  uint32 AccDataRecsize_u32
   ,  uint8 * SecurityAccessDataRecord
   ,  uint8 * Seed
   ,  Dcm_OpStatusType OpStatus
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
   uint8 ucAttempts = 3;
   Std_ReturnType tRetVal = DCM_E_OK;

   do{
   	CalculateSeed(Seed);
   	ucAttempts--;
   }while((DcmAppl_DcmCheckSeed(Seedlen_u32, Seed) == DCM_E_SEED_NOK) && (ucAttempts > 0));

   *ErrorCode = DcmAppl_DcmCheckSeed(Seedlen_u32, Seed);
   if(*ErrorCode == DCM_E_OK){
   	ComputeKeyFromSeed(SECA_LEVEL_PROGRAMMING);
   	tRetVal = DCM_E_OK;
   }
   else{
   	tRetVal = DCM_E_REQUESTOUTOFRANGE;
   }
   return tRetVal;
}

Std_ReturnType SecaDATA_GetSeed(Dcm_SecLevelType SecLevel_u8
   ,  uint32 Seedlen_u32
   ,  uint32 AccDataRecsize_u32
   ,  uint8 * SecurityAccessDataRecord
   ,  uint8 * Seed
   ,  Dcm_OpStatusType OpStatus
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){

  uint8 ucAttempts = 3;
  Std_ReturnType tRetVal = DCM_E_OK;

   if(sizeof(aucSecurityKeyApplication) != (uint16)Dcm_Dsp_Security[0].Key_size_u32){
    tRetVal = DCM_E_REQUESTOUTOFRANGE;
  }
  else{
      do{
      CalculateSeed(Seed);
      ucAttempts--;
   }
   while((DcmAppl_DcmCheckSeed(Seedlen_u32, Seed) == DCM_E_SEED_NOK) && (ucAttempts > 0));
    *ErrorCode = DcmAppl_DcmCheckSeed(Seedlen_u32, Seed);
      if(*ErrorCode == DCM_E_OK){
      ComputeKeyFromSeed(SECA_LEVEL_APPLICATION);
      tRetVal = DCM_E_OK;
   }
   else{
      tRetVal = DCM_E_REQUESTOUTOFRANGE;
   }
  }
  return tRetVal;
}

Std_ReturnType SecaDATA_CompareKey(
   uint32 KeyLen_32,
   uint8* Key,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
  uint8 i;
  Std_ReturnType tRetVal = DCM_E_OK;
   if(OpStatus == 0){
      for(i = 0; i < KeyLen_32; i++){
      if((aucSecurityKeyApplication[i] != (uint8)(*(Key+i)))
   	  && (aucSecurityKeyApplication[i] != (uint8)(*(Key + i + 1)))){
        *ErrorCode = DCM_E_INVALIDKEY;
        tRetVal = DCM_E_INVALIDKEY;
      }
   }
  }
  return tRetVal;
}

Std_ReturnType SecaFBL_CompareKey(
   uint32 KeyLen_32,
   uint8* Key,
   Dcm_OpStatusType OpStatus,
   Dcm_NegativeResponseCodeType* ErrorCode){
   uint8 i;
   Std_ReturnType tRetVal = DCM_E_OK;
   if(OpStatus == 0){
      for(i = 0; i < KeyLen_32; i++){
         if(aucSecurityKeyApplication[i] != (uint8)(*(Key + i))){
   			*ErrorCode = DCM_E_INVALIDKEY;
   			tRetVal = DCM_E_INVALIDKEY;
   		}
   	}
   }
   return tRetVal;
}

void ComputeKeyFromSeed(
   uint8 ucSecaLevel){
#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_AES256_CBC)
   struct AES_ctx tAesInput;
   uint8 aucVector[kEepSizeSecKey_AES_INITIAL_VECTOR];
   uint8 aucSymKey[kEepSizeSecKey_AES_SYMMETRIC_KEY];
   if((ucSecaLevel == SECA_LEVEL_APPLICATION) || (ucSecaLevel == SECA_LEVEL_PROGRAMMING)){
   	(void)FEEFBL_GetInitialVector(aucVector);
   	(void)FEEFBL_GetSymmetricKey(aucSymKey);
   }
   else
   {
   }
   if(sizeof(aucSecurityKeyApplication) >= (sizeof(aucCurrentSeed))){
   	rba_DiagLib_MemUtils_MemCpy(aucSecurityKeyApplication, aucCurrentSeed, sizeof(aucCurrentSeed));
   }
   AES_init_ctx_iv(&tAesInput, aucSymKey, aucVector);
   AES_CBC_encrypt_buffer(&tAesInput, aucSecurityKeyApplication, sizeof(aucSecurityKeyApplication));
#endif
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

