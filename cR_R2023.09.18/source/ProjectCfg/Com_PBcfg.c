#include "Std_Types.hpp"

#define COM_DontUseExternalSymbolicNames
#include "Com_Prv.hpp"
#include "Com_Cbk.hpp"
#include "PduR_Com.hpp"
#include "Com_PBcfg.hpp"
#include "Com_PBcfg_InternalId.hpp"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
CONST(Com_Lok_xTxSigCfg_tst ,COM_CONST) Com_Lok_xTxSigCfg_acst[COM_NUM_TX_SIGNALS] = {
      {(uint32)(0uL),0x54,56,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,48,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,40,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,32,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,24,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,16,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,8,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,0,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,48,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,49,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,63,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,62,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,61,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,60,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,56,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,40,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,32,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,16,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,24,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,11,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,15,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,3,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,7,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x6}
   ,  {(uint32)(0uL),0x54,8,3,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,12,3,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,4,3,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,0,3,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,56,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,48,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,40,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,32,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,24,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,16,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,8,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,0,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,56,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,48,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,40,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,32,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,24,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,16,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,8,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
   ,  {(uint32)(0uL),0x54,0,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0,0x0}
};

CONST(Com_Lok_xRxSigCfg_tst ,COM_CONST) Com_Lok_xRxSigCfg_acst[COM_NUM_RX_SIGNALS] = {
      {(uint32)(0uL),56,0,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),48,1,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),40,2,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),32,3,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),24,4,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),16,5,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),8,6,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),0,7,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),45,8,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,0x26,0x28}
   ,  {(uint32)(0x0uL),0,48,5,(Com_IpduIdType)ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,0x8,0x28}
   ,  {(uint32)(0uL),52,9,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),54,10,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),8,11,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),0,12,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),14,13,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),12,14,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),40,0,16,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x22,0x28}
   ,  {(uint32)(0uL),24,1,16,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,0x22,0x28}
   ,  {(uint32)(0uL),8,15,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),0,16,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),14,17,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),40,2,16,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x22,0x28}
   ,  {(uint32)(0uL),12,18,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),24,3,16,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x22,0x28}
   ,  {(uint32)(0uL),52,19,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),54,20,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),8,21,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),0,22,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),12,23,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x26,0x28}
   ,  {(uint32)(0uL),13,24,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x26,0x28}
   ,  {(uint32)(0uL),14,25,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x26,0x28}
   ,  {(uint32)(0uL),56,4,16,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x22,0x28}
   ,  {(uint32)(0uL),15,26,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x26,0x28}
   ,  {(uint32)(0uL),40,27,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),32,28,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),24,29,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),16,30,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),56,31,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),48,32,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),40,33,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),32,34,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),8,35,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),0,36,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),16,37,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),24,38,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,0x0,0x28}
   ,  {(uint32)(0uL),0,39,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),16,40,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_VehSts_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),16,41,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),0,42,8,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),8,43,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),28,44,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),20,45,4,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),30,46,2,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x20,0x28}
   ,  {(uint32)(0uL),27,47,1,(Com_IpduIdType)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,0x26,0x28}
};

static CONST(Com_TransModeInfo ,COM_CONST) Com_ApplicationCyclic_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {1,1,0,0,COM_TXMODE_PERIODIC}
   ,  {1,1,0,0,COM_TXMODE_PERIODIC}
};

static CONST(Com_TransModeInfo ,COM_CONST) Com_HMIPressure_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {100,1,0,0,COM_TXMODE_PERIODIC}
   ,  {100,1,0,0,COM_TXMODE_PERIODIC}
};

static CONST(Com_TransModeInfo ,COM_CONST) Com_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {100,1,0,0,COM_TXMODE_PERIODIC}
   ,  {100,1,0,0,COM_TXMODE_PERIODIC}
};

static CONST(Com_TransModeInfo ,COM_CONST) Com_ApplicationResponse_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {0,1,0,0,COM_TXMODE_DIRECT}
   ,  {0,1,0,0,COM_TXMODE_DIRECT}
};

static CONST(Com_TransModeInfo ,COM_CONST) Com_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {1000, 1, 0, 0, COM_TXMODE_PERIODIC}
   ,  {1000, 1, 0, 0, COM_TXMODE_PERIODIC}
};

