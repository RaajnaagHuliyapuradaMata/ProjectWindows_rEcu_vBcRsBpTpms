#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocol(
   P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol){
   if(ActiveProtocol != NULL_PTR){
      if(FALSE != Dcm_Lok_isProtocolStarted()){
            *(ActiveProtocol) = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8;
        }
        else{
            *(ActiveProtocol) = DCM_NO_ACTIVE_PROTOCOL;
        }
   }
    return(E_OK);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocolRxBufferSize(
   CONSTP2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA) rxBufferLength){
   VAR(Std_ReturnType,AUTOMATIC) bufferSizeStatus = E_NOT_OK;

   if(NULL_PTR != rxBufferLength){
      if(FALSE != Dcm_Lok_isProtocolStarted()){
            *(rxBufferLength) = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_buffer_size_u32;
            bufferSizeStatus = E_OK;
        }
   }
    return (bufferSizeStatus);
}

FUNC(void,DCM_CODE) Dcm_GetActiveServiceTable(
   P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ActiveServiceTable){
   if(NULL_PTR != ActiveServiceTable){
        *(ActiveServiceTable) = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
