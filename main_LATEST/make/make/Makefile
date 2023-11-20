MAKE_MODE=DOS

# ************************************************************************
# paths and source folders
# ************************************************************************
DIR_SOURCE     = ../source
DIR_OUTPUT_OBJ = output/objects
DIR_OUTPUT_LST = output/list

Include_common                 = $(DIR_SOURCE)/common
Source_LibAutosar              = $(DIR_SOURCE)/LibAutosar
Source_McalAdc                 = $(DIR_SOURCE)/McalAdc
Source_McalCan                 = $(DIR_SOURCE)/McalCan
Source_McalDio                 = $(DIR_SOURCE)/McalDio
Source_McalFls                 = $(DIR_SOURCE)/McalFls
Source_McalGpt                 = $(DIR_SOURCE)/McalGpt
Source_McalLin                 = $(DIR_SOURCE)/McalLin
Source_McalMcu                 = $(DIR_SOURCE)/McalMcu
Source_McalWdg                 = $(DIR_SOURCE)/McalWdg
Source_EcuabFee                = $(DIR_SOURCE)/EcuabFee
Source_EcuabIfCan              = $(DIR_SOURCE)/EcuabIfCan
Source_EcuabIfMem              = $(DIR_SOURCE)/EcuabIfMem
Source_EcuabTrcvCan            = $(DIR_SOURCE)/EcuabTrcvCan
Source_SwcServiceBswM          = $(DIR_SOURCE)/SwcServiceBswM
Source_SwcServiceCom           = $(DIR_SOURCE)/SwcServiceCom
Source_SwcServiceComM          = $(DIR_SOURCE)/SwcServiceComM
Source_SwcServiceDcm           = $(DIR_SOURCE)/SwcServiceDcm
Source_SwcServiceDem           = $(DIR_SOURCE)/SwcServiceDem
Source_SwcServiceDet           = $(DIR_SOURCE)/SwcServiceDet
Source_SwcServiceEcuM          = $(DIR_SOURCE)/SwcServiceEcuM
Source_SwcServiceFiM           = $(DIR_SOURCE)/SwcServiceFiM
Source_SwcServiceNvM           = $(DIR_SOURCE)/SwcServiceNvM
Source_SwcServiceOs            = $(DIR_SOURCE)/SwcServiceOs
Source_SwcServicePduR          = $(DIR_SOURCE)/SwcServicePduR
Source_SwcServiceSchM          = $(DIR_SOURCE)/SwcServiceSchM
Source_SwcServiceSmCan         = $(DIR_SOURCE)/SwcServiceSmCan
Source_SwcServiceStartUp       = $(DIR_SOURCE)/SwcServiceStartUp
Source_SwcServiceTpCan         = $(DIR_SOURCE)/SwcServiceTpCan
Source_SwcApplDcm              = $(DIR_SOURCE)/SwcApplDcm
Source_SwcApplDem              = $(DIR_SOURCE)/SwcApplDem
Source_SwcApplEcuM             = $(DIR_SOURCE)/SwcApplEcuM
Source_SwcApplNvM              = $(DIR_SOURCE)/SwcApplNvM
Source_SwcApplTpms             = $(DIR_SOURCE)/SwcApplTpms
Source_ProjectCfg              = $(DIR_SOURCE)/ProjectCfg
Source_ProjectMemMap           = $(DIR_SOURCE)/ProjectMemMap
Source_ProjectARA              = $(DIR_SOURCE)/ProjectARA
Source_wrappers                = $(DIR_SOURCE)/wrappers
Source_wrappers_Bfx            = $(DIR_SOURCE)/wrappers/Bfx
Source_wrappers_LibAutosarDiag = $(DIR_SOURCE)/wrappers/LibAutosarDiag
Source_wrappers_RDCMANAGER     = $(DIR_SOURCE)/wrappers/RDC_MANAGER
Source_wrappers_ENVMANAGER     = $(DIR_SOURCE)/wrappers/ENV_MANAGER
Source_wrappers_McalAta        = $(DIR_SOURCE)/wrappers/McalAta
Source_wrappers_FBL_APPL       = $(DIR_SOURCE)/wrappers/FBL_APPL
Source_wrappers_VStdLib        = $(DIR_SOURCE)/wrappers/VStdLib
Source_wrappers_rba_BswSrv     = $(DIR_SOURCE)/wrappers/rba_BswSrv

