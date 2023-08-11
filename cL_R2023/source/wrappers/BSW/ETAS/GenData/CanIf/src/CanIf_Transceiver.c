

#include "CanIf_Prv.h"
#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#include "CanTrcv.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId,
        CanTrcv_TrcvModeType TransceiverMode)
{

    Std_ReturnType Status_t;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_TRCV_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_SET_TRCV_MODE_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK(((TransceiverMode!=CANTRCV_TRCVMODE_NORMAL)&&(TransceiverMode!=CANTRCV_TRCVMODE_SLEEP)&&(TransceiverMode!=CANTRCV_TRCVMODE_STANDBY)), CANIF_SET_TRCV_MODE_SID, CANIF_E_PARAM_TRCVMODE)

    Status_t = CanTrcv_SetOpMode(TransceiverId,TransceiverMode);

     return (Status_t);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_GetTrcvMode(CanTrcv_TrcvModeType * TransceiverModePtr,
                                       uint8 TransceiverId)

{

    Std_ReturnType Status_t;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_TRCV_MODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_GET_TRCV_MODE_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK((TransceiverModePtr== NULL_PTR), CANIF_GET_TRCV_MODE_SID, CANIF_E_PARAM_POINTER)

    Status_t =CanTrcv_GetOpMode(TransceiverId, TransceiverModePtr);

    return (Status_t);
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_GetTrcvWakeupReason( uint8 TransceiverId,
        CanTrcv_TrcvWakeupReasonType * TrcvWuReasonPtr)
{

    Std_ReturnType Status_t;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_GET_TRCV_WUMODE_REASON_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_GET_TRCV_WUMODE_REASON_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK((TrcvWuReasonPtr== NULL_PTR), CANIF_GET_TRCV_WUMODE_REASON_SID, CANIF_E_PARAM_POINTER)

    Status_t =CanTrcv_GetBusWuReason(TransceiverId,TrcvWuReasonPtr);

    return (Status_t);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
Std_ReturnType CanIf_SetTrcvWakeupMode(uint8 TransceiverId,
        CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{

    Std_ReturnType Status_t;

    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SET_TRCV_WAKEUPMODE_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_NOT_OK(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_SET_TRCV_WAKEUPMODE_SID, CANIF_E_PARAM_TRCV)

    CANIF_DET_REPORT_ERROR_NOT_OK(((TrcvWakeupMode!=CANTRCV_WUMODE_ENABLE)&&(TrcvWakeupMode!=CANTRCV_WUMODE_DISABLE)&&(TrcvWakeupMode!=CANTRCV_WUMODE_CLEAR)), CANIF_SET_TRCV_WAKEUPMODE_SID, CANIF_E_PARAM_TRCVWAKEUPMODE)

    Status_t =CanTrcv_SetWakeupMode(TransceiverId, TrcvWakeupMode);

    return (Status_t);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"
void CanIf_TrcvModeIndication(uint8 TransceiverId,
        CanTrcv_TrcvModeType TransceiverMode)
{

    const CanIf_CallbackFuncType * CallBackPtr_Temp;

    CallBackPtr_Temp = &CanIf_Callback;

    CANIF_DET_REPORT_ERROR_VOID_RET((FALSE == CanIf_Lok_InitStatus_b), CANIF_TRCVMODEINDICATION_SID, CANIF_E_UNINIT)

    CANIF_DET_REPORT_ERROR_VOID_RET(TransceiverId >=CANIF_CFG_NUM_TRCVS, CANIF_TRCVMODEINDICATION_SID, CANIF_E_PARAM_TRCV)

    if(NULL_PTR != CallBackPtr_Temp->User_TransceiverModeIndication)
    {
        CallBackPtr_Temp->User_TransceiverModeIndication(TransceiverId, TransceiverMode);
    }
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

