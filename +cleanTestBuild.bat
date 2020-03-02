@echo off
cd src\test\
call +cleanTestBuilds.bat
cd ..\..
rmdir .gradle
rmdir build
pause
