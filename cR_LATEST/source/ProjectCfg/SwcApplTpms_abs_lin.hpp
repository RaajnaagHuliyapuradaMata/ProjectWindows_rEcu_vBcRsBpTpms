#ifndef _abs_lin_H
#define _abs_lin_H

#include "tss_stdx.hpp"
#include "iTPMS_Interface.hpp"

#define cABS_DEBUG_MODE        TRUE
#define ABS_SIG_SIZE_ONEBYTE
#define cAbsOverflowValue 0xFF
#define ABS_SIG_FFFF_IS_INVALID
#define cAbsOverflowCorrection 0
#define cTimeOverflowValue 0xFFFFFFFFU
#define cAbsBufferSize 30
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
   uint32 ulAbsTimeStamp;
   uint16 aushAbsCnt[cNUMBER_OF_WHEELS];
   uint8 aucOverflowCnt[cNUMBER_OF_WHEELS];
}tABS_DATA;

#endif
