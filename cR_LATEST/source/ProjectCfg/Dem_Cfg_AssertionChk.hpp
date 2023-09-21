#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_AssertionChk.hpp                                          */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

#include "Dem_Lib.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_GenericNvData.hpp"
#include "Dem_DisturbanceMemory.hpp"
#include "Dem_Cfg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_ON                   STD_ON
#define DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_OFF                  STD_OFF
#define DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH  DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_ON
#define DEM_NVM_ID_DEM_GENERIC_NV_DATA_SIZE                                   18
#define DEM_NVM_ID_EVMEM_LOC_0_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_1_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_2_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_3_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_4_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_5_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_6_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_7_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_8_SIZE                                           48
#define DEM_NVM_ID_EVMEM_LOC_9_SIZE                                           48
#define DEM_NVM_ID_EVT_STATUSBYTE_SIZE                                        42

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
DEM_STATIC_ASSERT((DEM_SIZEOF_VAR(Dem_GenericNvData)==DEM_NVM_ID_DEM_GENERIC_NV_DATA_SIZE),DEM_NVM_ID_DEM_GENERIC_NV_DATA_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_0_SIZE),DEM_NVM_ID_EVMEM_LOC_0_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_1_SIZE),DEM_NVM_ID_EVMEM_LOC_1_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_2_SIZE),DEM_NVM_ID_EVMEM_LOC_2_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_3_SIZE),DEM_NVM_ID_EVMEM_LOC_3_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_4_SIZE),DEM_NVM_ID_EVMEM_LOC_4_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_5_SIZE),DEM_NVM_ID_EVMEM_LOC_5_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_6_SIZE),DEM_NVM_ID_EVMEM_LOC_6_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_7_SIZE),DEM_NVM_ID_EVMEM_LOC_7_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_8_SIZE),DEM_NVM_ID_EVMEM_LOC_8_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_9_SIZE),DEM_NVM_ID_EVMEM_LOC_9_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_VAR(Dem_AllEventsStatusByte)==DEM_NVM_ID_EVT_STATUSBYTE_SIZE),DEM_NVM_ID_EVT_STATUSBYTE_BlockLengthIsInvalid);

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

