#pragma once
/******************************************************************************/
/* File   : Dem_Cfg.hpp                                                       */
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
#define DEM_CFG_OBD_OFF 0
#define DEM_CFG_OBD_ON  1
#define DEM_CFG_OBD        DEM_CFG_OBD_OFF
#define DEM_CFG_J1939DCM_OFF     0
#define DEM_CFG_J1939DCM_ON      1
#define DEM_CFG_J1939DCM       DEM_CFG_J1939DCM_OFF
#define DEM_CFG_J1939DCM_CLEAR_SUPPORT                     DEM_CFG_J1939DCM_OFF
#define DEM_CFG_J1939DCM_READ_DTC_SUPPORT       FALSE
#define DEM_CFG_J1939DCM_DM31_SUPPORT        FALSE
#define DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT               FALSE
#define DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT      FALSE
#define DEM_BFM_ON TRUE
#define DEM_BFM_OFF FALSE
#define DEM_CATPRIO_ON   1
#define DEM_CATPRIO_OFF  0
#define DEM_BFM_ENABLED  DEM_BFM_OFF
#define DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED            FALSE
#define DEM_CFG_SUSPICIOUS_SUPPORT                        FALSE
#define DEM_CFG_DEBTIMEBASED_CONFIGURED_CYCLICTASKTIME    TRUE
#define DEM_CFG_EVMEMGENERIC_SUPPORTED                    TRUE
#define DEM_CFG_VERSION_INFO_API_OFF          STD_OFF
#define DEM_CFG_VERSION_INFO_API_ON           STD_ON
#define DEM_CFG_VERSION_INFO_API              DEM_CFG_VERSION_INFO_API_OFF
#define DEM_CFG_ALTERNATIVEDTC_OFF                   STD_OFF
#define DEM_CFG_ALTERNATIVEDTC_ON                    STD_ON
#define DEM_CFG_ALTERNATIVEDTC  DEM_CFG_ALTERNATIVEDTC_OFF
#define DEM_CFG_ERASE_ALL_OFF                           0u
#define DEM_CFG_ERASE_ALL_WITHOUT_HASHID_CHECK          1u
#define DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK             2u
#define DEM_CFG_ERASE_ALL_DATA_SUPPORTED                DEM_CFG_ERASE_ALL_OFF
#define DEM_CFG_DEPENDENCY_OFF         STD_OFF
#define DEM_CFG_DEPENDENCY_ON          STD_ON
#define DEM_CFG_DEPENDENCY             DEM_CFG_DEPENDENCY_OFF
#define DEM_CFG_TESTMODE_SUPPORT_ON       STD_ON
#define DEM_CFG_TESTMODE_SUPPORT_OFF      STD_OFF
#define DEM_CFG_TESTMODE_SUPPORT          DEM_CFG_TESTMODE_SUPPORT_OFF
#define DEM_CFG_CHECKAPICONSISTENCY    TRUE
#define DEM_CFG_DEBUGDATA_OFF     0
#define DEM_CFG_DEBUGDATA_8BIT    (0+1)
#define DEM_CFG_DEBUGDATA_32BIT   (0+4)
#define DEM_CFG_DEBUGDATA         DEM_CFG_DEBUGDATA_32BIT
#define DEM_DEBUGDATA_PARAM(A,B)    ,A,B

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

