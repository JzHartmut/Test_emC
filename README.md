# This git Archive contains test Sources for emC

## emC

emC is embedded multiplatform C/C++. 

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


For more information 

* read [vishia.org/emc/html/GitTestEnv_en](https://vishia.org/emc/html/TestOrg/GitTestEnv_en.html))

* and [vishia.org/emc/html/testStrategie_en](https://vishia.org/emc/html/TestOrg/testStrategie_en.html))

Refer the web page: [vishia.org/emc](https://vishia.org/emc)
