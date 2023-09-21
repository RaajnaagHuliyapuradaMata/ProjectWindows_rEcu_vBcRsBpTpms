#pragma once
/******************************************************************************/
/* File   : CfgSwcServiceCanTp.hpp                                            */
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
#include "CanTp_Types.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   const        CanTp_ChannelIdType      NumberOfChannels;
   const        CanTp_SduIdType          NumberOfRxPdus; //TBD: Type_SwcServiceCom_tIdPdu
   const        CanTp_SduIdType          NumberOfTxPdus; //TBD: Type_SwcServiceCom_tIdPdu
   const        CanTp_SduIdType          NumberOfRxSdus;
   const        CanTp_SduIdType          NumberOfTxSdus;
   const struct CanTp_RxPduStructType*   RxPdu;
   const struct CanTp_TxSduStructType*   TxSdu;
   const struct CanTp_RxSduStructType*   RxSdu;
   const struct CanTp_TimeOutStructType* TimeOut;
   const struct CanTp_ParamStructType*   Param;
}Type_CfgSwcServiceCanTp_st;

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

