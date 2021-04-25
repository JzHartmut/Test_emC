#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
##if test -f ../../../src/version_Test_emC.txt; then cd ../../..; fi ##invoked from curr dir
#REM: should be invoked anytime from the root of the Working tree
##pwd
cd `dirname "$0"`/../../..
if ! test -e build; then src/buildScripts/-mkLinkBuild.sh; fi

#REM invokes JZtxtcmd as main class of vishiaBase with this file:
java -jar libs/vishiaBase.jar $0                                                                                          

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
      1=ObjSiReflNo, ObjSiReflSi, ObjSiReflOffs, ObjReflNo, ObjReflSi, ObjReflOffs, ObjCppReflOffs, ObjCppAdrReflOffs; 2=StrNo, StrUse; 
    + 1=ObjCppReflFull, ObjCppAdrReflFull; 2=StrUse;
  &   4=ThSimple, ThStackUsg, ThStacktrc, ThHeapStacktrc; 5=ExcNo, ExcJmp, ExcCpp; 6=TestBase; 3=CppAll;
  <.> );  ##Generate all relevant test cases
}

