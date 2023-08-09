

#ifndef PRODUCTION_FLASH_INTERFACE_H
#define PRODUCTION_FLASH_INTERFACE_H

#include "ProductionFlashInterfaceX.h"

#define DCM__PRODUCTION_DATA_FLASH_SIZE         (2048U)
#define DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE   (64U)

//------- Fixed area (only change if you want to have trouble with BHSENS production line) -----------
#define DCM__PRODUCTION_DATA_INDEX_1_SIZE       (16U)   //to be filled with 0xff
#define DCM__PRODUCTION_DATA_INDEX_2_SIZE       (10U)   //Customer HW part number 433
#define DCM__PRODUCTION_DATA_INDEX_3_SIZE       (10U)   //Customer HW part number 315
#define DCM__PRODUCTION_DATA_INDEX_4_SIZE       (3U)    //Huf specific HW ident number 433
#define DCM__PRODUCTION_DATA_INDEX_5_SIZE       (3U)    //Huf specific HW ident number 315
#define DCM__PRODUCTION_DATA_INDEX_6_SIZE       (3U)    //Hardware version info
#define DCM__PRODUCTION_DATA_INDEX_7_SIZE       (10U)   //Customer LU Sachnummer 433 (Daimler)
#define DCM__PRODUCTION_DATA_INDEX_8_SIZE       (10U)   //Customer LU Sachnummer 315 (Daimler)
#define DCM__PRODUCTION_DATA_INDEX_9_SIZE       (2U)    //Supplier number
#define DCM__PRODUCTION_DATA_INDEX_10_SIZE      (6U)    //Production day
#define DCM__PRODUCTION_DATA_INDEX_11_SIZE      (9U)    //Customer ECU serial number                      82 Bytes
//------- Rivian specific area -----------------------------------------------------------------------
#define DCM__PRODUCTION_DATA_INDEX_12_SIZE      (20U)   //Rivian: APPL SW Fingerprint Tester serial number
#define DCM__PRODUCTION_DATA_INDEX_13_SIZE      (3U)    //Rivian: APPL SW Fingerprint Programming date
#define DCM__PRODUCTION_DATA_INDEX_14_SIZE      (20U)   //Rivian: BL Fingerprint Tester serial number
#define DCM__PRODUCTION_DATA_INDEX_15_SIZE      (3U)    //Rivian: BL Fingerprint Programming date
#define DCM__PRODUCTION_DATA_INDEX_16_SIZE      (17U)   //Rivian: VIN
#define DCM__PRODUCTION_DATA_INDEX_17_SIZE      (1U)    //Rivian: Manufacturing Support Mode              64 Bytes
                                                        //--- Genealogy Block start ---
#define DCM__PRODUCTION_DATA_INDEX_18_SIZE      (1U)    //Rivian: Genealogy Version
#define DCM__PRODUCTION_DATA_INDEX_19_SIZE      (2U)    //Rivian: Component ID
#define DCM__PRODUCTION_DATA_INDEX_20_SIZE      (1U)    //Rivian: PCBA ID
#define DCM__PRODUCTION_DATA_INDEX_21_SIZE      (1U)    //Rivian: Aux ID
#define DCM__PRODUCTION_DATA_INDEX_22_SIZE      (2U)    //Rivian: Mode ID
#define DCM__PRODUCTION_DATA_INDEX_23_SIZE      (35U)   //Rivian: Board part number
#define DCM__PRODUCTION_DATA_INDEX_24_SIZE      (18U)   //Rivian: Board Serial number
#define DCM__PRODUCTION_DATA_INDEX_25_SIZE      (35U)   //Rivian: ECU part number
#define DCM__PRODUCTION_DATA_INDEX_26_SIZE      (18U)   //Rivian: ECU serial number
#define DCM__PRODUCTION_DATA_INDEX_27_SIZE      (16U)   //Rivian: Application Signature
#define DCM__PRODUCTION_DATA_INDEX_28_SIZE      (4U)    //Rivian: Genealogy CRC32                         133 Bytes
                                                        //--- Genealogy Block end ---
