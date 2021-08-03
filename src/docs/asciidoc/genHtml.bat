:loop
::call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/OSHAL/Serial_HAL.adoc ../../../../html/OSHAL
call C:\Programs\Asciidoc\genAsciidoc2Html.bat doc_emC/Examples_Course/Examples_MSVS.adoc ../../../../html/Examples_Course
echo done
pause
goto :loop

