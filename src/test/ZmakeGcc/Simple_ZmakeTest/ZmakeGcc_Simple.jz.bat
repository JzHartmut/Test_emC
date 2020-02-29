@echo off
call +mklink_builds.bat
::rmdir /S/Q build\Debug
::del build\hellotest.exe
call JZtxtcmd.bat %0
pause  
cd build
call make.bat
type gcc_err.txt
type ld_err.txt
pause
echo TEST hellotest.exe:
hellotest.exe
echo END TEST 
pause
exit /B                                      
                                                                   
==JZtxtcmd==

currdir=<:><&scriptdir>/../../..<.>;
text = <:><&scriptdir>/build/make.bat<.>;

String inclPath = "";

//String cc_options = "-O0 -g3 -Wall -c -fmessage-length=0";
String cc_options = "-O0 -Wall -c";

String cc_def = "-DDEF_DEVELOPER_TEST";

Fileset c_src = 
( hello.c
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




String xlibs = <:>-Lc:/Programs/MinGW/lib/gcc/mingw32/5.3.0 <: >
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
  

  zmake "build/*.o" := ccCompile(&c_src);
  zmake "build/hellotest.exe" := ccLink(&c_src);
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
    if not exist Debug\<&c_src1.localnameW()>.o g++ <&cc_options> <&cc_def> <&inclPath> -o Debug/<&c_src1.localname()>.o ../<&c_src1.file()> 1>>gcc_out.txt 2>>gcc_err.txt
    if not exist Debug\<&c_src1.localnameW()>.o echo <&c_src1.localfile()> >>gcc_nocc.txt
    <.>
  }
}  


##
##Creates a snippet in the output file for linking all sources with gcc:
##
sub ccLink(Obj target:org.vishia.cmd.ZmakeTarget) {
  <:>
  g++ -o "hellotest.exe"<.> 
  for(c_src1: target.allInputFilesExpanded()) {
    <:> Debug/<&c_src1.localname()>.o<.>
  }
  <:> <&libs> 1>ld_out.txt 2>ld_err.txt
  <.>
}  

