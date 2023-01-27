if test -d  ../../src/load_tools; then cd ../..; fi  
if ! test -d tools; then mkdir tools; fi
cp src/load_tools/+load_tools.sh tools
cp src/load_tools/tools.bom tools
cp src/load_tools/vishiaMinisys.jar tools
cd tools

echo Resolve dependencies, check tools/bomVishiaJava.txt
echo dir=$pwd 
java -cp vishiaMinisys.jar org.vishia.minisys.GetWebfile @tools.bom ./
