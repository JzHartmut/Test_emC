REM Starting in Windows, some conditions:

if "JAVA_HOME"=="" set JAVA_HOME=c:\Programs\Java\jdk1.8.0_211

REM extends the path to used Mingw.
REM Note if MinGw is in another path already, this statement is not disturbing
set PATH=c:\Programs\MinGW\bin;c:\Programs\MinGW\msys\1.0\bin\;%PATH%


