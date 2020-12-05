echo removes %~d0%~p0\Debug etc (*.db, *.sdf, *.user, .vs, x64 etc)

if exist %~d0%~p0\debug rmdir /S/Q %~d0%~p0\debug
if exist %~d0%~p0\dbgC1 rmdir /S/Q %~d0%~p0\dbgC1
if exist %~d0%~p0\x64   rmdir /S/Q %~d0%~p0\x64
if exist %~d0%~p0\x32   rmdir /S/Q %~d0%~p0\x32
if exist %~d0%~p0\Win32 rmdir /S/Q %~d0%~p0\Win32
if exist %~d0%~p0\.vs   rmdir /S/Q %~d0%~p0\.vs
if exist %~d0%~p0\*.user  del /S/Q %~d0%~p0\*.user
if exist %~d0%~p0\*.db    del /S/Q %~d0%~p0\*.db
if exist %~d0%~p0\*.sdf   del /S/Q %~d0%~p0\*.sdf

