echo ###########################################################################
echo # Create Production hex file                                              #
echo ###########################################################################
copy ..\03_application\Application.hex .
copy ..\Application_with_CRC32.s19 .
copy ..\..\..\..\..\repo_projects\pFOTA\cR_R2023.09.21\make\Bootloader.hex .\Bootloader.hex
..\..\..\..\..\06_Tools\HexView\hexview.exe Bootloader.hex /S /AD:256 /CS9:@0x1FFDC;0x0-0x1FEFF /XS:32:2 /o Bootloader.hex
..\..\..\..\..\06_Tools\HexView\hexview.exe /MO:Bootloader.hex+Application.hex+Application_PP.hex+TLRH850F1L016.hex+Application_EEP.hex /S /AD:256 /FP:FF /XS:32:2 /o Merged.hex
..\..\..\..\..\06_Tools\HexView\hexview.exe /MO:Bootloader.hex+Application_with_CRC32.s19+Application_PP.hex+Application_EEP.hex /S /AD:256 /FP:FF /XS:32:2 /o Production_aabbcc_ddeeffff_crc32.mot
echo.
echo.
echo ###########################################################################
echo # FINISH                                                                  #
echo ###########################################################################
