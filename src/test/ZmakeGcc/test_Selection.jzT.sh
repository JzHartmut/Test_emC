##not necessary because unix_script.bat is used anycase: call ..\..\..\src\buildScripts\-setEnv.bat test_Selection.jzT.cmd
#@echo off
#REM invoke from current dir, where this file is stored.
#SET LOGDIR=%CD%\test_Selection_Log_deleteMe
#if not exist %LOGDIR% mkdir %LOGDIR% 
#REM invokes the stimuli selection GUI
#REM Decision which SWT library should be used depends on the java version 32 or 64, not on the Operation System.
#::set SWTJAR=org.eclipse.swt.win32.win32.x86_3.5.1.v3555a.jar  ##for Win32
if test "$OS" = "Windows_NT"; then ##Win64
  CP="libs/vishiaGui.jar;libs/vishiaBase.jar;libs/org.eclipse.swt.win32.win32.x86_64_3.110.0.v20190305-0602.jar"
else
  CP="libs/vishiaGui.jar:libs/vishiaBase.jar:libs/swt-4.18M1-gtk-linux-x86_64.jar"
fi
#REM if javaw is used, the console window remain open but can be closed manually independent of the java run.
#REM The >out and >err can be used. If start is used here, >out and >err do not work. 
#REM Then no information is given on faulty conditions, especially missing jars.
#REM Therefore 'start' cannot be used here.
#REM write out the command line to help explore the starting conditions on faulty situation:
#@echo on  
cd ../../..
#call -setEnv.bat
pwd
#REM call the GUI. This file %0 is used as argument for SimSelector. It contains all control after the JZtxtcmd label
echo java -cp $CP org.vishia.simSelector.SimSelector src/test/ZmakeGcc/test_Selection.jzT.sh -size:D 
java -cp $CP org.vishia.simSelector.SimSelector src/test/ZmakeGcc/test_Selection.jzT.sh -size:D
#::1>%LOGDIR%\log.txt 2>%LOGDIR%\err.txt

#@echo off
#::type %LOGDIR%\err.txt
#::if errorlevel 1 pause
#REM exit /b means, the console window remain open though this called batch will be finished. exit pure closes the console.
#exit /b 
exit

==JZtxtcmd==

##include stimuli_template.m.jzT.cmd;    ##the template for the simulink stimuli file
##include setInspcArgs_template.jzTc;
##include "../../../lib_Sfn/stimuli/createStimuli.jzTc";

currdir = <:><&scriptdir>/../../..<.>;

Class SameChars = org.vishia.util.StringFunctions_B;


main() {
  call genTestcases(select="S", name="test_Selection");
}



##
##This routine will be called from inside the Java programm org.vishia.simSelector.SimSelector
##  on the button gen selection. It generates all selected test cases.
##  @args: Map linex contains some named variables which are processed in genSelection(...)
##
sub btnGenSelection(Map line1, Map line2, Map line3, Map line4, Map line5, Map line6){
  Openfile fAllsh = "build/testCurrSel.sh";      ##Helper to execute with "press any key" on end. 
  <+fAllsh>if test -d build; then cd build; fi  
  if test -f testCurrSel.out; then rm testCurrSel.out; fi
  <.+n>
  Openfile fAllBat = "build/testCurrSel.bat";      ##Helper to execute with "press any key" on end. 
  <+fAllBat>if exit build cd build  
  if exist testCurrSel.out del /S/Q testCurrSel.out
  <.+n>
  call genSelection(line1 = line1, line2 = line2, line3 = line3, line4 = line4, line5 = line5, line6 = line6
              , fAllsh = fAllsh, fAllBat = fAllBat);
  <+fAllsh>read -n1 -r -p "Press any key to continue..."<.+n>
  fAllsh.close();            
}



