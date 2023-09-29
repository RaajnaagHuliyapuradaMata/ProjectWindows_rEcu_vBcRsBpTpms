:: Create checksums
@echo off
if "%1" == "" goto usage

if not exist "%1" goto nohexfile

set local_dir=%~d0%~p0

:: Please configure the following variables
:: Root directory
set root_dir=%local_dir%\..\..\..\..\..
:: Hexview executable
set hexview_exe=%root_dir%\06_Tools\Hexview\hexview.exe
:: Keys
set key=%local_dir%\key.txt

echo Calculate CRC...
%hexview_exe% %1 /S -e:%local_dir%error.txt /cs9:%~dpn1.crc

echo Calculate signature
%hexview_exe% %1 /S /dp32:%key%;%~dpn1.sig -e:error.txt


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