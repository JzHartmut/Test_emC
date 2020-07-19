@echo off

REM activate MinGW
call ..\..\..\..\-setEnv.bat
:loop
REM execute in Linux sh, organized with the MinGW sh.exe
sh.exe -c TestSimple.jzTc.sh
echo
pause
goto :loop

