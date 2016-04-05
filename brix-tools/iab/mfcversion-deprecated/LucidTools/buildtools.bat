
PATH=c:\Program Files\Inno Setup 5;C:\Program Files\Microsoft Visual Studio 8\Common7\IDE;C:\Program Files\Microsoft Visual Studio 8\VC\BIN;C:\Program Files\Microsoft Visual Studio 8\Common7\Tools;%PATH%

devenv.exe /Build Release LucidTools.sln

cd ..\..\dist\installer_resources

compil32 /cc inxware-tools-runme_windows.iss

REM - compil32 /cc inxware-tools-runme_wine.iss

compil32 /cc inxware-tools-no_ehs-runme.iss

compil32 /cc inxware-ehs-runme.iss

shutdown -f -s -t 10

