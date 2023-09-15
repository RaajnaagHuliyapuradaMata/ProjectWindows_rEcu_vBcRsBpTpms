# Example linker script for RH850GHS variant F1L.
#
# Copyright ETAS GmbH 2019
#
# Notes:
#  Memory model 'FLASH'
#
#  The memory ranges used in this sample linker script have been configured for
#  use with one variation of the RH850/F1L. This may not be correct for all
#  RH850/F1L devices and so may need modification.
#  
#  History
#  -------
#  Stemmler 2019-05-17
#  Takeover for Rivian
#  Needs adaptation later when bootloader is implemented (check DAI MFA linkerfile as example)
#
#  Stemmler 2019-12-02
#  Rom and Ram defines changed to match RH850/F1L R7F7010133AFP (512K flash, 32K Primary Ram, 32K Retention Ram)
#
#  Stemmler 2020-02-10
#  Move application from 0x0 to 0x20100 like in VECTOR demo application. This is for use with bootloader!
#
#  Stemmler 2020-02-25
#  Added a section for Smart Tester Adlatus (production tester).
#  
#  Stemmler 2021-08-03
#  Added a 16 byte section in RRAM for WUF0 register copy (FBL must fill this on each startup so that Appl can
#  can see the initial reset cause -> after BL CR the FBL starts application always via soft reset, so the WUF0 
#  is overwritten after e.g. wakeup by TAUJ timer.
# ------------------------------------------------------------------------------------------------------------------

# -ETAS-
DEFAULTS {
  heap_reserve = 0
}

MEMORY {
  # Internal FLASH
  iVect             : ORIGIN = 0x00000000, LENGTH = 0x300        
  iBMHeader         : ORIGIN = 0x00000300, LENGTH = 0x60            # Bootmanager header table -> the address of StartFbl() is here!
  iFbl		          : ORIGIN = 0x00000360, LENGTH = 0x20000-0x360-0x100   # Bootloader is located here (RST 11.11.2020: minus 0x100 for FBL descriptor block)
  iFblDescBlock     : ORIGIN = 0x0001FF00, LENGTH = 0x100           # 256 bytes for Rivian Bootloader descriptor block
  
  iApplBMHeaderHdr  : ORIGIN = 0x00020000, LENGTH = 0x100           # Application header table -> Appl start address is here (used by BM to start the appl)
  iAppl             : ORIGIN = 0x00020100, LENGTH = 0x57900         # -RST- use code flash up to address 0x779FF for application code. 0x100 free bytes after this. 
  iApplDescBlock    : ORIGIN = 0x00077B00, LENGTH = 0x100           # -RST- 256 bytes for Rivian application descriptor block  
  iPresencePat      : ORIGIN = 0x00077C00, LENGTH = 0x400           # -RST- FBL uses the last 4 flash blocks from logic block "Application" for the presence patterns
  iAdlatus          : ORIGIN = 0x00078000, LENGTH = 0x7000          # -RST- use code flash from 0x78000 to 0x7efff for Adlatus. 0x1000 free bytes after this.
  iROM_DATA         : ORIGIN = 0xFF200000, LENGTH = 0x800           # -PC- 2k data flash for BH-SENS production data
                                                                        
  # Internal RAM (64 kBytes)
  iFlashDrv   : ORIGIN = 0xFEDF8000, LENGTH = 0x2800  
  iEeprom     : ORIGIN = 0xFEDFA800, LENGTH = 0x00000300
  MAGICFL     : ORIGIN = 0xFEDFAB00, LENGTH = 0x00000010
  iRAM2       : ORIGIN = 0xFEDFAB10, LENGTH = 0x000004F0
  iStack      : ORIGIN = 0xFEDFB000, LENGTH = 0x00001000
  iRAM        : ORIGIN = 0xFEDFC000, LENGTH = 0x0000BC00  # 47 kBytes, this is both normal and retention ram
  RRAM        : ORIGIN = 0xFEE07C00, LENGTH = 0x00000400  # 1024 Bytes retention RAM usage only for standstill monitoring, end at 0xfee08000
  # RRAM        : ORIGIN = 0xFEE07C00, LENGTH = 0x000003F0  # 1008 Bytes retention RAM usage only for standstill monitoring, end at 0xfee08000
  # RRAM_WUF    : ORIGIN = 0xFEE07FF0, LENGTH = 0x00000010  # 16 Bytes for a copy of the Wakeup Factor register (filled by FBL on each startup)
}


