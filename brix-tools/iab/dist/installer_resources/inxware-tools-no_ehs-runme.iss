;
; This is the installer setup script for Tools (i.e. tools and Windows target only)
; Most of the setup info is stored in Tools_common.iss. This file contains only
; features that are specific to this installer.
;
; Use Inno Setup v5.1.8 to create the installer corresponding to this script.

;{pf} Program Files
[Setup]
OutputBaseFilename=setup-inxware-tools-without-runtime
AppVerName=inxware version 1.0.0 Beta
AppName=inxware Tools
; DefaultDirName={pf}\inx\tools
DefaultDirName={userappdata}\inx\ehs\win\
VersionInfoDescription="Installer for inxware Tools v1.0.0.1B4"
DefaultGroupName=inx
LicenseFile="..\info\licence.rtf"
WizardImageFile="ripple.bmp"
WizardSmallImageFile="inxlogo-2.0-85-px-square-wide.bmp"
VersionInfoCompany="inx Ltd"
VersionInfoVersion=1.0.0.1

[Files]
;Source: "manifest v2.0.0B4.txt"; DestDir: "{app}"; DestName: "manifest.txt";
Source: "..\info\readme.txt"; DestDir: "{app}";
Source: "..\info\licence.pdf"; DestDir: "{app}";


;Dirs section contains directories created in the application
[Dirs]
Name: "{app}\userdefined"
Name: "{app}\temp"
Name: "{userdocs}\inxware Projects"

[Icons]
Name: "{group}\inxware Tools\inxware Application Builder"; Filename: "{app}\bin\inxware Application Builder.exe";
Name: "{group}\inxware Tools\inxware GUI Builder"; Filename: "{app}\bin\inxware GUI Builder.exe";
Name: "{group}\inxware Tools\Readme"; Filename: "{app}\readme.txt";
Name: "{group}\inxware Tools\License"; Filename: "{app}\license.pdf";
Name: "{group}\inxware Tools\Tutorial"; Filename: "{app}\Manuals\Tutorial_inxware.pdf";
Name: "{group}\inxware Tools\Uninstall inxware"; Filename: "{uninstallexe}"

[UninstallDelete]
Type: files; Name: "{app}\license.pdf"
Type: files; Name: "{app}\license.rtf"
Type: files; Name: "{app}\readme.txt";

#include "inxware_tools_common.iss"


