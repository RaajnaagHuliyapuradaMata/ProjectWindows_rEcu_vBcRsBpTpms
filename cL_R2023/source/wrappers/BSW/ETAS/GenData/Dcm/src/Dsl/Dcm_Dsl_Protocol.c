

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType Dcm_GetActiveProtocol(Dcm_ProtocolType * ActiveProtocol)
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

Std_ReturnType Dcm_GetActiveProtocolRxBufferSize(Dcm_MsgLenType * const rxBufferLength)
{
    Std_ReturnType bufferSizeStatus = E_NOT_OK;

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

void Dcm_GetActiveServiceTable (uint8 * ActiveServiceTable)
{
    if(NULL_PTR != ActiveServiceTable)
    {
        *(ActiveServiceTable) = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
    }
}

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

Std_ReturnType Dcm_GetMediumOfActiveConnection(\
        Dcm_DslDsd_MediumType_ten * const ActiveMediumId)
{
    if(ActiveMediumId != NULL_PTR)
    {

        *ActiveMediumId = Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].MediumId;
    }
    return(E_OK);
}

#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
