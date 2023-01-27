echo off
echo called: src\buildScripts\+clean_mkLinkBuild.bat
if exist ..\..\src\BuildScripts cd ..\..
echo workingDir %CD%


REM create build if it not exists with a link to tmp
if exist build rmdir /S/Q build
REM it creates the links to BUILD_TMP and the directories in BUILD_TMP

REM TMP should be set in windows, it may refer a RAM disk

REM only emergency if BUILD_TMP is not set:
if not "%TMP%"=="" goto :tmpOk 
  REM Windows-batch-bug: set inside a if ...(...) does not work!
  echo set TMP=c:\tmp
  set TMP=c:\tmp
  mkdir c:\tmp
:tmpOk

REM The used temporary inside %BUILD_TMP%
set TD=%TMP%\Test_emC\build


REM The current director as working dir
set PWD_TEST_EMC=%CD%

REM clean content if build is not existing, and link
if not exist build (
  REM Note rmdir /S/Q does not remove files under a found link inside
  REM       but rmdir /S/Q %TD%\build\src would be remove all sources, unfortunately
  REM Note: rmdir /S/Q cleans all, del /S/Q/F does not clean the directory tree
  if exist %TD% rmdir /S/Q %TD% 
  mkdir %TD%
  mklink /J build %TD%
  echo test empty >build/readme.txt
  echo %PWD_TEST_EMC%
) 

if not "%1"=="nopause" pause
exit /b