OBJLIST=obj_list.txt
EXT=abs
OUTFILE=$(TARGET)

# ******************************************************************************
# Library files for RIVIAN
# ******************************************************************************
LIB_OS   = "$(Source_SwcServiceOs)/RTAOS.a"

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
               -D BUILD_RIVIAN

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
applvect.o\
ata_dev_5785.o\
ata_Rec.o\
Bfx_Bit.o\
Bfx_GetVersionInfo.o\
Bfx_TstParityEven_u16_u8.o\
Bfx_TstParityEven_u32_u8.o\
Bfx_TstParityEven_u8_u8.o\
BrsStartup_c0.o\
bswm.o\
can.o\
can_table.o\
CanIf_Controller.o\
CanIf_Init.o\
CanIf_PBcfg.o\
CanIf_PduMode.o\
CanIf_Prv.o\
CanIf_Rb_Apis.o\
CanIf_ReadNotifStatus.o\
CanIf_RxIndication.o\
CanIf_Transmit.o\
CanIf_TxConfirmation.o\
CanManager.o\
CanSM_ControllerBusoff.o\
CanSM_ControllerModeIndication.o\
CanSM_GetCurrentComMode.o\
CanSM_Init.o\
CanSM_InternalStateTransition.o\
CanSM_Main.o\
CanSM_NetworkModes.o\
CanSM_PBcfg.o\
CanSM_RequestComMode.o\
CanSM_StartWakeupSource.o\
CanSM_StopWakeupSource.o\
CanSM_TxTimeoutException.o\
CanTp.o\
CanTp_Cfg.o\
CanTp_Prv.o\
cantrcv.o\
CfgMcalAdc.o\
CfgMcalDio.o\
CfgSwcServiceDcm_DslDsd.o\
clocks.o\
Com_BusLoadManagement.o\
Com_ByteCopy.o\
Com_ByteCopyInit.o\
Com_Cfg.o\
Com_DeInit.o\
Com_EnableRxDm.o\
Com_Filter.o\
Com_GetStatus.o\
Com_GetVersionInfo.o\
Com_Init.o\
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
Com_SwitchIpduTxMode.o\
Com_TriggerIPDUSend.o\
Com_TriggerTransmit.o\
Com_TxChangeMode.o\
Com_TxConfirmation.o\
Com_UnpackSignal.o\
Com_UpdateShadowSignal.o\
ComM.o\
ComM_BusSM_ModeIndication.o\
ComM_Cfg.o\
ComM_CommunicationAllowed.o\
ComM_Dcm_ActiveDiagnostic.o\
ComM_Dcm_InactiveDiagnostic.o\
ComM_DeInit.o\
ComM_EcuM_WakeupIndication.o\
ComM_GetCurrentComMode.o\
ComM_Init.o\
ComM_LChannelMainFunction.o\
ComM_Main.o\
ComM_PBcfg.o\
ComM_RequestComMode.o\
Dcm_Dsd_Lib.o\
Dcm_Dsd_StateMachine.o\
Dcm_Dsl_ComMInteraction.o\
Dcm_Dsl_CopyRxData.o\
Dcm_Dsl_CopyTxData.o\
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
DcmAppl_Dcm_ReadMemory.o\
DcmAppl_Dcm_SetProgConditions.o\
DcmAppl_Dcm_WriteMemory.o\
DcmAppl_DcmCheckCDTCRecord.o\
DcmAppl_DcmCheckRdbiResponseLength.o\
DcmAppl_DcmCheckRoutineControlOptionRecord.o\
DcmAppl_DcmCheckSeed.o\
DcmAppl_DcmCheckWDBIReqLen.o\
DcmAppl_DcmCommControlConditionCheck.o\
DcmAppl_DcmComModeError.o\
DcmAppl_DcmConfirmation.o\
DcmAppl_DcmConfirmation_GeneralReject.o\
DcmAppl_DcmControlDtcSettingEnableStatus.o\
DcmAppl_DcmCopyRxData.o\
DcmAppl_DcmEcuResetPreparation.o\
DcmAppl_DcmGetNRCForMinLengthCheck.o\
DcmAppl_DcmGetPermissionForMemoryAccess_u8.o\
DcmAppl_DcmGetPermTxWarmResp.o\
DcmAppl_DcmGetRxPermission.o\
DcmAppl_DcmGetSesChgPermission.o\
DcmAppl_DcmGetStoreType.o\
DcmAppl_DcmGetUpdatedDelayForPowerOn.o\
DcmAppl_DcmGetUpdatedDelayTime.o\
DcmAppl_DcmIsComModeDefault.o\
DcmAppl_DcmMemSizeCheckForTransferData.o\
DcmAppl_DcmModifyResponse.o\
DcmAppl_DcmNotification.o\
DcmAppl_DcmReadDataNRC.o\
DcmAppl_DcmRxIndication.o\
DcmAppl_DcmSecaInvalidKey.o\
DcmAppl_DcmSecaValidKey.o\
DcmAppl_DcmSecurityLevelLocked.o\
DcmAppl_DcmStartProtocol.o\
DcmAppl_DcmStopProtocol.o\
DcmAppl_DcmSwitchCommunicationControl.o\
DcmAppl_DcmTransferDataCheckPermission.o\
DcmAppl_DisableDTCSetting.o\
DcmAppl_Switch_DcmBootLoaderReset.o\
DcmAppl_Switch_DcmExecuteEcuReset.o\
DcmAppl_Switch_DcmSysSupplierReset.o\
DcmAppl_UserCommCtrlReEnableModeRuleService.o\
DcmAppl_UserDIDModeRuleService.o\
DcmAppl_UserRIDModeRuleService.o\
DcmAppl_UserServiceModeRuleService.o\
DcmAppl_UserSubServiceModeRuleService.o\
DcmCore_DslDsd_BootLoader.o\
DcmCore_DslDsd_ConfirmRespPend.o\
DcmCore_DslDsd_InternalApi.o\
DcmCore_DslDsd_RestartP3Timer.o\
DcmCore_DslDsd_RestoreSecaTimer.o\
DcmCore_DslDsd_SetKwpDefaultTimingValues.o\
DcmCore_DslDsd_SetKwpTimingValues.o\
DcmCore_DslDsd_SetP3MaxMonitoring.o\
DcmCore_DslDsd_SetServiceTable.o\
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
DcmDspUds_Rdtc_RepDataRecordByDTC.o\
DcmDspUds_Rdtc_RepDTCFaultDetectionCounter.o\
DcmDspUds_Rdtc_RepFailedDTC.o\
DcmDspUds_Rdtc_RepNumDTCByStatusMask.o\
DcmDspUds_Rdtc_ReportDTCBySevMaskRec.o\
DcmDspUds_Rdtc_ReportDTCSnapshotRecId.o\
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
Dem_Cfg_DTC_DataStructures.o\
Dem_Cfg_Events_DataStructures.o\
Dem_Cfg_NvmCallbacks.o\
Dem_Cfg_OperationCycle_DataStructures.o\
Dem_Clear.o\
Dem_Client.o\
Dem_ClientClearMachine.o\
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
EcuDiag.o\
EcuM_BootTarget.o\
EcuM_Callout_Stubs.o\
EcuM_Cfg.o\
EcuM_Lcfg.o\
EcuM_MainFunction.o\
EcuM_PBcfg.o\
EcuM_Prv.o\
EcuM_Shutdown.o\
EcuM_ShutdownServices.o\
EcuM_Startup.o\
EcuM_WakeupServices.o\
EnvManager.o\
fbl_apnv_fee.o\
fdl_descriptor.o\
Fee_30_SmallSector.o\
Fee_30_SmallSector_BlockHandler.o\
Fee_30_SmallSector_Cfg.o\
Fee_30_SmallSector_DatasetHandler.o\
Fee_30_SmallSector_FlsCoordinator.o\
Fee_30_SmallSector_InstanceHandler.o\
Fee_30_SmallSector_Layer1_Read.o\
Fee_30_SmallSector_Layer1_Write.o\
Fee_30_SmallSector_Layer2_DatasetEraser.o\
Fee_30_SmallSector_Layer2_InstanceFinder.o\
Fee_30_SmallSector_Layer2_WriteInstance.o\
Fee_30_SmallSector_Layer3_ReadManagementBytes.o\
Fee_30_SmallSector_PartitionHandler.o\
Fee_30_SmallSector_TaskManager.o\
FeeFblBlockInterface.o\
FiM.o\
FiM_Cfg_PbCfg.o\
FiM_Dem.o\
FiM_Init.o\
FiM_Monitor.o\
FiM_Permission.o\
FiM_Status.o\
FiM_Version.o\
Fls.o\
Fls_Internal.o\
Fls_Irq.o\
Fls_PBcfg.o\
Fls_Ram.o\
Fls_Version.o\
gpio.o\
hmac_sha2.o\
LibAutosar_Crc.o\
McalAdc.o\
McalDio.o\
McalGpt.o\
McalMcu.o\
McalWdg.o\
Mcu.o\
MemConversion.o\
MemIf.o\
MemIf_Cfg.o\
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
PduR_dLoIf.o\
PduR_EnableDisableRouting.o\
PduR_Gateway_DDIfTxConf_NoBuf.o\
PduR_GetConfigurationId.o\
PduR_Globals.o\
PduR_Init.o\
PduR_InvalidId_If.o\
PduR_InvalidId_Tp.o\
PduR_InvalidId_UpTx.o\
PduR_LoTp.o\
PduR_Multicast_UpToLo.o\
PduR_Multicast_UpTx.o\
PduR_NullFunc_TrigTx.o\
PduR_PBcfg.o\
PduR_UpIf.o\
PduR_UpTp.o\
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
rlin30.o\
rscan.o\
Rte_Dem_NvM.o\
Rte_Nvm_Type.o\
SchM.o\
sha2.o\
SignalCallbacks.o\
SwcApplDcm.o\
SwcApplDcm_MsgAuthentication.o\
SwcApplEcuM.o\
SwcApplTpms_DTC.o\
SwcApplTpms_NvM.o\
SwcApplTpms_NvM_Cat01_If.o\
SwcApplTpms_NvM_Cat02_If.o\
SwcApplTpms_NvM_Cat03_If.o\
SwcApplTpms_NvM_Cat04_If.o\
SwcApplTpms_NvM_Cat05_If.o\
SwcApplTpms_NvM_Cat06_If.o\
SwcApplTpms_NvM_Cat10_If.o\
SwcApplTpms_Nvm_If.o\
SwcApplTpms_abs_lin.o\
SwcApplTpms_FPA.o\
SwcApplTpms_Rte.o\
SwcApplTpms_Version.o\
Break.o\
busmsg.o\
calibr.o\
CD_DecoderSlim.o\
ctrl.o\
DevCanHandling.o\
eeiface.o\
IDOM.o\
IDOM_If.o\
multiframe.o\
procdat.o\
procdat_if.o\
REDiag.o\
REDiag_if.o\
sila.o\
statemanager.o\
state_bz.o\
state_fzz.o\
state_zk.o\
statistics.o\
statistics_if.o\
SwcApplTpms_CAN_If.o\
SwcApplTpms_Common.o\
SwcApplTpms_DevCanMessages.o\
SwcApplTpms_Diag.o\
SwcApplTpms_LearnEOL.o\
SwcApplTpms_OSEK_If.o\
SwcApplTpms_Vehstate.o\
TmsManager.o\
TSSMsg.o\
USCS.o\
USWarn.o\
uswarn_If.o\
USWTime.o\
WAlloc.o\
Walloc_IF.o\
watcf.o\
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
SwcServiceEcuM.o\
SwcServiceStartUp.o\
tau.o\
VStdLib.o\
wdt.o\
SysManager.o\
)