##
##This routine will be called from inside the Java programm org.vishia.simSelector.SimSelector
##  on the button with given button text as first argument of this.
##Note: It is the exec key. The gui reads exec1 ... exec4 and creates up to 4 exec keys.
##
sub btnExec1(String button="exec Selection", Map line1, Map line2, Map line3, Map line4, Map line5, Map line6){
  cmd cmd.exe /C start sh.exe -c build/testCurrSel.sh;
}


##
##
##This routine will be called from inside the Java programm org.vishia.simSelector.SimSelector
##  on the button gen testcases. It generates all selected test cases.
##
sub genTestcases(String select, String name = "testCaseXX"){
  ##T: should be used as the temporary output for debugging, it may be a RAM disk, only temporary
  
  ##if(not File:"T:\".exists() ) {  cmd cmd.exe /C subst T: d:\tmp; }
  <+>Generate Tests <&select><.+n>
  Num ixcase = 1;
  Openfile fAllsh = <:>build/<&name>.sh<.>;                         ##build/testCase.sh for all tests 
  ##Openfile fcsv = <:><&dirSimulink>/<&fileTestCases_m>.csv<.>; 
  <+fAllsh>                                                                                                                                                
  <:>
==echo off
==echo all output > all.out
==if test -d build; then cd build; fi
==if test -f <&name>.out; then rm <&name>.out; fi
==echo "==== new test select=<&select> ====" ><&name>.out
==date >> <&name>.out
==echo "==================================" >><&name>.out
==#All test cases
==<.><.+>

  Openfile fAllBat = <:>build/<&name>.bat<.>;                         ##build/testCase.bat for all tests                         
  ##Openfile fcsv = <:><&dirSimulink>/<&fileTestCases_m>.csv<.>; 
  <+fAllBat>                                                                                                                                                
  <:>
  echo all output > all.out
==if exist build cd build
==if exist <&name>.out del /S/Q <&name>.out
==echo "==== new test select=<&select> ====" ><&name>.out
==::date >> <&name>.out
==echo "==================================" >><&name>.out
==::All test cases
==<.><.+>

  ##<+fcsv>"Name", "Description", "todo",<.+n>    
  for(lineObj: tabObj) {                                                   
    for(lineRefl: tabRefl) {                                  
      for(lineStr: tabStr) {
        for(lineThExc: tabThExc) {
          for(lineTestSrc: tabTestSrc) {
            if(  select.length() == 0 
              || SameChars.checkMoreSameChars(select
                    , lineObj.select, lineRefl.select, lineStr.select, lineThExc.select, lineTestSrc.select)
              ) {
              <+out>Select: <&lineObj.name> <&lineRefl.name> <&lineStr.name> <&lineThExc.name><.+n>
              call genSelection(line1=lineObj, line2=lineRefl, line3=lineTestSrc, line4=lineStr, line5=lineThExc, line6=null
                                , fAllsh = fAllsh, fAllBat = fAllBat);   
              ixcase = ixcase + 1; 
  } } } } } }
  ##<+fAllsh>read -n1 -r -p "Press any key to continue..."<.+n>
  fAllsh.close();      
  <+fAllBat>pause<.+n>
  fAllBat.close();      
  Obj fileAllsh = new java.io.File(<:>build/<&name>.sh<.>);
  fileAllsh.setExecutable(true);   ##for linux, chmod to executable
  ##fcsv.close();
}

     



