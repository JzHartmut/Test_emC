echo off
call +clean.bat
set DBG=%TMP%\emc_Test\MSC15\All_Test
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\x64
mkdir %DBG%\dbgC1
mkdir %DBG%\x32
mkdir %DBG%\Win32
mkdir %DBG%\.vs
if not exist x64 mklink /J x64 %DBG%\x64
if not exist x32 mklink /J x32 %DBG%\x32
if not exist Win32 mklink /J win32 %DBG%\Win32
if not exist dbgC1 mklink /J dbgC1 %DBG%\dbgC1
if not exist .vs mklink /J .vs %DBG%\.vs
pause

