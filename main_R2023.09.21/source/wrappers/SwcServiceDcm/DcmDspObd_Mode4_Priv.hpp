

#ifndef DCMDSPOBD_MODE4_PRIV_H
#define DCMDSPOBD_MODE4_PRIV_H

#if(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)

#define DCM_OBDMODE04_REQ_LEN        0x00u

typedef enum{
    DCM_DSP_MODE04_UNINIT
   ,   DCM_DSP_MODE04_INIT
   ,   DCM_DSP_MODE04_CLEAR
}Dcm_DspObdMode04Type_ten;

#endif

#endif

