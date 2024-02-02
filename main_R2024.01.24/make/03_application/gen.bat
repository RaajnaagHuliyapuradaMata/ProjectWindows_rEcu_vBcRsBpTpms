@echo off
if "%1" == "" goto usage

if not exist "%1" goto nohexfile

set local_dir=%~d0%~p0

set root_dir=%local_dir%\..\..\..\..\..
set hexview_exe=%root_dir%\repo_tools\Hexview\hexview.exe
set key=%local_dir%\key.txt

echo Calculate CRC...
%hexview_exe% %1 /S -e:%local_dir%error.txt /cs9:%~n1.crc

echo Calculate signature
%hexview_exe% %1 /S -e:%local_dir%error.txt /dp30:%key%;%~n1.sig

%hexview_exe% %1 /S /XI:16:0 /o Application_aa.bb.cccc_Hermes.hex
echo.

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