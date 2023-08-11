

#include "EcuDiag.h"
#include "SysManagerX.h"
#include "EnvManagerX.h"
#include "DemManagerX.h"
#include "adcX.h"
#include "ata_rec_X.h"

//static uint8 ushLongTermAvgNoiseLvl;
//static uint8 aucLongTermAvgTelrecLvl[4];
//static uint8 aucLongTermRxRatePosition[4];
//static uint8 aucCurrentDriveRxRatePositoin[4];
//static uint8 aucLastreceivedBattStatus[4];
//static uint16 ushVBatADValue;
//uint8 ucRxRateStatisticUpdated;

static uint32 ulCheckRamAddress;
static uint32 ulRamStartAddress = RAM_START_ADDRESS;

static uint8 *piPDI = (uint8 *)START_FLASHADD4APPL;
static uint16 *piP2ApplChecksum = (uint16 *)CHECKSUMM_ADD_IN_APPL;
static uint8 ucByteCnt4MaxInTask = 0;
static uint16 uiPageCounter = 0;
static uint8 ucApplCheckSumLowByte = 0;
static uint16 uiCheckSum = 0;
static uint16 uiApplCheckSum = 0;

static boolean ECUD_DiagRFRec(void)
{
  static uint8 ucLastDemodLevel = (uint8) 0;
  static uint16 ushDemodSameLevelCt = 0;
  static uint16 ui16RfRecInactiveTime = 0;
  unsigned char ucCurLevl = Env_GetNoiseLevel();
  boolean bErrorActive = FALSE;

  if (ucLastDemodLevel == ucCurLevl)
  {
    if (ushDefDemodSameLevelCtc <= ushDemodSameLevelCt)
    {
      bErrorActive = TRUE;
    }
    else
    {
      ushDemodSameLevelCt++;
    }
  }
  else
  {
    if (ushDefDemodSameLevelCtc <= ushDemodSameLevelCt)
    {
      if ((ushDefDemodSameLevelCtc + ushDefDemodDifLevelGoodCtc) > ushDemodSameLevelCt)
      {
        ushDemodSameLevelCt++;
        bErrorActive = TRUE;
        ushDemodSameLevelCt = 0;
      }
    }
    else
    {
      ushDemodSameLevelCt = 0;
    }
  }
  ucLastDemodLevel = ucCurLevl;

  if (GetAtaState() == cRfdProcess)
  {
    if (ui16MaxRfRecInactiveTimeIn50msec <= ui16RfRecInactiveTime)
    {
      if ((ui16MaxRfRecInactiveTimeIn50msec + ui16RecActiveTimeIn50msec) > ui16RfRecInactiveTime)
      {
        ui16RfRecInactiveTime++;
        bErrorActive = TRUE;
      }
      else
      {
        ui16RfRecInactiveTime = 0;
      }
    }
    else
    {
      ui16RfRecInactiveTime = 0;
    }
  }
  else
  {
    if (ui16MaxRfRecInactiveTimeIn50msec <= ui16RfRecInactiveTime)
    {
      bErrorActive = TRUE;
    }
    else
    {
      ui16RfRecInactiveTime++;
    }
  }

  return bErrorActive;
}

#pragma ghs ZO
static uint32 ECUD_RAMCheckUi32(uint32 ulRamAddress)
{
  uint32 ul32Tmp;
  ul32Tmp = ulRamAddress;

  asm(" di  ");
  asm(" pushsp r20-r23 ");

  asm(" mov r6, r20");

  asm(" ldl.w [r20],r21 ");

  asm(" mov 0x55AA55AA, r23 ");
  asm(" stc.w r23,[r20] ");
  asm(" ldl.w [r20],r22 ");
  asm(" cmp r22,r23 ");
  asm(" bne _RAM_ERROR ");

  asm(" mov 0xAA55AA55, r23 ");
  asm(" stc.w r23,[r20] ");
  asm(" ldl.w [r20],r22 ");
  asm(" cmp r22,r23 ");
  asm(" bne _RAM_ERROR ");
  asm(" br _RAM_CHK_OKAY ");
  asm(" _RAM_ERROR:  ");

  asm(" mov 0x0, r6 ");
  ul32Tmp = 0;
  asm(" br _RAM_CHK_ENDE ");

  asm(" _RAM_CHK_OKAY:  ");
  asm(" stc.w r21,[r20] ");
  asm(" mov 0x0, r20  ");
  asm(" mov 0x0, r21  ");
  asm(" mov 0x0, r22  ");
  asm(" mov 0x0, r23  ");
  asm(" add 4, r6 ");
  ul32Tmp = ul32Tmp + 4;

  asm(" _RAM_CHK_ENDE:  ");
  asm(" popsp r20-r23 ");
  asm(" ei  ");

  return (ul32Tmp);
}

