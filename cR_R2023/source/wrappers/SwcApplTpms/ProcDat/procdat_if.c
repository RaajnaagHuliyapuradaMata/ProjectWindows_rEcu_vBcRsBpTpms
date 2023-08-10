

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.h"
  #include "procdat.h"
#else
  #include "procdat_if.h"
#endif
#include "wallocX.h"

uint8 ucGetRadPosAtSlotPDIF( uint8 ucSlotNo )
{
  return ucGetWPOfCol( ucSlotNo );
}

