cd ../../../..
java -jar libs/vishiaBase.jar src/test/ZmakeGcc/All_Test/ZmakeGcc.jzTc.sh                                                                                          
exit 0                                      
                                                                   
==JZtxtcmd==

##currdir=<:><&scriptdir>/../../../..<.>;

String inclPath =  ##from position of the generated make.cmd file 
<:>-Isrc/main/cpp/src_emC/emC_inclApplSpec/TargetNumericSimple <: >
-Isrc/main/cpp/src_emC/emC_inclComplSpec/cc_Gcc <: >
-Isrc/test/cpp <: >
-Isrc/main/cpp/src_emC<.>;

//String cc_options = "-O0 -g3 -Wall -c -fmessage-length=0";
String cc_options = "-O0 -Wall -c";
                                     
String cc_defSimple = "-D DEF_TESTALL_emC";

String cc_defBHeap = "-D DEF_TESTALL_emC -D USE_BlockHeap_emC";

##Note: All commented files are not necessary for the current test,
##They are some Problems in Linux-Gcc compilation, it is TODO

Fileset c_src = 
( src/main/cpp/src_emC:emC/Base/Assert_emC.c
, src/main/cpp/src_emC:emC/Base/CheckStack_emC.c
##, src/main/cpp/src_emC:emC/Base/DefPortTypes_emC.c
, src/main/cpp/src_emC:emC/Base/Event_emC.c           
##, src/main/cpp/src_emC:emC/Base/Formatter_emC.c  ##Linux problems with stdarg
, src/main/cpp/src_emC:emC/Base/Handle_ptr64_emC.c
, src/main/cpp/src_emC:emC/Base/Handle_ptr64_TimeMeas_emC.c
##, src/main/cpp/src_emC:emC/Base/LogMessage_emC.c
##, src/main/cpp/src_emC:emC/Base/LogMsgStream_emC.c
, src/main/cpp/src_emC:emC/Base/MemC_emC.c
, src/main/cpp/src_emC:emC/Base/Memfree_ThreadAndBlockHeap.c
, src/main/cpp/src_emC:emC/Base/Object_emC.c
, src/main/cpp/src_emC:emC/Base/ObjectJcpp_emC.cpp
, src/main/cpp/src_emC:emC/Base/Object_RAMclass_emC.c
, src/main/cpp/src_emC:emC/Base/os_common.c
, src/main/cpp/src_emC:emC/Base/ParseArgs_emC.c
, src/main/cpp/src_emC:emC/Base/Readline_emC.c
, src/main/cpp/src_emC:emC/Base/ReflectionBaseTypes_emC.c                
, src/main/cpp/src_emC:emC/Base/Reflection_emC.c
, src/main/cpp/src_emC:emC/Base/SimpleC_emC.c
, src/main/cpp/src_emC:emC/Base/StringBase_emC.c
##, src/main/cpp/src_emC:emC/Base/StringBuilder_emC.c
, src/main/cpp/src_emC:emC/Base/StringCompactor_emC.c
, src/main/cpp/src_emC:emC/Base/String_emC.c
, src/main/cpp/src_emC:emC/Base/Timeconversions_emC.c
, src/main/cpp/src_emC:emC/Base/Time_emC.c
##, src/main/cpp/src_emC:emC/Base/VaArgBuffer_emC.c

, src/main/cpp/src_emC:emC/Test/testAssert.cpp
, src/main/cpp/src_emC:emC/Test/testAssert_C.c


, src/main/cpp/src_emC:emC/StateM/StateFnCall_StateM_emC.c
, src/main/cpp/src_emC:emC/StateM/evQueue.c


, src/main/cpp/src_emC:emC_srcOSALspec/hw_Intel_x86_Gcc/os_atomic.c

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
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ExcNoStringStacktrcNo_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/fw_ThreadContextSimpleIntr.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/osal_FatalErrorPrintf_while0.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/stopAssert_Fwc_while0.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextInterrTpl.c
##, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextSimpleFromOsal.c
, src/main/cpp/src_emC:emC_srcApplSpec/SimpleNumCNoExc/ThreadContextSingle_emC.c

##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ApplThrowOnFatalError_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ExceptionPrintStacktrace_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/Exception_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ExcThCxtStacksize.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/LogException_emC.c
, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ObjectJc_allocStartup_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/os_endian_x86.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/RemoteCpu_Dummy.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/ThreadContextUserBuffer_emC.c
##, src/main/cpp/src_emC:emC_srcApplSpec/applConv/UmlContainer_Dummy.c

);


##This Fileset should be used only if the Blockheap concept is integrated in test files.
##Alternatively always emC_srcApplSpec/applConv/ObjectJc_allocStartup_emC.c is compiled,
##                     but this file is empty by compiler switch USE_BlockHeap_emC
Fileset src_Base_emC_BlockHeap = 
( src/main/cpp/src_emC:emC/BlockHeap/BlockHeapJc_Alloc.c
);






