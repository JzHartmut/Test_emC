echo off
REM hint: this file is able to use as template for all Visual Studio Projects
set NAMEWS=IDE\VS15\AllTest_emC_Base
cd %~d0%~p0\..\..\..\..\..
echo cleans and creates a directory %NAMEWS% beside the src tree
echo as Workspace for the Project.
echo the Workspace can always removed again, contains only temp files.
echo All real sources are linked to the src tree beside.
if not exist src\main\%NAMEWS%\+createWorkPrj.bat (
  echo ERROR not found: src\main\%NAMEWS%\+createWorkPrj.bat: faulty path
  cd
  if not "%1" == "NOPAUSE" pause
  exit /B
)
if exist %NAMEWS% (
  echo WARNING exists: %CD%\%NAMEWS%
  echo will be deleted, press abort ctrl-C to exit
  if not "%1" == "NOPAUSE" pause
  rmdir /S/Q %NAMEWS%
)
mkdir %NAMEWS%
cd %NAMEWS%
echo creates a so named hard link, the files are the same as in this original directory
mklink /H AllTest_emC_Base.vcxproj ..\..\..\src\main\%NAMEWS%\HlinkFiles\AllTest_emC_Base.vcxproj
mklink /H AllTest_emC_Base.vcxproj.filters ..\..\..\src\main\%NAMEWS%\HlinkFiles\AllTest_emC_Base.vcxproj.filters
mklink /H AllTest_emC_Base.sln ..\..\..\src\main\%NAMEWS%\HlinkFiles\AllTest_emC_Base.sln
mklink /H +clean_mklink_builds.bat ..\..\..\src\main\%NAMEWS%\HlinkFiles\+clean_mklink_builds.bat
mklink /H +clean.bat ..\..\..\src\main\%NAMEWS%\HlinkFiles\+clean.bat
mklink /H .editorconfig ..\..\..\src\main\%NAMEWS%\HlinkFiles\.editorconfig
REM only project specific sources:
mklink /J applstdef_CppObj ..\..\..\src\main\%NAMEWS%\applstdef_CppObj
mklink /J applstdef_C1 ..\..\..\src\main\%NAMEWS%\applstdef_C1
call +clean_mklink_builds.bat
dir
if not "%1" == "NOPAUSE" pause

