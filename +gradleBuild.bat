set JAVA_HOME=c:\Programs\Java\jdk1.8.0_211
set DB=T:\emC_Base_gradle
::if exist %DB% rmdir /S/Q %DB%
if not exist %DB% mkdir %DB%\build
if not exist %DB% mkdir %DB%\.gradle
if not exist build mklink /J build %DB%\build
if not exist .gradle mklink /J build %DB%\.gradle
if exist build\reports rmdir /S/Q build\reports
::pause
call gradle.bat asciidoctor 2>build\err.txt
type build\err.txt
pause
::call inetBrowser %CD%\build\reports\tests\test\index.html