static uint8 ECUD_PerformRomCheck(void)
{
  uint8 ucRetVal = cDiagRunning;

  for (ucByteCnt4MaxInTask = 0; ucByteCnt4MaxInTask < READ_BYTES4CHKInTask; ucByteCnt4MaxInTask++)
  {
    if (piPDI != (uint8 *)END_FLASHADD4APPL)
    {
      uiCheckSum += (uint16)*piPDI;
      piPDI++;
    }
    else
    {
      uiApplCheckSum = (uint16)*piP2ApplChecksum;
      ucApplCheckSumLowByte = ((uint8)((uiApplCheckSum >> 8) & 0x00FF));
      uiApplCheckSum = ((uint16)(uiApplCheckSum << 8));
      uiApplCheckSum = uiApplCheckSum + ((uint16)ucApplCheckSumLowByte);
      ucByteCnt4MaxInTask = READ_BYTES4CHKInTask;

      if (uiApplCheckSum != uiCheckSum)
      {

        ucRetVal = cDiagError;
      }
      else
      {

        ucRetVal = cDiagFinishNoError;
      }
    }
  }

  return (ucRetVal);
}

static uint8 ECUD_PerformRamCheck(void)
{
  uint8 ucRetVal;

  if (ulRamStartAddress != 0x00)
  {
    if (ulRamStartAddress < RAM_END_ADDRESS)
    {
      ulCheckRamAddress = ECUD_RAMCheckUi32(ulRamStartAddress);
      ulRamStartAddress = ulCheckRamAddress;
      ucRetVal = cDiagRunning;
    }
    else
    {
      ucRetVal = cDiagFinishNoError;
    }
  }
  else
  {

    ucRetVal = cDiagError;
  }

  return ucRetVal;
}

void ECUD_SelfDiag(void)
{
  static uint8 ucInternalFaultReason;

  uint8 ui8RAMTestResult;
  uint8 ui8ROMTestResult;
  uint8 ui8ECUFaultChange;
  uint8 ui8Status;
  uint8 ui8Voltage;
  boolean bRfErrorActive;
  tsTPMSDiag_Data tDiagData;

  ui8ECUFaultChange = ucInternalFaultReason;

  if (SYSMGR_GetEcuMode() == cECUMODE_FULL)
  {

    ui8Voltage = ADC_GetKl30Voltage();
    if ((ui8Voltage != ((uint8)0xff)) && (ui8Voltage > cECU_UBAT_MIN) && ((ui8Voltage < cECU_UBAT_MAX)))
    {
      ui8RAMTestResult = ECUD_PerformRamCheck();
      ui8ROMTestResult = ECUD_PerformRomCheck();
      bRfErrorActive = ECUD_DiagRFRec();

      if (cDiagError == ui8RAMTestResult)
      {
        ucInternalFaultReason |= EcuRamTestFailed;
      }

      if (cDiagError == ui8ROMTestResult)
      {
        ucInternalFaultReason |= EcuRomTestFailed;
      }

      if (bRfErrorActive)
      {
        ucInternalFaultReason |= EcuRfReceiverDefect;
      }
      else
      {
        ucInternalFaultReason &= ((uint8)~EcuRfReceiverDefect);
      }

      if (ucInternalFaultReason > ((uint8)0))
      {
        if (ucInternalFaultReason != ui8ECUFaultChange)
        {

          tDiagData.pucReqData = &ucInternalFaultReason;
          tDiagData.uiReqDataLen = (uint8)1;
          //RST 09.02.2021 -> we will never set this DTC because the risk of false alarms is much too high (same as in DAI MFA2)
          //(void)HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_ECU_FAULT_REASON, &tDiagData);
          //Dem_SetEventStatus(DemConf_DemEventParameter_Event_FailedMemory, DEM_EVENT_STATUS_FAILED);
        }
      }
      else
      {

        if (!bRfErrorActive && (cDiagFinishNoError == ui8ROMTestResult) && (cDiagFinishNoError == ui8RAMTestResult))	
        {

          tDiagData.pucReqData = &ucInternalFaultReason;
          tDiagData.uiReqDataLen = (uint8)1;
          //RST 09.02.2021 -> we will never set this DTC because the risk of false alarms is much too high (same as in DAI MFA2)
          //(void)HufIf_DiagReqCallback(E_TPMS_DIAG_WRITE_ECU_FAULT_REASON, &tDiagData);
          //Dem_SetEventStatus(DemConf_DemEventParameter_Event_FailedMemory, DEM_EVENT_STATUS_PASSED);
        }
      }
    }
  }
}

