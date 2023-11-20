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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CfgSwcServiceStartUp_dCategorySw_Production                            0
#define CfgSwcServiceStartUp_dCategorySw_Development                           1

typedef enum{
      CfgSwcServiceStartUp_eProgramSw_App
   ,  CfgSwcServiceStartUp_eProgramSw_Fbl
}Type_CfgSwcServiceStartUp_eProgramSw;

#define CfgSwcServiceStartUp_dCategorySw CfgSwcServiceStartUp_dCategorySw_Production
#define CfgSwcServiceStartUp_dAddressApplicationStart      ((uint32) 0x20000)
#define CfgSwcServiceStartUp_dAddressApplicationEnd        ((uint32) 0x77BFF)
#define CfgSwcServiceStartUp_dAddressDescriptorBlock_App   ((void*)  0x00077b00)
#define CfgSwcServiceStartUp_dAddressDescriptorBlock_Fbl   ((void*)  0x0001ff00)
#define CfgSwcServiceStartUp_dVersionSoftwareMajor         ((uint8)  0x02)
#define CfgSwcServiceStartUp_dVersionSoftwareMinor         ((uint8)  0x01)
#define CfgSwcServiceStartUp_dVersionSoftwareMicro         ((uint16) 0x0004)
#define CfgSwcServiceStartUp_dVersionSchema                ((uint8)  0x01)
#define CfgSwcServiceStartUp_dIdComponent                  ((uint16) 0x003A)
#define CfgSwcServiceStartUp_dIdPcba                       ((uint8)  0x01)
#define CfgSwcServiceStartUp_dIdAux                        ((uint8)  0x00)
#define CfgSwcServiceStartUp_dIdMode                       ((uint16) 0x0000)
#define CfgSwcServiceStartUp_dTypeProg_Fbl                 ((uint8)  0x02)
#define CfgSwcServiceStartUp_dTypeProg_App                 ((uint8)  0x05)
#define CfgSwcServiceStartUp_dIndexGenealogy               ((uint8)  0x01)
#define CfgSwcServiceStartUp_dVersionProtocolDL            ((uint16) 0x0001)
#define cTFS_CHANGESET                           'C','S','0','0','1','9','3','3'
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
