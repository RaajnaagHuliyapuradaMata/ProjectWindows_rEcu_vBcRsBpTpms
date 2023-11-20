#pragma once
/******************************************************************************/
/* File   : CompilerCfg_SwcServiceOs.hpp                                      */
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
#define SWCSERVICEOS_CODE                                                /*TBD*/
#define SWCSERVICEOS_CODE_CB                                             /*TBD*/
#define SWCSERVICEOS_CODE_FAST                                           /*TBD*/
#define SWCSERVICEOS_CODE_SLOW                                           /*TBD*/
#define SWCSERVICEOS_CONST                                               /*TBD*/
#define SWCSERVICEOS_CALIB                                               /*TBD*/
#define SWCSERVICEOS_CONFIG_DATA                                         /*TBD*/
#define SWCSERVICEOS_CONST_SAVED_RECOVERY_ZONE                           /*TBD*/
#define SWCSERVICEOS_APPL_DATA                                           /*TBD*/
#define SWCSERVICEOS_APPL_CONST                                          /*TBD*/
#define SWCSERVICEOS_VAR                                                 /*TBD*/
#define SWCSERVICEOS_VAR_FAST                                            /*TBD*/
#define SWCSERVICEOS_VAR_SLOW                                            /*TBD*/
#define SWCSERVICEOS_INTERNAL_VAR                                        /*TBD*/
#define SWCSERVICEOS_VAR_SAVED_ZONE                                      /*TBD*/

//TBD: Legacy sections
#define OS_CODE
#define OS_CODE_FAST
#define OS_CONST
#define OS_APPL_DATA
#define OS_APPL_CONST
#define OS_APPL_CODE
#define OS_VAR_NOINIT
#define OS_VAR_POWER_ON_INIT
#define OS_VAR_FAST
#define OS_VAR
#define OS_VAR_CORE0_NOINIT
#define OS_VAR_CORE1_NOINIT
#define OS_VAR_CORE0_POWER_ON_INIT
#define OS_VAR_CORE1_POWER_ON_INIT
#define OS_OS_CBK_GETABORTSTACK_CODE
#define OS_STARTUPHOOK_HUFTPMS_CODE
#define OS_SHUTDOWNHOOK_HUFTPMS_CODE
#define OS_ERRORHOOK_HUFTPMS_CODE
#define OS_OS_CBK_ALARM_CB_ALARM10MS_CODE
#define OS_OS_CBK_ALARM_CB_ALARMONESECOND_CODE
#define OS_OS_CBK_ALARM_CB_ALARM200MS_CODE
#define OS_OS_CBK_ALARM_CB_ALARM50MS_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER0_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER1_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER2_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TIMER3_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_VOLTAGEMONITOR_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_WAKEUP_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CAN0STATUS_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CANGLOBALSTATUS_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CAN0TRANSMIT_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_CAN0RECEIVE_CODE
#define OS_OS_CBK_TERMINATED_FLS_FLENDNM_CAT2_ISR_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_ONEMILLISECOND_CODE
#define OS_OS_CBK_TERMINATED_CAT2ISR_TELREC_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER0_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER1_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER2_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TIMER3_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_VOLTAGEMONITOR_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_WAKEUP_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CAN0STATUS_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CANGLOBALSTATUS_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CAN0TRANSMIT_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_CAN0RECEIVE_CODE
#define OS_OS_CBK_DISABLE_FLS_FLENDNM_CAT2_ISR_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_ONEMILLISECOND_CODE
#define OS_OS_CBK_DISABLE_CAT2ISR_TELREC_CODE
#define OS_ERRORHOOK_CODE
#define OS_PRETASKHOOK_CODE
#define OS_POSTTASKHOOK_CODE
#define OS_PROTECTIONHOOK_CODE
#define OS_STARTUPHOOK_CODE
#define OS_SHUTDOWNHOOK_CODE
#define OS_OS_CBK_CHECKMEMORYACCESS_CODE
#define OS_OS_CBK_IDLE_CODE
#define OS_OS_CBK_INSHUTDOWN_CODE
#define OS_OS_CBK_STACKOVERRUNHOOK_CODE
#define OS_OS_CBK_CHECKSTACKDEPTH_CODE
#define OS_OS_CBK_GETSTOPWATCH_CODE
#define OS_OS_CBK_TIMEOVERRUNHOOK_CODE
#define OS_OS_CBK_SUSPENDTIMELIMIT_CODE
#define OS_OS_CBK_SETTIMELIMIT_CODE
#define OS_OS_CBK_SETMEMORYACCESS_CODE
#define OS_OS_CBK_GETSETPROTECTION_CODE
#define OS_OS_CBK_TASKSTART_CODE
#define OS_OS_CBK_TASKEND_CODE
#define OS_OS_CBK_TASKACTIVATED_CODE
#define OS_OS_CBK_CROSSCOREISRSTART_CODE
#define OS_OS_CBK_CROSSCOREISREND_CODE
#define OS_OS_CBK_ISRSTART_CODE
#define OS_OS_CBK_ISREND_CODE
#define OS_OS_CBK_ISUNTRUSTEDCODEOK_CODE
#define OS_OS_CBK_ISUNTRUSTEDTRAPOK_CODE
#define OS_OS_CBK_ISSYSTEMTRAPALLOWED_CODE
#define OS_OS_CBK_RESTOREGLOBALREGISTERS_CODE
#define OS_OS_CBK_TRACECOMMINITTARGET_CODE
#define OS_OS_CBK_TRACECOMMDATAREADY_CODE
#define OS_OS_CBK_TRACECOMMTXSTART_CODE
#define OS_OS_CBK_TRACECOMMTXBYTE_CODE
#define OS_OS_CBK_TRACECOMMTXEND_CODE
#define OS_OS_CBK_TRACECOMMTXREADY_CODE

#define OS_CALLOUT_CODE  OS_APPL_CODE
#define OS_VAR_CLEARED   OS_VAR_POWER_ON_INIT
#define OS_VAR_NO_INIT   OS_VAR_NOINIT

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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
