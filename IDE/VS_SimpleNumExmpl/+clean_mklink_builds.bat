echo off
call +clean.bat
set DBG=%TMP%\emc_Test\MSC15_emC_TestSimpleExmpl
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\Debug
mkdir %DBG%\x32
mkdir %DBG%\x64
mkdir %DBG%\Win32
mkdir %DBG%\.vs
if not exist Debug mklink /J Debug %DBG%\Debug
if not exist x64 mklink /J x64 %DBG%\x64
if not exist x32 mklink /J x32 %DBG%\x32
if not exist Win32 mklink /J win32 %DBG%\Win32
if not exist .vs mklink /J .vs %DBG%\.vs
pause

