REM remember the curretn dir because the batches changes it.
SET ROOTDIR=%CD%

REM The github contains only sources. To work firstly the tools should be linked and downloaded.
REM The next line creates a tools directory beside sources, copies or links tool "bill of material" files
REM and loads the tools from internet. It is only some jar files from the vishia page, see inside called batch. 
REM This can be done also manually starting the following batch:
call src\tools\+createLoadTools.bat
cd %ROOTDIR%

REM The next java call touches the timestamps of all files to the original one. 
REM The information about the timestamp is stored in the .filelist.
REM It is better to know the original time stamps (other than suggestion of some Linux Gurus)
echo touch all files with the timestamp in .filelist:
java -cp tools/vishiaBase.jar org.vishia.util.FileList T -l:.filelist -d:.

REM The first git clone https://github.com/JzHartmut/Test_emC.git does only load the test environment, tools
REM but not the second git repository for src_emC. But the following batch file is part of the first one,
REM loads the second archive and adjusts also the time stamp of all files:
"C:\Program Files\git\bin\sh.exe" src\main\cpp\+gitclone_src_emC.sh

REM The src contains an IDE for Visual Studio. But the working dir for the IDE should not be inside the src,
REM it should be beside. The main reason is, this working tree for visual Studio IDE contains many temporary stuff
REM which should not burden the src directory tree!
REM This can be done also manually starting the following batch:
call src\main\IDE\VS15\AllTest_emC_Base\+createWorkPrj.bat
cd %ROOTDIR%

REM to have an output directory for build, the following batch should be started.
REM It creates an directory in the %TMP% directory tree for build
REM and links it via mklink /J (so named junction) for Windows
call +clean_mkLinkBuild.bat

REM Now the compile and test scripts can be called. 
REM But it is presumed that you have installed gcc with cygwin or such.
REM You should have on your harddisk in the PATH the starting batch file for shell scripts via Cygwin.
REM If you connect the extension .sh with this batch file you should able to call all .sh scripts per double click.
REM If the following batch file is not in the PATH, you should care about it. 
REM See documentation https://www.vishia.org/emc/html/TestOrg/GitTestEnv_en.html#unix_script
cd src/test/testScripts
call unix_script.bat ./testBasics_Simple.jzTc.sh
cd %ROOTDIR%

REM it should have compiled and run the first test. 
pause
