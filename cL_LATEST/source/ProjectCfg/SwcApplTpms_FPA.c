/******************************************************************************/
/* File   : SwcApplTpms_FPA.c                                                 */
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
#include "WallocX.hpp"
#include "Walloc_IF.hpp"
#include "walloc.hpp"
#include "FPA.hpp"
#include "SwcApplTpms_abs_lin.hpp"
#include "CD_Decoder_X.hpp"
#include "state_fzzX.hpp"
#include "procdatx.hpp"
#include "global.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#ifdef FPA
#define cFPARefWidth 1
#define cMinCt4Dec (unsigned char) 14
#define cDeltaRelValAtBegin 5 // delta to increase the allocation threshold value, to slowdown the allowing allocation for the first 3 minutes
#define cHSrange 1  //high speed range
#define cLSrange 2  //low speed range (not used in SYMC C300, because G5 WE don't diffirentiate between high and low speed range by calculation of angle delay )
#define cIFS 3
#define cIFS240Deg 4
#define SPEEDWEIGHT
#define cRotatSFrameNo_Mask      0x90U
#define cRotatSFrameNo_1st       0x00U
#define cRotatSFrameNo_2nd       0x80U
#define cRotatSFrameNo_3rd       0x10U
#define cRotatSFrameNo_Reserved  0x90U
#define REF_RESET_COUNTER_MAX_VALUES    ((unsigned char)16)
#define cLeftCarSide  (cWP_FL | cWP_RL) //(0x01 | 0x04)
#define cRightCarSide (cWP_FR | cWP_RR) //(0x02 | 0x08)
#define cFrontCarAxis (cWP_FL | cWP_FR) //(0x01 | 0x02)
#define cRearCarAxis (cWP_RL | cWP_RR) //(0x04 | 0x08)

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
static void GenCmpVal(unsigned char ucID);
static unsigned char ucGenDMnD(void);
static boolean bGenDMnD_CalcPercDiff(unsigned char* ucdMin, unsigned char ucMax);
static boolean bGenDMnD_CheckPosibleAssign(unsigned char* ucLowPrior);
static boolean bGenDMnD_TryNormalAssign(unsigned char* ucLowPrior, unsigned char* ucRet);
static unsigned char ucGenDMnD_TryExclMxAssign(unsigned char* ucdMid, unsigned char* ucdMin, unsigned char ucMax);
static unsigned char ucGenDMnD_DistingAxes_SamePosition(unsigned char i, unsigned char j, unsigned char* ucAssign);
static unsigned char ucGenDMnD_DistingAxes_DifferentPosition(unsigned char i, unsigned char j, unsigned char ucCarSide, unsigned char* ucAssign);
static void AssignBestRival(unsigned char ucDoAssignment, unsigned char i, unsigned char j, unsigned char* ucAssign);
static void SetAndExcludeWP(unsigned char ucZomIx, unsigned char ucZomWP);
void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax);
static unsigned char ucBitcount(unsigned char ucInt); //return the number of set bits (hamming weight)
static unsigned char ucGetPositionOnAx(unsigned char ucValue);

#ifdef BUILD_WITH_UNUSED_FUNCTION
static unsigned short ushGetABSingleTickTDL(unsigned char ucIx);
#endif // BUILD_WITH_UNUSED_FUNCTION

