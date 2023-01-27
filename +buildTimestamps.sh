echo build the timestamp in .filelist from all files:
Filemask="[[result/**|src/[IDE*|buildScripts|cmds|docs|load_tools|test]/**]/[~#*|~*#]|~_*]"
currdir="$(dirname $0)"
if test -f $currdir/tools/vishiaBase.jar; then 
  java -cp $currdir/tools/vishiaBase.jar org.vishia.util.FileList L -l:$currdir/.filelist -d:$currdir "-m:$Filemask"
else  
  ~/cmds/javavishia.sh org.vishia.util.FileList L -l:$currdir/.filelist -d:$currdir "-m:$Filemask"
fi