#define DCM__PRODUCTION_DATA_INDEX_29_SIZE      (1U)    //BHSENS EOL Checker Byte
#define DCM__PRODUCTION_DATA_INDEX_30_SIZE      (40)    //Free (until end of flash block 4)
#define DCM__PRODUCTION_DATA_INDEX_31_SIZE      (2U)    //copy of application checksum (Adlatus can read this)
#define DCM__PRODUCTION_DATA_INDEX_32_SIZE      (1662)  //Free
//------- iTac serial number -------------------------------------------------------------------------
#define DCM__PRODUCTION_DATA_INDEX_33_SIZE      (16U)   //iTac Number written by line programmer "itac"
//------- Unused -------------------------------------------------------------------------------------
#define DCM__PRODUCTION_DATA_INDEX_34_SIZE      (48U)   //Free until start of FEE Blocks

#define PROD_DATA                               __attribute__ ((section (".production_data")))

typedef union
{
  uint8 AU8_Production_Data_Array[DCM__PRODUCTION_DATA_FLASH_SIZE];
  struct
  {
    uint8 AU8_Index1_Reserved[DCM__PRODUCTION_DATA_INDEX_1_SIZE];
    uint8 AU8_Index2_CustomerHwPartNumber433[DCM__PRODUCTION_DATA_INDEX_2_SIZE];
    uint8 AU8_Index3_CustomerHwPartNumber315[DCM__PRODUCTION_DATA_INDEX_3_SIZE];
    uint8 AU8_Index4_HufSpecificHw433[DCM__PRODUCTION_DATA_INDEX_4_SIZE];
    uint8 AU8_Index5_HufSpecificHw315[DCM__PRODUCTION_DATA_INDEX_5_SIZE];
    uint8 AU8_Index6_HardwareVersionInfo[DCM__PRODUCTION_DATA_INDEX_6_SIZE];
    uint8 AU8_Index7_CustomerPartNumber433[DCM__PRODUCTION_DATA_INDEX_7_SIZE];
    uint8 AU8_Index8_CustomerPartNumber315[DCM__PRODUCTION_DATA_INDEX_8_SIZE];
    uint8 AU8_Index9_SupplierNumber[DCM__PRODUCTION_DATA_INDEX_9_SIZE];
    uint8 AU8_Index10_ProductionDay[DCM__PRODUCTION_DATA_INDEX_10_SIZE];
    uint8 AU8_Index11_CustomerECUSerialNumber[DCM__PRODUCTION_DATA_INDEX_11_SIZE];
    uint8 AU8_Index12_RivianApplSwFpTesterSerialNo[DCM__PRODUCTION_DATA_INDEX_12_SIZE];
    uint8 AU8_Index13_RivianApplSwFpProgrammingDate[DCM__PRODUCTION_DATA_INDEX_13_SIZE];
    uint8 AU8_Index14_RivianBlFpTesterSerialNo[DCM__PRODUCTION_DATA_INDEX_14_SIZE];
    uint8 AU8_Index15_RivianBlFpProgrammingDate[DCM__PRODUCTION_DATA_INDEX_15_SIZE];
    uint8 AU8_Index16_RivianVIN[DCM__PRODUCTION_DATA_INDEX_16_SIZE];
    uint8 AU8_Index17_RivianManufSuppMode[DCM__PRODUCTION_DATA_INDEX_17_SIZE];
    uint8 AU8_Index18_RivianGenealogyVersion[DCM__PRODUCTION_DATA_INDEX_18_SIZE];
    uint8 AU8_Index19_RivianComponentId[DCM__PRODUCTION_DATA_INDEX_19_SIZE];
    uint8 AU8_Index20_RivianPcbaId[DCM__PRODUCTION_DATA_INDEX_20_SIZE];
    uint8 AU8_Index21_RivianAuxId[DCM__PRODUCTION_DATA_INDEX_21_SIZE];
    uint8 AU8_Index22_RivianModeId[DCM__PRODUCTION_DATA_INDEX_22_SIZE];
    uint8 AU8_Index23_RivianBoardPartNumber[DCM__PRODUCTION_DATA_INDEX_23_SIZE];
    uint8 AU8_Index24_RivianBoardSerialNumber[DCM__PRODUCTION_DATA_INDEX_24_SIZE];
    uint8 AU8_Index25_RivianEcuPartNumber[DCM__PRODUCTION_DATA_INDEX_25_SIZE];
    uint8 AU8_Index26_RivianEcuSerialNumber[DCM__PRODUCTION_DATA_INDEX_26_SIZE];
    uint8 AU8_Index27_RivianApplicationSignature[DCM__PRODUCTION_DATA_INDEX_27_SIZE];
    uint8 AU8_Index28_RivianGenealogyCrc32[DCM__PRODUCTION_DATA_INDEX_28_SIZE];
    uint8 AU8_Index29_BHSENSEolCheckerByte[DCM__PRODUCTION_DATA_INDEX_29_SIZE];
    uint8 AU8_Index30_Reserved[DCM__PRODUCTION_DATA_INDEX_30_SIZE];
    uint8 AU8_Index31_ApplicationChecksum[DCM__PRODUCTION_DATA_INDEX_31_SIZE];
    uint8 AU8_Index32_Reserved[DCM__PRODUCTION_DATA_INDEX_32_SIZE];
    uint8 AU8_Index33_iTACSerialNumber[DCM__PRODUCTION_DATA_INDEX_33_SIZE];
    uint8 AU8_Index34_Reserved[DCM__PRODUCTION_DATA_INDEX_34_SIZE];
  } Struct_Split_Production_Data;
} Dcm__Union_ProductionData;

