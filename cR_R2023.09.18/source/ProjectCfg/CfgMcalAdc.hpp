#pragma once
/******************************************************************************/
/* File   : CfgMcalAdc.h                                                      */
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
#include "CompilerCfg_McalAdc.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CfgMcalAdc_cLenBufferChannel2                                          4
#define CfgMcalAdc_cValueMaxDefault                                        0xffu
#define CfgMcalAdc_cMaskBits16                                           0xffffu

#define CfgMcalAdc_cADCA0VCR02                                 CfgMcalAdc_st.u32ADCA0VCR02
#define CfgMcalAdc_cADCA0ADCR                                  CfgMcalAdc_st.u32ADCA0ADCR
#define CfgMcalAdc_cADCA0SMPCR                                 CfgMcalAdc_st.u32ADCA0SMPCR
#define CfgMcalAdc_cADCA0SFTCR                                 CfgMcalAdc_st.u32ADCA0SFTCR
#define CfgMcalAdc_cADCA0SGCR1                                 CfgMcalAdc_st.u32ADCA0SGCR1
#define CfgMcalAdc_cADCA0SGVCSP1                               CfgMcalAdc_st.u32ADCA0SGVCSP1
#define CfgMcalAdc_cADCA0SGVCEP1                               CfgMcalAdc_st.u32ADCA0SGVCEP1
#define CfgMcalAdc_cValueCompensationErrorNonLinearityDiodeDS3 CfgMcalAdc_st.u16ValueCompensationErrorNonLinearityDiodeDS3
#define CfgMcalAdc_cValueCompensationErrorRounding             CfgMcalAdc_st.u8ValueCompensationErrorRounding
#define CfgMcalAdc_cValueGain_mV                               CfgMcalAdc_st.u8ValueGain_mV

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint32 u32ADCA0VCR02;
   uint32 u32ADCA0ADCR;
   uint32 u32ADCA0SMPCR;
   uint32 u32ADCA0SFTCR;
   uint32 u32ADCA0SGCR1;
   uint32 u32ADCA0SGVCSP1;
   uint32 u32ADCA0SGVCEP1;
   uint16 u16ValueCompensationErrorNonLinearityDiodeDS3;
   uint8  u8ValueCompensationErrorRounding;
   uint8  u8ValueGain_mV;
}Type_CfgMcalAdc_st;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
extern CONST(Type_CfgMcalAdc_st, MCALADC_CONFIG_DATA) CfgMcalAdc_st;

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
