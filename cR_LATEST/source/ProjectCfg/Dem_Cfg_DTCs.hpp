#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_DTCs.hpp                                                  */
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
#define DEM_CFG_STOREWAITINGFORMONITORINGEVENT  FALSE
#define DEM_CFG_DTCFILTER_EXTERNALPROCESSING_OFF  STD_OFF
#define DEM_CFG_DTCFILTER_EXTERNALPROCESSING_ON   STD_ON
#define DEM_CFG_DTCFILTER_EXTERNALPROCESSING      DEM_CFG_DTCFILTER_EXTERNALPROCESSING_OFF
#define DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED   FALSE
#define DEM_CFG_DTCSTATUS_AVAILABILITYMASK     0xFFu
#define DEM_CFG_DTC_TRANSLATION_TYPE           DEM_DTC_TRANSLATION_ISO14229_1
#define DEM_CFG_DTCSTATEMANGER_DTCS_PER_CYCLE   10u
#define DEM_DTC_BP_STATE_SUPPRESSED             0u
#define DEM_DTC_BP_GROUP_DTCSETTING_DISABLED    1u

#define DEM_DTCSTATE_ISBITSET                    rba_DiagLib_Bit8IsBitSet
#define DEM_DTCSTATE_OVERWRITEBIT                rba_DiagLib_Bit8OverwriteBit
#define DEM_DTCSTATE_CLEARBIT                    rba_DiagLib_Bit8ClearBit
#define DEM_DTCSTATE_SETBIT                      rba_DiagLib_Bit8SetBit

#define DEM_CFG_DTCGROUPPARAMS { \
    DEM_DTCGROUPS_INIT(0       ) \
,DEM_DTCGROUPS_INIT(DEM_DTC_GROUP_ALL_DTCS) \
}

#define DEM_DTC_FILTER_NUMBER_OF_EVENTS_PER_CYCLE    25u
#define DEM_DTC_FILTER_RETRIEVE_NUMBER_OF_DTCS       50u
#define DEM_NUMBER_OF_DTCS_TO_PROCESS_PER_LOCK    1u
#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_OFF STD_OFF
#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON STD_ON
#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_OFF

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8 Dem_DtcStateType;

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

