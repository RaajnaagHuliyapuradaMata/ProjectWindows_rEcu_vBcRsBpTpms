#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_OperationCycle.hpp                                        */
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
#include "rba_DiagLib_Bits8.hpp"
#include "rba_DiagLib_Bits16.hpp"
#include "rba_DiagLib_Bits32.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_OPERATIONCYCLESTATUSSTORAGE                                 TRUE
#define DemConf_DemOperationCycle_DemOperationCycle_BUSACTIVE                0uL
#define DemConf_DemOperationCycle_DemOperationCycle_IGNITION                 1uL
#define DemConf_DemOperationCycle_DemOperationCycle_POWER                    2uL
#define DEM_OPERATIONCYCLE_COUNT                                               3
#define DEM_OPERATIONCYCLE_SETBIT                   rba_DiagLib_Bit8SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT                 rba_DiagLib_Bit8ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET                 rba_DiagLib_Bit8IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK                  rba_DiagLib_Bit8Mask
#define DEM_OPERATIONCYCLE_SETBITMASK               rba_DiagLib_Bit8SetBitMask
#define DEM_OPERATIONCYCLE_MERGEBITMASK             rba_DiagLib_Bit8MergeBitmask
#define DEM_OPERATIONCYCLE_CLEARBITMASK             rba_DiagLib_Bit8ClearBitMask

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8 Dem_OperationCycleList;

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