##
##This operation is kind of common but adapted to the test cases. 
##It is called here from execSelection button and from genTestcases
sub genSelection(Map line1, Map line2, Map line3, Map line4, Map line5, Map line6, Obj fAllsh, Obj fAllBat){

  
  Stringjar defineMsg = <:>echo "#define <&line1.def1>" > out.txt<:n><.>;
  Stringjar defineDef = <:>#define <&line1.def1><:n><.>;                ##line1, List
  Stringjar doption = <:>-D <&line1.def1> <.>;
  if(line1.def2) { 
    defineMsg += <:>echo "#define <&line1.def2>" >> out.txt<:n><.>; 
    defineDef += <:>#define <&line1.def2><:n><.>;
    doption += <:>-D <&line1.def2> <.>;
  }
  defineMsg += <:>echo "#define <&line2.def1>" >> out.txt<:n><.>;       ##line2, List 
  defineDef += <:>#define <&line2.def1><:n><.>;
  doption += <:>-D <&line2.def1> <.>;
  if(line2.def2) { 
    defineMsg += <:>echo "#define <&line2.def2>" >> out.txt<:n><.>; 
    defineDef += <:>#define <&line2.def2><:n><.>;
    doption += <:>-D <&line2.def2> <.>;
  }
  ##
  defineMsg += <:>echo "#define <&line4.def1>" >> out.txt<:n><.>;       ##line4, List
  defineDef += <:>#define <&line4.def1><:n><.>;
  doption += <:>-D <&line4.def1> <.>;
  if(line4.def2) { 
    defineMsg += <:>echo "#define <&line4.def2>" >> out.txt<:n><.>; 
    defineDef += <:>#define <&line4.def2><:n><.>;
    doption += <:>-D <&line4.def2> <.>;
  }
  defineMsg += <:>echo "#define <&line5.def1>" >> out.txt<:n><.>;       ##line5, List
  defineDef += <:>#define <&line5.def1><:n><.>;
  doption += <:>-D <&line5.def1> <.>;
  if(line5.def2) { 
    defineMsg += <:>echo "#define <&line5.def2>" >> out.txt<:n><.>; 
    defineDef += <:>#define <&line5.def2><:n><.>;
    doption += <:>-D <&line5.def2> <.>;
  }
  defineMsg += <:>echo "#define <&line3.def1>" >> out.txt<:n><.>;       ##line3, List tabTestSrc
  defineDef += <:>#define <&line3.def1><:n><.>;
  doption += <:>-D <&line3.def1> <.>;
  
  ##testCase is the name of the script, name of the directory etc. 
  String testCase = <:>dbg<&line1.name>_<&line2.name>_<&line4.name>_<&line5.name><.>;
  <+out>
  <:>
  Selection creates make_<&testCase>.sh
  <&defineDef>
  <.><.+> 
  ##
  ##writes to fAllsh, it is the shell script to invoke all tests:
  <+fAllsh>
  <&defineMsg>
  echo invokes ./objZmake/make_<&testCase>.sh, compile all:
  ./objZmake/make_<&testCase>.sh
  ##cat out.txt
  ##cat out.txt >> testCurrSel.out
  <.+>
  ##
  ##writes to fAllBat, it is the shell script to invoke all tests:
  <+fAllBat>
  <&defineMsg>
  echo invokes ./objZmake/make_<&testCase>.sh, compile all:
  call unix_script.bat ./objZmake/make_<&testCase>.sh
  ##cat out.txt
  ##cat out.txt >> testCurrSel.out
  <.+>
  ##
  ##Writes a header for visual Studio test
  Openfile fDefH = "src/test/VS15/All_Test/fDefSelection.h";
  <+fDefH><: >
  <:><: >
  //This file is produced by running the sim selection tool.
  #define DEFINED_fDefSelection
  
  //The next defines contains the selection:
  <&defineDef><.><.+>
  fDefH.close();
  ##
  ##The following subroutine generates the script with compiling statements
  call build_dbgC1(testCase=testCase, cc_def=doption, defineDef=defineDef, srcSet = &(line3.srcSet) ); ##srcset_Basics); ##

}






##The include path for all compilations.
String inclPath =  ##from position of the generated make.cmd file 
<:> <: >
-Isrc/main/cpp/src_emC/emC_inclComplSpec/cc_Gcc <: >
-Isrc/test/cpp <: >
-Isrc/main/cpp/src_emC<.>;
                                                                                 
//String cc_options = "-O0 -g3 -Wall -c -fmessage-length=0";
String cc_options = "-O0 -Wall -c -x c++";
                                     
String libs = 
<:><: >                                                                       
-lgcc_s <: >                                                                                                             
-lgcc <: >
<.>;


