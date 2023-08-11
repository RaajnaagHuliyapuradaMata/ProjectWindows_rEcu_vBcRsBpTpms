

#include "DcmAppInterface.h"
#include "DemAppInterfaceX.h"
#include "DemManagerX.h"
#include "version.h"
#include "iTpms_Interface.h"
#include "DcmAppl.h"
#include "rba_DiagLib_MemUtils.h"
#include "Rte_Nvm_Type.h"
#include "SysManagerX.h"
#include "DcmManagerX.h"
#include "FeeFblBlockInterfaceX.h"
#include "ProductionFlashInterfaceX.h"
#include "RdcStandstillX.h"
#include "DcmMsgAuthenticationX.h"

#include "version.h"
#include "crc.h"
#include "hmac_sha2.h"
#include "aes.h"

//#define LMC_SEEDKEY_TEST  //RST Info: test seed/key with test vectors provided by LMC in their security spec

//static uint8 aucSecurityKeyReprogramming[16];
static uint8 aucSecurityKeyApplication[16];
static uint8 aucCurrentSeed[16];

static uint8 aucGlobalDataTemp[10];

static void DecryptAes256CbcMessage(uint8* Message, uint16 ucSizeMessage)
{
  struct AES_ctx tAesInput;
  uint8 aucVector[16];
  uint8 aucSymKey[32];

  (void)FEEFBL_GetInitialVector(aucVector);
  (void)FEEFBL_GetSymmetricKey(aucSymKey);

  AES_init_ctx_iv(&tAesInput, aucSymKey, aucVector);
  AES_CBC_decrypt_buffer(&tAesInput, Message, ucSizeMessage); //decrypted clear text is in Message now
}

static void CalculateSeed(uint8* Seed)
{
  uint8 i; //, j;
  //uint32 ulRandom;
  uint64 ullRandom;
  //uint8 ucRandom[32];

#ifdef LMC_SEEDKEY_TEST
  uint8 aucTestSeed[16] = { 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46 };

  for (i = 0; i < 16; i++)
  {

    Seed[i] = aucTestSeed[i];
  }

#else

  ullRandom = DCMMGR_GetNonceCounter();
  ullRandom = ullRandom*ullRandom; // make it bigger

  for (i=0; i<16; i++)
  {

    Seed[i] = (ullRandom >> i) & 0xff;
  }
#endif

  rba_DiagLib_MemUtils_MemCpy(aucCurrentSeed, (const uint8*)Seed, sizeof(aucCurrentSeed));
}

extern Std_ReturnType DcmDsp_StartSelfTest_Callback(Dcm_OpStatusType OpStatus,
                                                    Dcm_NegativeResponseCodeType * ErrorCode)
{
  DCMMGR_TriggerDiagRoutineSelfCheck(); //RST Info: the self check is not started here, this is done in the next call of DCMMGR_MainFunction
  *ErrorCode = DCM_E_OK;
  return E_OK;
}

extern Std_ReturnType DcmDsp_RequestResultSelfTest_Callback(Dcm_OpStatusType OpStatus,
                                                            Dcm_NegativeResponseCodeType * ErrorCode)
{
  if (DCMMGR_GetDiagRoutineSelfCheckResult() == FALSE)
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    return E_NOT_OK;
  }
  else
  {
    *ErrorCode = DCM_E_OK;
    return E_OK;
  }
}

extern Std_ReturnType DcmDsp_StartVehicleEolTestProcedure_Callback(uint8  dataIn1,
                                                                   Dcm_OpStatusType OpStatus,
                                                                   uint8 * dataOut1,
                                                                   Dcm_NegativeResponseCodeType * ErrorCode)
{
  tsTPMSDiag_Data S_DiagData;
  uint16 ushRespDataLength;
  uint8 ucCounter;

  S_DiagData.pucReqData = &dataIn1;
  S_DiagData.uiReqDataLen = 1;  //1 byte start command
  S_DiagData.puiResDataLen = &ushRespDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_START_TPMS_EOL, &S_DiagData);

  if (*ErrorCode == DCM_E_OK)
  {

    for(ucCounter = 0; ucCounter < (*S_DiagData.puiResDataLen); ucCounter++)
    {
      dataOut1[ucCounter] = S_DiagData.pucResData[ucCounter];
    }
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}

extern Std_ReturnType DcmDsp_RequestResultVehicleEolTestProcedure_Callback( Dcm_OpStatusType OpStatus,
                                                                            uint8 * dataOut1,
                                                                            uint8 * dataOut2,
                                                                            uint8 * dataOut3,
                                                                            uint8 * dataOut4,
                                                                            uint8 * dataOut5,
  Dcm_NegativeResponseCodeType * ErrorCode)
{
  tsTPMSDiag_Data S_DiagData;
  uint16 ushRespDataLength;
  // uint8 ucCheckerByte;

  S_DiagData.pucReqData = (uint8*)NULL;
  S_DiagData.uiReqDataLen = 0;  //routine request result has no data byte
  S_DiagData.puiResDataLen = &ushRespDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_RESULT_TPMS_EOL, &S_DiagData);

  if ((*ErrorCode == DCM_E_OK) && (*S_DiagData.puiResDataLen == 5))
  {

    *dataOut1 = S_DiagData.pucResData[0];
    *dataOut2 = S_DiagData.pucResData[1];
    *dataOut3 = S_DiagData.pucResData[2];
    *dataOut4 = S_DiagData.pucResData[3];
    *dataOut5 = S_DiagData.pucResData[4];

	// KF 29.04.2022 Moved to security-key-exchange function, to fullfill the purpose of "provisioning"

    //if (S_DiagData.pucResData[0] == EOL_ROUT_FINISHED_SUCCESSFULLY)
    //{
    //  PRODFLASH_GetEolCheckerByte(&ucCheckerByte);
    //  if (ucCheckerByte == cPART_HAD_FIRST_STARTUP)
    //  {
    //    ucCheckerByte = cPART_PASSED_LMC_EOL;
    //    PRODFLASH_PutEolCheckerByte((const uint8*)&ucCheckerByte);
    //  }
    //}
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}

