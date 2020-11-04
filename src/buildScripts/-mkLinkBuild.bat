echo on
echo called: src\buildScripts\-mkLinkBuild.bat
REM it creates the links to BUILD_TMP and the directories in BUILD_TMP

REM do nothing if build exists, as link or direct.
REM Note: removing only the build link is sufficient to clean all.
::call .\+Clean.bat nopause

REM BUILD_TMP should be set in windows, it may refer a RAM disk
REM do not use TMP because it is changed by sh.exe with slash, use a new variable.
REM T: is a ramdisk, if not exists use D:\tmp or such.
if exist C:\tmp set BUILD_TMP=C:\tmp
if exist D:\tmp set BUILD_TMP=D:\tmp
if exist T:\tmp set BUILD_TMP=T:\tmp

REM only emergency if BUILD_TMP is not set:
if not "%BUILD_TMP%"=="" goto :tmpOk 
  REM Windows-batch-bug: set inside a if ...(...) does not work!
  echo set BUILD_TMP=c:\tmp
  set BUILD_TMP=c:\tmp
  mkdir c:\tmp
:tmpOk

REM The used temporary inside %BUILD_TMP%
set TD=%BUILD_TMP%\Test_emC


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

