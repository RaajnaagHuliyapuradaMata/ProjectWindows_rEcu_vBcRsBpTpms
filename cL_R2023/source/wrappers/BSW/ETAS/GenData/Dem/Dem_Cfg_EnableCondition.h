

#ifndef DEM_CFG_ENABLECONDITION_H
#define DEM_CFG_ENABLECONDITION_H

#include "Std_Types.h"

#define DEM_CFG_ENABLECONDITION_ON    STD_ON
#define DEM_CFG_ENABLECONDITION_OFF   STD_OFF
#define DEM_CFG_ENABLECONDITION       DEM_CFG_ENABLECONDITION_OFF

#define DEM_ENABLECONDITION_COUNT         0u
#define DEM_ENABLECONDITION_ARRAYLENGTH   (DEM_ENABLECONDITION_COUNT)

#if (DEM_ENABLECONDITION_ARRAYLENGTH <= 8) \
	|| (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_OFF)
typedef uint8 Dem_EnCoList;
#elif (DEM_ENABLECONDITION_ARRAYLENGTH <= 16)
typedef uint16 Dem_EnCoList;
#elif (DEM_ENABLECONDITION_ARRAYLENGTH <= 32)
typedef uint32 Dem_EnCoList;
#else
#error DEM currently only supports up to 32 EnableConditions
#endif

#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)

#define DEM_ENCO_EventParameter_DTC_0x500042_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x5000a2_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x5000a3_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560116_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560131_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560149_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x56014b_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560216_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560231_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560249_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x56024b_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560316_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560331_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560349_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x56034b_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560416_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560431_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560449_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x56044b_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560504_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560531_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x56064a_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560793_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x560929_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0x9CC055_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60129_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60188_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60329_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60429_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60529_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60629_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60729_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60829_Event  (0u)
#define DEM_ENCO_EventParameter_DTC_0xd60929_Event  (0u)

#define DEM_CFG_ENCO_INITIALSTATE    (   0u \
                                      )

#endif

#endif

