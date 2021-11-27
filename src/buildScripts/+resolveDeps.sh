#linux shell call via sh.exe -c thisfile in Windows. sh.exe is part for example of MinGW or git distribution
#Java as JRE8 should be available.

#get depending files from internet, accept if they are existing already, but check MD5
#bom is the bill of material, what is gotten from wwww
#Note: vishiaMinisys.jar is part of this distribution because it is initially necessary, but the MD5 is checked.
if test -f +resolveDeps.sh; then cd ../..; fi
echo PWD = $PWD
echo
echo Resolve dependencies, check tools/bomVishiaJava.txt
java -cp tools/vishiaMinisys.jar org.vishia.minisys.GetWebfile @tools/bomVishiaJava.txt tools/


if ! test -d src/main/cpp/src_emC; then
  ##The scr_emC is not part of the Test_emC.
  ##because of non-existing, the timestamps of this archive should be still touched:
  echo touch all files with the timestamp in .filelist:
  java -cp tools/vishiaBase.jar org.vishia.util.FileList T -l:.filelist -d:.
  ##
  ##clone src_emC form git archive:
  src/main/cpp/+gitclone_src_emC.sh
else 
  echo src/main/cpp/src_emC exists already, check it. Timestamps of this should be correct.
fi
