#pragma once
/******************************************************************************/
/* File   : Template.hpp                                                      */
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
#include "SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define SchM_Enter_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Enter_Com_TxIpduProtArea_##FUNCTIONNAME()
#define SchM_Exit_Com_TxIpduProtArea(FUNCTIONNAME)  SchM_Exit_Com_TxIpduProtArea_##FUNCTIONNAME()
#define SchM_Enter_Com_RxSigBuff(FUNCTIONNAME)      SchM_Enter_Com_RxSigBuff_##FUNCTIONNAME()
#define SchM_Exit_Com_RxSigBuff(FUNCTIONNAME)       SchM_Exit_Com_RxSigBuff_##FUNCTIONNAME()

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxPduBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxPduBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RXINDICATION (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RXINDICATION (void);


LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL (void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL (void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void){
     __DI();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void){
     __DI();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxPduBuffer(void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxPduBuffer(void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RXINDICATION (void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RXINDICATION (void){
     __EI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void){
     __DI();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void){
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