extern Std_ReturnType DcmDsp_StopVehicleEolTestProcedure_Callback(uint8  dataIn1,
                                                                  Dcm_OpStatusType OpStatus,
                                                                  uint8 * dataOut1,
                                                                  Dcm_NegativeResponseCodeType * ErrorCode)
{
  tsTPMSDiag_Data S_DiagData;
  uint16 ushRespDataLength;
  uint8 ucCounter;

  S_DiagData.pucReqData = &dataIn1;
  S_DiagData.uiReqDataLen = 1;  //1 byte stop command
  S_DiagData.puiResDataLen = &ushRespDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_STOP_TPMS_EOL, &S_DiagData);

  if (*ErrorCode == DCM_E_OK)
  {

    for(ucCounter = 0; ucCounter < (*S_DiagData.puiResDataLen); ucCounter++)
    {
      dataOut1[ucCounter] = S_DiagData.pucResData[ucCounter];
    }
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}

extern Std_ReturnType DcmDsp_StartResetEepromCallback(const uint8 *  dataIn1,
                                                      Dcm_OpStatusType OpStatus,
                                                      Dcm_NegativeResponseCodeType * ErrorCode)
{
                    //hex: 4D  53  50  50  44  50  32  30  32  30
  uint8 ucPassword[10] = {'M','S','P','P','D','P','2','0','2','0'};
  uint8 i;
  uint8 clearMem[32];
  Std_ReturnType RetVal = E_OK;

  for (i=0; i<8; i++)
  {
    if (dataIn1[i] != ucPassword[i])
    {
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
      RetVal = E_NOT_OK;
    }
  }

  if (RetVal == E_OK)
  {
    *ErrorCode = DCM_E_OK;
    for (i=0; i<sizeof(clearMem); i++)
    {
      clearMem[i] = 0xff;
    }

    #if (SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
    FEEFBL_PutUdsBootKey(clearMem);
    FEEFBL_PutUdsMsgKey(clearMem);
    FEEFBL_PutUdsAppKey(clearMem);

    #elif (SEED_KEY_ALGORITHM==SEED_KEY_USE_AES256_CBC)
    (void)FEEFBL_PutAesInitialVector(clearMem);
    (void)FEEFBL_PutAesSymmetricKey(clearMem);
    #endif

    PRODFLASH_PutVin(clearMem);
    PRODFLASH_PutManufacturingSupportMode(clearMem);

    Memstack_ClearCurrentNvMConsistence();
  }

  return RetVal;
}

Std_ReturnType Active_Diagnostic_Session_Active_Session_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  Dcm_SesCtrlType ActiveSession;
  (void)Dcm_GetSesCtrlType(&ActiveSession);
  *Data = ActiveSession;

  return E_OK;
}

Std_ReturnType Application_Software_Fingerprint_Application_Software_Fingerprint_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{

  (void)FEEFBL_GetFingerprint(Data);

  return E_OK;
}

Std_ReturnType Application_Software_ID_Application_Software_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[8];
  if (VERSION_GetLmcSwVersion(tempData, cSTRING_SIZ_LMCSWV, cMETADATA_APP) == FALSE)
  {
    return E_NOT_OK;
  }
  else
  {
    Data[0] = tempData[0];
	Data[1] = tempData[1];
	Data[2] = tempData[2];
    return E_OK;
  }
}

Std_ReturnType Application_Software_Version_LMC_SW_Version_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[8];
  if (VERSION_GetBhsensSwVersionString(tempData, cSTRING_BHSENS_SW_VERSION_LENGTH, cMETADATA_APP) == FALSE)
  {
    return E_NOT_OK;
  }
  else
  {
	
	//convet to ASCII
    Data[0] = tempData[0]/10 +0x30;
	Data[1] = tempData[0]%10 +0x30;
	Data[2] = tempData[1]/10 +0x30;
	Data[3] = tempData[1]%10 +0x30;
	Data[4] = tempData[3]/10 +0x30;
	Data[5] = tempData[3]%10 +0x30;
    return E_OK;
  }
}

#if 0

FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspData_BootloaderID_ReadFunc(VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) Data)
{
	
	Data[0] = 1U;
	Data += 1;
	if (VERSION_GetEcuProgramInformationPart1(Data, cSTRING_ECU_PROGRAM_INFO_1_LENGTH, cMETADATA_FBL) == FALSE)
	{
		return E_NOT_OK;
	}
	else
	{
		return E_OK;
	}
}
#endif

Std_ReturnType Ecu_Hardware_Number_ECU_Hardware_Number_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
	Data += PRODFLASH_GetCustomerHwPartNumber(Data);
	return E_OK;
}

Std_ReturnType Ecu_Installation_Date_MM_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[6];
  (void)FEEFBL_GetEcuInstallationDate(tempData);
  if ((tempData[0] < 10) && (tempData[1] < 10))
  {
    Data[0] = 10*tempData[0] + tempData[1];
  }
  else
  {
    Data[0] = 0xFF;
  }	
  return E_OK;
}