static unsigned short ushGetABSingleTickTDL(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_120Deg(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_240Deg(unsigned char ucIx);
static unsigned char ucGetTDL(unsigned char ucCorType, unsigned char ucWheelPosIx);
void NormalizeAndSortCnt(void);
static unsigned short ush1stABSTickFL;
static boolean bTelTypeFromNormalDrive;
unsigned short (*fp2ushABSingleTick) (unsigned char ucPos);
unsigned short ushCuRotatsIn05msec = 0;
static unsigned char ucRefResetCounter;  //Counter for number of resets caused by roll back or auto location timeouts
static unsigned char ucDebugSumCorr[cSumWE][cMaxLR]; //Correlation counter (in %) for wheel position FL - RR of all ID's from ZOM
static unsigned char ucDebugAllocType;  //the reason for successfull auto-loacation

#ifdef ABS_Test_LOG_ENABLE
unsigned short ushDebug_dN[cSumABSig] = {0};
unsigned short ushDebug_dN2[cSumABSig] = {0};
#endif

unsigned char CounterPreparation (unsigned char ucID, tRFTelType * ptInputWA){
  unsigned char ucRetVal = FALSE;
  unsigned char ucSpeedLoop;
  unsigned char ucTrackLoop;
  unsigned char j;

  ucSpeedLoop = 0;
  ucTrackLoop = 0;

  fp2ushABSingleTick = ((void *) 0); //#1.4 Angle compensation

  if((ptInputWA->AK35def.ucCmdID == cTelTypeHufStatus) || (ptInputWA->AK35def.ucCmdID == cTelTypeAK35def))
  {
   bTelTypeFromNormalDrive = TRUE; //for further analysis of this telegram in APC algorithm (allocation with exclusion matrix)
  }
  else if(ptInputWA->AK35def.ucCmdID == cTelTypeRotatS)  //#2.1 Check the current frame type
  {
   if((ptInputWA->RotatS .ucSnRH & cRotatSFrameNo_Mask) == cRotatSFrameNo_2nd) // 2nd frame?
   {
      fp2ushABSingleTick = &ushGetABSingleTickTDL_120Deg;
   }
   else if((ptInputWA->RotatS .ucSnRH & cRotatSFrameNo_Mask) == cRotatSFrameNo_1st)// 1st frame?
   {
      fp2ushABSingleTick = &ushGetABSingleTickTDL;
   }
   else if((ptInputWA->RotatS.ucSnRH & cRotatSFrameNo_Mask) == cRotatSFrameNo_3rd) //3rd frame?
   {
      fp2ushABSingleTick = &ushGetABSingleTickTDL_240Deg;
   }
   else{

   }
  }
  else if(ptInputWA->AK35def.ucCmdID == cTelTypeSchraderFP)
  {
    //don't do allocation for alien manufacturer wheel sensors
  }
  else{
    /* unrecognized command ID, nothing will be done. */
  }

  if(!(fp2ushABSingleTick == ((void *) 0)))
  {
    GenCmpVal(ucID);
#ifdef SPEEDWEIGHT
#ifdef IBTCM_SW_ANPASSUNGEN
    //#2.8 Initiate loop flags

    //at the moment bad APC quality can be marked only in 1st frame, => 2nd and 3rd frame have always good quality => almost every telegram will be countet double  (wish of M. Alexander)
   if(0x00 == (ptInputWA->RotatS.ucSnRH & 0x40)) //check APC detection quality bit
   {//initiate track loop
      ucTrackLoop++; //#2.12 Increment track loop
   }
   if(ushGetRotatSVehSpeed() < tWAPar.ucnVweight) // FP telegrams at low speed are high precise and therefore to be double weighted
   {//initiate speed loop
      ucSpeedLoop++; //#2.10 Increment speed loop
   }
   else{
      //at high speed, always weight telegrams just once
      ucSpeedLoop = 0;
      ucTrackLoop = 0;
   }

   if((ucSpeedLoop + ucTrackLoop) > 0) //#2.9, #2.11 check weighting
#else
   if(GETushSpeedFZZ() < (unsigned short) 60) // FP telegrams at low speed are high precise and therefore to be double weighted
#endif //IBTCM_SW_ANPASSUNGEN

   {
      GenCmpVal(ucID);
   }
#endif //SPEEDWEIGHT

    //#2.13 choose smallest value
   for(j = 0; j < cSumABSig; j++)
   {
      if(tZOM[ucID].ushPosCompVal2[j] < tZOM[ucID].ushPosCompVal[j])
      {
        tZOM[ucID].ushPosCompVal[j] = tZOM[ucID].ushPosCompVal2[j];
      }
   }

    //#2.14; (#3.9 + #3.10 of APC-algorithm)
    NormalizeAndSortCnt();

   ucRetVal = TRUE;
  }
  return ucRetVal;
}

void NormalizeAndSortCnt(void){
  unsigned char i, j;
  unsigned long ulCmpSum = 0;

  unsigned long ulTmp[cSumWE];

  for(i = 0; i < cSumWE; i++)
  {
   ulCmpSum = 0;
    // (#3.9)Normalize counter results
   for(j = 0; j < cSumABSig; j++)
   {
      ulCmpSum += tZOM[i].ushPosCompVal[j];
   }
   for(j = 0; j < cSumABSig; j++)
   {
      if(tZOM[i].ushPosCompVal[j] > 0)
      {
        ulTmp[i] = (unsigned long)tZOM[i].ushPosCompVal[j] * 100;
        ulTmp[i] /= ulCmpSum; //normalized counter
        tZOM[i].ucRelCmpVal[j] = (unsigned char)(0xFF & ulTmp[i]);
      }
      else{
        tZOM[i].ucRelCmpVal[j] = (unsigned char)1;
      }

      if(tZOM[i].ucRelCmpVal[j] == 0)
      {
        tZOM[i].ucRelCmpVal[j] = (unsigned char)1; //make sure there are no 0's as relative value, for the case we have to assign with the exclusion matrix
      }
      ucDebugSumCorr[i][j] = tZOM[i].ucRelCmpVal[j];
   }

    SortBiggest1st(tZOM[i].ucRelCmpVal, tZOM[i].ucSort, cSumABSig);   //sort the indices of Relative compare value by the hight of the values
  }
}

unsigned char ucConceptFixPos0(void){
  if((!(fp2ushABSingleTick == ((void *)0))) || (bTelTypeFromNormalDrive == TRUE))
  {
   bTelTypeFromNormalDrive = FALSE;
   if(ucGenDMnD() > 0)
   {
      return(1);
   }
   else{
      ResetAllocType();
      return(0);
   }
  }
  else{
    return (0);
  }
}

static void GenCmpVal(unsigned char ucID)
{
  unsigned long ulTmp;
  unsigned short ushdN, ushTmp, ushdN2;
  unsigned char i;

  //#2.2 Verify if there is already a start telegram/frame from this wheel sensor available, if not set start telegram as reference
  if((tZOM[ucID].ucAlgoTelEvtCnt > (cFPARefWidth - 1)) && (tZOM[ucID].ucResetABSRefFlag != 1)) // == cFPARefWidth
  {
   if((unsigned char)(128 + cFPARefWidth + 1) > tZOM[ucID].ucAlgoTelEvtCnt)
   {
      tZOM[ucID].ucAlgoTelEvtCnt++;
   }

   for(i = 0; i < cSumABSig; i++)
   {

      ushTmp = (unsigned short) ucGetAnZahn(i);
      ushdN =  fp2ushABSingleTick(i);   //get linearised+speed_delayed ABS-value for this ID-Rx
      //#2.4 Modulo determination
      ushdN %= ushTmp;                  // Modulo ABSTickFullRevolution (ABStickMOD)

   if(ushdN < tZOM[ucID].ucABSRef[i]) // allways stay in the range 0..ABSticksFullRevol   ABStickMOD < ABSrefMOD ->
   {
      ushdN += ushTmp;                  // ABStickMOD + ABSticksFullRevol
   }
      ushdN -= (unsigned short) tZOM[ucID].ucABSRef [i];    // dN = ABStickMOD - ABSrefMOD

      //(#2.5)

      ushTmp >>= 1; //Example for 104 ticks for one full revolution: 104 -> 52 ( make a half turn)
      ushdN  = ( ushdN > ushTmp) ? (ushdN - ushTmp):(ushdN + ushTmp);           // dN > 52 ? YES-> dN = dN - 52 ; NO -> dN = dN + 52
      ushdN2 = (ushdN + ((unsigned short)ucGetAnZahn(i) / 2)) % (unsigned short)ucGetAnZahn(i);

#ifdef ABS_Test_LOG_ENABLE
      ushDebug_dN[i]  = ushdN;
      ushDebug_dN2[i] = ushdN2;
#endif

#ifdef pb_ModulTest_050104
      tZOM[ucID].ucCurdN[i] = (unsigned char) ushdN;
#endif

      //(#2.6) Determine deviations
      if(tZOM[ucID].ucAlgoTelEvtCnt > (cFPARefWidth + 1))
      {
      if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)(128 + cFPARefWidth))
        { // arithmet. mean val
          tZOM[ucID].ushMVdN[i] += ushdN;
          tZOM[ucID].ushMVdN2[i] += ushdN2;
        }
        else{ // weighted mean val: MVdN = (MVdNalt x 127 + dN) / 128
          if(tZOM[ucID].ucAlgoTelEvtCnt == (unsigned char)(128 + cFPARefWidth))
          {
            tZOM[ucID].ushMVdN[i] +=64;
            tZOM[ucID].ushMVdN[i] >>= 7;
            tZOM[ucID].ushMVdN2[i] +=64;
            tZOM[ucID].ushMVdN2[i] >>= 7;

          }
          ushTmp = tZOM[ucID].ushMVdN[i]; // generate weighted mean value
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN;
          ulTmp += (unsigned long) 64;  // round
          ulTmp >>= 7;
          tZOM[ucID].ushMVdN[i] = (unsigned short) ulTmp;

          ushTmp = tZOM[ucID].ushMVdN2[i]; // generate weighted mean value 2
          ulTmp = (unsigned long) ushTmp << 7;
          ulTmp -= (unsigned long) ushTmp;
          ulTmp += (unsigned long) ushdN2;
          ulTmp += (unsigned long) 64;  // round
          ulTmp >>= 7;
          tZOM[ucID].ushMVdN2[i] = (unsigned short) ulTmp;
        }
      }
      else{
        tZOM[ucID].ushMVdN[i] = ushdN;
        tZOM[ucID].ushMVdN2[i] = ushdN2;
      }

   if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)(128 + cFPARefWidth))
   { // generate deviation with arithmet. mean val (actual calculation of #2.6)
      ushTmp = tZOM[ucID].ushMVdN[i] / ((unsigned short)(0xFFFF & (tZOM[ucID].ucAlgoTelEvtCnt - cFPARefWidth)));
        if( ushdN > ushTmp )
        {
          ushTmp = ushdN - ushTmp;
        }
        else{
          ushTmp -= ushdN;
        }
      }
      else{ // generate deviation with weighted mean val
        if(ushdN > tZOM[ucID].ushMVdN[i])
        {
          ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
        }
        else{
          ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
        }
      }
      // ushTmp now contains deviation

    //(#2.7) Increment counter & state
      ushTmp += tZOM[ucID].ushPosCompVal[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal[i])
      {
        tZOM[ucID].ushPosCompVal[i] = ushTmp;
      }
      // the same 4 2nd PosCompareVal
      if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)(128 + cFPARefWidth))
      { // generate deviation with arithmet. mean val
        ushTmp = tZOM[ucID].ushMVdN2[i] / ((unsigned short)(0xFFFF & (tZOM[ucID].ucAlgoTelEvtCnt - cFPARefWidth)));
        if( ushdN2 > ushTmp )
        {
          ushTmp = ushdN2 - ushTmp;
        }
        else{
          ushTmp -= ushdN2;
        }
      }
      else{ // generate deviation with weighted mean val
        if(ushdN2 > tZOM[ucID].ushMVdN2[i])
        {
          ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
        }
        else{
          ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
        }
      }
      // ushTmp now contains deviation

      ushTmp += tZOM[ucID].ushPosCompVal2[i];
      if(ushTmp > tZOM[ucID].ushPosCompVal2[i])
      {
        tZOM[ucID].ushPosCompVal2[i] = ushTmp;
      }
   }
  }
  else //#2.2 set first telegram as reference
  { // very 1st reception
   if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)1)
   {
      ush1stABSTickFL = fp2ushABSingleTick(0);
   }

   for(i = 0; i < cMaxLR; i++)
   {
      ushdN =  (fp2ushABSingleTick(i) % (unsigned short) ucGetAnZahn(i));
      tZOM[ucID].ucABSRef[i] = (unsigned char) ushdN;
   }

   if(tZOM[ucID].ucResetABSRefFlag == 1)
   {
      //no need to increment the telegram counter after a reference point reset
      tZOM[ucID].ucResetABSRefFlag=0;
   }
   else{
      tZOM[ucID].ucAlgoTelEvtCnt++;
   }
  }
}

