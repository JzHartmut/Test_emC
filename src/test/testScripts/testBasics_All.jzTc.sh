#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -f testBasics_All.jzTc.sh; then cd ../../..; fi
pwd

java -jar libs/vishiaBase.jar src/test/testScripts/testBasics_All.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
build/testBasicsObjSi_ReflNo_All.sh
build/testBasicsReflSi_All.sh
build/testBasicsReflOffs_All.sh
build/testBasicsReflFull_All.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jztsh;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  //call genTestcases(select=";");          ##Only the simplest test
  ##                        ObjSi ReflNo ReflSimple ReflOffs     ReflFull
  call genTestcases(select="iIqrnjtNJTsSB", name="testBasicsObjSi_ReflNo_All");  ##Generate all relevant test cases
  call genTestcases(select="ernjtNJTsSB", name="testBasicsReflSi_All");  ##Generate all relevant test cases
  call genTestcases(select="eErQnjtNJTsSB", name="testBasicsReflOffs_All");  ##Generate all relevant test cases
  call genTestcases(select="EaArRnjtNJTSB", name="testBasicsReflFull_All");  ##Generate all relevant test cases
}

