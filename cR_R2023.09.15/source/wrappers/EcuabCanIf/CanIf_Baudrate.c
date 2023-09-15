#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#if(CANIF_SET_BAUDRATE_API == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBaudrate(
        VAR(uint8,  AUTOMATIC) ControllerId
   ,  CONST(uint16, AUTOMATIC) BaudRateConfigID
){
       VAR(Std_ReturnType,     AUTOMATIC                 ) retVal_en = E_NOT_OK;
   P2CONST(CanIf_Cfg_CtrlConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst;
   VAR(uint8, AUTOMATIC)          lCtrlCustId_u8;
   lCtrlCustId_u8 = CanIf_Lok_ConfigSet_tpst->CtrlIdTable_Ptr[ControllerId];
   lCtrlConfig_pst  = (CanIf_Lok_ConfigSet_tpst->CanIf_CtrlConfigPtr) + lCtrlCustId_u8;
   retVal_en = Can_SetBaudrate((uint8)(lCtrlConfig_pst->CtrlCanCtrlRef), BaudRateConfigID);
   return(retVal_en);
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

