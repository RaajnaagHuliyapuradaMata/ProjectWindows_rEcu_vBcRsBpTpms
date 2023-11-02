#include "Std_Types.hpp"

#include "WallocX.hpp"
#include "Walloc_IF.hpp"
#include "walloc.hpp"
#include "FPA.hpp"
#include "CD_Decoder_X.hpp"
#include "state_fzzX.hpp"
#include "procdatx.hpp"
#include "global.hpp"
#include "SwcApplTpms_DevCanMesReqInterfaces.hpp"

#define cFPARefWidth                                                           1
#define cMinCt4Dec                                           ((unsigned char)14)
#define cDeltaRelValAtBegin                                                    5
#define cHSrange                                                               1
#define cLSrange                                                               2
#define cIFS                                                                   3
#define cIFS240Deg                                                             4
#define SPEEDWEIGHT
#define cRotatSFrameNo_Mask                                                0x90U
#define cRotatSFrameNo_1st                                                 0x00U
#define cRotatSFrameNo_2nd                                                 0x80U
#define cRotatSFrameNo_3rd                                                 0x10U
#define cRotatSFrameNo_Reserved                                            0x90U
#define REF_RESET_COUNTER_MAX_VALUES                         ((unsigned char)16)
#define cLeftCarSide                                           (cWP_FL | cWP_RL)
#define cRightCarSide                                          (cWP_FR | cWP_RR)
#define cFrontCarAxis                                          (cWP_FL | cWP_FR)
#define cRearCarAxis                                           (cWP_RL | cWP_RR)

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
static unsigned char ucBitcount(
   unsigned char ucInt);
static unsigned char ucGetPositionOnAx(unsigned char ucValue);

