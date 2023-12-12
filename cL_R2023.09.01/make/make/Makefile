MAKE_MODE=DOS

# ************************************************************************
# paths and source folders
# ************************************************************************
DIR_SOURCE     = ../source
DIR_OUTPUT_OBJ = output/objects
DIR_OUTPUT_LST = output/list

Include_common           = $(DIR_SOURCE)/common
Source_ProjectCompiler   = $(DIR_SOURCE)/ProjectCompiler
Source_ProjectCfg        = $(DIR_SOURCE)/ProjectCfg

SRC_INT_CANIF           = $(DIR_SOURCE)/wrappers/EcuabCanIf/Integration
SRC_INT_CANTP           = $(DIR_SOURCE)/wrappers/SwcServiceCanTp/Integration
SRC_INT_COM             = $(DIR_SOURCE)/wrappers/SwcServiceCom/Integration
SRC_INT_COMM            = $(DIR_SOURCE)/wrappers/SwcServiceComM/Integration
SRC_INT_DCM             = $(DIR_SOURCE)/wrappers/SwcServiceDcm/Integration
SRC_INT_DEM             = $(DIR_SOURCE)/wrappers/SwcServiceDem/Integration
SRC_INT_DET             = $(DIR_SOURCE)/SwcServiceDet/Integration
SRC_INT_FIM             = $(DIR_SOURCE)/SwcServiceFiM/Integration
SRC_INT_PDUR            = $(DIR_SOURCE)/wrappers/SwcServicePduR/Integration
SRC_INT_ECUM            = $(DIR_SOURCE)/wrappers/SwcServiceEcuM/Integration

Include_wrappers_EcuabCanIf         = $(DIR_SOURCE)/wrappers/EcuabCanIf/api
Include_wrappers_SwcServiceCom      = $(DIR_SOURCE)/wrappers/SwcServiceCom/api
Include_wrappers_SwcServiceComM     = $(DIR_SOURCE)/wrappers/SwcServiceComM/api
Include_wrappers_SwcServicePduR     = $(DIR_SOURCE)/wrappers/SwcServicePduR/api
Include_wrappers_api_Bfx            = $(DIR_SOURCE)/wrappers/Bfx/api      
Include_wrappers_api_rba_BswSrv     = $(DIR_SOURCE)/wrappers/rba_BswSrv/api
Include_wrappers_api_LibAutosarDiag = $(DIR_SOURCE)/wrappers/LibAutosarDiag/api
Include_SwcApplTpms_Intface         = $(DIR_SOURCE)/SwcApplTpms/Intface
Include_SwcServiceDet               = $(DIR_SOURCE)/SwcServiceDet/api
Include_SwcServiceFiM               = $(DIR_SOURCE)/SwcServiceFiM/api

Source_wrappers                            = $(DIR_SOURCE)/wrappers
Source_wrappers_EcuabCanIf                 = $(DIR_SOURCE)/wrappers/EcuabCanIf
Source_wrappers_SwcServiceCanSM            = $(DIR_SOURCE)/wrappers/SwcServiceCanSM
Source_wrappers_SwcServiceCanTp            = $(DIR_SOURCE)/wrappers/SwcServiceCanTp
Source_wrappers_SwcServiceCanTp_PreCompile = $(DIR_SOURCE)/wrappers/SwcServiceCanTp_PreCompile
Source_wrappers_SwcServiceCom              = $(DIR_SOURCE)/wrappers/SwcServiceCom
Source_wrappers_SwcServiceComM             = $(DIR_SOURCE)/wrappers/SwcServiceComM
Source_wrappers_SwcServiceDcm              = $(DIR_SOURCE)/wrappers/SwcServiceDcm
Source_wrappers_SwcServiceComStack         = $(DIR_SOURCE)/wrappers/SwcServiceComStack
Source_wrappers_SwcServicePduR             = $(DIR_SOURCE)/wrappers/SwcServicePduR
Source_wrappers_SwcServiceEcuM             = $(DIR_SOURCE)/wrappers/SwcServiceEcuM
Source_wrappers_Bfx                        = $(DIR_SOURCE)/wrappers/Bfx
Source_wrappers_SwcServiceDem              = $(DIR_SOURCE)/wrappers/SwcServiceDem
Source_wrappers_Crc                        = $(DIR_SOURCE)/wrappers/Crc
Source_wrappers_LibAutosarDiag             = $(DIR_SOURCE)/wrappers/LibAutosarDiag
Source_wrappers_CANMANAGER                 = $(DIR_SOURCE)/wrappers/CAN_MANAGER
Source_wrappers_NVMMANAGER                 = $(DIR_SOURCE)/wrappers/NVM_MANAGER
Source_wrappers_DEMMANAGER                 = $(DIR_SOURCE)/wrappers/DEM_MANAGER
Source_wrappers_RDCMANAGER                 = $(DIR_SOURCE)/wrappers/RDC_MANAGER
Source_wrappers_ENVMANAGER                 = $(DIR_SOURCE)/wrappers/ENV_MANAGER
Source_wrappers_SYSMANAGER                 = $(DIR_SOURCE)/wrappers/SYS_MANAGER
Source_wrappers_McalAta                    = $(DIR_SOURCE)/wrappers/McalAta
Source_wrappers_OS                         = $(DIR_SOURCE)/wrappers/OS
Source_wrappers_FBL_APPL                   = $(DIR_SOURCE)/wrappers/FBL_APPL
Source_wrappers_VStdLib                    = $(DIR_SOURCE)/wrappers/VStdLib
Source_wrappers_rba_BswSrv                 = $(DIR_SOURCE)/wrappers/rba_BswSrv
Source_SwcApplTpms                         = $(DIR_SOURCE)/SwcApplTpms
Source_SwcApplEcuM                         = $(DIR_SOURCE)/SwcApplEcuM
Source_SwcServiceDet                       = $(DIR_SOURCE)/SwcServiceDet
Source_SwcServiceEcuM                      = $(DIR_SOURCE)/SwcServiceEcuM
Source_SwcServiceFiM                       = $(DIR_SOURCE)/SwcServiceFiM
Source_SwcServiceNvM                       = $(DIR_SOURCE)/SwcServiceNvM
Source_SwcServiceOs                        = $(DIR_SOURCE)/SwcServiceOs
Source_SwcServiceSchM                      = $(DIR_SOURCE)/SwcServiceSchM
Source_SwcServiceStartUp                   = $(DIR_SOURCE)/SwcServiceStartUp
Source_EcuabFee                            = $(DIR_SOURCE)/EcuabFee
Source_EcuabMemIf                          = $(DIR_SOURCE)/EcuabMemIf
Source_McalAdc                             = $(DIR_SOURCE)/McalAdc
Source_McalCan                             = $(DIR_SOURCE)/McalCan
Source_McalDio                             = $(DIR_SOURCE)/McalDio
Source_McalFls                             = $(DIR_SOURCE)/McalFls
Source_McalGpt                             = $(DIR_SOURCE)/McalGpt
Source_McalLin                             = $(DIR_SOURCE)/McalLin
Source_McalMcu                             = $(DIR_SOURCE)/McalMcu
Source_McalWdg                             = $(DIR_SOURCE)/McalWdg

