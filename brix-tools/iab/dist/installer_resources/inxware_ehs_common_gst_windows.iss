; This is for inclusion by the part that has the set up info in for a specific install type.
; This is the common component of the installer setup script. It is referenced
; either by the inxwareTools or one of the inxwareTools_<target> installers.
;
; This file contains features that are common to all inxware installations

[Files]

Source: "..\..\TARGET_TREES\ehs_env-win_x86_gtk_gst\*"; DestDir: "{app}\EHS\ehs_env-win_x86_gtk_gst\"; Flags: recursesubdirs createallsubdirs ignoreversion;

;Dirs section contains directories created in the application
[Dirs]
;Name: "{app}\temp"

;The registry fields associate *.prg and *.gui files executables.
; Issue: we have a fight here - the latest installation takes over file
; associations.
[Registry]
; Associate .lpj with inxware Application Builder
Root: HKCR; Subkey: ".sdl"; ValueType: string; ValueName: ""; ValueData: "inxware executable"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware execitable"; ValueType: string; ValueName: ""; ValueData: "inxware executable"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware executable\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\EHS\ehs_env-win_x86_gtk_gst\bin\ehs.exe,0"; Flags: uninsdeletekey
Root: HKCR; Subkey: "inxware executable\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\EHS\ehs_env-win_x86_gtk_gst\bin\ehs.exe"" ""%1"""; Flags: uninsdeletekey
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment";ValueType: expandsz; ValueName: "Path"; ValueData: "{olddata};{app}\EHS\ehs_env-win_x86_gtk_gst\bin\cslib";Check: NeedsAddPath('{app}\EHS\ehs_env-win_x86_gtk_gst\bin\cslib')

; Establish the project root dir for inxware Application Builder
;Root: HKCR; Subkey: "inxware executable\inxwareApplicationBuilder\Project\ProjectRootDir"; ValueType: string; ValueName: ""; ValueData: """{userdocs}\inxware Projects\Examples"""; Flags: uninsdeletekey

[Setup]
ChangesEnvironment=yes
;Set the install directory of ehs

[UninstallDelete]
; Delete everything on delete except for:
; 1. Anything in Mydocuments
; 2. Anything in DEP (user created blocks for example)
Type: files; Name: "{app}\"


[Icons]
Name: "{group}\inxware\ehs"; Filename: "{app}\EHS\ehs_env-win_x86_gtk_gst\bin\ehs.exe"; WorkingDir: "{app}\EHS\ehs_env-win_x86_gtk_gst\bin";
;;Name: "{group}\inxware\Uninstall inxware runtime"; Filename: "{uninstallexe}"

[Code]
function NeedsAddPath(Param: string): boolean;
var
  OrigPath: string;
begin
  if not RegQueryStringValue(HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path', OrigPath)
  then begin
    Result := True;
    exit;
  end;
  // look for the path with leading and trailing semicolon
  // Pos() returns 0 if not found
  Result := Pos(';' + Param + ';', ';' + OrigPath + ';') = 0;
end;

