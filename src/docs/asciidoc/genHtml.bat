:loop
cls
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/emC_approach_en.adoc ../../../../html

::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/TestOrg/GitTestEnv_en.adoc ../../../../html/TestOrg
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/TestOrg/testStrategie_en.adoc ../../../../html/TestOrg
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/TestOrg/TEST_TRUE_en.adoc ../../../../html/TestOrg

::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/applstdef_emC_h.adoc ../../../../html/Base
call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/ObjectJc_en.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/LangExt_en.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC//Base/MemC_Alloc.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/types_def_common_h.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/StringJc_src.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/StringJc_en.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/ClassJc_en.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/ThCxtExc_emC.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/VirtualOp.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Ctrl/Overview.adoc ../../../../html/Ctrl
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/OSHAL/Serial_HAL.adoc ../../../../html/OSHAL
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Examples_Course/Examples_MSVS.adoc ../../../../html/Examples_Course
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Ctrl/OrthBandpass.adoc ../../../../html/Ctrl
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Ctrl/WaveMngAvg.adoc ../../../../html/Ctrl
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Ctrl/PIDctrl.adoc ../../../../html/Ctrl
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Style/NoLibs.adoc ../../../../html/Style
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Inspc/InspcOnTarget.adoc ../../../../html/Inspc
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Inspc/ReflectionGenerator.adoc ../../../../html/Inspc
echo done
pause
goto :loop