static unsigned short ushGetABSingleTickTDL(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_120Deg(unsigned char ucIx);
static unsigned short ushGetABSingleTickTDL_240Deg(unsigned char ucIx);
static unsigned char ucGetTDL(unsigned char ucCorType, unsigned char ucWheelPosIx);

void NormalizeAndSortCnt(void);

static unsigned short ush1stABSTickFL;
static boolean bTelTypeFromNormalDrive;
unsigned short (*fp2ushABSingleTick) (unsigned char ucPos);
unsigned short ushCuRotatsIn05msec = 0;
static unsigned char ucRefResetCounter;
static unsigned char ucDebugSumCorr[cSumWE][cMaxLR];
static unsigned char ucDebugAllocType;

unsigned short ushDebug_dN[cSumABSig] = {0};
unsigned short ushDebug_dN2[cSumABSig] = {0};

unsigned char CounterPreparation(
   unsigned char ucID,
   tRFTelType* ptInputWA){
   unsigned char ucRetVal = FALSE;
   unsigned char ucSpeedLoop;
   unsigned char ucTrackLoop;
   unsigned char j;
   ucSpeedLoop = 0;
   ucTrackLoop = 0;
   fp2ushABSingleTick = ((void*)0);
   if((ptInputWA->AK35def.ucCmdID == cTelTypeHufStatus) || (ptInputWA->AK35def.ucCmdID == cTelTypeAK35def)){
      bTelTypeFromNormalDrive = TRUE;
   }
   else if(ptInputWA->AK35def.ucCmdID == cTelTypeRotatS){
      if((ptInputWA->RotatS.ucSnRH & cRotatSFrameNo_Mask) == cRotatSFrameNo_2nd){
         fp2ushABSingleTick = &ushGetABSingleTickTDL_120Deg;
      }
      else if((ptInputWA->RotatS.ucSnRH & cRotatSFrameNo_Mask) == cRotatSFrameNo_1st){
         fp2ushABSingleTick = &ushGetABSingleTickTDL;
      }
      else if((ptInputWA->RotatS.ucSnRH & cRotatSFrameNo_Mask) == cRotatSFrameNo_3rd){
         fp2ushABSingleTick = &ushGetABSingleTickTDL_240Deg;
      }
      else{
      }
   }
   else if(ptInputWA->AK35def.ucCmdID == cTelTypeSchraderFP){
   }
   else{
   }
   if(!(fp2ushABSingleTick == ((void*)0))){
      GenCmpVal(
         ucID);

      if(0x00 == (ptInputWA->RotatS.ucSnRH & 0x40)){
         ucTrackLoop++;
      }
      if(ushGetRotatSVehSpeed() < tWAPar.ucnVweight){
         ucSpeedLoop++;
      }
      else{
         ucSpeedLoop = 0;
         ucTrackLoop = 0;
      }
      if((ucSpeedLoop + ucTrackLoop) > 0){
         GenCmpVal(
            ucID);
      }

      for(j = 0; j < cSumABSig ; j++){
         if(tZOM[ucID].ushPosCompVal2[j] < tZOM[ucID].ushPosCompVal[j]){
            tZOM[ucID].ushPosCompVal[j] = tZOM[ucID].ushPosCompVal2[j];
         }
      }
      NormalizeAndSortCnt();
      ucRetVal = TRUE;
   }
   return ucRetVal;
}

void NormalizeAndSortCnt(void){
   unsigned char i, j;
   unsigned long ulCmpSum = 0;
   unsigned long ulTmp[cSumWE];
   for(i = 0; i < cSumWE; i++){
      ulCmpSum = 0;
      for(j = 0; j < cSumABSig ; j++){
         ulCmpSum += tZOM[i].ushPosCompVal[j];
      }
      for(j = 0; j < cSumABSig ; j++){
         if(tZOM[i].ushPosCompVal[j] > 0){
            ulTmp[i] = (unsigned long)tZOM[i].ushPosCompVal[j] * 100;
            ulTmp[i] /= ulCmpSum; //normalized counter
            tZOM[i].ucRelCmpVal[j] = (unsigned char)(0xFF & ulTmp[i]);
         }
         else{
            tZOM[i].ucRelCmpVal[j] = (unsigned char)1;
         }
         if(tZOM[i].ucRelCmpVal[j] == 0){
            tZOM[i].ucRelCmpVal[j] = (unsigned char)1;
         }
         ucDebugSumCorr[i][j] = tZOM[i].ucRelCmpVal[j];
      }
      SortBiggest1st(
         tZOM[i].ucRelCmpVal,
         tZOM[i].ucSort,
         cSumABSig);
   }
}

unsigned char ucConceptFixPos0(void){
   if((!(fp2ushABSingleTick == ((void*)0))) || (bTelTypeFromNormalDrive == TRUE)){
      bTelTypeFromNormalDrive = FALSE;
      if(ucGenDMnD() > 0){
         return (1);
      }
      else{
         ResetAllocType();
         return (0);
      }
   }
   else{
      return (0);
   }
}

static void GenCmpVal(
   unsigned char ucID){
   unsigned long ulTmp;
   unsigned short ushdN, ushTmp, ushdN2;
   unsigned char i;

   if((tZOM[ucID].ucAlgoTelEvtCnt > (cFPARefWidth - 1)) && (tZOM[ucID].ucResetABSRefFlag != 1)){
      if((unsigned char)(128 + cFPARefWidth + 1) > tZOM[ucID].ucAlgoTelEvtCnt){
         tZOM[ucID].ucAlgoTelEvtCnt++;
      }
      for(i = 0; i < cSumABSig ; i++){
         ushTmp = (unsigned short)ucGetAnZahn(
            i);
         ushdN = fp2ushABSingleTick(
            i);
         ushdN %= ushTmp;
         if(ushdN < tZOM[ucID].ucABSRef[i]){
            ushdN += ushTmp;
         }
         ushdN -= (unsigned short)tZOM[ucID].ucABSRef[i];
         ushTmp >>= 1;
         ushdN = (ushdN > ushTmp) ? (ushdN - ushTmp) : (ushdN + ushTmp);
         ushdN2 = (ushdN + ((unsigned short)ucGetAnZahn(
            i) / 2)) % (unsigned short)ucGetAnZahn(
            i);

         ushDebug_dN[i] = ushdN;
         ushDebug_dN2[i] = ushdN2;

         if(tZOM[ucID].ucAlgoTelEvtCnt > (cFPARefWidth + 1)){
            if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)(128 + cFPARefWidth)){
               tZOM[ucID].ushMVdN[i] += ushdN;
               tZOM[ucID].ushMVdN2[i] += ushdN2;
            }
            else{
               if(tZOM[ucID].ucAlgoTelEvtCnt == (unsigned char)(128 + cFPARefWidth)){
                  tZOM[ucID].ushMVdN[i] += 64;
                  tZOM[ucID].ushMVdN[i] >>= 7;
                  tZOM[ucID].ushMVdN2[i] += 64;
                  tZOM[ucID].ushMVdN2[i] >>= 7;

               }
               ushTmp = tZOM[ucID].ushMVdN[i];
               ulTmp = (unsigned long)ushTmp << 7;
               ulTmp -= (unsigned long)ushTmp;
               ulTmp += (unsigned long)ushdN;
               ulTmp += (unsigned long)64;
               ulTmp >>= 7;
               tZOM[ucID].ushMVdN[i] = (unsigned short)ulTmp;
               ushTmp = tZOM[ucID].ushMVdN2[i];
               ulTmp = (unsigned long)ushTmp << 7;
               ulTmp -= (unsigned long)ushTmp;
               ulTmp += (unsigned long)ushdN2;
               ulTmp += (unsigned long)64;
               ulTmp >>= 7;
               tZOM[ucID].ushMVdN2[i] = (unsigned short)ulTmp;
            }
         }
         else{
            tZOM[ucID].ushMVdN[i] = ushdN;
            tZOM[ucID].ushMVdN2[i] = ushdN2;
         }

         if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)(128 + cFPARefWidth)){
            ushTmp = tZOM[ucID].ushMVdN[i] / ((unsigned short)(0xFFFF & (tZOM[ucID].ucAlgoTelEvtCnt - cFPARefWidth)));
            if(ushdN > ushTmp){
               ushTmp = ushdN - ushTmp;
            }
            else{
               ushTmp -= ushdN;
            }
         }
         else{
            if(ushdN > tZOM[ucID].ushMVdN[i]){
               ushTmp = ushdN - tZOM[ucID].ushMVdN[i];
            }
            else{
               ushTmp = tZOM[ucID].ushMVdN[i] - ushdN;
            }
         }
         ushTmp += tZOM[ucID].ushPosCompVal[i];
         if(ushTmp > tZOM[ucID].ushPosCompVal[i]){
            tZOM[ucID].ushPosCompVal[i] = ushTmp;
         }
         if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)(128 + cFPARefWidth)){
            ushTmp = tZOM[ucID].ushMVdN2[i] / ((unsigned short)(0xFFFF & (tZOM[ucID].ucAlgoTelEvtCnt - cFPARefWidth)));
            if(ushdN2 > ushTmp){
               ushTmp = ushdN2 - ushTmp;
            }
            else{
               ushTmp -= ushdN2;
            }
         }
         else{
            if(ushdN2 > tZOM[ucID].ushMVdN2[i]){
               ushTmp = ushdN2 - tZOM[ucID].ushMVdN2[i];
            }
            else{
               ushTmp = tZOM[ucID].ushMVdN2[i] - ushdN2;
            }
         }
         ushTmp += tZOM[ucID].ushPosCompVal2[i];
         if(ushTmp > tZOM[ucID].ushPosCompVal2[i]){
            tZOM[ucID].ushPosCompVal2[i] = ushTmp;
         }
      }
   }
   else{
      if(tZOM[ucID].ucAlgoTelEvtCnt < (unsigned char)1){
         ush1stABSTickFL = fp2ushABSingleTick(
            0);
      }
      for(i = 0; i < cMaxLR; i++){
         ushdN = (fp2ushABSingleTick(
            i) % (unsigned short)ucGetAnZahn(
            i));
         tZOM[ucID].ucABSRef[i] = (unsigned char)ushdN;
      }
      if(tZOM[ucID].ucResetABSRefFlag == 1){
         tZOM[ucID].ucResetABSRefFlag = 0;
      }
      else{
         tZOM[ucID].ucAlgoTelEvtCnt++;
      }
   }
}

