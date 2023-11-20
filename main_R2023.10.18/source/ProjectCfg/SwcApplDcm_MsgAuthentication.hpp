#ifndef _DCM_MSG_AUTH_H
#define _DCM_MSG_AUTH_H

#include "Types.hpp"
#include "DcmMsgAuthenticationX.hpp"

#define cSidDiagSessionCtrl   0x10
#define cSidEcuReset          0x11
#define cSidSecAccess         0x27
#define cSidCommControl       0x28
#define cSidTesterPresent     0x3E
#define cSidCtrlDtcSetting    0x85
#define cSidRoutineControl    0x31
#define cSidReadDataByIdent   0x22
#define cSidWriteDataByIdent  0x2E
#define cSubFuncHardReset     0x01
#define cSubFuncSoftReset     0x03
#define cSubFuncHRwoResp      0x40
#define cSubFuncSRwoResp      0x41
#define cSubFuncResUDSTimer   0x4C
#define cDidBootSwId          0xF180u
#define cDidApplSwId          0xF181u
#define cDidCalSwId           0xF182u
#define cDidBootSwFingerprint 0xF183u
#define cDidApplSwFingerprint 0xF184u
#define cDidAppCalFingerprint 0xF185u
#define cDidActiveSession     0xF186u
#define cDidSerialNumber      0xF18Cu
#define cDidVin               0xF190u
#define cDidRivianHwPN        0xF191u
#define cDidProgImgBM         0xF010u
#define cDidProgImgBL         0xF011u
#define cDidProgImgBLUP       0xF012u
#define cDidProgImgRAMUP      0xF013u
#define cDidProgImgAPP1       0xF014u
#define cDidProgImgAPP2       0xF015u
#define cDidProgImgCAL        0xF016u
#define cDidProgImgRAMAPP     0xF019u
#define cDidKeyGenCounters    0xF017u
#define cDidManufSuppMode     0xF018u
#define cDidCompAndSwType     0x0101u
#define cDidGenealVerNumber   0xF110u
#define cDidBoardPartNumber   0xF112u
#define cDidBoardSerNumber    0xF113u
#define cDidGenealCrc         0xF116u
#define cDidGenealFull        0xF117u
#define cDidCalVersionNumber  0xF118u
#define cDidCalCrc            0xF119u
#define cDidCalBlock          0xF11Au
#define cDidEepBlockStatus    0xF11Bu
#define cDidAuxId             0xF11Cu
#define cDidModeId            0xF11Du
#define cRidSelfTest          0xF200u
#define cRidKeyExchange       0x0207u
#define NO_OF_SID     4
#define NO_OF_DID_RID 8

static boolean DcmHashExist(uint8 ucSid, uint16 ushDidRid, uint32 ulServiceLength);
static boolean DcmAuthenticationNeeded(uint8 ucSid, uint16 ushDidRid);
static boolean DcmKeyExist(uint8* aucKey, uint8 ucLength);
static boolean DcmGetSubFunctionFromMessageBuffer(uint8 ucSID, const uint8* aucMessage, uint16* ushSubFunc);

#endif
