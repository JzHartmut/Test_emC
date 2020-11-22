@echo off
if not "%1" == "" goto :start
echo Start of a shell script, either with Cygwin, MinGW or git environment
echo -
echo unix_script.bat PATH_TO_SCRIPT [WORKING_DIR]
echo -
echo * PATH_TO_SCRIPT like given in windows on double click, absolute with backslash
echo                or relative from WORKING_DIR if given, may be also with slash
echo * WORKING_DIR optional, if given Windows-like with backslash (!)
echo             else current dir is the working dir.
echo * Adapt inner content to setup where Java, MinGW or Cygwin is able to find
echo                     and where the home is located!
exit /b

:start

REM often used in shell scripts, set it:
set JAVAC_HOME=C:/Programs/Java/jdk1.8.0_241
set JAVA_HOME=C:/Programs/Java/jre1.8.0_241

REM Settings for home in Unix:
set HOMEPATH=\vishia\HOME
set HOMEDRIVE=D:

REM possible other working dir
if not "" == "%2" cd "%2"

REM Preparation of the scriptpath, change backslash to slash,
set SCRIPTPATHB=%1
set "SCRIPTPATH=%SCRIPTPATHB:\=/%"
echo %SCRIPTPATH%

goto :cygwin

set MinGW_HOME=c:\Programs\MinGW
set PATH=C:\Program Files\git\bin;%JAVA_HOME%\bin;%PATH%
::echo include MinGW-path firstly, after them git, elsewhere version mismatch
::echo git necessary here? replace MinGw from git ...
set PATH=%MinGW_HOME%\bin;%MinGW_HOME%\msys\1.0\bin;%PATH%
echo sh from MinGW used: %MinGW_HOME%
where sh.exe
echo current dir: %CD%
REM sh.exe needs an home directory:

REM -x to output the command as they are executed.
REM %1 contains the whole path, with backslash, sh.exe needs slash
echo on
sh.exe -c %SCRIPTPATH%
echo off
REM to view problems let it open till key pressed.
pause
exit /b

:cygwin

set Cygwin_HOME=c:\Programs\Cygwin
set PATH=C:\Program Files\git\bin;%JAVA_HOME%\bin;%PATH%
set PATH=%Cygwin_HOME%\bin;%PATH%
echo bash from Cygwin used: %Cygwin_HOME%
where bash.exe
echo current dir: %CD%
echo on
bash.exe -c %SCRIPTPATH%
echo off
REM to view problems let it open till key pressed.
pause
