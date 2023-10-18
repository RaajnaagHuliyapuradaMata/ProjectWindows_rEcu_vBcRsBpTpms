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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
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

#if(COMM_NM_SUPPORT!= STD_OFF)
#define COMM_NM_VARIANT                                     COMM_NM_VARIANT_FULL
#endif

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
typedef VAR(ComM_UserHandleType, AUTOMATIC) ComM_InternalHandleArrayType;
typedef struct{
  VAR(uint8, AUTOMATIC) numberOfRequesters;
  VAR(ComM_InternalHandleArrayType, AUTOMATIC) handleArray[COMM_MAX_CHANNEL_REQUESTERS];
}ComM_UserHandleArrayType;
#endif

typedef struct{
     P2FUNC(Std_ReturnType, COMM_APPL_CODE, BusSm_RequestComMode)(NetworkHandleType, ComM_ModeType);
     P2FUNC(Std_ReturnType, COMM_APPL_CODE, BusSm_GetCurrentComMode)(NetworkHandleType
   ,     P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) ComM_ModePtr);
}ComM_BusSmApiType;

typedef struct{
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) DirectChannels_p;
#if(COMM_PNC_ENABLED != STD_OFF)
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Pncs_p;
#endif
   uint8 NumDirectChannels_u8;
   uint8 NumAllChannels_u8;
#if(COMM_PNC_ENABLED != STD_OFF)
   uint8 NumPnc_u8;
#endif
}ComM_UsersType;

typedef struct ComM_ChannelTypeStruct{
#if((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Pncs_p;
#endif
#if(COMM_INHIBITION_ENABLED)
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) DirectUsers_p;
#endif
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) AllUsers_p;
   ComM_BusType BusType_e;
   ComM_NMVariantType ComMNmVariant_e;
#if(COMM_PNC_GW_ENABLED != STD_OFF)
   ComM_PncGatewayType PncGwType;
#endif
   uint32 NmLightTimeout_u32;
   uint16 TMinFullComModeDuration_u16;
#if(COMM_PNC_ENABLED != STD_OFF)
   uint16 TxSigId;
#endif
    NetworkHandleType ComMChannelId_u8;
#if((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
   uint8 numPncs_u8;
#endif
#if(COMM_INHIBITION_ENABLED)
   uint8 numDirectUsers_u8;
   uint8 InhibitionInitValue_u8;
#endif
   uint8 numAllUsers_u8;
#if(COMM_PNC_ENABLED != STD_OFF)
   boolean PncNmRequest;
#endif
#if(COMM_NVM_ENABLED != STD_OFF)
   VAR(boolean, AUTOMATIC) ComMNoWakeUpInhibitionNvmStorage_b;
#endif
   boolean ComMFullCommRequestNotificationEnabled;
}ComM_ChannelType;

typedef struct ComM_PncStructType{
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Channels;
#if(COMM_INHIBITION_ENABLED)
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p;
#endif
   uint16 PrepareSleepTimer;
#if(COMM_INHIBITION_ENABLED)
   uint8 NumUsers_u8;
#endif
   uint8 NumChannels;
   uint8 PncId;
}ComM_PncConfigStruct_t;

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

#if(COMM_PNC_ENABLED != STD_OFF)
// For Signal array type for ERA and EIRA Rx signals of PNC
typedef const uint16 ComM_SignalArrayType[COMM_NO_OF_PNCS];
#endif

// Global config structure to store pointers to all config tables

typedef struct{
   P2CONST(ComM_ChannelType,COMM_CONST,COMM_APPL_CONST) ChannelConfig_pcs;
   P2CONST(ComM_UsersType,COMM_CONST,COMM_APPL_CONST) UserConfig_pcs;
#if(COMM_PNC_ENABLED != STD_OFF)
   P2CONST(ComM_PncConfigStruct_t,COMM_CONST,COMM_APPL_CONST) PncConfig_pcs;
   P2CONST(ComM_SignalArrayType,COMM_CONST,COMM_APPL_CONST) EiraSignalTable_pcs;
#if(COMM_PNC_GW_ENABLED != STD_OFF)
   P2CONST(ComM_SignalArrayType,COMM_CONST,COMM_APPL_CONST) EraSignalTable_pcs;
#endif
   VAR(boolean,COMM_VAR) ComMPncEnabled_b;
#endif
}ComM_GlobalConfigType;

#endif

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
#if(COMM_RTE_SUPPORT != STD_OFF)
extern FUNC(void, COMM_CODE) ComM_Rte_Switch_UM_currentMode(VAR(ComM_UserHandleType, AUTOMATIC) UserId, VAR(uint8, AUTOMATIC) lowestMode);
#endif

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
extern FUNC(void, COMM_CODE) ComM_CurrentChannelRequest_Rte_Write(VAR(uint8, AUTOMATIC) ChannelId,P2VAR(ComM_UserHandleArrayType, AUTOMATIC, COMM_APPL_DATA) data);
#endif

#define COMM_START_SEC_CONST_8
#include "ComM_Cfg_MemMap.hpp"
#if(COMM_INHIBITION_ENABLED)
extern CONST(ComM_InhibitionStatusType, COMM_CONST) ComM_EcuGroupClassification_Init;
#endif
#define COMM_STOP_SEC_CONST_8
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"
extern CONST(ComM_BusSmApiType, COMM_CONST) ComM_BusSmApi[];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"
extern CONST(ComM_ChannelType,COMM_CONST) ComM_ChanelList[];
extern CONST(ComM_UsersType,COMM_CONST) ComM_UserList[];

#if(COMM_PNC_ENABLED != STD_OFF)

extern CONST(ComM_PncConfigStruct_t,COMM_CONST) ComM_PncList[];
extern CONST(uint16, COMM_CONST) ComM_EIRA_RxSig[];

#if(COMM_PNC_GW_ENABLED != STD_OFF)
extern CONST(uint16, COMM_CONST) ComM_ERA_RxSig[];
#endif

#endif
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

