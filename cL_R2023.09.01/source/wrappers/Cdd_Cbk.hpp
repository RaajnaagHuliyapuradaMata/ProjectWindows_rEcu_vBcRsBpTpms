

#if !defined (CDD_CBK_H)
#define CDD_CBK_H

#include "ComStack_Types.hpp"
#include "J1939Rm_Types.hpp"

#ifndef CDD_USE_DUMMY_FUNCTIONS
#define CDD_USE_DUMMY_FUNCTIONS STD_OFF
#endif
#ifndef CDD_USE_DUMMY_STATEMENT
#define CDD_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef CDD_DUMMY_STATEMENT
#define CDD_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef CDD_DUMMY_STATEMENT_CONST
#define CDD_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef CDD_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CDD_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_ON
#endif
#ifndef CDD_ATOMIC_VARIABLE_ACCESS
#define CDD_ATOMIC_VARIABLE_ACCESS 32U
#endif
#ifndef CDD_PROCESSOR_CANOEEMU
#define CDD_PROCESSOR_CANOEEMU
#endif
#ifndef CDD_COMP_
#define CDD_COMP_
#endif
#ifndef CDD_GEN_GENERATOR_MSR
#define CDD_GEN_GENERATOR_MSR
#endif
#ifndef CDD_CPUTYPE_BITORDER_LSB2MSB
#define CDD_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef CDD_CONFIGURATION_VARIANT_PRECOMPILE
#define CDD_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CDD_CONFIGURATION_VARIANT_LINKTIME
#define CDD_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CDD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CDD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CDD_CONFIGURATION_VARIANT
#define CDD_CONFIGURATION_VARIANT CDD_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CDD_POSTBUILD_VARIANT_SUPPORT
#define CDD_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#define CDD_COMIF  STD_OFF
#define CDD_COMIF_RX  STD_OFF
#define CDD_COMIF_TX  STD_OFF
#define CDD_COMIF_TRIGGERTRANSMIT  STD_OFF

#define CDD_PDUR_UL_COMIF  STD_OFF
#define CDD_PDUR_UL_COMIF_TRIGGERTRANSMIT  STD_OFF

#define CDD_PDUR_UL_COMTP  STD_OFF

#define CDD_PDUR_LL_COMIF  STD_OFF
#define CDD_PDUR_LL_COMIF_TRIGGERTRANSMIT  STD_OFF

#define CDD_PDUR_LL_COMTP  STD_OFF

#define CDD_SOADUL_COMIF_RX  STD_OFF
#define CDD_SOADUL_COMIF_TRIGGERTRANSMIT  STD_OFF
#define CDD_SOADUL_COMIF_TXCONFIRMATION   STD_OFF

#define CDD_SOADUL_COMTP_RX  STD_OFF
#define CDD_SOADUL_COMTP_TX  STD_OFF

#define CDD_START_SEC_CODE

#include "MemMap.hpp"

FUNC(void, CDD_CODE) Cdd_RequestIndication(uint8 node, NetworkHandleType channel, uint32 requestedPgn, P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, CDD_APPL_DATA) extIdInfo, uint8 sourceAddress, uint8 destAddress, uint8 priority);

FUNC(void, CDD_CODE) Cdd_AckIndication(uint8 node, NetworkHandleType channel, uint32 ackPgn, P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, CDD_APPL_DATA) extIdInfo, J1939Rm_AckCode ackCode, uint8 ackAddress, uint8 sourceAddress, uint8 priority);

FUNC(void, CDD_CODE) Cdd_RequestTimeoutIndication(uint8 node, NetworkHandleType channel, uint32 requestedPgn, P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, CDD_APPL_DATA) extIdInfo, uint8 destAddress);

#define CDD_STOP_SEC_CODE

#include "MemMap.hpp"

#endif