SECTIONS {
  #----------------------------------
  # ROM AREA (iROM_0A)
  #----------------------------------
  .FBLBMHEADER                        :>iApplBMHeaderHdr        # Application header table
  .FBLBMHEADERHDR					            :>.                       # Application header table
  .APPLVECT                 align(4)  :>iAppl                   # alternative interrupt vector table position
  .FBLHEADER					                :>.
  .Os_intvect align(16)               :>.                       # use the section names from ETAS OS. Vector remaps the
  .Os_EI_vect align(16)               :>.                       # addresses to defines at the end of this file.
  .startup .: 
  {
    BrsStartup_c0.o(.text)
  } >.
                                                                                                                     
  # START OF CODE AREA #
  .text                     align(4)  :>.                       # program code area
  .Os_primitives            align(4)  :>.                       # RTA-OS code areas
  .Os_text                  align(4)  :>.
  .R_FDL_Text               align(4)  :>.                       # FDL code in ROM (used by MCAL)
  # END OF CODE AREA #
                                                                                                                                        
  # START OF CONST AREA #
  .rozdata                            :>.                       # constant datas in ZDA area
  .robase                   align(4)  :>.                       # initialize textpointer TP for SDA addressing
  .rosdata                  align(4)  :>.                       # constant datas in SDA area
  .rodata                   align(4)  :>.                       # constant datas in normal area
  .Os_rodata                align(4)  :>.                       # RTA-OS Read-only data area
  .R_FDL_Const              align(4)  :>.                       # constant datas for DrvFls
  # END OF CONST AREA 
  
  # The .fixaddr and .fixtype sections contain information needed for Position Independent Data (PID)                                                                                                                                          
  .fixaddr                  align(4)  :>.                       # ghs internal (compiler)
  .fixtype                  align(4)  :>.                       # ghs internal (compiler)
  # The .secinfo section contains information about how to initialize memory when your application loads.  
  # It tells us which sections of RAM need to be zero-initialized and which sections need to be copied from ROM.
  .secinfo                  align(4)  :>.                       # ghs internal (runtime library)
  # Special section that allows communication between the application and the MULTI debugger and/or simulator
  .syscall                  align(4)  :>.                       # ghs internal (linker)
                                                                                                                     
  .ROM.ramcopy              align(4)  ROM(.ramcopy)   :>.       # ROM copy to initialize text in ramcopy area
  .romdata                            ROM(.data)      :>.       # init values for .data (copied to RAM at startup)                  
  .romzdata                           ROM(.zdata)     :>.       # init values for .zdata (copied to RAM at startup)                 
  .romsdata                           ROM(.sdata)     :>.       # init values for .sdata (copied to RAM at startup)                 
  .romtdata                           ROM(.tdata)     :>.       # init values for .tdata (copied to RAM at startup)
  .ROM.Os_data ROM(.Os_data)                          :>.       # RST: const data to init variables RTA-OS Os_data area (copied to RAM at startup)
  .roAPP_METADATA           align(4)  :>iApplDescBlock          # RST: Rivian application descriptor block
  
  #----------------------------------
  # ROM AREA (iROM_1)
  #----------------------------------
  # START OF BH-SENS PRODUCTION DATA AREA # 
  .production_data          align(4)	:>iROM_DATA
  # END OF BH-SENS PRODUCTION DATA AREA #                                                                                                                    
                                                                                                                      
  #----------------------------------
  # RAM
  #----------------------------------
  .ram_start                          :>iFlashDrv               # Start of RAM area of MasterCore
  .FLASHDRV                 align(4)  :>.                       # Space for FlashCode
  .EEPDATA                  align(4)  :>iEeprom                 # Space Dummy EEPROM
  .FBLMAGIC                 align(4)  :>MAGICFL                 # Space for magic flag (Fbl Start feature)
                                                                                                                     
  # START OF NORMAL DATA RAM AREA # 
  .data                     align(4)        :>iRAM              # initialized data 
  .Os_data                  align(4)        :>.                 # RST Test: RTA-OS initialized data area (by startup)

  .R_FDL_Data               align(4)        :>.                 # data for DrvFls
  .bss                      align(4) CLEAR  :>.                 # zero initialized data 
  .Os_bss                   align(4) clear  :>.                 # RST Test: RTA-OS Zero-initialized data area
  .ramcopy                  align(4)        :                   # Initialized code segment in RAM 
  {                                                                                                                   
    *(.RAMCONST)                                                # RAM const
    *(.RAMCODE)                                                 # RAM code 
  } >.                                                                                                                
  # END OF NORMAL DATA RAM AREA 

  # START OF SDA RAM AREA #                                                                                        
  .sda_start                                :>.                 # start of SDA RAM area
  .sdabase               align(4)           :>.                 # initialize globalpointer GP for SDA addressing 
  .sdata                 align(4)           :>.                 # initialized data in SDA area                        
  .sbss                  align(4) CLEAR     :>.                 # zero initialized data in SDA area 
  .sda_end                                  :>.                 # end of SDA RAM area                                    
  # END OF SDA RAM AREA #                                                                                          
                                                                                                                                                                                                                                         
  .zdata                 align(4)                     :>.       # initialized data in ZDA area
  .zbss                  align(4) CLEAR               :>.       # zero initialized data in ZDA area 
  .tdata                 align(4) MAX_SIZE(256)       :>.       # initialized and zero-initialized data in TDA area 
  .heap                  align(4) pad(heap_reserve)   :>.       # RST Test: takeover from Etas linker file
  .stack                 align(4) pad(SIZEOF(iStack)) :>iStack  # definition of stack size
  
  # START OF RETENTION RAM AREA FOR STANDSTILL MONITORING #
  .rdata    align(4)                                  :>RRAM
  .rbss     align(4)                                  :>.
  # .rwufcopy align(4)                                  :>RRAM_WUF

  .ram_end               align(16)                    :>.                                                                 
                                                             
  #_VECTORTABLE_START_ADDR    = ADDR(.intvect_ExtExceptions);
  #_EXCEPTIONTABLE_START_ADDR = ADDR(.intvect);
  _VECTORTABLE_START_ADDR    = ADDR(.Os_EI_vect);               # RST Test: external interrupts. Use ETAS names
  _EXCEPTIONTABLE_START_ADDR = ADDR(.Os_intvect);               # RST Test: core interrupts. Use ETAS names
}
