@echo off
REM invoke from current dir, where this file is stored.
SET LOGDIR=%CD%\test_Selection_Log_deleteMe
if not exist %LOGDIR% mkdir %LOGDIR% 
REM invokes the stimuli selection GUI
REM Decision whether a 32.bit or 64.bit SWT library should be used depends on the java version 32 or 64, not on the Operation System.
::set SWTJAR=org.eclipse.swt.win32.win32.x86_3.5.1.v3555a.jar
set SWTJAR=org.eclipse.swt.win32.win32.x86_64_3.110.0.v20190305-0602.jar

REM if javaw is used, the console window remain open but can be closed manually independent of the java run.
REM The >out and >err can be used. If start is used here, >out and >err do not work. 
REM Then no information is given on faulty conditions, especially missing jars.
REM Therefore 'start' cannot be used here.
REM write out the command line to help explore the starting conditions on faulty situation:
@echo on  
cd ..\..\..\..
call -setEnv.bat

::javaw -cp ../../../../libs/vishiaGui.jar;../../../../libs/vishiaBase.jar;../../../../libs/%SWTJAR% org.vishia.simSelector.SimSelector %0 size:D 1>%LOGDIR%\log.txt 2>%LOGDIR%\err.txt
javaw -cp libs/vishiaGui.jar;libs/vishiaBase.jar;libs/%SWTJAR% org.vishia.simSelector.SimSelector %0 size:D 
::1>%LOGDIR%\log.txt 2>%LOGDIR%\err.txt
@echo off
type %LOGDIR%\err.txt
::if errorlevel 1 pause
REM exit /b means, the console window remain open though this called batch will be finished. exit pure closes the console.
exit /b 

==JZtxtcmd==

##include stimuli_template.m.jzT.cmd;    ##the template for the simulink stimuli file
##include setInspcArgs_template.jzTc;
##include "../../../lib_Sfn/stimuli/createStimuli.jzTc";

currdir = <:><&scriptdir>/../../../..<.>;

Class SameChars = org.vishia.util.StringFunctions_B;


main() {
  call genTestcases(select="S");
}

##Character for test case selection:
                                                                                                                                                            
## E Test all Exception variants with ObjRefl, ReflSi



List tabObj = 
[ { name="ObjSiSi",   descr="..ObjSiSi",     select="ix", def="-D DEF_ObjectSimple_emC -D DEF_ObjectJc_SIMPLE" }
, { name="ObjSiRefl", descr="..ObjSiRefl",   select="rx", def="-D DEF_ObjectSimple_emC -D DEF_ObjectJc_REFLREF" }
, { name="ObjSimpl",  descr="..ObjSimpl",    select="Ix", def="-D DEF_ObjectJc_SIMPLE" }
, { name="ObjRefl",   descr="..ObjRefl",     select="ERx", def="-D DEF_ObjectJc_REFLREF" }
, { name="ObjCpp",    descr="..ObjCpp",      select="Px", def="-D DEF_ObjectJcpp_REFLECTION -D " }
, { name="ObjCppAdr", descr="..ObjCppAdr",   select="Ax", def="-D DEF_ObjectJcpp_REFLECTION -D DEF_ObjectJc_OWNADDRESS" }
];

List tabRefl = 
[ { name="ReflNo",   descr="..ReflNo",       select="-", def="-D DEF_REFLECTION_NO"      }
, { name="ReflSi",   descr="..ReflSi",       select="EC", def="-D DEF_REFLECTION_SIMPLE"  }
, { name="ReflOffs", descr="..ReflOffs",     select="O", def="-D DEF_REFLECTION_OFFS"    }
, { name="ReflFull", descr="..ReflFull",     select="U", def="-D DEF_REFLECTION_FULL"    }
];


List tabStr = 
[ { name="StrNo",   descr="StrNo",         select="E+x", def="-D DEF_NO_StringJcCapabilities"      }
, { name="StrUse",  descr="StrUse",        select="E$x", def="-D DEF_StringJcCapab_USE"  }
];