#if 0

void InitLongTermStatData(void)
{
  uint8 ucIx;

  if ( cDefaultLongTermStatDataInitialized != GETushInitialisationValue())
  {
    InitLongTermDataMemory();
  }

    ushLongTermAvgNoiseLvl = GETucStoredLongTermAvgNoiseLvl();

  for (ucIx = 0; ucIx < 4; ucIx++)
  {
    aucLongTermAvgTelrecLvl[ucIx] = GETucStoredLongTermAvgTelRecLvl(ucIx);
  }

  ucRxRateStatisticUpdated = 0;
  for (ucIx = 0; ucIx < 4; ucIx++)
  {
    aucLongTermRxRatePosition[ucIx] = GETucStoredLongTermTelRecRate(ucIx);
    aucCurrentDriveRxRatePositoin[ucIx] = 0;
  }

  for (ucIx = 0; ucIx < 4; ucIx++)
  {
    aucLastreceivedBattStatus[ucIx] = GETucStoredLastRecBattStattus(ucIx);
  }

  ucPutStoredInternalErrorReason(GETucStoredEcuInternalFaultReason());
}

void CalcLongTermAvgNoiseLvl(void)
{
  uint16 ushTempVal;

  ushTempVal = (ushLongTermAvgNoiseLvl * 59 + ucGetRfNoiseLevel()) / 60;
  if (ushTempVal > 0)
  {
    ushLongTermAvgNoiseLvl = ushTempVal;
  }
}

uint16 GETushCurrentLongTermAvgNoiseLvl(void)
{
  return ushLongTermAvgNoiseLvl;
}

void CalcLongTermAvgTelRecLvl(uint8 ucRfRecLvl, uint8 ucPosition)
{
  uint8 ucTempLvl;
  sint8 scSignalToNoiseLvl;

  scSignalToNoiseLvl = ucRfRecLvl - ucGetRfNoiseLevel();
  ucTempLvl = 0;

  if (scSignalToNoiseLvl > 0)
  {
    ucTempLvl = (uint8)((aucLongTermAvgTelrecLvl[ucPosition] * 9 + scSignalToNoiseLvl) / 10);
  }

  if (ucTempLvl > 0)
  {
    aucLongTermAvgTelrecLvl[ucPosition] = ucTempLvl;
  }
}

uint8 GETucCurrentLongTermAvgTelRecLvl(uint8 ucPos)
{
  return aucLongTermAvgTelrecLvl[ucPos];
}

void CalcLongTermPositionRxRate(uint8 ucPosition)
{
  uint8 ucIdx;

  if (aucCurrentDriveRxRatePositoin[ucPosition] < 240)
  {
    aucCurrentDriveRxRatePositoin[ucPosition] += 1;
  }

  if ((GETushTimeCurrentDrive() >= c40MinusDriveTime) && (ucRxRateStatisticUpdated == 0))
  {

    for (ucIdx = 0; ucIdx < 4; ucIdx++)
    {
      aucLongTermRxRatePosition[ucIdx] = (aucLongTermRxRatePosition[ucIdx] * 9 + aucCurrentDriveRxRatePositoin[ucIdx]) / 10;
    }
    ucRxRateStatisticUpdated = 1;
  }
}

uint8 GETucCurrentLongTermTelRxRate(uint8 ucPos)
{
  return aucLongTermRxRatePosition[ucPos];
}

uint8 GETucCurrentDriveTelRxRate(uint8 ucPos)
{
  return aucCurrentDriveRxRatePositoin[ucPos];
}

void StoreLastReceivedBattStatus( uint8 ucPosition, uint8 ucBattStatus)
{
  aucLastreceivedBattStatus[ucPosition] = ucBattStatus;
}

uint8 GETucCurrentLastReceivedBattStatus(uint8 ucPos)
{
  return aucLastreceivedBattStatus[ucPos];
}
#endif