Std_ReturnType Ecu_Installation_Date_DD_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[6];
  (void)FEEFBL_GetEcuInstallationDate(tempData);
  if ((tempData[2] < 10) && (tempData[3] < 10))
  {
    Data[0] = 10*tempData[2] + tempData[3];
  }
  else
  {
    Data[0] = 0xFF;
  }	
  return E_OK;
}

Std_ReturnType Ecu_Installation_Date_YYYY_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[6];
  (void)FEEFBL_GetEcuInstallationDate(tempData);
  if ((tempData[4] < 10) && (tempData[5] < 10))
  {
	Data[0] = 0x20;
    Data[1] = 10*tempData[4] + tempData[5];	
  }
  else
  {
    Data[0] = 0xFF;
	Data[1] = 0xFF;	
  }	
  return E_OK;
}

Std_ReturnType Ecu_Manufacturing_Date_MM_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[6];
  (void)PRODFLASH_GetBhsensProductionDate(tempData);
  // convert from ascii to bcm
  if ((tempData[2] >= 0x30) && (tempData[2] <= 0x39) && (tempData[3] >= 0x30) && (tempData[3] <= 0x39))
  {
  Data[0] = 16*(tempData[2]-0x30) + (tempData[3]-0x30);
  }
  else
  {
    Data[0] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType Ecu_Manufacturing_Date_DD_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[6];
  (void)PRODFLASH_GetBhsensProductionDate(tempData);
  // convert from ascii to bcm
  if ((tempData[4] >= 0x30) && (tempData[4] <= 0x39) && (tempData[5] >= 0x30) && (tempData[5] <= 0x39))
  {
  Data[0] = 16*(tempData[4]-0x30) + (tempData[5]-0x30);
  }
  else
  {
    Data[0] = 0xFF;
  }
  return E_OK;
}

Std_ReturnType Ecu_Manufacturing_Date_YYYY_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 tempData[6];
  (void)PRODFLASH_GetBhsensProductionDate(tempData);
  // convert from ascii to bcm
  if ((tempData[0] >= 0x30) && (tempData[0] <= 0x39) && (tempData[1] >= 0x30) && (tempData[1] <= 0x39))
  {
	Data[0] = 0x20;
    Data[1] = 16*(tempData[0]-0x30) + (tempData[1]-0x30);
  }
  else
  {
    Data[0] = 0xFF;
	Data[1] = 0xFF;	
  }
  return E_OK;
}

Std_ReturnType Ecu_Programming_Date_MM_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
	uint8 tempData[6];

	(void)FEEFBL_GetProgrammingDate(tempData, cMETADATA_APP);

	if ((tempData[0] < 10) && (tempData[1] < 10))
	{
		Data[0] = 10 * tempData[0] + tempData[1];
	}
	else
	{
		Data[0] = 0xFF;
	}
	
	return E_OK;
}

Std_ReturnType Ecu_Programming_Date_DD_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
	uint8 tempData[6];

	(void)FEEFBL_GetProgrammingDate(tempData, cMETADATA_APP);

	if ((tempData[2] < 10) && (tempData[3] < 10))
	{
		Data[0] = 10 * tempData[2] + tempData[3];
	}
	else
	{
		Data[0] = 0xFF;
	}
	
	return E_OK;
}

Std_ReturnType Ecu_Programming_Date_YYYY_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
	uint8 tempData[6];

	(void)FEEFBL_GetProgrammingDate(tempData, cMETADATA_APP);

	if ((tempData[4] < 10) && (tempData[5] < 10))
	{
		Data[0] = 0x20;
		Data[1] = 10 * tempData[4] + tempData[5];
	}
	else
	{
		Data[0] = 0xFF;
		Data[1] = 0xFF;
	}
	
	return E_OK;
}

Std_ReturnType Ecu_Serial_Number_BHSENS_SerialNumber_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)PRODFLASH_GetCustomerEcuSerialNumber(Data);
  return E_OK;
}

Std_ReturnType System_Supplier_Hardware_Number_Supplier_Hardware_Number_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)PRODFLASH_GetBhsensHardwareNumber(Data);
  return E_OK;
}

Std_ReturnType System_Supplier_Hardware_Version_Number_Hardware_Version_Number_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 ucHwVersion[3];
  uint8 ucCalWeek;
  uint8 ucMonth;

  (void)PRODFLASH_GetBhsensHwVersionInfo(ucHwVersion);

  ucCalWeek = ucHwVersion[1] - 1;
  ucMonth = (ucCalWeek / 4) + 1;
  if (ucMonth > 12)
  {
    ucMonth = 12;
  }

  Data[0] = ucHwVersion[0];
  Data[1] = ucMonth;
  Data[2] = 1;

  return E_OK;
}

Std_ReturnType System_Supplier_Identifier_Supplier_Identifier_43_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  Data[0] = 'B';
  Data[1] = 'H';
  Data[2] = 'S';
  Data[3] = 'E';
  Data[4] = 'N';
  Data[5] = 'S';
  return E_OK;
}

Std_ReturnType Vehicle_Identification_VIN_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
	//uint8 i;
	//uint8 ucBuffer[20];
	//uint8 ucSize;
	//boolean bIsInitialized;

	(void)PRODFLASH_GetVin(Data);

	

	//ucSize = PRODFLASH_GetVin(ucBuffer);
	//bIsInitialized = DCM_IsMemoryInitialized(ucBuffer, ucSize);

	//if (bIsInitialized == FALSE)
	//{
	//	for (i = 0; i < 17; i++)
	//	{
	//		Data[i] = 0;
	//	}
	//}
	//else
	//{
	//	for (i = 0; i < 17; i++)
	//	{
	//		Data[i] = 0x00u;
	//	}
	//}

  return E_OK;
}

