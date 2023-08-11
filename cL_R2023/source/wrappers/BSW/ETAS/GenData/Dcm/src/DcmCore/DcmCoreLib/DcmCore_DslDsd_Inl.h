

#ifndef DCMCORE_DSLDSD_INL_H
#define DCMCORE_DSLDSD_INL_H

LOCAL_INLINE void Dcm_Lok_ReloadS3Timer (void);
LOCAL_INLINE void Dcm_Lok_ReloadS3Timer (void)
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

LOCAL_INLINE Std_ReturnType Dcm_StartProtocol(Dcm_ProtocolType ProtocolID);
LOCAL_INLINE void Dcm_StopProtocol(Dcm_ProtocolType ProtocolID);

LOCAL_INLINE  Std_ReturnType Dcm_StartProtocol(Dcm_ProtocolType ProtocolID)
{
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    uint32_least idxIndex_qu32;
#endif
    Std_ReturnType dataReturnType_u8;

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

LOCAL_INLINE  void Dcm_StopProtocol(Dcm_ProtocolType ProtocolID)
{
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    uint32_least idxIndex_qu32;
#endif

    (void)DcmAppl_DcmStopProtocol(ProtocolID);

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS!=0))

    for(idxIndex_qu32 =0x00 ; idxIndex_qu32<Rte_NPorts_CallbackDCMRequestServices_R() ; idxIndex_qu32++)
    {
        (void)((Rte_Ports_CallbackDCMRequestServices_R())[idxIndex_qu32].Call_StopProtocol)(ProtocolID);
    }
#endif
}

LOCAL_INLINE Std_ReturnType Dcm_SesCtrlChangeIndication(
        Dcm_SesCtrlType dataSesCtrlTypeOld_u8,
        Dcm_SesCtrlType dataSesCtrlTypeNew_u8
);

LOCAL_INLINE Std_ReturnType Dcm_SesCtrlChangeIndication(
        Dcm_SesCtrlType dataSesCtrlTypeOld_u8,
        Dcm_SesCtrlType dataSesCtrlTypeNew_u8
)
{

    DcmAppl_DcmSesCtrlChangeIndication(dataSesCtrlTypeOld_u8,dataSesCtrlTypeNew_u8);
    return(E_OK);
}

LOCAL_INLINE Std_ReturnType Dcm_ConfirmationRespPend(
        Dcm_ConfirmationStatusType status
);
LOCAL_INLINE Std_ReturnType Dcm_ConfirmationRespPend(
        Dcm_ConfirmationStatusType status
)
{

    DcmAppl_ConfirmationRespPend(status);
    return(E_OK);
}

#endif