static unsigned char ucGenDMnD(void){

  unsigned char i, j, ucRet;
  unsigned short ushPreCheckSum = 0;
  unsigned char ucIxLowPrior; // contains index of wheel sensor ID with smaller ucRelCmpVal.
  unsigned char ucdMin[4]; //percent difference between abs min in each ID line and 2nd minimum
  unsigned char ucdMid[4]; //percent difference between 3rd abs min in each ID line and 2nd minimum
  unsigned char ucHelpPlausib = 0; // to check plausibility of assigned wheel positions
  boolean bTmpCompResult;

  ucIxLowPrior = cMaxLR + 1;
  ucRet = 0;

  for( i = 0; i < cMaxLR; i++)
  {
   ushPreCheckSum = 0;
   for(j = 0; j < 4; j++)
   {
      ushPreCheckSum += tZOM[i].ushPosCompVal[j];
   }
   if(ushPreCheckSum == 0)
   {
      break;
   }
  }

  if(cMaxLR == i)
  { // all values are present, let it whip...

    // A) build up 4x4 WP relative shares
    //happens now in NormalizeAndSortCnt()

    //B) Determine percent difference and try to assign
    //Determine the percent difference of received wheel sensor ID in ZOM, check if event counter and percent differences are adequate to try an assignment
   bTmpCompResult = bGenDMnD_CalcPercDiff(ucdMin, cMaxLR);
   if(bTmpCompResult == TRUE)
   {
      //#4.4 Check if unique assignment of each wheel to one position is possible, if not find competing IDs
      bTmpCompResult = bGenDMnD_CheckPosibleAssign(&ucIxLowPrior);
      if(bTmpCompResult == TRUE)
      {
        //(#4.7) Try to assign each WS ID (n) to one ABS wheel position
        bTmpCompResult = bGenDMnD_TryNormalAssign(&ucIxLowPrior, &ucRet);
      }
   }

    //C) try assignment with exclusion matrix
   if(0 == bTmpCompResult)
   {
      ucRet = ucGenDMnD_TryExclMxAssign(ucdMid, ucdMin, cMaxLR);
   }
  }

  //Check the plausibility of assigned wheel positions
  if(ucRet == 1)
  {
   for(i = 0; i < cMaxLR; i++)
   {
      ucHelpPlausib |= (0x0F & tZOM[i].ucStatus);
   }
   if(ucHelpPlausib != 0x0F)
   {
      for(i = 0; i < cMaxLR; i++)
      {
        tZOM[i].ucStatus &= cNoWPos;
      }
      ucDebugAllocType  = 0;
      ucRet = 0; //wheel position assignment is not plausible, return "No decision"
   }
   else{
      //Do nothing, Return "WA finished"
   }
  }
  return (ucRet);
}

static boolean bGenDMnD_CalcPercDiff(unsigned char* ucdMin, unsigned char ucMax)
{
  unsigned char i;
  boolean bResult;
  unsigned char ucRelValMinDiffDelta = 0;

  bResult = TRUE;

  //add delta to increase the threshold value for allowing allocation for the first 3 minutes (to avoid wrong allocation)
  if(bGetHistProtecTimeOver() == TRUE)
  {
   ucRelValMinDiffDelta = tWAPar.ucnRelValMinDiff;
  }
  else{
   ucRelValMinDiffDelta = tWAPar.ucnRelValMinDiff + cDeltaRelValAtBegin;
  }

  for(i = 0; i < ucMax; i++)
  {
   ucdMin[i] = (uint8)(0xFF & (tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 2]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]]));  //#4.2 Determine percent difference

   if((ucdMin[i] >= ucRelValMinDiffDelta) &&               // #4.3 minimum lays 5% (+delta) below 2nd minimum
       (tZOM[i].ucAlgoTelEvtCnt >= tWAPar.ucNewMinCntEvt))   //necessary amount of RF telegrams to auto learn current ID received
   {
      bResult &= bResult;
   }
   else{
      bResult = FALSE;
   }
  }
  return bResult;
}

