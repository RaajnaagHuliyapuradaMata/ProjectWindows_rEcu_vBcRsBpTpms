#ifndef DCMCORE_DSLDSD_INL_H
#define DCMCORE_DSLDSD_INL_H

LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Lok_ReloadS3Timer (void){
    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, DCM_CFG_S3MAX_TIME,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_StopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);

LOCAL_INLINE  FUNC(Std_ReturnType,DCM_CODE) Dcm_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
   VAR(Std_ReturnType,AUTOMATIC) dataReturnType_u8;
    dataReturnType_u8 = DcmAppl_DcmStartProtocol(ProtocolID);
    return(dataReturnType_u8);
}

LOCAL_INLINE  FUNC(void,DCM_CODE) Dcm_StopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
    (void)DcmAppl_DcmStopProtocol(ProtocolID);
}

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SesCtrlChangeIndication(
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeOld_u8
   ,     VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeNew_u8
);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SesCtrlChangeIndication(
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeOld_u8
   ,     VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeNew_u8
){
   return E_OK;
}

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ConfirmationRespPend(
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ConfirmationRespPend(
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
)
{
    return(E_OK);
}

#endif

