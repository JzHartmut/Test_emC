#TMP should be exist propably under WIndows, it may exist under linux
#Test whether it is Windows or Linux, mklink or ln are different
if test -d build; then  ## -a -d .gradle ##and does not run ??
  ##if build exists, it was executed already after first clone or copy.
  echo links exist                ##do nothing else
else   
  ##The next lines are useful only in linux.
  ##For windows via -mkLinkBuildGradle.bat on start of build.bat build should be exist
  ##
  ##The TMP shell variable should be exist, else create it.
  if test "$TMP" = ""; then export TMP="/tmp"; fi    ##/tmp should be ok on Linux
  ##Clean existing sub directories because build is not existing.
  ##It does not remove files after a link, especially build/src
  ##Works too in Windows via sh.exe 
  if test -d $TMP/Test_emC/build; then 
    ##remove only the symbolic link src, 
    ##Attention: on using -r all src/files are removed, catastrophic
    ##not necessary: if test -d src; then rm $TMP/Test_emC/build/src; fi
    ##do not do it: rm -r $TMP/Test_emC/build; ##All other can be removed recursively.
    rm -f -r $TMP/Test_emC/build
  fi
  if ! test -d .gradle && test -d $TMP/Test_emC/.gradle; then 
    rm -r $TMP/Test_emC/.gradle; 
  fi
  ##Create the necessary sub directories in $TMP before link it
  mkdir -p $TMP/Test_emC/build;
  mkdir -p $TMP/Test_emC/.gradle;
  if test "$OS" = "Windows_NT"; then
    ##Unfortunately links in Linux and Windows can not be handled equal:
    ##call windows batch from sh.exe script in Windows, its ok
    ##Use cmd.exe to execute as windows batch, elsewhere it is handled as shell script
    cmd.exe /C ./-mkLinkBuildGradle.bat
    ##does not run, because \\ is unfortunately translated to / 
    ##./mkLink.bat $TMP\\Test_emC\\build build 
    ##./mkLink.bat $TMP\\Test_emC\\gradle .gradle
    ##does not run:
    ##cmd.exe /C mklink /J build %TMP%\Test_emC_build
  else  
    ##do it firstly after clone from git or copy, the file properties will be retained
    chmod -R 777 *.sh          ##all *.sh are executable (for all)
    ##create some symbolic linked directories
    ln -s $TMP/Test_emC/build build
    ln -s $TMP/Test_emC/.gradle .gradle  ##Note .gradle is the required directory
    ##create src inside build, link to sources because necessary for compiler
    ln -s $PWD/src build/src   
  fi
fi

