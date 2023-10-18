#pragma once
/******************************************************************************/
/* File   : CfgMcalFls_Fdl.hpp                                                */
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
#include "Fls.hpp"
#include "SchM_Fls.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
#define FDL_CRITICAL_SECTION_BEGIN     FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#define FDL_CRITICAL_SECTION_END       FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif

#if(FLS_CRITICAL_SECTION_PROTECTION == STD_OFF)
#define FDL_CRITICAL_SECTION_BEGIN
#define FDL_CRITICAL_SECTION_END
#endif

#define R_FDL_DEVICE_SPECIFIC_INIT                             \
   *(volatile uint32_t*)0xFFA08000UL = 0xFFFFFFFFUL;          \
   *(volatile uint32_t*)0xFFA08004UL = 0xFFFFFFFFUL;          \
   *(volatile uint32_t*)0xFFA08008UL = 0xFFFFFFFFUL;          \
   *(volatile uint32_t*)0xFFA0800CUL = 0xFFFFFFFFUL;

#define R_FDL_F1L_PATCH_DF_OVERSIZE

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