#******************************************************************************
# search for header files in following directories
#******************************************************************************
INC = \
$(Include_common)\
$(Source_ProjectMemMap)\
$(Source_ProjectCfg)\
$(Source_ProjectARA)\
$(Source_LibAutosar)\
$(Source_McalAdc)\
$(Source_McalCan)\
$(Source_McalDio)\
$(Source_McalFls)\
$(Source_McalGpt)\
$(Source_McalLin)\
$(Source_McalMcu)\
$(Source_McalWdg)\
$(Source_EcuabFee)\
$(Source_EcuabIfCan)\
$(Source_EcuabIfMem)\
$(Source_EcuabTrcvCan)\
$(Source_SwcServiceBswM)\
$(Source_SwcServiceCom)\
$(Source_SwcServiceComM)\
$(Source_SwcServiceDcm)\
$(Source_SwcServiceDem)\
$(Source_SwcServiceDet)\
$(Source_SwcServiceEcuM)\
$(Source_SwcServiceFiM)\
$(Source_SwcServiceNvM)\
$(Source_SwcServiceOs)\
$(Source_SwcServicePduR)\
$(Source_SwcServiceSchM)\
$(Source_SwcServiceSmCan)\
$(Source_SwcServiceStartUp)\
$(Source_SwcServiceTpCan)\
$(Source_SwcApplDcm)\
$(Source_SwcApplDem)\
$(Source_SwcApplEcuM)\
$(Source_SwcApplNvM)\
$(Source_SwcApplTpms)\
$(Source_wrappers_McalAta)\
$(Source_wrappers_VStdLib)\
$(Source_wrappers_FBL_APPL)\
$(Source_wrappers_RDCMANAGER)\
$(Source_wrappers_ENVMANAGER)\
$(Source_wrappers_Bfx)\
$(Source_wrappers_LibAutosarDiag)\
$(Source_wrappers_rba_BswSrv)\
$(Source_wrappers)\