static unsigned char ucGenDMnD(void){
   unsigned char i, j, ucRet;
   unsigned short ushPreCheckSum = 0;
   unsigned char ucIxLowPrior;
   unsigned char ucdMin[4];
   unsigned char ucdMid[4];
   unsigned char ucHelpPlausib = 0;
   boolean bTmpCompResult;
   ucIxLowPrior = cMaxLR + 1;
   ucRet = 0;
   for(i = 0; i < cMaxLR; i++){
      ushPreCheckSum = 0;
      for(j = 0; j < 4; j++){
         ushPreCheckSum += tZOM[i].ushPosCompVal[j];
      }
      if(ushPreCheckSum == 0){
         break;
      }
   }
   if(cMaxLR == i){
      bTmpCompResult = bGenDMnD_CalcPercDiff(
         ucdMin,
         cMaxLR);
      if(bTmpCompResult == TRUE){
         bTmpCompResult = bGenDMnD_CheckPosibleAssign(
            &ucIxLowPrior);
         if(bTmpCompResult == TRUE){
            bTmpCompResult = bGenDMnD_TryNormalAssign(
               &ucIxLowPrior,
               &ucRet);
         }
      }
      if(0 == bTmpCompResult){
         ucRet = ucGenDMnD_TryExclMxAssign(
            ucdMid,
            ucdMin,
            cMaxLR);
      }
   }
   if(ucRet == 1){
      for(i = 0; i < cMaxLR; i++){
         ucHelpPlausib |= (0x0F & tZOM[i].ucStatus);
      }
      if(ucHelpPlausib != 0x0F){
         for(i = 0; i < cMaxLR; i++){
            tZOM[i].ucStatus &= cNoWPos;
         }
         ucDebugAllocType = 0;
         ucRet = 0;
      }
      else{
      }
   }
   return (ucRet);
}

static boolean bGenDMnD_CalcPercDiff(
   unsigned char* ucdMin,
   unsigned char ucMax){
   unsigned char i;
   boolean bResult;
   unsigned char ucRelValMinDiffDelta = 0;
   bResult = TRUE;
   if(bGetHistProtecTimeOver() == TRUE){
      ucRelValMinDiffDelta = tWAPar.ucnRelValMinDiff;
   }
   else{
      ucRelValMinDiffDelta = tWAPar.ucnRelValMinDiff + cDeltaRelValAtBegin;
   }
   for(i = 0; i < ucMax; i++){
      ucdMin[i] = (uint8)(0xFF & (tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 2]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]])); //#4.2 Determine percent difference
      if((ucdMin[i] >= ucRelValMinDiffDelta) && (tZOM[i].ucAlgoTelEvtCnt >= tWAPar.ucNewMinCntEvt)){
         bResult &= bResult;
      }
      else{
         bResult = FALSE;
      }
   }
   return bResult;
}

