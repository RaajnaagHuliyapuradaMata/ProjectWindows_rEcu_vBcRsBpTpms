COLOR a
@echo off

path=%WINDIR%;%WINDIR%\System32\

set TARGET=Application
@echo off
goto GNU

:GNU
echo ##########################################################
echo # Build Application                                      #
echo ##########################################################
echo.


echo Build Start: %date% %time% >> build_time.txt
..\..\..\..\repo_tools\GNU\make.exe -f./make/makefile %TARGET% register=32

echo ###########################################################################
echo # Create .s19 from .s3                                                    #
echo ###########################################################################
if exist %TARGET%.s3 ..\..\..\..\repo_tools\HexView\hexview.exe %TARGET%.s3 /S /AD:256 /FP:FF /XS:32:2 /o %TARGET%_original.s19
echo.

echo ###########################################################################
echo # Fill 0x20000-0x200ff with 0xff (empty bytes only)                       #
echo # Fill 0x4e300-0x77aff with 0xff                                          #
echo # Calc CRC32, range 0x20000-0x77bdb, write to 0x77bdc..f                  #
echo # Calc XOR16, range 0x20000-0x77bfd, write to 0x77bfe..f                  #
echo # Copy file to 03_application folder                                      #
echo ###########################################################################
if exist %TARGET%_original.s19   ..\..\..\..\repo_tools\HexView\hexview.exe %TARGET%_original.s19   /S /AD:256 /FR:0x20020-0x200ff /FP:FF    /XS:32:2 /o %TARGET%_original.s19
if exist %TARGET%_original.s19   ..\..\..\..\repo_tools\HexView\hexview.exe %TARGET%_original.s19   /S /AD:256 /FR:0x4e300-0x77aff /FP:FF    /XS:32:2 /o %TARGET%_original.s19
if exist %TARGET%_original.s19   ..\..\..\..\repo_tools\HexView\hexview.exe %TARGET%_original.s19   /S /AD:256 /CS9:@0x77BDC;0x20000-0x77BDB /XS:32:2 /o %TARGET%_with_CRC32.s19
if exist %TARGET%_with_CRC32.s19 ..\..\..\..\repo_tools\HexView\hexview.exe %TARGET%_with_CRC32.s19 /S /AD:256 /CS0:@0x77BFE;0x20000-0x77BFD /XS:32:2 /o %TARGET%_with_CRC32.s19
copy %TARGET%_with_CRC32.s19 .\03_application\%TARGET%.hex
echo.

echo ##########################################################
echo # Create Checksum/Signature file on application          #
echo ##########################################################
cd .\03_application
call gen.bat %TARGET%.hex
cd..
echo.

cd .\01_production
call create_production_file.bat
cd..
echo.

echo ##########################################################
echo # Copy hex and sig file to Canoe Config update folder    #
echo ##########################################################
cd .\03_application
copy %TARGET%.hex ..\..\..\..\..\..\..\Lordstown\Target\repo_tools\Canoe\Vector_Download_Sequence\CANoe\_TestFiles\%TARGET%.hex
copy %TARGET%.sig ..\..\..\..\..\..\..\Lordstown\Target\repo_tools\Canoe\Vector_Download_Sequence\CANoe\_TestFiles\%TARGET%.sig

cd..
echo.

goto END
:END

echo Build End: %date% %time% >> build_time.txt

