echo ##########################################################
echo # Create Production hex file                             #
echo ##########################################################
copy ..\Application_with_CRC32.s19 .
copy ..\..\..\..\..\repo_projects\pFOTA\cL_R2023.09.01\make\Bootloader.hex .\Bootloader.hex
..\..\..\..\..\repo_tools\HexView\hexview.exe Bootloader.hex /S /AD:256 /CS9:@0x1FFDC;0x0-0x1FEFF /XS:32:2 /o Bootloader.hex
..\..\..\..\..\repo_tools\HexView\hexview.exe /MO:Bootloader.hex+Application_with_CRC32.s19+Application_PP.hex+TLRH850F1L016.hex+Application_EEP.hex /S /AD:256 /FP:FF /XS:32:2 /o Merged.hex
..\..\..\..\..\repo_tools\HexView\hexview.exe /MO:Bootloader.hex+Application_with_CRC32.s19+Application_PP.hex+Application_EEP_Production.hex /S /AD:256 /FP:FF /XS:32:2 /o Production_aabbcc_ddeeffff_crc32.mot
echo.
echo.
echo ##########################################################
echo # FINISH                                                 #
echo ##########################################################
