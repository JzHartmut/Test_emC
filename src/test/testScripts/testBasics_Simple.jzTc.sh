#REM: should be invoked anytime from the root of the Working tree, change to it:
cd `dirname "$0"`/../../..
pwd
if ! test -e build; then src/buildScripts/-mkLinkBuild.sh; fi

#REM invokes JZtxtcmd as main class of vishiaBase with this file:
java -jar libs/vishiaBase.jar src/test/testScripts/testBasics_Simple.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
build/testBasics_Simple.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jztsh;
currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  ##Generate all relevant test cases
  call genTestcases(name = "testBasics_Simple", select =
  <:><: >
    1=ObjSiReflNo; 2=StrNo; 3=CppAll; 4=ThSimple; 5=ExcJmp; 6=TestBase
  + 1=ObjCppAdrReflFull; 2=StrUse; 3=CppAll; 4=ThHeapStacktrc; 5=ExcCpp; 6=TestBase
  + 1=ObjSiReflNo; 2=StrUse; 3=CppAll; 4=ThSimple; 5=ExcJmp; 6=TestEvMsg
  <.>);  ##Generate all relevant test cases
}

