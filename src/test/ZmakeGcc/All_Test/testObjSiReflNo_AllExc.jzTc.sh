#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -f cfgCheckDeps.cfg; then cd ../../../..; fi

java -jar libs/vishiaBase.jar src/test/ZmakeGcc/All_Test/testObjSiReflNo_AllExc.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
cd build
./testObjSiReflNo_AllExc.sh


exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include test_Selection.jzT.cmd;

currdir=<:><&scriptdir>/../../../..<.>;                             

main() {
  ##call genTestcases(select=";");          ##Only the simplest test
  ##call genTestcases(select=";SE:}SE:{SE" name = "testAllBase");  ##Generate all relevant test cases
  call genTestcases(select=";SE", name = "testObjSiReflNo_AllExc");  ##Generate all relevant test cases
}

