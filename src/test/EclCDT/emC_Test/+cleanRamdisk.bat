set DIRDBG=%TMP%\EclCDT2009\emC_Test\Debug
if exist Debug rmdir /S/Q Debug
if exist Debug del 

if exist %DIRDBG% rmdir /S/Q %DIRDBG% 
mkdir %DIRDBG%
mklink /J Debug %DIRDBG%