OBJLIST=obj_list.txt
EXT=abs
OUTFILE=$(TARGET)

# ******************************************************************************
# Library files for RIVIAN
# ******************************************************************************
LIB_OS   = "$(Source_wrappers_OS)/RTAOS.a"

# ******************************************************************************
# COMPILER PATH
# ******************************************************************************
COMPILER_INSTALL_DIR = c:\ghs\comp_201517

# ******************************************************************************
# COMPILER SPECIFIC DEFINES
# ******************************************************************************
CC="$(COMPILER_INSTALL_DIR)\ccv850.exe"
AS="$(COMPILER_INSTALL_DIR)\ccv850.exe"
LD="$(COMPILER_INSTALL_DIR)\ccv850.exe"
 
DEFINES = $(patsubst %,-D%,$(PRJ_DEFINES))

# ******************************************************************************
# compiler specific includes
# ******************************************************************************
CINCLUDE = $(patsubst %,-I%,$(INC))

# ******************************************************************************
# COMPILER OPTIONS 
# ******************************************************************************
COMMONFLAGS  = -cpu=rh850 -fhard -ignore_callt_state_in_interrupts -large_sda -misalign_pack -nofarcalls -nofloatio -no_callt -Ogeneral \
               -Onounroll -prepare_dispose -registermode=32 -reserve_r2 -sda=0 -shorten_loads -Wshadow --brief_diagnostics --no_commons \
               --no_wrap_diagnostics --prototype_errors --short_enum -list -G -dual_debug -dwarf -X5523 \
               -lnk=-no_xda_modifications \
               -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT \
               -D IBTCM_SW_ANPASSUNGEN \
               -D BUILD_LORDSTOWN

# ******************************************************************************
# Compile *.c files to *.lst and *.obj and link everything to .elf file
# ******************************************************************************
CFLAGS  = $(COMMONFLAGS) -c -inline_prologue $(DEFINES) $(CINCLUDE) -object_dir=$(DIR_OUTPUT_OBJ) -list_dir=$(DIR_OUTPUT_LST)
ASFLAGS = $(COMMONFLAGS) -c -passsource -preprocess_assembly_files $(DEFINES) $(CINCLUDE) -object_dir=$(DIR_OUTPUT_OBJ) -list_dir=$(DIR_OUTPUT_LST)
LDFLAGS = $(COMMONFLAGS) $(LIB_OS) -map="$(TARGET).map" $(LDSCRIPT) -o "$(TARGET).elf"

# ****************************************************************************** 
# Tools (create a .s3 from .elf)
# ******************************************************************************
ADD_TOOLS  = "$(COMPILER_INSTALL_DIR)\gsrec" $(TARGET).elf -o $(TARGET).s3
DEL_TOOL := del /F /Q

# ******************************************************************************
# linker script
# ******************************************************************************
LDSCRIPT = ./LinkerFile.ld

