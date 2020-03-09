@echo off
REM this script is a batch cmd and also a JZtxtcmd called from gradle
REM Only if called as command line immediately, the following statements are executed:
call +setEnv.bat  
:repeat
cls
java -cp downloaded/jars/vishiaBase.jar org.vishia.jztxtcmd.JZtxtcmd %0
echo close window to exit, else repeat:
pause
goto :repeat
exit /B                                      
                                                                   
==JZtxtcmd==

##The following script is the test script. It is included to execute as standard
##It can be independent executed too.

include src/test/ZmakeGcc/All_Test/ZmakeGcc.jzTc.sh;

currdir=scriptdir;


main() {
  call test_emC();
}



