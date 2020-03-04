@echo off
REM this script is a batch cmd and also a JZtxtcmd called from gradle
REM Only if called as command line immediately, the following statements are executed:
call +setEnv.bat  
:repeat
cls
java -cp libs/zbnf.jar org.vishia.jztxtcmd.JZtxtcmd %0
::call JZtxtcmd.bat %0
echo close window to exit, else repeat:
pause
goto :repeat
exit /B                                      
                                                                   
==JZtxtcmd==
include src/test/ZmakeGcc/All_Test/ZmakeGcc.jz.bat;

currdir=scriptdir;


main() {
  call test_emC();
}