# ******************************************************************************
# Object files
# ******************************************************************************
OBJS := $(addprefix $(DIR_OUTPUT_OBJ)/,\
adc.o\
aes.o\
applvect.o\
ata_dev_5785.o\
ata_Rec.o\
Bfx_Bit.o\
Bfx_GetVersionInfo.o\
Bfx_TstParityEven_u16_u8.o\
Bfx_TstParityEven_u32_u8.o\
Bfx_TstParityEven_u64_u8.o\
Bfx_TstParityEven_u8_u8.o\
Break.o\
BrsStartup_c0.o\
bswm.o\
busmsg.o\
calibr.o\
can.o\
can_table.o\
CanIf_Baudrate.o\
CanIf_Controller.o\
CanIf_ControllerModeIndication_Integration.o\
CanIf_GetTxConfirmationState.o\
CanIf_GetVersionInfo.o\
CanIf_Init.o\
CanIf_Lok_Buffer.o\
CanIf_PBcfg.o\
CanIf_PduMode.o\
CanIf_Prv.o\
CanIf_Rb_Apis.o\
CanIf_ReadNotifStatus.o\
CanIf_ReadRxPduData.o\
CanIf_RxIndication.o\
CanIf_RxIndication_Integration.o\
CanIf_SetControllerMode_Integration.o\
CanIf_SetDynamicTxId.o\
CanIf_Shared.o\
CanIf_Transceiver.o\
CanIf_Transmit.o\
CanIf_TriggerTransmit.o\
CanIf_TxConfirmation.o\
CanIf_Wakeup.o\
CanIf_Write_Integration.o\
CanIf_XCore.o\
CanManager.o\
CanSM_CheckTransceiverWakeFlagIndication.o\
CanSM_ClearTrcvWufFlagIndication.o\
CanSM_ConfirmPnAvailability.o\
CanSM_ControllerBusoff.o\
CanSM_ControllerModeIndication.o\
CanSM_GetCurrentComMode.o\
CanSM_GetVersionInfo.o\
CanSM_Init.o\
CanSM_InternalStateTransition.o\
CanSM_Main.o\
CanSM_NetworkModes.o\
CanSM_PBcfg.o\
CanSM_RequestComMode.o\
CanSM_SetBaudrate.o\
CanSM_SetEcuPassive.o\
CanSM_StartWakeupSource.o\
CanSM_StopWakeupSource.o\
CanSM_TransceiverModeIndication.o\
CanSM_TxTimeoutException.o\
CanTp.o\
CanTP_Callout.o\
CanTp_Cfg.o\
CanTp_Prv.o\
cantrcv.o\
CD_DecoderSlim.o\
CfgMcalAdc.o\
CfgMcalDio.o\
CfgSwcServiceDcm_DslDsd.o\
clocks.o\
Com_BusLoadManagement.o\
Com_ByteCopy.o\
Com_ByteCopyInit.o\
Com_Cfg.o\
Com_CopyRxData.o\
Com_CopyTxData.o\
Com_DeInit.o\
Com_EnableRxDm.o\
Com_Filter.o\
Com_GetStatus.o\
Com_GetVersionInfo.o\
Com_Init.o\
Com_Integration.o\
Com_InvalidateShadowSignal.o\
Com_InvalidateSignal.o\
Com_InvalidateSignalGroup.o\
Com_IpduGroupStart.o\
Com_IpduGroupStop.o\
Com_MainFunctionRouteSignals.o\
Com_MainFunctionRx.o\
Com_MainFunctionTx.o\
Com_PackGwMappings.o\
Com_PackSignal.o\
Com_PBcfg.o\
Com_ProcessSignal.o\
Com_ProcessSignalGroup.o\
Com_ReceiveDynSignal.o\
Com_ReceiveShadowSignal.o\
Com_ReceiveSignal.o\
Com_ReceiveSignalGroup.o\
Com_ReceiveSignalGroupArray.o\
Com_RxIndication.o\
Com_SendDynSignal.o\
Com_SendIpdu.o\
Com_SendSignal.o\
Com_SendSignalGroup.o\
Com_SendSignalGroupArray.o\
Com_ShadowBuffToIpduBuff.o\
Com_StartOfReception.o\
Com_SwitchIpduTxMode.o\
Com_TpRxIndication.o\
Com_TpTxConfirmation.o\
Com_TriggerIPDUSend.o\
Com_TriggerIPDUSendWithMetaData.o\
Com_TriggerTransmit.o\
Com_TxChangeMode.o\
Com_TxConfirmation.o\
Com_UnpackSignal.o\
Com_UpdateShadowSignal.o\
ComAppl.o\
ComM.o\
ComM_BusSM_ModeIndication.o\
ComM_Cfg.o\
ComM_CommunicationAllowed.o\
ComM_Dcm_ActiveDiagnostic.o\
ComM_Dcm_InactiveDiagnostic.o\
ComM_DeInit.o\
ComM_EcuM_PNCWakeUpIndication.o\
ComM_EcuM_WakeupIndication.o\
ComM_GetCurrentComMode.o\
ComM_GetInhibitionStatus.o\
ComM_GetMaxComMode.o\
ComM_GetRequestedComMode.o\
ComM_GetState.o\
ComM_GetStatus.o\
ComM_GetVersionInfo.o\
ComM_Init.o\
ComM_LChannelMainFunction.o\
ComM_LimitChannelToNoComMode.o\
ComM_LimitECUToNoComMode.o\
ComM_LPncMainFunction.o\
ComM_LUpdateFullComRequestors.o\
ComM_Main.o\
ComM_Nm_BusSleepMode.o\
ComM_Nm_NetworkMode.o\
ComM_Nm_NetworkStartIndication.o\
ComM_Nm_PrepareBusSleepMode.o\
ComM_Nm_RestartIndication.o\
ComM_PBcfg.o\
ComM_PreventWakeUp.o\
ComM_ReadInhibitCounter.o\
ComM_RequestComMode.o\
ComM_ResetInhibitCounter.o\
ComM_SetECUGroupClassification.o\
ComMAppl.o\
Crc.o\
Crc_Cfg.o\
ctrl.o\
Dcm_Dsd_Lib.o\
Dcm_Dsd_Rdpi.o\
Dcm_Dsd_Roe.o\
Dcm_Dsd_StateMachine.o\
Dcm_Dsl_CancelTransmit.o\
Dcm_Dsl_ComMInteraction.o\
Dcm_Dsl_CopyRxData.o\
Dcm_Dsl_CopyTxData.o\
Dcm_Dsl_OBDStateMachine.o\
Dcm_Dsl_PagedBuffer.o\
Dcm_Dsl_Protocol.o\
Dcm_Dsl_RxIndication.o\
Dcm_Dsl_Security.o\
Dcm_Dsl_Session.o\
Dcm_Dsl_StartOfReception.o\
Dcm_Dsl_StateMachine.o\
Dcm_Dsl_TxResponse.o\
Dcm_Lcfg_DspUds.o\
DcmAppl_CheckEncryptionCompressionMethod.o\
DcmAppl_ConfirmationRespPend.o\
DcmAppl_Dcm_GetProgConditions.o\
DcmAppl_Dcm_ProcessRequestDownload.o\
DcmAppl_Dcm_ProcessRequestTransferExit.o\
DcmAppl_Dcm_ProcessRequestUpload.o\
DcmAppl_Dcm_ReadMemory.o\
DcmAppl_Dcm_SetProgConditions.o\
DcmAppl_Dcm_WriteMemory.o\
DcmAppl_DcmCancelPagedBufferProcessing.o\
DcmAppl_DcmCheckCDTCRecord.o\
DcmAppl_DcmCheckControlMaskAndState.o\
DcmAppl_DcmCheckRdbiResponseLength.o\
DcmAppl_DcmCheckRoutineControlOptionRecord.o\
DcmAppl_DcmCheckSeed.o\
DcmAppl_DcmCheckWDBIReqLen.o\
DcmAppl_DcmClearRoeEventInformation.o\
DcmAppl_DcmCommControlConditionCheck.o\
DcmAppl_DcmComModeError.o\
DcmAppl_DcmConfirmation.o\
DcmAppl_DcmConfirmation_DcmNegResp.o\
DcmAppl_DcmConfirmation_GeneralReject.o\
DcmAppl_DcmConfirmationRDPI.o\
DcmAppl_DcmControlDtcSettingEnableStatus.o\
DcmAppl_DcmCopyRxData.o\
DcmAppl_DcmEcuResetPreparation.o\
DcmAppl_DcmGetNRCForMinLengthCheck.o\
DcmAppl_DcmGetP2Timings.o\
DcmAppl_DcmGetPermissionForMemoryAccess_u8.o\
DcmAppl_DcmGetPermTxWarmResp.o\
DcmAppl_DcmGetRemainingResponseLength.o\
DcmAppl_DcmGetROEDidInfo.o\
DcmAppl_DcmGetRoeDTCInfo.o\
DcmAppl_DcmGetRxPermission.o\
DcmAppl_DcmGetSesChgPermission.o\
DcmAppl_DcmGetStoreType.o\
DcmAppl_DcmGetUpdatedDelayForPowerOn.o\
DcmAppl_DcmGetUpdatedDelayTime.o\
DcmAppl_DcmIndicationFuncTpr.o\
DcmAppl_DcmIsComModeDefault.o\
DcmAppl_DcmMemSizeCheckForTransferData.o\
DcmAppl_DcmModifyResponse.o\
DcmAppl_DcmNotification.o\
DcmAppl_DcmReadDataNRC.o\
DcmAppl_DcmReadDddiFromNvM.o\
DcmAppl_DcmRespWarmInit.o\
DcmAppl_DcmRxIndication.o\
DcmAppl_DcmSecaInvalidKey.o\
DcmAppl_DcmSecaValidKey.o\
DcmAppl_DcmSecurityLevelLocked.o\
DcmAppl_DcmSesCtrlChangeIndication.o\
DcmAppl_DcmSetUpRoeEvent.o\
DcmAppl_DcmStartOfReception.o\
DcmAppl_DcmStartProtocol.o\
DcmAppl_DcmStopProtocol.o\
DcmAppl_DcmStoreRespForJump.o\
DcmAppl_DcmStoreROEcycleCounter.o\
DcmAppl_DcmStoreRoeDidInfo.o\
DcmAppl_DcmStoreRoeDTCInfo.o\
DcmAppl_DcmSwitchCommunicationControl.o\
DcmAppl_DcmTransferDataCheckPermission.o\
DcmAppl_DcmUpdateRxTable.o\
DcmAppl_DcmWriteOrClearDddiInNvM.o\
DcmAppl_DDDI_Read_Memory_Condition.o\
DcmAppl_DisableDTCSetting.o\
DcmAppl_EnableDTCSetting.o\
DcmAppl_ManufacturerNotification.o\
DcmAppl_OBD_Callbacks.o\
DcmAppl_OBD_Mode04.o\
DcmAppl_P3TimeoutIndication.o\
DcmAppl_Switch_DcmBootLoaderReset.o\
DcmAppl_Switch_DcmDiagnosticSessionControl.o\
DcmAppl_Switch_DcmDriveToDriveReset.o\
DcmAppl_Switch_DcmEcuReset.o\
DcmAppl_Switch_DcmExecuteDscReset.o\
DcmAppl_Switch_DcmExecuteEcuReset.o\
DcmAppl_Switch_DcmExecuteReset.o\
DcmAppl_Switch_DcmResponseOnEvent.o\
DcmAppl_Switch_DcmSysSupplierReset.o\
DcmAppl_UserCommCtrlReEnableModeRuleService.o\
DcmAppl_UserDIDModeRuleService.o\
DcmAppl_UserDTCSettingEnableModeRuleService.o\
DcmAppl_UserMemoryRangeModeRuleService.o\
DcmAppl_UserRIDModeRuleService.o\
DcmAppl_UserServiceModeRuleService.o\
DcmAppl_UserSubServiceModeRuleService.o\
DcmCore_DslDsd_BootLoader.o\
DcmCore_DslDsd_ConfirmRespPend.o\
DcmCore_DslDsd_GetKwpTimingValues.o\
DcmCore_DslDsd_InternalApi.o\
DcmCore_DslDsd_PrepareKwpTimingValues.o\
DcmCore_DslDsd_RestartP3Timer.o\
DcmCore_DslDsd_RestoreSecaTimer.o\
DcmCore_DslDsd_SetKwpDefaultTimingValues.o\
DcmCore_DslDsd_SetKwpTimingValues.o\
DcmCore_DslDsd_SetP3MaxMonitoring.o\
DcmCore_DslDsd_SignalLib.o\
DcmCore_DslDsd_WarmStart.o\
DcmCore_Main.o\
DcmCore_Main_Init.o\
DcmDspObd_Mode1.o\
DcmDspObd_Mode2.o\
DcmDspObd_Mode37A.o\
DcmDspObd_Mode4.o\
DcmDspObd_Mode6.o\
DcmDspObd_Mode8.o\
DcmDspObd_Mode9.o\
DcmDspUds_CC.o\
DcmDspUds_Cdi.o\
DcmDspUds_Cdtcs.o\
DcmDspUds_Dddi.o\
DcmDspUds_Did_Support.o\
DcmDspUds_Dsc.o\
DcmDspUds_Er.o\
DcmDspUds_GetVIN.o\
DcmDspUds_Iocbi.o\
DcmDspUds_Memaddress_Calc.o\
DcmDspUds_Rc.o\
DcmDspUds_Rdbi.o\
DcmDspUds_Rdpi.o\
DcmDspUds_Rdtc.o\
DcmDspUds_Rdtc_GetFreezeFrameDataByRecord.o\
DcmDspUds_Rdtc_RepDTCFaultDetectionCounter.o\
DcmDspUds_Rdtc_RepFailedDTC.o\
DcmDspUds_Rdtc_RepNumDTCByStatusMask.o\
DcmDspUds_Rdtc_ReportDTCBySevMaskRec.o\
DcmDspUds_Rdtc_ReportDTCSnapshotRecId.o\
DcmDspUds_Rdtc_ReportExtendedDataRecordByDTC.o\
DcmDspUds_Rdtc_ReportSnapshotRecordByDTC.o\
DcmDspUds_Rdtc_RepSeverityOfDTC.o\
DcmDspUds_Rdtc_RepSuppDTC.o\
DcmDspUds_RequestDownload.o\
DcmDspUds_RequestTransferExit.o\
DcmDspUds_RequestUpload.o\
DcmDspUds_Rmba.o\
DcmDspUds_Roe.o\
DcmDspUds_Seca.o\
DcmDspUds_Seca_ChgSecurity.o\
DcmDspUds_Seca_RestoreDelayCount.o\
DcmDspUds_Seca_SecurityIni.o\
DcmDspUds_Tp.o\
DcmDspUds_TransferData.o\
DcmDspUds_Uds_Did_F186.o\
DcmDspUds_Wdbi.o\
DcmDspUds_Wmba.o\
DcmManager.o\
DcmMemCheck.o\
Dem_Cfg_Clear.o\
Dem_Cfg_Client_DataStructures.o\
Dem_Cfg_DTC_DataStructures.o\
Dem_Cfg_Events_DataStructures.o\
Dem_Cfg_NvmCallbacks.o\
Dem_Cfg_OperationCycle_DataStructures.o\
Dem_Clear.o\
Dem_Client.o\
Dem_Client_Api.o\
Dem_ClientMachine_Clear.o\
Dem_ClientRequestDispatcher.o\
Dem_ConsisChk.o\
Dem_Deb.o\
Dem_DebArTime.o\
Dem_DebBase.o\
Dem_DebCtrBaseClass.o\
Dem_Dependencies.o\
Dem_DisturbanceMemory.o\
Dem_DTCFilter.o\
Dem_DTCGroup.o\
Dem_DTCs.o\
Dem_DTCStatusByte.o\
Dem_EnableCondition.o\
Dem_EnvDataElement.o\
Dem_EnvDid.o\
Dem_EnvExtendedData.o\
Dem_EnvExtendedDataRec.o\
Dem_EnvFFRecNumeration.o\
Dem_EnvFreezeFrame.o\
Dem_EnvMain.o\
Dem_EvBuff.o\
Dem_EvBuffDistributor.o\
Dem_EventFHandling.o\
Dem_EventRecheck.o\
Dem_Events.o\
Dem_EventStatus.o\
Dem_EvMem.o\
Dem_EvMemApi.o\
Dem_EvMemGen.o\
Dem_EvtRelatedData.o\
Dem_GenericNvData.o\
Dem_Indicator.o\
Dem_IndicatorAttributes.o\
Dem_J1939EnvFreezeFrame.o\
Dem_KL15Persistence.o\
Dem_Lok_J1939Dcm.o\
Dem_Main.o\
Dem_Mapping.o\
Dem_Nvm.o\
Dem_NvmCallbacks.o\
Dem_OperationCycle.o\
Dem_PrjChronoSorting.o\
Dem_PrjDisturbanceMemory.o\
Dem_PrjEnvDataElement.o\
Dem_PrjEraseAllNvMDataHandling.o\
Dem_PrjEvmemProjectExtension.o\
Dem_StorageCondition.o\
DemAppInterface.o\
DemManager.o\
det.o\
DevCanHandling.o\
EcuDiag.o\
EcuM_BootTarget.o\
EcuM_Callout_Stubs.o\
EcuM_Cfg.o\
EcuM_Cfg_PbExt.o\
EcuM_Cfg_Sleep.o\
EcuM_Cfg_Startup.o\
EcuM_Cfg_SynchPoint.o\
EcuM_CurrentState.o\
EcuM_KillAllRequests.o\
EcuM_Lcfg.o\
EcuM_Lok_RteActions.o\
EcuM_MainFunction.o\
EcuM_Misc.o\
EcuM_PBcfg.o\
EcuM_Prv.o\
EcuM_ReleasePOST_RUN.o\
EcuM_ReleaseRUN.o\
EcuM_RequestPOST_RUN.o\
EcuM_RequestRUN.o\
EcuM_SetState.o\
EcuM_Shutdown.o\
EcuM_ShutdownServices.o\
EcuM_Sleep.o\
EcuM_Startup.o\
EcuM_WakeupServices.o\
eeiface.o\
EnvManager.o\
fbl_apnv_fee.o\
fdl_descriptor.o\
Fee_30_SmallSector.o\
EcuabFee_BlockHandler.o\
EcuabFee_Cfg.o\
EcuabFee_DatasetHandler.o\
EcuabFee_FlsCoordinator.o\
EcuabFee_InstanceHandler.o\
EcuabFee_Layer1_Read.o\
EcuabFee_Layer1_Write.o\
EcuabFee_Layer2_DatasetEraser.o\
EcuabFee_Layer2_InstanceFinder.o\
EcuabFee_Layer2_WriteInstance.o\
EcuabFee_Layer3_ReadManagementBytes.o\
EcuabFee_PartitionHandler.o\
EcuabFee_TaskManager.o\
FeeFblBlockInterface.o\
Fls.o\
Fls_Internal.o\
Fls_Irq.o\
Fls_PBcfg.o\
Fls_Ram.o\
Fls_Version.o\
gpio.o\
hmac_sha2.o\
IDOM.o\
IDOM_If.o\
McalAdc.o\
McalDio.o\
McalGpt.o\
McalMcu.o\
McalWdg.o\
Mcu.o\
MemConversion.o\
MemIf.o\
MemIf_Cfg.o\
multiframe.o\
NvM.o\
NvM_Act.o\
NvM_Cfg.o\
NvM_Crc.o\
NvM_JobProc.o\
NvM_Qry.o\
NvM_Queue.o\
NvmManager.o\
Os_SwcApplTpms.o\
ostm0.o\
PartWAlloc.o\
PduR_BufferPool.o\
PduR_Cfg.o\
PduR_dLoIf.o\
PduR_EnableDisableRouting.o\
PduR_Gateway_DDIfTransmit_FiFo.o\
PduR_Gateway_DDIfTxConf_FiFo.o\
PduR_Gateway_DDIfTxConf_NoBuf.o\
PduR_Gateway_IfRxInd.o\
PduR_Gateway_TpDcmTx.o\
PduR_Gateway_TpRx.o\
PduR_Gateway_TpTx.o\
PduR_Gateway_TpTxConf.o\
PduR_Gateway_TTIfTransmit_Buf.o\
PduR_Gateway_TTIfTransmit_FiFo.o\
PduR_Gateway_TTIfTrigTx_Buf.o\
PduR_Gateway_TTIfTrigTx_FiFo.o\
PduR_Gateway_TTIfTxConf_Buf.o\
PduR_Gateway_TTIfTxConf_FiFo.o\
PduR_Gateway_UpIf.o\
PduR_GetBuffer.o\
PduR_GetConfigurationId.o\
PduR_GetVersionInfo.o\
PduR_Globals.o\
PduR_Init.o\
PduR_InvalidId_If.o\
PduR_InvalidId_Tp.o\
PduR_InvalidId_UpTx.o\
PduR_LoTp.o\
PduR_Multicast_LoTpTxToUp.o\
PduR_Multicast_Tp.o\
PduR_Multicast_UpToLo.o\
PduR_Multicast_UpTx.o\
PduR_Null_UpIf.o\
PduR_NullFunc_TrigTx.o\
PduR_PBcfg.o\
PduR_RPG_TpRx.o\
PduR_UpIf.o\
PduR_UpTp.o\
PduRAppl.o\
pkcs7_padding.o\
procdat.o\
procdat_if.o\
ProductionFlashInterface.o\
r_fdl_hw_access.o\
r_fdl_user_if.o\
r_fdl_user_if_init.o\
rba_BswSrv_MemCompare.o\
rba_BswSrv_MemCopy.o\
rba_BswSrv_MemSet.o\
rba_DiagLib_ByteOrderUtils.o\
RdcManager.o\
RdcRingbuffer.o\
RdcStandstill.o\
RdcStandstillDebug.o\
REDiag.o\
REDiag_if.o\
rlin30.o\
rscan.o\
Rte_Dem_NvM.o\
Rte_Nvm_Type.o\
SchM.o\
sha2.o\
SignalCallbacks.o\
sila.o\
state_bz.o\
state_fzz.o\
state_zk.o\
statemanager.o\
statistics.o\
statistics_if.o\
SwcApplDcm.o\
SwcApplDcm_MsgAuthentication.o\
SwcApplEcuM.o\
SwcApplTpms_abs_lin.o\
SwcApplTpms_CAN_If.o\
SwcApplTpms_Common.o\
SwcApplTpms_DevCanMessages.o\
SwcApplTpms_Diag.o\
SwcApplTpms_DTC.o\
SwcApplTpms_FPA.o\
SwcApplTpms_LearnEOL.o\
SwcApplTpms_NvM.o\
SwcApplTpms_NvM_Cat01_If.o\
SwcApplTpms_NvM_Cat02_If.o\
SwcApplTpms_NvM_Cat03_If.o\
SwcApplTpms_NvM_Cat04_If.o\
SwcApplTpms_NvM_Cat05_If.o\
SwcApplTpms_NvM_Cat06_If.o\
SwcApplTpms_NvM_Cat10_If.o\
SwcApplTpms_Nvm_If.o\
SwcApplTpms_OSEK_If.o\
SwcApplTpms_Rte.o\
SwcApplTpms_Vehstate.o\
SwcApplTpms_Version.o\
SwcServiceEcuM.o\
SwcServiceStartUp.o\
SysManager.o\
tau.o\
TmsManager.o\
TSSMsg.o\
USCS.o\
USWarn.o\
uswarn_If.o\
USWTime.o\
version.o\
VStdLib.o\
WAlloc.o\
Walloc_IF.o\
watcf.o\
wdt.o\
WTAxImb.o\
WTDHW.o\
WTEuF.o\
WTFT.o\
WTHiP.o\
WTHTDR.o\
WTHTVDR.o\
WTLowP.o\
WTPminDR.o\
WTT.o\
)

