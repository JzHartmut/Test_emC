echo ==== pure shell script solution to remove all directories except .git 
echo find . -maxdepth 1 -type d -not -name .git -not -name . -exec rm -r "{}" \;
find . -maxdepth 1 -type d -not -name .git -not -name . -exec rm -r "{}" \;
##echo ==== Executes script only to delete all dirs except .git and maybe some files
##~/cmds/jztxtcmd.sh $0
ls
read -n1 -r -p "Press any key to continue..."
echo ==== checkout newly the current version of git, overwrite also the files on local root position
echo git checkout --force --progress
git checkout --force
ls
echo ==== FileList sets the time stamp of all files due to the list ...
read -n1 -r -p "Press any key to continue..."
## -d:. as current directory
~/cmds/javavishia.sh org.vishia.util.FileList T -d:. -l:.filelist

exit

==JZtxtcmd==

currdir=scriptdir;

Fileset dirs =
( zbnfjax
, target
);

main()
{
  Obj dirs = currdir.listFiles();
  for(dir: dirs){
    if(dir.isDirectory()) {
      String sdir = dir.toString();
      ##<+out><&dir>!!!!!<.+n>
      if(!sdir.endsWith(".git")) {           ## remove all dirs exclusively .git
        <+out>cleans <&dir><.+n>
        FileSystem.rmdir(dir);
      }
    }                                        ## don't remove files, (handle manually)
  }                         
##  cmd git checkout --force;
##  Obj filelist = File: .filelist; 
##  String sFilelist = filelist.getAbsolutePath(); 
##  java org.vishia.util.FileList.touch(sFilelist, null, null);
}

