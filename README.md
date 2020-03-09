# This git Archive contains test Sources for emC

## emC

emC is embedded multiplatform C. 

## directory organisation and sub modules

The dir tree is organized with gradle standard.

src/main/cpp/src_emC is a submodule, which should be cloned via
 
 src/main/cpp/+gitclone_src_emC.sh
 
The submodule capability of git is not used! It is not useable. 

## System dependencies

The system can be Windows or Linux.

On Windows MinGW or adquate should be installed to support sh.exe for unix shell scripts
and to offer the Gnu Compiler suite (gcc). 

Java as version JRE8 should be available. java as command line should be invoke JRE8.
If another version of java is installed as standard, 
the PATH of the system can be changed temporary or all scripts should be invoked
with a locally changed PATH environment setting.


## build

The build can be done using gradle or using a simple linux shell.

* +resolveDeps.sh resolves all dependencies from Internet. 
  It can be invoked more as one time, but an internet access is only done if the components are missing.
  It is:
** downloaded/jars/vishiaBase.jar: Java-executables for organization and some source generate capabilities.
    (about 1 MByte Java-Archive).
** src/main/cpp/src_emC: The src_emC sub git archive is an external dependency too.

* build.sh calls +resolveDeps.sh, compiles all and starts a test.

## Libraries

Because of emC is not for a specific system, it is for embedded Control, 
theire is not a universal library. For usage under Windows (for test of sources
for embedded Control) theire is a project src/mklib/VS15-IDE/libMsc15_emC.sln
for Microsoft visual Studio 15. It can be adapted to newer versions as working version.



