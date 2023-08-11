

#ifndef DEM_CFG_DTCID_H
#define DEM_CFG_DTCID_H

#include "Dem_Cfg_EventId.h"

#define DEM_CFG_EVCOMB_DISABLED       1u
#define DEM_CFG_EVCOMB_ONSTORAGE      2u
#define DEM_CFG_EVCOMB_ONRETRIEVAL    3u
#define DEM_CFG_EVCOMB            DEM_CFG_EVCOMB_DISABLED

#define DEM_DTCID_INVALID           0u
#define DEM_DTCID_COUNT             34u
#define DEM_DTCID_ARRAYLENGTH       (DEM_DTCID_COUNT+1u)

#define DemConf_DemDTCClass_DemDTC_DTC_0x9CC055                      1u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60188                      2u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60129                      3u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60929                      4u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60329                      5u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60429                      6u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60529                      7u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60629                      8u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60729                      9u
#define DemConf_DemDTCClass_DemDTC_DTC_0xd60829                      10u
#define DemConf_DemDTCClass_DemDTC_DTC_0x5000a2                      11u
#define DemConf_DemDTCClass_DemDTC_DTC_0x5000a3                      12u
#define DemConf_DemDTCClass_DemDTC_DTC_0x500042                      13u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560116                      14u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560131                      15u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560149                      16u
#define DemConf_DemDTCClass_DemDTC_DTC_0x56014b                      17u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560216                      18u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560231                      19u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560249                      20u
#define DemConf_DemDTCClass_DemDTC_DTC_0x56024b                      21u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560316                      22u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560331                      23u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560349                      24u
#define DemConf_DemDTCClass_DemDTC_DTC_0x56034b                      25u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560416                      26u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560431                      27u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560449                      28u
#define DemConf_DemDTCClass_DemDTC_DTC_0x56044b                      29u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560504                      30u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560531                      31u
#define DemConf_DemDTCClass_DemDTC_DTC_0x56064a                      32u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560793                      33u
#define DemConf_DemDTCClass_DemDTC_DTC_0x560929                      34u

#define DEM_DTCGROUPID_INVALID           0u
#define DEM_DTCGROUPID_COUNT             1u
#define DEM_DTCGROUPID_ARRAYLENGTH       (DEM_DTCGROUPID_COUNT+1u)

// genInfo: for (EvCombination==OFF) the explicit mapping from dtcid to eventId is necessary, because an event may not be assigned to any DTC
#define  DEM_MAP_EVENTID_DTCID   \
const Dem_DtcIdType Dem_MapEventIdToDtcId[DEM_EVENTID_ARRAYLENGTH] = \
{ \
   DEM_DTCID_INVALID \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x500042   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x5000a2   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x5000a3   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560116   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560131   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560149   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x56014b   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560216   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560231   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560249   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x56024b   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560316   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560331   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560349   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x56034b   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560416   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560431   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560449   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x56044b   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560504   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560531   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x56064a   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560793   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x560929   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0x9CC055   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60129   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60188   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60329   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60429   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60529   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60629   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60729   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60829   \
   ,DemConf_DemDTCClass_DemDTC_DTC_0xd60929   \
};

#define DEM_MAP_DTCGROUPID_DTCID \
{ {0u,0u}\
 ,{DemConf_DemDTCClass_DemDTC_DTC_0x9CC055 , DemConf_DemDTCClass_DemDTC_DTC_0x560929}	\
}

#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)

#define DEM_MAP_DTCID_EVENTID        \
const Dem_MapDtcIdToEventIdType  Dem_MapDtcIdToEventId[DEM_DTCID_ARRAYLENGTH] = \
{ \
   DEM_EVENTID_INVALID \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x9CC055_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60188_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60129_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60929_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60329_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60429_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60529_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60629_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60729_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0xd60829_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x5000a2_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x5000a3_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x500042_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560116_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560131_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560149_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x56014b_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560216_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560231_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560249_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x56024b_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560316_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560331_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560349_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x56034b_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560416_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560431_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560449_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x56044b_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560504_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560531_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x56064a_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560793_Event  \
   ,DemConf_DemEventParameter_EventParameter_DTC_0x560929_Event  \
};

#else

#define DEM_MAP_DTCID_EVENTID        \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x9CC055[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x9CC055_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60188[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60188_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60129[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60129_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60929[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60929_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60329[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60329_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60429[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60429_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60529[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60529_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60629[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60629_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60729[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60729_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60829[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0xd60829_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a2[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x5000a2_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a3[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x5000a3_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x500042[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x500042_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560116[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560116_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560131[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560131_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560149[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560149_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x56014b[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x56014b_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560216[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560216_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560231[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560231_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560249[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560249_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x56024b[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x56024b_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560316[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560316_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560331[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560331_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560349[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560349_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x56034b[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x56034b_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560416[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560416_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560431[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560431_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560449[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560449_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x56044b[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x56044b_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560504[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560504_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560531[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560531_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x56064a[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x56064a_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560793[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560793_Event \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DTC_0x560929[] = { \
   DemConf_DemEventParameter_EventParameter_DTC_0x560929_Event \
}; \
 \
 \
 \
const Dem_MapDtcIdToEventIdType  Dem_MapDtcIdToEventId[DEM_DTCID_ARRAYLENGTH] = \
{ \
   { \
      NULL_PTR, \
      0u \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x9CC055[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x9CC055)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x9CC055[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60188[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60188)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60188[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60129[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60129)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60129[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60929[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60929)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60929[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60329[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60329)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60329[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60429[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60429)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60429[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60529[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60529)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60529[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60629[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60629)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60629[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60729[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60729)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60729[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60829[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60829)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0xd60829[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a2[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a2)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a2[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a3[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a3)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x5000a3[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x500042[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x500042)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x500042[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560116[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560116)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560116[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560131[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560131)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560131[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560149[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560149)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560149[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x56014b[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56014b)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56014b[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560216[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560216)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560216[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560231[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560231)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560231[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560249[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560249)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560249[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x56024b[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56024b)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56024b[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560316[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560316)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560316[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560331[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560331)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560331[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560349[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560349)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560349[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x56034b[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56034b)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56034b[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560416[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560416)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560416[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560431[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560431)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560431[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560449[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560449)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560449[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x56044b[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56044b)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56044b[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560504[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560504)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560504[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560531[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560531)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560531[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x56064a[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56064a)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x56064a[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560793[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560793)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560793[0])) \
   } \
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DTC_0x560929[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560929)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DTC_0x560929[0])) \
   } \
};

#endif

#endif

