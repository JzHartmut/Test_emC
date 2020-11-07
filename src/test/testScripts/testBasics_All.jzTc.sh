#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -d ../../../build; then cd ../../..; fi
pwd

java -jar libs/vishiaBase.jar src/test/testScripts/testBasics_All.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
cd build
pwd
./testBasics_All.sh


exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jzT.sh;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  //call genTestcases(select=";");          ##Only the simplest test
  ##                        ObjSi         ReflSimple  ReflOffs    ReflFull
  call genTestcases(select="ieIqrnjtNJTsS:ernjtNJTsS:ErQnjtNJTsS:EaArRnjtNJTS", name="testBasics_All");  ##Generate all relevant test cases
}