List tabThExc = 
[ { name="ThSi_ExcNo",  descr="ThSi_ExcNo",  select="EWx", def="-D DEF_ThreadContext_SIMPLE -D DEF_Exception_NO" }
, { name="ThSi_ExcJmp", descr="ThSi_ExcJmp", select="EJx", def="-D DEF_ThreadContext_SIMPLE -D DEF_Exception_longjmp"}
, { name="ThSi_ExcCpp", descr="ThSi_ExcCpp", select="EX",  def="-D DEF_ThreadContext_SIMPLE -D DEF_Exception_TRYCpp"}
                              
, { name="ThST_ExcNo",  descr="ThST_ExcNo",  select="EW",  def="-D DEF_ThreadContext_STACKTRC -D DEF_Exception_NO"}
, { name="ThST_ExcJmp", descr="ThST_ExcJmp", select="EJ",  def="-D DEF_ThreadContext_STACKTRC -D DEF_Exception_longjmp"}
, { name="ThST_ExcCpp", descr="ThST_ExcCpp", select="EX",  def="-D DEF_ThreadContext_STACKTRC -D DEF_Exception_TRYCpp"}
                              
];


class ToGui 
{
  List tdata1 = tabObj;
  List tdata2 = tabRefl;
  List tdata5 = tabStr;
  List tdata4 = tabThExc;

}


sub XXXgenStimuli(String key1, String key2, String key3, String key4, String key5, String key6){
  <+out>genStimuli
  <.+>

}


sub execSelection(Map line1, Map line2, Map line3, Map line4, Map line5, Map line6){
  Openfile fAllsh = "build/testAllBase.sh";
  <+fAllsh>if test -d build; then cd build; fi  
  echo all output > all.out
  <.+n>
  call genSelection(line1 = line1, line2 = line2, line3 = line3, line4 = line4, line5 = line5, line6 = line6
              , fAllsh = fAllsh);
  <+fAllsh>read -n1 -r -p "Press any key to continue..."<.+n>
  fAllsh.close();            
}




sub genSelection(Map line1, Map line2, Map line3, Map line4, Map line5, Map line6, Obj fAllsh){
  String sDefTest = <:><&line1.def> <&line2.def> <&line3.def> <&line4.def> <&line5.def><.>;
  String dbgOut = <:>dbg<&line1.name>_<&line2.name>_<&line4.name>_<&line5.name><.>;
  <+out>Selection: dbgOut = <&dbgOut>
  DEF=<&sDefTest>
  <.+> 
  <+fAllsh>./make_<&dbgOut>.sh >out.txt
  cat out.txt
  cat out.txt >> all.txt
  <.+n>
  call build_dbgC1(dbgOut=dbgOut, cc_def=sDefTest);

}

sub exec1(String button="Exec", Map line1, Map line2, Map line3, Map line4, Map line5, Map line6){
  cmd cmd.exe /C start sh.exe -c build/testAllBase.sh;
}



sub genTestcases(String select){
  ##T: should be used as the temporary output for debugging, it may be a RAM disk, only temporary
  
  ##if(not File:"T:\".exists() ) {  cmd cmd.exe /C subst T: d:\tmp; }
  <+>Generate Tests <&select><.+n>
  Num ixcase = 1;
  Openfile fAllsh = <:>build/testAllBase.sh<.>; 
  ##Openfile fcsv = <:><&dirSimulink>/<&fileTestCases_m>.csv<.>; 
  <+fAllsh>                                                                                                                                                
  <:>
  echo all output > all.out
==if test -d build; then cd build; fi
==#All test cases
==<.><.+>
  ##<+fcsv>"Name", "Description", "todo",<.+n>    
  for(lineObj: tabObj) {                                                   
    for(lineRefl: tabRefl) {                                  
      for(lineStr: tabStr) {
        for(lineThExc: tabThExc) {
          ##for(var5: variation_5) {
            if(select.length() == 0 || SameChars.checkSameChars(select, lineObj.select, lineRefl.select, lineStr.select, lineThExc.select)) {
              <+out>Select: <&lineObj.name> <&lineRefl.name> <&lineStr.name> <&lineThExc.name><.+n>
              call genSelection(line1=lineObj, line2=lineRefl, line3=null, line4=lineStr, line5=lineThExc, line6=null
                                , fAllsh = fAllsh);
              ixcase = ixcase + 1; 
  } } } }   }
  <+fAllsh>read -n1 -r -p "Press any key to continue..."<.+n>
  fAllsh.close();      
  ##fcsv.close();
}

     






