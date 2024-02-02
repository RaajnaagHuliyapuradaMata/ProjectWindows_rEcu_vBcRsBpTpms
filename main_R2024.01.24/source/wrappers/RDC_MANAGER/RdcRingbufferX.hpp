#ifndef RDC_RINGBUFFER_X_H
#define RDC_RINGBUFFER_X_H

#include "iTpms_Interface.hpp"

extern void           RdcRb_Init                   (void);
#include "TypesMcalAtaRfd.hpp"
extern void           RdcRb_StoreTelegram          (TypeMcalAtaRfd_stTelegram* pstTelegram, uint32* PU32_Timestamp);
extern void           RdcRb_StoreSimulatedTelegram (tsWS_RxDataIn* tSimulatedTelegram);
extern tsWS_RxDataIn* RdcRb_ReadTelegram           (void);
extern boolean        RdcRb_IsBufferEmpty          (void);

#endif