#******************************************************************************
# search for header files in following directories
#******************************************************************************
INC = \
$(Include_common)\
$(Source_ProjectCompiler)\
$(Source_ProjectCfg)\
$(Source_SwcApplTpms)\
$(Include_SwcApplTpms_Intface)\
$(Source_SwcApplEcuM)\
$(Source_SwcServiceEcuM)\
$(Source_SwcServiceNvM)\
$(Source_SwcServiceOs)\
$(Source_SwcServiceStartUp)\
$(Source_McalAdc)\
$(Source_McalDio)\
$(Source_McalGpt)\
$(Source_McalMcu)\
$(Source_McalWdg)\
$(DIR_SOURCE)/wrappers\
$(Source_wrappers_McalAta)\
$(Source_McalLin)\
$(Source_McalCan)\
$(Source_wrappers_OS)\
$(Source_McalFls)\
$(Source_EcuabFee)\
$(Source_EcuabMemIf)\
$(Source_wrappers_VStdLib)\
$(Source_wrappers)\
$(Source_wrappers_Crc)\
$(Source_wrappers_FBL_APPL)\
$(Source_wrappers_CANMANAGER)\
$(Source_wrappers_NVMMANAGER)\
$(Source_wrappers_DEMMANAGER)\
$(Source_wrappers_RDCMANAGER)\
$(Source_wrappers_ENVMANAGER)\
$(Source_wrappers_SYSMANAGER)\
$(Source_wrappers_EcuabCanIf)\
$(Source_wrappers_SwcServiceCanSM)\
$(Source_wrappers_SwcServiceCanTp)\
$(Source_wrappers_SwcServiceCanTp_PreCompile)\
$(Source_wrappers_SwcServiceCom)\
$(Source_wrappers_SwcServiceComM)\
$(Source_wrappers_SwcServiceComStack)\
$(Source_wrappers_SwcServiceDcm)\
$(Source_wrappers_SwcServicePduR)\
$(Source_wrappers_SwcServiceEcuM)\
$(Source_wrappers_Bfx)\
$(Source_wrappers_SwcServiceDem)\
$(Source_wrappers_SwcServiceDcm_SRC_CORE_DSLDSD)\
$(Source_wrappers_SwcServiceDcm_SRC_CORE_LIB)\
$(Source_wrappers_SwcServiceDcm_SRC_CORE_MAIN)\
$(Source_wrappers_SwcServiceDcm_SRC_DSP_LIB)\
$(Source_wrappers_SwcServiceDcm_SRC_DSP_OBD)\
$(Source_wrappers_SwcServiceDcm_SRC_DSP_UDS)\
$(Source_wrappers_SwcServiceDcm_SRC_DSD)\
$(Source_wrappers_SwcServiceDcm_SRC_DSL)\
$(Source_SwcServiceDet)\
$(Source_SwcServiceFiM)\
$(Source_wrappers_LibAutosarDiag)\
$(Source_wrappers_rba_BswSrv)\
$(Source_SwcServiceSchM)\
$(SRC_INT_COMM)\
$(SRC_INT_PDUR)\
$(SRC_INT_CANIF)\
$(SRC_INT_COM)\
$(SRC_INT_CANTP)\
$(SRC_INT_ECUM)\
$(SRC_INT_DET)\
$(SRC_INT_DCM)\
$(SRC_INT_DEM)\
$(SRC_INT_FIM)\
$(Include_wrappers_EcuabCanIf)\
$(Include_wrappers_SwcServiceCom)\
$(Include_wrappers_SwcServiceComM)\
$(Include_wrappers_SwcServicePduR)\
$(Include_wrappers_api_Bfx)\
$(Include_SwcServiceDet)\
$(Include_SwcServiceFiM)\
$(Include_wrappers_api_LibAutosarDiag)\
$(Include_wrappers_api_rba_BswSrv)\

