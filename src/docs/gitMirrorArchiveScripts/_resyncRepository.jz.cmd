jztxtcmd.bat %0

==JZtxtcmd==

currdir=scriptdir;


main()
{
  call resyncRepository(); 
  
  <+out>success<.+n>

}


sub resyncRepository()
{
  Obj dirs = currdir.listFiles();
  for(dir: dirs){
    if(dir.isDirectory()) {
      String sdir = dir.toString();
      ##<+out><&dir>!!!!!<.+n>
      if(!sdir.endsWith(".git") && !sdir.equals("_organization")) {
        <+out>cleans <&dir><.+n>
        FileSystem.rmdir(dir);
      }
    }
  }
  ##cmd cmd.exe /C start cmd.exe /C gitc.bat checkout --force;
  cmd cmd.exe /C gitc.bat checkout --force;
  Obj filelist = File: emC.filelist; 
  String sFilelist = filelist.getAbsolutePath(); 
  java org.vishia.util.FileList.touch(sFilelist, null, null);
}
