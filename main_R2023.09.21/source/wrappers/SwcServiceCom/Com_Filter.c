#include "Std_Types.hpp"

#include "Com_Prv.hpp"

#if(defined(COM_TxFilters) || defined(COM_RxFilters))
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(boolean, COM_CODE) Com_Filter( VAR(uint32, AUTOMATIC) NewVal, VAR(uint8, AUTOMATIC) Algorithm
   ,     VAR(Com_FilterType, AUTOMATIC) FilterIndex, VAR(boolean,AUTOMATIC) CallContext_b )
{

   VAR(boolean, AUTOMATIC) State;

    State = ((Algorithm == COM_ALWAYS) ? COM_TRUE : COM_FALSE);

   switch(Algorithm)
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
           if(State)
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
         State = ((COM_GET_NEGMINMAX(FilterIndex).Min <= (sint32)NewVal) && ((sint32)NewVal <= COM_GET_NEGMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_NEWISOUTSIDE_POS
     case COM_NEW_IS_OUTSIDE_POS:
         State = ((NewVal < COM_GET_POSMINMAX(FilterIndex).Min) || (NewVal > COM_GET_POSMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_NEWISOUTSIDE_NEG
     case COM_NEW_IS_OUTSIDE_NEG:
         State = (((sint32)NewVal < COM_GET_NEGMINMAX(FilterIndex).Min) || ((sint32)NewVal > COM_GET_NEGMINMAX(FilterIndex).Max));
         break;
#endif

#ifdef COM_F_ONEEVERYN
     case COM_ONE_EVERY_N:
         State = (COM_GET_ONEEVERYN(FilterIndex).Occurrence == COM_GET_ONEEVERYN(FilterIndex).Offset);

         COM_GET_ONEEVERYN(FilterIndex).Occurrence += ((CallContext_b != COM_FALSE) ? 1u : 0u);

         COM_GET_ONEEVERYN(FilterIndex).Occurrence = ((COM_GET_ONEEVERYN(FilterIndex).Occurrence == COM_GET_ONEEVERYN(FilterIndex).Period)
                                                            ? 0 : COM_GET_ONEEVERYN(FilterIndex).Occurrence);
            break;
#endif

     default:

            break;
   }

#ifndef COM_F_ONEEVERYN
  (void)CallContext_b;
#endif
    return State;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