Fileset src_OSALgcc =
( src/main/cpp/src_emC:emC_srcOSALspec/hw_Intel_x86_Gcc/os_atomic.c
, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_endian.c
, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_error.c
, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_file.c
, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_mem.c
##, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_mutex.c
##, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_socket.c
##, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_sync.c
##, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_thread.c
, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_time.c
);

##                                                                          
##The real core sources for simple applications only used ObjectJc.
##See sub build_dbgC1(), only the OSAL should be still added.  
##
Fileset c_src_emC_core =                                        
( src/main/cpp/src_emC:emC/Base/Assert_emC.c
, src/main/cpp/src_emC:emC/Base/MemC_emC.c
, src/main/cpp/src_emC:emC/Base/StringBase_emC.c
, src/main/cpp/src_emC:emC/Base/ObjectSimple_emC.c
, src/main/cpp/src_emC:emC/Base/ObjectRefl_emC.c
##Note: following only necessary for C++ usage with virtual interface concepts
, src/main/cpp/src_emC:emC/Base/ObjectJcpp_emC.cpp
##Note: the following files are empty if DEF_ThreadContext_SIMPLE is set, should be omissible
, src/main/cpp/src_emC:emC/Base/Exception_emC.c
, src/main/cpp/src_emC:emC/Base/ExceptionCpp_emC.cpp
, src/main/cpp/src_emC:emC/Base/ExcThreadCxt_emC.c
, src/main/cpp/src_emC:emC/Base/ReflectionBaseTypes_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ExceptionPrintStacktrace_emC.c
##Note: Only for test evaluation
, src/main/cpp/src_emC:emC/Test/testAssert_C.c
, src/main/cpp/src_emC:emC/Test/testAssert.cpp
, src/test/cpp:emC_TestAll/outTestConditions.c
, &src_OSALgcc
);



Fileset src_Base_emC_NumericSimple = 
( src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ApplSimpleStop_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/fw_ThreadContextSimpleIntr.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextSingle_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/LogException_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ObjectJc_allocStartup_emC.c
);


Fileset src_Base_emC_Multithread_Linux = 
( src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_mutex.c
, src/main/cpp/src_emC:emC_srcOSALspec/os_LinuxGcc/os_thread.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/LogException_emC.c
);



Fileset srcTest_ObjectJc = 
( src/test/cpp:emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.cpp
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJcpp.cpp
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJc.c
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJc_Mutex.c
);

  
Fileset srcTest_Exception =
( src/test/cpp:emC_Test_Stacktrc_Exc\TestException.cpp
, src/test/cpp:emC_Test_C_Cpp\test_stdArray.cpp
, src/test/cpp:emC_Test_C_Cpp/TestVtblExplicit.cpp
, src/test/cpp:emC_Test_C_Cpp/TestVtbl_virtual.cpp
);


Fileset srcTest_EventStmn = 
( src/main/cpp/src_emC:emC/Base/EventQu_emC.c
, src/main/cpp/src_emC:emC/Base/RingBuffer_emC.c
, src/test/cpp:emC_Test_Container/Test_RingBuffer_emC.c
, src/test/cpp:org/vishia/emC/StateM/test_StateM/testEventQueue.cpp
);




##
## main file for Basic tests.
##
Fileset srcTestBasics =
( src/test/cpp:emC_TestAll\testBasics.cpp
, &srcTest_ObjectJc
, &srcTest_Exception
, &src_Base_emC_NumericSimple
);


Fileset srcTestEvMsg =
( src/test/cpp:emC_TestAll\testmain.cpp
, &srcTest_EventStmn
, &srcTest_ObjectJc
, &srcTest_Exception
, &src_Base_emC_Multithread_Linux
);






##Character for test case selection:

##===large tests:
## cannot be combined, either-or, but combined with one of E or select char ThExc and 
## { Test all Reflection full variants, not possible where only } is noted
## } Test all variants of DEF_Object not with REFLECTION_FULL, excluding where only { is noted.

