@echo off
REM TEST: set the PATH without knowledge of git.
::set PATH=C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\iCLS\;C:\Program Files\Intel\Intel(R) Management Engine Components\iCLS\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\WINDOWS\system32\config\systemprofile\.dnx\bin;C:\Program Files\Microsoft DNX\Dnvm\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files (x86)\Windows Kits\10\Windows Performance Toolkit\;c:\Programs\Mathworks_2019a\bin;C:\Users\hartmut\AppData\Local\Microsoft\WindowsApps
::set PATH=C:\Program Files\git\mingw64\bin;%PATH%
set HOMEPATH=\vishia\HOME
set HOMEDRIVE=D:
::sh.exe --login -i
::"C:\Program Files\git\bin\sh.exe" --help
"C:\Program Files\git\bin\sh.exe"
::"C:\Program Files\git\git-bash.exe"
::"C:\Program Files\git\git-cmd.exe"
::pause

