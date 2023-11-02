#define ABS_LIN_C

#include "Std_Types.hpp"

#include "SwcApplTpms_abs_lin.hpp"
#include "abs_linX.hpp"
#include "wallocX.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

static uint8 ucAbsState;
static tABS_DATA tAbsDataBuff[cAbsBufferSize];
static uint16 ushLinAbsData[4];
static uint8 ucAbsIndex;
static uint8 ucABSIndex1, ucABSIndex2;
static uint8 aucPreviousOverflowCnt[cNUMBER_OF_WHEELS];
static uint8 aucCurrentOverflowCnt[cNUMBER_OF_WHEELS];
uint32 ulDebugAbsTimeDiff = 0;
uint32 ulDebugRfTimeStamp = 0;
uint32 ulDebugRfTimeStampDiff = 0;
uint32 ulDebugAbs2RfTimeDiff = 0;
uint16 ushDebugAbsCntVlDiff = 0;
uint16 ushDebugAbsCntVrDiff = 0;
uint16 ushDebugAbsCntHlDiff = 0;
uint16 ushDebugAbsCntHrDiff = 0;
uint16 ushDebugDivisor = 0;
uint16 ushDebugAbsCntVlLin = 0;
uint16 ushDebugAbsCntVrLin = 0;
uint16 ushDebugAbsCntHlLin = 0;
uint16 ushDebugAbsCntHrLin = 0;
uint8 ucDebugError = 0;

unsigned short ushABSRefOffset[4];
unsigned char ucABSComp[4];

static uint16 ushCalcABS(
   uint32 ulRfTimeStamp,
   uint32 ul1stAbsTimeStamp,
   uint16 ush1stAbsCnt,
   uint32 ul2ndAbsTimeStamp,
   uint16 ush2ndAbsCnt);

static void HandleOverflowABS(
   uint8 ucWheelPosition,
   uint8 ucABSTicksAx);

void InitABS(void)
{
  uint8 ucLoop;
  uint8 ucWheelCounter;
   uint8 j;

   ulDebugAbsTimeDiff     = 0;
   ulDebugRfTimeStamp     = 0;
   ulDebugRfTimeStampDiff = 0;
   ulDebugAbs2RfTimeDiff  = 0;
   ushDebugAbsCntVlDiff    = 0;
   ushDebugAbsCntVrDiff    = 0;
   ushDebugAbsCntHlDiff    = 0;
   ushDebugAbsCntHrDiff    = 0;
   ushDebugDivisor         = 0;
   ushDebugAbsCntVlLin     = 0;
   ushDebugAbsCntVrLin     = 0;
   ushDebugAbsCntHlLin     = 0;
   ushDebugAbsCntHrLin     = 0;
   ucDebugError            = 0;

  for( ucLoop = 0; ucLoop < cAbsBufferSize; ucLoop++ )
  {
    tAbsDataBuff[ucLoop].ulAbsTimeStamp = (uint32) 0;

   for(ucWheelCounter = 0; ucWheelCounter < cNUMBER_OF_WHEELS; ucWheelCounter++)
   {
      tAbsDataBuff[ucLoop].aushAbsCnt[ucWheelCounter] = (uint16) 0;
      tAbsDataBuff[ucLoop].aucOverflowCnt[ucWheelCounter] = (uint8) 0;
   }
  }

  for(ucWheelCounter = 0; ucWheelCounter < cNUMBER_OF_WHEELS; ucWheelCounter++)
  {
    aucPreviousOverflowCnt[ucWheelCounter] = 0;
    aucCurrentOverflowCnt[ucWheelCounter] = 0;
  }

   for(j = 0; j < 4; j++)
   {
      ucABSComp[j] = 0;
      ushABSRefOffset[j] = 0;
   }

  ucAbsState = cABS_STATE_INIT;
  ucAbsIndex = 0;
  ucABSIndex1 = 0;
  ucABSIndex2 = 0;
}

