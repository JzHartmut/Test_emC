REM to have an output directory for build, the following batch should be started.
REM It creates an directory in the %TMP% directory tree for build
REM and links it via mklink /J (so named junction) for Windows
if not exist build call +clean_mkLinkBuild.bat

cygwin-script.bat "./build.sh"
pause
