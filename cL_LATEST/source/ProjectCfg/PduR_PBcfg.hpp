#pragma once
/******************************************************************************/
/* File   : PduR_PBcfg.hpp                                                    */
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
#include "PduR_Types.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#if !defined(PduR_RF_CanIf_Transmit)
#define PduR_RF_CanIf_Transmit    (0)
#endif

#if !defined(PduR_RF_CanTp_Transmit)
#define PduR_RF_CanTp_Transmit    (1)
#endif

#define MAX_NO_OF_LO_TXTABLE_ENTRIES 1

#if !defined(PduR_IH_CancelTransmit)
#define PduR_IH_CancelTransmit    (0)
#endif

#define MAX_NO_OF_LO_CANCEL_TXTABLE_ENTRIES 0

#if !defined(PduR_RF_Com_RxIndication)
#define PduR_RF_Com_RxIndication    (0)
#endif

#define MAX_NO_OF_UPIF_RXINDICATION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Com_TxConfirmation)
#define PduR_RF_Com_TxConfirmation    (0)
#endif

#define MAX_NO_OF_UPIF_TXCONFIRMATION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_CopyRxData)
#define PduR_RF_Dcm_CopyRxData    (0)
#endif

#define MAX_NO_OF_UPTP_COPYRXDATA_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_StartOfReception)
#define PduR_RF_Dcm_StartOfReception    (0)
#endif

#define MAX_NO_OF_UPTP_STARTOFRECEPTION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_TpRxIndication)
#define PduR_RF_Dcm_TpRxIndication    (0)
#endif

#define MAX_NO_OF_UPTP_RXINDICATION_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_CopyTxData)
#define PduR_RF_Dcm_CopyTxData    (0)
#endif

#define MAX_NO_OF_UPTP_COPYTXDATA_TABLE_ENTRIES 0

#if !defined(PduR_RF_Dcm_TpTxConfirmation)
#define PduR_RF_Dcm_TpTxConfirmation    (0)
#endif

#define MAX_NO_OF_UPTP_TXCONFIRMATION_TABLE_ENTRIES 0

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

