#pragma once
/******************************************************************************/
/* File   : Com_Cfg_SchM.hpp                                                  */
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

#if(COM_ECUC_RB_RTE_IN_USE == STD_ON)
#include "SchM_Com.hpp"
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define SchM_Enter_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Enter_Com_TxIpduProtArea_##FUNCTIONNAME()
#define SchM_Exit_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Exit_Com_TxIpduProtArea_##FUNCTIONNAME()
#define SchM_Enter_Com_RxSigBuff(FUNCTIONNAME) SchM_Enter_Com_RxSigBuff_##FUNCTIONNAME()
#define SchM_Exit_Com_RxSigBuff(FUNCTIONNAME) SchM_Exit_Com_RxSigBuff_##FUNCTIONNAME()

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_MAINFUNCTION_ROUTE_SIGNALS(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_MAINFUNCTION_ROUTE_SIGNALS(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);

#if(defined(COM_TxFilters) && defined(COM_TX_SIGNALGROUP))
LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void);
#endif

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_IPDUGROUPSTART(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_IPDUGROUPSTART(void);

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SWITCHTXIPDU(void);
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SWITCHTXIPDU(void);

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE void SchM_Enter_Com_TxGrpSigBuffer(void);
LOCAL_INLINE void SchM_Exit_Com_TxGrpSigBuffer(void);
#endif

LOCAL_INLINE void SchM_Enter_Com_RxPduBuffer(void);
LOCAL_INLINE void SchM_Exit_Com_RxPduBuffer(void);

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE void SchM_Enter_Com_RxGrpSigSecBuff (void);
LOCAL_INLINE void SchM_Exit_Com_RxGrpSigSecBuff (void);
#endif

#if defined( COM_RX_SIGNALGROUP_ARRAY )
LOCAL_INLINE void SchM_Enter_Com_RxSigGrpArrayBuff(void);
LOCAL_INLINE void SchM_Exit_Com_RxSigGrpArrayBuff(void);
#endif

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE void SchM_Enter_Com_RxGrpSigBuff(void);
LOCAL_INLINE void SchM_Exit_Com_RxGrpSigBuff (void);
#endif

LOCAL_INLINE void SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void);
LOCAL_INLINE void SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void);

LOCAL_INLINE void SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void);
LOCAL_INLINE void SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void);

LOCAL_INLINE void SchM_Enter_Com_RxSigBuff_RXINDICATION (void);
LOCAL_INLINE void SchM_Exit_Com_RxSigBuff_RXINDICATION (void);

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
LOCAL_INLINE void SchM_Enter_Com_RxSigDynBuff (void);
LOCAL_INLINE void SchM_Exit_Com_RxSigDynBuff (void);
#endif

#ifdef COM_RxSigUpdateTimeout
LOCAL_INLINE void SchM_Enter_Com_RxSigToTicks (void);
LOCAL_INLINE void SchM_Exit_Com_RxSigToTicks (void);
#endif

#ifdef COM_RxSigGrpUpdateTimeout
LOCAL_INLINE void SchM_Enter_Com_RxSigGrpToTicks(void);
LOCAL_INLINE void SchM_Exit_Com_RxSigGrpToTicks(void);
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

LOCAL_INLINE void SchM_Enter_Com_RxSigGwMcLockProtArea (void);
LOCAL_INLINE void SchM_Exit_Com_RxSigGwMcLockProtArea (void);

#endif

#ifdef COM_PDUBASEDLOCKSENABLED
#if defined(COM_SIGNALGATEWAY) || defined(COM_SIGNALGROUPGATEWAY)
LOCAL_INLINE void SchM_Enter_Com_RxGateway(void);
LOCAL_INLINE void SchM_Exit_Com_RxGateway(void);
#endif

LOCAL_INLINE void SchM_Enter_Com_RxIPduProcess(void);
LOCAL_INLINE void SchM_Exit_Com_RxIPduProcess(void);

LOCAL_INLINE void SchM_Enter_Com_RxIndication(void);
LOCAL_INLINE void SchM_Exit_Com_RxIndication(void);

LOCAL_INLINE void SchM_Enter_Com_TxIPdu(void);
LOCAL_INLINE void SchM_Exit_Com_TxIPdu(void);
#endif

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL (void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL (void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_MAINFUNCTION_ROUTE_SIGNALS(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_MAINFUNCTION_ROUTE_SIGNALS(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void){

   __EI();
}

#if(defined(COM_TxFilters) && defined(COM_TX_SIGNALGROUP))

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void){

   __EI();
}
#endif

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_IPDUGROUPSTART(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_IPDUGROUPSTART(void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_TxIpduProtArea_SWITCHTXIPDU(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_TxIpduProtArea_SWITCHTXIPDU(void){

   __EI();
}

#ifdef COM_TX_SIGNALGROUP

LOCAL_INLINE void SchM_Enter_Com_TxGrpSigBuffer(void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_TxGrpSigBuffer(void){

   __EI();
}
#endif

LOCAL_INLINE void SchM_Enter_Com_RxPduBuffer(void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_RxPduBuffer(void){

   __EI();
}

#ifdef COM_RxSigUpdateTimeout

LOCAL_INLINE void SchM_Enter_Com_RxSigToTicks (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigToTicks (void){

   __EI();
}
#endif

#ifdef COM_RxSigGrpUpdateTimeout

LOCAL_INLINE void SchM_Enter_Com_RxSigGrpToTicks (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigGrpToTicks (void){

   __EI();
}
#endif

LOCAL_INLINE void SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void){

   __DI();
}
LOCAL_INLINE void SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_RxSigBuff_RXINDICATION (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigBuff_RXINDICATION (void){

   __EI();
}

LOCAL_INLINE void SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void){

   __EI();
}

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT

LOCAL_INLINE void SchM_Enter_Com_RxSigDynBuff (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigDynBuff (void){

   __EI();
}
#endif

#ifdef COM_RX_SIGNALGROUP

LOCAL_INLINE void SchM_Enter_Com_RxGrpSigSecBuff (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxGrpSigSecBuff(void){

   __EI();
}
#endif

#if defined( COM_RX_SIGNALGROUP_ARRAY )

LOCAL_INLINE void SchM_Enter_Com_RxSigGrpArrayBuff(void)
{

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigGrpArrayBuff(void)
{

   __EI();
}
#endif

#ifdef COM_RX_SIGNALGROUP

LOCAL_INLINE void SchM_Enter_Com_RxGrpSigBuff (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxGrpSigBuff (void){

   __EI();
}
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

LOCAL_INLINE void SchM_Enter_Com_RxSigGwMcLockProtArea (void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxSigGwMcLockProtArea (void){

   __EI();
}

#endif

# if(defined(COM_PDUBASEDLOCKSENABLED)) && (defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY))
LOCAL_INLINE void SchM_Enter_Com_RxGateway(void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxGateway(void){

   __EI();
}
# endif

# ifdef COM_PDUBASEDLOCKSENABLED
LOCAL_INLINE void SchM_Enter_Com_RxIPduProcess(void){

    __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxIPduProcess(void){

    __EI();
}
# endif

# ifdef COM_PDUBASEDLOCKSENABLED
LOCAL_INLINE void SchM_Enter_Com_RxIndication(void){

    __DI();
}

LOCAL_INLINE void SchM_Exit_Com_RxIndication(void){

    __EI();
}
# endif

# ifdef COM_PDUBASEDLOCKSENABLED
LOCAL_INLINE void SchM_Enter_Com_TxIPdu(void){

   __DI();
}

LOCAL_INLINE void SchM_Exit_Com_TxIPdu(void){

   __EI();
}
# endif

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

