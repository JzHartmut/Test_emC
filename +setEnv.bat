REM Starting in Windows, some conditions:

if "JAVA_HOME"=="" set JAVA_HOME=c:\Programs\Java\jdk1.8.0_211

REM extends the path to used Mingw.
REM Note if MinGw is in another path already, this statement is not disturbing
set PATH=c:\Programs\MinGW\bin;c:\Programs\MinGW\msys\1.0\bin\;%PATH%

REM Use a link instead writing created files of gradle and build immediately in this file tree
set DB=%TMP%\emC_Test_gradle
::if exist %DB% rmdir /S/Q %DB%
if not exist %DB%\build mkdir %DB%\build
if not exist %DB%\.gradle mkdir %DB%\.gradle
if not exist build mklink /J build %DB%\build
if not exist .gradle mklink /J .gradle %DB%\.gradle