#******************************************************************************
# search for source files in following directories
#******************************************************************************
VPATH = \
$(Source_ProjectCompiler)\
$(Source_ProjectCfg)\
$(Source_SwcApplTpms)\
$(Source_SwcApplEcuM)\
$(Source_SwcServiceEcuM)\
$(Source_SwcServiceNvM)\
$(Source_SwcServiceOs)\
$(Source_SwcServiceStartUp)\
$(Source_McalAdc)\
$(Source_McalDio)\
$(Source_McalGpt)\
$(Source_McalMcu)\
$(Source_McalWdg)\
$(DIR_SOURCE)/wrappers\
$(Source_wrappers_McalAta)\
$(Source_McalLin)\
$(Source_McalCan)\
$(Source_wrappers_OS)\
$(Source_McalFls)\
$(Source_EcuabFee)\
$(Source_EcuabMemIf)\
$(Source_wrappers_VStdLib)\
$(Source_wrappers)\
$(Source_wrappers_Crc)\
$(Source_wrappers_FBL_APPL)\
$(Source_wrappers_CANMANAGER)\
$(Source_wrappers_NVMMANAGER)\
$(Source_wrappers_DEMMANAGER)\
$(Source_wrappers_RDCMANAGER)\
$(Source_wrappers_ENVMANAGER)\
$(Source_wrappers_SYSMANAGER)\
$(Source_wrappers_EcuabCanIf)\
$(Source_wrappers_SwcServiceCanSM)\
$(Source_wrappers_SwcServiceCanTp)\
$(Source_wrappers_SwcServiceCanTp_PreCompile)\
$(Source_wrappers_SwcServiceCom)\
$(Source_wrappers_SwcServiceComM)\
$(Source_wrappers_SwcServiceDcm)\
$(Source_wrappers_SwcServiceDcm_SRC_CORE_DSLDSD)\
$(Source_wrappers_SwcServiceDcm_SRC_CORE_LIB)\
$(Source_wrappers_SwcServiceDcm_SRC_CORE_MAIN)\
$(Source_wrappers_SwcServiceDcm_SRC_DSP_LIB)\
$(Source_wrappers_SwcServiceDcm_SRC_DSP_OBD)\
$(Source_wrappers_SwcServiceDcm_SRC_DSP_UDS)\
$(Source_wrappers_SwcServiceDcm_SRC_DSD)\
$(Source_wrappers_SwcServiceDcm_SRC_DSL)\
$(Source_wrappers_SwcServiceDem)\
$(Source_wrappers_SwcServiceComStack)\
$(Source_wrappers_SwcServicePduR)\
$(Source_wrappers_SwcServiceEcuM)\
$(Source_SwcServiceDet)\
$(Source_wrappers_LibAutosarDiag)\
$(SRC_INT_CANIF)\
$(SRC_INT_CANTP)\
$(SRC_INT_COM)\
$(SRC_INT_COMM)\
$(SRC_INT_PDUR)\
$(SRC_INT_DET)\
$(SRC_INT_DCM)\
$(SRC_INT_DEM)\
$(SRC_INT_ECUM)\
$(Source_wrappers_rba_BswSrv)\
$(Source_wrappers_Bfx)\

