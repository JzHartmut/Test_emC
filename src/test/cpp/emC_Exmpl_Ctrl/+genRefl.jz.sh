#@echo off
#REM start problem: The batch needs the zbnf.jar File. Either the ZBNFJAX_HOME environment variable is set already,
#REM or it is set via a found setZBNFJAX_HOME.bat, or it is on D:\vishia... or you should adapt it.
#call setZBNFJAX_HOME.bat
#if "%ZBNFJAX_HOME%" == "" set ZBNFJAX_HOME=../../zbnfjax

#It is the path if this sources are part of test_emC         
if ! test -f ../../../../libs/vishiaBase.jar; then ../../../../libs/+load.sh; fi
export JAR=../../../../libs/vishiaBase.jar

java -cp $JAR org.vishia.jztxtcmd.JZtxtcmd $0
exit                  

==JZtxtcmd==

include ../../../main/cpp/src_emC/make/scriptsCommon/Cheader2Refl.jztxt.cmd; 
currdir=<:><&scriptdir><.>;

Fileset headers = ( ..:emC_Exmpl_Ctrl/*.h);

Fileset allHeaders = 
( ..:emC_Exmpl_Ctrl/*.h
, ../../../main/cpp/src_emC:emC/Ctrl/PIDf_Ctrl_emC.h
, ../../../main/cpp/src_emC:emC/Base/Time_emC.h
);

main()
{
  //mkdir T:/header;
  zmake "genRefl/*.crefl" := genReflection(./:&headers); ##, html="T:/header"); 

  zmake "genRefl/emC_Exmpl_Ctrl.refl.bin" := genReflection(./:&allHeaders ##, html="T:/header"
  , fileBin = <:>genRefl/emC_Exmpl_Ctrl.refl.bin<.>
  , fileOffs = <:>genRefl/emC_Exmpl_Ctrl_reflOffs<.>
  ); 

  <+out>success<.+n>

}

