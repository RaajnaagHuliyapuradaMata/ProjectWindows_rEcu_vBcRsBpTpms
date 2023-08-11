
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJEVTPROJECTEXTENSION_H
#define DEM_PRJEVTPROJECTEXTENSION_H

//#include "rba_DemObdBasic_Iumpr.h"
//#include "rba_DemObdBasic_Ratio.h"
//#include "rba_DemObdBasic.h"
//#include "Dem_Events.h"

DEM_INLINE void Dem_EvtProjectExtensionSetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus, uint8_least debAction)
{

//#if DEM_CFG_OBD_IUMPR
//   uint8 idxRatio;
//   Dem_EventIdType EventIDRef;
//   uint16 Numerator;
//   uint16 Denominator;
//   uint8 Group;
//   uint8 RatioStatus;

//
//   for (idxRatio = 0u; idxRatio < DEM_CFG_NUM_ALL_IUMPR_RATIOS; idxRatio++)
//   {
//      Dem_GetIUMPRRatioData(idxRatio, &Numerator, &Denominator, &EventIDRef, &Group);
//      if ((EventId == EventIDRef) && (Group == DEM_OBDIUMPR_GRP_EVAP)){
//         break;
//      }
//   }

//
//   if (idxRatio < DEM_CFG_NUM_ALL_IUMPR_RATIOS){
//      RatioStatus = rba_DemObdBasic_Iumpr_RatioSt(idxRatio);
//
//      if ((RatioStatus & (DEM_RATIO_STSMASK_NUMER_INCD | DEM_RATIO_STSMASK_NUMER_LOCKED)) == 0u && !Dem_EvtIsSuppressed(EventIDRef)){
//         rba_DemObdBasic_Iumpr_RatioNum(idxRatio)++;
//      }
//   } else {
//
//   }
//#endif
}

DEM_INLINE void Dem_ProjectExtensionRepIUMPRFaultDetect(Dem_RatioIdType RatioID)
{

//#if DEM_CFG_OBD_IUMPR
//   Dem_EventIdType EventIDRef;
//   uint16 Numerator;
//   uint16 Denominator;
//   uint8 Group;
//   uint8 RatioStatus;

//   Dem_GetIUMPRRatioData(RatioID, &Numerator, &Denominator, &EventIDRef, &Group);

//
//   if ((RatioID < DEM_CFG_NUM_ALL_IUMPR_RATIOS) && (Group == DEM_OBDIUMPR_GRP_EVAP)){
//      RatioStatus = rba_DemObdBasic_Iumpr_RatioSt(RatioID);
//
//      if (((RatioStatus & (DEM_RATIO_STSMASK_NUMER_INCD | DEM_RATIO_STSMASK_NUMER_LOCKED)) == 0u) && (!Dem_EvtIsSuppressed(EventIDRef))){
//         rba_DemObdBasic_Iumpr_RatioNum(RatioID)++;
//      }
//   } else {
//
//   }
//#endif
}
#endif
