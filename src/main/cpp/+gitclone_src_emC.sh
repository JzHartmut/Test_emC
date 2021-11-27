version="2021-08-31"
dstdir="src_emC"  
echo this shell script gets the $dstdir core sources of emC
echo if not exists $dstdir: clone https://github.com/JzHartmut/src_emC.git
cd `dirname $0`  ##script directory as current
if ! test -d $dstdir; then
  ##echo for the present clone the src_emC with tag "$version" as 'detached head':
  git clone https://github.com/JzHartmut/src_emC.git -b $version $dstdir
  ##git clone https://github.com/JzHartmut/src_emC.git srcvishia_emC
  cd $dstdir
  pwd
  echo touch all files with the timestamp in emC.filelist:
  #this file is part of test_emC, hence the .../libs exists:
  java -cp ../../../../tools/vishiaBase.jar org.vishia.util.FileList T -l:emC.filelist -d:.
else 
  echo $dstdir already exists, not cloned 
fi

