echo this shell script gets the src_emC core sources of emC
echo if not exists src_emC: clone https://github.com/JzHartmut/src_emC.git
cd `dirname $0`  ##script directory as current
if ! test -d src_emC; then
  git clone https://github.com/JzHartmut/src_emC.git
  cd src_emC
  pwd
  echo touch all files with the timestamp in emC.filelist:
  java -cp ../../../../downloaded/jars/vishiaBase.jar org.vishia.util.FileList T -l:emC.filelist -d:.
else 
  echo src_emC already exists, not cloned 
fi

