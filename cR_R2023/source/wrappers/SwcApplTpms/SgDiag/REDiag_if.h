

#ifndef REDiag_if_H
#define REDiag_if_H

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.h"
  #include "SwcApplTpms_Rte.h"
  #include "tss_stdx.h"
#else
  #include "tss_stdx.h"
  #include "sgdiagX.h"
  #include "applmainx.h"
#endif

extern uint16 MaxFailCounterInEE(void);

#endif
