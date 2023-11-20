#pragma once
/******************************************************************************/
/* File   : Types_CfgSwcServiceStartUp.hpp                                    */
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

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8  ucSchemaVersion;
   uint8  ucUnused1;
   uint16 ushComponentId;
   uint8  ucPcbaId;
   uint8  ucAuxId;
   uint16 ushModeId;
   uint8  aucTfsChangeset[8];
   uint8  ucEcuProgramType;
   uint8  ucUnused2;
   uint16 ushDownloadProtocolVersion;
   uint32 ulStartupAddress;
   uint32 ulCrc32;
   uint8  aucUnused3[4];
   uint8  ucMajor;
   uint8  ucMinor;
   uint16 ushMicro;
   uint8  ucIndex;
   uint8  ucDummy1[183];
   uint32 ulCrc32App;
   uint8  ucHash[16];
   uint8  ucDummy2[14];
   uint8  ucChecksum[2];
}tDescriptorBlock;

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