##The include path for all compilations.
String inclPath =  ##from position of the generated make.cmd file 
<:> <: >
-Isrc/main/cpp/src_emC/emC_inclComplSpec/cc_Gcc <: >
-Isrc/test/cpp <: >
-Isrc/main/cpp/src_emC<.>;
                                                                                 
//String cc_options = "-O0 -g3 -Wall -c -fmessage-length=0";
String cc_options = "-O0 -Wall -c";
                                     
String libs = 
<:><: >                                                                       
-lgcc_s <: >                                                                                                             
-lgcc <: >
<.>;


##                                                                          
##The real core sources for simple applications only used ObjectJc.
##See sub build_dbgC1(), only the OSAL should be still added.  
##
Fileset c_src_emC_core =                                        
( src/main/cpp/src_emC:emC/Base/Assert_emC.c
, src/main/cpp/src_emC:emC/Base/MemC_emC.c
, src/main/cpp/src_emC:emC/Base/StringBase_emC.c
, src/main/cpp/src_emC:emC/Base/ObjectSimple_emC.c
, src/main/cpp/src_emC:emC/Base/Object_emC.c
##Note: following only necessary for C++ usage with virtual interface concepts
, src/main/cpp/src_emC:emC/Base/ObjectJcpp_emC.cpp
##Note: the following files are empty if DEF_ThreadContext_SIMPLE is set, should be omissible
, src/main/cpp/src_emC:emC/Base/Exception_emC.c
, src/main/cpp/src_emC:emC/Base/ExceptionCpp_emC.cpp
, src/main/cpp/src_emC:emC/Base/ReflectionBaseTypes_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ThreadContextUserBuffer_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ExceptionPrintStacktrace_emC.c
##Note: Only for test evaluation
, src/main/cpp/src_emC:emC/Test/testAssert_C.c
, src/main/cpp/src_emC:emC/Test/testAssert.cpp
, src/test/cpp/emC_TestAll/outTestConditions.c
);



Fileset src_Base_emC_NumericSimple = 
( src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ApplSimpleStop_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/fw_ThreadContextSimpleIntr.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextSingle_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/LogException_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ObjectJc_allocStartup_emC.c
);



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


Fileset srcTestBasics =
( src/test/cpp:emC_TestAll\testBasics.cpp
);

Fileset srcTest_ObjectJc = 
( src/test/cpp:emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.cpp
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJcpp.cpp
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJc.c
);
  
Fileset srcTest_Exception =
( src/test/cpp:emC_Test_Stacktrc_Exc\TestException.cpp
, src/test/cpp:emC_Test_C_Cpp\test_stdArray.cpp
, src/test/cpp:emC_Test_C_Cpp/TestVtblExplicit.cpp
);






