#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -f testSimple1.jzTc.sh; then cd ../../..; fi

java -jar libs/vishiaBase.jar src/test/testScripts/testSimple1.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
cd build
./testSimple1.sh


exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jzT.cmd;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  ##call genTestcases(select=";");          ##Only the simplest test
  ##call genTestcases(select=";SE:}SE:{SE" name = "testAllBase");  ##Generate all relevant test cases
  call genTestcases(select=";", name = "testSimple1");  ##Generate all relevant test cases
}

