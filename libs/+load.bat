REM Java as JRE8 should be available.

REM get depending files from internet, accept if they are existing already, but check MD5
REM bom is the bill of material, what is gotten from wwww
REM Note: vishiaMinisys.jar is part of this distribution because it is initially necessary, but the MD5 is checked.
set SCRIPTDIR=%~d0%~p0

java -cp %SCRIPTDIR%/vishiaMinisys.jar org.vishia.minisys.GetWebfile @%SCRIPTDIR%/bomVishiaJava.txt %SCRIPTDIR%/


