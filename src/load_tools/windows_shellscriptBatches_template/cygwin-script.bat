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
::pause
::exit /b

:start

echo PATH_TO_SCRIPT=%1
echo WORKING_DIR=%2

REM often used in shell scripts, set it:
set JAVAC_HOME=C:\Programs\Java\jdk1.8.0_241
set JAVA_HOME=C:\Programs\Java\jre1.8.0_291

REM Settings for home in Unix:
REM possible other working dir
if not "" == "%2" cd "%2"

REM Preparation of the scriptpath, change backslash to slash,                                                                                              
set SCRIPTPATHB=%1
set "SCRIPTPATH=%SCRIPTPATHB:\=/%"
::if not "%SCRIPTPATHB%" == "" set SCRIPTPATH="%SCRIPTPATHB:\=/%"
echo Scriptpath = %SCRIPTPATH%
REM sh.exe needs an home directory:
REM comment it to use mingw, execute to use cygwin
goto :cygwin

set HOMEPATH=\vishia\HOME
set HOMEDRIVE=D:
echo Homedrive = %HOMEDRIVE% 
echo Homepath = %HOMEPATH%


set MinGW_HOME=c:\Programs\MinGW
set PATH=C:\Program Files\git\bin;%JAVA_HOME%\bin;%PATH%
::echo include MinGW-path on first position, after them git, elsewhere version mismatch
::echo git necessary here? replace MinGw from git ...
set PATH=%MinGW_HOME%\bin;%MinGW_HOME%\msys\1.0\bin;%PATH%
echo sh from MinGW used: %MinGW_HOME%
where sh.exe
echo current dir: %CD%
REM -x to output the command as they are executed.
REM %1 contains the whole path, with backslash, sh.exe needs slash
echo on
sh.exe %SCRIPTPATH%
echo off
REM to view problems let it open till key pressed.
pause
exit /b

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
if "%SCRIPTPATH%"=="" bash.exe
if not "%SCRIPTPATH%"=="" bash.exe -c %SCRIPTPATH%
echo off
REM to view problems let it open till key pressed.
pause

