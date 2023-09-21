#pragma once
/******************************************************************************/
/* File   : CanTp.hpp                                                         */
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
#include "CanTp_Cfg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANTP_INIT                                                         0x01u
#define CANTP_SHUTDOWN                                                     0x02u
#define CANTP_TRANSMIT                                                     0x03u
#define CANTP_TXCONFIRMATION                                               0x40u
#define CANTP_RXINDICATION                                                 0x42u
#define CANTP_MAINFUNCTION                                                 0x06u
#define CANTP_GETVERSIONINFO                                               0x07u
#define CANTP_CANCELTRANSMIT                                               0x08u
#define CANTP_CANCELRECEIVE                                                0x09u
#define CANTP_CHANGEPARAMETER                                              0x0Au
#define CANTP_READPARAMETER                                                0x0Bu
#define CANTP_TRIGGERTRANSMIT                                              0x0Cu
#define CANTP_E_PARAM_CONFIG                                               0x01u
#define CANTP_E_PARAM_ID                                                   0x02u
#define CANTP_E_PARAM_POINTER                                              0x03u
#define CANTP_E_INIT_FAILED                                                0x04u
#define CANTP_E_UNINIT                                                     0x20u
#define CANTP_E_INVALID_TX_ID                                              0x30u
#define CANTP_E_INVALID_RX_ID                                              0x40u
#define CANTP_E_PADDING                                                    0x70u
#define CANTP_E_INVALID_TATYPE                                             0x90u
#define CANTP_E_OPER_NOT_SUPPORTED                                         0xA0u
#define CANTP_E_COM                                                        0xB0u
#define CANTP_E_RX_COM                                                     0xC0u
#define CANTP_E_TX_COM                                                     0xD0u

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
#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"
extern uint8 CanTp_MainState;
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.hpp"

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.hpp"
#if(CANTP_VERSION_INFO_API == STD_ON)
extern void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void CanTp_Init(const Type_CfgSwcServiceCanTp_st *CfgPtr);

#if(CANTP_CANTPLITE_SUPPORT != STD_ON)
extern void CanTp_Shutdown(void);
#endif

extern Std_ReturnType CanTp_Transmit(Type_SwcServiceCom_tIdPdu CanTpTxSduId, const Type_SwcServiceCom_stInfoPdu *CanTpTxInfoPtr);

#if(CANTP_CANTPLITE_SUPPORT != STD_ON)
extern Std_ReturnType CanTp_CancelTransmit(Type_SwcServiceCom_tIdPdu CanTpTxSduId);
extern Std_ReturnType CanTp_CancelReceive(Type_SwcServiceCom_tIdPdu CanTpRxSduId);
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

