;
; This is the common component of the installer setup script. It is referenced
; either by the inxwareTools or one of the inxwareTools_<target> installers.
;
; This file contains features that are common to all inxware installations

[Setup]
Compression=lzma
SolidCompression=yes
OutputDir="..\installers"
ChangesAssociations=yes


;Files section contains source directories and destination directories
;Flags: ignorerevision will overwite existing files
;Flags: recursesubdirs will retrieve sub directories
[Files]
Source: "..\bin\LucidApplicationBuilderRelease.exe"; DestDir: "{app}\bin"; DestName: "inxware Application Builder.exe"; Flags: ignoreversion
Source: "..\bin\LucidGUIBuilderRelease.exe"; DestDir: "{app}\bin"; DestName: "inxware GUI Builder.exe"; Flags: ignoreversion
;Source: "..\bin\RemoteControl.exe"; DestDir: "{app}\bin"; DestName: "Remote Control.exe"; Flags: ignoreversion
Source: "..\bin\NationalLanguageSupport.exe"; DestDir: "{app}\bin"; DestName: "NationalLanguageSupport.exe"; Flags: ignoreversion
;Source: "..\bin\ehs_win_x86.exe"; DestDir: "{app}\bin";  DestName: "ehs_win_x86.exe"; Flags: ignoreversion   ; moved to inxware_Tools.iss
Source: "..\defaultHelp.html"; DestDir: "{app}\"; DestName: "defaultHelp.html"; Flags: ignoreversion

Source: "..\fonts\*"; DestDir: "{app}\Fonts"; Flags: recursesubdirs createallsubdirs ignoreversion;
Source: "..\BMP\*"; DestDir: "{app}\BMP"; Flags: recursesubdirs createallsubdirs ignoreversion;
Source: "..\IDF\*"; DestDir: "{app}\IDF"; Flags: recursesubdirs createallsubdirs ignoreversion;
Source: "..\DEP\*"; DestDir: "{app}\DEP"; Flags: recursesubdirs createallsubdirs ignoreversion;
Source: "..\CDF\*"; DestDir: "{app}\CDF"; Flags: recursesubdirs createallsubdirs ignoreversion;
;Source: "..\RTA-Trace\header.rta"; DestDir: "{app}\RTA-Trace";
Source: "..\Images\*"; DestDir: "{app}\Images"; Flags: recursesubdirs createallsubdirs ignoreversion;
Source: "..\manuals\*"; DestDir: "{app}\Manuals"; Flags: recursesubdirs createallsubdirs ignoreversion;
Source: "..\config\*"; DestDir: "{app}\config"; Flags: recursesubdirs createallsubdirs ignoreversion;
;Source: "..\Examples\*"; DestDir: "{app}\Examples"; Flags: recursesubdirs createallsubdirs ignoreversion;
;Source: "..\info\known_problems.txt"; DestDir: "{app}";

;package up and install any dlls
Source: "..\bin\*.dll"; DestDir: "{sys}"; CopyMode: alwaysskipifsameorolder; Flags: sharedfile

;Dirs section contains directories created in the application
[Dirs]
Name: "{app}\userdefined"
Name: "{app}\temp"
; EHS has moved to own dir outside of bin
; Name: "{app}\bin\ehs_env"
; Name: "{app}\bin\ehs_env\media"
Name: "{userdocs}\inxware Projects"

;The registry fields associate *.prg and *.gui files executables.
; Issue: we have a fight here - the latest installation takes over file
; associations.
[Registry]
; Associate .lpj with inxware Application Builder
Root: HKCR; Subkey: ".lpj"; ValueType: string; ValueName: ""; ValueData: "inxware Project File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware Project File"; ValueType: string; ValueName: ""; ValueData: "inxware Project File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware Project File\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\inxware Application Builder.EXE,0"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware Project File\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\inxware Application Builder.exe"" ""%1"""; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware Project File\shell\edit GUI\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\inxware GUI Builder.exe"" ""%1"""; Flags: uninsdeletekey
; Establish the project root dir for inxware Application Builder
Root: HKCR; Subkey: "inxware\inxwareApplicationBuilder\Project\ProjectRootDir"; ValueType: string; ValueName: ""; ValueData: """{userdocs}\inxware Projects\Examples"""; Flags: uninsdeletekey

Root: HKCR; Subkey: ".gui"; ValueType: string; ValueName: ""; ValueData: "inxware GUI File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware GUI File"; ValueType: string; ValueName: ""; ValueData: "inxware GUI File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware GUI File\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\bin\inxware GUI Builder.EXE,0"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware GUI File\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\inxware GUI Builder.exe"" ""%1"""; Flags: uninsdeletekey
;Root: HKCR; Subkey: "inxware Project File\shell\edit GUI\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\inxware GUI Builder.exe"" ""%1"""; Flags: uninsdeletekey


;Set the install directory of ehs


[UninstallDelete]
; Delete everything on delete except for:
; 1. Anything in Mydocuments
; 2. Anything in DEP (user created blocks for example)
Type: files; Name: "{app}\fonts"
Type: files; Name: "{app}\BMP"
Type: files; Name: "{app}\IDF"
Type: files; Name: "{app}\Images"
Type: files; Name: "{app}\Manuals"
Type: files; Name: "{app}\IDF"
Type: files; Name: "{app}\bin\*.exe";
Type: files; Name: "{app}\known_problems.*";