static boolean bGenDMnD_CheckPosibleAssign(
   unsigned char* ucLowPrior){
   unsigned char i, j;
   unsigned char ucPreAssign;
   unsigned char ucTmp = 0;
   boolean bResult;
   bResult = TRUE;
   ucPreAssign = 0;
   for(i = 0; i < cMaxLR; i++){
      ucPreAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);
   }
   if(ucPreAssign == 0x0F){
   }
   else{
      ucTmp = 0xFF & ((NEGATE_UCHAR(
         ucPreAssign)) << 4);
      ucTmp = ucBitcount(
         ucTmp);
      if(ucTmp <= 1){
         for(i = 0; i < cMaxLR; i++){
            for(j = 0; j < cSumABSig ; j++){
               if(i != j){
                  if(tZOM[i].ucSort[cSumABSig - 1] == tZOM[j].ucSort[cSumABSig - 1]){
                     ucTmp = 0;
                     break;
                  }
               }
            }
            if(0 == ucTmp){
               break;
            }
         }

         if(i != j){
            if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] > tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]]){
               ucTmp = tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] - tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]];
               *ucLowPrior = i;
            }
            else{
               ucTmp = tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]];
               *ucLowPrior = j;
            }
            if((tZOM[i].ucSort[cSumABSig - 2] == tZOM[j].ucSort[cSumABSig - 2]) && (ucTmp >= tWAPar.ucnRelValCompetDiff)){
            }
            else{
               bResult = FALSE;
            }
         }
         else{
            bResult = FALSE;
         }
      }
      else{
         bResult = FALSE;
      }
   }
   return bResult;
}

static boolean bGenDMnD_TryNormalAssign(
   unsigned char* ucLowPrior,
   unsigned char* ucRet){
   unsigned char i;
   unsigned char l_ucAssign;
   boolean bResult;
   bResult = TRUE;
   l_ucAssign = 0;
   for(i = 0; i < cMaxLR; i++){
      if(ucGetWPOfCol(
         ucGetColOfID(
            &tZOM[i].ulID)) == tZOM[i].ucSort[cSumABSig - 1]){
         SetZOMWP(
            i,
            (tZOM[i].ucSort[cSumABSig - 1]));
         l_ucAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);
         ucDebugAllocType |= 0x01;
         *ucRet = 1;
      }
      else{
         if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] < tWAPar.ucMaxZOnorm){
            if(i == *ucLowPrior){
               SetZOMWP(
                  i,
                  (tZOM[i].ucSort[cSumABSig - 2]));
               l_ucAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 2]);
            }
            else{
               SetZOMWP(
                  i,
                  (tZOM[i].ucSort[cSumABSig - 1]));
               l_ucAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);
            }
            ucDebugAllocType |= 0x02;
            *ucRet = 1;
         }
         else{
            ucDebugAllocType &= ~(0x03);
            *ucRet = 0;
            bResult = FALSE;
         }
      }
   }
   if((l_ucAssign != 0x0F) && (bResult == TRUE)){
      for(i = 0; i < cMaxLR; i++){
         tZOM[i].ucStatus &= cNoWPos;
         ucDebugAllocType &= ~(0x03);
         *ucRet = 0;
         bResult = FALSE;
      }
   }
   else{
   }
   return bResult;
}

