/******************************************************************************/
/* File   : Fls_PBcfg.c                                                       */
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
#include "Fls_PBTypes.hpp"
#include "Fls_Cbk.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FLS_PBCFG_C_AR_MAJOR_VERSION  2U
#define FLS_PBCFG_C_AR_MINOR_VERSION  4U
#define FLS_PBCFG_C_AR_PATCH_VERSION  0U

#define FLS_PBCFG_C_SW_MAJOR_VERSION  1U
#define FLS_PBCFG_C_SW_MINOR_VERSION  3U

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define FLS_START_SEC_DBTOC_DATA_UNSPECIFIED
#include "MemMap.hpp"
CONST(Fls_ConfigType, FLS_CONST) Fls_GstConfiguration[] = {
  {
    0x0ED70118UL,
    EcuabFee_JobEndNotification,
    EcuabFee_JobErrorNotification,
    NULL_PTR,
    NULL_PTR,
    0x00000100UL,
    0x0003E801UL,
    0x00004291UL,
    0x00000FA1UL
  }
};
#define FLS_STOP_SEC_DBTOC_DATA_UNSPECIFIED
#include "MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define FLS_START_SEC_BUFFER_CODE
#include "MemMap.hpp"
VAR(uint32, AUTOMATIC) Fls_GulTempBuffer[64];
#define FLS_STOP_SEC_BUFFER_CODE
#include "MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

