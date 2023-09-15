:: Create checksums
@echo off
if "%1" == "" goto usage

if not exist "%1" goto nohexfile

echo.
echo Generate 2 checksums (CRC32 and CMAC)
echo Compress file (Vector compression)
echo.
echo CRC (Security model NONE)          :
echo %~d1%~p1%~n1.crc
echo CMAC signature (Security model C)  :
echo %~d1%~p1%~n1_cmac.sig
echo.

set local_dir=%~d0%~p0

:: Please configure the following variables
:: Root directory
set root_dir=%local_dir%\..
:: Hexview executable
set hexview_exe=%root_dir%\06_Tools\Hexview\hexview.exe
:: Keys
set cmac_key=%local_dir%\c_key.txt

echo Calculate CRC...
%hexview_exe% %1 /S -e:%local_dir%error.txt /cs9:%~n1.crc

echo Calculate CMAC signature (Security class C)...
%hexview_exe% %1 /S -e:%local_dir%error.txt /dp45:%cmac_key%;%~n1_cmac.sig


echo ...finished.
echo.
goto end

:nohexfile
echo "Hex file does not exist."
del %local_dir%\error.txt
goto end

:usage
echo "Please call with a hex file as parameter."

pause
del %local_dir%\error.txt

:end