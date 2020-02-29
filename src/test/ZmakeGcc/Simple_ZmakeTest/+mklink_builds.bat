echo off
set DBG=T:\emcBase_Test\ZmakeGcc\Simple_ZmakeTest
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\Debug
call +clean.bat
if not exist build mklink /J build %DBG%
pause