void PutABS( uint32 ulTime, const uint16 ushCnt[] )
{
  uint8 ucAbsIndexPrev;
  uint8 ucWheelCounter;
  if(ucAbsState == cABS_STATE_INIT)
  {
   if(ucAbsIndex < cAbsBufferSize) //out of bounds protection
   {
      tAbsDataBuff[ucAbsIndex].ulAbsTimeStamp = ulTime;
      for(ucWheelCounter = 0; ucWheelCounter < cNUMBER_OF_WHEELS; ucWheelCounter++)
      {
        tAbsDataBuff[ucAbsIndex].aushAbsCnt[ucWheelCounter] = ushCnt[ucWheelCounter];
      }
      ucAbsState = ccABS_STATE_LinABS_ERR;
   }
  }
  else{

      ucAbsIndex %= cAbsBufferSize;
   if(ucAbsIndex == 0)
   {
      ucAbsIndexPrev = cAbsBufferSize - 1;
   }
   else{
      ucAbsIndexPrev = ucAbsIndex - 1;
   }

    tAbsDataBuff[ucAbsIndex].ulAbsTimeStamp = ulTime;

   for(ucWheelCounter = 0; ucWheelCounter < cNUMBER_OF_WHEELS; ucWheelCounter++)
   {
      if(ushCnt[ucWheelCounter] < tAbsDataBuff[ucAbsIndexPrev].aushAbsCnt[ucWheelCounter])
      {
        aucCurrentOverflowCnt[ucWheelCounter]++;
      }

      tAbsDataBuff[ucAbsIndex].aucOverflowCnt[ucWheelCounter] = aucCurrentOverflowCnt[ucWheelCounter];
      tAbsDataBuff[ucAbsIndex].aushAbsCnt[ucWheelCounter] = ushCnt[ucWheelCounter];
   }
  }
  ucAbsIndex++;
}

uint8 GetLinABS( uint16 ushCnt[] )
{
  uint8 ucRet;

  if(ucAbsState == ccABS_STATE_LinABS_AVL)
  {
   ushCnt[0] = ushLinAbsData[0];
   ushCnt[1] = ushLinAbsData[1];
   ushCnt[2] = ushLinAbsData[2];
   ushCnt[3] = ushLinAbsData[3];

   ucRet = cABS_OK;
  }
  else{
   ushCnt[0] = cAbsOverflowValue;
   ushCnt[1] = cAbsOverflowValue;
   ushCnt[2] = cAbsOverflowValue;
   ushCnt[3] = cAbsOverflowValue;
   ucRet = cABS_ERROR;
  }

  return ucRet;
}