Std_ReturnType FL_sensor_ID_FL_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_FL, &S_DiagData);

  for (U8_Counter = 0; U8_Counter < 4U; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType FR_sensor_ID_FR_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_FR, &S_DiagData);

  for (U8_Counter = 0; U8_Counter < 4U; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType RL_sensor_ID_RL_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_RL, &S_DiagData);

  for (U8_Counter = 0; U8_Counter < 4U; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType RR_sensor_ID_RR_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ID_RR, &S_DiagData);

  for (U8_Counter = 0; U8_Counter < 4U; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Front_Axle_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ABS_TICKS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[0];
  //}

  return E_OK;
}

Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Rear_Axle_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_ABS_TICKS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[1];
  //}

  return E_OK;
}

Std_ReturnType TPMS_Auto_Learn_WS_parameters_Clear_ZOM_Scaling_Factor_Value_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[0];
  //}

  return E_OK;
}

Std_ReturnType TPMS_Auto_Learn_WS_parameters_Set_Min_ER_RSSI_Level_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[1];
  //}

  return E_OK;
}

Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_Level_Offset_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_NOISE_LEVEL, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[0];
  //}

  return E_OK;
}

Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_level_threshold_for_RF_interference_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_NOISE_LEVEL, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[1];
  //}

  return E_OK;
}

Std_ReturnType TPMS_Temperature_Warning_Threshold_Temperature_Threshold_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_TEMPERATURE_WARNING_THR, &S_DiagData);

  for (U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType Wheel_Sensor_Parameter_Legislation_Market_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[0];
  //}

  return E_OK;
}

Std_ReturnType Wheel_Sensor_Parameter_Pressure_Placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[1];
  //}

  return E_OK;
}

Std_ReturnType Wheel_Sensor_Parameter_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[2];
  //}

  return E_OK;
}

Std_ReturnType Wheel_Sensor_Parameter_Pressure_Minimum_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
  //{
  Data[0] = S_DiagData.pucResData[3];
  //}

  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);

  for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[4];
  //}

  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[5];
  //}

  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[6];
  //}

  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_LAST_RECEIVED_WS, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[7];
  //}

  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  Data[0] = 0xFF; //Todo GL
  return E_OK;
}

Std_ReturnType Last_received_wheel_sensor_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  Data[0] = 0xFF; //Todo GL
  return E_OK;
}

Std_ReturnType TPMS_Rx_Time_Stamp_Rx_time_stamp_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  return E_OK;
}

Std_ReturnType TPMS_Rx_Time_Stamp_Wheel_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  return E_OK;
}

Std_ReturnType TPMS_Rx_Time_Stamp_RSSI_Level_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  return E_OK;
}

Std_ReturnType TPMS_Rx_Time_Stamp_Noise_RSSI_Level_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  return E_OK;
}

// N/a for LMC

//Std_ReturnType TPMS_Temperature_Warning_Threshold_Temperature_Threshold_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
//{
//  uint8 U8_Counter;
//  tsTPMSDiag_Data S_DiagData;
//
//  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_TEMPERATURE_WARNING_THR, &S_DiagData);
//
//  for(U8_Counter = 0; U8_Counter < (*S_DiagData.puiResDataLen); U8_Counter++)
//  {
//    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
//  }
//
//  return E_OK;
//}

Std_ReturnType Wheel_sensor_number_01_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_01_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[4];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_01_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[5];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_01_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[6];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_01_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[7];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_01_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[8];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_01_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID1, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[9];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[4];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[5];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[6];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[7];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[8];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_02_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID2, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[9];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[4];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[5];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[6];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[7];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[8];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_03_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID3, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[9];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_Wheel_sensor_ID_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  uint8 U8_Counter;
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  {
    Data[U8_Counter] = S_DiagData.pucResData[U8_Counter];
  }

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_Position_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[4];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[5];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_Last_Received_Pressure_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[6];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_Temperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[7];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_P_placard_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[8];
  //}

  return E_OK;
}

Std_ReturnType Wheel_sensor_number_04_Sensor_life_time_counter_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  tsTPMSDiag_Data S_DiagData;

  (void) HufIf_DiagReqCallback(E_TPMS_DIAG_READ_WS_ID4, &S_DiagData);

  //for(U8_Counter = 0; U8_Counter < 4; U8_Counter++)
  //{
    Data[0] = S_DiagData.pucResData[9];
  //}

  return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Bootloader_ID_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en)
{
	Std_ReturnType result;
	result = E_OK;

	

	
	if (dataDirection_en == DCM_SUPPORT_WRITE)
	{
		result = E_NOT_OK;
		*Nrc_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
	}

	return result;
}

