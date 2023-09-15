
#ifndef SCHM_CANTRCV_30_TJA1043_H
#define SCHM_CANTRCV_30_TJA1043_H

#include "SchM.hpp"

#define CANTRCV_30_TJA1043_EXCLUSIVE_AREA_0   (SCHM_EA_SUSPENDALLINTERRUPTS)

#define SCHM_CANTRCV_30_TJA1043_INSTANCE_0    (0U)

#define SchM_Enter_CanTrcv_30_Tja1043(ExclusiveArea) \
   SCHM_ENTER_EXCLUSIVE(ExclusiveArea)

#define SchM_Exit_CanTrcv_30_Tja1043(ExclusiveArea) \
   SCHM_EXIT_EXCLUSIVE(ExclusiveArea)

extern void SchM_Enter_CanTrcv_30_Tja1043_CANTRCV_30_TJA1043_EXCLUSIVE_AREA_0(void);
extern void SchM_Exit_CanTrcv_30_Tja1043_CANTRCV_30_TJA1043_EXCLUSIVE_AREA_0(void);

#endif

