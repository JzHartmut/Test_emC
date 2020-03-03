@echo off
call +mklink_builds.bat
call JZtxtcmd.bat %0
pause  
cd build
call make.bat
pause
exit /B                                      
                                                                   
==JZtxtcmd==
              
include cc.zmake.jzTc;

currdir=<:><&scriptdir>/../../..<.>;
text = <:><&scriptdir>/build/make.bat<.>;

String inclPath = 
<:>-I../../../main/cpp/org/vishia/emC/incApplSpecific/TargetNumericSimple <: >
-I../../../main/cpp/org/vishia/emC/incComplSpecific/cc_Gcc <: >
-I../../../test/cpp <: >
-I../../../main/cpp/org/vishia<.>;

Fileset includePath = 
( ../../../main/cpp/org/vishia/emC/incApplSpecific/TargetNumericSimple
, ../../../main/cpp/org/vishia/emC/incComplSpecific/cc_Gcc
, ../../../test/cpp
, ../../../main/cpp/org/vishia
);


String cc_options = 
 <:>/c /GS /TP /W3 /Zc:wchar_t <: >
 /ZI /Gm /Od /sdl /Fd"Debug\vc140.pdb" /Zc:inline /fp:precise <: >
 /D "DEF_REFLECTION_SIMPLE" /D "_MBCS" <: >
 /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /MDd <: >
 /EHsc /nologo <: >
 /I"c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include" <: >
 /I"c:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt" <: >
 <.>;
 
## /Fp"x64\Debug\ObjectJcpp_Test.pch" /Fa /Fo"x64\Debug\" 

String cc_def = "-DDEF_DEVELOPER_TEST";

Fileset c_src = 
( org/vishia/emC/Base/Assert_emC.c
, org/vishia/emC/Base/CheckStack_emC.c
##, org/vishia/emC/Base/DefPortTypes_emC.c
##, org/vishia/emC/Base/Event_emC.c           
, org/vishia/emC/Base/Formatter_emC.c
, org/vishia/emC/Base/Handle_ptr64_emC.c
, org/vishia/emC/Base/Handle_ptr64_TimeMeas_emC.c
##, org/vishia/emC/Base/LogMessage_emC.c
##, org/vishia/emC/Base/LogMsgStream_emC.c
, org/vishia/emC/Base/MemC_emC.c
, org/vishia/emC/Base/Memfree_ThreadAndBlockHeap.c
, org/vishia/emC/Base/Object_emC.c
, org/vishia/emC/Base/ObjectJcpp_emC.cpp
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



, org/vishia/emC/sourceSpecials/osal_Windows32/os_atomic.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_file.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_internal.h
, org/vishia/emC/sourceSpecials/osal_Windows/os_keyboard.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_mem.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_mutex.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_sharedmem.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_socket.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_sync.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_thread.c
, org/vishia/emC/sourceSpecials/osal_Windows/os_time.c




);




main() {

  <:>REM call of compile, link and execute for Test emC_Base with gcc<:n><.>
  <:>
  set PATH=c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\;c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64_x86;%PATH%
  gcc --help >gcc.hlp.txt
  del /Q gcc*.txt
  <.>
  

  zmake "build/**/*.o" := cc( "src/main/cpp:"&c_src
                         , compilerOptions = cc_options
                         , cfgCheckDeps = "../../mklib/VS15/cfgCheckDeps.cfg"
                         , srcDir = "src/main/cpp"
                         , objDir = "Debug"
                         , ccCmd = <:>"cl.exe"<.>
                         );
                         
  <:>
  goto :end
    :error 
    pause
  :end
  exit /B
  <.>
  <+out>success<.+n>
}




