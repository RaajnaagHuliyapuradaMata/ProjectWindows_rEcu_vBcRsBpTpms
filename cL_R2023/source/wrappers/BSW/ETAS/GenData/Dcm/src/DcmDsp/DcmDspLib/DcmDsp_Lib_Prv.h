

#ifndef DCMDSP_LIB_PRV_H
#define DCMDSP_LIB_PRV_H

#include "DcmCore_DslDsd_Inf.h"
#include "Dem.h"

LOCAL_INLINE uint8 Dcm_Lok_GetDemClientId(boolean Context)
{
    uint8 DemClientID_u8;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    DemClientID_u8 = (Context == DCM_UDSCONTEXT)?
                      Dcm_Dsld_Conf_cs.protocol_table_pcs[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].demclientid:
                      Dcm_Dsld_Conf_cs.protocol_table_pcs[Dcm_OBDGlobal_st.idxCurrentProtocol_u8].demclientid;
#else
    DemClientID_u8 = Dcm_Dsld_Conf_cs.protocol_table_pcs[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].demclientid;
    (void) Context;
#endif
    return DemClientID_u8;
}

LOCAL_INLINE Dcm_NegativeResponseCodeType Dcm_Lok_SetErrorCodeForDemOperation(Std_ReturnType Result)
{
    Dcm_NegativeResponseCodeType dataNegRespCode_u8 ;

    switch(Result)
    {
        case E_NOT_OK:
        case DEM_WRONG_DTC:
        case DEM_WRONG_DTCORIGIN:
             dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
             break;
        case DEM_CLEAR_MEMORY_ERROR:
             dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
             break;
        default:
            dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            break;
    }
    return dataNegRespCode_u8;
}

#endif
