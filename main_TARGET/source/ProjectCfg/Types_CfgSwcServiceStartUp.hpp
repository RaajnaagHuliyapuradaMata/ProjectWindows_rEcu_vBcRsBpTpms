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
   uint8  u8VersionSchema;
   uint8  u8Unused1;
   uint16 u16IdComponent;
   uint8  u8IdPcba;
   uint8  u8IdAux;
   uint16 u16IdMode;
   uint8  au8ChangesetTfs[8];
   uint8  u8TypeProgramEcu;
   uint8  u8Unused2;
   uint16 u16VersionProtocolDownload;
   uint32 u32AddressStartup;
   uint32 u32Crc;
   uint8  au8Unused3[4];
   uint8  u8VersionMajor;
   uint8  u8VersionMinor;
   uint16 u16VersionMicro;
   uint8  u8Index;
   uint8  u8Dummy1[183];
   uint32 u32CrcApp;
   uint8  u8Hash[16];
   uint8  u8Dummy2[14];
   uint8  u8Checksum[2];
}Type_CfgSwcServiceStartUp_stDescriptorBlock;

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

