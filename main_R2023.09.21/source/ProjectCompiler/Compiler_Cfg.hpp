#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H
/******************************************************************************/
/* File   : Compiler_Cfg.h                                                    */
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
/* git@github.com:RaajnaagHuliyapuradaMata/<module_name>.git                  */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
Compiler configuration for
--------------------------------------------------------------------------------
Vendor   : Green Hills Software
Compiler : MULTI
Version  : 2015.1.7
*******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define AUTOSAR_COMSTACKDATA
#define MSR_REGSPACE                                                    REGSPACE
#define REGSPACE
#define _STATIC_                                                          STATIC

/* Move to respective CompilerCfg_<Module_Name>.h */
#define _CDD_CODE
#define _CDD_APPL_DATA

#define FEE_30_SMALLSECTOR_PUBLIC_CODE
#define FEE_30_SMALLSECTOR_PRIVATE_CODE
#define FEE_30_SMALLSECTOR_APPL_DATA
#define FEE_30_SMALLSECTOR_FAST_DATA
#define FEE_30_SMALLSECTOR_PRIVATE_CONST
#define FEE_30_SMALLSECTOR_PUBLIC_CONST
#define FEE_30_SMALLSECTOR_NVM_CODE

#define FEE_30_SMALLSECTOR_CODE FEE_30_SMALLSECTOR_PUBLIC_CODE
#define MEMIF_CODE
#define MEMIF_PRIVATE_CODE
#define MEMIF_CONST
#define MEMIF_APPL_DATA

#define NVM_APPL_DATA
#define NVM_APPL_CODE
#define NVM_APPL_CONST
#define NVM_CRC_APPL_DATA
#define NVM_CONFIG_DATA
#define NVM_CONFIG_CONST
#define NVM_FAST_DATA
#define NVM_PRIVATE_CODE
#define NVM_PRIVATE_CONST
#define NVM_PRIVATE_DATA
#define NVM_PUBLIC_CODE
#define NVM_PUBLIC_CONST
#define NVM_CODE NVM_PUBLIC_CODE

#define VSTDLIB_CODE
#define VSTDLIB_VAR_FAR
#define VSTDLIB_APPL_VAR

#define FBLBMHDR_CONST
#define FBLBMHDR_CODE

