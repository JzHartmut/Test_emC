echo off
call +clean.bat
set DBG=%TMP%\emc_Test\MSC15_InspcTargetProxy\All_Test
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\x32
mkdir %DBG%\Win32
mkdir %DBG%\.vs
if not exist x32 mklink /J x32 %DBG%\x32
if not exist Win32 mklink /J win32 %DBG%\Win32
if not exist .vs mklink /J .vs %DBG%\.vs
pause

