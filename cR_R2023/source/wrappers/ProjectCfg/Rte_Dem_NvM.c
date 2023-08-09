

#include "Rte_Nvm_Type.h"
#include "Rte_Dem_Type.h"
#include "Rte_Dem.h"

Std_ReturnType NvM_Rn_SetWriteAllTrigger(uint16 ushBlockNr, boolean bSet)
{
  if (bSet == TRUE)
  {
    Memstack_SetEcuNvMRamBlockStatus(ushBlockNr);
  }
  return E_OK;
}
