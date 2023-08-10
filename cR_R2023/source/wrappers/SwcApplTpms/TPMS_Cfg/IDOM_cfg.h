

#if !defined(EA_A83A7579_EED8_44b4_B880_9ED064B14782__INCLUDED_)
#define EA_A83A7579_EED8_44b4_B880_9ED064B14782__INCLUDED_

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "Tpms_Rte_Data_Type.h"
#endif

#ifdef IBTCM_SW_ANPASSUNGEN

#define ucDefOffsetInRSSIc   ((uint8)46)
#else
//#define cADCResInmVx100 488
#define cADCResInmVx100 977
//#define cADCResInmVx100 1953

//#define cOverlapsInmV 88
//#define cOverlaps ((unsigned short)( cOverlapsInmV * 100 ) / cADCResInmVx100)

#define ucDefOffsetInRSSIcInmV 400
#define ucDefOffsetInRSSIc (unsigned char) ((unsigned short) (ucDefOffsetInRSSIcInmV *100) / cADCResInmVx100)
#endif

#define ushHFiAlarmTimeInSec         ((unsigned short)600)
//#define ucMaxFF4RFInterference          ((unsigned char)4)
#define ucMaxFF4RFInterference          ((unsigned char)133)
#define ushMaxTimeWithoutMsgInSec ((unsigned short)(9*60))

#endif