#include "CompilerCfg_SwcServiceOs.hpp"
#ifndef OS_STARTUPHOOK_HUFTPMS_CODE
#define OS_STARTUPHOOK_HUFTPMS_CODE
#endif
#ifndef OS_SHUTDOWNHOOK_HUFTPMS_CODE
#define OS_SHUTDOWNHOOK_HUFTPMS_CODE
#endif
#ifndef OS_ERRORHOOK_HUFTPMS_CODE
#define OS_ERRORHOOK_HUFTPMS_CODE
#endif
#ifndef OS_OS_CBK_ALARM_CB_ALARM10MS_CODE
#define OS_OS_CBK_ALARM_CB_ALARM10MS_CODE
#endif
#ifndef OS_OS_CBK_ALARM_CB_ALARMONESECOND_CODE
#define OS_OS_CBK_ALARM_CB_ALARMONESECOND_CODE
#endif
#ifndef OS_OS_CBK_ALARM_CB_ALARM200MS_CODE
#define OS_OS_CBK_ALARM_CB_ALARM200MS_CODE
#endif
#ifndef OS_OS_CBK_ALARM_CB_ALARM50MS_CODE
#define OS_OS_CBK_ALARM_CB_ALARM50MS_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_TIMER0_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER0_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_TIMER1_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER1_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_TIMER2_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER2_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_TIMER3_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER3_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_VOLTAGEMONITOR_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_VOLTAGEMONITOR_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_WAKEUP_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_WAKEUP_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_CAN0STATUS_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CAN0STATUS_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_CANGLOBALSTATUS_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CANGLOBALSTATUS_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_CAN0TRANSMIT_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CAN0TRANSMIT_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_CAN0RECEIVE_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CAN0RECEIVE_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_FLS_FLENDNM_CAT2_ISR_CODE
#define OS_OS_CBK_TERMINATED_FLS_FLENDNM_CAT2_ISR_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_ONEMILLISECOND_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_ONEMILLISECOND_CODE
#endif
#ifndef OS_OS_CBK_TERMINATED_CAT2ISR_TELREC_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TELREC_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_TIMER0_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER0_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_TIMER1_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER1_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_TIMER2_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER2_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_TIMER3_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER3_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_VOLTAGEMONITOR_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_VOLTAGEMONITOR_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_WAKEUP_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_WAKEUP_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_CAN0STATUS_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CAN0STATUS_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_CANGLOBALSTATUS_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CANGLOBALSTATUS_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_CAN0TRANSMIT_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CAN0TRANSMIT_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_CAN0RECEIVE_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CAN0RECEIVE_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_FLS_FLENDNM_CAT2_ISR_CODE
#define OS_OS_CBK_DISABLE_FLS_FLENDNM_CAT2_ISR_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_ONEMILLISECOND_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_ONEMILLISECOND_CODE
#endif
#ifndef OS_OS_CBK_DISABLE_CAT2ISR_TELREC_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TELREC_CODE
#endif
#ifndef OS_ERRORHOOK_CODE
#define OS_ERRORHOOK_CODE
#endif
#ifndef OS_PRETASKHOOK_CODE
#define OS_PRETASKHOOK_CODE
#endif
#ifndef OS_POSTTASKHOOK_CODE
#define OS_POSTTASKHOOK_CODE
#endif
#ifndef OS_PROTECTIONHOOK_CODE
#define OS_PROTECTIONHOOK_CODE
#endif
#ifndef OS_STARTUPHOOK_CODE
#define OS_STARTUPHOOK_CODE
#endif
#ifndef OS_SHUTDOWNHOOK_CODE
#define OS_SHUTDOWNHOOK_CODE
#endif
#ifndef OS_OS_CBK_CHECKMEMORYACCESS_CODE
#define OS_OS_CBK_CHECKMEMORYACCESS_CODE
#endif
#ifndef OS_OS_CBK_IDLE_CODE
#define OS_OS_CBK_IDLE_CODE
#endif
#ifndef OS_OS_CBK_INSHUTDOWN_CODE
#define OS_OS_CBK_INSHUTDOWN_CODE
#endif
#ifndef OS_OS_CBK_STACKOVERRUNHOOK_CODE
#define OS_OS_CBK_STACKOVERRUNHOOK_CODE
#endif
#ifndef OS_OS_CBK_CHECKSTACKDEPTH_CODE
#define OS_OS_CBK_CHECKSTACKDEPTH_CODE
#endif
#ifndef OS_OS_CBK_GETSTOPWATCH_CODE
#define OS_OS_CBK_GETSTOPWATCH_CODE
#endif
#ifndef OS_OS_CBK_TIMEOVERRUNHOOK_CODE
#define OS_OS_CBK_TIMEOVERRUNHOOK_CODE
#endif
#ifndef OS_OS_CBK_SUSPENDTIMELIMIT_CODE
#define OS_OS_CBK_SUSPENDTIMELIMIT_CODE
#endif
#ifndef OS_OS_CBK_SETTIMELIMIT_CODE
#define OS_OS_CBK_SETTIMELIMIT_CODE
#endif
#ifndef OS_OS_CBK_SETMEMORYACCESS_CODE
#define OS_OS_CBK_SETMEMORYACCESS_CODE
#endif
#ifndef OS_OS_CBK_GETSETPROTECTION_CODE
#define OS_OS_CBK_GETSETPROTECTION_CODE
#endif
#ifndef OS_OS_CBK_TASKSTART_CODE
#define OS_OS_CBK_TASKSTART_CODE
#endif
#ifndef OS_OS_CBK_TASKEND_CODE
#define OS_OS_CBK_TASKEND_CODE
#endif
#ifndef OS_OS_CBK_TASKACTIVATED_CODE
#define OS_OS_CBK_TASKACTIVATED_CODE
#endif
#ifndef OS_OS_CBK_CROSSCOREISRSTART_CODE
#define OS_OS_CBK_CROSSCOREISRSTART_CODE
#endif
#ifndef OS_OS_CBK_CROSSCOREISREND_CODE
#define OS_OS_CBK_CROSSCOREISREND_CODE
#endif
#ifndef OS_OS_CBK_ISRSTART_CODE
#define OS_OS_CBK_ISRSTART_CODE
#endif
#ifndef OS_OS_CBK_ISREND_CODE
#define OS_OS_CBK_ISREND_CODE
#endif
#ifndef OS_OS_CBK_ISUNTRUSTEDCODEOK_CODE
#define OS_OS_CBK_ISUNTRUSTEDCODEOK_CODE
#endif
#ifndef OS_OS_CBK_ISUNTRUSTEDTRAPOK_CODE
#define OS_OS_CBK_ISUNTRUSTEDTRAPOK_CODE
#endif
#ifndef OS_OS_CBK_ISSYSTEMTRAPALLOWED_CODE
#define OS_OS_CBK_ISSYSTEMTRAPALLOWED_CODE
#endif
#ifndef OS_OS_CBK_RESTOREGLOBALREGISTERS_CODE
#define OS_OS_CBK_RESTOREGLOBALREGISTERS_CODE
#endif
#ifndef OS_OS_CBK_TRACECOMMINITTARGET_CODE
#define OS_OS_CBK_TRACECOMMINITTARGET_CODE
#endif
#ifndef OS_OS_CBK_TRACECOMMDATAREADY_CODE
#define OS_OS_CBK_TRACECOMMDATAREADY_CODE
#endif
#ifndef OS_OS_CBK_TRACECOMMTXSTART_CODE
#define OS_OS_CBK_TRACECOMMTXSTART_CODE
#endif
#ifndef OS_OS_CBK_TRACECOMMTXBYTE_CODE
#define OS_OS_CBK_TRACECOMMTXBYTE_CODE
#endif
#ifndef OS_OS_CBK_TRACECOMMTXEND_CODE
#define OS_OS_CBK_TRACECOMMTXEND_CODE
#endif
#ifndef OS_OS_CBK_TRACECOMMTXREADY_CODE
#define OS_OS_CBK_TRACECOMMTXREADY_CODE
#endif

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define UNUSED(x)                                                      ((void)x)/*(x=x)*/

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
#endif