##
##A simple executable only for basic tests with ObjectJc
##uses less files.
##
sub build_dbgC1(String dbgOut, String cc_def) {
  
  <+out>Generates a file build/make_test_emC.sh for compilation and start test ... 
  <&cc_def>
  <.+n>
  String cc_defh = <:><&cc_def> -Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef<.>;
  
  Obj checkDeps = new org.vishia.checkDeps_C.CheckDependencyFile(console, 1);
  checkDeps.setDirObj(<:>build/<&dbgOut>/*.o<.>);
  checkDeps.readCfgData("src/test/ZmakeGcc/All_Test/cfgCheckDeps.cfg", File: <:><&currdir><.>);
  checkDeps.readDependencies(<:>build/<&dbgOut>/deps.txt<.>);
  <+out><:n>checkDeps_C: build/<&dbgOut>/deps.txt read successfully<.+n>
  
  Stringjar cmd1; cmd1 += cmd cmd.exe /C CD;
  <+out><&cmd1><.+n>
  ##<+makeAll>build/make_<&dbgOut>.sh<.+n>
  String sMake = <:>build/make_<&dbgOut>.sh<.>;
  <+out>create <&sMake><.+n>
  Openfile makesh = sMake;
  <+makesh># call of compile, link and execute for Test emC_Base with gcc<:n><.+>
  <+makesh><:>
  if test -f make_<&dbgOut>.sh; then cd ..; fi  #is in build directory, should call from root
  pwd
  if ! test -d build/result; then mkdir build/result; fi
  rm -f build/<&dbgOut>/gcc*.txt
  #rm -r Debug  #for test
  echo <&dbgOut>: Compile with <&cc_def> 1> build/<&dbgOut>/gcc_err.txt
  echo <&dbgOut>: Compile with <&cc_def>
  <.><.+>
  
  zmake <:>build/<&dbgOut>/*.o<.> := ccCompile( &c_src_emC_core
  , &src_Base_emC_NumericSimple, &src_OSALgcc
  , &srcTest_ObjectJc
  , &srcTest_Exception
  , cc_def = cc_defh, makesh = makesh, checkDeps = checkDeps
  );
  zmake <:>build/<&dbgOut>/*.o<.> := ccCompile(&srcTestBasics
  ,cc_def = <:><&cc_defh> -D DEF_TESTBasics_emC<.>
  , makesh = makesh, checkDeps = checkDeps
  );
  
  //Use other objects, controlled by output directory! It uses the DbgC1/... object files.
  zmake <:>build/<&dbgOut>/emCBase_.test.exe<.> := ccLink(&c_src_emC_core
  , &src_Base_emC_NumericSimple, &src_OSALgcc
  , &srcTest_ObjectJc, &srcTest_Exception, &srcTestBasics
  , makesh = makesh);                                                                
  
  <+makesh><:>
  if ! test -f build/<&dbgOut>/emCBase_.test.exe; then
    echo ERROR exe not built. See linker output.
    echo ==========================
  else  
    echo ==== execute the test ====                  
    build/<&dbgOut>/emCBase_.test.exe 1> build/result/<&dbgOut>.out 2> build/result/<&dbgOut>.err
    echo ==== Test cases ==========
    cat build/result/<&dbgOut>.out
    echo
    echo ==== Test failures =======
    cat build/result/<&dbgOut>.err
    echo
    echo ==========================
  fi  
  <.><.+>
  
  makesh.close();
  Obj fMake = new java.io.File(sMake);
  fMake.setExecutable(true);   ##for linux, chmod to executable
  ##currdir = "build";
  checkDeps.writeDependencies();
  checkDeps.close();
  <+out>success generate <&sMake><.+n>
  ##out += cmd sh.exe -c <:><&sMake><.>;
  
}


##
##Creates a snippet in the output file for compiling all sources with gcc:
##
sub ccCompile(Obj target:org.vishia.cmd.ZmakeTarget, String cc_def, Obj makesh, Obj checkDeps) {
  for(c_src1: target.allInputFilesExpanded()) {
    ##The checkDeps algorithm itself may be unnecessary for compilation for compilation of all files.
    ##but it creates the obj directory tree which is necessary for compilation.
    ##The checkDeps checks whether the file is changed, delete the obj file on changed file.
    Obj infoDeps = checkDeps.processSrcfile(File: &c_src1.file(), c_src1.localfile());
    <+out><&infoDeps><.+n> ##show state, info and file name on console.
    <+makesh><: >
    <:>
    echo ==== gcc <&c_src1.localfile()> 1>> <&target.output.localdir()>/gcc_err.txt
    if ! test -e <&target.output.localdir()>/<&c_src1.localname()>.o; then
      mkdir -p <&target.output.localdir()>/<&c_src1.localdir()>
      gcc <&cc_options> -Wa,-adhln <&cc_def> <&inclPath> -o <&target.output.localdir()>/<&c_src1.localname()>.o <&c_src1.file()> 1>> <&target.output.localdir()>/<&c_src1.localname()>.lst 2>> <&target.output.localdir()>/gcc_err.txt 
      if test ! -e <&target.output.localdir()>/<&c_src1.localname()>.o; then 
        echo gcc ERROR: <&c_src1.localfile()>
        echo ERROR: <&c_src1.localfile()> >> gcc_nocc.txt; 
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
##Creates a snippet in the output file for linking all sources with gcc:
##
sub ccLink(Obj target:org.vishia.cmd.ZmakeTarget, Obj makesh) {
  <+makesh><: >
  <:>
  if test -e <&target.output.localfile()>; then rm -f test.exe; fi
  g++ -o <&target.output.localfile()><.><.+> 
  for(c_src1: target.allInputFilesExpanded()) {
    <+makesh> <&target.output.localdir()>/<&c_src1.localname()>.o<.+>    
  }
  <+makesh><: >
  <:> <&libs> 1> <&target.output.localdir()>/ld_out.txt 2> <&target.output.localdir()>/ld_err.txt            
  echo view gcc_err.txt and ld_err.txt for warnings or errors if the test does not run.                                     
  <.><.+>
}  

