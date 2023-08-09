

#include "PduR_Prv.h"
#include "PduR_Cfg.h"

#include "PduR_UpTp.h"

#if defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_CANTP_CHANGE_PARAMETER_SUPPORT != 0)
#include "PduR_CanTp.h"
#endif
#if defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT != 0)
#include "PduR_FrTp.h"
#endif

#include "PduR_Dcm.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    return (PduR_rDcmTransmit( (id) , (ptr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmCancelTransmit( VAR(PduIdType,AUTOMATIC) id)
{
    VAR( Std_ReturnType, AUTOMATIC) r;

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)

    PDUR_CHECK_STATE_RET(PDUR_SID_DCMCNCLTX, E_NOT_OK)

    if ( ( id >= PDUR_NR_VALID_DCM_IDS ) || ( PduR_iDcmCancelTransmitFunc(id) == NULL_PTR ) )
    {
        PDUR_REPORT_ERROR(PDUR_SID_DCMCNCLTX, PDUR_E_PDU_ID_INVALID);
        return  E_NOT_OK;
    }
#endif

    r = PduR_iDcmCancelTransmitFunc(id)( PduR_iDcmCancelTransmitID(id) );

    return r;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CHANGE_PARAMETER_SUPPORT) && (PDUR_CHANGE_PARAMETER_SUPPORT != 0)
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmChangeParameter(VAR(PduIdType, AUTOMATIC) id,
                                                    VAR(TPParameterType, AUTOMATIC) parameter,
                                                    VAR(uint16, AUTOMATIC) value)
{

#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION!= STD_OFF)

    PDUR_CONFIG_SINGLE_TPTX_LO(ChangeParameter)(id,parameter,value);

#else
    Std_ReturnType          retval;
    PduR_LowerTpModuleName  lowerModule;
    PduIdType               lowerId;

    retval = E_NOT_OK;

    if ( id < PDUR_NR_VALID_DCM_IDS  )
    {

        lowerModule = PDUR_CHANGEPARAM_SUPPORT[id].loTp;

        lowerId     = PDUR_CHANGEPARAM_SUPPORT[id].loId;

        if(lowerModule == (PduR_LowerTpModuleName)PDUR_CANTP)
        {
            #if defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_CANTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = CanTp_ChangeParameter(lowerId,parameter,value);

            #endif

        }
        else if(lowerModule == (PduR_LowerTpModuleName)PDUR_FRTP)
        {
            #if defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = FrTp_ChangeParameter(lowerId,parameter,value);

            #endif

        }
        else
        {

        }
    }
    else
    {

        PDUR_REPORT_ERROR(PDUR_SID_DCMCHANGEPARAMETER, PDUR_E_PDU_ID_INVALID);
    }

    return retval;
#endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

#if defined(PDUR_CHANGE_PARAMETER_SUPPORT) && (PDUR_CHANGE_PARAMETER_SUPPORT != 0)
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmReadParameter( VAR(PduIdType, AUTOMATIC) id,
                                                          VAR(TPParameterType, AUTOMATIC) parameter,
                                                          P2VAR(uint16, AUTOMATIC, PDUR_APPL_DATA) value)
{
#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION!= STD_OFF)

    return (PDUR_CONFIG_SINGLE_TPTX_LO(ReadParameter)(id,parameter,value));

#else
    Std_ReturnType          retval;
    PduR_LowerTpModuleName  lowerModule;
    PduIdType               lowerId;

    retval      = E_NOT_OK;

    if ( (id < PDUR_NR_VALID_DCM_IDS ) && (value != NULL_PTR))
    {

        lowerModule = PDUR_CHANGEPARAM_SUPPORT[id].loTp;
        lowerId     = PDUR_CHANGEPARAM_SUPPORT[id].loId;

        if(lowerModule == (PduR_LowerTpModuleName)PDUR_CANTP)
        {
            #if defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_CANTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = CanTp_ReadParameter(lowerId,parameter,value);

            #endif

        }
        else if(lowerModule == (PduR_LowerTpModuleName)PDUR_FRTP)
        {
            #if defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = FrTp_ReadParameter(lowerId,parameter,value);

            #endif

        }
        else
        {

        }
    }
    else
    {

        #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
        if(id >= PDUR_NR_VALID_DCM_IDS)
        {
            PDUR_REPORT_ERROR(PDUR_SID_DCMREADPARAMETER, PDUR_E_PDU_ID_INVALID);
        }
        if(value == NULL_PTR)
        {
            PDUR_REPORT_ERROR(PDUR_SID_DCMREADPARAMETER, PDUR_E_NULL_POINTER);
        }
        #endif

    }
    return retval;
#endif

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

