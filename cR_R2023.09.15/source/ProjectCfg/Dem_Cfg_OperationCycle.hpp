

#ifndef DEM_CFG_OPERATIONCYCLE_H
#define DEM_CFG_OPERATIONCYCLE_H

#include "rba_DiagLib_Bits8.hpp"
#include "rba_DiagLib_Bits16.hpp"
#include "rba_DiagLib_Bits32.hpp"

#define DEM_CFG_OPERATIONCYCLESTATUSSTORAGE         TRUE

#define DemConf_DemOperationCycle_DemOperationCycle_BUSACTIVE  0uL
#define DemConf_DemOperationCycle_DemOperationCycle_IGNITION  1uL
#define DemConf_DemOperationCycle_DemOperationCycle_POWER  2uL

#define DEM_OPERATIONCYCLE_COUNT      3

#if(DEM_OPERATIONCYCLE_COUNT <= 8)
typedef uint8 Dem_OperationCycleList;
#define DEM_OPERATIONCYCLE_SETBIT        rba_DiagLib_Bit8SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT      rba_DiagLib_Bit8ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET      rba_DiagLib_Bit8IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK       rba_DiagLib_Bit8Mask
#define DEM_OPERATIONCYCLE_SETBITMASK    rba_DiagLib_Bit8SetBitMask
#define DEM_OPERATIONCYCLE_MERGEBITMASK  rba_DiagLib_Bit8MergeBitmask
#define DEM_OPERATIONCYCLE_CLEARBITMASK  rba_DiagLib_Bit8ClearBitMask

#elif(DEM_OPERATIONCYCLE_COUNT <= 16)
typedef uint16 Dem_OperationCycleList;
#define DEM_OPERATIONCYCLE_SETBIT        rba_DiagLib_Bit16SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT      rba_DiagLib_Bit16ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET      rba_DiagLib_Bit16IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK       rba_DiagLib_Bit16Mask
#define DEM_OPERATIONCYCLE_SETBITMASK    rba_DiagLib_Bit16SetBitMask
#define DEM_OPERATIONCYCLE_MERGEBITMASK  rba_DiagLib_Bit16MergeBitmask
#define DEM_OPERATIONCYCLE_CLEARBITMASK  rba_DiagLib_Bit16ClearBitMask

#elif(DEM_OPERATIONCYCLE_COUNT <= 32)
typedef uint32 Dem_OperationCycleList;
#define DEM_OPERATIONCYCLE_SETBIT        rba_DiagLib_Bit32SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT      rba_DiagLib_Bit32ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET      rba_DiagLib_Bit32IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK       rba_DiagLib_Bit32Mask
#define DEM_OPERATIONCYCLE_SETBITMASK    rba_DiagLib_Bit32SetBitMask
#define DEM_OPERATIONCYCLE_MERGEBITMASK  rba_DiagLib_Bit32MergeBitmask
#define DEM_OPERATIONCYCLE_CLEARBITMASK  rba_DiagLib_Bit32ClearBitMask

#endif

#endif
