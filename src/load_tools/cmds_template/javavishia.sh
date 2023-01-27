## This is the start script for JZtxtcmd execution in shell scripts (usable also on MS-Windows).
## It should be copied in a directory which is referenced by the Operation system's PATH
## or it should be copied to ~/cmds/jztxtcmd.sh
## and adapt with the paths to Java and the other tools.
## All what is need to run JZtxtcmd, it is referenced here. 
 
## The TMP variable may used by some scrips. Export it to a defined location if necessary:
## On MinGw in windows the /tmp directory seems to be the $TMP& environment variable value. 
export TMP="/tmp"

## Set the variable to refer the jar files to execute JZtxtcmd and all Java
## They should be found in local distance to this file. $(dirname $0) is the directory of this file.
## Or in any of the others. The first found location is used, 
export VISHIAJAR="C:/Programs/vishia/tools"       ## try first absolute location for windows
if ! test -f $VISHIAJAR/vishiaBase.jar; then
  export VISHIAJAR="$HOME/vishia/tools"           ## home location only usable for Linux
  if ! test -f $VISHIAJAR/vishiaBase.jar; then
#    export VISHIAJAR="$(dirname $0)/../../tools"    ## situation in a working tree in src/cmds/jztxtcmd.sh
#    if ! test -f $VISHIAJAR/vishiaBase.jar; then
#      export VISHIAJAR="$(dirname $0)/../vishia/tools"  ## situation in ~/cmds/jztxtcmd.sh
#      if ! test -f $VISHIAJAR/vishiaBase.jar; then  ##Note: the java cmd line needs windows-oriented writing style also in MinGW under Windows.
        echo problem tools for jar files not found
#      fi
#    fi
  fi
fi              
echo VISHIAJAR=$VISHIAJAR

## If necessary adapt the PATH for a special java version. Comment it if the standard Java installation should be used.
## Note Java does not need an installation. It runs well if it is only present in the file system.
## swt is the graphic adaption, different for Linux and Windows:
if test -d /C/Windows; then
  export JAVA_HOME="/c/Programs/Java/jre1.8.0_291"
  export SWTJAR="org.eclipse.swt.win32.x86_64.jar"
  JAVAPATHSEP=";"
else
  export JAVA_HOME="/usr/local/bin/JDK8"
  export SWTJAR="org.eclipse.swt.Linux.win32.x86_64.jar"
  JAVAPATHSEP=":"
fi
export PATH="$JAVA_HOME/bin$JAVAPATHSEP$PATH"
#echo PATH=$PATH

## adapt the path to the Xml-Tools. See zbnfjax-readme. 
## The XML tools are necessary for some XML operations. This environment variable may be used in some JZtxtcmd scripts. 
## Comment it if not used.
##export XML_TOOLS=C:\Programs\XML_Tools

## This is the invocation of JZtxtcmd, with up to 9 arguments.
echo Note: the java cmd line needs windows-oriented writing style also in MinGW under Windows.
echo java -cp $VISHIAJAR/vishiaBase.jar$JAVAPATHSEP$VISHIAJAR/vishiaGui.jar$JAVAPATHSEP$VISHIAJAR/$SWTJAR $1 $2 $3 $4 $5 $6 $7 $8 $9
java -cp $VISHIAJAR/vishiaBase.jar$JAVAPATHSEP$VISHIAJAR/vishiaGui.jar$JAVAPATHSEP$VISHIAJAR/$SWTJAR $1 $2 $3 $4 $5 $6 $7 $8 $9