Std_ReturnType DtcEnvData_B001_BatteryVoltage_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_LVBatteryVoltage(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B002_VehicleSpeed_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_VehicleSpeed(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B003_AmbientTemperature_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_AmbientTemperature(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B004_Reserved_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_Reserved(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B005_OccurenceDate_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_OccDate(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B006_OccurenceTime_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_OccTime(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B007_TirePressures_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_TirePressures(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B008_TireTemperatures_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_TireTemperatures(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_B009_EcuModesAndStatus_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_EcuMode_LLStatus(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_F103_VehiclePowerMode_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
 (void) Dem_GetData_VehicleMode(Data);
  return E_OK;
}
Std_ReturnType DtcEnvData_F104_Mileage_ReadFunc(Dcm_OpStatusType OpStatus, uint8 * Data)
{
  (void)Dem_GetData_Mileage(Data);
  return E_OK;
}

Std_ReturnType Active_Diagnostic_Session_Active_Session_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Application_Software_Fingerprint_Application_Software_Fingerprint_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
	
	(void)FEEFBL_PutFingerprint(Data);

	return E_OK;
}
Std_ReturnType Application_Software_ID_Application_Software_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Application_Software_Version_LMC_SW_Version_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Ecu_Hardware_Number_ECU_Hardware_Number_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Ecu_Installation_Date_MM_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint8 i;
  for( i =0; i<10; i++)
  {
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0]/10;
  aucGlobalDataTemp[1] = Data[0]%10;
  return E_OK;
}
Std_ReturnType Ecu_Installation_Date_DD_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  aucGlobalDataTemp[2] = Data[0]/10;
  aucGlobalDataTemp[3] = Data[0]%10;
  return E_OK;
}
Std_ReturnType Ecu_Installation_Date_YYYY_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  aucGlobalDataTemp[4] = Data[1]/10;
  aucGlobalDataTemp[5] = Data[1]%10;
  (void)FEEFBL_PutEcuInstallationDate(aucGlobalDataTemp);
  return E_OK;
}
Std_ReturnType Ecu_Manufacturing_Date_MM_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Ecu_Manufacturing_Date_DD_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Ecu_Manufacturing_Date_YYYY_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType Ecu_Programming_Date_MM_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
	Std_ReturnType tRetVal = E_OK;

	uint8 i;
	for (i = 0; i < 10; i++)
	{
		aucGlobalDataTemp[i] = 0;
	}
	aucGlobalDataTemp[0] = Data[0] / 10;
	aucGlobalDataTemp[1] = Data[0] % 10;

	return tRetVal;
}
Std_ReturnType Ecu_Programming_Date_DD_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
	Std_ReturnType tRetVal = E_OK;

	aucGlobalDataTemp[2] = Data[0] / 10;
	aucGlobalDataTemp[3] = Data[0] % 10;

	return tRetVal;
}
Std_ReturnType Ecu_Programming_Date_YYYY_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
	Std_ReturnType tRetVal = E_OK;

	aucGlobalDataTemp[4] = Data[1] / 10;
	aucGlobalDataTemp[5] = Data[1] % 10;
	(void)FEEFBL_PutProgrammingDate(aucGlobalDataTemp, 0);

	return tRetVal;
}
Std_ReturnType Ecu_Serial_Number_BHSENS_SerialNumber_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
	*ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
	return E_NOT_OK;  // not used
  // FEEFBL_PutTesterSerialNumber(Data, 0);
  // PRODFLASH_PutCustomerEcuSerialNumber(Data);
}
Std_ReturnType System_Supplier_Hardware_Number_Supplier_Hardware_Number_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType System_Supplier_Hardware_Version_Number_Hardware_Version_Number_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}
Std_ReturnType System_Supplier_Identifier_Supplier_Identifier_43_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  return E_NOT_OK;  // not used
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Vin_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en)
{
	Std_ReturnType result = E_OK;
	// uint8 ucBuffer[20];
	// uint8 ucSize;
	// boolean bIsInitialized;

	
    #if 0
	
	ucSize = PRODFLASH_GetVin(ucBuffer);
	bIsInitialized = DCM_IsMemoryInitialized(ucBuffer, ucSize);

	if (((dataDirection_en == DCM_SUPPORT_READ) && (bIsInitialized == TRUE))
	    || ((dataDirection_en == DCM_SUPPORT_WRITE) && (bIsInitialized == FALSE)))
	//if (FALSE)
	{
		result = E_NOT_OK;
		*Nrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
	}
    #endif
	return result;
}

Std_ReturnType Vehicle_Identification_VIN_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  PRODFLASH_PutVin(Data);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Programming_Date_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16, VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en)
{
	Std_ReturnType result = E_OK;
	//uint8 ucBuffer[6];
	//uint8 ucSize;
	boolean bIsInitialized = TRUE;

	
	//ucSize = FEEFBL_GetProgrammingDate(ucBuffer, cMETADATA_APP);
	//bIsInitialized = DCM_IsMemoryInitialized(ucBuffer, ucSize);

	//if (((dataDirection_en == DCM_SUPPORT_READ) && (bIsInitialized == TRUE))
	   // || ((dataDirection_en == DCM_SUPPORT_WRITE) && (bIsInitialized == FALSE)))
	if (bIsInitialized == FALSE)
	{
		result = E_NOT_OK;
		*Nrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
	}
	return result;
}

Std_ReturnType FL_sensor_ID_FL_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID1, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}
Std_ReturnType FR_sensor_ID_FR_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID2, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}
Std_ReturnType RL_sensor_ID_RL_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID3, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}
Std_ReturnType RR_sensor_ID_RR_sensor_ID_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_WS_ID4, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}

Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Front_Axle_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint8 i;

  for( i =0; i<10; i++)
  {
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType TPMS_ABS_Ticks_ABS_Ticks_Rear_Axle_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  aucGlobalDataTemp[1] = Data[0];

  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_ABS_TICKS, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}
