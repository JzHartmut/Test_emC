echo off
REM it creates the links to TMP and the directories in TMP

REM do nothing if build exists, as link or direct.
REM Note: removing only the build link is sufficient to clean all.
call .\+Clean.bat nopause

REM TMP should be set in windows, it may refer a RAM disk
REM only emergency if TMP is not set:
if not "%TMP%"=="" goto :tmpOk 
  REM Windows-batch-bug: set inside a if ...(...) does not work!
  set TMP=c:\tmp
  mkdir c:\tmp
:tmpOk

REM The used temporary inside %TMP%
set TD=%TMP%\Test_emC

REM The current director as working dir
set PWD_TEST_EMC=%CD%

REM clean content if build is not existing, and link
if not exist build (
  REM Note rmdir /S/Q does not remove files under a found link inside
  REM       but rmdir /S/Q %TD%\build\src would be remove all sources, unfortunately
  REM Note: rmdir /S/Q cleans all, del /S/Q/F does not clean the directory tree
  if exist %TD%\build rmdir /S/Q %TD%\build 
  mkdir %TD%\build
  mklink /J build %TD%\build
  echo %PWD_TEST_EMC%
) 

if not "%1"=="nopause" pause
exit /b
