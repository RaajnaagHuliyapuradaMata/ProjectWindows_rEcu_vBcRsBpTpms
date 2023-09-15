#pragma once
/******************************************************************************/
/* File   : PduR_Cfg_SchM.hpp                                                 */
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
#include "rba_BswSrv.hpp"
#include "Os.hpp"

#if( PDUR_ECUC_RB_RTE_IN_USE == STD_ON )
#include "SchM_PduR.hpp"
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
LOCAL_INLINE void SchM_Enter_PduR_LockTpGatewayBuffer(void);
LOCAL_INLINE void SchM_Exit_PduR_LockTpGatewayBuffer(void);
LOCAL_INLINE void SchM_Enter_PduR_LockDisableRoutingNoNest(void);
LOCAL_INLINE void SchM_Exit_PduR_LockDisableRoutingNoNest(void);
LOCAL_INLINE void SchM_Enter_PduR_LockEnableRoutingNoNest(void);
LOCAL_INLINE void SchM_Exit_PduR_LockEnableRoutingNoNest(void);
LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTx(void);
LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTx(void);
LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTxConf(void);
LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTxConf(void);
LOCAL_INLINE void SchM_Enter_PduR_LockTpGatewayCopyRxData(void);
LOCAL_INLINE void SchM_Exit_PduR_LockTpGatewayCopyRxData(void);
LOCAL_INLINE void SchM_Enter_PduR_LockTpGatewayCopyTxDataNoNest(void);
LOCAL_INLINE void SchM_Exit_PduR_LockTpGatewayCopyTxDataNoNest(void);
LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(void);
LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest(void);
LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTriggerTx(void);
LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTriggerTx(void);
LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTriggerTxConf(void);
LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTriggerTxConf(void);
LOCAL_INLINE void SchM_Enter_PduR_LockMcTpTxCopyTxData(void);
LOCAL_INLINE void SchM_Exit_PduR_LockMcTpTxCopyTxData(void);
LOCAL_INLINE void SchM_Enter_PduR_LockMcTpTxConf(void);
LOCAL_INLINE void SchM_Exit_PduR_LockMcTpTxConf(void);
LOCAL_INLINE void SchM_Enter_PduR_LockMCTxConfNoNest(void);
LOCAL_INLINE void SchM_Exit_PduR_LockMCTxConfNoNest(void);

LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTx(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTx(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTxConf(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTxConf(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTriggerTxConf(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTriggerTxConf(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockEnableRoutingNoNest(void){
   __DI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(void){
   __DI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockIFGatewayTriggerTx(void){
   __DI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockDisableRoutingNoNest(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockDisableRoutingNoNest(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockMCTxConfNoNest(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockMCTxConfNoNest(void){
   __EI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest(void){
   __EI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockIFGatewayTriggerTx(void){
   __EI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockEnableRoutingNoNest(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockTpGatewayBuffer(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockTpGatewayBuffer(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockTpGatewayCopyRxData(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockTpGatewayCopyRxData(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockMcTpTxCopyTxData(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockMcTpTxCopyTxData(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockMcTpTxConf(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockMcTpTxConf(void){
   __EI();
}

LOCAL_INLINE void SchM_Enter_PduR_LockTpGatewayCopyTxDataNoNest(void){
   __DI();
}

LOCAL_INLINE void SchM_Exit_PduR_LockTpGatewayCopyTxDataNoNest(void){
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

