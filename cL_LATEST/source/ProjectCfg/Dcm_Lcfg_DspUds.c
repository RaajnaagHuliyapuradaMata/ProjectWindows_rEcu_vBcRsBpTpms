/******************************************************************************/
/* File   : Dcm_Lcfg_DspUds.c                                                 */
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
#include "Dcm.hpp"
#include "Rte_Dcm.hpp"
#include "DcmDspUds_Uds_Prot.hpp"
#include "rba_BswSrv.hpp"
#include "ComM_Dcm.hpp"
#include "DcmDspUds_Rc_Prot.hpp"
#include "DcmDspUds_Rdtc_Priv.hpp"
#include "DcmDspUds_Er_Prot.hpp"
#include "DcmDspUds_Cdtcs_Prot.hpp"
#include "DcmDspUds_RequestDownload_Prot.hpp"
#include "DcmAppl.hpp"
#include "DcmCore_DslDsd_Prot.hpp"
#include "SwcApplDcm.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SwcServiceDcm_StartRoutineInSignal_Password_StrtIn     0u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Type_CfgSwcServiceDcm_Session CfgSwcServiceDcm_astListSession[DCM_CFG_DSP_NUMSESSIONS] = {
      {50000, 5000000, 0x01, DCM_NO_BOOT}
   ,  {50000, 5000000, 0x02, DCM_NO_BOOT}
   ,  {50000, 5000000, 0x03, DCM_NO_BOOT}
   ,  {50000, 5000000, 0x04, DCM_NO_BOOT}
   ,  {50000, 5000000, 0x60, DCM_SYS_BOOT}
};
const Dcm_Dsp_Security_t Dcm_Dsp_Security[DCM_CFG_DSP_NUMSECURITY] = {
      {50, 5, (void*)&SecaFBL_GetSeed,  (void*)&SecaFBL_CompareKey,  0x1, 16, 16, 5, 0, 0, USE_ASYNCH_FNC, FALSE}
   ,  {50, 5, (void*)&SecaDATA_GetSeed, (void*)&SecaDATA_CompareKey, 0x2, 16, 16, 5, 0, 0, USE_ASYNCH_FNC, FALSE}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
sint16 Dcm_RCSigOutN_as16[1];
uint16 Dcm_RCSigOutN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
sint32 Dcm_RCSigOutN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
sint8 Dcm_RCSigOutN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_RCSigOutN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

typedef enum{
      SwcServiceDcm_EndOfLineTestProcedure_StopRoutineOutSignal_0_StpOut
   ,  SwcServiceDcm_EndOfLineTestProcedure_StartRoutineOutSignal_0_StrtOut
   ,  SwcServiceDcm_EndOfLineTestProcedure_0_ReqRsltOut
   ,  SwcServiceDcm_EndOfLineTestProcedure_1_ReqRsltOut
   ,  SwcServiceDcm_EndOfLineTestProcedure_2_ReqRsltOut
   ,  SwcServiceDcm_EndOfLineTestProcedure_3_ReqRsltOut
   ,  SwcServiceDcm_EndOfLineTestProcedure_4_ReqRsltOut
   ,  DCM_RC_SIGOUTUINT8MAX
}Dcm_DspRoutineSigOutUInt8Idx_ten;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 Dcm_RCSigOut_au8[7];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
uint8 Dcm_RCSigOutN_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
sint16 Dcm_RCSigInN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
sint32 Dcm_RCSigInN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
sint8 Dcm_RCSigInN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_RCSigInN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_RCSigInN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

typedef enum{
      SwcServiceDcm_EndOfLineTestProcedure_StopRoutineInSignal_0_StpIn
   ,  SwcServiceDcm_EndOfLineTestProcedure_StartRoutineInSignal_0_StrtIn
   ,  DCM_RC_SIGINUINT8MAX
}Dcm_DspRoutineSigInUInt8Idx_ten;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 Dcm_RCSigIn_au8[2];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
uint8 Dcm_RCSigInN_au8[10];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
uint32 Dcm_RCGetSigVal_u32(
      uint8  dataSigType_en
   ,  uint16 idxSignalIndex_u16
){
   uint32 dataSigVal_u32;
   if(dataSigType_en == DCM_UINT8){
      dataSigVal_u32 = (uint32)Dcm_RCSigOut_au8[idxSignalIndex_u16];
   }
   else{
      dataSigVal_u32 = 0;
   }
   return (dataSigVal_u32);
}

void Dcm_RCSetSigVal(
      uint8  dataSigType_en
   ,  uint16 idxSignalIndex_u16
   ,  uint32 dataSigVal_u32
){
   if(dataSigType_en == DCM_UINT8){
      Dcm_RCSigIn_au8[idxSignalIndex_u16]=(uint8)dataSigVal_u32;
   }
   else{
      (void)dataSigVal_u32;
      (void)idxSignalIndex_u16;
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static const Type_SwcServiceDcm_stInfoSignalRoutine SwcServiceDcm_RoutineClearMem_StrtInSig[]            = {{0,  80, SwcServiceDcm_StartRoutineInSignal_Password_StrtIn,                   DCM_BIG_ENDIAN, DCM_UINT8_N}};
static const Type_SwcServiceDcm_stInfoSignalRoutine SwcServiceDcm_EndOfLineTestProcedure_StpInSig[]      = {{0,  8,  SwcServiceDcm_EndOfLineTestProcedure_StopRoutineInSignal_0_StpIn,     DCM_OPAQUE,     DCM_UINT8}};
static const Type_SwcServiceDcm_stInfoSignalRoutine SwcServiceDcm_EndOfLineTestProcedure_StrtInSig[]     = {{0,  8,  SwcServiceDcm_EndOfLineTestProcedure_StartRoutineInSignal_0_StrtIn,   DCM_OPAQUE,     DCM_UINT8}};
static const Type_SwcServiceDcm_stInfoSignalRoutine SwcServiceDcm_EndOfLineTestProcedure_StrtOutSig[]    = {{0,  8,  SwcServiceDcm_EndOfLineTestProcedure_StartRoutineOutSignal_0_StrtOut, DCM_OPAQUE,     DCM_UINT8}};
static const Type_SwcServiceDcm_stInfoSignalRoutine SwcServiceDcm_EndOfLineTestProcedure_StopOutSig[]    = {{0,  8,  SwcServiceDcm_EndOfLineTestProcedure_StopRoutineOutSignal_0_StpOut,   DCM_OPAQUE,     DCM_UINT8}};
static const Type_SwcServiceDcm_stInfoSignalRoutine SwcServiceDcm_EndOfLineTestProcedure_ReqRsltOutSig[] = {{0,  8,  SwcServiceDcm_EndOfLineTestProcedure_0_ReqRsltOut,                    DCM_OPAQUE,     DCM_UINT8}
                                                                                                         ,  {8,  8,  SwcServiceDcm_EndOfLineTestProcedure_1_ReqRsltOut,                    DCM_OPAQUE,     DCM_UINT8}
                                                                                                         ,  {16, 8,  SwcServiceDcm_EndOfLineTestProcedure_2_ReqRsltOut,                    DCM_OPAQUE,     DCM_UINT8}
                                                                                                         ,  {24, 8,  SwcServiceDcm_EndOfLineTestProcedure_3_ReqRsltOut,                    DCM_OPAQUE,     DCM_UINT8}
                                                                                                         ,  {32, 8,  SwcServiceDcm_EndOfLineTestProcedure_4_ReqRsltOut,                    DCM_OPAQUE,     DCM_UINT8}};
static const Type_SwcServiceDcm_stInfoRoutine   SwcServiceDcm_RoutineECU_Self_Test      = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, NULL_PTR,                                       NULL_PTR,                                      NULL_PTR, NULL_PTR,                                        NULL_PTR,                                        NULL_PTR,                                           0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const Type_SwcServiceDcm_stInfoRoutine   SwcServiceDcm_RoutineEOL_Test_Procedure = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, SwcServiceDcm_EndOfLineTestProcedure_StrtInSig, SwcServiceDcm_EndOfLineTestProcedure_StpInSig, NULL_PTR, SwcServiceDcm_EndOfLineTestProcedure_StrtOutSig, SwcServiceDcm_EndOfLineTestProcedure_StopOutSig, SwcServiceDcm_EndOfLineTestProcedure_ReqRsltOutSig, 1,  1, 0, 1, 1, 5, 1,  1, 0, 1, 1, 5, 1, 1, 0, 1, 1, 5};
static const Type_SwcServiceDcm_stInfoRoutine   SwcServiceDcm_RoutineClearMem           = {0xFFFFFFFFuL, 0xFFFFFFFFuL, NULL_PTR, SwcServiceDcm_RoutineClearMem_StrtInSig,        NULL_PTR,                                      NULL_PTR, NULL_PTR,                                        NULL_PTR,                                        NULL_PTR,                                           10, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
static Std_ReturnType SwcServiceDcm_RoutineECU_Self_Test_Func(uint8 dataSubFunc_u8){
   Std_ReturnType dataRetVal_u8 = E_NOT_OK;
   switch(dataSubFunc_u8){
      case 1u: dataRetVal_u8       = DcmDsp_StartSelfTest_Callback(         Dcm_RCOpStatus_u8, &(Dcm_RCNegResCode_u8)); break;
      case 3u: dataRetVal_u8       = DcmDsp_RequestResultSelfTest_Callback( Dcm_RCOpStatus_u8, &(Dcm_RCNegResCode_u8)); break;
      default: Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;                                                     break;
   }
   return dataRetVal_u8;
}

static Std_ReturnType SwcServiceDcm_RoutineEOL_Test_Procedure_Func(uint8 dataSubFunc_u8){
   Std_ReturnType dataRetVal_u8;
   dataRetVal_u8 = E_NOT_OK;
   switch(dataSubFunc_u8){
      case 1u: dataRetVal_u8       = DcmDsp_StartVehicleEolTestProcedure_Callback(
                                          Dcm_RCSigIn_au8[SwcServiceDcm_EndOfLineTestProcedure_StartRoutineInSignal_0_StrtIn]
                                       ,  Dcm_RCOpStatus_u8
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_StartRoutineOutSignal_0_StrtOut])
                                       ,  &(Dcm_RCNegResCode_u8)
                                     );
                                     break;
      case 2u: dataRetVal_u8       = DcmDsp_StopVehicleEolTestProcedure_Callback(
                                          Dcm_RCSigIn_au8[SwcServiceDcm_EndOfLineTestProcedure_StopRoutineInSignal_0_StpIn]
                                       ,  Dcm_RCOpStatus_u8
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_StopRoutineOutSignal_0_StpOut])
                                       ,  &(Dcm_RCNegResCode_u8)
                                     );
                                     break;
      case 3u: dataRetVal_u8       = DcmDsp_RequestResultVehicleEolTestProcedure_Callback(
                                          Dcm_RCOpStatus_u8
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_0_ReqRsltOut])
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_1_ReqRsltOut])
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_2_ReqRsltOut])
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_3_ReqRsltOut])
                                       ,  &(Dcm_RCSigOut_au8[SwcServiceDcm_EndOfLineTestProcedure_4_ReqRsltOut])
                                       ,  &(Dcm_RCNegResCode_u8)
                                     );
                                     break;
      default: Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED; break;
   }
   return dataRetVal_u8;
}

