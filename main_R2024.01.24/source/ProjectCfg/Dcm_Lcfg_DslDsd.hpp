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
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tTesterPresent(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tDiagnosticSessionControl(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tSecurityAccess(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tWriteDataByIdentifier(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tReadDataByIdentifier(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tEcuReset(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tRoutineControl(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tRequestDownload(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tTransferData(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tRequestTransferExit(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tCommunicationControl(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tReadDTCInformation(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tClearDiagnosticInformation(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tControlDTCSetting(VAR( Dcm_SrvOpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(void,DCM_CODE) Dcm_Dsp_DscIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_SecaIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dcm_WDBIInit(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_RdbiIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_EcuReset_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_RC_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_RequestDownload_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_TransferDataIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_RequestTransferExit_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_CCIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_ReadDTCInfo_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_CDIIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_CDTCSIni(void);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmAppl_UserServiceModeRuleService(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint8, AUTOMATIC) Sid_u8);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmAppl_UserSubServiceModeRuleService(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint8, AUTOMATIC) Sid_u8,VAR(uint8, AUTOMATIC) Subfunc_u8);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadApplicationId_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadAppSwFingerprint_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadApplicationProgramInformation_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBootloaderId_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBootSwFingerprint_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBootloaderProgramInformation_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadComponentAndSwType_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadAuxId_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadModeId_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadGenealogyVersionNumber_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadGenealogyCrc32_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadFullGenealogyBlock_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadApplicationSignature_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadEcuSerialNumber_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBoardSerialNumber_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadEcuPartNumber_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadBoardPartNumber_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ManufacturingSupportMode_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ReadActiveSessionIndicator_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_Vin_UserSpecificCheck(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmAppl_UserDIDModeRuleService(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) did_u16,VAR(Dcm_Direction_t, AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmAppl_UserRIDModeRuleService(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) Nrc_u8, VAR(uint16, AUTOMATIC) rid_u16, VAR(uint8, AUTOMATIC) subfunction_u8);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmAppl_UserCommCtrlReEnableModeRuleService(void);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmExecuteEcuReset(VAR(uint8, AUTOMATIC) ResetType_u8);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmBootLoaderReset(void);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmSysSupplierReset(void);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

