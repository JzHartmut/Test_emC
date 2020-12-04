#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -d ../../../build; then cd ../../..; fi
pwd

java -jar libs/vishiaBase.jar src/test/testScripts/testEvMsg_All.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
cd build
pwd
./testEvMsgObjSi_ReflNo_All.sh
./testEvMsgReflSi_All.sh
./testEvMsgReflOffs_All.sh
./testEvMsgReflFull_All.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jztsh;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  //call genTestcases(select=";");          ##Only the simplest test
  ##                        ObjSi ReflNo ReflSimple ReflOffs     ReflFull
  call genTestcases(select="iIqrnjtNJTsSM", name="testEvMsgObjSi_ReflNo_All");  ##Generate all relevant test cases
  call genTestcases(select="ernjtNJTsSM", name="testEvMsgsReflSi_All");  ##Generate all relevant test cases
  call genTestcases(select="eErQnjtNJTsSM", name="testEvMsgReflOffs_All");  ##Generate all relevant test cases
  call genTestcases(select="EaArRnjtNJTSM", name="testEvMsgReflFull_All");  ##Generate all relevant test cases
}