static unsigned char ucGenDMnD_TryExclMxAssign(
   unsigned char* ucdMid,
   unsigned char* ucdMin,
   unsigned char ucMax){
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
   for(i = 0; i < ucMax; i++){
      if(tWAPar.ucnMinRxTGRF > tZOM[i].ucProbeCt){
         bTmpResult = FALSE;
         ucIncrErrCnt = 0;
         ucRet = 0;
         break;
      }
      else{
         ucdMid[i] = (uint8)(0xFF & (tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 3]] - tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 2]]));
      }
      if((ucdMid[i] >= tWAPar.ucnRelValMidDiff) && (tZOM[i].ucAlgoTelEvtCnt >= tWAPar.ucNewMinCntEvt)){
         tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 4]] = 0xFF;
         tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 3]] = 0xFF;
      }
      SortBiggest1st(
         tZOM[i].ucRelCmpVal,
         tZOM[i].ucSort,
         cSumABSig);
   }
   if(bTmpResult == TRUE){
      for(i = 0; i < cMaxLR; i++){
         ucTmp = TRUE;
         if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] > 0){
            for(j = 0; j < cMaxLR; j++){
               if((j != i) && (tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]] > 0)){
                  if(tZOM[i].ucSort[cSumABSig - 1] == tZOM[j].ucSort[cSumABSig - 1]){
                     ucTempCarSide = (1 << tZOM[i].ucSort[cSumABSig - 1]) | (1 << tZOM[i].ucSort[cSumABSig - 2]);
                     if((tZOM[i].ucSort[cSumABSig - 2] == tZOM[j].ucSort[cSumABSig - 2]) && ((ucTempCarSide == cLeftCarSide) || (ucTempCarSide == cRightCarSide))){
                        ucHelpRet |= ucGenDMnD_DistingAxes_SamePosition(
                           i,
                           j,
                           &ucPreAssign);
                        ucIncrErrCnt |= ucHelpRet;
                        AssignBestRival(
                           ucHelpRet,
                           i,
                           j,
                           &ucPreAssign);
                     }
                     ucTmp = 0;
                     break;
                  }
                  else{
                     ucTempCarSide = (1 << tZOM[i].ucSort[cSumABSig - 1]) | (1 << tZOM[j].ucSort[cSumABSig - 1]);
                     if((ucTempCarSide == cLeftCarSide) || (ucTempCarSide == cRightCarSide)){
                        ucHelpRet |= ucGenDMnD_DistingAxes_DifferentPosition(
                           i,
                           j,
                           ucTempCarSide,
                           &ucPreAssign);
                        ucIncrErrCnt |= ucHelpRet;
                        AssignBestRival(
                           ucHelpRet,
                           i,
                           j,
                           &ucPreAssign);
                        ucTmp = 0;
                        break;
                     }
                  }
               }
            }
            if(ucTmp == TRUE){
               if((ucdMin[i] >= tWAPar.ucnRelValMinDiff) && (tZOM[i].ucAlgoTelEvtCnt > tWAPar.ucNewMinCntEvt)){
                  SetAndExcludeWP(
                     i,
                     tZOM[i].ucSort[cSumABSig - 1]);
                  ucPreAssign |= 1 << (tZOM[i].ucSort[cSumABSig - 1]);
                  ucDebugAllocType |= 0x08;
               }
               else{
               }
            }
            if(ucPreAssign == 0x0F){
               break;
            }
         }
      }
      if(ucIncrErrCnt != 0){
         IncAxisDetectionError();
}
      if(ucPreAssign == 0x0F){
         ucRet = 1;
      }
      else{
         ucTmp = (unsigned char)((~ucPreAssign) & 0x0F);
         if(ucBitcount(
            ucTmp) == 1){
            if(ucTmp == 8){
               ucTmp = 3;
            }
            else{
               ucTmp = ucTmp >> 1;
            }
            for(i = 0; i < cMaxLR; i++){
               if((tZOM[i].ucStatus & 0x0F) == 0){
                  ucTmpZomIx |= (1 << i);
                  ucIndex = i;
               }
            }
            if(ucBitcount(
               ucTmpZomIx) == 1){
               SetZOMWP(
                  ucIndex,
                  ucTmp);
               ucRet = 1;
               ucDebugAllocType |= 0x10;
            }
         }
      }
   }
   return ucRet;
}

static unsigned char ucGenDMnD_DistingAxes_SamePosition(
   unsigned char i,
   unsigned char j,
   unsigned char* ucAssign){
   unsigned char ucRet;
   unsigned char ucLowIx;
   unsigned char ucHighIx;
   unsigned char ucHelpAbsDevi = 0;
   unsigned char ucHelpRssiDist = 0;
   unsigned char ucSensorWishAxis = (1 << tZOM[i].ucSort[cSumABSig - 1]);
   ucRet = 0;
   ucLowIx = cMaxLR;
   ucHighIx = cMaxLR;

   if((tWAPar.ucEcuPosition != ucECUPosNeutral ) && (ucSensorWishAxis != 0)){
      if(ushGetMeanRssiSum(
         i) > ushGetMeanRssiSum(
         j)){
         if(((tWAPar.ucEcuPosition == ucECUPosFront ) && ((ucSensorWishAxis & cFrontCarAxis) > 0)) || ((tWAPar.ucEcuPosition == ucECUPosRear ) && ((ucSensorWishAxis & cRearCarAxis) > 0))){
            ucLowIx = j;
            ucHighIx = i;
         }
         else if(((tWAPar.ucEcuPosition == ucECUPosFront ) && ((ucSensorWishAxis & cRearCarAxis) > 0)) || ((tWAPar.ucEcuPosition == ucECUPosRear ) && ((ucSensorWishAxis & cFrontCarAxis) > 0))){
            ucLowIx = i;
            ucHighIx = j;
         }
         else{
            ucRet = 1;
         }
      }
      else{
         ucRet = 1;
      }
      ucHelpAbsDevi = tZOM[ucHighIx].ucRelCmpVal[tZOM[ucHighIx].ucSort[cSumABSig - 2]] - tZOM[ucHighIx].ucRelCmpVal[tZOM[ucHighIx].ucSort[cSumABSig - 1]];
      ucHelpRssiDist = ucGetRssiDifference(
         i,
         j);
      if((ucHelpAbsDevi >= 2) && (ucRet != 1) && (ucHelpRssiDist >= tWAPar.ucMinRssiDistance)){
         SetAndExcludeWP(
            ucHighIx,
            tZOM[ucHighIx].ucSort[cSumABSig - 1]);
         SetAndExcludeWP(
            ucLowIx,
            tZOM[ucLowIx].ucSort[cSumABSig - 2]);
         *ucAssign |= 1 << (tZOM[ucHighIx].ucSort[cSumABSig - 1]);
         *ucAssign |= 1 << (tZOM[ucLowIx].ucSort[cSumABSig - 2]);
         ucDebugAllocType |= 0x04;
         ucRet = 0;
      }
      else{
         ucRet = 1;
         ucDebugAllocType &= ~(0x04);
      }
   }
   else{
      ucRet = 1;
   }
   return ucRet;
}

