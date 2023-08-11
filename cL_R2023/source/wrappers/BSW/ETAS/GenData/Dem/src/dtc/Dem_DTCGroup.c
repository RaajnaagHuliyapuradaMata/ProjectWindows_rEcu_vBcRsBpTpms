

#include "Dem_Dcm_Internal.h"
#include "Dem_DTCGroup.h"

#include "Dem_DTCs.h"

#define DEM_START_SEC_CONST
#include "Dem_MemMap.h"
DEM_ARRAY_DEFINE_CONST(Dem_DtcGroupParam, Dem_AllDTCGroupsParam, DEM_DTCGROUPID_ARRAYLENGTH, DEM_CFG_DTCGROUPPARAMS);
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
Dem_DTCGroupIdType Dem_DtcGroupIdFromDtcGroupCode (Dem_DTCGroupType dtcGrpCode)
{
   Dem_DtcGroupIdIterator dtcGroupId;

   for (Dem_DtcGroupIdIteratorNew(&dtcGroupId);
        Dem_DtcGroupIdIteratorIsValid(&dtcGroupId);
        Dem_DtcGroupIdIteratorNext(&dtcGroupId))
   {
      if (Dem_DtcGroupGetCode(Dem_DtcGroupIdIteratorCurrent(&dtcGroupId)) == dtcGrpCode)
      {
         return Dem_DtcGroupIdIteratorCurrent(&dtcGroupId);
      }
   }
   return DEM_DTCGROUPID_INVALID;
}

void Dem_DtcsClearDtcInGroup(uint8 GroupId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr)
{
    Dem_DtcIdType dtcId;

    if (Dem_ClientClearMachinePtr->IsNewClearRequest)
    {
        Dem_DtcIdListIteratorNewFromDtcGroup(&(Dem_ClientClearMachinePtr->DtcIt), GroupId);
    }

    while (Dem_DtcIdListIteratorIsValid(&(Dem_ClientClearMachinePtr->DtcIt)))
    {
        dtcId = Dem_DtcIdListIteratorCurrent(&(Dem_ClientClearMachinePtr->DtcIt));
        Dem_ClearSingleDTC(dtcId, DTCOrigin, Dem_ClientClearMachinePtr);

        if (Dem_ClientClearMachinePtr->IsClearInterrupted)
        {
            return;
        }
        Dem_DtcIdListIteratorNext(&(Dem_ClientClearMachinePtr->DtcIt));
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