uint8 LinABS( uint32 ulRfTimeStamp )
{
  uint8 ucRet = 0xFF;
  uint8 ucLoop;
  uint16 aushDivisor[cNUMBER_OF_WHEELS];
  uint8 ucABSTicksFrontAx = 0xFF;
  uint8 ucABSTicksRearAx = 0xFF;
  uint8 ucRefCorrectionValue = 0;
  uint8 ucWheelCounter;

   ucABSTicksFrontAx = ucGetABSTicksFullRevolFrontAx();
   ucABSTicksRearAx = ucGetABSTicksFullRevolRearAx();

   if( ulDebugRfTimeStamp > ulRfTimeStamp )
   {

      ulDebugRfTimeStampDiff = (0xFFFFFFFFu - ulDebugRfTimeStamp) + ulRfTimeStamp;
   }
   else{
      ulDebugRfTimeStampDiff = ulRfTimeStamp - ulDebugRfTimeStamp;
   }

   ulDebugRfTimeStamp = ulRfTimeStamp;

   ucABSIndex1 = 0xFF;
   ucABSIndex2 = 0xFF;
   for(ucLoop = 0; ucLoop < cAbsBufferSize; ucLoop++)
   {
      if(tAbsDataBuff[ucLoop].ulAbsTimeStamp < ulRfTimeStamp)
      {

        if(ucABSIndex1 == 0xFF)
        {
          ucABSIndex1 = ucLoop;
        }
        else{
            if(tAbsDataBuff[ucLoop].ulAbsTimeStamp >= tAbsDataBuff[ucABSIndex1].ulAbsTimeStamp)
          {
            ucABSIndex1 = ucLoop;
          }
        }
      }
      else if(tAbsDataBuff[ucLoop].ulAbsTimeStamp == ulRfTimeStamp)
      {

        ucABSIndex1 = ucLoop;
        ucABSIndex2 = ucABSIndex1;

        break;
      }
      else{

      }
   }

   if(ucABSIndex1 != 0xFF)
   {
      if(ucABSIndex1 == ucABSIndex2)
      {

      }
      else if(ucABSIndex1 == (cAbsBufferSize - 1))
      {

        ucABSIndex2 = 0;
      }
      else{
        ucABSIndex2 = ucABSIndex1 + 1;
      }
      if(tAbsDataBuff[ucABSIndex1].ulAbsTimeStamp <= tAbsDataBuff[ucABSIndex2].ulAbsTimeStamp)
      {
        if(tAbsDataBuff[ucABSIndex2].ulAbsTimeStamp < ulRfTimeStamp)
        {
          ucRet = cABS_VALUE_TOO_OLD;
          ucAbsState = ccABS_STATE_LinABS_ERR;
        }
        else{
          for(ucWheelCounter = 0; ucWheelCounter < cNUMBER_OF_WHEELS; ucWheelCounter++)
          {
            if(ucABSIndex1 == ucABSIndex2)
            {
              aushDivisor[ucWheelCounter] = 0;
            }
            else{
              aushDivisor[ucWheelCounter] = ushCalcABS(ulRfTimeStamp, tAbsDataBuff[ucABSIndex1].ulAbsTimeStamp, tAbsDataBuff[ucABSIndex1].aushAbsCnt[ucWheelCounter], tAbsDataBuff[ucABSIndex2].ulAbsTimeStamp, tAbsDataBuff[ucABSIndex2].aushAbsCnt[ucWheelCounter]);
            }

            ushLinAbsData[ucWheelCounter] = (0xFFFF & (tAbsDataBuff[ucABSIndex1].aushAbsCnt[ucWheelCounter] + aushDivisor[ucWheelCounter]));
          }

          ushDebugAbsCntVlLin = ushLinAbsData[0];
          ushDebugAbsCntVrLin = ushLinAbsData[1];
          ushDebugAbsCntHlLin = ushLinAbsData[2];
          ushDebugAbsCntHrLin = ushLinAbsData[3];

          HandleOverflowABS(cFRONT_LEFT, ucABSTicksFrontAx);
          HandleOverflowABS(cFRONT_RIGHT, ucABSTicksFrontAx);
          HandleOverflowABS(cREAR_LEFT, ucABSTicksRearAx);
          HandleOverflowABS(cREAR_RIGHT, ucABSTicksRearAx);
          ucABSComp[0] = (uint8)((ushLinAbsData[0] + ushABSRefOffset[0]) % ucABSTicksFrontAx);
          ucABSComp[1] = (uint8)((ushLinAbsData[1] + ushABSRefOffset[1]) % ucABSTicksFrontAx);
          ucABSComp[2] = (uint8)((ushLinAbsData[2] + ushABSRefOffset[2]) % ucABSTicksRearAx);
          ucABSComp[3] = (uint8)((ushLinAbsData[3] + ushABSRefOffset[3]) % ucABSTicksRearAx);
          ucRet = cABS_OK;
          ucAbsState = ccABS_STATE_LinABS_AVL;
        }
      }
      else{
        ucRet = cABS_ERROR;
        ucAbsState = ccABS_STATE_LinABS_ERR;
      }
   }
   else{
      ucRet = cABS_ERROR;
      ucAbsState = ccABS_STATE_LinABS_ERR;
   }
  return ucRet;
}

