echo removes %~d0%~p0\Debug etc.
if exist %~d0%~p0\Debug rmdir /S/Q %~d0%~p0\Debug
if exist %~d0%~p0\RelO3 rmdir /S/Q %~d0%~p0\RelO3
if exist %~d0%~p0\DbgC1 rmdir /S/Q %~d0%~p0\DbgC1
if exist %~d0%~p0\RelC1 rmdir /S/Q %~d0%~p0\RelC1

