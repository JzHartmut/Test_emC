set TIDBG=T:\TI\TestAll
call +clean.bat
if exist %TIDBG% rmdir /S/Q %TIDBG% 
mkdir %TIDBG%\Debug
mkdir %TIDBG%\RelO3
mkdir %TIDBG%\DbgC1
mkdir %TIDBG%\RelC1
mklink /J Debug %TIDBG%\Debug
mklink /J RelO3 %TIDBG%\RelO3
mklink /J DbgC1 %TIDBG%\DbgC1
mklink /J RelC1 %TIDBG%\RelC1