typedef enum
{
  DCM__E_RESERVED_1 = 0x00U,                        //"Daimler" block start
  DCM__E_CUSTOMER_HW_PART_NUMBER_433,               //         |
  DCM__E_CUSTOMER_HW_PART_NUMBER_315,               //         |
  DCM__E_HUF_SPECIFIC_HW_NUMBER_433,                //         |
  DCM__E_HUF_SPECIFIC_HW_NUMBER_315,                //         |
  DCM__E_HARDWARE_VERSION_INFO,                     //         |
  DCM__E_CUSTOMER_PART_NUMBER_433,                  //         |
  DCM__E_CUSTOMER_PART_NUMBER_315,                  //         |
  DCM__E_SUPPLIER_NUMBER,                           //         |
  DCM__E_PRODUCTION_DAY,                            //         V
  DCM__E_CUSTOMER_ECU_SERIAL_NUMBER,                //"Daimler" block end
  DCM__E_RIVIAN_APPL_SWFP_TESTER_SERIAL_NO,
  DCM__E_RIVIAN_APPL_SWFP_PROGRAMMING_DATE,
  DCM__E_RIVIAN_BL_SWFP_TESTER_SERIAL_NO,
  DCM__E_RIVIAN_BL_SWFP_PROGRAMMING_DATE,
  DCM__E_RIVIAN_VIN,
  DCM__E_RIVIAN_MANUF_SUPP_MODE,
  DCM__E_RIVIAN_GENEALOGY_VERSION,                  //Genealogy block start
  DCM__E_RIVIAN_COMPONENT_ID,                       //         |
  DCM__E_RIVIAN_PCBA_ID,                            //         |
  DCM__E_RIVIAN_AUX_ID,                             //         |
  DCM__E_RIVIAN_MODE_ID,                            //         |
  DCM__E_RIVIAN_BOARD_PART_NUMBER,                  //         |
  DCM__E_RIVIAN_BOARD_SERIAL_NUMBER,                //         |
  DCM__E_RIVIAN_ECU_PART_NUMBER,                    //         |
  DCM__E_RIVIAN_ECU_SERIAL_NUMBER,                  //         |
  DCM__E_RIVIAN_APPLICATION_SIGNATURE,              //         V
  DCM__E_RIVIAN_GENEALOGY_CRC32,                    //Genealogy block end
  DCM__E_BHSENS_EOL_CHECKER_BYTE,
  DCM__E_RESERVED_2,
  DCM__E_APPLICATION_CHECKSUM,
  DCM__E_RESERVED_3,
  DCM__E_ITAC_SERIAL_NUMBER,
  DCM__E_RESERVED_4
} Dcm__Enum_ProductionDataMembers;

static void PRODFLASH__WriteProductionDataMember(Dcm__Enum_ProductionDataMembers EN_Member, const uint8 *PU8_Data, const uint8 U8_Length);

static uint16 PRODFLASH__GetSizeOfMember(Dcm__Enum_ProductionDataMembers EN_Member);

static uint32 PRODFLASH__GetAddressOfMember(Dcm__Enum_ProductionDataMembers EN_Member);

static uint8 PRODFLASH__GetStartBlockNumber(uint32 U32_AddressOfMember);

static uint8 PRODFLASH__GetEndBlockNumber(uint32 U32_AddressOfMember, uint16 U16_SizeOfMember);

static void PRODFLASH__EraseFlashBlock(uint8 U8_BlockNumber);

static void PRODFLASH__WriteFlashBlock(uint8 U8_BlockNumber, uint8 *PU8_Data);
#endif //PRODUCTION_FLASH_INTERFACE_H