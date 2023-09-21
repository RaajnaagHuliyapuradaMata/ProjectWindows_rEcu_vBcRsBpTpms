#pragma once
/******************************************************************************/
/* File   : ComM_Cfg_SchM.hpp                                                 */
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
#include "Os.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_UserNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_UserNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ChannelNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ChannelNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_EIRANoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_EIRANoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ERANoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ERANoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCTxSigNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCTxSigNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCWakeUpNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCWakeUpNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_LimitationNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_LimitationNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_Channel(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_Channel(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_FullComRequestors(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_FullComRequestors(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCTxSigNoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCTxSigNoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCNoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCNoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_EIRANoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_EIRANoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ERANoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ERANoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCWakeUpNoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCWakeUpNoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_UserNoNest(void){
    __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_UserNoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ChannelNoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ChannelNoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_LimitationNoNest(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_LimitationNoNest(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_Channel(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_Channel(void){
  __EI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_FullComRequestors(void){
    __DI();
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_FullComRequestors(void){
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

