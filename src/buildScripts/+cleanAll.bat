@echo off
echo called: src\buildScripts\+cleanAll.bat
if exist ..\..\src\BuildScripts cd ..\..
echo workingDir %CD%

if exist build rmdir build
REM cleans all IDE build directories
call src\test\TI\Test_All\+clean.bat
call src\test\EclCDT\emC_Test\+clean.bat
call IDE\VS15_emCapplications\+clean.bat
call IDE\VS_SimpleNumExmpl\+clean.bat
call IDE\VS_StringFileExmpl\+clean.bat
call IDE\VS_InspcTargetExmpl\+clean.bat
call IDE\VS15\+clean.bat

if not "%1"=="nopause" pause
