
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dem_EventStatus.h"

Std_ReturnType Dem_GetIndicatorStatus(uint8 IndicatorId, Dem_IndicatorStatusType* IndicatorStatus)
{
  return E_NOT_OK;
}

void Dem_IndicatorAttributeMainFunction(void)
{
}

void Dem_IndicatorAttributeInit(void)
{
}

void Dem_SetIndicatorDeActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{
}

void Dem_SetIndicatorActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{
}

void Dem_IndicatorAttribute_ConsistencyCheck(Dem_EventIdType EventId, uint16_least EventStatus )
{
}

Std_ReturnType Dem_SetWIRStatus (
        Dem_EventIdType EventId,
        boolean WIRStatus
)
{
    return E_NOT_OK;
}