static boolean bGenDMnD_CheckPosibleAssign(unsigned char* ucLowPrior)
{
  unsigned char i, j;
  unsigned char ucPreAssign;
  unsigned char ucTmp = 0;
  boolean bResult;

  bResult = TRUE; //opposite has to be proved first
  ucPreAssign = 0;

  for(i = 0; i < cMaxLR; i++)
  {
   ucPreAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);  //Try to assign each of own WS IDs to a position
  }

  if(ucPreAssign == 0x0F) //#4.5 Check unique assignment
  {
    //assignement is possible, do nothing here => continue
  }
  else{//no unique assignment
    //#4.6 Relative comparison of competitors
   ucTmp = 0xFF & ((NEGATE_UCHAR(ucPreAssign)) << 4);
   ucTmp = ucBitcount(ucTmp);
   if(ucTmp <= 1)
   {//only 2 different IDs are competing for same ABS position, try to assign
      //try to find competing IDs
      for(i = 0; i < cMaxLR; i++)
      {
        for(j = 0; j < cSumABSig; j++)
        {
          if(i != j) //don't compare with itself
          {
            if(tZOM[i].ucSort[cSumABSig - 1] == tZOM[j].ucSort[cSumABSig - 1])
            {
              ucTmp = 0;
              break;
            }
          }
        }
        if(0 == ucTmp)
        {
          break;
        }
      }

      if(i != j) //Just a check to make sure that two competing different ID were found
      {
        //competing IDs are now i and j
        if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] > tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]])
        {
          ucTmp = tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] - tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]]; //difference between lowest ucRelCmpVal of competing IDs
          *ucLowPrior = i;
        }
        else{
          ucTmp = tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]]; //difference between lowest ucRelCmpVal of competing IDs
          *ucLowPrior = j;
        }

        if((tZOM[i].ucSort[cSumABSig - 2] == tZOM[j].ucSort[cSumABSig - 2]) &&  //part of #4.6
          (ucTmp >= tWAPar.ucnRelValCompetDiff))
        {
          //assignment of competitors is possible => do nothing, continue
        }
        else{//requirements for assignment are not fulfilled => stop here and try assignment with exclusion matrix
          bResult = FALSE;
        }
      }
      else{//competitors haven't been found for some reason => stop here and try assignment with exclusion matrix
        bResult = FALSE;
      }
   }
   else{//more then two concurranting wheels => stop here and try assignment with exclusion matrix
      bResult = FALSE;
   }
  }
  return bResult;
}

static boolean bGenDMnD_TryNormalAssign(unsigned char* ucLowPrior, unsigned char* ucRet)
{
  unsigned char i;
  unsigned char l_ucAssign;
  boolean bResult;

  bResult = TRUE; //opposite has to be proved first
  l_ucAssign = 0;

  //(#4.7) Try to assign each WS ID (n) to one ABS wheel position
  for(i = 0; i < cMaxLR; i++)
  {
   if(ucGetWPOfCol(ucGetColOfID(&tZOM[i].ulID)) == tZOM[i].ucSort[cSumABSig - 1])  //(#4.8 Compare to history positions)
   {
      SetZOMWP(i, (tZOM[i].ucSort[cSumABSig - 1]));
      l_ucAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);
      ucDebugAllocType |= 0x01; //save alloc reason: auto location according to history position matching
      *ucRet = 1;
   }
   else{// history position changed or new
      if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] < tWAPar.ucMaxZOnorm)  // changed or new WP must be obviously clear (means abs min < 15%)
      {
        if(i == *ucLowPrior)
        {
          SetZOMWP(i, (tZOM[i].ucSort[cSumABSig - 2]));
          l_ucAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 2]);
        }
        else{
          SetZOMWP(i, (tZOM[i].ucSort[cSumABSig - 1]));
          l_ucAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);
        }
        ucDebugAllocType |= 0x02; //save alloc reason: auto location according to obvious percen diviations
        *ucRet = 1;
      }
      else{
        //try the next ID, but the exclusion Matrix will be needed anyway
        ucDebugAllocType &= ~(0x03);
        *ucRet = 0;
        bResult = FALSE;
      }
   }
  }

  //check the final assignment, if not correct: delete assigned positions from ZOM
  if((l_ucAssign != 0x0F) && (bResult == TRUE))
  {
   for(i = 0; i < cMaxLR; i++)
   {
      tZOM[i].ucStatus &= cNoWPos;
      ucDebugAllocType &= ~(0x03);
      *ucRet = 0;
      bResult = FALSE;
   }
  }
  else{
    //do nothing
  }

  return bResult;
}

static unsigned char ucGenDMnD_TryExclMxAssign(unsigned char* ucdMid, unsigned char* ucdMin, unsigned char ucMax)
{
  boolean bTmpResult;
  unsigned char ucPreAssign;
  unsigned char ucRet;
  unsigned char ucHelpRet;
  unsigned char ucTmp;
  unsigned char ucTmpZomIx = 0;
  unsigned char ucIndex = 0;
  unsigned char ucIncrErrCnt = 0;
  unsigned char ucTempCarSide = 0;
  unsigned char i, j;

  bTmpResult = TRUE;
  ucPreAssign = 0;
  ucRet = 0;
  ucHelpRet = 0;

  //(#4.9) Enough TG received?
  for(i = 0; i < ucMax; i++)
  {
   if(tWAPar.ucnMinRxTGRF > tZOM[i].ucProbeCt)
   {//not enough telegrams received
      bTmpResult = FALSE;
      ucIncrErrCnt = 0;
      ucRet = 0;
      break;
   }
   else{
      ucdMid[i] = (uint8)(0xFF & (tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 3]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 2]]));  //(#4.10) Determine percent difference dMid
   }

    //(#4.11) Exclusion matrix step 1
   if((ucdMid[i] >= tWAPar.ucnRelValMidDiff) && (tZOM[i].ucAlgoTelEvtCnt >= tWAPar.ucNewMinCntEvt)) //SSC: additionally check the amount of analysed RotatS telegrams, to avoid wrong exclusion
                                                                                                      //(percentage deviations have to be stable, this is guaranteed by high amount of analysed telegrams)
   {
      tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 4]] = 0xFF;    //ucRelCmpVal[WS][PS] == 0 or 0xFF means this spot is excluded in the matrix
      tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 3]] = 0xFF;
   }
#ifdef G_USE_ROTATION_DIRECTION
    //(#4.12) Exclusion matrix step 2: consider rotation direction information
   if(tZOM[i].ucStatus & cLeftSpin)
   {
      tZOM[i].ucRelCmpVal[1] = 0xFF;
      tZOM[i].ucRelCmpVal[3] = 0xFF;
   }
   else if(tZOM[i].ucStatus & cRightSpin)
   {
      tZOM[i].ucRelCmpVal[0] = 0xFF;
      tZOM[i].ucRelCmpVal[2] = 0xFF;
   }
   else{
      ucIncrErrCnt |= 1;
   }
#endif //G_USE_ROTATION_DIRECTION
    SortBiggest1st(tZOM[i].ucRelCmpVal, tZOM[i].ucSort, cSumABSig);   //  sort the indices of Relative compare value by the hight of the values
  }
#ifdef G_USE_ROTATION_DIRECTION
  if(ucIncrErrCnt != 0)
  {
    // no rotation direction could be estimate => incriment error count
#ifdef DETECT_SYMC_WALLOC_DTC
    IncDirDetectionError();
   ucIncrErrCnt = 0;
#endif
  }
