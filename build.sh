#linux shell call via sh.exe -c thisfile in Windows. sh.exe is part for example of MinGW or git distribution
#Java as JRE8 should be available.

if test "$OS" = "Windows_NT"; then
  echo windows
  ##problems between Unix-shell and windows: Backslash will be changed ...
  ##cmd.exe '/C -start4Win.bat Test\backslash'
else
  ##set all src/*.sh to executable for all, also in maybe symbolic linked folder of src
  ##Note: src may a symbolic link by itself by testing on second linux PC, 
  ##      while the src are used also on a windows PC. 
  ##      Copy src to /tmp in RAM  for fast access
  ##      (not using network connection, it is slower).
  ##do it firstly after clone from git or copy, the file properties will be retained
  find -L "src" -name '*.sh' -exec chmod 777 {} \;
  find -L "src" -name '*.jztsh' -exec chmod 777 {} \;
  ##NOTE -R only for all files in directory, does not run chmod -R 777 *.sh  
fi  


##compare files in lib, load missing from internet with the 'bill of material.txt' 
if ! test -d tools; then src/load_tools/+loadTools.sh; fi
if ! test -d build; then ./+clean_mkLinkBuild.sh; fi
if ! test -d src/src_emC; then src/+gitclone_src_emC.sh; fi

echo "==== run a simple check, check whether the compiler runs"
src/test/testScripts/testBasics_Simple.jzTc.sh

echo "==== evaluate test results:"
./src/test/testScripts/evalTests.jzTc.sh
read -n1 -r -p "Press any key to continue..."

#src/test/ZmakeGcc/All_Test/TestAllBase.jzTc.sh
#src/test/ZmakeGcc/All_Test/TestComplex.jzTc.sh

##The jzTc.cmd does the task of build and test:
#java -jar tools/vishiaBase.jar jzTc.cmd