static Std_ReturnType SwcServiceDcm_RoutineClearMem_Func(uint8 dataSubFunc_u8){
   Std_ReturnType dataRetVal_u8;
   dataRetVal_u8 = E_NOT_OK;
   switch(dataSubFunc_u8){
      case 1u: dataRetVal_u8 = DcmDsp_StartResetEepromCallback(
               &Dcm_RCSigInN_au8[SwcServiceDcm_StartRoutineInSignal_Password_StrtIn]
            ,  Dcm_RCOpStatus_u8
            ,  &(Dcm_RCNegResCode_u8)
         );
         break;
      default: Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED; break;
   }
   return (dataRetVal_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Type_SwcServiceDcm_Routine SwcServiceDcm_castListRoutine[DCM_CFG_RC_NUMRIDS] = {
      {0x1248, TRUE, FALSE, &SwcServiceDcm_RoutineClearMem,           &SwcServiceDcm_RoutineClearMem_Func,           TRUE, FALSE, FALSE, FALSE, FALSE}
   ,  {0xf200, TRUE, FALSE, &SwcServiceDcm_RoutineECU_Self_Test,      &SwcServiceDcm_RoutineECU_Self_Test_Func,      TRUE, FALSE, FALSE, TRUE,  TRUE}
   ,  {0xfdc2, TRUE, FALSE, &SwcServiceDcm_RoutineEOL_Test_Procedure, &SwcServiceDcm_RoutineEOL_Test_Procedure_Func, TRUE, TRUE,  TRUE,  TRUE,  TRUE}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_DspRoutineStatusType_ten Dcm_RoutineStatus_aen[DCM_CFG_RC_NUMRIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Type_CfgSwcServiceDcm_stInfoDidWrite CfgSwcServiceDcm_castListInfoDidWrite[36] = {
      {NULL_PTR, NULL_PTR, NULL_PTR,                                                                   NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_SecurityKeyEncodedIV,                    NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_SwApplId,                                NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_SwApplFingerprint,                       NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_SessionDiagnosticActive,                 NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_SwApplVersion_cL,                        NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_IdSupplierSys,                           NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuManufacturing_MM,                 NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuManufacturing_DD,                 NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuManufacturing_YYYY,               NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_NumEcuSerial_Supplier1,                  NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_NumIdVehicle,                            NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_NumEcuHw,                                NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_NumHw_Supplier1,                         NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_NumHwVersionSys_Supplier1,               NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuProgramming_MM,                   NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuProgramming_DD,                   NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuProgramming_YYYY,                 NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuInstallation_MM,                  NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuInstallation_DD,                  NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_DateEcuInstallation_YYYY,                NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_IdSensor_FL,                             NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_IdSensor_FR,                             NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_IdSensor_RR,                             NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_IdSensor_RL,                             NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_ParamSensorWheelLegislation,             NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_ParamSensorWheelPressurePlacard,         NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_ParamSensorWheelReserved,                NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_ParamSensorWheelPressureMin,             NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_ParamSensorWheelAutolearnClearScaleZom,  NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_ParamSensorWheelAutolearnErRssiLvl_Min,  NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_WarningTemperature_Threshold,            NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_TicksAbsAxle_Front,                      NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_TicksAbsAxle_Rear,                       NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_LvlNoiseRfOffset_Threshold,              NULL_PTR, NULL_PTR}
   ,  {NULL_PTR, NULL_PTR, (void*)&SwcApplDcm_FuncDidWrite_LvlNoiseRfOffset_ThresholdInterference,  NULL_PTR, NULL_PTR}
};

const Dcm_DataInfoConfig_tst Dcm_DspDataInfo_st [85] = {
      {(void*)&SwcApplDcm_FuncDidRead_SessionDiagnosticActive,                NULL_PTR, NULL_PTR, 1,  4,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_SwApplFingerprint,                      NULL_PTR, NULL_PTR, 26, 3,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_SwApplId,                               NULL_PTR, NULL_PTR, 3,  2,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_SwApplVersion_cL,                       NULL_PTR, NULL_PTR, 6,  5,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B001_VoltageBattery,         NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B002_SpeedVehicle,           NULL_PTR, NULL_PTR, 2,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B003_TemperatureAmbient,     NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B004_Reserved,               NULL_PTR, NULL_PTR, 2,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B006_OccurenceDate,          NULL_PTR, NULL_PTR, 8,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B006_OccurenceTime,          NULL_PTR, NULL_PTR, 8,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B007_TirePressures,          NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B008_TireTemperatures,       NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_B009_ModesAndStatusEcu,      NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_F103_ModePowerVehicle,       NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DataDtcEnv_F104_Mileage,                NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumEcuHw,                               NULL_PTR, NULL_PTR, 11, 12, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuInstallation_DD,                 NULL_PTR, NULL_PTR, 1,  19, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuInstallation_MM,                 NULL_PTR, NULL_PTR, 1,  18, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuInstallation_YYYY,               NULL_PTR, NULL_PTR, 2,  20, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuManufacturing_DD,                NULL_PTR, NULL_PTR, 1,  8,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuManufacturing_MM,                NULL_PTR, NULL_PTR, 1,  7,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuManufacturing_YYYY,              NULL_PTR, NULL_PTR, 2,  9,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuProgramming_DD,                  NULL_PTR, NULL_PTR, 1,  16, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuProgramming_MM,                  NULL_PTR, NULL_PTR, 1,  15, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_DateEcuProgramming_YYYY,                NULL_PTR, NULL_PTR, 2,  17, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumEcuSerial_Supplier1,                 NULL_PTR, NULL_PTR, 24, 10, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_IdSensor_FL,                            NULL_PTR, NULL_PTR, 4,  21, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_IdSensor_FR,                            NULL_PTR, NULL_PTR, 4,  22, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ReceivedLastPressure,                   NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_PressurePlacard,                        NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ReceivedLastPosition,                   NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ReceivedLastReserved,                   NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ReceivedLastCounterLifeTime,            NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ReceivedLastTemperature,                NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ReceivedLastIdSensor,                   NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_IdSensor_RL,                            NULL_PTR, NULL_PTR, 4,  24, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_IdSensor_RR,                            NULL_PTR, NULL_PTR, 4,  23, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {NULL_PTR,                                                              NULL_PTR, NULL_PTR, 96, 1,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumHw_Supplier1,                        NULL_PTR, NULL_PTR, 3,  13, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumHwVersionSys_Supplier1,              NULL_PTR, NULL_PTR, 3,  14, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_IdSupplierSys,                          NULL_PTR, NULL_PTR, 43, 6,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_TicksAbsAxle_Front,                     NULL_PTR, NULL_PTR, 1,  32, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_TicksAbsAxle_Rear,                      NULL_PTR, NULL_PTR, 1,  33, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ParamSensorWheelAutolearnClearScaleZom, NULL_PTR, NULL_PTR, 1,  29, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ParamSensorWheelAutolearnErRssiLvl_Min, NULL_PTR, NULL_PTR, 1,  30, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_LvlNoiseRfOffset_Threshold,             NULL_PTR, NULL_PTR, 1,  34, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_LvlNoiseRfOffset_ThresholdInterference, NULL_PTR, NULL_PTR, 1,  35, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_TimeStampRxRssiLvlNoise,                NULL_PTR, NULL_PTR, 2,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_TimeStampRxRssiLvl,                     NULL_PTR, NULL_PTR, 2,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_TimeStampRx,                            NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_TimeStampRxIdWheel,                     NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_WarningTemperature_Threshold,           NULL_PTR, NULL_PTR, 1,  31, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumIdVehicle,                           NULL_PTR, NULL_PTR, 17, 11, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ParamSensorWheelLegislation,            NULL_PTR, NULL_PTR, 1,  25, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ParamSensorWheelPressureMin,            NULL_PTR, NULL_PTR, 1,  28, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ParamSensorWheelPressurePlacard,        NULL_PTR, NULL_PTR, 1,  26, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_ParamSensorWheelReserved,               NULL_PTR, NULL_PTR, 1,  27, DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_Pressure_ReceivedLast,       NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_PressurePlacard,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_Position,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_Reserved,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_CounterLifeTime,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_Temperature,                 NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor1_IdSensor,                    NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_Pressure_ReceivedLast,       NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_PressurePlacard,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_Position,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_Reserved,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_CounterLifeTime,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_Temperature,                 NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor2_IdSensor,                    NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_Pressure_ReceivedLast,       NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_PressurePlacard,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_Position,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_Reserved,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_CounterLifeTime,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_Temperature,                 NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor3_IdSensor,                    NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_Pressure_ReceivedLast,       NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_PressurePlacard,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_Position,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_Reserved,                    NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_CounterLifeTime,             NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_Temperature,                 NULL_PTR, NULL_PTR, 1,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
   ,  {(void*)&SwcApplDcm_FuncDidRead_NumSensor4_IdSensor,                    NULL_PTR, NULL_PTR, 4,  0,  DCM_UINT8, USE_DATA_ASYNCH_FNC}
};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B001[1] = {{0,  4,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B002[1] = {{0,  5,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B003[1] = {{0,  6,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B004[1] = {{0,  7,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B005[1] = {{0,  8,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B006[1] = {{0,  9,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B007[1] = {{0,  10, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B008[1] = {{0,  11, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_B009[1] = {{0,  12, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F103[1] = {{0,  13, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F104[1] = {{0,  14, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F16A[1] = {{0,  37, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F180[1] = {{0,  2,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F181[1] = {{0,  2,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F184[1] = {{0,  1,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F186[1] = {{0,  0,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F189[1] = {{0,  3,  NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F18A[1] = {{0,  40, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F18B[3] = {{0,  20, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  19, NULL_PTR, NULL_PTR}
                                                                                    ,  {2,  21, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F18C[1] = {{0,  25, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F190[1] = {{0,  52, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F191[1] = {{0,  15, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F192[1] = {{0,  38, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F193[1] = {{0,  39, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F199[3] = {{0,  23, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  22, NULL_PTR, NULL_PTR}
                                                                                    ,  {2,  24, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_F19D[3] = {{0,  17, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  16, NULL_PTR, NULL_PTR}
                                                                                    ,  {2,  18, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD01[1] = {{0,  26, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD02[1] = {{0,  27, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD03[1] = {{0,  36, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD04[1] = {{0,  35, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD0C[4] = {{0,  53, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  55, NULL_PTR, NULL_PTR}
                                                                                    ,  {2,  56, NULL_PTR, NULL_PTR}
                                                                                    ,  {3,  54, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD14[4] = {{0,  49, NULL_PTR, NULL_PTR}
                                                                                    ,  {4,  50, NULL_PTR, NULL_PTR}
                                                                                    ,  {8,  48, NULL_PTR, NULL_PTR}
                                                                                    ,  {10, 47, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD15[2] = {{0,  43, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  44, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD16[1] = {{0,  51, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD23[2] = {{0,  41, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  42, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FD24[2] = {{0,  45, NULL_PTR, NULL_PTR}
                                                                                    ,  {1,  46, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FDA1[7] = {{0,  63, NULL_PTR, NULL_PTR}
                                                                                    ,  {4,  59, NULL_PTR, NULL_PTR}
                                                                                    ,  {5,  60, NULL_PTR, NULL_PTR}
                                                                                    ,  {6,  57, NULL_PTR, NULL_PTR}
                                                                                    ,  {7,  62, NULL_PTR, NULL_PTR}
                                                                                    ,  {8,  58, NULL_PTR, NULL_PTR}
                                                                                    ,  {9,  61, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FDA2[7] = {{0,  70, NULL_PTR, NULL_PTR}
                                                                                    ,  {4,  66, NULL_PTR, NULL_PTR}
                                                                                    ,  {5,  67, NULL_PTR, NULL_PTR}
                                                                                    ,  {6,  64, NULL_PTR, NULL_PTR}
                                                                                    ,  {7,  69, NULL_PTR, NULL_PTR}
                                                                                    ,  {8,  65, NULL_PTR, NULL_PTR}
                                                                                    ,  {9,  68, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FDA3[7] = {{0,  77, NULL_PTR, NULL_PTR}
                                                                                    ,  {4,  73, NULL_PTR, NULL_PTR}
                                                                                    ,  {5,  74, NULL_PTR, NULL_PTR}
                                                                                    ,  {6,  71, NULL_PTR, NULL_PTR}
                                                                                    ,  {7,  76, NULL_PTR, NULL_PTR}
                                                                                    ,  {8,  72, NULL_PTR, NULL_PTR}
                                                                                    ,  {9,  75, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FDA4[7] = {{0,  84, NULL_PTR, NULL_PTR}
                                                                                    ,  {4,  80, NULL_PTR, NULL_PTR}
                                                                                    ,  {5,  81, NULL_PTR, NULL_PTR}
                                                                                    ,  {6,  78, NULL_PTR, NULL_PTR}
                                                                                    ,  {7,  83, NULL_PTR, NULL_PTR}
                                                                                    ,  {8,  79, NULL_PTR, NULL_PTR}
                                                                                    ,  {9,  82, NULL_PTR, NULL_PTR}};
static const Type_CfgSwcServiceDcm_stSignalDid CfgSwcServiceDcm_stSignalDid_FDA5[7] = {{0,  34, NULL_PTR, NULL_PTR}
                                                                                    ,  {4,  30, NULL_PTR, NULL_PTR}
                                                                                    ,  {5,  31, NULL_PTR, NULL_PTR}
                                                                                    ,  {6,  28, NULL_PTR, NULL_PTR}
                                                                                    ,  {7,  33, NULL_PTR, NULL_PTR}
                                                                                    ,  {8,  29, NULL_PTR, NULL_PTR}
                                                                                    ,  {9,  32, NULL_PTR, NULL_PTR}};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B001_BatteryVoltage_info          = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_F103_VehiclePowerMode_info        = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B002_VehicleSpeed_info            = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B003_AmbientTemperature_info      = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B004_Reserved_info                = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B005_OccurenceDate_info           = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B006_OccurenceTime_info           = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B007_TirePressures_info           = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B008_TireTemperatures_info        = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_B009_EcuModesAndStatus_info       = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedDtcEnvData_F104_Mileage_info                 = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedBootloader_ID_info                           = {0xffffffffuL, 0xFFFFFFFFuL, &Dcm_Bootloader_ID_UserSpecificCheck,0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedActive_Diagnostic_Session_info               = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedApplication_Software_Fingerprint_info        = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x1EuL,       0x6uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedApplication_Software_ID_info                 = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedApplication_Software_Version_info            = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedEcu_Hardware_Number_info                     = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedEcu_Installation_Date_info                   = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x4uL,        0x4uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedEcu_Manufacturing_Date_info                  = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedEcu_Programming_Date_info                    = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x1EuL,       0x6uL,        &Dcm_Programming_Date_UserSpecificCheck};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedEcu_Serial_Number_info                       = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x1EuL,       0x6uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedFL_sensor_ID_info                            = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedFR_sensor_ID_info                            = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedLast_received_wheel_sensor_info              = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedRL_sensor_ID_info                            = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedRR_sensor_ID_info                            = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedSystem_Supplier_Hardware_Number_info         = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedSystem_Supplier_Hardware_Version_Number_info = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedSystem_Supplier_Identifier_info              = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedTPMS_ABS_Ticks_info                          = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x4uL,        0x4uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedTPMS_Auto_Learn_WS_parameters_info           = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x4uL,        0x4uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedTPMS_RF_Noise_Level_Threshold_info           = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedTPMS_Rx_Time_Stamp_info                      = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedTPMS_Temperature_Warning_Threshold_info      = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedVehicle_Identification_info                  = {0xffffffffuL, 0xFFFFFFFFuL, &Dcm_Vin_UserSpecificCheck,          0x4uL,        0x4uL,        &Dcm_Vin_UserSpecificCheck};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_01_info                  = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_02_info                  = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_03_info                  = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_04_info                  = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0x0uL,        0x0uL,        NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedWheel_Sensor_Parameter_info                  = {0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR,                            0xffffffffuL, 0xFFFFFFFFuL, NULL_PTR};
static const Type_CfgSwcServiceDcm_stDidExtended CfgSwcServiceDcm_stDidExtendedSecurity_key_info                            = {0x0uL,        0x0uL,        NULL_PTR,                            0x4uL,        0x4uL,        NULL_PTR};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Type_CfgSwcServiceDcm_stDid CfgSwcServiceDcm_astListDid[] = {
      {0xB001, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 1,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B001, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B001_BatteryVoltage_info}
   ,  {0xB002, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 2,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B002, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B002_VehicleSpeed_info}
   ,  {0xB003, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 1,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B003, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B003_AmbientTemperature_info}
   ,  {0xB004, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 2,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B004, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B004_Reserved_info}
   ,  {0xB005, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 8,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B005, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B005_OccurenceDate_info}
   ,  {0xB006, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 8,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B006, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B006_OccurenceTime_info}
   ,  {0xB007, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B007, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B007_TirePressures_info}
   ,  {0xB008, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B008, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B008_TireTemperatures_info}
   ,  {0xB009, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 1,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_B009, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_B009_EcuModesAndStatus_info}
   ,  {0xF103, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 1,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F103, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_F103_VehiclePowerMode_info}
   ,  {0xF104, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F104, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedDtcEnvData_F104_Mileage_info}
   ,  {0xF16A, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 96, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F16A, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedSecurity_key_info}
   ,  {0xF180, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 3,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F180, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedBootloader_ID_info}
   ,  {0xF181, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 3,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F181, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedApplication_Software_ID_info}
   ,  {0xF184, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 26, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F184, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedApplication_Software_Fingerprint_info}
   ,  {0xF186, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 1,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F186, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedActive_Diagnostic_Session_info}
   ,  {0xF189, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 6,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F189, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedApplication_Software_Version_info}
   ,  {0xF18A, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 43, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F18A, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedSystem_Supplier_Identifier_info}
   ,  {0xF18B, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 3, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F18B, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedEcu_Manufacturing_Date_info}
   ,  {0xF18C, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 24, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F18C, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedEcu_Serial_Number_info}
   ,  {0xF190, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 17, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F190, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedVehicle_Identification_info}
   ,  {0xF191, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 11, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F191, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedEcu_Hardware_Number_info}
   ,  {0xF192, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 3,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F192, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedSystem_Supplier_Hardware_Number_info}
   ,  {0xF193, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 3,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F193, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedSystem_Supplier_Hardware_Version_Number_info}
   ,  {0xF199, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 3, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F199, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedEcu_Programming_Date_info}
   ,  {0xF19D, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 3, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_F19D, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedEcu_Installation_Date_info}
   ,  {0xFD01, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD01, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedFL_sensor_ID_info}
   ,  {0xFD02, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD02, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedFR_sensor_ID_info}
   ,  {0xFD03, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD03, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedRR_sensor_ID_info}
   ,  {0xFD04, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD04, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedRL_sensor_ID_info}
   ,  {0xFD0C, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 4, 4,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD0C, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedWheel_Sensor_Parameter_info}
   ,  {0xFD14, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 4, 12, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD14, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedTPMS_Rx_Time_Stamp_info}
   ,  {0xFD15, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 2, 2,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD15, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedTPMS_Auto_Learn_WS_parameters_info}
   ,  {0xFD16, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 1, 1,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD16, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedTPMS_Temperature_Warning_Threshold_info}
   ,  {0xFD23, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 2, 2,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD23, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedTPMS_ABS_Ticks_info}
   ,  {0xFD24, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 2, 2,  TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FD24, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedTPMS_RF_Noise_Level_Threshold_info}
   ,  {0xFDA1, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 7, 10, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FDA1, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_01_info}
   ,  {0xFDA2, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 7, 10, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FDA2, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_02_info}
   ,  {0xFDA3, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 7, 10, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FDA3, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_03_info}
   ,  {0xFDA4, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 7, 10, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FDA4, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedWheel_sensor_number_04_info}
   ,  {0xFDA5, USE_DATA_ELEMENT_SPECIFIC_INTERFACES, FALSE, 7, 10, TRUE, FALSE, CfgSwcServiceDcm_stSignalDid_FDA5, NULL_PTR, &CfgSwcServiceDcm_stDidExtendedLast_received_wheel_sensor_info}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_DIDcalculateTableSize_u16(void){
  return ((uint16)(sizeof(CfgSwcServiceDcm_astListDid))/(uint16)(sizeof(Type_CfgSwcServiceDcm_stDid)));
}

boolean Dcm_ControlDtcSettingModecheck_b(
Dcm_NegativeResponseCodeType * NegRespCode_u8){
   boolean retVal_b;
   if(E_OK!=DcmAppl_UserDTCSettingEnableModeRuleService()){
      (void)NegRespCode_u8;
      retVal_b = FALSE;
   }
   else{
      (void)NegRespCode_u8;
      retVal_b = TRUE;
   }
   return (retVal_b);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Dcm_DspEcuReset_tst Dcm_DspEcuResetType_cast[DCM_CFG_DSP_NUMRESETTYPE] = {
      {0x1, DCM_RESET_NO_BOOT}
   ,  {0x3, DCM_RESET_NO_BOOT}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType (*Dcm_ComMUserReEnableModeRuleRef) (void) = &DcmAppl_UserCommCtrlReEnableModeRuleService;
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Dcm_Dsld_AllChannelsInfoType Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO] = {{ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel}};
const Dcm_RequestDownloadConfig_tst Dcm_RequestDownloadConfig_cast [] = {
      {0xA0080000, 0xA00FFFFF, 0xFFFFFFFFuL, 0}
   ,  {0xA0048000, 0xA005FFFF, 0xFFFFFFFFuL, 0}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
uint16 Dcm_RequestDownloadCalculateTableSize_u16(void){return((uint16)(sizeof(Dcm_RequestDownloadConfig_cast))/(uint16)(sizeof(Dcm_RequestDownloadConfig_tst)));}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

