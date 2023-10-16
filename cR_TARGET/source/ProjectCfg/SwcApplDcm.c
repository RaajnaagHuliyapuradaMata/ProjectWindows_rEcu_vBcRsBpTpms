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
#include "Std_Types.hpp"

#include "SwcApplDcm.hpp"

#include "SwcApplTpms_Diag.hpp"
#include "Types_CfgSwcServiceStartUp.hpp"
#include "CfgSwcServiceStartUp.hpp"
#include "SwcServiceStartUp.hpp"
#include "iTpms_Interface.hpp"
#include "DcmAppl.hpp"
#include "rba_DiagLib_MemUtils.hpp"
#include "DcmManagerX.hpp"
#include "FeeFblBlockInterfaceX.hpp"
#include "ProductionFlashInterfaceX.hpp"
#include "DcmMsgAuthenticationX.hpp"
#include "LibAutosar_Crc.hpp"
#include "hmac_sha2.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SECA_LEVEL_APPLICATION                                                 3
#define SECA_LEVEL_PROGRAMMING                                                 5

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
static uint8 aucSecurityKeyReprogramming[16];
static uint8 aucSecurityKeyApplication[16];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
static void CalculateSeed(uint8* Seed);
static void ComputeKeyFromSeed(uint8 ucSecaLevel, uint8* seed, uint16 sizeSeed, uint8* key, uint16 maxSizeKey, uint16* sizeKey);
static boolean DCM_IsMemoryInitialized(uint8* ucBuffer, uint8 lu8Length);

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartEcuEolTestProcedure_Callback(
        VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartSelfTest_Callback(
        VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   DCMMGR_TriggerDiagRoutineSelfCheck();
   *ErrorCode = DCM_E_OK;
   return E_OK;
}

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_RequestResultSelfTest_Callback(
        VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   if(FALSE == DCMMGR_GetDiagRoutineSelfCheckResult()){*ErrorCode = DCM_E_CONDITIONSNOTCORRECT; return E_NOT_OK;}
   else                                               {*ErrorCode = DCM_E_OK;                   return E_OK;}
}

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartVehicleEolTestProcedure_Callback(
        VAR(uint8,                        AUTOMATIC               ) dataIn1
   ,    VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut1
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   tsTPMSDiag_Data S_DiagData;
   uint16          ushRespDataLength;
   uint8           ucCounter;
   S_DiagData.pucReqData    = &dataIn1;
   S_DiagData.uiReqDataLen  = 1;
   S_DiagData.puiResDataLen = &ushRespDataLength;
   *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_START_TPMS_EOL, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){
      for(
         ucCounter = 0;
         ucCounter < (*S_DiagData.puiResDataLen);
         ucCounter ++
      ){
         dataOut1[ucCounter] = S_DiagData.pucResData[ucCounter];
      }
      return E_OK;
   }
   else{
      return E_NOT_OK;
   }
}

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_RequestResultVehicleEolTestProcedure_Callback(
        VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut1
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut2
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut3
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut4
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut5
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   tsTPMSDiag_Data S_DiagData;
   uint16          ushRespDataLength;
   S_DiagData.pucReqData    = (uint8*)NULL;
   S_DiagData.uiReqDataLen  = 0;
   S_DiagData.puiResDataLen = &ushRespDataLength;
   *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_RESULT_TPMS_EOL, &S_DiagData);
   if(
         (DCM_E_OK == *ErrorCode)
      && (5 == *S_DiagData.puiResDataLen)
   ){
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

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StopVehicleEolTestProcedure_Callback(
        VAR(uint8,                        AUTOMATIC               ) dataIn1
   ,    VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,  P2VAR(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataOut1
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   tsTPMSDiag_Data S_DiagData;
   uint16          ushRespDataLength;
   uint8           ucCounter;
   S_DiagData.pucReqData    = &dataIn1;
   S_DiagData.uiReqDataLen  = 1;
   S_DiagData.puiResDataLen = &ushRespDataLength;
   *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_STOP_TPMS_EOL, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){
      for(
         ucCounter = 0;
         ucCounter < (*S_DiagData.puiResDataLen);
         ucCounter ++
      ){
      dataOut1[ucCounter] = S_DiagData.pucResData[ucCounter];
      }
      return E_OK;
   }
   else{
      return E_NOT_OK;
   }
}

extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartResetEeprom_Callback(
      P2CONST(uint8,                        AUTOMATIC, DCM_APPL_DATA) dataIn1
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   uint8          ucPassword[10] = {'M','S','P','P','D','P','2','0','2','0'};
   uint8          i;
   uint8          clearMem[20];
   Std_ReturnType RetVal = E_OK;

   for(
      i = 0;
      i < 8;
      i ++
   ){
      if(dataIn1[i] != ucPassword[i]){
         *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
         RetVal     = E_NOT_OK;
      }
   }
   if(E_OK == RetVal){
      for(
         i = 0;
         i < 20;
         i ++
      ){
         clearMem[i] = 0xff;
      }
      FEEFBL_PutUdsBootKey(clearMem);
      FEEFBL_PutUdsMsgKey(clearMem);
      FEEFBL_PutUdsAppKey(clearMem);
      PRODFLASH_PutVin(clearMem);
      PRODFLASH_PutManufacturingSupportMode(clearMem);
   }
   return RetVal;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDsp_StartAuthorizeEcuProgram_Callback(
        VAR(Dcm_OpStatusType,             AUTOMATIC               ) OpStatus
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ApplicationID_ReadFunc(
      VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,          AUTOMATIC, DCM_INTERN_DATA) Data //TBD: use correct naming convention for local variables!
){
   Data[0] = 1U;
   Data += 1;
   if(
         SwcServiceStartUp_u8GetEcuProgramInformationPart1(
               Data
            ,  cSTRING_ECU_PROGRAM_INFO_1_LENGTH
            ,  CfgSwcServiceStartUp_eProgramSw_App
         )
      == FALSE
   ){
      return E_NOT_OK;
   }
   else{
      return E_OK;
   }
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_AppSwFingerprint_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   Data[0] = 1U;
   Data += 1;
   Data += FEEFBL_GetTesterSerialNumber(Data, CfgSwcServiceStartUp_eProgramSw_App);
   Data += FEEFBL_GetProgrammingDate(Data, CfgSwcServiceStartUp_eProgramSw_App);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ApplicationProgramInformation_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data)
{
   Data[0] = 1U;
   Data += 1;
   Data += SwcServiceStartUp_u8GetEcuProgramInformationPart1(Data, cSTRING_ECU_PROGRAM_INFO_1_LENGTH, CfgSwcServiceStartUp_eProgramSw_App);
   Data += SwcServiceStartUp_u8GetEcuProgramInformationPart2(Data, cSTRING_ECU_PROGRAM_INFO_2_LENGTH, CfgSwcServiceStartUp_eProgramSw_App);
   Data += FEEFBL_GetTesterSerialNumber(Data, CfgSwcServiceStartUp_eProgramSw_App);
   Data += FEEFBL_GetProgrammingDate(Data, CfgSwcServiceStartUp_eProgramSw_App);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ApplicationSignature_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetApplicationSignature(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_BootloaderID_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   Data[0] = 1U;
   Data += 1;
   if(
      FALSE == SwcServiceStartUp_u8GetEcuProgramInformationPart1(
            Data
         ,  cSTRING_ECU_PROGRAM_INFO_1_LENGTH
         ,  CfgSwcServiceStartUp_eProgramSw_Fbl
      )
   )    {return E_NOT_OK;}
   else {return E_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_BootSwFingerprint_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   Data[0] = 1U;
   Data += 1;
   Data += FEEFBL_GetTesterSerialNumber(Data, CfgSwcServiceStartUp_eProgramSw_Fbl);
   Data += FEEFBL_GetProgrammingDate(Data, CfgSwcServiceStartUp_eProgramSw_Fbl);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_BootloaderProgramInformation_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   Data[0] = 1U;
   Data += 1;
   Data += SwcServiceStartUp_u8GetEcuProgramInformationPart1(Data, cSTRING_ECU_PROGRAM_INFO_1_LENGTH, CfgSwcServiceStartUp_eProgramSw_Fbl);
   Data += SwcServiceStartUp_u8GetEcuProgramInformationPart2(Data, cSTRING_ECU_PROGRAM_INFO_2_LENGTH, CfgSwcServiceStartUp_eProgramSw_Fbl);
   Data += FEEFBL_GetTesterSerialNumber(Data, CfgSwcServiceStartUp_eProgramSw_Fbl);
   Data += FEEFBL_GetProgrammingDate(Data, CfgSwcServiceStartUp_eProgramSw_Fbl);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_AuxId_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   SwcServiceStartUp_u8GetAuxId(Data, cSTRING_SIZ_AUX_ID, CfgSwcServiceStartUp_eProgramSw_App);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ModeId_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   SwcServiceStartUp_u8GetModeId(Data, cSTRING_SIZ_AUX_ID, CfgSwcServiceStartUp_eProgramSw_App);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ComponentAndSwType_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)SwcServiceStartUp_u8GetComponentAndSwType(Data, cSTRING_SIZ_COMPANDSWTYPE, CfgSwcServiceStartUp_eProgramSw_App);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_FullGenealogyBlock_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   Data += PRODFLASH_GetGenealogyVersion(Data);
   Data += PRODFLASH_GetComponentId(Data);
   Data += PRODFLASH_GetPcbaId(Data);
   Data += PRODFLASH_GetAuxId(Data);
   Data += PRODFLASH_GetModeId(Data);
   Data += PRODFLASH_GetRivianBoardPartNumber(Data);
   Data += PRODFLASH_GetRivianBoardSerialNumber(Data);
   Data += PRODFLASH_GetRivianEcuPartNumber(Data);
   Data += PRODFLASH_GetRivianEcuSerialNumber(Data);
   Data += PRODFLASH_GetApplicationSignature(Data);
   Data += PRODFLASH_GetGenealogyCrc32(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_GenealogyCrc32_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetGenealogyCrc32(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_GenealogyVersionNumber_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   PRODFLASH_GetGenealogyVersion(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ActiveSessionIndicator_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   Dcm_SesCtrlType ActiveSession;
   Dcm_GetSesCtrlType(&ActiveSession);
   *Data = ActiveSession;
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_EcuSerialNumber_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetRivianEcuSerialNumber(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_BoardSerialNumber_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetRivianBoardSerialNumber(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_EcuPartNumber_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetRivianEcuPartNumber(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_BoardPartNumber_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetRivianBoardPartNumber(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_Vin_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetVin(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ManufacturingSupportMode_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   (void)PRODFLASH_GetManufacturingSupportMode(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TpmsAbsTicks_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_ABS_TICKS, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_FLSensorID_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_ID_FL, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < 4U;
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_FRSensorID_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_ID_FR, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < 4U;
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_RLSensorID_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_ID_RL, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < 4U;
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_RRSensorID_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_ID_RR, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < 4U;
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_WheelSensorParameter_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TpmsRxTimeStamp_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TpmsAutoLearnWsParameters_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_NoiseLevelThreshold_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_NOISE_LEVEL, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_WheelSensor01_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_WheelSensor02_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_WheelSensor03_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
   (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_WheelSensor04_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
  (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_LastReceivedWheelSensor_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
  (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_PressureOnKeyConfig_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TemperatureWarningThreshold_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   uint8           U8_Counter;
   tsTPMSDiag_Data S_DiagData;
  (void) infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_READ_TEMPERATURE_WARNING_THR, &S_DiagData);
   for(
      U8_Counter = 0;
      U8_Counter < (*S_DiagData.puiResDataLen);
      U8_Counter ++
   ){
      Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
   }
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_PressureOnKeyStatus_ReadFunc(
        VAR(Dcm_OpStatusType, AUTOMATIC                 ) OpStatus
   ,  P2VAR(uint8,            AUTOMATIC, DCM_INTERN_DATA) Data
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_Vin_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
   PRODFLASH_PutVin(Data);
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TpmsAbsTicks_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
   uint16         U16_ResponseDataLength;
   tsTPMSDiag_Data S_DiagData;
   S_DiagData.pucReqData    = ((uint8*)&Data[0]);
   S_DiagData.puiResDataLen = &U16_ResponseDataLength;
   *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_ABS_TICKS, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_FLSensorID_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_WS_ID1, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_FRSensorID_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_WS_ID2, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_RLSensorID_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_WS_ID3, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_RRSensorID_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_WS_ID4, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_WheelSensorParameter_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_SPECIFIC_PARAMETERS, &S_DiagData);
  if(*ErrorCode != 0){return E_NOT_OK;}
  else               {return E_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TpmsAutoLearnWsParameters_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_NoiseLevelThreshold_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_NOISE_LEVEL, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_PressureOnKeyConfig_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_TemperatureWarningThreshold_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;
  S_DiagData.pucReqData = ((uint8*)&Data[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;
  *ErrorCode = infSwcApplTpmsSwcServiceDcm_u8Callback(E_TPMS_DIAG_WRITE_TEMPERATURE_WARNING_THR, &S_DiagData);
   if(DCM_E_OK == *ErrorCode){return E_OK;}
   else                      {return E_NOT_OK;}
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_ManufacturingSupportMode_WriteFunc(
      P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_DATA) Data
   ,      VAR(Dcm_OpStatusType,             AUTOMATIC                 ) OpStatus
   ,    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) SecaFBL_GetSeed(VAR(Dcm_SecLevelType, AUTOMATIC) SecLevel_u8,VAR(uint32, AUTOMATIC) Seedlen_u32,VAR(uint32, AUTOMATIC) AccDataRecsize_u32,P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) SecurityAccessDataRecord,P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) Seed,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode){
  uint8 ucAttempts = 3;
  uint16 ushSizeOfKey = (uint16)Dcm_Dsp_Security[0].Key_size_u32;
  Std_ReturnType tRetVal = DCM_E_OK;
  do{
   CalculateSeed(Seed);
   ucAttempts--;
  }
  while((DcmAppl_DcmCheckSeed(Seedlen_u32, Seed) == DCM_E_SEED_NOK) && (ucAttempts > 0));
  *ErrorCode = DcmAppl_DcmCheckSeed(Seedlen_u32, Seed);
  if(DCM_E_OK == *ErrorCode){
   ComputeKeyFromSeed(SECA_LEVEL_PROGRAMMING, Seed, (uint16)Seedlen_u32, aucSecurityKeyReprogramming, ushSizeOfKey, &ushSizeOfKey);
    tRetVal = DCM_E_OK;
  }
  else{
    tRetVal = DCM_E_REQUESTOUTOFRANGE;
  }
  return tRetVal;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) SecaDATA_GetSeed(VAR(Dcm_SecLevelType, AUTOMATIC) SecLevel_u8,VAR(uint32, AUTOMATIC) Seedlen_u32,VAR(uint32, AUTOMATIC) AccDataRecsize_u32,P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) SecurityAccessDataRecord,P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) Seed,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode){
  uint8 ucAttempts = 3;
  uint16 ushSizeOfKey = (uint16)Dcm_Dsp_Security[0].Key_size_u32;
  Std_ReturnType tRetVal = DCM_E_OK;
  do{
   CalculateSeed(Seed);
   ucAttempts--;
  }
  while((DcmAppl_DcmCheckSeed(Seedlen_u32, Seed) == DCM_E_SEED_NOK) && (ucAttempts > 0));
  *ErrorCode = DcmAppl_DcmCheckSeed(Seedlen_u32, Seed);
  if(DCM_E_OK == *ErrorCode){
   ComputeKeyFromSeed(SECA_LEVEL_APPLICATION, Seed, (uint16)Seedlen_u32, aucSecurityKeyApplication, ushSizeOfKey, &ushSizeOfKey);
    tRetVal = DCM_E_OK;
  }
  else{
    tRetVal = DCM_E_REQUESTOUTOFRANGE;
  }
  return tRetVal;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) SecaFBL_CompareKey(VAR(uint32, AUTOMATIC) KeyLen_32,P2VAR(uint8, AUTOMATIC,DCM_INTERN_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode){
  uint8 i;
  Std_ReturnType tRetVal = DCM_E_OK;
  if(OpStatus == 0){
   for(i=0; i<KeyLen_32; i++){
      if(aucSecurityKeyReprogramming[i] != (uint8)(*(Key+i)))
      {
        *ErrorCode = DCM_E_INVALIDKEY;
        tRetVal = DCM_E_INVALIDKEY;
      }
   }
  }
  return tRetVal;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) SecaDATA_CompareKey(VAR(uint32, AUTOMATIC) KeyLen_32,P2VAR(uint8, AUTOMATIC,DCM_INTERN_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode){
  uint8 i;
  Std_ReturnType tRetVal = DCM_E_OK;
  if(OpStatus == 0){
   for(i=0; i<KeyLen_32; i++){
      if(aucSecurityKeyApplication[i] != (uint8)(*(Key+i))){
        *ErrorCode = DCM_E_INVALIDKEY;
        tRetVal = DCM_E_INVALIDKEY;
      }
   }
  }
  return tRetVal;
}

static void CalculateSeed(uint8* Seed){
  uint8 i, j;
  uint32 ulRandom;
  uint64 ullRandom;
  uint8 ucRandom[8];
  for(j=0; j<4; j++){
   ullRandom = DCMMGR_GetNonceCounter();
   ullRandom <<= j;
   for(i=0; i<8; i++){
      ucRandom[i] = ullRandom & 0xff;
      ullRandom >>= 8;
   }
   ulRandom = LibAutosarCrc_u32Calculate((const uint8*)ucRandom, 8, 0xffffffff, TRUE);
   for(i=(j*4); i<((j*4)+4); i++){
      Seed[i] = (uint8)(ulRandom & 0xff);
      ulRandom >>= 8;
   }
  }
}

static void ComputeKeyFromSeed(uint8 ucSecaLevel, uint8* seed, uint16 sizeSeed, uint8* key, uint16 maxSizeKey, uint16* sizeKey){
  uint8 aucSecretKey[16];
  if(ucSecaLevel == SECA_LEVEL_APPLICATION){
    FEEFBL_GetUdsAppKey(aucSecretKey);
  }
  else{
    FEEFBL_GetUdsBootKey(aucSecretKey);
  }
  hmac_sha256(aucSecretKey, maxSizeKey, (const uint8*)seed, sizeSeed, key, maxSizeKey);
  *sizeKey= maxSizeKey;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Fbl_ProgM_EraseMemoryCallback_65280(
                         P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) dataIn1
   ,     VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     VAR(uint16, AUTOMATIC) CurrentDataLength
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Fbl_ProgM_VerifyDownloadCallback(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
){
   return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Fbl_Port_DisableRxAndTx(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint8, AUTOMATIC) Sid_u8, VAR(uint8, AUTOMATIC) Subfunc_u8){
   return E_OK;
}

Std_ReturnType DCM_CheckSecurityLevelForReadDids(Dcm_NegativeResponseCodeType *Nrc_u8, Dcm_Direction_t dataDirection_en){
  Dcm_SesCtrlType ActiveSession;
  Dcm_SecLevelType ucCurrentSecurityLevel;
  Std_ReturnType retVal = E_OK;
  if(dataDirection_en == DCM_SUPPORT_READ){
    Dcm_GetSesCtrlType(&ActiveSession);
   if(ActiveSession == EXTENDED_DIAGNOSTIC_SESSION){
      Dcm_GetSecurityLevel(&ucCurrentSecurityLevel);
      if(ucCurrentSecurityLevel != DCM_SEC_LEV_L2){
        *Nrc_u8 = DCM_E_SECURITYACCESSDENIED;
        retVal = E_NOT_OK;
      }
   }
  }
  return retVal;
}

static boolean DCM_IsMemoryInitialized(uint8* ucBuffer, uint8 lu8Length){
  boolean bResult = TRUE;
  uint8 i;
  for(i=0; i<lu8Length; i++){
   if(ucBuffer[i] != 0xff){
      bResult = FALSE;
   }
  }
  return bResult;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadApplicationId_UserSpecificCheck                 (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadAppSwFingerprint_UserSpecificCheck              (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadApplicationProgramInformation_UserSpecificCheck (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBootloaderId_UserSpecificCheck                  (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBootSwFingerprint_UserSpecificCheck             (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBootloaderProgramInformation_UserSpecificCheck  (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadComponentAndSwType_UserSpecificCheck            (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadAuxId_UserSpecificCheck                         (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadModeId_UserSpecificCheck                        (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadGenealogyVersionNumber_UserSpecificCheck        (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadGenealogyCrc32_UserSpecificCheck                (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadFullGenealogyBlock_UserSpecificCheck            (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadApplicationSignature_UserSpecificCheck          (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadEcuSerialNumber_UserSpecificCheck               (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBoardSerialNumber_UserSpecificCheck             (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadEcuPartNumber_UserSpecificCheck                 (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBoardPartNumber_UserSpecificCheck               (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadActiveSessionIndicator_UserSpecificCheck        (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){return DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Vin_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){
  Std_ReturnType result;
  uint8 ucBuffer[20];
  uint8 ucSize;
  boolean bIsInitialized;
  result = DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);
  if(result == E_OK){
   ucSize = PRODFLASH_GetVin(ucBuffer);
   bIsInitialized = DCM_IsMemoryInitialized(ucBuffer, ucSize);
   if(((dataDirection_en == DCM_SUPPORT_READ) && (bIsInitialized == TRUE))
     || ((dataDirection_en == DCM_SUPPORT_WRITE) && (bIsInitialized == FALSE))){
      result = E_NOT_OK;
      *Nrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
   }
  }
  return result;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ManufacturingSupportMode_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en){
  Std_ReturnType result;
  if(dataDirection_en == DCM_SUPPORT_WRITE){
    result = E_NOT_OK;
    *Nrc_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  }
  else{
    result = DCM_CheckSecurityLevelForReadDids(Nrc_u8, dataDirection_en);
  }
  return result;
}

FUNC(void,DCM_CODE) Dcm_Dsp_CCIni(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

