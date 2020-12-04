#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -f ../../../src; then cd ../../..; fi

java -jar libs/vishiaBase.jar src/test/ZmakeGcc/All_Test/ZmakeGcc.jzTc.sh                                                                                          

##Execute the even yet generated sh scripts, compile and execute: 
build/makeAll.sh

exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

currdir=<:><&scriptdir>/../../..<.>;                             

Openfile makeAll = "build/makeAll.sh"; ##global access for all build_... 

##Compilation, Link and Test routine called also from the gradle task.
main() { 
  call testObjectJc_cc(); 
  call test_emC(); 
  makeAll.close();  
  Obj fMakeAll = new java.io.File("build/makeAll.sh");
  fMakeAll.setExecutable(true);   ##for linux, chmod to executable
}



##it compiles only the files necessary for testMain_ObjectJc.c
##Using the C compiler only. 
sub testObjectJc_cc() {
  ##This routine calls all variants of compiling
  call build_dbgC1(dbgOut="dbgSimpleNch", cc_def=cc_defSimpleNch);
  call build_dbgC1(dbgOut="dbgReflNch", cc_def=cc_defReflNch);
  call build_dbgC1(dbgOut="dbgSimple", cc_def=cc_defSimple);
  call build_dbgC1(dbgOut="dbgRefl", cc_def=cc_defRefl);
  call build_dbgC1(dbgOut="dbgClassJcFull", cc_def=cc_defClassJcFull);
}


##testAll
##It uses the g++ compiler for all sources. 
sub test_emC() {
  ##This routine calls all variants of compiling
  call build_DbgBheap(dbgOut="dbgBhSimpleNch", cc_def=cc_defSimpleNch);
  call build_DbgBheap(dbgOut="dbgBhReflNch", cc_def=cc_defReflNch);
  call build_DbgBheap(dbgOut="dbgBhSimple", cc_def=cc_defSimple);
  call build_DbgBheap(dbgOut="dbgBhRefl", cc_def=cc_defRefl);
  call build_DbgBheap(dbgOut="dbgBhClassJcFull", cc_def=cc_defClassJcFull);
  call build_DbgBheap(dbgOut="dbgBheap", cc_def=cc_defBHeap);

  
  
}



sub build_common() {
}







##The include path for all compilations.
String inclPath =  ##from position of the generated make.cmd file 
<:> <: >
-Isrc/main/cpp/src_emC/emC_inclComplSpec/cc_Gcc <: >
-Isrc/test/cpp <: >
-Isrc/main/cpp/src_emC<.>;
                                                                                 
//String cc_options = "-O0 -g3 -Wall -c -fmessage-length=0";
String cc_options = "-O0 -Wall -c";
                                     
##Uses minimized ThreadContext, no Stacktrace, for small embedded hardware
##Simplest code:
String cc_defSimpleNch = "-Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef -D DEF_ObjectJc_SIMPLE -D DEF_ThreadContext_SIMPLE -D DEF_Exception_NO -D DEF_NO_StringJcCapabilities";

##Simplest, but with reflection (Type check)
String cc_defReflNch = "-Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef -D DEF_ObjectJc_REFLREF -D DEF_ThreadContext_SIMPLE -D DEF_Exception_NO -D DEF_NO_StringJcCapabilities";

##Using strings, 
String cc_defSimple = "-Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef -D DEF_ObjectJc_SIMPLE -D DEF_ThreadContext_SIMPLE -D DEF_Exception_NO";

##Using strings, with reflection (Type check, type names)
String cc_defRefl = "-Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef -D DEF_ObjectJc_REFLREF -D DEF_ThreadContext_SIMPLE -D DEF_Exception_NO";

##Uses full ThreadContext and Stacktrace, hence with TRYCpp
String cc_defClassJcFull = "-Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef -D DEF_ObjectJc_REFLREF";
                                                        
##yet not activated, hence with TRYCpp
String cc_defBHeap = "-Isrc/test/ZmakeGcc/All_Test/applstdef_UseCCdef -D DEF_ObjectJc_REFLREF -D USE_BlockHeap_emC";

##Note: All commented files are not necessary for the current test,
##They are some Problems in Linux-Gcc compilation, it is TODO