static uint16 ushCalcABS( uint32 ulRfTimeStamp, uint32 ul1stAbsTimeStamp, uint16 ush1stAbsCnt
   ,     uint32 ul2ndAbsTimeStamp, uint16 ush2ndAbsCnt )
{
  uint16 ushAbs2RfTimeDiff;
  uint16 ushAbsTimeDiff;
  uint16 ushAbsCntDiff;
  uint16 ushDiv;

  if( ul1stAbsTimeStamp > ulRfTimeStamp )
  {

   ushAbs2RfTimeDiff =(uint16) ( 0xFFFF & ((cTimeOverflowValue - ul1stAbsTimeStamp) + ulRfTimeStamp) );
  }
  else{
   ushAbs2RfTimeDiff =(uint16) ( 0xFFFF & (ulRfTimeStamp - ul1stAbsTimeStamp) );
  }

  if( ul1stAbsTimeStamp > ul2ndAbsTimeStamp )
  {

   ushAbsTimeDiff = (uint16)( 0xFFFF & ((cTimeOverflowValue - ul1stAbsTimeStamp) + ul2ndAbsTimeStamp));
  }
  else{
   ushAbsTimeDiff = (uint16)( 0xFFFF & (ul2ndAbsTimeStamp - ul1stAbsTimeStamp) );
  }

  if( ush1stAbsCnt > ush2ndAbsCnt )
  {

   ushAbsCntDiff = ( cAbsOverflowValue & ( (cAbsOverflowValue - ush1stAbsCnt) + ush2ndAbsCnt ) );
  }
  else{
   ushAbsCntDiff = ush2ndAbsCnt - ush1stAbsCnt;
  }

  ushDiv =(uint16)(0xFFFF & ((((ushAbsTimeDiff * 100) / ushAbs2RfTimeDiff) + 5) / 10));

  return (uint16)(0xFFFF & ((((ushAbsCntDiff * 100) / ushDiv) + 5) / 10));
}

static void HandleOverflowABS(uint8 ucWheelPosition, uint8 ucABSTicksAx)
{
  uint8 ucOverflowOffset;
  uint8 ucTempOverflowCntIdx;
  uint8 ucRefCorrectionValue = 0;
  if(ushLinAbsData[ucWheelPosition] < tAbsDataBuff[ucABSIndex1].aushAbsCnt[ucWheelPosition])
  {
   ucTempOverflowCntIdx = ucABSIndex2;
  }
  else{
   ucTempOverflowCntIdx = ucABSIndex1;
  }

  ucOverflowOffset = (uint8)((tAbsDataBuff[ucTempOverflowCntIdx].aucOverflowCnt[ucWheelPosition] >= aucPreviousOverflowCnt[ucWheelPosition]) ?
              (tAbsDataBuff[ucTempOverflowCntIdx].aucOverflowCnt[ucWheelPosition] - aucPreviousOverflowCnt[ucWheelPosition]) :
              (((0xFFU - aucPreviousOverflowCnt[ucWheelPosition]) + tAbsDataBuff[ucTempOverflowCntIdx].aucOverflowCnt[ucWheelPosition]) + 1));

  ucRefCorrectionValue = (ucOverflowOffset * ucABSigOFL_MOD_ZAHN(ucABSTicksAx)) % ucABSTicksAx;

  RebuildABSRef(ucWheelPosition, ucABSTicksAx, ucRefCorrectionValue);
  ushABSRefOffset[ucWheelPosition] = (ushABSRefOffset[ucWheelPosition] + (uint16)ucRefCorrectionValue) % (uint8)ucABSTicksAx;
  aucPreviousOverflowCnt[ucWheelPosition] = tAbsDataBuff[ucTempOverflowCntIdx].aucOverflowCnt[ucWheelPosition];
}

uint8 DCM_InvIf_AbsLinAngle_FL_GetHistoryValue(void){
  return ucABSComp[0];
}

uint8 DCM_InvIf_AbsLinAngle_FR_GetHistoryValue(void){
  return ucABSComp[1];
}

uint8 DCM_InvIf_AbsLinAngle_RL_GetHistoryValue(void){
  return ucABSComp[2];
}

uint8 DCM_InvIf_AbsLinAngle_RR_GetHistoryValue(void){
  return ucABSComp[3];
}

uint8 DCM_InvIf_AbsLinGetCntValueFL(void){
  return (uint8) (0xFF & ushLinAbsData[0]);
}

uint8 DCM_InvIf_AbsLinGetCntValueFR(void){
  return (uint8) (0xFF & ushLinAbsData[1]);
}

uint8 DCM_InvIf_AbsLinGetCntValueRL(void){
  return (uint8) (0xFF & ushLinAbsData[2]);
}

uint8 DCM_InvIf_AbsLinGetCntValueRR(void){
  return (uint8) (0xFF & ushLinAbsData[3]);
}