Std_ReturnType TPMS_Auto_Learn_WS_parameters_Clear_ZOM_Scaling_Factor_Value_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint8 i;
  for( i =0; i<10; i++)
  {
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType TPMS_Auto_Learn_WS_parameters_Set_Min_ER_RSSI_Level_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  aucGlobalDataTemp[1] = Data[0];

  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_AUTO_LEARN_WS_PARAMETERS, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}
Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_Level_Offset_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint8 i;

  for(i =0; i<10; i++)
  {
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType TPMS_RF_Noise_Level_Threshold_Noise_level_threshold_for_RF_interference_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  aucGlobalDataTemp[1] = Data[0];

  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_NOISE_LEVEL, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}
Std_ReturnType TPMS_Temperature_Warning_Threshold_Temperature_Threshold_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  S_DiagData.pucReqData = (uint8 *)&Data[0];
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_TEMPERATURE_WARNING_THR, &S_DiagData);
  if (*ErrorCode == DCM_E_OK)
  {
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}

Std_ReturnType Wheel_Sensor_Parameter_Legislation_Market_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint8 i;
  for(i =0; i<10; i++)
  {
    aucGlobalDataTemp[i]=0;
  }
  aucGlobalDataTemp[0] = Data[0];
  return E_OK;
}
Std_ReturnType Wheel_Sensor_Parameter_Pressure_Placard_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  aucGlobalDataTemp[1] = Data[0];
  return E_OK;
}
Std_ReturnType Wheel_Sensor_Parameter_Reserved_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  aucGlobalDataTemp[2] = Data[0];
  return E_OK;
}
Std_ReturnType Wheel_Sensor_Parameter_Pressure_Minimum_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint16 U16_ResponseDataLength;
  tsTPMSDiag_Data S_DiagData;

  aucGlobalDataTemp[3] = Data[0];

  S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
  S_DiagData.puiResDataLen = &U16_ResponseDataLength;

  *ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_SPECIFIC_PARAMETERS, &S_DiagData);
  if (*ErrorCode != 0)
  {
    return E_NOT_OK;
  }
  else
  {
    return E_OK;
  }
}

Std_ReturnType Security_key_Encoded_IV_and_key_WriteFunc(const uint8 * Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
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

	
	for (i = 0; i < sizeof(aucHmac); i++)
	{
		if (aucHmacCalculated[i] != aucHmac[i])
		{
			bHmacMatch = FALSE;
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			retVal = E_NOT_OK;
			
		}
	}

	if (bHmacMatch == TRUE)
	{
		
		DecryptAes256CbcMessage(aucCipherText, sizeof(aucCipherText));
		
		
		(void)FEEFBL_PutAesSymmetricKey((const uint8*)aucCipherText);
		(void)FEEFBL_PutAesInitialVector((const uint8*)&aucCipherText[sizeof(aucSymmetricKey)]);

		
		(void)PRODFLASH_GetEolCheckerByte(&ucCheckerByte);
		if (ucCheckerByte == cPART_HAD_FIRST_STARTUP)
		{
			ucCheckerByte = cPART_PASSED_LMC_EOL;
			PRODFLASH_PutEolCheckerByte((const uint8*)&ucCheckerByte);
		}

		
		DemMGR_CheckModuleProvisioning();

		*ErrorCode = DCM_E_OK;
	}

	return retVal;
}

Std_ReturnType DcmAppl_RequestSeedLevel3ModeRuleCheck(Dcm_NegativeResponseCodeType * Nrc_u8, uint8 Sid_u8, uint8 Subfunc_u8)
{
  *Nrc_u8 = DCM_E_OK;
  return E_OK;
}

// FUNC(Std_ReturnType, DCM_APPL_CODE) SecaFBL_GetSeed(VAR(Dcm_SecLevelType, AUTOMATIC) SecLevel_u8, VAR(uint32, AUTOMATIC) Seedlen_u32, VAR(uint32, AUTOMATIC) AccDataRecsize_u32, P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) SecurityAccessDataRecord, P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) Seed, VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) ErrorCode)
Std_ReturnType SecaFBL_GetSeed(Dcm_SecLevelType SecLevel_u8,
	uint32 Seedlen_u32,
	uint32 AccDataRecsize_u32,
	uint8 * SecurityAccessDataRecord,
	uint8 * Seed,
	Dcm_OpStatusType OpStatus,
	Dcm_NegativeResponseCodeType * ErrorCode)
{
	uint8 ucAttempts = 3;
	// uint16 ushSizeOfKey = (uint16)Dcm_Dsp_Security[0].Key_size_u32;
	Std_ReturnType tRetVal = DCM_E_OK;

	
	do
	{
		CalculateSeed(Seed);
		ucAttempts--;
	} while ((DcmAppl_DcmCheckSeed(Seedlen_u32, Seed) == DCM_E_SEED_NOK) && (ucAttempts > 0));

	
	*ErrorCode = DcmAppl_DcmCheckSeed(Seedlen_u32, Seed);
	if (*ErrorCode == DCM_E_OK)
	{
		
		// ComputeKeyFromSeed(SECA_LEVEL_PROGRAMMING, Seed, (uint16)Seedlen_u32, aucSecurityKeyReprogramming, ushSizeOfKey, &ushSizeOfKey);
		ComputeKeyFromSeed(SECA_LEVEL_PROGRAMMING);
		tRetVal = DCM_E_OK;
	}
	else
	{
		
		tRetVal = DCM_E_REQUESTOUTOFRANGE;
	}

	return tRetVal;
}