#endif //G_USE_ROTATION_DIRECTION

  if(bTmpResult == TRUE)
  {
    //(#4.13) Exclusion matrix step 3
   for(i = 0; i < cMaxLR; i++)
   {
      ucTmp = TRUE;
      if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] > 0) //check if this position still available (>0)
      {
        for(j = 0; j < cMaxLR; j++)
        {
          if((j != i) && (tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]] > 0))
          {
            if(tZOM[i].ucSort[cSumABSig - 1] == tZOM[j].ucSort[cSumABSig - 1])
            {//competition between at least two WS for this position, try to distinguish axes with help of RSSI levels
              //(#4.14) Competition FA-RA or competition on the same axle?
              ucTempCarSide = (1 << tZOM[i].ucSort[cSumABSig - 1]) | (1 << tZOM[i].ucSort[cSumABSig - 2]);
              if((tZOM[i].ucSort[cSumABSig - 2] == tZOM[j].ucSort[cSumABSig - 2]) && ((ucTempCarSide == cLeftCarSide) || (ucTempCarSide == cRightCarSide)))
              {
                //competition between WS for the same wheel position
                ucHelpRet |= ucGenDMnD_DistingAxes_SamePosition(i, j, &ucPreAssign);
                ucIncrErrCnt |= ucHelpRet;
                AssignBestRival(ucHelpRet, i, j, &ucPreAssign);
              }
              ucTmp = 0;
              break;
            }
            else{
              //check if on the same car side
              ucTempCarSide = (1 << tZOM[i].ucSort[cSumABSig - 1]) | (1 << tZOM[j].ucSort[cSumABSig - 1]);
              if((ucTempCarSide == cLeftCarSide) || (ucTempCarSide == cRightCarSide))
              {
                //competition between WS on the same side, but different wheel positions try to distinguish axes with RSSI-Levels
                ucHelpRet |= ucGenDMnD_DistingAxes_DifferentPosition(i, j, ucTempCarSide, &ucPreAssign);
                ucIncrErrCnt |= ucHelpRet;
                AssignBestRival(ucHelpRet, i, j, &ucPreAssign);
                ucTmp = 0;
                break;
              }
            }
          }
        }
        if(ucTmp == TRUE)
        {
          if((ucdMin[i] >= tWAPar.ucnRelValMinDiff) && (tZOM[i].ucAlgoTelEvtCnt > tWAPar.ucNewMinCntEvt)) //part of #4.13
          {//no competition for this WS on this position and other requirements fulfilled => put position in ZOM-Status
            SetAndExcludeWP(i, tZOM[i].ucSort[cSumABSig - 1]);
            ucPreAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);	//mark the assignment of this WS to this position
            ucDebugAllocType |= 0x08; //save reason: auto location according to exclusion matrix
          }
          else{
            //Requirements are not fulfilled, no auto location possible
          }
        }
        if(ucPreAssign == 0x0F) //allocation already completed stop this "for"-loop
        {
          break;
        }
      }
   }
   if(ucIncrErrCnt != 0)
   {
      //can't be distinguished between axes
#ifdef DETECT_SYMC_WALLOC_DTC
      IncAxisDetectionError();
#endif /* DETECT_SYMC_WALLOC_DTC */
   }

   if(ucPreAssign == 0x0F)
   {
      ucRet = 1; //autolocation is complete
   }
   else{//(#4.15)if only one ID left without position, assign it to the last free slot
      ucTmp = (unsigned char)((~ucPreAssign) & 0x0F); //index of free WP
      if(ucBitcount(ucTmp) == 1)
      {
        if(ucTmp == 8)
        {
          ucTmp = 3;
        }
        else{
          ucTmp = ucTmp >> 1;
        }
        for(i = 0; i < cMaxLR; i++)
        {
          //find not located Ws in ZOM
          if((tZOM[i].ucStatus & 0x0F) == 0)
          {
            ucTmpZomIx |= (1 << i);
            ucIndex = i; //save index of not located wheel sensor
          }
        }
        if(ucBitcount(ucTmpZomIx) == 1)
        {
          SetZOMWP(ucIndex, ucTmp);
          ucRet = 1; //autolocation is complete
          ucDebugAllocType |= 0x10; //save reason: auto location with forced location of last free position
        }
      }
   }
  }
  return ucRet;
}

static unsigned char ucGenDMnD_DistingAxes_SamePosition( unsigned char i, unsigned char j, unsigned char* ucAssign)
{
  unsigned char ucRet;
  unsigned char ucLowIx;  //ZOM index of wheel-sensor with lower RSSI-value
  unsigned char ucHighIx; //ZOM index of wheel-sensor with higher RSSI-value
  unsigned char ucHelpAbsDevi = 0; //deviation between two best correlating WS on one position
  unsigned char ucHelpRssiDist = 0; // distance between two competing wheel sensors
  unsigned char ucSensorWishAxis = (1 << tZOM[i].ucSort[cSumABSig - 1]); // mask of sensors axis according to lowest percent diviation
  ucRet = 0;
  ucLowIx = cMaxLR;
  ucHighIx = cMaxLR;

  if((tWAPar.ucEcuPosition != ucECUPosNeutral) && (ucSensorWishAxis != 0))
  {// distinguish the correct wheel sensor position based of the ECU position (front or rear).
   if(ushGetMeanRssiSum(i) > ushGetMeanRssiSum(j))
   { //MISRA 12.6 conform
      if(((tWAPar.ucEcuPosition == ucECUPosFront) && ((ucSensorWishAxis & cFrontCarAxis) > 0)) //wheel sensor i "wish" to be on front axil and RSSI-value confirms it too => WS i get higher priority
        || ((tWAPar.ucEcuPosition == ucECUPosRear) && ((ucSensorWishAxis & cRearCarAxis) > 0))) //wheel sensor i "wish" to be on rear axil and RSSI-value confirms it too => WS i get higher priority
      {
        ucLowIx = j;
        ucHighIx = i;
      }
      else if(((tWAPar.ucEcuPosition == ucECUPosFront) && ((ucSensorWishAxis & cRearCarAxis) > 0))//wheel sensor i "wish" to be on rear axil, but RSSI-value contradict it => WS j get higher priority
        || ((tWAPar.ucEcuPosition == ucECUPosRear) && ((ucSensorWishAxis & cFrontCarAxis) > 0)))  //wheel sensor i "wish" to be on front axil, but RSSI-value contradict it => WS j get higher priority
      {
        ucLowIx = i;
        ucHighIx = j;
      }
      else{//can't be distinguished between axes or competing positions are not on the same side of the car
        ucRet = 1;
      }
   }
   else{
      //can't be distinguished between axes
      ucRet = 1;
   }

   ucHelpAbsDevi = tZOM[ucHighIx].ucRelCmpVal[tZOM[ucHighIx].ucSort[cSumABSig - 2]] - tZOM[ucHighIx].ucRelCmpVal[tZOM[ucHighIx].ucSort[cSumABSig - 1]];
   ucHelpRssiDist = ucGetRssiDifference(i, j); //because of MISRA 12.4

   if((ucHelpAbsDevi >= 2) && (ucRet != 1) && (ucHelpRssiDist >= tWAPar.ucMinRssiDistance))
   {
      SetAndExcludeWP(ucHighIx, tZOM[ucHighIx].ucSort[cSumABSig - 1]);
      SetAndExcludeWP(ucLowIx, tZOM[ucLowIx].ucSort[cSumABSig - 2]);
      *ucAssign |= 1 << (tZOM[ucHighIx].ucSort[cSumABSig - 1]); //mark the assignment of this WS to this position
      *ucAssign |= 1 << (tZOM[ucLowIx].ucSort[cSumABSig - 2]); //mark the assignment of this WS to this position
      ucDebugAllocType |= 0x04; //save reason: auto location according to RSSI deviations between axes
      ucRet = 0;
   }
   else{
      ucRet = 1; //can't be distinguished between axes
      ucDebugAllocType &= ~(0x04);
   }
  }
  else{
   ucRet = 1;//can't be distinguished between axes
  }
  return ucRet;
}

