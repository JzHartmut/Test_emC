@echo off

REM activate MinGW
call ..\..\..\..\-setEnv.bat
:loop
REM execute in Linux sh, organized with the MinGW sh.exe
sh.exe -c ZmakeGcc.jzTc.sh
..\..\..\..\build\emCBase.test.exe
echo
pause
goto :loop

