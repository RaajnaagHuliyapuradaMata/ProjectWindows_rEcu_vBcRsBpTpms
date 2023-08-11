#include "CanIf_Prv.h"

#if (CANIF_SET_BAUDRATE_API == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId,
        const uint16 BaudRateConfigID){
    Std_ReturnType retVal_en = E_NOT_OK;
    const CanIf_Cfg_CtrlConfig_tst * lCtrlConfig_pst;
    uint8 lCtrlCustId_u8;
    CANIF_DET_REPORT_ERROR_NOT_OK((FALSE == CanIf_Lok_InitStatus_b), CANIF_SETBAUDRATE_SID, CANIF_E_UNINIT)
    CANIF_DET_REPORT_ERROR_NOT_OK((ControllerId >= CANIF_TOTAL_CTRLS), CANIF_SETBAUDRATE_SID, CANIF_E_PARAM_CONTROLLERID)
    lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
    CANIF_DET_REPORT_ERROR_NOT_OK((lCtrlCustId_u8 == 0xFFu), CANIF_SETBAUDRATE_SID, CANIF_E_PARAM_CONTROLLERID)
    lCtrlConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + lCtrlCustId_u8;
    retVal_en = Can_SetBaudrate((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), BaudRateConfigID);

    return(retVal_en);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"
#endif

