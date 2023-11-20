

#ifndef _abs_lin_H
#define _abs_lin_H

#include "tss_stdx.hpp"
#include "iTPMS_Interface.hpp"

#define cABS_DEBUG_MODE        TRUE

#define ABS_SIG_SIZE_ONEBYTE 	//SSC take over from MFA2

//SSC
#ifdef ABS_SIG_SIZE_ONEBYTE
   #define cAbsOverflowValue 0xFF //SYMC ABS-Counter count the edges from 0 to 254
#else
   #define cAbsOverflowValue 0xFFFF
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

typedef struct typedef_struct_tABS_DATA
{
  uint32 ulAbsTimeStamp;                    // time stamp ABS-Signal
  uint16 aushAbsCnt[cNUMBER_OF_WHEELS];     // Edge counter (ABS signal) for all wheels
  uint8 aucOverflowCnt[cNUMBER_OF_WHEELS];  // Overflow counter for all wheels
}tABS_DATA;

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

#ifdef ABS_LIN_C
  static uint16 ushCalcABS(uint32 ulRfTimeStamp, uint32 ul1stAbsTimeStamp, uint16 ush1stAbsCnt, uint32 ul2ndAbsTimeStamp, uint16 ush2ndAbsCnt );
  static void HandleOverflowABS(uint8 ucWheelPosition, uint8 ucABSTicksAx);
#endif

#endif
