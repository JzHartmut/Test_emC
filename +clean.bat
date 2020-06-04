@echo off
if exist .gradle rmdir .gradle
if exist build rmdir build
if not "%1"=="nopause" pause
