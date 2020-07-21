@echo off

REM activate MinGW
call ..\..\..\..\-setEnv.bat
:loop
REM execute in Linux sh, organized with the MinGW sh.exe
cls
sh.exe -c TestSimple.jzTc.sh
echo
pause
goto :loop

