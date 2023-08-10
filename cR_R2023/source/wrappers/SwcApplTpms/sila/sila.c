

#ifdef IBTCM_SW_ANPASSUNGEN
	#include "iTpms_Interface.h"
	#include "SwcApplTpms_Rte.h"
	#include "SilaX.h"
	#include "sila.h"
#else
	#include "SilaX.h"
	#include "sila.h"
	#include "transmitX.h"
	#include "eecata2_ifX.h"
	#include "applmainX.h"
	
	#include "testvi.h"
	#include "testviX.h"
#endif

STATIC tSilaStateType ucSilaState;
STATIC tSilaStateType ucSilaStateOut;
STATIC tSilaStateType ucSilaStateInt;

void SilaInit(void)
{
  ucSilaState    = SILA_STATE_NORMAL_OFF;
  ucSilaStateOut = SILA_STATE_NORMAL_OFF;
  ucSilaStateInt = SILA_STATE_NORMAL_OFF;
}

void SilaPutState(tSilaStateType ucState)
{
  if(    (ucSilaStateInt == SILA_STATE_MALFUNCTIONFLASH)
      && (ucState == SILA_STATE_PERMANENT_ON)            )
  {

  }
  else
  {
    ucSilaStateInt = ucState;
  }
}

tSilaStateType SilaGetState(void)
{
  return( ucSilaStateOut );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void SilaKL15On(void)
{
  ucSilaState = SILA_STATE_CHECK;
  ucSilaStateOut = SILA_STATE_NORMAL_OFF;
  ucSilaStateInt = SILA_STATE_NORMAL_OFF;
}
#endif

void  SilaTask(void)
{
  ucSilaStateOut = ucSilaStateInt;
}
