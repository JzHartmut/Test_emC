if test -d  ../../src/load_tools; then
  cd ../..
  if ! test exist tools; then mkdir tools; fi
  cp src/load_tools/* tools
  cd tools
fi
echo Resolve dependencies, check tools/bomVishiaJava.txt
java -cp vishiaMinisys.jar org.vishia.minisys.GetWebfile @tools.bom ./
