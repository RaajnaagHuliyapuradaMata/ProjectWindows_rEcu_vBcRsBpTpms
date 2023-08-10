

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.h"
  #include "iTPMS_Interface.h"
  #include "SwcApplTpms_NvM_If.h"
  #include "SwcApplTpms_Rte.h"
  #include "IDOM_IF.h"
  #include "IDOM_cfg.h"
  #include "state_fzzX.h"
  #include "statisticsX.h"
#else
  #include "IDOM_IF.h"
  #include "IDOM_cfg.h"
  #include "applmainX.h"
  #include "RSGuard_x.h"
  #include "state_fzzX.h"
  #include "statisticsX.h"
  #include "romdata_ifX.h"
#endif

static uint16 ushAlarmTimeInSec;

void StartIDOMAlarm(uint16 ushNrOfCurFF)
{
  if ( ((ushNrOfCurFF + ushAlarmTimeInSec) >= ushMaxTimeWithoutMsgInSec) &&
      (ushNrOfCurFF < ushMaxTimeWithoutMsgInSec) )
  {
    SetRelAlarmAlIDOMOS( ( 0xFFFF & (ushMaxTimeWithoutMsgInSec - ushNrOfCurFF) ), 0 );
  }
  else
  {
    SetRelAlarmAlIDOMOS( ushAlarmTimeInSec, 0 );
  }
}

void StopIDOMAlarm(void)
{
  CancelAlarmAlIDOMOS();

  ushAlarmTimeInSec = ushHFiAlarmTimeInSec;
}

void BreakIDOMAlarm(void)
{
  uint16 ushHelp;

#ifdef IBTCM_SW_ANPASSUNGEN
  uint8 u8AlarmStatus = FALSE;

  ushHelp = 0;

  u8AlarmStatus = GetAlarmAlIDOMOS(&ushHelp);

  if(FALSE != u8AlarmStatus)
  {

    ushAlarmTimeInSec = ushHelp;
  }
  else
  {

    ushAlarmTimeInSec = 0;
  }

  CancelAlarmAlIDOMOS();

#else
  ushHelp = ushBreakAlarmIDOMOS();

  if (ushHelp > 0)
  {
    ushAlarmTimeInSec = ushHelp;
  }
#endif
}

void GetIDOMInput(tIDOMInput * pIDOMInput)
{
  uint8 i = (unsigned char) 0;
  uint16 usMaxFF = (unsigned short) 0;

  for (i = 0; i < 4;i++)
  {
    if ( GETusFolgeAusfallCntSTATISTICS(i) > usMaxFF )
    {
      usMaxFF = GETusFolgeAusfallCntSTATISTICS(i);
    }
  }
  pIDOMInput->ucApplState = (unsigned char) bGetBitFahrzeugzustandFZZ( cRS_VTHRES );
  pIDOMInput->ushMaxFFCtVal = usMaxFF;
  pIDOMInput->ushCurBaseLevel = GetBaseLevel();
}

uint16 GetParaOffset(void)
{
  return ((uint16) GETucMinOffsetGXeEE());
}

uint16 GetParaOverlaps(void)
{
  return ((uint16)  GETucOffsetOverlapsGXeEE());
}
