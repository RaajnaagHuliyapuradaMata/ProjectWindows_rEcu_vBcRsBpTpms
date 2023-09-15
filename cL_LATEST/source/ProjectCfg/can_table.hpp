#pragma once
/******************************************************************************/
/* File   : can_table.hpp                                                     */
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
#define CfgMcalCan_dNumRulesRx_CH0                                         (13U)
#define CfgMcalCan_dNumRulesRx_CH1                                          (0U)
#define CfgMcalCan_dNumRulesRx_CH2                                          (0U)
#define CfgMcalCan_dNumRulesRx_CH3                                          (0U)
#define CfgMcalCan_dNumRulesRx_CH4                                          (0U)

#define CfgMcalCan_dNumRulesRx               (                                 \
                                                    CfgMcalCan_dNumRulesRx_CH0 \
                                                +   CfgMcalCan_dNumRulesRx_CH1 \
                                                +   CfgMcalCan_dNumRulesRx_CH2 \
                                                +   CfgMcalCan_dNumRulesRx_CH3 \
                                                +   CfgMcalCan_dNumRulesRx_CH4 \
                                             )

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint32 lword[4];
}Type_McalCan_stRuleRx;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
extern const Type_McalCan_stRuleRx CfgMcalCan_castListRulesRx[CfgMcalCan_dNumRulesRx];

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

