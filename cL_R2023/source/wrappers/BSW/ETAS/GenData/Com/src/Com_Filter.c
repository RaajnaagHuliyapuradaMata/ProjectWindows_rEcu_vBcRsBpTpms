

#include "Com_Prv.h"

#ifdef COM_FILTERS

#if !(defined(COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX) || defined(COM_F_MASKEDNEWDIFFERSOLD) || \
       defined(COM_F_NEWISWITHIN_POS)  || defined(COM_F_NEWISWITHIN_NEG)   || defined(COM_F_NEWISOUTSIDE_POS) || \
       defined(COM_F_NEWISOUTSIDE_NEG) || defined(COM_F_ONEEVERYN))
#define COM_FILTER_C_FilterIndex_IS_NOT_USED
#endif

#if !(defined(COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX) || defined(COM_F_MASKEDNEWDIFFERSOLD) || \
       defined(COM_F_NEWISWITHIN_POS)  || defined(COM_F_NEWISWITHIN_NEG)   || defined(COM_F_NEWISOUTSIDE_POS) || \
       defined(COM_F_NEWISOUTSIDE_NEG))
#define COM_FILTER_C_NewVal_IS_NOT_USED
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
boolean Com_Filter(
                uint32              NewVal,
                uint8               Algorithm,
                Com_FilterType      FilterIndex,
                boolean             CallContext_b
                  )
{
    boolean     State;

#ifdef COM_FILTER_C_NewVal_IS_NOT_USED
    (void)NewVal;
#endif
#ifdef COM_FILTER_C_FilterIndex_IS_NOT_USED
    (void)FilterIndex;
#endif
#ifndef COM_F_ONEEVERYN
    (void)CallContext_b;
#endif

    State = (Algorithm == COM_ALWAYS);

    switch (Algorithm)
    {
#ifdef COM_F_MASKEDNEWEQUALSX
     case COM_MASKED_NEW_EQUALS_X:
         State = ((NewVal & COM_GET_MASK_X(FilterIndex).Mask) == COM_GET_MASK_X(FilterIndex).X_Val);
         break;
#endif

#ifdef COM_F_MASKEDNEWDIFFERSX
     case COM_MASKED_NEW_DIFFERS_X:
         State = ((NewVal & COM_GET_MASK_X(FilterIndex).Mask) != COM_GET_MASK_X(FilterIndex).X_Val);
         break;
#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD
     case COM_MASKED_NEW_DIFFERS_MASKED_OLD:
         State = ((NewVal & COM_GET_MASK(FilterIndex)) != (COM_GET_F_OLDVALUE(FilterIndex) & COM_GET_MASK(FilterIndex)));
         if (State)
         {

             COM_GET_F_OLDVALUE(FilterIndex) = NewVal;
         }
         break;
#endif

#ifdef COM_F_NEWISWITHIN_POS
     case COM_NEW_IS_WITHIN_POS:
         State = ((COM_GET_POSMINMAX(FilterIndex).Min <= NewVal) && (NewVal <= COM_GET_POSMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_NEWISWITHIN_NEG
     case COM_NEW_IS_WITHIN_NEG:
         State = ((COM_GET_NEGMINMAX(FilterIndex).Min <= (sint32)NewVal) &&
                  ((sint32)NewVal <= COM_GET_NEGMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_NEWISOUTSIDE_POS
     case COM_NEW_IS_OUTSIDE_POS:
         State = ((NewVal < COM_GET_POSMINMAX(FilterIndex).Min) ||
                  (NewVal > COM_GET_POSMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_NEWISOUTSIDE_NEG
     case COM_NEW_IS_OUTSIDE_NEG:
         State = (((sint32)NewVal < COM_GET_NEGMINMAX(FilterIndex).Min) ||
                  ((sint32)NewVal > COM_GET_NEGMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_ONEEVERYN
     case COM_ONE_EVERY_N:
         State = (COM_GET_ONEEVERYN(FilterIndex).Occurrence == COM_GET_ONEEVERYN(FilterIndex).Offset);

         COM_GET_ONEEVERYN(FilterIndex).Occurrence += (CallContext_b ? COM_ONE : COM_ZERO);

         COM_GET_ONEEVERYN(FilterIndex).Occurrence =
                 ((COM_GET_ONEEVERYN(FilterIndex).Occurrence == COM_GET_ONEEVERYN(FilterIndex).Period) ?
                   COM_ZERO : COM_GET_ONEEVERYN(FilterIndex).Occurrence);
         break;
#endif

     default:
         break;
    }

    return State;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif

