
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dem_KL15Persistence.h"

#include "Dem.h"

static boolean Dem_Lok_KL15PersistenceIsStorageScheduled;

void Dem_KL15PersistenceMain(void)
{
    if (Dem_Lok_KL15PersistenceIsStorageScheduled)
    {
        Dem_Lok_KL15PersistenceIsStorageScheduled = FALSE;

    }
}

void Dem_KL15PersistenceScheduleStorage(void)
{
    Dem_Lok_KL15PersistenceIsStorageScheduled = TRUE;
}

Std_ReturnType Dem_KL15PersistenceImmediateStorage(void)
{
    Dem_Lok_KL15PersistenceIsStorageScheduled = FALSE;

    return 0;
}