static unsigned char ucGenDMnD_DistingAxes_DifferentPosition(
   unsigned char i,
   unsigned char j,
   unsigned char ucCarSide,
   unsigned char* ucAssign){
   unsigned char ucRet;
   unsigned char ucHighRssiIx;
   unsigned char ucLowRssiIx;
   unsigned char ucRssiDifference;
   unsigned char ucPosInFront;
   unsigned char ucPosInRear;
   unsigned char ucHighSensorAbsDevi = 0;
   unsigned char ucLowSensorAbsDevi = 0;
   unsigned char ucHighSensorWishAxis = 0;
   unsigned char ucLowSensorWishAxis = 0;
   ucRet = 1;
   if(tWAPar.ucEcuPosition != ucECUPosNeutral){
      ucRssiDifference = ucGetRssiDifference(
         i,
         j);
      if(ucRssiDifference >= tWAPar.ucMinRssiDistance){
         if(ushGetMeanRssiSum(
            i) >= ushGetMeanRssiSum(
            j)){
            ucHighRssiIx = i;
            ucLowRssiIx = j;
         }
         else{
            ucHighRssiIx = j;
            ucLowRssiIx = i;
         }
         ucHighSensorWishAxis = (1 << tZOM[ucHighRssiIx].ucSort[cSumABSig - 1]);
         ucLowSensorWishAxis = (1 << tZOM[ucLowRssiIx].ucSort[cSumABSig - 1]);
         ucHighSensorAbsDevi = tZOM[ucHighRssiIx].ucRelCmpVal[tZOM[ucHighRssiIx].ucSort[cSumABSig - 2]] - tZOM[ucHighRssiIx].ucRelCmpVal[tZOM[ucHighRssiIx].ucSort[cSumABSig - 1]];
         ucLowSensorAbsDevi = tZOM[ucLowRssiIx].ucRelCmpVal[tZOM[ucLowRssiIx].ucSort[cSumABSig - 2]] - tZOM[ucLowRssiIx].ucRelCmpVal[tZOM[ucLowRssiIx].ucSort[cSumABSig - 1]];
         if(ucHighSensorAbsDevi >= 2){
            if(((tWAPar.ucEcuPosition == ucECUPosFront ) && ((ucHighSensorWishAxis & cFrontCarAxis) > 0) && ((ucLowSensorWishAxis & cRearCarAxis) > 0)) || ((tWAPar.ucEcuPosition == ucECUPosRear ) && ((ucHighSensorWishAxis & cRearCarAxis) > 0) && ((ucLowSensorWishAxis & cFrontCarAxis) > 0))){
               SetAndExcludeWP(
                  ucHighRssiIx,
                  tZOM[ucHighRssiIx].ucSort[cSumABSig - 1]);
               SetAndExcludeWP(
                  ucLowRssiIx,
                  tZOM[ucLowRssiIx].ucSort[cSumABSig - 1]);
               *ucAssign |= ucHighSensorWishAxis;
               *ucAssign |= ucLowSensorWishAxis;
               ucDebugAllocType |= 0x04;
               ucRet = 0;
            }
            else{
               if((ucRssiDifference >= tWAPar.ucSufficientRssiDistance) && (ucHighSensorAbsDevi < tWAPar.ucnRelValMinDiff) && (ucLowSensorAbsDevi < tWAPar.ucnRelValMinDiff)){
                  ucPosInFront = ucGetPositionOnAx(
                     cFrontCarAxis & ucCarSide);
                  ucPosInRear = ucGetPositionOnAx(
                     cRearCarAxis & ucCarSide);
                  if((ucPosInFront != 0xFF) && (ucPosInRear != 0xFF)){
                     if(tWAPar.ucEcuPosition == ucECUPosFront){
                        SetAndExcludeWP(
                           ucHighRssiIx,
                           ucPosInFront);
                        SetAndExcludeWP(
                           ucLowRssiIx,
                           ucPosInRear);
                        *ucAssign |= (cFrontCarAxis & ucCarSide);
                        *ucAssign |= (cRearCarAxis & ucCarSide);
                        ucRet = 0;
                     }
                     else{
                        SetAndExcludeWP(
                           ucHighRssiIx,
                           ucPosInRear);
                        SetAndExcludeWP(
                           ucLowRssiIx,
                           ucPosInFront);
                        *ucAssign |= (cRearCarAxis & ucCarSide);
                        *ucAssign |= (cFrontCarAxis & ucCarSide);
                        ucRet = 0;
                     }
                  }
                  else{
                     ucRet = 1;
                  }
               }
            }
         }
      }
   }
   else{
      ucRet = 1;
   }
   return ucRet;
}

