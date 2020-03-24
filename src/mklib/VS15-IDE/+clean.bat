if exist debug rmdir /S/Q debug
if exist dbgC1 rmdir /S/Q dbgC1
if exist x64 rmdir /S/Q x64
if exist x32 rmdir /S/Q x32
if exist .vs rmdir /S/Q .vs
if exist *.user del /S/Q *.user
if exist *.db del /S/Q *.db
if exist *.sdf del /S/Q *.sdf

REM remove the libs too, it should be build only on demand if necessary
if exist lib rmdir /S/Q lib
mkdir lib

