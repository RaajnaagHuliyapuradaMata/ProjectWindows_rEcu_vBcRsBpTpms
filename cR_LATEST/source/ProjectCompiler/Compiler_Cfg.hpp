#pragma once
/******************************************************************************/
/* File   : Compiler_Cfg.h                                                    */
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
/* git@github.com:RaajnaagHuliyapuradaMata/<module_name>.git                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
Compiler configuration for
--------------------------------------------------------------------------------
Vendor   : Green Hills Software
Compiler : MULTI
Version  : 2015.1.7
*******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define AUTOSAR_COMSTACKDATA
#define MSR_REGSPACE                                                    REGSPACE
#define REGSPACE
#define _STATIC_                                                          STATIC

/* Move to respective CompilerCfg_<Module_Name>.h */
#define _CDD_CODE
#define _CDD_APPL_DATA

#define FEE_30_SMALLSECTOR_PUBLIC_CODE
#define FEE_30_SMALLSECTOR_PRIVATE_CODE
#define FEE_30_SMALLSECTOR_APPL_DATA
#define FEE_30_SMALLSECTOR_FAST_DATA
#define FEE_30_SMALLSECTOR_PRIVATE_CONST
#define FEE_30_SMALLSECTOR_PUBLIC_CONST
#define FEE_30_SMALLSECTOR_NVM_CODE

#define FEE_30_SMALLSECTOR_CODE FEE_30_SMALLSECTOR_PUBLIC_CODE
#define MEMIF_CODE
#define MEMIF_PRIVATE_CODE
#define MEMIF_CONST
#define MEMIF_APPL_DATA

#define NVM_APPL_DATA
#define NVM_APPL_CODE
#define NVM_APPL_CONST
#define NVM_CRC_APPL_DATA
#define NVM_CONFIG_DATA
#define NVM_CONFIG_CONST
#define NVM_FAST_DATA
#define NVM_PRIVATE_CODE
#define NVM_PRIVATE_CONST
#define NVM_PRIVATE_DATA
#define NVM_PUBLIC_CODE
#define NVM_PUBLIC_CONST
#define NVM_CODE NVM_PUBLIC_CODE

#define VSTDLIB_CODE
#define VSTDLIB_VAR_FAR
#define VSTDLIB_APPL_VAR

#define FBLBMHDR_CONST
#define FBLBMHDR_CODE

#include "CompilerCfg_SwcServiceOs.hpp"

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define UNUSED(x)                                                      ((void)x)/*(x=x)*/

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

