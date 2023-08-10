

#ifdef IBTCM_SW_ANPASSUNGEN
	#include "iTpms_Interface.h"
	#include "SwcApplTpms_Rte.h"
	#include "SwcApplTpms_NvM_If.h"
  #include "statemanagerx.h"
	#include "calibr.h"
	#include "calibrX.h"
#else
	#include "tss_stdx.h"

	#include "eecatc_ifx.h"
	#include "eecate_ifx.h"
	#include "procdatx.h"
	#include "statemanagerx.h"
	#include "statisticsx.h"
	#include "busmsgX.h"

	#include "calibr.h"
	#include "calibrX.h"
#endif

void CalibrSetPressureCAL(void)
{
  uint8 u8Press;
  uint8 u8LocalVarCodPlacardPress;

  u8LocalVarCodPlacardPress = GETucVarCodPlacardPressEE();

  if ( (u8LocalVarCodPlacardPress >=  cMINPOK) &&
       (u8LocalVarCodPlacardPress <=  cMAXPOK)    )

  {
    u8Press = u8LocalVarCodPlacardPress;
  }
  else
  {

    //u8Press = 136;
	  u8Press = 96;

    PUTucVarCodPlacardPressEE(u8Press);
  }

  InformWarnHandlerSM( 0, u8Press, u8Press);
}

