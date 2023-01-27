@echo off

REM often used in shell scripts, set it:
set JAVAC_HOME=C:\Programs\Java\jdk1.8.0_241
set JAVA_HOME=C:\Programs\Java\jre1.8.0_241

REM Settings for home in Unix:
set HOMEPATH=\vishia\HOME
set HOMEDRIVE=D:

echo Homedrive = %HOMEDRIVE% 
echo Homepath = %HOMEPATH%

REM comment it to use mingw, execute to use cygwin
goto :cygwin

:cygwin

set Cygwin_HOME=c:\Programs\Cygwin
set PATH=%JAVA_HOME%\bin;%JAVAC_HOME%\bin;%PATH%
set PATH=%Cygwin_HOME%\bin;%PATH%
PATH
echo "JAVAC_HOME=>>%JAVAC_HOME%<<"
echo bash from Cygwin used: %Cygwin_HOME%
where bash.exe
echo current dir: %CD%
echo on
bash.exe 
echo off
REM to view problems let it open till key pressed.
pause
exit /b