static unsigned char ucGenDMnD_DistingAxes_DifferentPosition(unsigned char i, unsigned char j, unsigned char ucCarSide, unsigned char* ucAssign)
{
  unsigned char ucRet;
  unsigned char ucHighRssiIx;
  unsigned char ucLowRssiIx;
  unsigned char ucRssiDifference;
  unsigned char ucPosInFront;
  unsigned char ucPosInRear;
  unsigned char ucHighSensorAbsDevi = 0; //diviation between two best correlating WS on one position, with higher RSSI
  unsigned char ucLowSensorAbsDevi = 0; //diviation between two best correlating WS on one position, with lower RSSI
  unsigned char ucHighSensorWishAxis = 0; // mask of sensors axis according to lowest percent diviation
  unsigned char ucLowSensorWishAxis = 0; // mask of sensors axis according to lowest percent diviation

  ucRet = 1; //prove the opposite first

  if(tWAPar.ucEcuPosition != ucECUPosNeutral) //can only be ucECUPosNeutral, ucECUPosFront or ucECUPosRear
  {
   ucRssiDifference = ucGetRssiDifference(i, j);

   if(ucRssiDifference >= tWAPar.ucMinRssiDistance) //RSSI-difference big enough for differenciation?
   {
      if(ushGetMeanRssiSum(i) >= ushGetMeanRssiSum(j)) //which RSSI is higher
      {
        ucHighRssiIx = i;
        ucLowRssiIx = j;
      }
      else{
        ucHighRssiIx = j;
        ucLowRssiIx = i;
      }

      //calculate needed values
      ucHighSensorWishAxis = (1 << tZOM[ucHighRssiIx].ucSort[cSumABSig - 1]);
      ucLowSensorWishAxis = (1 << tZOM[ucLowRssiIx].ucSort[cSumABSig - 1]);
      ucHighSensorAbsDevi = tZOM[ucHighRssiIx].ucRelCmpVal[tZOM[ucHighRssiIx].ucSort[cSumABSig - 2]] - tZOM[ucHighRssiIx].ucRelCmpVal[tZOM[ucHighRssiIx].ucSort[cSumABSig - 1]];
      ucLowSensorAbsDevi = tZOM[ucLowRssiIx].ucRelCmpVal[tZOM[ucLowRssiIx].ucSort[cSumABSig - 2]] - tZOM[ucLowRssiIx].ucRelCmpVal[tZOM[ucLowRssiIx].ucSort[cSumABSig - 1]];

      if(ucHighSensorAbsDevi >= 2)
      {
        //does ECU-position and RSSI-differences correspont correctly with percentage differences (//MISRA 12.6 conform)
        if(((tWAPar.ucEcuPosition == ucECUPosFront) && ((ucHighSensorWishAxis & cFrontCarAxis) > 0) && ((ucLowSensorWishAxis & cRearCarAxis) > 0)) ||
          ((tWAPar.ucEcuPosition == ucECUPosRear) && ((ucHighSensorWishAxis & cRearCarAxis) > 0) && ((ucLowSensorWishAxis & cFrontCarAxis) > 0))   )
        {
          SetAndExcludeWP(ucHighRssiIx, tZOM[ucHighRssiIx].ucSort[cSumABSig - 1]);
          SetAndExcludeWP(ucLowRssiIx, tZOM[ucLowRssiIx].ucSort[cSumABSig - 1]);
          *ucAssign |= ucHighSensorWishAxis;	//mark the assignment of this WS to this position
          *ucAssign |= ucLowSensorWishAxis;	//mark the assignment of this WS to this position
          ucDebugAllocType |= 0x04; //save reason: auto location according to RSSI diviations between axes
          ucRet = 0;
        }
        else{
          //ABS-Percentage-Differences and RF-Level-Differences are contradicting here => if RF-Level-Differences are high enough and ABS-Percentage-Differences low enough, make allocation based on RF-Levels
          if((ucRssiDifference >= tWAPar.ucSufficientRssiDistance)
               && (ucHighSensorAbsDevi < tWAPar.ucnRelValMinDiff)
               && (ucLowSensorAbsDevi < tWAPar.ucnRelValMinDiff)  )
          {
            ucPosInFront = ucGetPositionOnAx(cFrontCarAxis & ucCarSide);
            ucPosInRear = ucGetPositionOnAx(cRearCarAxis & ucCarSide);
            if((ucPosInFront != 0xFF) && (ucPosInRear != 0xFF))
            {
              if(tWAPar.ucEcuPosition == ucECUPosFront) //if ECU-position on front axis, put wheel with higher RF-level on front axis, lower one - on rear axis
              {
                SetAndExcludeWP(ucHighRssiIx, ucPosInFront);
                SetAndExcludeWP(ucLowRssiIx, ucPosInRear);
                *ucAssign |= (cFrontCarAxis & ucCarSide); //mark the assignment of this WS to this position
                *ucAssign |= (cRearCarAxis & ucCarSide); //mark the assignment of this WS to this position
                ucRet = 0;
              }
              else{//ECU-Positon == Rear
                SetAndExcludeWP(ucHighRssiIx, ucPosInRear);
                SetAndExcludeWP(ucLowRssiIx, ucPosInFront);
                *ucAssign |= (cRearCarAxis & ucCarSide); //mark the assignment of this WS to this position
                *ucAssign |= (cFrontCarAxis & ucCarSide); //mark the assignment of this WS to this position
                ucRet = 0;
              }
            }
            else{
              ucRet = 1;//can't be distinguished between axes
            }
          }
        }
      }
   }
  }
  else{
   ucRet = 1;//can't be distinguished between axes
  }
  return ucRet;
}

static void AssignBestRival(unsigned char ucDoAssignment, unsigned char i, unsigned char j, unsigned char* ucAssign)
{
  unsigned char ucLowPrioIx;  //ZOM index of wheel-sensor with higher percentage share, so low priority
  unsigned char ucHighPrioIx; //ZOM index of wheel-sensor with lower percentage share, so high priority

  if(ucDoAssignment == 0x01U)
  {
    //assign best one of two ws to most plausible position
    //choose the ws with the lowest percentage deviation (HighPrio)
   if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] < tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]])
   {
      ucHighPrioIx = i;
      ucLowPrioIx = j;
   }
   else{
      ucHighPrioIx = j;
      ucLowPrioIx = i;
   }
   //assign the better ws to a position
   if(((tZOM[ucHighPrioIx].ucRelCmpVal[tZOM[ucHighPrioIx].ucSort[cSumABSig - 2]] - tZOM[ucHighPrioIx].ucRelCmpVal[tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]]) > tWAPar.ucnRelValMinDiff))
   {
   	//if competing for same position(ucDoAssignment == 1) and percentage deviation of better ws is low enough and the deviation of second ws is high enough (>15%), assign the better ws to a position
   	if((ucDoAssignment == 1) && (tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]] > tWAPar.ucMaxZOnorm))
   	{
   		SetAndExcludeWP(ucHighPrioIx, tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]); //#4.14.2 Assign best correlating sensor
   		*ucAssign |= 1 << (tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]);
   		ucDebugAllocType |= 0x08; //save reason: auto location according to exclusion matrix
   	}
   	//if percentage deviation of both WS on one car side is low enough and they don't compete for the same position (ucDoAssignment == 2) => assign the wheels
   	else if((ucDoAssignment == 2) && (tZOM[ucHighPrioIx].ucRelCmpVal[tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]] < tWAPar.ucMaxZOnorm))
   	{//assign the WS wih high prio
   		SetAndExcludeWP(ucHighPrioIx, tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]); //#4.14.2 Assign best correlating sensor
   		*ucAssign |= 1 << (tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]);
   		//assign WS with low prio if percentage values are good enough
   		if(((tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 2]] - tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]]) > tWAPar.ucnRelValMinDiff)
   			&& (tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]] < tWAPar.ucnRelValCompetDiff))
   		{
   			SetAndExcludeWP(ucLowPrioIx, tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]); //#4.14.2 Assign best correlating sensor
   			*ucAssign |= 1 << (tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]);
   		}
   		ucDebugAllocType |= 0x48; //save reason: auto location according to exclusion matrix
   	}
   	else
   	{
   		//do nothing
   	}
   }
   else{
      //do nothing
   }
  }
}

