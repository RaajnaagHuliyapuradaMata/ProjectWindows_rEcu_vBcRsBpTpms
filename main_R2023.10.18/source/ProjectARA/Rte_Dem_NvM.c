#include "Std_Types.hpp"

#include "Rte_Nvm_Type.hpp"
#include "Rte_Dem_Type.hpp"
#include "Rte_Dem.hpp"

Std_ReturnType NvM_Rn_SetWriteAllTrigger(uint16 ushBlockNr, boolean bSet)
{
  if(bSet == TRUE)
  {
    Memstack_SetEcuNvMRamBlockStatus(ushBlockNr);
  }
   return E_OK;
}
