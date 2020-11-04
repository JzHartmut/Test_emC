@echo off
REM sets environment, maybe executes sh.exe with given file
echo This script should be adapted to the user's system.
echo It determines paths to JAVA, MINGW

if "%JAVA_HOME%"=="" set JAVA_HOME=c:\Programs\Java\jdk1.8.0_241
if not exist "%JAVA_HOME%\bin\java.exe" (
  echo JAVA_HOME=%JAVA_HOME%
  %JAVA_HOME%\bin\java --version
  echo java.exe not found.
  exit #close the shell
) 

REM extends the path to used Mingw.
REM Note if MinGw is in another path already, this statement is not disturbing
set MINGW=c:\Programs\MinGW
echo MINGW: %MINGW%
sh.exe --version
set PATH=%MINGW%\bin;%MINGW%\msys\1.0\bin\;%PATH%

echo Win environment ok

REM invoke a given shell script with this settings given as argument:
if "%1"=="" exit /b 
REM If a command is given, execute it. Finished the cmd after them. 
echo sh.exe -C %1
sh.exe -c %1
exit #close the shell.



