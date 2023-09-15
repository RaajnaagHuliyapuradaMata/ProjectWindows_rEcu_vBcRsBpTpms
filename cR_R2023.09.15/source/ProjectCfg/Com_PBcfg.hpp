#ifndef COM_PBCFG_H
#define COM_PBCFG_H

#define COM_NUM_RX_SIGNALS        54u
#define COM_NUM_TX_SIGNALS        43u
#define COM_NUM_TX_IPDU         5u
#define COM_NUM_RX_IPDU         9u
#define COM_NUM_GWSRC_SIGNALS  0u
#define COM_NUM_GWSRC_GRPSIGNALS  0u
#define COM_NUM_GWSRC_IPDUS     0u
#define COM_NUM_GRPSIG_NOGW     0u
#define COM_NUM_IPDUS_IN_LAST_IPDUGRP 1u
#define COM_UPDATE_MAX      0xFF

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
extern VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_IpduBuf_TPMS_Software_ID_TPM_Can_Network_CANNODE_0[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
extern VAR(uint8,COM_VAR) Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,COM_VAR) Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
extern VAR(uint8,COM_VAR) Com_SigType_u8[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.hpp"
extern VAR(uint16,COM_VAR) Com_SigType_u16[];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.hpp"

#endif
