@echo off
set BUILD_DIR=%TMP%\emC_Test_gradle
if exist %BUILD_DIR% rmdir /S/Q %BUILD_DIR% 
rmdir .gradle
rmdir build
pause