static void AssignBestRival(
   unsigned char ucDoAssignment,
   unsigned char i,
   unsigned char j,
   unsigned char* ucAssign){
   unsigned char ucLowPrioIx;
   unsigned char ucHighPrioIx;
   if(ucDoAssignment == 0x01U){
      if(tZOM[i].ucRelCmpVal[tZOM[i].ucSort[cSumABSig - 1]] < tZOM[j].ucRelCmpVal[tZOM[j].ucSort[cSumABSig - 1]]){
         ucHighPrioIx = i;
         ucLowPrioIx = j;
      }
      else{
         ucHighPrioIx = j;
         ucLowPrioIx = i;
      }
      if(((tZOM[ucHighPrioIx].ucRelCmpVal[tZOM[ucHighPrioIx].ucSort[cSumABSig - 2]] - tZOM[ucHighPrioIx].ucRelCmpVal[tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]]) > tWAPar.ucnRelValMinDiff)){
         if((ucDoAssignment == 1) && (tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]] > tWAPar.ucMaxZOnorm)){
            SetAndExcludeWP(
               ucHighPrioIx,
               tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]);
            *ucAssign |= 1 << (tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]);
            ucDebugAllocType |= 0x08;
         }
         else if((ucDoAssignment == 2) && (tZOM[ucHighPrioIx].ucRelCmpVal[tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]] < tWAPar.ucMaxZOnorm)){
            SetAndExcludeWP(
               ucHighPrioIx,
               tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]);
            *ucAssign |= 1 << (tZOM[ucHighPrioIx].ucSort[cSumABSig - 1]);
            if(((tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 2]] - tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]]) > tWAPar.ucnRelValMinDiff) && (tZOM[ucLowPrioIx].ucRelCmpVal[tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]] < tWAPar.ucnRelValCompetDiff)){
               SetAndExcludeWP(
                  ucLowPrioIx,
                  tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]);
               *ucAssign |= 1 << (tZOM[ucLowPrioIx].ucSort[cSumABSig - 1]);
            }
            ucDebugAllocType |= 0x48;
         }
         else{
         }
      }
      else{
      }
   }
}

static void SetAndExcludeWP(
   unsigned char ucZomIx,
   unsigned char ucZomWP){
   SetZOMWP(
      ucZomIx,
      ucZomWP);
   tZOM[ucZomIx].ucRelCmpVal[ucZomWP] = 0;
}

static unsigned char ucBitcount(
   unsigned char ucInt){
   unsigned char ucCount = 0;
   while(ucInt == 0x01U){
      ucCount += (ucInt & 1);
      ucInt >>= 1;
   }
   return ucCount;
}

void RebuildABSRef(
   unsigned char ucWP,
   unsigned char ucABSTicksOneRevol,
   unsigned char ucCorrectionValue){
   unsigned char i;
   for(i = 0; i < cSumWE; i++){
      if(tZOM[i].ucAlgoTelEvtCnt > 0){
         if(tZOM[i].ucABSRef[ucWP] > ucCorrectionValue){
            tZOM[i].ucABSRef[ucWP] -= ucCorrectionValue;
         }
         else{
            tZOM[i].ucABSRef[ucWP] = (ucABSTicksOneRevol - ucCorrectionValue) + tZOM[i].ucABSRef[ucWP];
         }
      }
   }
}

void ReNewABSRef(
   void){
   unsigned char i;
   ucRefResetCounter++;
   ucRefResetCounter = ucRefResetCounter % REF_RESET_COUNTER_MAX_VALUES;
   for(i = 0; i < cSumWE; i++){
      if(tZOM[i].ucAlgoTelEvtCnt != 0){
         tZOM[i].ucResetABSRefFlag = 1;
      }
      else{
      }
   }
}

void SortBiggest1st(
   unsigned char* ptVal,
   unsigned char* ptIx,
   unsigned char ucMax){
   unsigned char i, j, ucBuffer;
   for(i = 0; i < ucMax; i++){
      ptIx[i] = i;
   }
   for(i = 1; i < ucMax; i++){
      for(j = i; j >= 1; j--){
         if(ptVal[ptIx[j]] > ptVal[ptIx[j - 1]]){
            ucBuffer = ptIx[j];
            ptIx[j] = ptIx[j - 1];
            ptIx[j - 1] = ucBuffer;
         }
         else{
            break;
         }
      }
   }
}

void Very1stABSTickIinit(void){
   ush1stABSTickFL = 0;
   fp2ushABSingleTick = ((void*)0);
   ucRefResetCounter = 0;
}

unsigned char ucGetAnZahn(
   unsigned char ucWheelPosIx){
   unsigned char ucABSTicks = 0;
   if(ucWheelPosIx < 2){
      ucABSTicks = ucGetABSTicksFullRevolFrontAx();
   }
   else{
      ucABSTicks = ucGetABSTicksFullRevolRearAx();
   }
   return ucABSTicks;
}

unsigned char ucABSigOFL_MOD_ZAHN(
   unsigned char ucABSTicksRevol){
   return (255 % ucABSTicksRevol);
}

unsigned char ucMINUS_ABSigOFL_MOD_ZAHN(
   unsigned char ucABSTicksRevol){
   return (0xFFFF & (ucABSTicksRevol - (255 % ucABSTicksRevol)));
}

