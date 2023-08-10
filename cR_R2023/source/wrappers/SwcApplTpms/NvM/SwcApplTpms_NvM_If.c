

#include "iTpms_Interface.h"
#include "SwcApplTpms_Rte.h"
#include "TSS_StdX.h"
#include "SwcApplTpms_NvM.h"
#include "SwcApplTpms_NvM_If.h"
#include "TPMS_Global_Cfg.h"
#include "TPMS_Warning_Cfg.h"
#include "walloc_if.h"
#include "WallocX.h"
#include "UsWarnX.h"
#include "global.h"
#include "USCS.h"

uint8 GETucResetWarnPresLimitEE(void)
{
  static const uint8 cResetWarnPresLimit = 12U;
  return (cResetWarnPresLimit);
}

uint8 GETucPSollMinVaEE( void )
{
  STATIC const uint8  cPSollMinVaBarAbs = 72U;
  return( cPSollMinVaBarAbs );

}

uint8 GETucPSollMinHaEE( void )
{
  STATIC const uint8  cPSollMinHaBarAbs = 72U;
  return( cPSollMinHaBarAbs );
}

uint16 GETushSuppIdentFilterEE(void)
{

  const uint16 ushSuppIdentFilter = 0x0004U;
  return(ushSuppIdentFilter);
}

uint16 GETusMaxFolgeAusfallEE(void)
{
  STATIC const uint16  cMaxFolgeAusfall = 540U; // 9 minutes in 1 second counter //16U;
  return( cMaxFolgeAusfall );
}

#ifdef G_USE_PART_ER

uint8 GETucPartErTimerFactorEE(void)
{
  STATIC const uint8  cucPartErTimerFactor = 250U;//9U;
  return( cucPartErTimerFactor );
}
#endif //G_USE_PART_ER

uint8 GETucTimeTransmitIntervalCompletePeriodEE(void)
{
  STATIC const uint8 cucTimeTransmitIntervalCompletePeriod = 33U;

  return( cucTimeTransmitIntervalCompletePeriod );
}

uint8 GETucMinOffsetGXeEE(void)
{

  WAParameter LocaltWAPar;
  GetWADataEE(cWAParameter, (unsigned char *) &LocaltWAPar);

  return( LocaltWAPar.ucMinOffsetGXe );
}

uint8 GETucOffsetOverlapsGXeEE(void)
{

  WAParameter LocaltWAPar;
  GetWADataEE(cWAParameter, (unsigned char *) &LocaltWAPar);

  return( LocaltWAPar.ucOffsetOverlapsGXe );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

uint8 GETucMaxStoersenderZeitMinutenEE( void )
{

  STATIC const uint8  cucMaxStoersenderZeitMinuten = 10;

  return( cucMaxStoersenderZeitMinuten );
}

boolean GETbTransportModeEE(void)
{
  boolean l_bRet;

  l_bRet = FALSE;
  return(l_bRet);

}

boolean GETbTabCalRequestEE(void)
{
  boolean l_bRet;
  l_bRet = FALSE;
  return(l_bRet);

}
#endif

