@echo off
REM This file is called from build.sh and does windows specific things.
echo TMP=%TMP% ... hint: The sh.exe has changed backslash to slashd, correct in next bat.
echo arg1=%1
::call src\buildScripts\-setEnv.bat
::if not exist build call src\buildScripts\-mkLinkBuild.bat
