#include "CanTp.h"
#include "PduR_CanTp.h"

#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "CanIf.h"
#if (!defined(CANIF_AR_RELEASE_MAJOR_VERSION) || (CANIF_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANIF_AR_RELEASE_MINOR_VERSION) || (CANIF_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define CANTP_IF_PDU_ID_00000     CanIfConf_CanIfTxPduCfg_TPMS_Diag_Resp_Can_Network_0_CANNODE_0
#define CANTP_IF_FC_PDU_ID_00000  0
#define CANTP_IF_FC_PDU_ID_00001  CanIfConf_CanIfTxPduCfg_TPMS_Diag_Resp_Can_Network_0_CANNODE_0
#define CANTP_PDUR_DEST_ID_00000  PduRConf_PduRDestPdu_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_PduR2CanTp
#define CANTP_PDUR_SRC_ID_00000   PduRConf_PduRSrcPdu_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0_CanTp2PduR
#define CANTP_PDUR_SRC_ID_00001   PduRConf_PduRSrcPdu_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0_CanTp2PduR

#define CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "CanTp_MemMap.h"
static const struct CanTp_RxPduStructType CanTp_RxPdu[2u] = {
    {  0,         2,         NULL_PTR                 },
    {  1,         0,         NULL_PTR                 }
};

static const struct CanTp_TxSduStructType CanTp_TxSdu[1u] = {
    {  0x8,  0x18, 0xF1, 0,    0,    1,     0,     CANTP_IF_PDU_ID_00000, CANTP_PDUR_DEST_ID_00000 }
};

static const struct CanTp_RxSduStructType CanTp_RxSdu[2u] = {
    {  0xC,  0x0,  0,    1,    0,    0,     0,     CANTP_IF_FC_PDU_ID_00000, CANTP_PDUR_SRC_ID_00000  },
    {  0x8,  0xF1, 0,    1,    1,    0,     0,     CANTP_IF_FC_PDU_ID_00001, CANTP_PDUR_SRC_ID_00001  }
};

static const struct CanTp_TimeOutStructType CanTp_TimeOut[2u] = {
{   3,                  75,                 11         },
{   3,                  0,                  15         }
};

static const struct CanTp_ParamStructType CanTp_Param[2u] = {
    {{ 0x64,     0x0,      },     0x0       },
    {{ 0x0,      0x0,      },     0x0       }
};

const Type_CfgSwcServiceCanTp_st CanTp_Config = {
      2
   ,  2
   ,  1
   ,  2
   ,  1
   ,  &CanTp_RxPdu[0]
   ,  &CanTp_TxSdu[0]
   ,  &CanTp_RxSdu[0]
   ,  &CanTp_TimeOut[0]
   ,  &CanTp_Param[0]
};

#define CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "CanTp_MemMap.h"

