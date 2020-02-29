set DIRDBG=T:\EclCDT\ObjectJcpp_Test\Debug
if exist Debug rmdir /S/Q Debug
if exist %DIRDBG% rmdir /S/Q %DIRDBG% 
mkdir %DIRDBG%
mklink /J Debug %DIRDBG%

