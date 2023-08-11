

#ifndef PDUR_CFG_SYMBOLICNAMES_H
#define PDUR_CFG_SYMBOLICNAMES_H

#define PDUR_VARIANT_PRE_COMPILE    (0)

#define PDUR_VARIANT_POSTBUILD_LOADABLE    (1)

#if !defined(PDUR_CONFIGURATION_VARIANT)
#define PDUR_CONFIGURATION_VARIANT    PDUR_VARIANT_PRE_COMPILE
#endif

#define PduRConf_PduRSrcPdu_BCM_PowerMode_Can_Network_0_CANNODE_0_CanIf2PduR    0

#define PduRConf_PduRSrcPdu_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0_CanTp2PduR    0
#define PduRConf_PduRDestPdu_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0_PduR2Dcm  0

#define PduRConf_PduRSrcPdu_CGW_EPOCHTime_Can_Network_0_CANNODE_0_CanIf2PduR    1

#define PduRConf_PduRSrcPdu_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0_CanIf2PduR    2

#define PduRConf_PduRSrcPdu_CGW_ODO_Can_Network_0_CANNODE_0_CanIf2PduR    3

#define PduRConf_PduRSrcPdu_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0_CanIf2PduR    4

#define PduRConf_PduRSrcPdu_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0_CanTp2PduR    1
#define PduRConf_PduRDestPdu_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0_PduR2Dcm  1

#define PduRConf_PduRSrcPdu_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0_CanIf2PduR    5

#define PduRConf_PduRSrcPdu_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0_CanIf2PduR    6

#define PduRConf_PduRSrcPdu_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0_CanIf2PduR    7

#define PduRConf_PduRSrcPdu_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0_CanIf2PduR    8

#define PduRConf_PduRSrcPdu_CGW_VehicleSpeed_Can_Network_0_CANNODE_0_CanIf2PduR    9

#define PduRConf_PduRSrcPdu_RdcData_TPMS_Can_Network_0_CANNODE_0_CanIf2PduR    10

#define PduRConf_PduRSrcPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_Com2PduR    0
#define PduRConf_PduRDestPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_PduR2CanIf  0

#define PduRConf_PduRSrcPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_Com2PduR    1
#define PduRConf_PduRDestPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_PduR2CanIf  1

#define PduRConf_PduRSrcPdu_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_Dcm2PduR    0
#define PduRConf_PduRDestPdu_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_PduR2CanTp  0

#define PduRConf_PduRSrcPdu_TPMS_Status_Can_Network_0_CANNODE_0_Com2PduR    2
#define PduRConf_PduRDestPdu_TPMS_Status_Can_Network_0_CANNODE_0_PduR2CanIf  2

#define PduRConf_PduRSrcPdu_TPMS_TirePT_Can_Network_0_CANNODE_0_Com2PduR    3
#define PduRConf_PduRDestPdu_TPMS_TirePT_Can_Network_0_CANNODE_0_PduR2CanIf  3

#endif
