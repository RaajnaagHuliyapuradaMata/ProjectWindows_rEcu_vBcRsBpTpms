
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "Rte_Dcm.h"

#include "DcmDspUds_Uds_Prot.h"
#include "rba_BswSrv.h"

#include "ComM_Dcm.h"

#include "DcmDspUds_Rc_Prot.h"

#include "DcmDspUds_Rdtc_Priv.h"

#include "DcmDspUds_Er_Prot.h"

#include "DcmDspUds_Cdtcs_Prot.h"

#include "DcmDspUds_RequestDownload_Prot.h"

#include "DcmAppl.h"

#include "DcmCore_DslDsd_Prot.h"

#include "DcmAppInterfaceX.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
const Dcm_Dsp_Session_t Dcm_Dsp_Session[DCM_CFG_DSP_NUMSESSIONS] =
{

   {
		50000,				
		5000000,				
		0x1,				
		DCM_NO_BOOT			
	},

   {
		50000,				
		5000000,				
		0x2,				
		DCM_NO_BOOT			
	},

   {
		50000,				
		5000000,				
		0x3,				
		DCM_NO_BOOT			
	},

   {
		50000,				
		5000000,				
		0x4,				
		DCM_NO_BOOT			
	},

   {
		50000,				
		5000000,				
		0x60,				
		DCM_SYS_BOOT			
	}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
const Dcm_Dsp_Security_t Dcm_Dsp_Security[DCM_CFG_DSP_NUMSECURITY] =
{

   {

        50,

		5,			

		
		(void*)	&SecaFBL_GetSeed,
		
		(void*)	&SecaFBL_CompareKey,
		0x1, 		
		16,			
		16,			
		5,			
		0,			
		0,			
		USE_ASYNCH_FNC,				  		  FALSE
	}
,

   {

        50,

		5,			

		
		(void*)	&SecaDATA_GetSeed,
		
		(void*)	&SecaDATA_CompareKey,
		0x2, 		
		16,			
		16,			
		5,			
		0,			
		0,			
		USE_ASYNCH_FNC,				  		  FALSE
	}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#if (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
sint16 Dcm_RCSigOutN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
sint32 Dcm_RCSigOutN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
sint8 Dcm_RCSigOutN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
uint32 Dcm_RCSigOutN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
uint16 Dcm_RCSigOutN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

typedef enum
{
    DcmDspRoutine_EOL_Test_Procedure_DcmDspStopRoutineOutSignal_0_StpOut,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspStartRoutineOutSignal_0_StrtOut,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_0_ReqRsltOut,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_1_ReqRsltOut,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_2_ReqRsltOut,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_3_ReqRsltOut,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_4_ReqRsltOut,
    DCM_RC_SIGOUTUINT8MAX
} Dcm_DspRoutineSigOutUInt8Idx_ten;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static uint8 Dcm_RCSigOut_au8[7];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
uint8 Dcm_RCSigOutN_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
sint16 Dcm_RCSigInN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
sint32 Dcm_RCSigInN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
sint8 Dcm_RCSigInN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
uint32 Dcm_RCSigInN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
uint16 Dcm_RCSigInN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

typedef enum
{
    DcmDspRoutine_EOL_Test_Procedure_DcmDspStopRoutineInSignal_0_StpIn,
    DcmDspRoutine_EOL_Test_Procedure_DcmDspStartRoutineInSignal_0_StrtIn,
    DCM_RC_SIGINUINT8MAX
} Dcm_DspRoutineSigInUInt8Idx_ten;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static uint8 Dcm_RCSigIn_au8[2];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DcmDspRoutine_ClearMem_DcmDspStartRoutineInSignal_Password_StrtIn  0u

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
uint8 Dcm_RCSigInN_au8[10];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

uint32 Dcm_RCGetSigVal_u32 ( uint8 dataSigType_en, uint16 idxSignalIndex_u16 )
{
    uint32 dataSigVal_u32;

 if(dataSigType_en == DCM_UINT8)
    {
        dataSigVal_u32 = (uint32)Dcm_RCSigOut_au8[idxSignalIndex_u16];
    }
	else	
	{
        dataSigVal_u32 = 0;
	}

    return (dataSigVal_u32);
}

void Dcm_RCSetSigVal ( uint8 dataSigType_en, uint16 idxSignalIndex_u16, uint32 dataSigVal_u32)
{

 if(dataSigType_en == DCM_UINT8)
    {
        Dcm_RCSigIn_au8[idxSignalIndex_u16]=(uint8)dataSigVal_u32;
    }
	else	
    {
        (void)dataSigVal_u32;
        (void)idxSignalIndex_u16;
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

static const Dcm_DspRoutineSignalInfo_tst DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StpInSig[]=
{
   {
        0,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspStopRoutineInSignal_0_StpIn,
        DCM_OPAQUE,
         DCM_UINT8
    }
};

static const Dcm_DspRoutineSignalInfo_tst DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StrtInSig[]=
{
     {
        0,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspStartRoutineInSignal_0_StrtIn,
        DCM_OPAQUE,
        DCM_UINT8
    }
};

static const Dcm_DspRoutineSignalInfo_tst DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StrtOutSig[]=
{
   {
        0,
        8,
	    DcmDspRoutine_EOL_Test_Procedure_DcmDspStartRoutineOutSignal_0_StrtOut,
	    DCM_OPAQUE,
	   DCM_UINT8
    }
};

static const Dcm_DspRoutineSignalInfo_tst DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StopOutSig[]=
{
   {
        0,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspStopRoutineOutSignal_0_StpOut,
        DCM_OPAQUE,
        DCM_UINT8
    }
};

static const Dcm_DspRoutineSignalInfo_tst DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_ReqRsltOutSig[]=
{
    {
        0,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_0_ReqRsltOut,
        DCM_OPAQUE,
        DCM_UINT8
    }
,
    {
        8,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_1_ReqRsltOut,
        DCM_OPAQUE,
        DCM_UINT8
    }
,
    {
        16,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_2_ReqRsltOut,
        DCM_OPAQUE,
        DCM_UINT8
    }
,
    {
        24,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_3_ReqRsltOut,
        DCM_OPAQUE,
        DCM_UINT8
    }
,
    {
        32,
        8,
        DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_4_ReqRsltOut,
        DCM_OPAQUE,
        DCM_UINT8
    }
};

static const Dcm_DspRoutineSignalInfo_tst DcmDspRc_DcmDspRoutine_ClearMem_StrtInSig[]=
{
     {
        0,
        80,
        DcmDspRoutine_ClearMem_DcmDspStartRoutineInSignal_Password_StrtIn,
        DCM_BIG_ENDIAN,
        DCM_UINT8_N
    }
};

static const Dcm_DspRoutineInfoType_tst DcmDspRc_DcmDspRoutine_ECU_Self_Test=
{

  0xFFFFFFFFuL,

  0xFFFFFFFFuL,
     NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0
};

static const Dcm_DspRoutineInfoType_tst DcmDspRc_DcmDspRoutine_EOL_Test_Procedure=
{

  0xFFFFFFFFuL,

  0xFFFFFFFFuL,
     NULL_PTR,

    DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StrtInSig,

    DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StpInSig,

    NULL_PTR,

    DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StrtOutSig,

    DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_StopOutSig,

    DcmDspRc_DcmDspRoutine_EOL_Test_Procedure_ReqRsltOutSig,

    1,

    1,

    0,

    1,

    1,

    5,

    1,

    1,

    0,

    1,

    1,

    5,

    1,

    1,

    0,

    1,

    1,

    5
};

static const Dcm_DspRoutineInfoType_tst DcmDspRc_DcmDspRoutine_ClearMem=
{

  0xFFFFFFFFuL,

  0xFFFFFFFFuL,
     NULL_PTR,

    DcmDspRc_DcmDspRoutine_ClearMem_StrtInSig,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    NULL_PTR,

    10,

    0,

    0,

    0,

    0,

    0,

    10,

    0,

    0,

    0,

    0,

    0,

    1,

    0,

    0,

    0,

    0,

    0
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static Std_ReturnType Dcm_Dsp_RC_DcmDspRoutine_ECU_Self_Test_Func ( uint8 dataSubFunc_u8 )
{
    Std_ReturnType dataRetVal_u8;
    dataRetVal_u8 = E_NOT_OK;

    switch (dataSubFunc_u8)
    {
    case 1u:
        dataRetVal_u8 = DcmDsp_StartSelfTest_Callback
                (
                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCNegResCode_u8)
                  );

        break;

    case 3u:
        dataRetVal_u8 = DcmDsp_RequestResultSelfTest_Callback
                (
                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCNegResCode_u8)
                );
        break;

    default:
        Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
    }

    return (dataRetVal_u8);
}

static Std_ReturnType Dcm_Dsp_RC_DcmDspRoutine_EOL_Test_Procedure_Func ( uint8 dataSubFunc_u8 )
{
    Std_ReturnType dataRetVal_u8;
    dataRetVal_u8 = E_NOT_OK;

    switch (dataSubFunc_u8)
    {
    case 1u:
        dataRetVal_u8 = DcmDsp_StartVehicleEolTestProcedure_Callback
                (
Dcm_RCSigIn_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspStartRoutineInSignal_0_StrtIn],
                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspStartRoutineOutSignal_0_StrtOut]),
                    &(Dcm_RCNegResCode_u8)
                  );

        break;

    case 2u:
        dataRetVal_u8 = DcmDsp_StopVehicleEolTestProcedure_Callback
                (
Dcm_RCSigIn_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspStopRoutineInSignal_0_StpIn],                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspStopRoutineOutSignal_0_StpOut]),
                    &(Dcm_RCNegResCode_u8)
                );

        break;

    case 3u:
        dataRetVal_u8 = DcmDsp_RequestResultVehicleEolTestProcedure_Callback
                (
                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_0_ReqRsltOut]),
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_1_ReqRsltOut]),
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_2_ReqRsltOut]),
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_3_ReqRsltOut]),
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_EOL_Test_Procedure_DcmDspRequestRoutineResultsOutSignal_4_ReqRsltOut]),
                    &(Dcm_RCNegResCode_u8)
                );
        break;

    default:
        Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
    }

    return (dataRetVal_u8);
}

