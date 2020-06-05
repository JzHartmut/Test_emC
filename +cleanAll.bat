@echo off
if exist .gradle rmdir .gradle
if exist build rmdir build
REM cleans all IDE build directories
call src\test\TI\Test_All\+clean.bat
call src\test\VS15\All_Test\+clean.bat
call src\test\EclCDT\emC_Test\+clean.bat
call src\main\cpp\src_emC\make\mklib\VS15-Zmake\+clean.bat
call src\main\cpp\src_emC\make\InspcTargetProxy\VS15-IDE\+clean.bat

if not "%1"=="nopause" pause
