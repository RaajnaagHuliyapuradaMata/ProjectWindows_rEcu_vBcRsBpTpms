#pragma once

#define PDUR_VARIANT_PRE_COMPILE                                                     (0)
#define PDUR_VARIANT_POSTBUILD_LOADABLE                                              (1)

#define PDUR_CONFIGURATION_VARIANT                              PDUR_VARIANT_PRE_COMPILE

#define PduRConf_PduRSrcPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0_Com2PduR       0
#define PduRConf_PduRDestPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0_PduR2CanIf    0
#define PduRConf_PduRSrcPdu_ApplicationRequest_TPM_Can_Network_CANNODE_0_CanIf2PduR    0
#define PduRConf_PduRSrcPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0_Com2PduR     1
#define PduRConf_PduRDestPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0_PduR2CanIf  1
#define PduRConf_PduRSrcPdu_BCM_peripheralMasterClock_Can_Network_CANNODE_0_CanIf2PduR 1
#define PduRConf_PduRSrcPdu_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR 2
#define PduRConf_PduRSrcPdu_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR  3
#define PduRConf_PduRSrcPdu_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0_CanIf2PduR   4
#define PduRConf_PduRSrcPdu_HMIPressure_TPM_Can_Network_CANNODE_0_Com2PduR             2
#define PduRConf_PduRDestPdu_HMIPressure_TPM_Can_Network_CANNODE_0_PduR2CanIf          2
#define PduRConf_PduRSrcPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_Com2PduR      3
#define PduRConf_PduRDestPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_PduR2CanIf   3
#define PduRConf_PduRSrcPdu_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_Com2PduR        4
#define PduRConf_PduRDestPdu_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_PduR2CanIf     4
#define PduRConf_PduRSrcPdu_RdcData_TPM_Can_Network_CANNODE_0_CanIf2PduR               5
#define PduRConf_PduRSrcPdu_TMM_Status_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR       6
#define CfgSwcServicePduR_PduSrcRxDiagUdsReq_Functional_CanTp2PduR                     0
#define PduRConf_PduRDestPdu_UDS_Rx_Functional_Can_Network_CANNODE_0_PduR2Dcm          0
#define CfgSwcServicePduR_PduSrcRxDiagUdsReq_Physical_CanTp2PduR                       1
#define PduRConf_PduRDestPdu_UDS_Rx_Physical_Can_Network_CANNODE_0_PduR2Dcm            1
#define PduRConf_PduRSrcPdu_UDS_Tx_Physical_Can_Network_CANNODE_0_Phys_Dcm2PduR        0
#define CfgSwcServicePduR_PduDestTxDiagUds_Physical_PduR2CanTp                         0
#define PduRConf_PduRSrcPdu_VehSts_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR           7
#define PduRConf_PduRSrcPdu_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0_CanIf2PduR        8
