

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.h"
  #include "SwcApplTpms_NvM_If.h"
  #include "SwcApplTpms_DTC_If.h"
  #include "cfg.h"
  #include "tss_stdx.h"
  #include "REDiag_if.h"
#else
  #include "REDiag_if.h"
  #include "errmemx.h"
  #include "eecata2_ifx.h"
  #include "cfg.h"
  #include "tss_stdx.h"
#endif

const uint8 ucWUDefectERRc[cAnzRad+1]=
{
  cZO_ERR_WS_DEFECT_FL,
  cZO_ERR_WS_DEFECT_FR,
  cZO_ERR_WS_DEFECT_RL,
  cZO_ERR_WS_DEFECT_RR,
  cZO_ERR_WS_DEFECT_XX
};

const uint8 ucWUFailERRc[cAnzRad+1] =
{
  cZO_ERR_WS_MISSING_FL,
  cZO_ERR_WS_MISSING_FR,
  cZO_ERR_WS_MISSING_RL,
  cZO_ERR_WS_MISSING_RR,
  cZO_ERR_WS_MISSING_XX
}
;

#ifdef js_ReHighTemperatureDiag_230312

const uint8 ucWUTemperatureERRc[cAnzRad+1] =
{
  cZO_ERR_WS_OVERTEMPERATURE_FL,
  cZO_ERR_WS_OVERTEMPERATURE_FR,
  cZO_ERR_WS_OVERTEMPERATURE_RL,
  cZO_ERR_WS_OVERTEMPERATURE_RR,
  cZO_ERR_WS_OVERTEMPERATURE_XX
}
;
#endif

const uint8 ucWULowLifeTimeERRc[cAnzRad+1] =
{
  cZO_ERR_WS_BATTERY_LOW_FL,
  cZO_ERR_WS_BATTERY_LOW_FR,
  cZO_ERR_WS_BATTERY_LOW_RL,
  cZO_ERR_WS_BATTERY_LOW_RR,
  cZO_ERR_WS_BATTERY_LOW_XX
}
;

uint16 MaxFailCounterInEE(void)
{
  return (GETusMaxFolgeAusfallEE());
}
