#pragma once
/******************************************************************************/
/* File   : CfgSwcServiceStartUp.hpp                                          */
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
#include "types.hpp"
#include "Types_CfgSwcServiceStartUp.hpp" //TBD: To be deleted!

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cAPP                                                                   0
#define cFBL                                                                   1
#define PRODUCTION_SW                                                        0x0
#define DEVELOPMENT_SW                                                       0x1
#define SW_CATEGORY                                                PRODUCTION_SW
//#define SW_CATEGORY                                             DEVELOPMENT_SW

#define CfgSwcServiceStartUp_dAddressApplicationStart      ((uint32) 0x20000)
#define CfgSwcServiceStartUp_dAddressApplicationEnd        ((uint32) 0x77BFF)
#define cSTRING_ECU_PROGRAM_INFO_1_LENGTH                                     17
#define cSTRING_ECU_PROGRAM_INFO_2_LENGTH                                     38
#define cSTRING_SIZ_SCHEMA_VERS                                                1
#define cSTRING_SIZ_COMP_ID                                                    2
#define cSTRING_SIZ_PCBA_ID                                                    1
#define cSTRING_SIZ_AUX_ID                                                     1
#define cSTRING_SIZ_MODE_ID                                                    2
#define cSTRING_SIZ_PROG_TYPE                                                  1
#define cSTRING_SIZ_DL_PROT_VERS                                               2
#define cSTRING_SIZ_INDEX                                                      1
#define cSTRING_SIZ_MAJOR                                                      1
#define cSTRING_SIZ_MINOR                                                      1
#define cSTRING_SIZ_MICRO                                                      2
#define cSTRING_SIZ_CRC32                                                      4
#define cSTRING_SIZ_HASH                                                      16
#define cSTRING_SIZ_COMPANDSWTYPE ((cSTRING_SIZ_COMP_ID-1) + (cSTRING_SIZ_DL_PROT_VERS-1) + cSTRING_SIZ_PROG_TYPE)
#define cSTRING_SIZ_FULLGENBLOCK                                             133
#define cSTRING_SIZ_TFSCS                                                      8
#define cSTRING_IDX_SCHEMA_VERS                                                0
#define cSTRING_IDX_COMP_ID   cSTRING_IDX_SCHEMA_VERS + cSTRING_SIZ_SCHEMA_VERS
#define cSTRING_IDX_PCBA_ID   cSTRING_IDX_COMP_ID     + cSTRING_SIZ_COMP_ID
#define cSTRING_IDX_AUX_ID    cSTRING_IDX_PCBA_ID     + cSTRING_SIZ_PCBA_ID
#define cSTRING_IDX_MODE_ID   cSTRING_IDX_AUX_ID      + cSTRING_SIZ_AUX_ID
#define cSTRING_IDX_PROG_TYPE cSTRING_IDX_MODE_ID     + cSTRING_SIZ_MODE_ID
#define cSTRING_IDX_INDEX     cSTRING_IDX_PROG_TYPE   + cSTRING_SIZ_PROG_TYPE
#define cSTRING_IDX_MAJOR     cSTRING_IDX_INDEX       + cSTRING_SIZ_INDEX
#define cSTRING_IDX_MINOR     cSTRING_IDX_MAJOR       + cSTRING_SIZ_MAJOR
#define cSTRING_IDX_MICRO     cSTRING_IDX_MINOR       + cSTRING_SIZ_MINOR
#define cSTRING_IDX_CRC       cSTRING_IDX_MICRO       + cSTRING_SIZ_MICRO

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
