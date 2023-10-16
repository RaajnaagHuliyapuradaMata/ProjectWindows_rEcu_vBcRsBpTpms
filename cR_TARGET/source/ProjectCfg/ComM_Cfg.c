/******************************************************************************/
/* File   : ComM_Cfg.c                                                        */
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

#include "Types_SwcServiceComM.hpp"

#include "ComStack_Types.hpp"
#include "ComM_Cfg.hpp"
#include "ComM_Priv.hpp"
#include "CanSM_ComM.hpp"

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
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
static FUNC(Std_ReturnType, COMM_CODE) ComM_Dummy_RequestComMode(
   VAR(NetworkHandleType, AUTOMATIC) NetworkHandle
   ,     VAR(Type_SwcServiceComM_tMode, AUTOMATIC) ComM_Mode
);

static FUNC(Std_ReturnType, COMM_CODE) ComM_Dummy_GetCurrentComMode(
   VAR(NetworkHandleType, AUTOMATIC) NetworkHandle
   ,     P2VAR(Type_SwcServiceComM_tMode, AUTOMATIC, COMM_APPL_DATA) ComM_ModePtr
);

static FUNC(Std_ReturnType, COMM_CODE) ComM_Dummy_RequestComMode(
   VAR(NetworkHandleType, AUTOMATIC) NetworkHandle
   ,     VAR(Type_SwcServiceComM_tMode, AUTOMATIC) ComM_Mode
){
    (void) NetworkHandle;
    (void) ComM_Mode;
    return E_OK;
}

static FUNC(Std_ReturnType, COMM_CODE) ComM_Dummy_GetCurrentComMode(
   VAR(NetworkHandleType, AUTOMATIC) NetworkHandle
   ,     P2VAR(Type_SwcServiceComM_tMode, AUTOMATIC, COMM_APPL_DATA) ComM_ModePtr
){
    *ComM_ModePtr = ComM_ChannelStruct[NetworkHandle].ChannelMode_u8;
    return E_OK;
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"
CONST(ComM_BusSmApiType, COMM_CONST) ComM_BusSmApi[] = {
   {
        &CanSM_RequestComMode
   ,     &CanSM_GetCurrentComMode
   }
   ,  {
        &ComM_Dummy_RequestComMode
   ,     &ComM_Dummy_GetCurrentComMode
   }
   ,  {
        &ComM_Dummy_RequestComMode
   ,     &ComM_Dummy_GetCurrentComMode
   }
   ,  {
        &ComM_Dummy_RequestComMode
   ,     &ComM_Dummy_GetCurrentComMode
   }
   ,  {
        &ComM_Dummy_RequestComMode
   ,     &ComM_Dummy_GetCurrentComMode
   }
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

