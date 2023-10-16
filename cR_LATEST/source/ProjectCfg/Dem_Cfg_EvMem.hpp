#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EvMem.hpp                                                 */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Dem_Cfg_Main.hpp"
#include "Dem_Cfg_DtcId.hpp"
#include "Dem_Cfg_Events.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_EVMEM_DISPLACEMENT_SUPPORTED                 TRUE

#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR          1u
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_FIFO             2u
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_CUST             3u
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_NONE             4u

#define DEM_CFG_EVMEM_MEMORY_DISPLACEMENT_STRATEGY           DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR

#define DEM_CFG_EVMEM_MIRROR_DISPLACEMENT_STRATEGY           DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR

#define DEM_CFG_EVMEM_STORAGE_TESTFAILED_SUPPORTED           TRUE

#define DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_STATUS_BYTE_BLOCK    1u
#define DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_EVENT_MEMORY         2u
#define DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE                      DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_STATUS_BYTE_BLOCK

#define DEM_CFG_EVMEM_OCCCOUNTER_TRIGGER_STSMASK             0u

#define DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED                FALSE
#define DEM_CFG_EVMEM_EXTENDED_DATA_ON_MIRROR_SUPPORTED      FALSE
#define DEM_CFG_EVMEM_EXTENDED_DATA_ON_PASSED_SUPPORTED      FALSE
#define DEM_CFG_EVMEM_TRIGGER_ON_FDC_SUPPORTED               FALSE

#define DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED                 TRUE

#define DEM_CFG_EVMEM_TESTCOMPLETE_TFC_SUPPORTED             FALSE

#define DEM_CFG_IMMEDIATE_NV_STORAGE_SUPPORTED               TRUE
#define DEM_CFG_IMMEDIATE_NV_STORAGE_LIMIT_SUPPORTED         TRUE
#define DEM_CFG_IMMEDIATE_NV_STORAGE_LIMIT                   1

#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY               10u

#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY             0u

#define DEM_DTC_ORIGIN_USERDEFINED_MEMORY                    0x0u

#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR                0u

#define DEM_CFG_EVMEM_MIRROR_ON_FAILED                       1u
#define DEM_CFG_EVMEM_MIRROR_ON_CLEAR                        2u
#define DEM_CFG_EVMEM_MIRROR                                 DEM_CFG_EVMEM_MIRROR_ON_CLEAR

#define DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED        FALSE

#define DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED                FALSE
#define DEM_CFG_EVMEM_MEMID_SHADOW                           DEM_CFG_EVMEM_MEMID_PRIMARY

#define DEM_CFG_EVMEM_SHADOW_ENTRIES_VISIBLE                 FALSE

#if(DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED || DEM_CFG_EVMEM_SHADOW_ENTRIES_VISIBLE)
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED               TRUE
#else
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED               FALSE
#endif
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED        DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED

#define DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP                  1u
#define DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN                2u
#define DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE            3u
#define DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP          4u
#define DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN        5u
#define DEM_CFG_EVMEM_AGING_METHOD_USER                      6u

#define DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED                TRUE
#define DEM_CFG_EVMEM_AGING_METHOD                           DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP

#define DEM_CFG_EVMEM_TESTFAILED_TAC_SUPPORTED               FALSE

#define DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED             FALSE

#define DEM_CFG_EVMEM_AGING_COUNTER_MAX                      0xFF

#define DEM_CFG_EVMEM_OCCURRENCE_COUNTER_SUPPORTED           TRUE

#define DEM_CFG_EVMEM_USERDEF_EVENT_MEM_STORAGE_STRATEGY     FALSE

#define DEM_CFG_EVMEM_USERDEF_MIRROR_MEM_STORAGE_STRATEGY    FALSE

#define DEM_CFG_EVMEM_RESET_CONFIRMED_BIT_ON_OVERFLOW        FALSE

#define DEM_CFG_EVMEM_PROJECT_EXTENSION                      FALSE

#define DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK               FALSE

#if(DEM_CFG_BUILDTARGET == DEM_CFG_BUILDTARGET_DEMTESTSUITE)
#define DEM_CFG_EVMEM_DEBUG_BITFIELDS                     TRUE
#else
#define DEM_CFG_EVMEM_DEBUG_BITFIELDS                     FALSE
#endif

#define DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x03      TRUE

#define DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04      TRUE

#define DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06      TRUE

#define DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT                1u
#define DEM_CFG_EVMEM_EVENTSEARCH1_FIRST                     2u
#define DEM_CFG_EVMEM_EVENTSEARCH1                           DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT

#define DEM_CFG_EVMEM_OCCURRENCE_COUNTER_MAX                 0xFFu

#define DEM_CFG_EVMEM_SHUTDOWN_NV_STORAGE_SUPPORTED          TRUE

#define DEM_CFG_EVMEMNVMIDS \
{ \
   DEM_NVM_ID_EVMEM_LOC_0,\
   DEM_NVM_ID_EVMEM_LOC_1,\
   DEM_NVM_ID_EVMEM_LOC_2,\
   DEM_NVM_ID_EVMEM_LOC_3,\
   DEM_NVM_ID_EVMEM_LOC_4,\
   DEM_NVM_ID_EVMEM_LOC_5,\
   DEM_NVM_ID_EVMEM_LOC_6,\
   DEM_NVM_ID_EVMEM_LOC_7,\
   DEM_NVM_ID_EVMEM_LOC_8,\
   DEM_NVM_ID_EVMEM_LOC_9\
}

#define DEM_EVMEM_MEMCOUNTER0                               0u

#define DEM_CFG_EVMEM_MEMID_PRIMARY                         (DEM_EVMEM_MEMCOUNTER0)
#define DEM_EVMEM_MEMCOUNTER1                               (DEM_EVMEM_MEMCOUNTER0+1u)

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0)
#define DEM_CFG_EVMEM_MEMID_SECONDARY                       (DEM_EVMEM_MEMCOUNTER1)
#define DEM_EVMEM_MEMCOUNTER2                               (DEM_EVMEM_MEMCOUNTER1+1u)
#define DEM_CFG_EVMEM_SECONDARY_MEMORY_SUPPORTED             TRUE
#else
#define DEM_CFG_EVMEM_MEMID_SECONDARY                        DEM_EVMEM_INVALID_MEMID
#define DEM_EVMEM_MEMCOUNTER2                               (DEM_EVMEM_MEMCOUNTER1)
#define DEM_CFG_EVMEM_SECONDARY_MEMORY_SUPPORTED             FALSE
#endif

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
#define DEM_CFG_EVMEM_MEMID_MIRROR                          (DEM_EVMEM_MEMCOUNTER2)
#define DEM_EVMEM_MEMCOUNTER3                               (DEM_EVMEM_MEMCOUNTER2+1u)
#define DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED                TRUE
#else
#define DEM_CFG_EVMEM_MEMID_MIRROR                           DEM_EVMEM_INVALID_MEMID
#define DEM_EVMEM_MEMCOUNTER3                               (DEM_EVMEM_MEMCOUNTER2)
#define DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED                FALSE

#endif

#define DEM_CFG_EVMEM_MAX_MEMS                               DEM_EVMEM_MEMCOUNTER3

#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL                  (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR)

#if(DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED && DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED)
  #error only mirror memory OR shadow memory is supported
#endif

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

