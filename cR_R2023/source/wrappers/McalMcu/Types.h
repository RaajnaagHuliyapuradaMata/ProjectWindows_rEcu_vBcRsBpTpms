

#ifndef _COMMON_H_
#define _COMMON_H_

//#include "Platform_Types.h"   //RST -> mehrfache Typdefinitionen eliminiert. Alles nur noch in Platform_Types.h
#include "Std_Types.h"

//
#define bool                rBool
#define false               0
#define true                1

// RST: Standard Autosar Types nur noch in Platform_Types.h definiert!
//#define TRUE (unsigned char) 1
//#define FALSE (unsigned char) 0
//
#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN (-9223372036854775807LL - 1LL)

#define INT8_MAX (127)
#define INT16_MAX (32767)
#define INT32_MAX (2147483647)
#define INT64_MAX (9223372036854775807LL)

#define UINT8_MAX (255)
#define UINT16_MAX (65535)
#define UINT32_MAX (4294967295U)
#define UINT64_MAX (18446744073709551615ULL)
//
//
//
//
//
//
//
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed long  int32_t;
//
//typedef uint8_t  uint8;
//typedef uint16_t uint16;
//typedef uint32_t uint32;
//
//typedef signed char  sint8;
//typedef signed short sint16;
//typedef signed long  sint32;
//
//typedef unsigned char boolean;
//
//
//
//
//
//struct ADC_R
//{
//  uint8 ch;
//  uint16 result;
//  uint8 err;
//};
//
//typedef struct ADC_R ADC_Return;

#endif
