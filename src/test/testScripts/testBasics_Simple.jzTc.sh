#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -f testBasics_Simple.jzTc.sh; then cd ../../..; fi
pwd
java -jar libs/vishiaBase.jar src/test/testScripts/testBasics_Simple.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
cd build
./testBasics_Simple.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jzT.sh;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  ##call genTestcases(select=";");          ##Only the simplest test
  ##call genTestcases(select=";SE:}SE:{SE" name = "testAllBase");  ##Generate all relevant test cases
  call genTestcases(select="iqnsB:IJrSB", name = "testBasics_Simple");  ##Generate all relevant test cases
}

