:loop
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/OSHAL/Serial_HAL.adoc ../../../../html/OSHAL
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Examples_Course/Examples_MSVS.adoc ../../../../html/Examples_Course
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Ctrl/OrthBandpass.adoc ../../../../html/Ctrl
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Ctrl/Overview.adoc ../../../../html/Ctrl
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/applstdef_emC_h.adoc ../../../../html/Base
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/types_def_common_h.adoc ../../../../html/Base
call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/StringJc_src.adoc ../../../../html/Base
call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Base/StringJc_en.adoc ../../../../html/Base
echo done
pause
goto :loop

