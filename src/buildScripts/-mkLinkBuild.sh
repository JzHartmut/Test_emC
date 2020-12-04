#TMP should be exist propably under WIndows, it may exist under linux
#Test whether it is Windows or Linux, mklink or ln are different
if test -d ../../src/buildScripts; then cd ../..; fi
if test -d build; then  ## -a -d .gradle ##and does not run ??
  ##if build exists, it was executed already after first clone or copy.
  echo links exist                ##do nothing else
elif test "$OS" = "Windows_NT"; then
  ##Unfortunately links in Linux and Windows can not be handled equal:
  ##call windows batch from sh.exe script in Windows is not ok
  ##especially if $TMP will be used. $TMP is /tmp for the linux shell.
  ##It does not work in windows
  echo ERROR build directory should be created using +Clean_mkLinkBuild.bat in Windows
  echo it should be invoked manually.
  ##does not run because TMP: Use cmd.exe to execute as windows batch, elsewhere it is handled as shell script
  ##cmd.exe /K ++Clean_mkLinkBuild.bat
  ##does not run, because \\ is unfortunately translated to / 
  ##./mkLink.bat $TMP\\Test_emC\\build build 
  ##./mkLink.bat $TMP\\Test_emC\\gradle .gradle
  ##does not run:
  ##cmd.exe /C mklink /J build %TMP%\Test_emC_build
else   
  ##The next lines are useful only in linux.
  ##For windows via -+Clean_mkLinkBuild.bat on start of build.bat build should be exist
  ##
  ##The TMP shell variable should be exist, else create it.
  echo TMP=$TMP
  if test "$TMP" = ""; then export TMP="/tmp"; fi    ##/tmp should be ok on Linux
  echo TMP=$TMP
  if test -d $TMP/RAMd; then export BUILDD="$TMP/RAMd/Test_emC/build"
  else export BUILDD="$TMP/Test_emC/build"
  fi
  ##Clean existing sub directories because build is not existing.
  ##Works too in Windows via sh.exe 
  if test -d $BUILDD; then 
    rm -f -r $BUILDD
  fi
  ##Create the necessary sub directories in $TMP before link it
  mkdir -p $BUILDD;
  ##do it firstly after clone from git or copy, the file properties will be retained
  chmod -R 777 *.sh          ##all *.sh are executable (for all)
  ##create some symbolic linked directories
  ln -s $BUILDD build
fi

