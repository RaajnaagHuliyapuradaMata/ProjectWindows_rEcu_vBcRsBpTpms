/******************************************************************************/
/* File   : CanTp_Cfg.c                                                       */
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
#include "Std_Types.hpp"

#include "CanTp.hpp"
#include "CanTp_Types.hpp"
#include "CfgSwcServiceCanTp.hpp"
#include "PduR_CanTp.hpp"
#include "CanIf.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANTP_IF_PDU_ID_00000     CfgEcuabCanIf_dPduTx_DiagUdsResp_Physical
#define CANTP_IF_FC_PDU_ID_00000  0
#define CANTP_IF_FC_PDU_ID_00001  CfgEcuabCanIf_dPduTx_DiagUdsResp_Physical
#define CANTP_PDUR_DEST_ID_00000  CfgSwcServicePduR_PduDestTxDiagUds_Physical_PduR2CanTp
#define CANTP_PDUR_SRC_ID_00000   CfgSwcServicePduR_PduSrcRxDiagUdsReq_Functional_CanTp2PduR
#define CANTP_PDUR_SRC_ID_00001   CfgSwcServicePduR_PduSrcRxDiagUdsReq_Physical_CanTp2PduR

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "CanTp_MemMap.hpp"
static const struct CanTp_RxPduStructType CanTp_RxPdu[2u] = {
      {0,  2,  NULL_PTR}
   ,  {1,  0,  NULL_PTR}
};

static const struct CanTp_TxSduStructType CanTp_TxSdu[1u] = {
   {0x8, 0x8, 0xF1, 0, 0, 1, 0, CANTP_IF_PDU_ID_00000, CANTP_PDUR_DEST_ID_00000}
};

static const struct CanTp_RxSduStructType CanTp_RxSdu[2u] = {
      {0xC,  0x0,   0,  1,  0,  0,  0,  CANTP_IF_FC_PDU_ID_00000,  CANTP_PDUR_SRC_ID_00000}
   ,  {0x8,  0xF1,  0,  1,  1,  0,  0,  CANTP_IF_FC_PDU_ID_00001,  CANTP_PDUR_SRC_ID_00001}
};

static const struct CanTp_TimeOutStructType CanTp_TimeOut[2u] = {
      {3,  75,  11}
   ,  {3,  0,   15}
};

static const struct CanTp_ParamStructType CanTp_Param[2u] = {
      {{0x64,  0x0},  0x0}
   ,  {{0x0,   0x0},  0x0}
};

const Type_CfgSwcServiceCanTp_st CfgSwcServiceCanTp_cst = {
      2
   ,  2
   ,  1
   ,  2
   ,  1
   ,  &CanTp_RxPdu[0]
   ,  &CanTp_TxSdu[0]
   ,  &CanTp_RxSdu[0]
   ,  &CanTp_TimeOut[0]
   ,  &CanTp_Param[0]
};
#define CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "CanTp_MemMap.hpp"

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

