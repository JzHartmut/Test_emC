echo touch all files with the timestamp in emC.filelist:
currdir="$(dirname $0)"
if test -f $currdir/tools/vishiaBase.jar; then 
  java -cp $currdir/tools/vishiaBase.jar org.vishia.util.FileList T -l:$currdir/.filelist -d:$currdir
else  
  ~/cmds/javavishia.sh org.vishia.util.FileList T -l:$currdir/.filelist -d:$currdir
fi
read -n1 -r -p "Press any key to continue..."