Std_ReturnType SecaDATA_GetSeed(Dcm_SecLevelType SecLevel_u8,
  uint32 Seedlen_u32,
  uint32 AccDataRecsize_u32,
  uint8 * SecurityAccessDataRecord,
  uint8 * Seed,
  Dcm_OpStatusType OpStatus,
  Dcm_NegativeResponseCodeType * ErrorCode)
{

  uint8 ucAttempts = 3;
  //uint16 ushSizeOfKey;
  Std_ReturnType tRetVal = DCM_E_OK;

  if (sizeof (aucSecurityKeyApplication) != (uint16)Dcm_Dsp_Security[0].Key_size_u32)
  {
    tRetVal = DCM_E_REQUESTOUTOFRANGE;
  }

  else
  {

    do
    {
      CalculateSeed(Seed);
      ucAttempts--;
    }
    while ((DcmAppl_DcmCheckSeed(Seedlen_u32, Seed) == DCM_E_SEED_NOK) && (ucAttempts > 0));

    *ErrorCode = DcmAppl_DcmCheckSeed(Seedlen_u32, Seed);
    if (*ErrorCode == DCM_E_OK)
    {

      //ComputeKeyFromSeed(SECA_LEVEL_APPLICATION, Seed, (uint16)Seedlen_u32, aucSecurityKeyApplication, sizeof(aucSecurityKeyApplication), &ushSizeOfKey);
      ComputeKeyFromSeed(SECA_LEVEL_APPLICATION);
      tRetVal = DCM_E_OK;
    }
    else
    {

      tRetVal = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  return tRetVal;
}

Std_ReturnType SecaDATA_CompareKey(uint32 KeyLen_32, uint8 * Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
  uint8 i;
  Std_ReturnType tRetVal = DCM_E_OK;

  if (OpStatus == 0)
  {
    for (i=0; i<KeyLen_32; i++)
    {
      if ((aucSecurityKeyApplication[i] != (uint8)(*(Key+i)))
		  && (aucSecurityKeyApplication[i] != (uint8)(*(Key + i + 1))))
      {
        *ErrorCode = DCM_E_INVALIDKEY;
        tRetVal = DCM_E_INVALIDKEY;
      }
    }
  }

  return tRetVal;
}

Std_ReturnType SecaFBL_CompareKey(uint32 KeyLen_32, uint8 * Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType * ErrorCode)
{
	uint8 i;
	Std_ReturnType tRetVal = DCM_E_OK;

	

	if (OpStatus == 0)
	{
		for (i = 0; i < KeyLen_32; i++)
		{
			if (aucSecurityKeyApplication[i] != (uint8)(*(Key + i)))
			{
				*ErrorCode = DCM_E_INVALIDKEY;
				tRetVal = DCM_E_INVALIDKEY;
			}
		}
	}

	return tRetVal;
}

//static void ComputeKeyFromSeed(uint8 ucSecaLevel, uint8* seed, uint16 sizeSeed, uint8* key, uint16 maxSizeKey, uint16* sizeKey)
void ComputeKeyFromSeed(uint8 ucSecaLevel)
{
  #if (SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
  uint8 aucSecretKey[16];

  if (ucSecaLevel == SECA_LEVEL_APPLICATION)
  {
    FEEFBL_GetUdsAppKey(aucSecretKey);
  }
  else //SECA_LEVEL_REPROGRAMMING
  {
    FEEFBL_GetUdsBootKey(aucSecretKey);
  }

  hmac_sha256(aucSecretKey, maxSizeKey, (const uint8*)seed, sizeSeed, key, maxSizeKey);

  // Report length of calculated key
  *sizeKey= maxSizeKey;

  #elif (SEED_KEY_ALGORITHM==SEED_KEY_USE_AES256_CBC)

	struct AES_ctx tAesInput;
	uint8 aucVector[kEepSizeSecKey_AES_INITIAL_VECTOR];
	uint8 aucSymKey[kEepSizeSecKey_AES_SYMMETRIC_KEY];

	
	if ((ucSecaLevel == SECA_LEVEL_APPLICATION) || (ucSecaLevel == SECA_LEVEL_PROGRAMMING))
	{
		(void)FEEFBL_GetInitialVector(aucVector);
		(void)FEEFBL_GetSymmetricKey(aucSymKey);
	}
	else //
	{
	}

    #if 0
	
	// For backward compatibility to App versions 01.02.05 and 01.02.06:
	// (some 120 ECUs have/would have been installed in vehicles for customers)
	// Uninitialized flash is 0xff, but seems like not always, so let's assume if 24 of the 32 bytes is 0xff, then it is uninitialized

	DCM_MakeBackwardCompartibleToVers010205();

	for (i = 0; i < kEepSizeSecKey_AES_SYMMETRIC_KEY; i++)
	{
		if (aucSymKey[i] == 0xff)
		{
			num_of_0xff++;
		}
	}

	for (i = 0; i < kEepSizeSecKey_AES_INITIAL_VECTOR; i++)
	{
		if (aucVector[i] != aucInitialVector[i])
		{
			bIV_identical = FALSE;
		}
	}
    #endif /* #if 0 */

	
	// AES function replaces the input buffer with encrypted data in the same buffer > copy clear text data to target buffer first
	if (sizeof(aucSecurityKeyApplication) >= (sizeof(aucCurrentSeed)))
	{
		rba_DiagLib_MemUtils_MemCpy(aucSecurityKeyApplication, aucCurrentSeed, sizeof(aucCurrentSeed));
	}
    #if 0
	/* THIS PART OF THE CODE IS NOT BEING USED */
	if ((num_of_0xff > MAX_NUM_OF_FF_ALLOWED_FOR_BACKWARD_COMP) && (bIV_identical))
	{
		AES_init_ctx_iv(&tAesInput, aucSymmetricKey, aucVector); // use the default
	}
	else
	{
		AES_init_ctx_iv(&tAesInput, aucSymKey, aucVector);
	}
    #endif /* #if 0 */
	/* Encrypt the seed with local secret, that's the key */
	AES_init_ctx_iv(&tAesInput, aucSymKey, aucVector);
	AES_CBC_encrypt_buffer(&tAesInput, aucSecurityKeyApplication, sizeof(aucSecurityKeyApplication));

#ifdef LMC_SEEDKEY_TEST
	aucSymKey[0] = SecaDATA_CompareKey(16, aucSecurityKeyApplication, 0, &aucVector);
	//check w debugger if aucSymKey == 0 (ok) or 0x35 (invalid key)
#endif

#endif
}

#if 0

static boolean DCM_IsMemoryInitialized(uint8* ucBuffer, uint8 ucLength)
{
  boolean bResult = TRUE;
  uint8 i;

  for (i=0; i<ucLength; i++)
  {
    if (ucBuffer[i] != 0xff)
    {
      bResult = FALSE;
	  break;
    }
  }
  return bResult;
}
#endif

#if 0

void DCM_MakeBackwardCompartibleToVers010205(void)
{
#define MAX_NUM_OF_FF_ALLOWED_FOR_BACKWARD_COMP 24
	// Default key/vector from Cybersecurity spec 2.1 Chapter 2.1.3.1
	static const uint8 aucSymmetricKey[32] = { 0xf6, 0x81, 0x0c, 0xe9, 0x9f, 0xc6, 0x7d, 0x89,
											   0x0d, 0x97, 0xad, 0xcb, 0x8b, 0x18, 0x7e, 0x81,
											   0xdf, 0x59, 0x06, 0x0d, 0xf4, 0xce, 0x4b, 0xd2,
											   0xf5, 0x61, 0x95, 0x58, 0x7d, 0x49, 0x87, 0x75 };
	static const uint8 aucInitialVector[16] = { 0x48, 0x75, 0x33, 0x57, 0x86, 0x22, 0x47, 0xb1,
											   0x20, 0xed, 0xe3, 0x7e, 0x0e, 0x74, 0x72, 0x6a };
	const uint8 LMC_New_Requested_Pressure_Placard = 0x7C;
	uint8 aucVector[kEepSizeSecKey_AES_INITIAL_VECTOR];
	uint8 aucSymKey[kEepSizeSecKey_AES_SYMMETRIC_KEY];
	uint8 num_of_0xff = 0;
	uint8 i;
	boolean bIV_identical = TRUE;

	// uint16 U16_ResponseDataLength;
	// tsTPMSDiag_Data S_DiagData;
	// Dcm_NegativeResponseCodeType * ErrorCode;

	
	// For backward compatibility to App versions 01.02.05 and 01.02.06:
	// (some 120 ECUs have/would have been installed in vehicles for customers)
	// Uninitialized flash is 0xff, but seems like not always, so let's assume if 24 of the 32 bytes is 0xff, then it is uninitialized
	
	(void)FEEFBL_GetInitialVector(aucVector);
	(void)FEEFBL_GetSymmetricKey(aucSymKey);

	
	for (i = 0; i < kEepSizeSecKey_AES_SYMMETRIC_KEY; i++)
	{
		if (aucSymKey[i] == 0xff)
		{
			num_of_0xff++;
		}
	}

	
	for (i = 0; i < kEepSizeSecKey_AES_INITIAL_VECTOR; i++)
	{
		if (aucVector[i] != aucInitialVector[i])
		{
			bIV_identical = FALSE;
		}
	}

	
	if ((num_of_0xff > MAX_NUM_OF_FF_ALLOWED_FOR_BACKWARD_COMP) && (bIV_identical))
	{
		(void)FEEFBL_PutAesSymmetricKey((const uint8*)aucSymmetricKey);
	}

	
	
	
	 (void)HufIf_DiagReqCallback(E_TPMS_DIAG_READ_SPECIFIC_PARAMETERS, &S_DiagData);
	
	
	 if (((S_DiagData.pucResData[0] == 0x02)
	 	&& (S_DiagData.pucResData[1] == 0x84)
	 	&& (S_DiagData.pucResData[2] == 0x40)
	 	&& (S_DiagData.pucResData[3] == 0x38))
	 	)
	 {
	 	aucGlobalDataTemp[0] = 0x02;
	 	aucGlobalDataTemp[0] = LMC_New_Requested_Pressure_Placard;
	 	aucGlobalDataTemp[0] = 0x40;
	 	aucGlobalDataTemp[0] = 0x38;
	
	 	//S_DiagData.pucResData[0] = 0x02;
	 	//S_DiagData.pucResData[1] = LMC_New_Requested_Pressure_Placard; // 0x7C;
	 	//S_DiagData.pucResData[2] = 0x40;
	 	//S_DiagData.pucResData[3] = 0x38;
	 	S_DiagData.pucReqData = ((uint8 *)&aucGlobalDataTemp[0]);
	 	S_DiagData.puiResDataLen = &U16_ResponseDataLength;
	
	 	*ErrorCode = HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_SPECIFIC_PARAMETERS, &S_DiagData);
	 	
	 }
}
#endif
