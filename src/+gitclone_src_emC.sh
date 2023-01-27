version="2022-04-25"
dstdir="src_emC"  
echo this shell script gets the $dstdir core sources of emC
echo if not exists $dstdir: clone https://github.com/JzHartmut/src_emC.git
cd `dirname $0`  ##script directory as current
if ! test -d $dstdir; then
  ##echo for the present clone the src_emC with tag "$version" as 'detached head':
  git clone https://github.com/JzHartmut/src_emC.git -b $version $dstdir
  ##git clone https://github.com/JzHartmut/src_emC.git $dstdir
  cd $dstdir
  pwd
  ## touch all files with the timestamp in emC.filelist:
  src_emC/+adjustTimestamps.sh
else 
  echo $dstdir already exists, not cloned 
fi

