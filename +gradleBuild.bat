call +setEnv.bat
REM create test results newly
if exist build\reports rmdir /S/Q build\reports

REM execute in loop during devlopment of the scripts:
:repeat
cls
call gradle.bat 2>build\err.txt
type build\err.txt
echo close window to abort, or ctrl-C, else repeat
pause
::call inetBrowser %CD%\build\reports\tests\test\index.html
goto :repeat