##==group tests
## E Test all Exception variants 


List tabObj = 
[ { name="ObjSiSi",   descr="..ObjSiSi",     select="i", def1="DEF_ObjectSimple_emC", def2="DEF_ObjectJc_SIMPLE" }
, { name="ObjSiRefl", descr="..ObjSiRefl",   select="e", def1="DEF_ObjectSimple_emC", def2="DEF_ObjectJc_REFLREF" }
, { name="ObjSimpl",  descr="..ObjSimpl",    select="I", def1="DEF_ObjectJc_SIMPLE" }
, { name="ObjRefl",   descr="..ObjRefl",     select="E", def1="DEF_ObjectJc_REFLREF" }
, { name="ObjCpp",    descr="..ObjCpp",      select="a", def1="DEF_ObjectJcpp_REFLECTION" }
, { name="ObjCppAdr", descr="..ObjCppAdr",   select="A", def1="DEF_ObjectJcpp_REFLECTION", def2="DEF_ObjectJc_OWNADDRESS" }
];

List tabRefl = 
[ { name="ReflNo",   descr="..ReflNo",       select="q", def1="DEF_REFLECTION_NO"      }
, { name="ReflSi",   descr="..ReflSi",       select="r", def1="DEF_REFLECTION_SIMPLE"  }
, { name="ReflOffs", descr="..ReflOffs",     select="Q", def1="DEF_REFLECTION_OFFS"    }
, { name="ReflFull", descr="..ReflFull",     select="R", def1="DEF_REFLECTION_FULL"    }
];


List tabStr = 
[ { name="StrNo",   descr="StrNo",         select="s", def1="DEF_NO_StringJcCapabilities"      }
, { name="StrUse",  descr="StrUse",        select="S", def1="DEF_StringJcCapab_USE"  }
];

List tabThExc = 
[ { name="ThSi_ExcNo",  descr="ThSi_ExcNo",  select="n", def1="DEF_ThreadContext_SIMPLE", def2="DEF_Exception_NO" }
, { name="ThSi_ExcJmp", descr="ThSi_ExcJmp", select="j", def1="DEF_ThreadContext_SIMPLE", def2="DEF_Exception_longjmp"}
, { name="ThSi_ExcCpp", descr="ThSi_ExcCpp", select="t",  def1="DEF_ThreadContext_SIMPLE", def2="DEF_Exception_TRYCpp"}
                              
, { name="ThST_ExcNo",  descr="ThST_ExcNo",  select="N",  def1="DEF_ThreadContext_STACKTRC", def2="DEF_Exception_NO"}
, { name="ThST_ExcJmp", descr="ThST_ExcJmp", select="J",  def1="DEF_ThreadContext_STACKTRC", def2="DEF_Exception_longjmp"}
, { name="ThST_ExcCpp", descr="ThST_ExcCpp", select="T",  def1="DEF_ThreadContext_STACKTRC", def2="DEF_Exception_TRYCpp"}
];


List tabTestSrc =                               ##Note: srcsets should be defined above.
[ { name="TestBase",  descr="Test Basics",  select="B", srcSet="srcTestBasics", def1="DEF_TESTBasics_emC"}
, { name="TestEvMsg",  descr="Test Main",   select="M", srcSet="srcTestEvMsg",  def1="DEF_TESTALL_emC" }
];



##
##This information will be read from inside the Java programm org.vishia.simSelector.SimSelector
##It determines what is presented in the tables.
##
class ToGui 
{
  List tdata1 = tabObj;
  List tdata2 = tabRefl;
  List tdata3 = tabTestSrc;
  List tdata5 = tabStr;
  List tdata4 = tabThExc;

}