CONST(Com_Lok_xTxIpduInfoCfg_tst ,COM_CONST) Com_Lok_xTxIpduCfg_acst[COM_NUM_TX_IPDU] = {
      {Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0, Com_ApplicationCyclic_TPM_Can_Network_CANNODE_0_TransModeInfo, &Com_IPdu_Callout_ApplicationCyclic_TPM, NULL_PTR, 8, 1, 0, 8, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0_Com2PduR, (Com_TxIntSignalIdType)ComSignal_Internal_AppCyclic_7, 0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0, Com_HMIPressure_TPM_Can_Network_CANNODE_0_TransModeInfo, &Com_IPdu_Callout_HMIPressure_TPM, NULL_PTR, 8, 100, 0, 19, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_HMIPressure_TPM_Can_Network_CANNODE_0_Com2PduR, (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_LOCATE_Status, 0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0, Com_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_TransModeInfo, &Com_IPdu_Callout_HMITempAndRefPress_TPM, NULL_PTR, 8, 100, 0, 8, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_Com2PduR, (Com_TxIntSignalIdType)ComSignal_Internal_TIRE_REF_PRESS_RR, 0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0, Com_ApplicationResponse_TPM_Can_Network_CANNODE_0_TransModeInfo, &Com_IPdu_Callout_ApplicationResponse_TPM, &Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0, 8, 0, 0, 8, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0_Com2PduR, (Com_TxIntSignalIdType)ComSignal_Internal_AppResponse_7, 0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}

   ,  {Com_IpduBuf_TPMS_Software_ID_TPM_Can_Network_CANNODE_0, Com_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_TransModeInfo,
        &Com_IPdu_Callout_TPMS_Software_ID_TPM,
        NULL_PTR,
        8,
        100,
        0,
        19,
        (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_Com2PduR,
        (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_LOCATE_Status,
        0x4000,
        ComMainFunction_Internal_MainFunctionTx,
        0xFF
    }
};

CONST(Com_Lok_xRxIpduInfoCfg_tst ,COM_CONST) Com_Lok_xRxIpduCfg_acst[COM_NUM_RX_IPDU] = {
      {Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0,&Com_IPdu_Callout_ApplicationRequest,8,8,(Com_RxIntSignalIdType)ComSignal_Internal_AppReqCmd_7,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0,&Com_IPdu_Callout_BCM_peripheralMasterClock,8,2,(Com_RxIntSignalIdType)ComSignal_Internal_BCM_peripherialMasterClockValid,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,&Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN,8,8,(Com_RxIntSignalIdType)ComSignal_Internal_ESP_Wheel_Dir_Right_Front,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,&Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN,8,8,(Com_RxIntSignalIdType)ComSignal_Internal_ESP_WSpeed_Rear_Message_Counter,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,&Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped,8,11,(Com_RxIntSignalIdType)ComSignal_Internal_ESP_Wheel_Pulse_Stamped_MC,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0,&Com_IPdu_Callout_RdcData_TPM,8,8,(Com_RxIntSignalIdType)ComSignal_Internal_User_defined_val_5,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,&Com_IPdu_Callout_TMM_Status_BodyLCAN,8,1,(Com_RxIntSignalIdType)ComSignal_Internal_TMM_TempAmb,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0,&Com_IPdu_Callout_VehSts_BodyLCAN,8,1,(Com_RxIntSignalIdType)ComSignal_Internal_VehModCurr,ComMainFunction_Internal_MainFunctionRx,0x0}
   ,  {Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,&Com_IPdu_Callout_VmsStsReq_BodyLCAN,8,7,(Com_RxIntSignalIdType)ComSignal_Internal_VmsStateFdbk,ComMainFunction_Internal_MainFunctionRx,0x0}
};

CONST(Com_Lok_xIpduGrpInfoCfg_tst ,COM_CONST) Com_Lok_xIpduGrpCfg_acst[4] = {
      { 0, 9}
   ,  { 9, 0}
   ,  {13, 0}
   ,  {14, 0}
};

CONST(Com_IpduIdType ,COM_CONST) Com_Lok_xIPduGrp_IpduRefCfg_au8[16] = {
      ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_TMM_Status_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_VehSts_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_TPMS_Software_ID_TPM_Can_Network_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0)
   ,  (COM_NUM_RX_IPDU + (Com_IpduIdType)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0)
};

#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_TPMS_Software_ID_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0[8];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
VAR(Com_TxIpduRamData,COM_VAR)      Com_TxIpduRam_s[COM_NUM_TX_IPDU];
VAR(Com_RxIpduRamData,COM_VAR)      Com_RxIpduRam_s[COM_NUM_RX_IPDU];
VAR(Com_TxSignalFlagType,COM_VAR)   Com_TxSignalFlag[COM_NUM_TX_SIGNALS];
VAR(Com_RxSignalFlagType,COM_VAR)   Com_RxSignalFlag[COM_NUM_RX_SIGNALS];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
VAR(uint8,COM_VAR)    Com_IpduCounter_s[COM_NUM_TX_IPDU + COM_NUM_RX_IPDU];
VAR(uint8,COM_VAR)    Com_IpduCounter_DM[COM_NUM_RX_IPDU];
VAR(uint8,COM_VAR) Com_SigType_u8[53];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.hpp"
VAR(uint16,COM_VAR) Com_SigType_u16[5];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.hpp"

#define Com_SigType_u32          ( NULL_PTR )


#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
CONST(Com_Lok_xRxRamBuf_tst, COM_CONST) Com_Lok_xRxRamBuf_acst[1u] = {
   {
         (P2VAR(uint8,  TYPEDEF, COM_APPL_DATA)) Com_SigType_u8
      ,  (P2VAR(uint16, TYPEDEF, COM_APPL_DATA)) Com_SigType_u16
      ,  (P2VAR(uint32, TYPEDEF, COM_APPL_DATA)) Com_SigType_u32
   }
};

CONST(Com_MainFunctionCfgType, COM_CONST) Com_MainFunctionCfg[COM_NUM_OF_MAINFUNCTION] = {
      {0u,9u,10u}
   ,  {0u,5u,10u}
};
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

