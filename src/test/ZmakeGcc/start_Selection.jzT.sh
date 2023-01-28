##not necessary because unix_script.bat is used anycase: call ..\..\..\src\buildScripts\-setEnv.bat test_Selection.jzT.cmd
#@echo off
#REM invoke from current dir, where this file is stored.
#SET LOGDIR=%CD%\test_Selection_Log_deleteMe
#if not exist %LOGDIR% mkdir %LOGDIR% 
#REM invokes the stimuli selection GUI
#REM Decision which SWT library should be used depends on the java version 32 or 64, not on the Operation System.
#::set SWTJAR=org.eclipse.swt.win32.win32.x86_3.5.1.v3555a.jar  ##for Win32
if test "$OS" = "Windows_NT"; then ##Win64
  CP="tools/vishiaGui.jar;tools/vishiaBase.jar;tools/org.eclipse.swt.win32.x86_64.jar"
  JAVAW=javaw
else
  CP="tools/vishiaGui.jar:tools/vishiaBase.jar:tools/swt.linux.x86_64.jar"
  JAVAW=java
fi
#REM if javaw is used, the console window remain open but can be closed manually independent of the java run.
#REM The >out and >err can be used. If start is used here, >out and >err do not work. 
#REM Then no information is given on faulty conditions, especially missing jars.
#REM Therefore 'start' cannot be used here.
#REM write out the command line to help explore the starting conditions on faulty situation:
#@echo on  
cd `dirname "$0"`/../../..
#call -setEnv.bat
echo dir=
pwd
#REM call the GUI. This file %0 is used as argument for SimSelector. It contains all control after the JZtxtcmd label
echo $JAVAW -cp $CP org.vishia.stimuliSelector.StimuliSelector src/test/ZmakeGcc/test_Selection.jztsh -size:C 
##Note: The script while will be left open (it is locked) by the shell (bash). Hence extra file yet.
$JAVAW -cp $CP org.vishia.stimuliSelector.StimuliSelector src/test/ZmakeGcc/test_Selection.jztsh -size:C & ## 2 > /tmp/err.txt ;
#::1>%LOGDIR%\log.txt 2>%LOGDIR%\err.txt
echo xxx
if [$? -ge 1]; then
  cat /tmp/err.txt
  read -n1 -r -p "Press any key to continue..."
fi  

#@echo off
#::type %LOGDIR%\err.txt
#::if errorlevel 1 pause
#REM exit /b means, the console window remain open though this called batch will be finished. exit pure closes the console.
#exit /b 
exit