##
##A simple executable only for basic tests with ObjectJc
##uses less files.
##
sub build_dbgC1(String testCase, String cc_def, String defineDef, Obj srcSet) {
  
  <+out>Generates a file build/make_test_emC.sh for compilation and start test ... 
  <&cc_def>
  <&srcSet>
  <.+n>
  String cc_defh = <:><&cc_def> -Isrc/test/ZmakeGcc/applstdef_UseCCdef<.>;
  
  mkdir <:>build/objZmake/<&testCase><.>;
  
  String checkDeps = "";
  Openfile depArgs = <:>build/objZmake/deps_<&testCase>.args<.>;
  <+depArgs>-currdir:<&currdir><:n><: >
    -obj:build/objZmake/<&testCase>/*.o<:n><: >
    -cfg:src/test/ZmakeGcc/cfgCheckDeps.cfg<:n><: >
    -depAll:build/objZmake/<&testCase>/deps.txt<:n><: >
  <.+>
  ###Obj checkDeps = new org.vishia.checkDeps_C.CheckDependencyFile(console, 1);
  ###checkDeps.setDirObj(<:>build/objZmake/<&testCase>/*.o<.>);
  ###checkDeps.readCfgData("src/test/ZmakeGcc/cfgCheckDeps.cfg", File: <:><&currdir><.>);
  ###checkDeps.readDependencies(<:>build/objZmake/<&testCase>/deps.txt<.>);
  ###<+out><:n>checkDeps_C: build/objZmake/<&testCase>/deps.txt read successfully<.+n>
  
  ##<+makeAll>build/objZmake/make_<&testCase>.sh<.+n>
  Openfile filedefineDef = <:>build/objZmake/<&testCase>/fDefSelection.h<.>;    ##fDefSelection.h written for manual tests
  <+filedefineDef><:>//This file is produces by running a test case
    #define DEFINED_fDefSelection
    ///The next defines contains the selection:
    <&defineDef><.><.+close>
  String sMake = <:>build/objZmake/make_<&testCase>.sh<.>;
  <+out>create <&sMake><.+n>
  Openfile makesh = sMake;
  <+makesh># call of compile, link and execute for Test emC_Base with gcc<:n><.+>
  <+makesh><:>
  if test -d ../../build; then cd ../..; fi  #is in build directory, should call from root
  if test -d ../build; then cd ..; fi
  echo working dir to compile should be the SBOX root
  pwd                                                                          ##first invoke checkDeps
  if ! test -d build/result; then mkdir build/result; fi
  if ! test -d build/objZmake/<&testCase>; then mkdir build/objZmake/<&testCase>; fi
  echo run checkDeps, see output in build/...testCase/checkDeps.out
  java -cp libs/vishiaBase.jar org.vishia.checkDeps_C.CheckDeps --@build/objZmake/deps_<&testCase>.args > build/objZmake/<&testCase>/checkDeps.out 
  rm -f build/objZmake/<&testCase>/gcc*.txt ##clean output files
  rm -f build/result/<&testCase>.cc_err

  #rm -r Debug  #for test
  ##echo <&testCase>: Compile with <&cc_def> 1> build/objZmake/<&testCase>/compile_Defs.txt
  echo <&testCase>: Compile with <&cc_def>     
  <.><.+>
                                                                               ##compile first tranche of sources
  zmake <:>build/objZmake/<&testCase>/*.o<.> := ccCompile( &c_src_emC_core
  , &srcSet
  , cc_def = cc_defh, makesh = makesh, depArgs = depArgs, checkDeps = checkDeps, testCase=testCase
  );
                                                                               ##link
  //Use other objects, controlled by output directory! It uses the DbgC1/... object files.
  zmake <:>build/objZmake/<&testCase>/emCBase_.test.exe<.> := ccLink(&c_src_emC_core
  , &srcSet
  , makesh = makesh, testCase=testCase);                                                                
  
  <+makesh>
  <:>
  if ! test -f build/objZmake/<&testCase>/emCBase_.test.exe; then
    echo ERROR build/objZmake/<&testCase>/emCBase_.test.exe not built. See linker output.                                                       
    echo MISSING: <&testCase>/..exe >> build/result/_all_result.txt
    cat build/result/<&testCase>.cc_err >> build/result/_all.cc_err
    cat build/objZmake/<&testCase>/ld_err.txt                                                                                 
    echo ==========================
  else  
    echo ==== execute the test ====                  
    echo TEST   : <&testCase>/..exe >> build/result/_all_result.txt
    build/objZmake/<&testCase>/emCBase_.test.exe 1> build/result/<&testCase>.out 2> build/result/<&testCase>.err
    echo ==== Test cases ==========
    cat build/result/<&testCase>.out
    echo
    echo ==== Test failures =======
    cat build/result/<&testCase>.err
    echo
    echo ==========================
  fi  
  <.><.+>
  
  depArgs.close();
  makesh.close();
  Obj fMake = new java.io.File(sMake);
  fMake.setExecutable(true);   ##for linux, chmod to executable
  ##currdir = "build";
  ###checkDeps.writeDependencies();
  ###checkDeps.close();
  <+out>success generate <&sMake><.+n>
  ##out += cmd sh.exe -c <:><&sMake><.>;
  
}


##
##Creates a snippet in the generated make shell file for compiling all sources with gcc:
##
sub ccCompile(Obj target:org.vishia.cmd.ZmakeTarget, String cc_def, Obj makesh, Obj depArgs, Obj checkDeps, String testCase) {
  for(c_src1: target.allInputFilesExpanded()) {
    ##The checkDeps algorithm itself may be unnecessary for compilation for compilation of all files.
    ##but it creates the obj directory tree which is necessary for compilation.
    ##The checkDeps checks whether the file is changed, delete the obj file on changed file.
    ###Obj infoDeps = checkDeps.processSrcfile(File: &c_src1.file(), c_src1.localfile());
    String src1Base = c_src1.basepath();
    if(src1Base.length() >0) { 
      <+depArgs>-src:<&c_src1.basepath()>:<&c_src1.localfile()><.+n>  ##writes the file for checkDeps
    } else {
      <+depArgs>-src:<&c_src1.file()><.+n>  ##writes the file for checkDeps
    }
    ###<+out><&infoDeps><.+n> ##show state, info and file name on console.
    <+makesh><: >
    <:>
    #echo ==== gcc <&c_src1.localfile()> 1>> <&target.output.localdir()>/gcc_err.txt
    if ! test -e <&target.output.localdir()>/<&c_src1.localname()>.o; then
      mkdir -p <&target.output.localdir()>/<&c_src1.localdir()>
      gcc <&cc_options> -Wa,-adhln <&cc_def> <&inclPath> -o <&target.output.localdir()>/<&c_src1.localname()>.o <&c_src1.file()> 1>> <&target.output.localdir()>/<&c_src1.localname()>.lst 2>> build/result/<&testCase>.cc_err 
      
      if test ! -e <&target.output.localdir()>/<&c_src1.localname()>.o; then 
        echo gcc ERROR: <&c_src1.localfile()>
        echo ERROR: <&c_src1.localfile()> >> build/result/gcc_nocc.txt; 
      else
        echo gcc ok: <&c_src1.localfile()>
      fi
    else
      echo exist: <&c_src1.localfile()>
    fi  
    <.><.+>
  }
}  


##
##Creates a snippet in the generated make shell file for linking all sources with gcc:
##
sub ccLink(Obj target:org.vishia.cmd.ZmakeTarget, Obj makesh, String testCase) {
  <+makesh><: >
  <:>
  if test -e <&target.output.localfile()>; then rm -f test.exe; fi
  g++ -o <&target.output.localfile()><.><.+> 
  for(c_src1: target.allInputFilesExpanded()) {
    <+makesh> <&target.output.localdir()>/<&c_src1.localname()>.o<.+>    
  }
  <+makesh><: >
  <:> <&libs> 1> <&target.output.localdir()>/ld_out.txt 2>> build/result/<&testCase>.cc_err            
  echo view build/result/<&testCase>.cc_err for warnings or errors if the test does not run.                                     
  <.><.+>
}  

