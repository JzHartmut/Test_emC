set CP="tools/vishiaGui.jar;tools/vishiaBase.jar;tools/org.eclipse.swt.win32.x86_64.jar"                                                    
set JAVAW=javaw
cd ..\..\..
echo dir=
cd
REM call the GUI. This file %0 is used as argument for SimSelector. It contains all control after the JZtxtcmd label
echo $JAVAW -cp $CP org.vishia.simSelector.StimuliSelector src/test/ZmakeGcc/test_Selection.jztsh -size:C 
%JAVAW% -cp %CP% org.vishia.stimuliSelector.StimuliSelector src/test/ZmakeGcc/test_Selection.jztsh -size:C
::#::1>%LOGDIR%\log.txt 2>%LOGDIR%\err.txt
echo xxx
if test $? -ge 1; then
  cat /tmp/err.txt
  read -n1 -r -p "Press any key to continue..."
fi  

::#@echo off
::#::type %LOGDIR%\err.txt
::#::if errorlevel 1 pause
::#REM exit /b means, the console window remain open though this called batch will be finished. exit pure closes the console.
::#exit /b 
exit /b

                                       
