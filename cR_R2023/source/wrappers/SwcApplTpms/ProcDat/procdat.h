

#ifndef _procdat_H
#define _procdat_H

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.h"
  #include "SwcApplTpms_Rte.h"
  #include "tss_stdx.h"
#else
  #include "tss_stdx.h"
  #include "procdat_cfg.h"
  #include "ring_buffer_X.h"
#endif

extern uint8 ucGetRadPosAtSlotPDIF(uint8 ucSlotNo);

#endif
