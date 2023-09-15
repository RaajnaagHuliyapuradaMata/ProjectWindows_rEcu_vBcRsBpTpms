#pragma once
/******************************************************************************/
/* File   : SwcApplTpms_abs_lin.hpp                                           */
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
#include "tss_stdx.hpp"
#include "iTPMS_Interface.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cABS_DEBUG_MODE        TRUE

#ifdef BUILD_LORDSTOWN
#define ABS_SIG_SIZE_10BIT
#define cAbsOverflowValue 0x3E8
#else
#define ABS_SIG_SIZE_ONEBYTE 	//SSC take over from MFA2
#endif

//SSC
#ifdef ABS_SIG_SIZE_ONEBYTE
#define cAbsOverflowValue 0xFF //SYMC ABS-Counter count the edges from 0 to 254
#endif

#define ABS_SIG_FFFF_IS_INVALID

#ifdef ABS_SIG_FFFF_IS_INVALID
#define cAbsOverflowCorrection 0
#else
#define cAbsOverflowCorrection 1
#endif

#define cTimeOverflowValue 0xFFFFFFFFU

#ifdef _WINDLL
#define cAbsBufferSize 30 //in SIL tests, based on how SHILT is transmitting the ABS data, the abs buffer size has to be bigger
#else
#define cAbsBufferSize 30
#endif

#define c1ST_ABS_SIG                          ((uint8) 0x00)
#define c2ND_ABS_SIG                          ((uint8) 0x01)

#define cDEBUG_ERROR_NO_ERROR                 ((uint8) 0x00)
#define cDEBUG_ERROR_OVERFLOW_ABSTIMEDIFF     ((uint8) 0x01)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVL        ((uint8) 0x02)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTVR        ((uint8) 0x04)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHL        ((uint8) 0x08)
#define cDEBUG_ERROR_OVERFLOW_ABSCNTHR        ((uint8) 0x10)

#define cNUMBER_OF_WHEELS                     ((uint8) 0x04)
#define cFRONT_LEFT                           ((uint8) 0x00)
#define cFRONT_RIGHT                          ((uint8) 0x01)
#define cREAR_LEFT                            ((uint8) 0x02)
#define cREAR_RIGHT                           ((uint8) 0x03)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct typedef_struct_tABS_DATA{
  uint32 ulAbsTimeStamp;                    // time stamp ABS-Signal
  uint16 aushAbsCnt[cNUMBER_OF_WHEELS];     // Edge counter (ABS signal) for all wheels
  uint8 aucOverflowCnt[cNUMBER_OF_WHEELS];  // Overflow counter for all wheels
}tABS_DATA;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#ifdef ABS_LIN_C
static uint8 ucAbsState;          // is needed for state control
static tABS_DATA tAbsDataBuff[cAbsBufferSize];//!< Global ABS Buffer
static uint16 ushLinAbsData [4];  //!< Linearized ABS counter
static uint8 ucAbsIndex;          //!< index inside the buffer
static uint8 ucABSIndex1, ucABSIndex2;
static  uint8 aucPreviousOverflowCnt[cNUMBER_OF_WHEELS];
static  uint8 aucCurrentOverflowCnt[cNUMBER_OF_WHEELS];
#endif

#if(cABS_DEBUG_MODE == TRUE)
#ifdef ABS_LIN_C
  uint32 ulDebugAbsTimeDiff     = 0; // Zeitlicher Abstand zwischen 1. und 2. ABS-Botschaft
  uint32 ulDebugRfTimeStamp     = 0; // Zeitstempel des aktuellen RF-Telegramms
  uint32 ulDebugRfTimeStampDiff = 0; // Zeitlicher Abstand zwischen letztem und aktuellem RF-Telegramm
  uint32 ulDebugAbs2RfTimeDiff  = 0; // Zeitlicher Abstand zwischen 1. ABS-Botschaft und aktuellem RF-Telegramm
  uint16 ushDebugAbsCntVlDiff    = 0; // Anzahl der Raddrehimpulse des ABS-Sensors vorne links zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugAbsCntVrDiff    = 0; // Anzahl der Raddrehimpulse des ABS-Sensors vorne rechts zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugAbsCntHlDiff    = 0; // Anzahl der Raddrehimpulse des ABS-Sensors hinten links zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugAbsCntHrDiff    = 0; // Anzahl der Raddrehimpulse des ABS-Sensors hinten rechts zwischen 1. und 2. ABS-Botschaft
  uint16 ushDebugDivisor         = 0; // Teiler fur Linearisierung
  uint16 ushDebugAbsCntVlLin     = 0; // Linearisierte Raddrehimpulse des ABS-Sensors vorne links
  uint16 ushDebugAbsCntVrLin     = 0; // Linearisierte Raddrehimpulse des ABS-Sensors vorne rechts
  uint16 ushDebugAbsCntHlLin     = 0; // Linearisierte Raddrehimpulse des ABS-Sensors hinten links
  uint16 ushDebugAbsCntHrLin     = 0; // Linearisierte Raddrehimpulse des ABS-Sensors hinten rechts
  uint8  ucDebugError            = 0; // Fehlervariable
#endif
#endif

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#ifdef ABS_LIN_C
  static uint16 ushCalcABS(uint32 ulRfTimeStamp, uint32 ul1stAbsTimeStamp, uint16 ush1stAbsCnt, uint32 ul2ndAbsTimeStamp, uint16 ush2ndAbsCnt );
  static void HandleOverflowABS(uint8 ucWheelPosition, uint8 ucABSTicksAx);
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

