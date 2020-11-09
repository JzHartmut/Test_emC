#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -d ../../../build; then cd ../../..; fi
pwd

java -jar libs/vishiaBase.jar src/test/testScripts/testBasics_All.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
cd build
pwd
./testBasicsObjSi_ReflNo_All.sh
./testBasicsReflSi_All.sh
./testBasicsReflOffs_All.sh
./testBasicsReflFull_All.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jzT.sh;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  //call genTestcases(select=";");          ##Only the simplest test
  ##                        ObjSi ReflNo ReflSimple ReflOffs     ReflFull
  call genTestcases(select="iIqrnjtNJTsS", name="testBasicsObjSi_ReflNo_All");  ##Generate all relevant test cases
  call genTestcases(select="ernjtNJTsS", name="testBasicsReflSi_All");  ##Generate all relevant test cases
  call genTestcases(select="eErQnjtNJTsS", name="testBasicsReflOffs_All");  ##Generate all relevant test cases
  call genTestcases(select="EaArRnjtNJTS", name="testBasicsReflFull_All");  ##Generate all relevant test cases
}

