#REM: should be invoked anytime from the root of the Working tree, change to it:
cd `dirname "$0"`/../../..
pwd

if test "$OS" = "Windows_NT"; then
  echo windows
else
  ##set all src/*.sh to executable for all, also in maybe symbolic linked folder of src
 ##do it firstly after clone from git or copy, the file properties will be retained
  echo find -L "src" -name '*.sh' -exec chmod 777 {} \;
  find -L "src" -name '*.sh' -exec chmod 777 {} \;
  find -L "src" -name '*.jztsh' -exec chmod 777 {} \;
  ##NOTE -R only for all files in directory, does not run chmod -R 777 *.sh
  ##
  ##NOTE: only create build newly if it does not exists, prevent already compiled files there.
  if ! test -d build ; then src/buildScripts/+clean_mkLinkBuild.sh; fi
fi  


#REM invokes JZtxtcmd as main class of vishiaBase with this file:
java -jar tools/vishiaBase.jar src/test/testScripts/testBasics_Simple.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
build/testBasics_Simple.sh
read -n1 -r -p "Press any key to continue..."

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

include ../ZmakeGcc/test_Selection.jztsh;
currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  ##Generate all relevant test cases
  debug;
  call genTestcases(name = "testBasics_Simple", select =
  <:><: >
    1=ObjNo; 2=StrNo; 3=CppAll; 4=ThExcNo; 5=ExcNo; 6=TestBase
  + 1=ObjSiReflNo; 2=StrNo; 3=CppAll; 4=ThSimple; 5=ExcJmp; 6=TestBase
  + 1=ObjCppAdrReflFull; 2=StrUse; 3=CppAll; 4=ThHeapStacktrc; 5=ExcCpp; 6=TestBase
  + 1=ObjSiReflNo; 2=StrUse; 3=CppAll; 4=ThSimple; 5=ExcJmp; 6=TestEvMsg
  <.>);  ##Generate all relevant test cases
}

