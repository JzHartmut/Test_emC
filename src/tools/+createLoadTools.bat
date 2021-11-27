echo off
cd %~d0%~p0\..\..
echo creates and loads the tools if Workingtree/tools beside .../src is not existing
if not exist src\tools\+createLoadTools.bat (
  echo ERROR not found: src\tools\+createLoadTools.bat: faulty path
  cd
  if not "%1" == "NOPAUSE" pause
  exit /B
)
if exist .\tools (
  echo tools exists, nothing done. Maybe check the files manually
  if not "%1" == "NOPAUSE" pause
  exit /B
)
mkdir tools
cd tools
echo creates a so named hard link, the files are the same as in this original directory
mklink /H vishiaMinisys.jar ..\src\tools\HlinkFiles\vishiaMinisys.jar
mklink /H tools.bom ..\src\tools\HlinkFiles\tools.bom
mklink /H +load.bat ..\src\tools\HlinkFiles\+load.bat
mklink /H +load.sh ..\src\tools\HlinkFiles\+load.sh
call +load.bat
dir
if not "%1" == "NOPAUSE" pause