#******************************************************************************
# search for source files in following directories
#******************************************************************************
VPATH = \
$(Source_LibAutosar)\
$(Source_McalAdc)\
$(Source_McalCan)\
$(Source_McalDio)\
$(Source_McalFls)\
$(Source_McalGpt)\
$(Source_McalLin)\
$(Source_McalMcu)\
$(Source_McalWdg)\
$(Source_EcuabFee)\
$(Source_EcuabIfCan)\
$(Source_EcuabIfMem)\
$(Source_EcuabTrcvCan)\
$(Source_SwcServiceBswM)\
$(Source_SwcServiceCom)\
$(Source_SwcServiceComM)\
$(Source_SwcServiceDcm)\
$(Source_SwcServiceDem)\
$(Source_SwcServiceDet)\
$(Source_SwcServiceEcuM)\
$(Source_SwcServiceFiM)\
$(Source_SwcServiceNvM)\
$(Source_SwcServiceOs)\
$(Source_SwcServicePduR)\
$(Source_SwcServiceSchM)\
$(Source_SwcServiceSmCan)\
$(Source_SwcServiceStartUp)\
$(Source_SwcServiceTpCan)\
$(Source_SwcApplDcm)\
$(Source_SwcApplDem)\
$(Source_SwcApplEcuM)\
$(Source_SwcApplNvM)\
$(Source_SwcApplTpms)\
$(Source_ProjectARA)\
$(Source_ProjectCfg)\
$(Source_wrappers_McalAta)\
$(Source_wrappers_VStdLib)\
$(Source_wrappers_FBL_APPL)\
$(Source_wrappers_RDCMANAGER)\
$(Source_wrappers_ENVMANAGER)\
$(Source_wrappers_LibAutosarDiag)\
$(Source_wrappers_rba_BswSrv)\
$(Source_wrappers_Bfx)\
$(Source_wrappers)\

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

