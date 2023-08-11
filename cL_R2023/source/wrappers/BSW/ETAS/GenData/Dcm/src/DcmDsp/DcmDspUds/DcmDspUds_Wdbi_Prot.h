

#ifndef DCMDSPUDS_WDBI_PROT_H
#define DCMDSPUDS_WDBI_PROT_H

#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

typedef   Std_ReturnType (*WriteFncRange1_pfct) ( uint16 DID,
		  const uint8 * Data,
		  Dcm_OpStatusType OpStatus,
		  uint16 DataLength,
		  Dcm_NegativeResponseCodeType * ErrorCode
		);

typedef   Std_ReturnType (*WriteFncRange2_pfct) ( uint16 DID,
        const uint8 * Data,
		  Dcm_OpStatusType OpStatus,
		  uint16 DataLength,
		  Dcm_NegativeResponseCodeType * ErrorCode
		);

typedef Std_ReturnType (*WdbiFnc1_pfct) (const uint8 * Data,
                                    uint16 DataLength,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc2_pfct) (const uint8 * Data,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc18_pfct) (const uint8 * Data,
                                    uint16 DataLength,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc19_pfct) (const uint8 * Data,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc3_pfct) (const uint8 * Data,
                                    uint16 DataLength,
                                    Dcm_OpStatusType OpStatus,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc4_pfct) (const uint8 * Data,
                                    Dcm_OpStatusType OpStatus,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc20_pfct) (const uint8 * Data,
                                    uint16 DataLength,
                                    Dcm_OpStatusType OpStatus,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*WdbiFnc21_pfct) (const uint8 * Data,
                                    Dcm_OpStatusType OpStatus,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

#if(DCM_CFG_DSP_WRITE_ASP_ENABLED != DCM_CFG_OFF)

typedef Std_ReturnType (*WdbiFnc22_pfct) (const uint8 * Data,
                                    Dcm_OpStatusType OpStatus);

typedef Std_ReturnType (*WdbiFnc23_pfct) (const uint8 * Data,
                                    uint16 DataLength,
                                    Dcm_OpStatusType OpStatus);

typedef Std_ReturnType (*WdbiFnc24_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);
#endif

typedef Std_ReturnType (*WdbiFnc5_pfct) (boolean Data);
typedef Std_ReturnType (*WdbiFnc6_pfct) (uint8 Data);
typedef Std_ReturnType (*WdbiFnc7_pfct) (uint16 Data);
typedef Std_ReturnType (*WdbiFnc8_pfct) (uint32 Data);
typedef Std_ReturnType (*WdbiFnc9_pfct) (sint8 Data);
typedef Std_ReturnType (*WdbiFnc10_pfct) (sint16 Data);
typedef Std_ReturnType (*WdbiFnc11_pfct) (sint32 Data);
typedef Std_ReturnType (*WdbiFnc12_pfct) (const uint8 * Data);
typedef Std_ReturnType (*WdbiFnc13_pfct) (const uint16 * Data);
typedef Std_ReturnType (*WdbiFnc14_pfct) (const uint32 * Data);
typedef Std_ReturnType (*WdbiFnc15_pfct) (const sint8 * Data);
typedef Std_ReturnType (*WdbiFnc16_pfct) (const sint16 * Data);
typedef Std_ReturnType (*WdbiFnc17_pfct) (const sint32 * Data);

#endif
#endif

