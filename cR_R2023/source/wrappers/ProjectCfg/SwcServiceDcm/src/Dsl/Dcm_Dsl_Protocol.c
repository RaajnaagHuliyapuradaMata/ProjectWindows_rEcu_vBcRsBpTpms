

#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol)
{
    if(ActiveProtocol != NULL_PTR)
    {
        if(FALSE != Dcm_Lok_isProtocolStarted())
        {
            *(ActiveProtocol) = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8;
        }
        else
        {
            *(ActiveProtocol) = DCM_NO_ACTIVE_PROTOCOL;
        }
    }
    return(E_OK);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocolRxBufferSize(CONSTP2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA) rxBufferLength)
{
    VAR(Std_ReturnType,AUTOMATIC) bufferSizeStatus = E_NOT_OK;

    if(NULL_PTR != rxBufferLength)
    {
        if(FALSE != Dcm_Lok_isProtocolStarted())
        {
            *(rxBufferLength) = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_buffer_size_u32;
            bufferSizeStatus = E_OK;
        }
    }

    return (bufferSizeStatus);
}

FUNC(void,DCM_CODE) Dcm_GetActiveServiceTable (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ActiveServiceTable)
{
    if(NULL_PTR != ActiveServiceTable)
    {
        *(ActiveServiceTable) = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
    }
}

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetMediumOfActiveConnection(\
        CONSTP2VAR(Dcm_DslDsd_MediumType_ten, AUTOMATIC, DCM_APPL_DATA) ActiveMediumId)
{
    if(ActiveMediumId != NULL_PTR)
    {

        *ActiveMediumId = Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].MediumId;
    }
    return(E_OK);
}

#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