##                                                                          
##The real core sources for simple applications only used ObjectJc.
##See sub build_dbgC1(), only the OSAL should be still added.  
##
Fileset c_src_emC_core =                                        
( src/main/cpp/src_emC:emC/Base/Assert_emC.c
, src/main/cpp/src_emC:emC/Base/MemC_emC.c
, src/main/cpp/src_emC:emC/Base/StringBase_emC.c
, src/main/cpp/src_emC:emC/Base/Object_emC.c
##Note: following only necessary for C++ usage with virtual interface concepts
, src/main/cpp/src_emC:emC/Base/ObjectJcpp_emC.cpp
##Note: the following files are empty if DEF_ThreadContext_SIMPLE is set, should be omissible
, src/main/cpp/src_emC:emC/Base/Exception_emC.c
, src/main/cpp/src_emC:emC/Base/ExceptionCpp_emC.cpp
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ThreadContextUserBuffer_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ExceptionPrintStacktrace_emC.c
##Note: Only for test evaluation
, src/main/cpp/src_emC:emC/Test/testAssert_C.c
, src/main/cpp/src_emC:emC/Test/testAssert.cpp
, src/test/cpp/emC_TestAll/outTestConditions.c
);


Fileset c_src = 
( src/main/cpp/src_emC:emC/Base/CheckStack_emC.c
##, src/main/cpp/src_emC:emC/Base/DefPortTypes_emC.c
, src/main/cpp/src_emC:emC/Base/Event_emC.c           
##, src/main/cpp/src_emC:emC/Base/Formatter_emC.c  ##Linux problems with stdarg
, src/main/cpp/src_emC:emC/Base/Handle_ptr64_emC.c
, src/main/cpp/src_emC:emC/Base/Handle_ptr64_TimeMeas_emC.c
##, src/main/cpp/src_emC:emC/Base/LogMessage_emC.c
##, src/main/cpp/src_emC:emC/Base/LogMsgStream_emC.c
, src/main/cpp/src_emC:emC/Base/Memfree_ThreadAndBlockHeap.c
, src/main/cpp/src_emC:emC/Base/Object_RAMclass_emC.c
, src/main/cpp/src_emC:emC/Base/os_common.c
, src/main/cpp/src_emC:emC/Base/ParseArgs_emC.c
, src/main/cpp/src_emC:emC/Base/Readline_emC.c
, src/main/cpp/src_emC:emC/Base/ReflectionBaseTypes_emC.c                
, src/main/cpp/src_emC:emC/Base/Reflection_emC.c
, src/main/cpp/src_emC:emC/Base/SimpleC_emC.c
##, src/main/cpp/src_emC:emC/Base/StringBuilder_emC.c
, src/main/cpp/src_emC:emC/Base/StringCompactor_emC.c
, src/main/cpp/src_emC:emC/Base/String_emC.c
, src/main/cpp/src_emC:emC/Base/Timeconversions_emC.c
, src/main/cpp/src_emC:emC/Base/Time_emC.c
##, src/main/cpp/src_emC:emC/Base/VaArgBuffer_emC.c



, src/main/cpp/src_emC:emC/StateM/StateFnCall_StateM_emC.c
, src/main/cpp/src_emC:emC/StateM/evQueue.c


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




##Commented files here are not selected for compilation. 
##They are more variantes for the application.
##The commented files are specified here to document what is possible.

Fileset src_Base_emC_NumericSimple = 
( src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ApplSimpleStop_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ExcNoStringStacktrcNo_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/fw_ThreadContextSimpleIntr.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/osal_FatalErrorPrintf_while0.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/stopAssert_Fwc_while0.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextInterrTpl.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextSimpleFromOsal.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextSingle_emC.c

##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ApplThrowOnFatalError_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/Exception_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ExcThCxtStacksize.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/LogException_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ObjectJc_allocStartup_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/os_endian_x86.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/RemoteCpu_Dummy.c
##
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/UmlContainer_Dummy.c

);


##This Fileset should be used only if the Blockheap concept is integrated in test files.
##Alternatively always emC_srcApplSpec/applConv/ObjectJc_allocStartup_emC.c is compiled,
##                     but this file is empty by compiler switch USE_BlockHeap_emC
Fileset src_Base_emC_BlockHeap = 
( src/main/cpp/src_emC:emC/BlockHeap/BlockHeapJc_Alloc.c
);


Fileset src_Ctrl_emC = 
( src/main/cpp/src_emC:emC/Ctrl/*.c
);



Fileset test_Ctrl_emC = 
( src/test/cpp:emC_Test_Ctrl/*.c
);






##
##The files for test statemachines and events
##
Fileset srcTestStmEv = 
( src/test/cpp:org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.cpp
, src/test/cpp:org/vishia/emC/StateM/test_StateM/testEventQueue.cpp
, src/test/cpp:org/vishia/emC/StateM/test_StateM/testStateFncall_StateMemCBase.c
, src/test/cpp:org/vishia/emC/StateM/test_StateM/tplGen_StateFncall_StateMemCBase.c
, src/test/cpp:emC_Test_C_Cpp/TestVtblExplicit.cpp
);
                                                                      

Fileset srcTestBlockHeap = 
( src/test/cpp:emC_BlockHeapTest/BlockHeapTest_emC.cpp
);
                                                                      

Fileset srcTest_ObjectJc = 
( src/test/cpp:emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.cpp
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJcpp.cpp
, src/test/cpp:emC_Test_ObjectJc/test_ObjectJc.c
);
  
Fileset srcTest_Exception =
( src/test/cpp:emC_Test_Stacktrc_Exc\TestException.cpp
, src/test/cpp:emC_Test_C_Cpp\test_stdArray.cpp
);



Fileset srcTestMain_ObjectJc = ( src/test/cpp:emC_Test_ObjectJc/testMain_ObjectJc.c);
                                                                      
Fileset srcTestMain_All = ( src/test/cpp:emC_TestAll/testmain.cpp);
                                                                      




String libs = 
<:><: >                                                                       
-lgcc_s <: >                                                                                                             
-lgcc <: >
<.>;
##unnecessary and harmful for linux:
##-ladvapi32 <: >  
##-lshell32 <: >   
##-luser32 <: >                                                                                                                         
##-lkernel32 <: >  
##<.>;

##Note: The lib paths are unecessary if compilation is done in the MinGW shell itself.
##(Other then calling g++ from windows)
##-Lc:/Programs/MinGW/lib/gcc/mingw32/5.3.0 <: >
##-Lc:/Programs/MinGW/lib <: >



##
##A simple executable only for basic tests with ObjectJc
##uses less files.
##
sub build_dbgC1(String dbgOut, String cc_def) {
  
  <+out>Generates a file build/make_test_emC.sh for compilation and start test ... <.+n>
  
  Obj checkDeps = new org.vishia.checkDeps_C.CheckDependencyFile(console, 1);
  checkDeps.setDirObj(<:>build/<&dbgOut>/*.o<.>);
  checkDeps.readCfgData("src/test/ZmakeGcc/All_Test/cfgCheckDeps.cfg", File: <:><&currdir><.>);
  checkDeps.readDependencies(<:>build/<&dbgOut>/deps.txt<.>);
  <+out><:n>checkDeps_C: build/<&dbgOut>/deps.txt read successfully<.+n>
  
  <+makeAll>build/make_<&dbgOut>.sh<.+n>
  String sMake = <:><&currdir>/build/make_<&dbgOut>.sh<.>;
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
  ,cc_def = cc_def, makesh = makesh, checkDeps = checkDeps
  );
  zmake <:>build/<&dbgOut>/*.o<.> := ccCompile(&srcTestMain_ObjectJc
  ,cc_def = <:><&cc_def> -D DEF_MAIN_testMain_ObjectJc<.>
  , makesh = makesh, checkDeps = checkDeps
  );
  
  //Use other objects, controlled by output directory! It uses the DbgC1/... object files.
  zmake <:>build/<&dbgOut>/emCBase_.test.exe<.> := ccLink(&c_src_emC_core
  , &src_Base_emC_NumericSimple, &src_OSALgcc
  , &srcTest_ObjectJc, &srcTestMain_ObjectJc
  , makesh = makesh);                                                                
  
  <+makesh><:>
  echo ==== execute the test ====                  
  build/<&dbgOut>/emCBase_.test.exe 1> build/result/<&dbgOut>.out 2> build/result/<&dbgOut>.err
  echo ==== Test cases ==========
  cat build/result/<&dbgOut>.out
  echo
  echo ==== Test failures =======
  cat build/result/<&dbgOut>.err
  echo
  echo ==========================
  <.><.+>
  
  makesh.close();
  Obj fMake = new java.io.File(sMake);
  fMake.setExecutable(true);   ##for linux, chmod to executable
  ##currdir = "build";
  checkDeps.writeDependencies();
  checkDeps.close();
  <+out>success generate <&sMake><.+n>
}





##Compilation, Link and Test routine called also from the gradle task.
sub build_DbgBheap(String dbgOut, String cc_def) {
  
  <+out>Generates a file build/make_test_emC.sh for compilation and start test ... <.+n>
  
  Obj checkDeps = new org.vishia.checkDeps_C.CheckDependencyFile(console, 1);
  checkDeps.setDirObj(<:>build/<&dbgOut>/*.o<.>);
  checkDeps.readCfgData("src/test/ZmakeGcc/All_Test/cfgCheckDeps.cfg", File: <:><&currdir><.>);
  checkDeps.readDependencies(<:>build/<&dbgOut>/deps.txt<.>);
  <+out><:n>checkDeps_C: build/<&dbgOut>/deps.txt read successfully<.+n>
  
  <+makeAll>build/make_<&dbgOut>.sh<.+n>
  String sMake = <:><&currdir>/build/make_<&dbgOut>.sh<.>;
  Openfile makesh = sMake;
  <+makesh># call of compile, link and execute for Test emC_Base with gcc<:n><.+>
  <+makesh><:>
  if test -f make_<&dbgOut>.sh; then cd ..; fi  #is in build directory, should call from root
  if ! test -d build/result; then mkdir build/result; fi
  rm -f build/<&dbgOut>/gcc*.txt
  #rm -r Debug  #for test
  #gcc --help > gcc.hlp.txt
  echo <&dbgOut>: Compile with <&cc_def> 1> build/<&dbgOut>/gcc_err.txt
  echo <&dbgOut>: Compile with <&cc_def>
  <.><.+>
  
  zmake <:>build/<&dbgOut>/*.o<.> := cppCompile( &c_src_emC_core
  , &c_src, &src_Base_emC_BlockHeap, &src_Ctrl_emC
  , &src_Base_emC_NumericSimple, &src_OSALgcc
  , &srcTest_ObjectJc
  , &srcTest_Exception
  , &srcTestStmEv
  , &test_Ctrl_emC
  , &srcTestBlockHeap
  , cc_def = cc_def, makesh = makesh
  , checkDeps = checkDeps
  );
  zmake <:>build/<&dbgOut>/*.o<.> := cppCompile(&srcTestMain_All
  ,cc_def = <:><&cc_def> -D DEF_TESTALL_emC <.>
  , makesh = makesh, checkDeps = checkDeps
  );
  
  //This is the comprehensive test project.
  zmake <:>build/<&dbgOut>/emCBase_.test.exe<.> := ccLink(&c_src_emC_core
  , &c_src, &src_Base_emC_BlockHeap, &src_Ctrl_emC
  , &src_Base_emC_NumericSimple, &src_OSALgcc
  , &srcTest_ObjectJc
  , &srcTest_Exception
  , &srcTestStmEv
  , &test_Ctrl_emC
  , &srcTestBlockHeap
  , &srcTestMain_All
  , makesh = makesh);
  
  <+makesh><:>
  echo ==== execute the test ====                  
  build/<&dbgOut>/emCBase_.test.exe 1> build/result/<&dbgOut>.out 2> build/result/<&dbgOut>.err
  echo ==== Test cases ==========
  cat build/result/<&dbgOut>.out
  echo
  echo ==== Test failures =======
  cat build/result/<&dbgOut>.err
  echo
  echo ==========================
  <.><.+>
  
  makesh.close();
  Obj fMake = new java.io.File(sMake);
  fMake.setExecutable(true);   ##for linux, chmod to executable
  ##currdir = "build";
  
  <+out>executes the build/make_test_emC.sh, firstly compile all (silent, a few seconds)
  then start the executable to test<.+n>
  ##Stringjar outtest;
  ##outtest += cmd sh -c pwd ;
  ##outtest += cmd sh -c build/make_test_emC.sh ;
  ##<+out><&outtest><.+n>
  checkDeps.writeDependencies();
  checkDeps.close();
  <+out>success generate <&sMake><.+n>
}



##
##Creates a snippet in the output file for compiling all sources with gcc:
##
sub cppCompile ( Obj target:org.vishia.cmd.ZmakeTarget, String cc_def, Obj makesh, Obj checkDeps ) {
  for(c_src1: target.allInputFilesExpanded()) {
    ##The checkDeps algorithm itself may be unnecessary for compilation for compilation of all files.
    ##but it creates the obj directory tree which is necessary for compilation.
    ##The checkDeps checks whether the file is changed, delete the obj file on changed file.
    Obj infoDeps = checkDeps.processSrcfile(File: &c_src1.file(), c_src1.localfile());
    <+out><&infoDeps><.+n> ##show state, info and file name on console.
    <+makesh><: >
    <:>
    echo ==== g++ <&c_src1.localfile()> 1>> <&target.output.localdir()>/gcc_err.txt
    if ! test -e <&target.output.localdir()>/<&c_src1.localname()>.o; then
      ##mkdir -p <&target.output.localdir()>/<&c_src1.localdir()>
      g++ <&cc_options> -Wa,-adhln <&cc_def> <&inclPath> -o <&target.output.localdir()>/<&c_src1.localname()>.o <&c_src1.file()> 1>> <&target.output.localdir()>/<&c_src1.localname()>.lst 2>> <&target.output.localdir()>/gcc_err.txt 
      if test ! -e <&target.output.localdir()>/<&c_src1.localname()>.o; then 
        echo c++ ERROR: <&c_src1.localfile()>
        echo ERROR: <&c_src1.localfile()> >> gcc_nocc.txt; 
      else
        echo c++ ok: <&c_src1.localfile()>
      fi
    else
      echo exist: <&c_src1.localfile()>
    fi  
    <.><.+>
  }
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

