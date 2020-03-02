@echo off
set PATH=c:\Programs\MinGW\bin;c:\Programs\MinGW\msys\1.0\bin\;%PATH%
  
call +mklink_builds.bat
:repeat
cls
call JZtxtcmd.bat %0
echo close window to exit, else repeat:
pause
goto :repeat
::cd build
::call make.bat
exit /B                                      
                                                                   
==JZtxtcmd==
include src/test/ZmakeGcc/All_Test/ZmakeGcc.jz.bat;

currdir=scriptdir;


main() {
  call test_emC();
}



