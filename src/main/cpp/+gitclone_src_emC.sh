echo this shell script gets the src_emC core sources of emC
echo if not exists src_emC: clone https://github.com/JzHartmut/src_emC.git
cd `dirname $0`  ##script directory as current
version_src_emC="2021-08-15"
if ! test -d src_emC; then
  ##echo for the present clone the src_emC with tag "$version_src_emC" as 'detached head':
  git clone https://github.com/JzHartmut/src_emC.git -b $version_src_emC
  ##git clone https://github.com/JzHartmut/src_emC.git
  cd src_emC
  pwd
  echo touch all files with the timestamp in emC.filelist:
  #this file is part of test_emC, hence the .../libs exists:
  java -cp ../../../../libs/vishiaBase.jar org.vishia.util.FileList T -l:emC.filelist -d:.
else 
  echo src_emC already exists, not cloned 
fi

