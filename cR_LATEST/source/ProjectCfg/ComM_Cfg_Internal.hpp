#pragma once
/******************************************************************************/
/* File   : ComM_Cfg_Internal.hpp                                             */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ComM_Cfg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define COMM_CAN                                                          STD_ON
#define COMM_LIN                                                         STD_OFF
#define COMM_FLXRY                                                       STD_OFF
#define COMM_ETH                                                         STD_OFF
#define COMM_DEV_ERROR_DETECT                                            STD_OFF
#define COMM_SYNCHRONOUS_WAKE_UP                                         STD_OFF
#define COMM_VERSION_INFO_API                                            STD_OFF
#define COMM_NM_SUPPORT                                                  STD_OFF
#define COMM_DCM_SUPPORT                                                 STD_ON
#define COMM_RTE_SUPPORT                                                 STD_OFF
#define COMM_FULLCOMREQ_NOTIF                                            STD_OFF
#define COMM_PNC_ENABLED                                                 STD_OFF
#define COMM_PNC_GW_ENABLED                                              STD_OFF
#define COMM_LIMIT_TO_NOCOM_ENABLED                                      STD_OFF
#define COMM_PREVENT_WAKEUP_ENABLED                                      STD_OFF
#define COMM_NVM_ENABLED                                                 STD_OFF
#define COMM_RESET_AFTER_NO_COM                                          STD_OFF
#define COMM_NO_OF_USERS                                                       1
#define COMM_NO_OF_CHANNELS                                                    1
#define COMM_NVM_NO_WAKEUP_SIZE                                                1
#define COMM_MAX_CHANNEL_REQUESTERS                                            1
#define COMM_MAX_NO_OF_PNCS                                                 (56)
#define COMM_NO_OF_PNCS                                                      (0)
#define COMM_NO_OF_CH_WITH_ERA                                               (0)
#define COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA                              (1)
#define COMM_INHIBITION_ENABLED     ((COMM_PREVENT_WAKEUP_ENABLED != STD_OFF) || (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF))


/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
     P2FUNC(Std_ReturnType, COMM_APPL_CODE, BusSm_RequestComMode)(NetworkHandleType, ComM_ModeType);
     P2FUNC(Std_ReturnType, COMM_APPL_CODE, BusSm_GetCurrentComMode)(NetworkHandleType
   ,     P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) ComM_ModePtr);
}ComM_BusSmApiType;

typedef struct{
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) DirectChannels_p;
   uint8 NumDirectChannels_u8;
   uint8 NumAllChannels_u8;
}ComM_UsersType;

typedef struct ComM_ChannelTypeStruct{
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) AllUsers_p;
   ComM_BusType BusType_e;
   ComM_NMVariantType ComMNmVariant_e;
   uint32 NmLightTimeout_u32;
   uint16 TMinFullComModeDuration_u16;
   NetworkHandleType ComMChannelId_u8;
   uint8 numAllUsers_u8;
   boolean ComMFullCommRequestNotificationEnabled;
}ComM_ChannelType;

typedef struct ComM_PncStructType{
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Channels;
   uint16 PrepareSleepTimer;
   uint8 NumChannels;
   uint8 PncId;
}ComM_PncConfigStruct_t;

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
extern CONST(ComM_BusSmApiType, COMM_CONST) ComM_BusSmApi[];
extern CONST(ComM_ChannelType,COMM_CONST) ComM_ChanelList[];
extern CONST(ComM_UsersType,COMM_CONST) ComM_UserList[];

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

