@echo off
REM often used in shell scripts, set it:
set JAVAC_HOME=C:/Programs/Java/jdk1.8.0_241
set JAVA_HOME=C:/Programs/Java/jre1.8.0_241
set MinGW_HOME=c:\Programs\MinGW
set PATH=%MinGW_HOME%\bin;%MinGW_HOME%\msys\1.0\bin;%PATH%
set PATH=C:\Program Files\git\bin;%JAVA_HOME%\bin;%PATH%

REM sh.exe needs an home directory:
set HOMEPATH=\vishia\HOME
set HOMEDRIVE=D:

REM possible other working dir
if not "" == "%2" cd "%2" 

REM -x to output the command as they are executed.
REM %1 contains the whole path, with backslash, sh.exe needs slash
REM change backslash to slash, 
set SCRIPTPATHB=%1
set "SCRIPTPATH=%SCRIPTPATHB:\=/%"
echo %SCRIPTPATH%
echo on
sh.exe -c %SCRIPTPATH%

REM to view problems let it open till key pressed.
pause
