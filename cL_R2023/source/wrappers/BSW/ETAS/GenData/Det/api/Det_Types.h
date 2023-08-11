

#ifndef DET_TYPES_H
#define DET_TYPES_H

#include "Std_Types.h"
#include "Rte_Det_Type.h"

#define DET_APIID_INIT                  0x00u
#define DET_APIID_REPORTERROR           0x01u
#define DET_APIID_START                 0x02u
#define DET_APIID_GETVERSIONINFO        0x03u
#define DET_APIID_REPORTRUNTIMEERROR    0x04u
#define DET_APIID_REPORTTRANSIENTFAULT  0x05u
#define DET_APIID_GETLASTBUFFERINDEX    0x06u
#define DET_APIID_GETBUFFERENTRY        0x07u

#define DET_E_PARAM_POINTER     0x01u
#define DET_E_CANNOT_REPORT     0x01u
#define DET_E_WRONG_MODULE      0x02u
#define DET_E_WRONG_INSTANCE    0x03u
#define DET_E_WRONG_API         0x04u
#define DET_E_WRONG_ERROR       0x05u
#define DET_E_UNAVAILABLE       0x01u

typedef uint16 Det_BufferIndexType;

typedef struct{
    uint8 Dummy;
} Det_ConfigType;

typedef struct{
    uint16 ModuleId;
    uint8 InstanceId;
    uint8 ApiId;
    uint8 ErrorId;
} Det_ErrorEntryBufferType;

#endif