###############################################################################
# Command to link all the generated object files                              #
###############################################################################
$(TARGET) : $(OBJS) $(LDSCRIPT)
	@echo Check application directory ...
	@echo ... Done
	@echo Building the executable...
	$(LD) $(OBJS) $(LDFLAGS)
	$(ADD_TOOLS)
	@echo ... Successful


################################################################################
# Command to generate object files from all dependent files                    
################################################################################
$(DIR_OUTPUT_OBJ)/%.o : %.c
	@echo Check C-obj output directory ...
	@if not exist $(DIR_OUTPUT_OBJ) mkdir $(subst /,\,$(DIR_OUTPUT_OBJ))
	@echo ... Done
	@echo Generating $(@F):
	@echo Compiling $<
	$(CC) $< $(CFLAGS)
	@echo ... Done
	@echo ***************************************************************************

$(DIR_OUTPUT_OBJ)/%.o : %.850
	@echo Check 850-obj output directory ...
	@if not exist $(DIR_OUTPUT_OBJ) mkdir $(subst /,\,$(DIR_OUTPUT_OBJ))
	@echo ... Done
	@echo Generating $(@F):
	@echo Compiling $<
	$(AS) $< $(ASFLAGS)
	@echo ... Done
	@echo ***************************************************************************

$(DIR_OUTPUT_LST)/%.o : %.850
	@echo Check 850-lst output directory ...
	@if not exist $(DIR_OUTPUT_LST) mkdir $(subst /,\,$(DIR_OUTPUT_LST))
	@echo ... Done
	@echo Generating $(@F):
	@echo Compiling $< 
	$(AS) $< $(ASFLAGS)
	@echo ... Done
	@echo ***************************************************************************


###############################################################################
# Command to delete all generated files                                       #
###############################################################################
clean:
	@echo Delete all object files ...
	@if exist $(subst /,\,$(DIR_OUTPUT_OBJ)) $(DEL_TOOL) $(subst /,\,$(DIR_OUTPUT_OBJ))\*.*>nul 2>nul
	@if exist $(subst /,\,$(DIR_OUTPUT_LST)) $(DEL_TOOL) $(subst /,\,$(DIR_OUTPUT_LST))\*.*>nul 2>nul
	@echo Delete application ...
	@echo ... Done

