REM Start build with shell scripts under windows

REM if necessary enhance path here.
call -setEnv.bat

REM create some linked directories if not existing:
call -mkLinkBuildGradle.bat 

REM execute in Linux sh, organized with the MinGW sh.exe
sh.exe -c build.sh
pause