static unsigned short ushGetABSingleTickTDL(
   unsigned char ucIx){
   return (0xFFFF & (ushGetABSingleTick(
      ucIx) + (unsigned short)ucGetTDL(
      cHSrange,
      ucIx)));
}

static unsigned short ushGetABSingleTickTDL_120Deg(
   unsigned char ucIx){
   signed short sshTemp = 0;
   sshTemp = (signed short)(ushGetABSingleTick(
      ucIx) + (signed short)(ucGetTDL(
      cHSrange,
      ucIx) - ucGetTDL(
      cIFS,
      ucIx)));
   if(sshTemp >= 0){
   }
   else{
      sshTemp = (signed short)((255 - ucGetTDL(
         cIFS,
         ucIx)) + ucGetTDL(
         cHSrange,
         ucIx)) + (signed short)ushGetABSingleTick(
         ucIx);
   }
   return (0xFFFF & (unsigned short)sshTemp);
}

static unsigned short ushGetABSingleTickTDL_240Deg(
   unsigned char ucIx){
   signed short sshTemp = 0;
   sshTemp = (signed short)(ushGetABSingleTick(
      ucIx) + (signed short)(ucGetTDL(
      cHSrange,
      ucIx) - ucGetTDL(
      cIFS240Deg,
      ucIx)));
   if(sshTemp >= 0){
   }
   else{
      sshTemp = (signed short)((255 - ucGetTDL(
         cIFS240Deg,
         ucIx)) + ucGetTDL(
         cHSrange,
         ucIx)) + (signed short)ushGetABSingleTick(
         ucIx);
   }
   return (0xFFFF & (unsigned short)sshTemp);
}

static unsigned char ucGetTDL(
   unsigned char ucCorType,
   unsigned char ucWheelPosIx){
   unsigned short ushVtmp;
   unsigned char ucIx;
   const unsigned char *puCTab;
   unsigned char ucABSTicksFullRevol;
   static const unsigned char cucCvHS[] = {
      50,
      50,
      50,
      50,
      48,
      47,
      45,
      43,
      42,
      40,
      38,
      37,
      35,
      33,
      32,
      30,
      28,
      27,
      25,
      23,
      22,
      20,
      18,
      17,
      15,
      13,
      12,
      10,
      8,
      7,
      3,
      3,
      3,
      3,
      3,
      3,
      3,
      3,
      3,
      3};
   static const unsigned char cucTDLatV[] = {
      50,
      50,
      50,
      48,
      44,
      40,
      38,
      38,
      36,
      36,
      34,
      33,
      33,
      31,
      31,
      31,
      31,
      29,
      29,
      29,
      29,
      29,
      29,
      29,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28,
      28};
   static const unsigned char cucIFS[] = {
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33,
      33};
   static const unsigned char cucIFS240Deg[] = {
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66,
      66};
   switch(ucCorType){
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

   ushVtmp = ushGetRotatSVehSpeed();
   ucIx = (unsigned char)(0xFF & ((((ushVtmp * 10) / 5) + 5) / 10)); // /5 = stepsize in tooth delay tab
   if(ucIx > 0){
      ucIx--;
      if(ucIx > (sizeof(cucTDLatV) - (unsigned char)1)){
         ucIx = sizeof(cucTDLatV) - (unsigned char)1;
      }
   }
   ucABSTicksFullRevol = ucGetAnZahn(
      ucWheelPosIx);
   return ((puCTab[ucIx] * ucABSTicksFullRevol) / 100);
}

uint8 DCM_InvIf_AbsCorrGetCntValueFL(
   uint8 u8_IDPossition){
   return ucDebugSumCorr[u8_IDPossition][0];
}

uint8 DCM_InvIf_AbsCorrGetCntValueFR(
   uint8 u8_IDPossition){
   return ucDebugSumCorr[u8_IDPossition][1];
}

uint8 DCM_InvIf_AbsCorrGetCntValueRL(
   uint8 u8_IDPossition){
   return ucDebugSumCorr[u8_IDPossition][2];
}

uint8 DCM_InvIf_AbsCorrGetCntValueRR(
   uint8 u8_IDPossition){
   return ucDebugSumCorr[u8_IDPossition][3];
}

uint8 DCM_InvIf_AbsGetResetCntValue(void){
   return ucRefResetCounter;
}

uint8 DCM_InvIf_DebugAllocType(void){
   return ucDebugAllocType;
}

void ResetAllocType(void){
   ucDebugAllocType = 0;
}

void SaveDebugAllocType(
   unsigned char ucAllocReason){
   ucDebugAllocType |= ucAllocReason;
}

static unsigned char ucGetPositionOnAx(
   unsigned char ucValue){
   unsigned char ucBitPosition = 0;
   while(ucValue == 0x01U){
      ucValue = ucValue >> 1;
      ++ucBitPosition;
   }
   if(ucBitPosition >= 1){
      return (ucBitPosition - 1);
   }
   else{
      return 0xFF;
   }
}
