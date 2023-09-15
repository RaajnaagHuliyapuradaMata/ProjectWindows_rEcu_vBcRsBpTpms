#pragma once
/******************************************************************************/
/* File   : CfgSwcApplTpms_IDOM.hpp                                           */
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
#ifdef IBTCM_SW_ANPASSUNGEN
#include "Tpms_Rte_Data_Type.hpp"
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#ifdef IBTCM_SW_ANPASSUNGEN
#define ucDefOffsetInRSSIc   ((uint8)46)
#else
#define cADCResInmVx100 977
#define ucDefOffsetInRSSIcInmV 400
#define ucDefOffsetInRSSIc (unsigned char) ((unsigned short) (ucDefOffsetInRSSIcInmV *100) / cADCResInmVx100)
#endif

#define ushHFiAlarmTimeInSec         ((unsigned short)600)
#define ucMaxFF4RFInterference          ((unsigned char)133)
#define ushMaxTimeWithoutMsgInSec ((unsigned short)(9*60))

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

