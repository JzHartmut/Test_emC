REM Starting in Windows, some conditions:

if "JAVA_HOME"=="" set JAVA_HOME=c:\Programs\Java\jdk1.8.0_211

REM extends the path to used Mingw.
REM Note if MinGw is in another path already, this statement is not disturbing
set PATH=c:\Programs\MinGW\bin;c:\Programs\MinGW\msys\1.0\bin\;%PATH%

REM Use a link instead writing created files of gradle and build immediately in this file tree
set BUILD_DIR=%TMP%\emC_Test_gradle
::if exist %BUILD_DIR% rmdir /S/Q %BUILD_DIR%
if not exist %BUILD_DIR%\build mkdir %BUILD_DIR%\build
if not exist %BUILD_DIR%\.gradle mkdir %BUILD_DIR%\.gradle
if not exist build mklink /J build %BUILD_DIR%\build
if not exist .gradle mklink /J .gradle %BUILD_DIR%\.gradle