static void SetAndExcludeWP(unsigned char ucZomIx, unsigned char ucZomWP)
{
  //set ws with index ucZomIx to a concrete wheel position ucZomWP
  SetZOMWP(ucZomIx, ucZomWP);
  //exclude this wheel position from further allocation
  tZOM[ucZomIx].ucRelCmpVal[ucZomWP] = 0; //exclude this spot from free positions
}

static unsigned char ucBitcount(unsigned char ucInt)
{
  unsigned char ucCount = 0;
  while(ucInt == 0x01U)
  {
   ucCount += (ucInt & 1);
   ucInt >>= 1;
  }
  return ucCount;
}

void RebuildABSRef(unsigned char ucWP, unsigned char ucABSTicksOneRevol, unsigned char ucCorrectionValue)    // provided interface function of Walloc module -> wallocX.h decl;  ucWP is always only in the range [0;3]
{
  unsigned char i;

  for(i = 0; i < cSumWE ;i++)
  {
   if(tZOM[i].ucAlgoTelEvtCnt > 0)
   {
      if(tZOM[i].ucABSRef[ucWP] > ucCorrectionValue)
      {
        tZOM[i].ucABSRef[ucWP] -= ucCorrectionValue;
      }
      else{
        tZOM[i].ucABSRef[ucWP] = (ucABSTicksOneRevol - ucCorrectionValue) + tZOM[i].ucABSRef[ucWP];
      }
   }
  }
}

void ReNewABSRef(void)  // provided interface function of Walloc module -> wallocX.h decl
{
  unsigned char i;

  ucRefResetCounter++;
  ucRefResetCounter = ucRefResetCounter % REF_RESET_COUNTER_MAX_VALUES;

  for(i = 0; i < cSumWE ;i++)
  {
   if(tZOM[i].ucAlgoTelEvtCnt != 0)
   {
          tZOM[i].ucResetABSRefFlag = 1;
   }
   else{

   }
  }
}

void SortBiggest1st(unsigned char *ptVal, unsigned char *ptIx, unsigned char ucMax)
{
  unsigned char i,j, ucBuffer;

  for(i=0;i<ucMax;i++)
  {
    ptIx[i] = i;
  }

  for(i = 1; i < ucMax; i++)
  {
   for(j = i; j >= 1; j--)
   {
      if(ptVal[ptIx[j]] > ptVal[ptIx[j-1]])
      {
        ucBuffer = ptIx[j];
        ptIx[j] = ptIx[j-1];
        ptIx[j-1] = ucBuffer;
      }
      else{
        break;
      }
   }
  }
}

void Very1stABSTickIinit(void){
  ush1stABSTickFL = 0;
  fp2ushABSingleTick = ((void *) 0);
  ucRefResetCounter = 0;
}

unsigned char ucGetAnZahn(unsigned char ucWheelPosIx)
{
  unsigned char ucABSTicks = 0;

  if(ucWheelPosIx < 2) //Index 0=FL, 1=FR, 2=RL, 3=RR
  {
   ucABSTicks = ucGetABSTicksFullRevolFrontAx();
  }
  else{
   ucABSTicks = ucGetABSTicksFullRevolRearAx();
  }

  return ucABSTicks;
}

unsigned char ucABSigOFL_MOD_ZAHN(unsigned char ucABSTicksRevol) //ucABSTicksRevol allways != 0
{
  return ((cAbsOverflowValue + 1) % ucABSTicksRevol);
}

unsigned char ucMINUS_ABSigOFL_MOD_ZAHN(unsigned char ucABSTicksRevol) //ucABSTicksRevol allways != 0
{
  return (0xFFFF & (ucABSTicksRevol - (255 % ucABSTicksRevol))); //= ucGetAnZahn - (255 % ucGetAnZahn()) because of 0xFF == invalid value, we count from 0 to 254 = 255 valid counter values
}

static unsigned short ushGetABSingleTickTDL(unsigned char ucIx)
{
  return (0xFFFF & (ushGetABSingleTick(ucIx) + (unsigned short)ucGetTDL(cHSrange, ucIx)));
}

//for 2nd frame
static unsigned short ushGetABSingleTickTDL_120Deg(unsigned char ucIx)
{
  signed short sshTemp = 0;

  sshTemp = (signed short)(ushGetABSingleTick(ucIx) + (signed short)(ucGetTDL(cHSrange, ucIx) - ucGetTDL(cIFS, ucIx)));
  if(sshTemp >= 0)
  {
    //do nothing
  }
  else{
   sshTemp = (signed short)((255 - ucGetTDL(cIFS, ucIx)) + ucGetTDL(cHSrange, ucIx)) + (signed short)ushGetABSingleTick(ucIx);
  }
  return (0xFFFF & (unsigned short)sshTemp);
}

//for 3rd frame
static unsigned short ushGetABSingleTickTDL_240Deg(unsigned char ucIx)
{
  signed short sshTemp = 0;

  sshTemp = (signed short) (ushGetABSingleTick(ucIx) + (signed short)(ucGetTDL(cHSrange, ucIx) - ucGetTDL(cIFS240Deg, ucIx)));
  if(sshTemp >= 0)
  {
    //do nothing
  }
  else{
   sshTemp = (signed short)((255 - ucGetTDL(cIFS240Deg, ucIx)) + ucGetTDL(cHSrange, ucIx)) + (signed short)ushGetABSingleTick(ucIx);
  }
  return (0xFFFF & (unsigned short)sshTemp);
}

