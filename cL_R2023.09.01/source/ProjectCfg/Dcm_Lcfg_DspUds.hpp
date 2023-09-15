#pragma once
/******************************************************************************/
/* File   : Dcm_Lcfg_DspUds.hpp                                               */
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
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern Std_ReturnType Dcm_DidServices_F186_ReadData(uint8 * adrData_pu8);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern Std_ReturnType DcmAppl_DcmReadDataNRC(uint16 Did,uint32 DidSignalPosn,Dcm_NegativeResponseCodeType * ErrorCode);

extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B001_VoltageBattery (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B002_SpeedVehicle (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B003_TemperatureAmbient (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B004_Reserved (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B006_OccurenceDate (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B006_OccurenceTime (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B007_TirePressures (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B008_TireTemperatures (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_B009_ModesAndStatusEcu (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_F103_ModePowerVehicle (Dcm_OpStatusType OpStatus,uint8 * Data);
extern Std_ReturnType SwcApplDcm_FuncDidRead_DataDtcEnv_F104_Mileage (Dcm_OpStatusType OpStatus,uint8 * Data);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern sint16 Dcm_RCSigOutN_as16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern sint32 Dcm_RCSigOutN_as32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern sint8 Dcm_RCSigOutN_as8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern uint32 Dcm_RCSigOutN_au32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_RCSigOutN_au16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern uint8 Dcm_RCSigOutN_au8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern sint16 Dcm_RCSigInN_as16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern sint32 Dcm_RCSigInN_as32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern sint8 Dcm_RCSigInN_as8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern uint32 Dcm_RCSigInN_au32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_RCSigInN_au16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern uint8 Dcm_RCSigInN_au8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

