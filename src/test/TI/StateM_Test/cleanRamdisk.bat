set TIDBG=T:\TI\StateMTest_Debug
if exist Debug rmdir /S/Q Debug
if exist %TIDBG% rmdir /S/Q %TIDBG% 
mkdir %TIDBG%
mklink /J Debug %TIDBG%

