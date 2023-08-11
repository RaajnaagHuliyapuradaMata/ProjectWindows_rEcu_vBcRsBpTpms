

#ifndef FIM_UTILS_H
#define FIM_UTILS_H

#include "FiM_Cfg.h"
#include "FiM_Priv_Data.h"
#include "rba_DiagLib_MemUtils.h"

#define FIM_MEMSET    RBA_DIAGLIB_MEMSET

#define FIM_USE_VAR(P)   ((void)(P))

#define FIM_PRIV_MIN(a, b)  ( ((a) < (b)) ? (a) : (b) )
#define FIM_PRIV_MAX(a, b)  ( ((a) > (b)) ? (a) : (b) )

#define FIM_LAST_FAILED_MASK        0x01u
#define FIM_LAST_FAILED_VALUE       0x01u
#define FIM_NOT_TESTED_MASK         0x40u
#define FIM_NOT_TESTED_VALUE        0x40u
#define FIM_TESTED_MASK             0x40u
#define FIM_TESTED_VALUE            0x00u
#define FIM_TESTED_AND_FAILED_MASK  0x41u
#define FIM_TESTED_AND_FAILED_VALUE 0x01u

#define FIM_INHIBITION_BITS_MASK    0x41u

#define FIM_PENDING_BITS_MASK       0x04u
#define FIM_PENDING_BITS_VALUE      0x04u

#define FIM_PRIV_ENTERLOCK_MONITOR()            SchM_Enter_FiM_Monitor_NoNest()
#define FIM_PRIV_EXITLOCK_MONITOR()             SchM_Exit_FiM_Monitor_NoNest()

#define FIM_PRIV_ENTERLOCK_STATUS()             SchM_Enter_FiM_Status_NoNest()
#define FIM_PRIV_EXITLOCK_STATUS()              SchM_Exit_FiM_Status_NoNest()

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

LOCAL_INLINE boolean FiM_Priv_IsInhibitionSet(uint8 statusByte_u8, FiM_InhibitionMaskType maskType_uo)
{
    boolean retVal_b = FALSE;

    switch (maskType_uo)
    {
        case FIM_CFG_LAST_FAILED:
            if ((statusByte_u8 & FIM_LAST_FAILED_MASK) == FIM_LAST_FAILED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_NOT_TESTED:
            if ((statusByte_u8 & FIM_NOT_TESTED_MASK) == FIM_NOT_TESTED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_TESTED:
            if ((statusByte_u8 & FIM_TESTED_MASK) == FIM_TESTED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_TESTED_AND_FAILED:
            if ((statusByte_u8 & FIM_TESTED_AND_FAILED_MASK) == FIM_TESTED_AND_FAILED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_FAILED_OR_NOT_TESTED:
            if (((statusByte_u8 & FIM_NOT_TESTED_MASK) == FIM_NOT_TESTED_VALUE)
                    || ((statusByte_u8 & FIM_LAST_FAILED_MASK) == FIM_LAST_FAILED_VALUE))
            {
                retVal_b = TRUE;
            }
            break;

        default:
            retVal_b = FALSE;
            break;
    }

    return retVal_b;
}

LOCAL_INLINE boolean FiM_Priv_IsInhibitionChanged(uint8 statusByteNew_u8, uint8 statusByteOld_u8,
        FiM_InhibitionMaskType maskType_uo, boolean* inhStatusNew_b)
{
    boolean inhStatusOld_b = FiM_Priv_IsInhibitionSet(statusByteOld_u8, maskType_uo);
    *inhStatusNew_b = FiM_Priv_IsInhibitionSet(statusByteNew_u8, maskType_uo);

    return (*inhStatusNew_b != inhStatusOld_b);
}

LOCAL_INLINE boolean FiM_Priv_IsInhMaskServ07Relevant(FiM_InhibitionMaskType maskType_uo)
{
    return ((maskType_uo == FIM_CFG_LAST_FAILED) || (maskType_uo == FIM_CFG_TESTED_AND_FAILED)
            || (maskType_uo == FIM_CFG_FAILED_OR_NOT_TESTED));
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif

