echo off
set TMP=T:\tmp
set DBG=%TMP%\emcBase_Mklib\ZmakeGcc\Test_All
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\Debug
call +clean.bat
mklink /J build %DBG%
pause

