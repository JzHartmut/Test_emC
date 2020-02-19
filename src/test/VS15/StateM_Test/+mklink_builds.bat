echo off
set DBG=T:\emcBase_Test\MSC15\Test_StateM
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\x64
mkdir %DBG%\x32
mkdir %DBG%\.vs
call +clean.bat
if not exist x64 mklink /J x64 %DBG%\x64
if not exist x32 mklink /J x32 %DBG%\x32
if not exist .vs mklink /J .vs %DBG%\.vs
pause

