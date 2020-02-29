@echo off
call +mklink_builds.bat
call JZtxtcmd.bat %0
pause  
cd build
call make.bat
type gcc_err.txt
type ld_err.txt
pause
test.exe
pause
exit /B                                      
                                                                   
==JZtxtcmd==

currdir=<:><&scriptdir>/../../../..<.>;
text = <:><&scriptdir>/build/make.bat<.>;

String inclPath = 
<:>-I../../../../main/cpp/org/vishia/emC/incApplSpecific/TargetNumericSimple <: >
-I../../../../main/cpp/org/vishia/emC/incComplSpecific/cc_Gcc <: >
-I../../../../test/cpp <: >
-I../../../../main/cpp/org/vishia<.>;

//String cc_options = "-O0 -g3 -Wall -c -fmessage-length=0";
String cc_options = "-O0 -Wall -c";

String cc_def = "-DDEF_DEVELOPER_TEST";

Fileset c_src = 
( org/vishia/emC/Base/Assert_emC.c
, org/vishia/emC/Base/CheckStack_emC.c
##, org/vishia/emC/Base/DefPortTypes_emC.c
, org/vishia/emC/Base/Event_emC.c
, org/vishia/emC/Base/Formatter_emC.c
, org/vishia/emC/Base/Handle_ptr64_emC.c
, org/vishia/emC/Base/Handle_ptr64_TimeMeas_emC.c
##, org/vishia/emC/Base/LogMessage_emC.c
##, org/vishia/emC/Base/LogMsgStream_emC.c
, org/vishia/emC/Base/MemC_emC.c
, org/vishia/emC/Base/Memfree_ThreadAndBlockHeap.c
, org/vishia/emC/Base/Object_emC.c
, org/vishia/emC/Base/Object_RAMclass_emC.c
, org/vishia/emC/Base/os_common.c
, org/vishia/emC/Base/ParseArgs_emC.c
, org/vishia/emC/Base/Readline_emC.c
, org/vishia/emC/Base/ReflectionBaseTypes_emC.c
, org/vishia/emC/Base/Reflection_emC.c
, org/vishia/emC/Base/SimpleC_emC.c
, org/vishia/emC/Base/StringBase_emC.c
##, org/vishia/emC/Base/StringBuilder_emC.c
##, org/vishia/emC/Base/StringCompactor_emC.c
, org/vishia/emC/Base/String_emC.c
, org/vishia/emC/Base/Timeconversions_emC.c
, org/vishia/emC/Base/Time_emC.c
##, org/vishia/emC/Base/VaArgBuffer_emC.c

, org/vishia/emC/Test/testAssert.cpp
, org/vishia/emC/Test/testAssert_C.c

, org/vishia/emC/sourceSpecials/hw_Intel_x86_Gcc/os_atomic.c

, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_endian.c
, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_error.c
, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_file.c
, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_mem.c
##, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_mutex.c
##, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_socket.c
##, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_sync.c
##, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_thread.c
, org/vishia/emC/sourceSpecials/os_LinuxGcc/os_time.c

, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ApplSimpleStop_emC.c
, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ExcNoStringStacktrcNo_emC.c
, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/fw_ThreadContextSimpleIntr.c
, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ObjectJcppSimple.cpp
##, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ObjectSimple_emc.c
##, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/osal_FatalErrorPrintf_while0.c
##, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/stopAssert_Fwc_while0.c
##, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ThreadContextInterrTpl.c
##, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ThreadContextSimpleFromOsal.c
, org/vishia/emC/sourceApplSpecific/SimpleNumCNoExc/ThreadContextSingle_emC.c



##, org/vishia/emC/sourceApplSpecific/applConv/ApplThrowOnFatalError_emC.c
##, org/vishia/emC/sourceApplSpecific/applConv/ExceptionPrintStacktrace_emC.c
##, org/vishia/emC/sourceApplSpecific/applConv/Exception_emC.c
##, org/vishia/emC/sourceApplSpecific/applConv/ExcThCxtStacksize.c
, org/vishia/emC/sourceApplSpecific/applConv/LogException_emC.c
, org/vishia/emC/sourceApplSpecific/applConv/ObjectJc_allocStartup_emC.c
##, org/vishia/emC/sourceApplSpecific/applConv/os_endian_x86.c
##, org/vishia/emC/sourceApplSpecific/applConv/RemoteCpu_Dummy.c
##, org/vishia/emC/sourceApplSpecific/applConv/ThreadContextUserBuffer_emC.c
##, org/vishia/emC/sourceApplSpecific/applConv/UmlContainer_Dummy.c


);

Fileset c_srcTest = 
( src/test/cpp:org/vishia/emC/Base/test_ObjectJc/testAll_ObjectJcpp_emCBase.cpp
, src/test/cpp:org/vishia/emC/Base/test_ObjectJc/test_ObjectJcpp.cpp
);


String libs = <:>-Lc:/Programs/MinGW/lib/gcc/mingw32/5.3.0 <: >
-Lc:/Programs/MinGW/lib <: >
-lgcc_s <: >     
-lgcc <: >       
-ladvapi32 <: >  
-lshell32 <: >   
-luser32 <: >    
-lkernel32 <: >  
<.>;


main() {

  <:>REM call of compile, link and execute for Test emC_Base with gcc<:n><.>
  <:>
  set PATH=c:\Programs\MinGW\bin;c:\Programs\MinGW\msys\1.0\bin\;%PATH%
  gcc --help >gcc.hlp.txt
  del /Q gcc*.txt
  <.>
  

  zmake "build/*.o" := ccCompile("src/main/cpp:"&c_src);
  zmake "build/*.o" := ccCompile(&c_srcTest);
  zmake "build/emCBase.test.exe" := ccLink("src/main/cpp:"&c_src, &c_srcTest);
  <+out>success<.+n>
}



##
##Creates a snippet in the output file for compiling all sources with gcc:
##
sub ccCompile(Obj target:org.vishia.cmd.ZmakeTarget) {
  for(c_src1: target.allInputFilesExpanded()) {
  
    <:>
    if not exist Debug\<&c_src1.localdirW()> mkdir Debug\<&c_src1.localdirW()>
    echo cc <&c_src1.localfile()>
    if not exist Debug\<&c_src1.localnameW()>.o g++ <&cc_options> <&cc_def> <&inclPath> -o Debug/<&c_src1.localname()>.o ../../../../../<&c_src1.file()> 1>>gcc_out.txt 2>>gcc_err.txt
    if not exist Debug\<&c_src1.localnameW()>.o echo <&c_src1.localfile()> >>gcc_nocc.txt
    <.>
  }
}  


##
##Creates a snippet in the output file for linking all sources with gcc:
##
sub ccLink(Obj target:org.vishia.cmd.ZmakeTarget) {
  <:>
  if exist test.exe del test.exe
  g++ -o "test.exe"<.> 
  for(c_src1: target.allInputFilesExpanded()) {
    <:> Debug/<&c_src1.localname()>.o<.>
  }
  <:> <&libs> 1>ld_out.txt 2>ld_err.txt
  <.>
}  

