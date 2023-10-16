

#ifndef _RTE_DEM_TYPE_H_
#define _RTE_DEM_TYPE_H_

#include "types.hpp"

#define DEM_UDS_STATUS_TF      0x01   //bit 0: TestFailed
#define DEM_UDS_STATUS_TFTOC   0x02   //bit 1: TestFailedThisOperationCycle
#define DEM_UDS_STATUS_PDTC    0x04   //bit 2: PendingDTC
#define DEM_UDS_STATUS_CDTC    0x08   //bit 3: ConfirmedDTC
#define DEM_UDS_STATUS_TNCSLC  0x10   //bit 4: TestNotCompletedSinceLastClear
#define DEM_UDS_STATUS_TFSLC   0x20   //bit 5: TestFailedSince-LastClear
#define DEM_UDS_STATUS_TNCTOC  0x40   //bit 6: TestNotCompletedThisOperationCycle
#define DEM_UDS_STATUS_WIR     0x80   //bit 7: WarningIndicator-Requested

#define DEM_TEMPORARILY_DEFECTIVE 0x01 //Bit 0: Temporarily Defective (corresponds to 0 < FDC < 127)
#define DEM_FINALLY_DEFECTIVE     0x02 //Bit 1: finally Defective (corresponds to FDC = 127)
#define DEM_TEMPORARILY_HEALED    0x04 //Bit 2: temporarily healed (corresponds to -128 < FDC < 0)
#define DEM_TEST_COMPLETE         0x08 //Bit 3: Test complete (corresponds to FDC = -128 or FDC = 127)
#define DEM_DTR_UPDATE            0x10 //Bit 4: DTR Update (= Test complete && Debouncing complete && enable conditions / storage

// Values for Dem_DTCOriginType. Used to define the location of the events. The definition and use of the different memory types is OEM-specific.
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY   0x01    // Event information located in the primary memory
#define DEM_DTC_ORIGIN_MIRROR_MEMORY    0x02    // Event information located in the mirror memory
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY 0x03    // The Event information is located in the permanent memory
//DEM_DTC_ORIGIN_USERDEFINED_MEMORY_XX 0xXX Event information located in the user defined memory, where XX is the configured DemUserDefined-MemoryIdentifier in hexadecimal
//RST note: secondary memory is not defined by Huf but generated module Dem_clear.c uses this define, so it must be defined here:
#define DEM_DTC_ORIGIN_SECONDARY_MEMORY 0x04

// Description: Indicator mode used by Dem_GetIndicatorStatus().
typedef enum{
  DEM_INDICATOR_OFF         = 0x00, // Indicator off mode
  DEM_INDICATOR_CONTINUOUS  = 0x01, // Indicator continuously on mode
  DEM_INDICATOR_BLINKING    = 0x02, // Indicator blinking mode
  DEM_INDICATOR_BLINK_CONT  = 0x03, // Indicator blinking or continuously on mode
  DEM_INDICATOR_SLOW_FLASH  = 0x04, // Indicator slow flashing mode
  DEM_INDICATOR_FAST_FLASH  = 0x05, // Indicator fast flashing mode
  DEM_INDICATOR_ON_DEMAND   = 0x06, // Indicator on-demand mode
  DEM_INDICATOR_SHORT       = 0x07  // Indicator short mode
}Dem_IndicatorStatusType;

// Description: This type contains all definitions to control an internal debounce counter/timer via the function Dem_ResetEventDebounceStatus().
typedef enum{
  DEM_DEBOUNCE_STATUS_FREEZE  = (uint8)0x00, //Freeze the internal debounce counter/timer.
  DEM_DEBOUNCE_STATUS_RESET   = (uint8)0x01  //Reset the internal debounce counter/timer.
  //0x02 - 0xFF reserved
}Dem_DebounceResetStatusType;

// (Re-)Initialization reason returned by the callback <Module>_DemInitMonitorFor<EventName>().
typedef enum{
  DEM_INIT_MONITOR_CLEAR              = (uint8)0x01, //Event was cleared and all internal values and states are reset.
  DEM_INIT_MONITOR_RESTART            = (uint8)0x02, //Operation cycle of the event was (re-)started.
  DEM_INIT_MONITOR_REENABLED          = (uint8)0x03, //Enable conditions or DTC settings re-enabled.
  DEM_INIT_MONITOR_STORAGE_REENABLED  = (uint8)0x04  //Storage condition reenabled.
}Dem_InitMonitorReasonType;

typedef enum{
  DEM_EVENT_STATUS_PASSED                = (uint8)0x00,   //Monitor reports qualified test result passed.
  DEM_EVENT_STATUS_FAILED                = (uint8)0x01,   //Monitor reports qualified test result failed.
  DEM_EVENT_STATUS_PREPASSED             = (uint8)0x02,   //Monitor reports nonqualified test result pre-passed (debounced Dem-internally).
  DEM_EVENT_STATUS_PREFAILED             = (uint8)0x03,   //Monitor reports nonqualified test result pre-failed (debounced Dem-internally).
  DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED = (uint8)0x04    //Monitor triggers the storage of Extended-DataRecords and Freeze-Frames ON_FDC_THRESHOLD.
}Dem_EventStatusType;

typedef enum{
  DEM_DTC_FORMAT_OBD     = (uint8)0
   ,  DEM_DTC_FORMAT_UDS     = (uint8)1
   ,  DEM_DTC_FORMAT_J1939   = (uint8)2
}Dem_DTCFormatType;

// Used to return the status of Dem_<...>ClearDTC.
typedef enum{
  DEM_CLEAR_OK                   = (uint8)0x00, //DTC successfully cleared
  DEM_CLEAR_WRONG_DTC            = (uint8)0x01, //DTC value not existing (in this format)
  DEM_CLEAR_WRONG_DTCORIGIN      = (uint8)0x02, //Wrong DTC origin
  DEM_CLEAR_FAILED               = (uint8)0x03, //DTC clearing failed
  DEM_CLEAR_PENDING              = (uint8)0x04, //The DTC clearing is performed asynchronously and still pending. The caller can retry later.
  DEM_CLEAR_BUSY                 = (uint8)0x05, //DTC not cleared, as another clearing process is in progress. The caller can retry later.
  DEM_CLEAR_MEMORY_ERROR         = (uint8)0x06  //An error occurred during erasing a memory location (e.g. if Dem-ClearDTCBehavior in Dem is set to
                                                //DEM_CLRRESP_NONVOLATILE_FINISH and erasing of non-volatile-block failed).
}Dem_ReturnClearDTCType;

typedef enum{
  DEM_CYCLE_STATE_START = (uint8)0x00,  //Start/restart the operation cycle
  DEM_CYCLE_STATE_END   = (uint8)0x01   //End the operation cycle
}Dem_OperationCycleStateType;

typedef uint16 Dem_EventIdType;
typedef uint8 Dem_IndicatorIdType;
typedef uint8 Dem_DebouncingStateType;
typedef uint8 Dem_UdsStatusByteType;
typedef uint8 Dem_DTCOriginType;
typedef uint8 Dem_OperationCycleIdType;

extern Std_ReturnType NvM_Rn_SetWriteAllTrigger(uint16 ushBlockNr, boolean bSet);
#endif
