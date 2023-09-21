#pragma once
/******************************************************************************/
/* File   : CanSM_Cfg_SchM.hpp                                                */
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
#include "SchM.hpp"
#include "Os.hpp"

#include "CanSM_Cfg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BOR_Nw_ModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BOR_Nw_ModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BaudModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BaudModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_GetMutexNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_GetMutexNoNest(void);

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BOR_Nw_ModesNoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BOR_Nw_ModesNoNest(void){
   __EI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BaudModesNoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BaudModesNoNest(void){
   __EI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_GetMutexNoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_GetMutexNoNest(void){
   __EI();
}

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

