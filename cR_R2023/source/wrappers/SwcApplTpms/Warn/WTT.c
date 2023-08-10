

#include "iTpms_Interface.h"
#include "SwcApplTpms_Rte.h"
#include "SwcApplTpms_NvM_If.h"
#include "global.h"
#include "uswarn.h"
#include "WnTypePar.h"

unsigned char bTW( struct LocalWarnDat *ptLWD, unsigned char ucWarnCfg)
{
  unsigned char ucRet = 0;
  sint8 S8_TempThreshold;
  uint8 U8_CurrentWarnBitState;
  uint8 LocalWarnCfgToRemoveWarning;

  LocalWarnCfgToRemoveWarning = ucWarnCfg;

  S8_TempThreshold = NvM3_GETucVarCodTemperatureWarningThresEE();
  U8_CurrentWarnBitState = ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);

  if (U8_CurrentWarnBitState == 0)
  {

    if (ptLWD->tHFD.tHF.scTWE >= S8_TempThreshold)
    {

      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
    }
  }

  else
  {

    if (ptLWD->tHFD.tHF.scTWE < (S8_TempThreshold - 10))
    {

      ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
      ucRet = 0;
    }

    else
    {

      ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
    }
  }

  //if(ptLWD->tHFD.tHF.scTWE >= S8_TempThreshold)
  //{
  //
  //  ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
  //}
  //else
  //{
  //  ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucTWxc);
  //  ucRet = 0;
  //}

  return(ucRet);
}
