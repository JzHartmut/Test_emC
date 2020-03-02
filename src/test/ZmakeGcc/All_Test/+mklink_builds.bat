echo off
set DBG=%TMP%\emc_Test\ZmakeGcc\Test_All
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\Debug
call +clean.bat
mklink /J build %DBG%
pause

