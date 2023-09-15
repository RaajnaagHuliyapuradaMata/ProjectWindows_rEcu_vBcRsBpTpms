@echo off
path=%WINDIR%;%WINDIR%\System32\
echo.
echo.
echo.
echo ##########################################################
echo # Clean application                                      #
echo ##########################################################
echo.
..\..\..\..\06_Tools\GNU\make.exe clean -f./Make/Makefile
echo.

@if errorlevel 1 goto fehler
echo CLEAN OKAY
goto END

:fehler
echo CLEAN NOT OKAY
goto END

:END
@echo on


