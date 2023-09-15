/******************************************************************************/
/* File   : SwcApplDcm_MsgAuthentication.c                                    */
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
#include "SwcApplDcm_MsgAuthentication.hpp"
#include "hmac_sha2.hpp"
#include "FeeFblBlockInterfaceX.hpp"
#include "version.hpp"
#include "Dcm.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
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
uint8 DcmCheckMessageAuthentication(uint8 ucSid, const uint8* aucMessage, uint16 ushLength){
  uint16 ushSubFunc;
  uint8  aucHash[cSIZE_OF_HASH];
  uint8  i;
  uint8  ucRetVal = MSG_NO_AUTH_NEEDED;

#ifdef DEBUG_IGNORE_MESSAGE_AUTHENTICATION
  ushSubFunc=ushSubFunc;
  aucHash[0]=aucHash[0];
  i=i;
  ucRetVal = MSG_NO_AUTH_NEEDED;
#endif
  return ucRetVal;
}

uint8 DcmAppendMessageAuthentication(uint8 ucSid, uint8* aucDataToAdd, uint32 ushLength, uint8* ucResponseMessage){
  uint16 ushSubFunc;
  uint8 ucRetVal = 0;

#ifdef DEBUG_IGNORE_MESSAGE_AUTHENTICATION
  ushSubFunc=ushSubFunc;
#endif
  return ucRetVal;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

