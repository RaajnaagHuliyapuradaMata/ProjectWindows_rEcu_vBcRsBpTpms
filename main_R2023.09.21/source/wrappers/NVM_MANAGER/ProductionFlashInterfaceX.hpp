#ifndef PRODUCTION_FLASH_INTERFACE_X_H
#define PRODUCTION_FLASH_INTERFACE_X_H

#include "types.hpp"

extern uint8 PRODFLASH_GetApplicationSignature(uint8* ucData);
extern uint8 PRODFLASH_GetAuxId(uint8* ucData);
extern uint8 PRODFLASH_GetComponentId(uint8* ucData);
extern uint8 PRODFLASH_GetCustomerEcuPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetCustomerEcuSerialNumber(uint8* ucData);
extern uint8 PRODFLASH_GetCustomerHwPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetEcuProgramFingerprintApplication(uint8* ucData);
extern uint8 PRODFLASH_GetEcuProgramFingerprintBootloader(uint8* ucData);
extern uint8 PRODFLASH_GetEolCheckerByte(uint8* ucData);
extern uint8 PRODFLASH_GetGenealogyCrc32(uint8* ucData);
extern uint8 PRODFLASH_GetGenealogyVersion(uint8* ucData);
extern uint8 PRODFLASH_GetManufacturingSupportMode(uint8* ucData);
extern uint8 PRODFLASH_GetModeId(uint8* ucData);
extern uint8 PRODFLASH_GetPcbaId(uint8* ucData);
extern uint8 PRODFLASH_GetRivianBoardPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetRivianBoardSerialNumber(uint8* ucData);
extern uint8 PRODFLASH_GetRivianEcuPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetRivianEcuSerialNumber(uint8* ucData);
extern uint8 PRODFLASH_GetVin(uint8* ucData);
extern uint8* PRODFLASH_GetGenealogyBlockStartAddress(void);
extern void PRODFLASH_PutApplicationChecksum(const uint8* ucData);
extern void PRODFLASH_PutEolCheckerByte(const uint8* ucData);
extern void PRODFLASH_PutManufacturingSupportMode(const uint8* ucData);
extern void PRODFLASH_PutRivianEcuPartNumber(const uint8* ucData);
extern void PRODFLASH_PutVin(const uint8* ucData);

#endif //PRODUCTION_FLASH_INTERFACE_X_H