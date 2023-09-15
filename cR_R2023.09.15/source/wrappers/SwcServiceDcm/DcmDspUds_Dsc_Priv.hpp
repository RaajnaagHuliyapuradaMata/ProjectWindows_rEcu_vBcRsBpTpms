

#ifndef DCMDSPUDS_DSC_PRIV_H
#define DCMDSPUDS_DSC_PRIV_H

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

#define DCM_DSP_DSC_REQ_LEN              0x01u

#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
#define DCM_DSP_DSC_RESP_LEN             0x05u
#else
#define DCM_DSP_DSC_RESP_LEN             0x01u
#endif

#define DCM_DSP_DSC_POSITION_SUBFUNC     0x00u

#endif

#endif