##
##The files for test of all
##
Fileset c_srcTest = 
( src/test/cpp:org/vishia/emC/Base/test_ObjectJc/testAll_ObjectJcpp_emCBase.cpp
, src/test/cpp:org/vishia/emC/Base/test_ObjectJc/test_ObjectJcpp.cpp
, src/test/cpp:org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.cpp
, src/test/cpp:org/vishia/emC/StateM/test_StateM/testEventQueue.cpp
, src/test/cpp:org/vishia/emC/StateM/test_StateM/testStateFncall_StateMemCBase.c
, src/test/cpp:org/vishia/emC/StateM/test_StateM/tplGen_StateFncall_StateMemCBase.c
, src/test/cpp:emC_Test_C_Cpp/TestVtblExplicit.cpp
, src/test/cpp:emC_BlockHeapTest/BlockHeapTest_emC.cpp
, src/test/cpp:emC_TestAll/testmain.cpp
);
                                                                      

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

main() {
  call test_emC();
}

##Compilation, Link and Test routine called also from the gradle task.
sub test_emC() {
  
  <+out>Generates a file build/make_test_emC.sh for compilation and start test ... <.+n>
  String sMake = <:><&currdir>/build/make_test_emC.sh<.>;
  Openfile makesh = sMake;
  <+makesh># call of compile, link and execute for Test emC_Base with gcc<:n><.+>
  <+makesh><:>
  if test -d build; then cd build; fi  #if invoked with build/make...sh
  rm -f gcc*.txt
  #rm -r Debug  #for test
  gcc --help > gcc.hlp.txt
  <.><.+>
  
  String cc_def = cc_defBHeap;
  zmake "build/*.o" := ccCompile(&c_src, cc_def = cc_def, makesh = makesh);
  zmake "build/*.o" := ccCompile(&src_Base_emC_NumericSimple, cc_def = cc_def, makesh = makesh);
  zmake "build/*.o" := ccCompile(&src_Base_emC_BlockHeap, cc_def = cc_def, makesh = makesh);
  zmake "build/*.o" := ccCompile(&c_srcTest, cc_def = cc_def, makesh = makesh);
  zmake "emCBase.test.exe" := ccLink(&c_src, &src_Base_emC_BlockHeap, &src_Base_emC_NumericSimple, &c_srcTest, makesh = makesh);
  makesh.close();
  Obj fMake = new java.io.File(sMake);
  fMake.setExecutable(true);   ##for linux, chmod to executable
  ##currdir = "build";
  
  <+out>executes the build/make_test_emC.sh, firstly compile all (silent, a few seconds)
  then start the executable to test<.+n>
  Stringjar outtest;
  outtest += cmd sh -c pwd ;
  outtest += cmd sh -c build/make_test_emC.sh ;
  <+out><&outtest><.+n>
  <+out>success<.+n>
}



##
##Creates a snippet in the output file for compiling all sources with gcc:
##
sub ccCompile(Obj target:org.vishia.cmd.ZmakeTarget, String cc_def, Obj makesh) {
  for(c_src1: target.allInputFilesExpanded()) {
    ##Note: all relativ paths from position of the makesh file
    <+makesh><:>
    echo cc <&c_src1.localfile()>
    if ! test -e Debug/<&c_src1.localname()>.o; then
      mkdir -p Debug/<&c_src1.localdir()>
      g++ <&cc_options> <&cc_def> <&inclPath> -o Debug/<&c_src1.localname()>.o <&c_src1.file()> 1>> gcc_out.txt 2>> gcc_err.txt 
      if test ! -e Debug/<&c_src1.localname()>.o; then echo error: <&c_src1.localfile()> >> gcc_nocc.txt; fi
    fi  
    <.><.+>
  }
}  


##
##Creates a snippet in the output file for linking all sources with gcc:
##
sub ccLink(Obj target:org.vishia.cmd.ZmakeTarget, Obj makesh) {
  <+makesh><:>
  if test -e <&target.output.localfile()>; then rm -f test.exe; fi
  g++ -o <&target.output.localfile()><.><.+> 
  for(c_src1: target.allInputFilesExpanded()) {
    <+makesh> Debug/<&c_src1.localname()>.o<.+>    
  }
  <+makesh><: >
  <:> <&libs> 1> ld_out.txt 2> ld_err.txt            
  echo view gcc_err.txt and ld_err.txt for warnings or errors if the test does not run.                                     
  #type gcc_err.txt
  #type ld_err.txt
  #pause
  echo ==== execute the test ====                  
  ./<&target.output.localfile()> 1> test.out 2> test.err
  echo ==== Test cases ==========
  cat test.out
  echo
  echo ==== Test failures =======
  cat test.err
  echo
  echo ==========================
  #pause
  <.><.+>
}  

