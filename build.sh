#linux shell call via sh.exe -c thisfile in Windows. sh.exe is part for example of MinGW or git distribution
#Java as JRE8 should be available.

##set all *.sh to executable for all
##do it firstly after clone from git or copy, the file properties will be retained
find -name '*.sh' -exec chmod 777 {} \;
##NOTE -R only for all files in directory, does not runchmod -R 777 *.sh  

./+resolveDeps.sh
./+mkLinkBuildGradle.sh

src/test/ZmakeGcc/All_Test/TestSimple.jzTc.sh
src/test/ZmakeGcc/All_Test/TestComplex.jzTc.sh

##The jzTc.cmd does the task of build and test:
#java -jar libs/vishiaBase.jar jzTc.cmd

