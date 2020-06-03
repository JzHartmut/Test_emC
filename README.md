# This git Archive contains test Sources for emC

## emC

emC is embedded multiplatform C. 

## directory organisation and sub modules

The dir tree is organized with gradle standard.

src/main/cpp/src_emC is a sub component, which should be cloned via
 
 src/main/cpp/+gitclone_src_emC.sh
 
The specified version is loaded, designated by the tag. It results in a "detouched HEAD", see git documentation.
It is possible to clone another version or change the version by "git checkout -b version"
 
 
## System dependencies

The system can be Windows or Linux.

On Windows MinGW or adquate should be installed to support sh.exe for unix shell scripts
and to offer the Gnu Compiler suite (gcc). 

Java as version JRE8 should be available. java as command line should be invoke JRE8.
If another version of java is installed as standard, 
the PATH of the system can be changed temporary or all scripts should be invoked
with a locally changed PATH environment setting.


## dependent content from internet

The +resolveDeps.sh reads from internet the libs/vishiaBase.jar. 
This file is necessary for generation of the generation scripts (Zmake, JZtxtcmd).

To load it, a "bill of material" file is used, see libs/bomVishiaJava.txt.
This file contains The URL and MD5 check codes also for the vishiaMinisys.jar.

The libs/vishisMinisys.jar is part of this distribution because it is need to initially load.
But its source and MD5 is contained in the libs/bomVishiaJava.txt too, for check of source.

The sub component src/main/cpp/src_emC is cloned too, with call of src/main/cpp/+gitclone_src_emC.sh. 

All content from internet do not loaded if they are existing already. 
It is only checked whether the directory and files exist, the content can be abbreviating (for experience).
It is changed by MD5 check Whether the file.jar in the libs/bomVishiaJava.txt are the correct ones.
But the user can use abbreviating files.

The user is responsible to the correctness of the sub component src/main/cpp/src_emC.
Use git to check the content. Remove this directory to clone again.   

## first build

The build can be done using a simple linux shell.

* call build.bat in MS-Windows. It calls -mkLinkBuildGradle.bat 
  which creates links for build and .gradle to %TMP% location. 
  It can be (recommended) a RAM-Disk-location to speed up and save the SSD-Hard-Disk.
  
* build.bat invokes build.sh after clean.  

* call build.sh in Linux, it creates symbolic links for build and .gradle to the /tmp location.
  
* call build_withGradle.bat to run build with gradle. Note: This is yet not elaborately used yet.  
  
build.sh calls +resolveDeps.sh, compiles all and starts a test.

## repeated build

You can manually remove the directories .gradle and build. Because they are links they can be simple removed.
Use +clean.bat respecitively +clean.exe to do so.

The temporary locations where cleaned if the linked directories are not existing, so it is a true clean.

## build results

* The build directory contains a make_test_emC.sh script which was used for compile. 
* The build/Debug directory contains obj files
* The build/emCBase.test.exe is the exectuable for test. If it is existing, all sources are well compiled and linked.
* gcc*.txt contains some warnings and maybe errors of compilation.

One can remove Debug any emCBase.test.exe and start make_test_emC.sh in the build directory to repeat the compilation.
Note that gcc respectively g++ should be available in the PATH. 

If the Compiler suite is not available, the make_test_emC.sh was generated but executed with errors. 

## Build organization

The generation of the build/make_test_emC.sh is controlled by 

 src/test/ZmakeGcc/All_Test/ZmakeGcc.jzTc.sh
 
This is a JZtxtcmd script which contains a Zmake approach. 

* All files are listed in some Fileset, some files are commented because they are not necessary for this build.
* All compiler options are obviously
* The compiler and linker command line arrengement is obviously

To check the dependencies the org.vishia.checkDeps_C.CheckDependencyFile can be used (yet not used, TODO)  

## What is tested

### Variants of build

Because of the emC source can be compiled with different approaches (variants, see [vishia/.../testStrategie_en](https://vishia.org/emcdocu/html5/TestOrg/testStrategie_en.html))
it compiles more as one emCBase_.test.exe in different directories.

...TODO


## Other projects to explore and use as templates

* Their are some Visual Studio Projects for special tests

(yet TODO)




## Libraries

Because of emC is not for a specific system, it is for embedded Control, 
theire is not a universal library. For usage under Windows (for test of sources
for embedded Control) theire is a project src/mklib/VS15-IDE/libMsc15_emC.sln
for Microsoft visual Studio 15. It can be adapted to newer versions as working version.



