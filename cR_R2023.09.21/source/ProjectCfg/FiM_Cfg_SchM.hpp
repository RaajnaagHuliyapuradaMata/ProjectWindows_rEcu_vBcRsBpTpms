#pragma once
/******************************************************************************/
/* File   : FiM_Cfg_SchM.hpp                                                  */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Monitor_NoNest(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Monitor_NoNest(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Status_NoNest(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Status_NoNest(void);

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Monitor_NoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Monitor_NoNest(void){
   __EI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Status_NoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Status_NoNest(void){
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


