

#include "iTpms_Interface.h"
#include "SwcApplTpms_NvM_If.h"
#include "SwcApplTpms_Rte.h"
#include "SwcApplTpms_NvM.h"

#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_NvInitialized(uint8 ucData);
void NvM_ReadData_NvInitialized(uint8 *ucpData);
#endif

#ifdef BUILD_WITH_UNUSED_FUNCTION
void NvM_WriteData_NvInitialized(uint8 ucData)
{
  WriteMember2Blocks  (10,1,&ucData );
}

void NvM_ReadData_NvInitialized(uint8 *ucpData)
{
  ReadBlock2Member (10,1,ucpData);
}
#endif

void NvM_WriteData_ECUDefect(uint8 ucData)
{
  WriteMember2Blocks  (10,2,&ucData );
}

void NvM_ReadData_ECUDefect(uint8 *ucpData)
{
  ReadBlock2Member (10,2,ucpData);
}

