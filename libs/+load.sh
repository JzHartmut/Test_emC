#linux shell call via sh.exe -c thisfile in Windows. sh.exe is part for example of MinGW or git distribution
#Java as JRE8 should be available.

#get depending files from internet, accept if they are existing already, but check MD5
#bom is the bill of material, what is gotten from wwww
#Note: vishiaMinisys.jar is part of this distribution because it is initially necessary, but the MD5 is checked.
SCRIPTDIR=$(dirname "$0")

java -cp $SCRIPTDIR/vishiaMinisys.jar org.vishia.minisys.GetWebfile @$SCRIPTDIR/bomVishiaJava.txt $SCRIPTDIR/


