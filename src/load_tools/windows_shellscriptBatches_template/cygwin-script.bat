@echo off
if not "%1" == "" goto :start
echo Start of cygwin bash.exe maybe with shell script
echo -
echo cygwin_script.bat PATH_TO_SCRIPT [WORKING_DIR]
echo -
echo * PATH_TO_SCRIPT like given in windows on double click, absolute with backslash
echo                or relative from WORKING_DIR if given, may be also with slash
echo * WORKING_DIR optional, if given Windows-like with backslash (!)
echo             else current dir is the working dir.
echo * Adapt inner content to setup where Java, MinGW or Cygwin is able to find
echo                     and where the home is located!

:start

echo PATH_TO_SCRIPT=%1
echo WORKING_DIR=%2

REM sh.exe needs an home directory:
set HOMEPATH=\vishia\HOME
set HOMEDRIVE=D:
set Cygwin_HOME=c:\Programs\Cygwin
set PATH=%JAVA_HOME%\bin;%JAVAC_HOME%\bin;%PATH%
set PATH=%Cygwin_HOME%\bin;%PATH%
::PATH
echo bash from Cygwin used: %Cygwin_HOME%
where bash.exe

REM often used in shell scripts, set it:
set JAVAC_HOME=C:\Programs\Java\jdk1.8.0_241
set JAVA_HOME=C:\Programs\Java\jre1.8.0_291
echo "JAVAC_HOME=>>%JAVAC_HOME%<<"

REM Settings for home in Unix:
REM possible other working dir
if not "" == "%2" cd "%2"

REM Preparation of the scriptpath, change backslash to slash,                                                                                              
set SCRIPTPATHB=%1
set "SCRIPTPATH=%SCRIPTPATHB:\=/%"
echo Scriptpath = %SCRIPTPATH%

REM comment it to use mingw, execute to use cygwin

echo current dir: %CD%
echo on
bash.exe -c %SCRIPTPATH%
echo off
REM to view problems let it open till key pressed.
pause

