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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"
#include "Com_Cbk.hpp"
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
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
Com_IpduGroupVector Com_IpduGrpVector;

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
Com_IpduGroupVector Com_IpduGrpVector_DM;
#endif

#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.hpp"
const Com_TransModeInfo Com_NONE_TransModeInfo =
{
    0
   ,   0,

    0
   ,   0,

#ifdef COM_MIXEDPHASESHIFT
   COM_TXMODE_NONE
   ,  COM_FALSE
#else

   COM_TXMODE_NONE

#endif
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
#include "infSwcServiceComSwcServiceSchM.hpp"
void infSwcServiceComSwcServiceSchM_vMainFunctionRx(void){
#ifdef COM_RX_MAINFUNCTION_PROC
   Com_InternalMainFunctionRx( (Com_MainFuncType)ComMainFunction_Internal_MainFunctionRx );
#endif
}

void infSwcServiceComSwcServiceSchM_vMainFunctionTx(void){
   Com_InternalMainFunctionTx( (Com_MainFuncType)ComMainFunction_Internal_MainFunctionTx );
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

