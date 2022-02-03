#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
##if test -f ../../../src/version_Test_emC.txt; then cd ../../..; fi ##invoked from curr dir
#REM: should be invoked anytime from the root of the Working tree
clear
pwd
CURRDIR=$CD
echo $CURRDIR
cd `dirname "$0"`/../../..
pwd
if ! test -e build; then src/buildScripts/-mkLinkBuild.sh; fi

#REM invokes JZtxtcmd as main class of vishiaBase with this file:
java -jar tools/vishiaBase.jar src/test/testScripts/testAllObjModis.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
build/testBasics_SimpleAll.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jztsh;

currdir=<:><&scriptdir>/../../..<.>;                             

##Map ccSet;  ##Settings for compilation

##String ccSet.cc = "clang";



main() {
  call genTestcases(name = "testBasics_SimpleAll", select=
  <:>
      1= ObjNo, ObjSiReflNo, 
         ObjSiReflSi,   ObjSiSynReflSi,   ObjSiAddrReflSi,   ObjSiSynAddrReflSi, 
         ObjSiReflOffs, ObjSiCppReflOffs, ObjSiAddrReflOffs, ObjSiCppAddrReflOffs, 
         ObjReflNo, ObjReflSi, ObjReflOffs, ObjCppReflOffs, ObjCppAdrReflOffs; 
         2=StrNo, StrUse; 
    + 1= ObjReflFull, ObjCppReflFull, ObjCppAdrReflFull; 2=StrUse, CharSeq;
  &   4= ThExcNo; 5= ExcNo;
  &   6= TestBase; 3=CppAll;  
  <.> );  ##Generate all relevant test cases
}

