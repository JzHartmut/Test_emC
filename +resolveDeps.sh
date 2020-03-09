#linux shell call via sh.exe -c thisfile in Windows. sh.exe is part for example of MinGW or git distribution
#Java as JRE8 should be available.

if ! test -f downloaded/jars/vishiaBase.jar; then
  if ! test -d downloaded/jars; then mkdir -p downloaded/jars; fi 
  pwd
  echo java -cp libs/minisys_vishia.jar org.vishia.minisys.Wget https://www.vishia.org/Java/Download/versionArchive/vishiaBase-3.1.0.jar downloaded/jars/vishiaBase.jar
  java -cp libs/minisys_vishia.jar org.vishia.minisys.Wget https://www.vishia.org/Java/Download/versionArchive/vishiaBase-3.1.0.jar downloaded/jars/vishiaBase.jar
else 
  echo downloaded/jars/vishiaBase.jar exists, remove it to get the dedicated version. 
fi

if ! test -d src/main/cpp/src_emC; then
  ##The scr_emC is not part of the Test_emC.
  ##because of non-existing, the timestamps of this archive should be still touched:
  echo touch all files with the timestamp in .filelist:
  java -cp downloaded/jars/vishiaBase.jar org.vishia.util.FileList T -l:.filelist -d:.
  ##
  ##clone src_emC form git archive:
  src/main/cpp/+gitclone_src_emC.sh
else 
  echo src/main/cpp/src_emC exists already, check it. Timestamps of this should be correct.
fi
