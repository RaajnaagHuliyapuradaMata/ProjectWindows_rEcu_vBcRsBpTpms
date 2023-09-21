/******************************************************************************/
/* File   : Com_Cfg.c                                                         */
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
#include "Std_Types.hpp"

#include "infSwcServiceComSwcServiceSchM.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"
#include "Com_Cbk.hpp"
#include "PduR_Com.hpp"
#include "Com_PBcfg_InternalId.hpp"

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
#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.hpp"
CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST) Com_NONE_TransModeInfo = {
      0
   ,  0
   ,  0
   ,  0
   ,  COM_TXMODE_NONE
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector;
VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector_DM;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) infSwcServiceComSwcServiceSchM_vMainFunctionRx(void){
   Com_InternalMainFunctionRx(
      (Com_MainFuncType)ComMainFunction_Internal_MainFunctionRx
   );
}

FUNC(void, COM_CODE) infSwcServiceComSwcServiceSchM_vMainFunctionTx(void){
   Com_InternalMainFunctionTx(
      (Com_MainFuncType)ComMainFunction_Internal_MainFunctionTx
   );
}

FUNC(void,COM_CODE) Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0(void){
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

