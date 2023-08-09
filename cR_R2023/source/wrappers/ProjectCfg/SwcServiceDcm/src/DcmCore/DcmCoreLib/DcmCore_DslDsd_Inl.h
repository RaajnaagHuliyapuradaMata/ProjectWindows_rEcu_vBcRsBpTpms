

#ifndef DCMCORE_DSLDSD_INL_H
#define DCMCORE_DSLDSD_INL_H

LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Lok_ReloadS3Timer (void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Lok_ReloadS3Timer (void)
{

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
    {

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, Dcm_DsldTimer_st.dataTimeoutP3max_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
    }
    else
    {

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, DCM_CFG_S3MAX_TIME,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
    }
#else

    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, DCM_CFG_S3MAX_TIME,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
#endif
}

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_StopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);

LOCAL_INLINE  FUNC(Std_ReturnType,DCM_CODE) Dcm_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    VAR(uint32_least,AUTOMATIC) idxIndex_qu32;
#endif
    VAR(Std_ReturnType,AUTOMATIC) dataReturnType_u8;

    dataReturnType_u8 = DcmAppl_DcmStartProtocol(ProtocolID);

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    if(dataReturnType_u8 == E_OK)
    {

        for(idxIndex_qu32 = 0x00 ; idxIndex_qu32<Rte_NPorts_CallbackDCMRequestServices_R() ; idxIndex_qu32++)
        {
            dataReturnType_u8 =((Rte_Ports_CallbackDCMRequestServices_R())[idxIndex_qu32].Call_StartProtocol)(ProtocolID);

            if(Dcm_IsInfrastructureErrorPresent_b(dataReturnType_u8) != FALSE )
            {
                dataReturnType_u8 = DCM_INFRASTRUCTURE_ERROR;

            }
            else if((dataReturnType_u8 == DCM_E_PROTOCOL_NOT_ALLOWED) || (dataReturnType_u8 == E_NOT_OK))
            {

            }
            else
            {
                dataReturnType_u8 = E_OK;
            }
            if(dataReturnType_u8 != E_OK)
            {
                break;
            }
        }
    }
#endif
    return(dataReturnType_u8);
}

LOCAL_INLINE  FUNC(void,DCM_CODE) Dcm_StopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    VAR(uint32_least,AUTOMATIC) idxIndex_qu32;
#endif

    (void)DcmAppl_DcmStopProtocol(ProtocolID);

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS!=0))

    for(idxIndex_qu32 =0x00 ; idxIndex_qu32<Rte_NPorts_CallbackDCMRequestServices_R() ; idxIndex_qu32++)
    {
        (void)((Rte_Ports_CallbackDCMRequestServices_R())[idxIndex_qu32].Call_StopProtocol)(ProtocolID);
    }
#endif
}

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SesCtrlChangeIndication(
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeOld_u8,
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeNew_u8
);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SesCtrlChangeIndication(
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeOld_u8,
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeNew_u8
)
{

    DcmAppl_DcmSesCtrlChangeIndication(dataSesCtrlTypeOld_u8,dataSesCtrlTypeNew_u8);
    return(E_OK);
}

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ConfirmationRespPend(
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);
LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ConfirmationRespPend(
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
)
{

    DcmAppl_ConfirmationRespPend(status);
    return(E_OK);
}

#endif

