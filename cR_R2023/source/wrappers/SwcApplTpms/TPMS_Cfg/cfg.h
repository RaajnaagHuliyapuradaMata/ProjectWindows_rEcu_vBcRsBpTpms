#ifndef CFG_H
#define CFG_H

#define FILTER_SYMC_CAN_MSGS
#define DETECT_SYMC_WALLOC_DTC
#define ZWANGSZUORDNUNG_NACH_TO
#define js_ReHighTemperatureDiag_230312 // for WS Temperature Diagnose

#ifdef IBTCM_SW_ANPASSUNGEN
#else
#define USE_TMPIS_AS_TMPIR
#define COMPILER_IS_cosmotic
#define CPU_DERIVATIVE_IS_xs256
#define xx_VwMac_250603
#define cd_DynWarnResetCond_100309
#define cd_NoSecAcc_230709
#define cInvalid (255)
#define cFalse   ( 0 )
#define cTrue    ( 1 )
#define SEC_CLASS_NONE        0
#define SEC_CLASS_C           1
#define SEC_CLASS_CCC         2
#define SEC_SECURITY_CLASS    SEC_CLASS_NONE
#define cUSWAlgo_ParaByte0 0x45
#define cUSWAlgo_ParaByte1 0x0D
#define cUSWAlgo_ParaByte2 0xF9
#define cUSWAlgo_DpRel         25
#define cUSWAlgo_EuDpRel       20
#define cUSWAlgo_DpHwIsoVlow   20
#define cUSWAlgo_DpHwIsoVhi    16
#define cUSWAlgo_DpHwIso       20
#define cUSWAlgo_DpWwIso       12
#define cUSWAlgo_DpWw          12
#define cUSWAlgo_DpHyst        0
#define cUSWAlgo_DtWw          30
#define cUSWAlgo_WWFilter      10
#define cUSWAlgo_PVmaxFA      160
#define cUSWAlgo_PVmaxRA      180
#define cUSWAlgo_Vmax           0
#define cUSWAlgo_VHyst          0
#define cUSWAlgo_DtDropHw      40
#define cUSWAlgo_TResLimit     25
#define cUSWAlgo_AdOn           0
#define cUSWAlgo_ucSDDif        8
#define cUSWAlgo_ucNegHyst      0
#define cUSWAlgo_PMinReset     12
#endif

#endif