static Std_ReturnType Dcm_Dsp_RC_DcmDspRoutine_ClearMem_Func ( uint8 dataSubFunc_u8 )
{
    Std_ReturnType dataRetVal_u8;
    dataRetVal_u8 = E_NOT_OK;

    switch (dataSubFunc_u8)
    {
    case 1u:
        dataRetVal_u8 = DcmDsp_StartResetEepromCallback
                (
&Dcm_RCSigInN_au8[DcmDspRoutine_ClearMem_DcmDspStartRoutineInSignal_Password_StrtIn],
                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCNegResCode_u8)
                  );

        break;

    default:
        Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
    }

    return (dataRetVal_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

const Dcm_DspRoutineType_tst Dcm_DspRoutine_cast[DCM_CFG_RC_NUMRIDS]=
{

    {
        0x1248,
        TRUE,
        FALSE,
        &DcmDspRc_DcmDspRoutine_ClearMem,
        &Dcm_Dsp_RC_DcmDspRoutine_ClearMem_Func,

        TRUE,

        FALSE,
        FALSE,
        FALSE,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif
        FALSE,
    }
,

    {
        0xf200,
        TRUE,
        FALSE,
        &DcmDspRc_DcmDspRoutine_ECU_Self_Test,
        &Dcm_Dsp_RC_DcmDspRoutine_ECU_Self_Test_Func,

        TRUE,

        FALSE,
        FALSE,
        TRUE,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif
        TRUE,
    }
,

    {
        0xfdc2,
        TRUE,
        FALSE,
        &DcmDspRc_DcmDspRoutine_EOL_Test_Procedure,
        &Dcm_Dsp_RC_DcmDspRoutine_EOL_Test_Procedure_Func,

        TRUE,

        TRUE,
        TRUE,
        TRUE,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif
        TRUE,
    }
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

Dcm_DspRoutineStatusType_ten Dcm_RoutineStatus_aen[DCM_CFG_RC_NUMRIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#endif

//  #define DCM_START_SEC_CODE
//  #include "Dcm_MemMap.h"
// static Std_ReturnType Dcm_WriteDidSignal_Security_key_Encoded_IV_and_key(const uint8 * Data)
// {
//     return(Rte_Write_P_DataServices_Security_key_Encoded_IV_and_key_Data(Data));
// }
//
// #define DCM_STOP_SEC_CODE
// #include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
const Dcm_SignalDIDSubStructConfig_tst Dcm_DspDid_ControlInfo_st[36]=
{
    {
        NULL_PTR,
        NULL_PTR
,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },

    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Security_key_Encoded_IV_and_key_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Application_Software_ID_Application_Software_ID_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Application_Software_Fingerprint_Application_Software_Fingerprint_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Active_Diagnostic_Session_Active_Session_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Application_Software_Version_LMC_SW_Version_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&System_Supplier_Identifier_Supplier_Identifier_43_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Manufacturing_Date_MM_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Manufacturing_Date_DD_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Manufacturing_Date_YYYY_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Serial_Number_BHSENS_SerialNumber_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Vehicle_Identification_VIN_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Hardware_Number_ECU_Hardware_Number_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&System_Supplier_Hardware_Number_Supplier_Hardware_Number_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&System_Supplier_Hardware_Version_Number_Hardware_Version_Number_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Programming_Date_MM_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Programming_Date_DD_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Programming_Date_YYYY_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Installation_Date_MM_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Installation_Date_DD_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Ecu_Installation_Date_YYYY_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&FL_sensor_ID_FL_sensor_ID_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&FR_sensor_ID_FR_sensor_ID_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&RR_sensor_ID_RR_sensor_ID_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&RL_sensor_ID_RL_sensor_ID_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Wheel_Sensor_Parameter_Legislation_Market_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Wheel_Sensor_Parameter_Pressure_Placard_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Wheel_Sensor_Parameter_Reserved_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&Wheel_Sensor_Parameter_Pressure_Minimum_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_Auto_Learn_WS_parameters_Clear_ZOM_Scaling_Factor_Value_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_Auto_Learn_WS_parameters_Set_Min_ER_RSSI_Level_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_Temperature_Warning_Threshold_Temperature_Threshold_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_ABS_Ticks_ABS_Ticks_Front_Axle_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_ABS_Ticks_ABS_Ticks_Rear_Axle_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_RF_Noise_Level_Threshold_Noise_Level_Offset_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
,
    {

            NULL_PTR,
            NULL_PTR,

	    (void*)&TPMS_RF_Noise_Level_Threshold_Noise_level_threshold_for_RF_interference_WriteFunc,
            NULL_PTR,
            NULL_PTR,

    }
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
const Dcm_DataInfoConfig_tst Dcm_DspDataInfo_st [85]=
{

     {

	        (void*)&Active_Diagnostic_Session_Active_Session_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           4,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Application_Software_Fingerprint_Application_Software_Fingerprint_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           26,

           3,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Application_Software_ID_Application_Software_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           3,

           2,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Application_Software_Version_LMC_SW_Version_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           6,

           5,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B001_BatteryVoltage_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B002_VehicleSpeed_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B003_AmbientTemperature_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B004_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B005_OccurenceDate_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           8,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B006_OccurenceTime_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           8,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B007_TirePressures_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B008_TireTemperatures_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_B009_EcuModesAndStatus_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_F103_VehiclePowerMode_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&DtcEnvData_F104_Mileage_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Hardware_Number_ECU_Hardware_Number_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           11,

           12,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Installation_Date_DD_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           19,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Installation_Date_MM_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           18,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Installation_Date_YYYY_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           20,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Manufacturing_Date_DD_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           8,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Manufacturing_Date_MM_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           7,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Manufacturing_Date_YYYY_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           9,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Programming_Date_DD_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           16,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Programming_Date_MM_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           15,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Programming_Date_YYYY_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           17,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Ecu_Serial_Number_BHSENS_SerialNumber_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           24,

           10,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&FL_sensor_ID_FL_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           21,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&FR_sensor_ID_FR_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           22,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_Last_Received_Pressure_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_P_placard_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_Position_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_Sensor_life_time_counter_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_Temperature_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Last_received_wheel_sensor_Wheel_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&RL_sensor_ID_RL_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           24,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&RR_sensor_ID_RR_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           23,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {
            NULL_PTR,
            NULL_PTR,

            NULL_PTR,

           96,

           1,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&System_Supplier_Hardware_Number_Supplier_Hardware_Number_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           3,

           13,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&System_Supplier_Hardware_Version_Number_Hardware_Version_Number_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           3,

           14,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&System_Supplier_Identifier_Supplier_Identifier_43_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           43,

           6,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_ABS_Ticks_ABS_Ticks_Front_Axle_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           32,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_ABS_Ticks_ABS_Ticks_Rear_Axle_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           33,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Auto_Learn_WS_parameters_Clear_ZOM_Scaling_Factor_Value_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           29,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Auto_Learn_WS_parameters_Set_Min_ER_RSSI_Level_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           30,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_RF_Noise_Level_Threshold_Noise_Level_Offset_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           34,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_RF_Noise_Level_Threshold_Noise_level_threshold_for_RF_interference_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           35,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Rx_Time_Stamp_Noise_RSSI_Level_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Rx_Time_Stamp_RSSI_Level_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           2,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Rx_Time_Stamp_Rx_time_stamp_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Rx_Time_Stamp_Wheel_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&TPMS_Temperature_Warning_Threshold_Temperature_Threshold_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           31,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Vehicle_Identification_VIN_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           17,

           11,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_Sensor_Parameter_Legislation_Market_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           25,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_Sensor_Parameter_Pressure_Minimum_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           28,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_Sensor_Parameter_Pressure_Placard_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           26,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_Sensor_Parameter_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           27,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_Last_Received_Pressure_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_P_placard_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_Position_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_Sensor_life_time_counter_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_Temperature_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_01_Wheel_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_Last_Received_Pressure_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_P_placard_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_Position_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_Sensor_life_time_counter_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_Temperature_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_02_Wheel_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_Last_Received_Pressure_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_P_placard_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_Position_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_Sensor_life_time_counter_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_Temperature_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_03_Wheel_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_Last_Received_Pressure_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_P_placard_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_Position_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_Reserved_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_Sensor_life_time_counter_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_Temperature_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           1,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }

,
     {

	        (void*)&Wheel_sensor_number_04_Wheel_sensor_ID_ReadFunc,
            NULL_PTR,

            NULL_PTR,

           4,

           0,
           DCM_UINT8,
	       USE_DATA_ASYNCH_FNC,

    }
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

static const Dcm_SignalDIDConfig_tst DcmDspDid_B001_SigConf[1]=
{

    {
        0,
        4,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B002_SigConf[1]=
{

    {
        0,
        5,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B003_SigConf[1]=
{

    {
        0,
        6,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B004_SigConf[1]=
{

    {
        0,
        7,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B005_SigConf[1]=
{

    {
        0,
        8,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B006_SigConf[1]=
{

    {
        0,
        9,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B007_SigConf[1]=
{

    {
        0,
        10,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B008_SigConf[1]=
{

    {
        0,
        11,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_B009_SigConf[1]=
{

    {
        0,
        12,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F103_SigConf[1]=
{

    {
        0,
        13,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F104_SigConf[1]=
{

    {
        0,
        14,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F180_SigConf[1]=
{

    {
        0,
        2,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F186_SigConf[1]=
{

    {
        0,
        0,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F184_SigConf[1]=
{

    {
        0,
        1,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F181_SigConf[1]=
{

    {
        0,
        2,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F189_SigConf[1]=
{

    {
        0,
        3,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F191_SigConf[1]=
{

    {
        0,
        15,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F19D_SigConf[3]=
{

    {
        0,
        17,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        16,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        2,
        18,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F18B_SigConf[3]=
{

    {
        0,
        20,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        19,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        2,
        21,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F199_SigConf[3]=
{

    {
        0,
        23,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        22,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        2,
        24,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F18C_SigConf[1]=
{

    {
        0,
        25,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD01_SigConf[1]=
{

    {
        0,
        26,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD02_SigConf[1]=
{

    {
        0,
        27,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FDA5_SigConf[7]=
{

    {
        0,
        34,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        4,
        30,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        5,
        31,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        6,
        28,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        7,
        33,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        8,
        29,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        9,
        32,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD04_SigConf[1]=
{

    {
        0,
        35,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD03_SigConf[1]=
{

    {
        0,
        36,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F192_SigConf[1]=
{

    {
        0,
        38,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F193_SigConf[1]=
{

    {
        0,
        39,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F18A_SigConf[1]=
{

    {
        0,
        40,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD23_SigConf[2]=
{

    {
        0,
        41,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        42,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD15_SigConf[2]=
{

    {
        0,
        43,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        44,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD24_SigConf[2]=
{

    {
        0,
        45,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        46,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD14_SigConf[4]=
{

    {
        0,
        49,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        4,
        50,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        8,
        48,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        10,
        47,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD16_SigConf[1]=
{

    {
        0,
        51,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F190_SigConf[1]=
{

    {
        0,
        52,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FDA1_SigConf[7]=
{

    {
        0,
        63,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        4,
        59,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        5,
        60,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        6,
        57,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        7,
        62,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        8,
        58,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        9,
        61,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FDA2_SigConf[7]=
{

    {
        0,
        70,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        4,
        66,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        5,
        67,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        6,
        64,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        7,
        69,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        8,
        65,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        9,
        68,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FDA3_SigConf[7]=
{

    {
        0,
        77,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        4,
        73,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        5,
        74,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        6,
        71,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        7,
        76,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        8,
        72,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        9,
        75,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FDA4_SigConf[7]=
{

    {
        0,
        84,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        4,
        80,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        5,
        81,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        6,
        78,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        7,
        83,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        8,
        79,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        9,
        82,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_FD0C_SigConf[4]=
{

    {
        0,
        53,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        1,
        55,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        2,
        56,
        NULL_PTR,
        NULL_PTR
    }
,

    {
        3,
        54,
        NULL_PTR,
        NULL_PTR
    }
};

static const Dcm_SignalDIDConfig_tst DcmDspDid_F16A_SigConf[1]=
{

    {
        0,
        37,
        NULL_PTR,
        NULL_PTR
    }
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B001_BatteryVoltage_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_F103_VehiclePowerMode_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B002_VehicleSpeed_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B003_AmbientTemperature_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B004_Reserved_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B005_OccurenceDate_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B006_OccurenceTime_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B007_TirePressures_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B008_TireTemperatures_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_B009_EcuModesAndStatus_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_DtcEnvData_F104_Mileage_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Bootloader_ID_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        &Dcm_Bootloader_ID_UserSpecificCheck,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Active_Diagnostic_Session_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Application_Software_Fingerprint_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0x1EuL,
    0x6uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Application_Software_ID_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Application_Software_Version_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Ecu_Hardware_Number_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Ecu_Installation_Date_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0x4uL,
    0x4uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Ecu_Manufacturing_Date_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Ecu_Programming_Date_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0x1EuL,
    0x6uL,
        &Dcm_Programming_Date_UserSpecificCheck,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Ecu_Serial_Number_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0x1EuL,
    0x6uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_FL_sensor_ID_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_FR_sensor_ID_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Last_received_wheel_sensor_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_RL_sensor_ID_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_RR_sensor_ID_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_System_Supplier_Hardware_Number_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_System_Supplier_Hardware_Version_Number_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_System_Supplier_Identifier_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_TPMS_ABS_Ticks_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0x4uL,
    0x4uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_TPMS_Auto_Learn_WS_parameters_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0x4uL,
    0x4uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_TPMS_RF_Noise_Level_Threshold_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_TPMS_Rx_Time_Stamp_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_TPMS_Temperature_Warning_Threshold_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Vehicle_Identification_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        &Dcm_Vin_UserSpecificCheck,
    0x4uL,
    0x4uL,
        &Dcm_Vin_UserSpecificCheck,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Wheel_sensor_number_01_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Wheel_sensor_number_02_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Wheel_sensor_number_03_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Wheel_sensor_number_04_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
        0x0uL,
        0x0uL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Wheel_Sensor_Parameter_info=
{

    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
    0xffffffffuL,
    0xFFFFFFFFuL,
        NULL_PTR,
};
static const Dcm_ExtendedDIDConfig_tst Did_extendedConfig_Security_key_info=
{
        0x0uL,
        0x0uL,
        NULL_PTR,
    0x4uL,
    0x4uL,
        NULL_PTR,
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

const Dcm_DIDConfig_tst Dcm_DIDConfig []=
{

    {
        0xB001,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        1,
        TRUE,
        FALSE,
        DcmDspDid_B001_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B001_BatteryVoltage_info
    }

,
    {
        0xB002,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        2,
        TRUE,
        FALSE,
        DcmDspDid_B002_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B002_VehicleSpeed_info
    }

,
    {
        0xB003,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        1,
        TRUE,
        FALSE,
        DcmDspDid_B003_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B003_AmbientTemperature_info
    }

,
    {
        0xB004,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        2,
        TRUE,
        FALSE,
        DcmDspDid_B004_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B004_Reserved_info
    }

,
    {
        0xB005,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        8,
        TRUE,
        FALSE,
        DcmDspDid_B005_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B005_OccurenceDate_info
    }

,
    {
        0xB006,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        8,
        TRUE,
        FALSE,
        DcmDspDid_B006_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B006_OccurenceTime_info
    }

,
    {
        0xB007,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_B007_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B007_TirePressures_info
    }

,
    {
        0xB008,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_B008_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B008_TireTemperatures_info
    }

,
    {
        0xB009,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        1,
        TRUE,
        FALSE,
        DcmDspDid_B009_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_B009_EcuModesAndStatus_info
    }

,
    {
        0xF103,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        1,
        TRUE,
        FALSE,
        DcmDspDid_F103_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_F103_VehiclePowerMode_info
    }

,
    {
        0xF104,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_F104_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_DtcEnvData_F104_Mileage_info
    }

,
    {
        0xF16A,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        96,
        TRUE,
        FALSE,
        DcmDspDid_F16A_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Security_key_info
    }

,
    {
        0xF180,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        3,
        TRUE,
        FALSE,
        DcmDspDid_F180_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Bootloader_ID_info
    }

,
    {
        0xF181,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        3,
        TRUE,
        FALSE,
        DcmDspDid_F181_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Application_Software_ID_info
    }

,
    {
        0xF184,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        26,
        TRUE,
        FALSE,
        DcmDspDid_F184_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Application_Software_Fingerprint_info
    }

,
    {
        0xF186,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        1,
        TRUE,
        FALSE,
        DcmDspDid_F186_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Active_Diagnostic_Session_info
    }

,
    {
        0xF189,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        6,
        TRUE,
        FALSE,
        DcmDspDid_F189_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Application_Software_Version_info
    }

,
    {
        0xF18A,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        43,
        TRUE,
        FALSE,
        DcmDspDid_F18A_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_System_Supplier_Identifier_info
    }

,
    {
        0xF18B,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        3,
        4,
        TRUE,
        FALSE,
        DcmDspDid_F18B_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Ecu_Manufacturing_Date_info
    }

,
    {
        0xF18C,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        24,
        TRUE,
        FALSE,
        DcmDspDid_F18C_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Ecu_Serial_Number_info
    }

,
    {
        0xF190,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        17,
        TRUE,
        FALSE,
        DcmDspDid_F190_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Vehicle_Identification_info
    }

,
    {
        0xF191,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        11,
        TRUE,
        FALSE,
        DcmDspDid_F191_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Ecu_Hardware_Number_info
    }

,
    {
        0xF192,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        3,
        TRUE,
        FALSE,
        DcmDspDid_F192_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_System_Supplier_Hardware_Number_info
    }

,
    {
        0xF193,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        3,
        TRUE,
        FALSE,
        DcmDspDid_F193_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_System_Supplier_Hardware_Version_Number_info
    }

,
    {
        0xF199,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        3,
        4,
        TRUE,
        FALSE,
        DcmDspDid_F199_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Ecu_Programming_Date_info
    }

,
    {
        0xF19D,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        3,
        4,
        TRUE,
        FALSE,
        DcmDspDid_F19D_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Ecu_Installation_Date_info
    }

,
    {
        0xFD01,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_FD01_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_FL_sensor_ID_info
    }

,
    {
        0xFD02,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_FD02_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_FR_sensor_ID_info
    }

,
    {
        0xFD03,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_FD03_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_RR_sensor_ID_info
    }

,
    {
        0xFD04,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        4,
        TRUE,
        FALSE,
        DcmDspDid_FD04_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_RL_sensor_ID_info
    }

,
    {
        0xFD0C,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        4,
        4,
        TRUE,
        FALSE,
        DcmDspDid_FD0C_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Wheel_Sensor_Parameter_info
    }

,
    {
        0xFD14,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        4,
        12,
        TRUE,
        FALSE,
        DcmDspDid_FD14_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_TPMS_Rx_Time_Stamp_info
    }

,
    {
        0xFD15,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        2,
        2,
        TRUE,
        FALSE,
        DcmDspDid_FD15_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_TPMS_Auto_Learn_WS_parameters_info
    }

,
    {
        0xFD16,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        1,
        1,
        TRUE,
        FALSE,
        DcmDspDid_FD16_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_TPMS_Temperature_Warning_Threshold_info
    }

,
    {
        0xFD23,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        2,
        2,
        TRUE,
        FALSE,
        DcmDspDid_FD23_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_TPMS_ABS_Ticks_info
    }

,
    {
        0xFD24,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        2,
        2,
        TRUE,
        FALSE,
        DcmDspDid_FD24_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_TPMS_RF_Noise_Level_Threshold_info
    }

,
    {
        0xFDA1,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        7,
        10,
        TRUE,
        FALSE,
        DcmDspDid_FDA1_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Wheel_sensor_number_01_info
    }

,
    {
        0xFDA2,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        7,
        10,
        TRUE,
        FALSE,
        DcmDspDid_FDA2_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Wheel_sensor_number_02_info
    }

,
    {
        0xFDA3,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        7,
        10,
        TRUE,
        FALSE,
        DcmDspDid_FDA3_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Wheel_sensor_number_03_info
    }

,
    {
        0xFDA4,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        7,
        10,
        TRUE,
        FALSE,
        DcmDspDid_FDA4_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Wheel_sensor_number_04_info
    }

,
    {
        0xFDA5,
        USE_DATA_ELEMENT_SPECIFIC_INTERFACES,
        FALSE,
        7,
        10,
        TRUE,
        FALSE,
        DcmDspDid_FDA5_SigConf,
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),
#endif

        NULL_PTR,

        &Did_extendedConfig_Last_received_wheel_sensor_info
    }
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
uint16 Dcm_DIDcalculateTableSize_u16(void)
{
  return ((uint16)(sizeof(Dcm_DIDConfig))/(uint16)(sizeof(Dcm_DIDConfig_tst)));
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
boolean Dcm_ControlDtcSettingModecheck_b(

Dcm_NegativeResponseCodeType * NegRespCode_u8)
{
    Std_ReturnType retVal_u8;
    boolean retVal_b;

    retVal_u8 =DcmAppl_UserDTCSettingEnableModeRuleService();

    if(retVal_u8!=E_OK)
    {
        (void)NegRespCode_u8;
        retVal_b = FALSE;
    }
    else
    {
        (void)NegRespCode_u8;
        retVal_b = TRUE;
    }
    return (retVal_b);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

const Dcm_DspEcuReset_tst Dcm_DspEcuResetType_cast[DCM_CFG_DSP_NUMRESETTYPE] =
{

    {
        0x1,
        DCM_RESET_NO_BOOT

    },

    {
        0x3,
        DCM_RESET_NO_BOOT

    }
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
Std_ReturnType (*Dcm_ComMUserReEnableModeRuleRef) (void) = &DcmAppl_UserCommCtrlReEnableModeRuleService;
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

const Dcm_Dsld_AllChannelsInfoType Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO]=
{
	{
 		ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel
	}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

//
// #define DCM_START_SEC_CONST_UNSPECIFIED
// #include "Dcm_MemMap.h"
// const Dcm_RMBAConfig_tst Dcm_RMBAConfig_cast []=
// {
//     {
// 	
//                 0xA0080000uL,
//
//         0xA00FFFFFuL,
//         0xFFFFFFFFuL,
//         0xffffffffuL,
//         NULL_PTR,
//         0
//     }
// };
// #define DCM_STOP_SEC_CONST_UNSPECIFIED
// #include "Dcm_MemMap.h"
// #define DCM_START_SEC_CODE
// #include "Dcm_MemMap.h"
// uint16 Dcm_RmbacalculateTableSize_u16(void)
// {
//   return ((uint16)(sizeof(Dcm_RMBAConfig_cast))/(uint16)(sizeof(Dcm_RMBAConfig_tst)));
// }
// #define DCM_STOP_SEC_CODE
// #include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
const Dcm_RequestDownloadConfig_tst Dcm_RequestDownloadConfig_cast []=
{
    {
        0xA0080000,
        0xA00FFFFF,
        0xFFFFFFFFuL,
        0
    }
,
    {
        0xA0048000,
        0xA005FFFF,
        0xFFFFFFFFuL,
        0
    }
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
uint16 Dcm_RequestDownloadCalculateTableSize_u16(void)
{
  return ((uint16)(sizeof(Dcm_RequestDownloadConfig_cast))/(uint16)(sizeof(Dcm_RequestDownloadConfig_tst)));
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