static unsigned char ucGetTDL(unsigned char ucCorType, unsigned char ucWheelPosIx)
{
  unsigned short ushVtmp;
  unsigned char ucIx;
  const unsigned char * puCTab;
  unsigned char ucABSTicksFullRevol;
  static const unsigned char cucCvHS[] = { 50, 50, 50, 50, 48, 47, 45, 43, 42, 40, 38, 37, 35, 33, 32, 30, 28, 27, 25, 23, 22, 20, 18, 17, 15, 13, 12, 10, 8, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
  static const unsigned char cucTDLatV[] = { 50, 50, 50, 48, 44, 40, 38, 38, 36, 36, 34, 33, 33, 31, 31, 31, 31, 29, 29, 29, 29, 29, 29, 29, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28 }; //values not used for SYMC X150/C300, only as default

  static const unsigned char cucIFS[] = { 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33 };
  static const unsigned char cucIFS240Deg[] = { 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66 };

  switch( ucCorType )
  {
  case cHSrange:
    puCTab = &cucCvHS[0];
   break;
  case cIFS:
    puCTab = &cucIFS[0];
   break;
  case cIFS240Deg:
    puCTab = &cucIFS240Deg[0];
   break;
  default:
    puCTab = &cucTDLatV[0];
   break;
  }

#ifdef IBTCM_SW_ANPASSUNGEN
   ushVtmp = ushGetRotatSVehSpeed();
#else
     ushVtmp =  GETushSpeedFZZ();
#endif //IBTCM_SW_ANPASSUNGEN

  ucIx = (unsigned char)(0xFF & ((((ushVtmp * 10)/5)+5)/10) );  // /5 = stepsize in tooth delay tab
  if(ucIx > 0)
  {
   ucIx--;
   if(ucIx > (sizeof(cucTDLatV)-(unsigned char)1))
   {
      ucIx = sizeof(cucTDLatV)-(unsigned char)1;
   }
  }

  ucABSTicksFullRevol = ucGetAnZahn(ucWheelPosIx);

  return((puCTab[ucIx] * ucABSTicksFullRevol) / 100);
}

uint8 DCM_InvIf_AbsCorrGetCntValueFL(uint8 u8_IDPossition)
{
  return ucDebugSumCorr[u8_IDPossition][0];
}

uint8 DCM_InvIf_AbsCorrGetCntValueFR(uint8 u8_IDPossition)
{
  return ucDebugSumCorr[u8_IDPossition][1];
}

uint8 DCM_InvIf_AbsCorrGetCntValueRL(uint8 u8_IDPossition)
{
  return ucDebugSumCorr[u8_IDPossition][2];
}

uint8 DCM_InvIf_AbsCorrGetCntValueRR(uint8 u8_IDPossition)
{
  return ucDebugSumCorr[u8_IDPossition][3];
}

uint8 DCM_InvIf_AbsGetResetCntValue(void){
  return ucRefResetCounter;
}

uint8 DCM_InvIf_DebugAllocType(void){
  return ucDebugAllocType;
}

#ifdef DEBUG_AUTOLOCATION

void DCM_InvIf_ushMVdNfromZOM(uint8 u8ZOMSlot, uint8 u8Position,  uint8 *u8pReturnedValue)
{
  u8pReturnedValue[0] = (uint8)((tZOM[u8ZOMSlot].ushMVdN[u8Position] & 0xFF00U ) >>  8U);;
  u8pReturnedValue[1] = (uint8)( tZOM[u8ZOMSlot].ushMVdN[u8Position] & 0x00FF  );
}

void DCM_InvIf_ushMVdN2fromZOM(uint8 u8ZOMSlot, uint8 u8Position,  uint8 *u8pReturnedValue)
{
  u8pReturnedValue[0] = (uint8)((tZOM[u8ZOMSlot].ushMVdN2[u8Position] & 0xFF00U ) >>  8U);;
  u8pReturnedValue[1] = (uint8)( tZOM[u8ZOMSlot].ushMVdN2[u8Position] & 0x00FF  );
}

uint8 DCM_InvIf_ucABSReffromZOM(uint8 u8ZOMSlot, uint8 u8Position)
{
  return tZOM[u8ZOMSlot].ucABSRef[u8Position];
}

uint8 DCM_InvIf_ucAlgoTelEvtCntfromZOM(uint8 u8ZOMSlot)
{
  return tZOM[u8ZOMSlot].ucAlgoTelEvtCnt;
}

#endif

void ResetAllocType(void){
  ucDebugAllocType = 0;
}

void SaveDebugAllocType(unsigned char ucAllocReason)
{
  ucDebugAllocType |= ucAllocReason;
}

static unsigned char ucGetPositionOnAx(unsigned char ucValue)
{
  unsigned char ucBitPosition = 0;
  while(ucValue == 0x01U)
  {
   ucValue = ucValue >> 1;
    ++ucBitPosition;
  }

  if(ucBitPosition >= 1)
  {
    return (ucBitPosition - 1);
  }
  else{
    return 0xFF;
  }
}

#ifdef pb_ModulTest_050104
void TESTPrintToothZOM_HL(void){
  unsigned char i,j;
  unsigned char aucWPSeq[][3] = {"FL","RL","FR","RR"};

  for(i = 0; i < 4;i++)
  {
    printf(";ID[%s];Status[%s];ucFPATelCt[%s]",aucWPSeq[i],aucWPSeq[i],aucWPSeq[i]);
   for( j  = 0; j < 4 ; j++)
      printf(";dN[%s][%d]",aucWPSeq[i],j);
   for( j  = 0; j < 4 ; j++)
      printf(";MVdN[%s][%d]",aucWPSeq[i],j);
   for( j  = 0; j < 4 ; j++)
      printf(";CmpVal[%s][%d]",aucWPSeq[i],j);
   for( j  = 0; j < 4 ; j++)
      printf(";MVdN2[%s][%d]",aucWPSeq[i],j);
   for( j  = 0; j < 4 ; j++)
      printf(";CmpVal2[%s][%d]",aucWPSeq[i],j);
   for( j  = 0; j < 4 ; j++)
      printf(";RelCmp[%s][%d]",aucWPSeq[i],j);
  }
}
void TESTPrintToothZOMAsLine(void){
  unsigned long ulID;

  ulID = ulGetRatIDatWP(0);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

   ulID = ulGetRatIDatWP(2);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

   ulID = ulGetRatIDatWP(1);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

   ulID = ulGetRatIDatWP(3);
    TESTPrintFPAZOMSlot(ucGetZOMPosOfID( &ulID));

  printf(";");
}
void TESTPrintFPAZOMSlot(unsigned char ucSlot)
{
  unsigned char j;

  printf(";%lu;0x%02X;%d",tZOM[ucSlot].ulID,tZOM[ucSlot].ucStatus,tZOM[ucSlot].ucToothTelCt );
  for( j  = 0; j < 4 ; j++)
    printf(";%d",tZOM[ucSlot].ucCurdN[j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushMVdN [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushPosCompVal [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushMVdN2 [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d", tZOM[ucSlot].ushPosCompVal2 [j]);
  for( j  = 0; j < 4 ; j++)
    printf(";%d",tZOM[ucSlot].ucRelCmpVal [j]);
}
void TESTPrinToothZOMSummary(unsigned char i)
{
  unsigned char j;

  if(i < 4)
  {
      printf(" %d; 0x%02X; %d; %d;",tZOM[i].ulID,tZOM[i].ucStatus ,tZOM[i].ucProbeCt ,tZOM[i].ucToothTelCt);
      for( j = 0; j < cMaxLR; j++)
        printf("%d;",tZOM[i].ucRelCmpVal[j]);
      for( j = 0; j < cMaxLR; j++)
        printf("%d;",tZOM[i].ushPosCompVal[j]);
  }
  else
   for( j = 0; j < 3; j++)
     printf(" %d; %d; %d; %d;",0,0,0,0);
}
#endif // pb_ModulTest_050104
#endif //FPA

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

