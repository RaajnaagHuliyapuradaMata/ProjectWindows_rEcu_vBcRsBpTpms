#pragma once
/******************************************************************************/
/* File   : Dcm_Lcfg_DslDsd.hpp                                               */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

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
extern Std_ReturnType SwcServiceDcm_tReadDTCInformation(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tRequestDownload(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tTransferData(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tRequestTransferExit(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tEcuReset(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tControlDTCSetting(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tClearDiagnosticInformation(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tDiagnosticSessionControl(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tSecurityAccess(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tReadDataByIdentifier(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tWriteDataByIdentifier(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tCommunicationControl(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tRoutineControl(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern Std_ReturnType SwcServiceDcm_tTesterPresent(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern void Dcm_Dsp_ReadDTCInfo_Ini(void);
extern void Dcm_Dsp_RequestDownload_Ini(void);
extern void Dcm_Dsp_TransferDataIni(void);
extern void Dcm_Dsp_RequestTransferExit_Ini(void);
extern void Dcm_Dsp_EcuReset_Ini(void);
extern void Dcm_Dsp_CDTCSIni(void);
extern void Dcm_Dsp_DscIni(void);
extern void Dcm_Dsp_SecaIni(void);
extern void Dcm_Dsp_RdbiIni(void);
extern void Dcm_Dcm_WDBIInit(void);
extern void Dcm_Dsp_RC_Ini(void);
extern Std_ReturnType DcmAppl_UserServiceModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint8 Sid_u8);
extern Std_ReturnType DcmAppl_RequestSeedLevel3ModeRuleCheck(Dcm_NegativeResponseCodeType * Nrc_u8, uint8 Sid_u8, uint8 Subfunc_u8);
extern Std_ReturnType DcmAppl_UserSubServiceModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint8 Sid_u8,uint8 Subfunc_u8);
extern Std_ReturnType Dcm_Bootloader_ID_UserSpecificCheck(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 did_u16,Dcm_Direction_t dataDirection_en);
extern Std_ReturnType Dcm_Vin_UserSpecificCheck(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 did_u16, Dcm_Direction_t dataDirection_en);
extern Std_ReturnType Dcm_Programming_Date_UserSpecificCheck(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 did_u16, Dcm_Direction_t dataDirection_en);
extern Std_ReturnType DcmAppl_UserDIDModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 did_u16,Dcm_Direction_t dataDirection_en);
extern Std_ReturnType DcmAppl_UserRIDModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 rid_u16, uint8 subfunction_u8);
extern Std_ReturnType DcmAppl_UserCommCtrlReEnableModeRuleService(void);
extern Std_ReturnType DcmAppl_UserDTCSettingEnableModeRuleService(void);
extern void DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_SesCtrlType SessionMode);
extern void DcmAppl_Switch_DcmExecuteDscReset(uint8 SessionLevel_u8);
extern void DcmAppl_Switch_DcmEcuReset(uint8 ResetMode);
extern void DcmAppl_Switch_DcmExecuteReset(void);
extern void DcmAppl_Switch_DcmExecuteEcuReset(uint8 ResetType_u8);
extern void DcmAppl_Switch_DcmBootLoaderReset(void);
extern void DcmAppl_Switch_DcmSysSupplierReset(void);
extern void DcmAppl_Switch_DcmDriveToDriveReset(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

