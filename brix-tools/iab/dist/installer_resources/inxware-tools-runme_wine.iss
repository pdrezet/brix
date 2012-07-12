
; Load up the tools and the runtime.
; may need to avoid collisions???

;
; This is the installer setup script for inxwareTools (i.e. tools and Windows target only)
; Most of the setup info is stored in inxwareTools_common.iss. This file contains only
; features that are specific to this installer.
;
; Use Inno Setup v5.1.8 to create the installer corresponding to this script.

;{pf} Program Files
[Setup]
OutputBaseFilename=setup-inxware-tools-with-linux-runtime
AppVerName=inxware version 1.0.0 Beta
AppName=inxware Tools
; for Win7 compatability putting everything in user data, so EHS can write user data
; DefaultDirName={pf}\inx\tools
UsePreviousAppDir=no
DefaultDirName={userappdata}\inx\tools\
VersionInfoDescription="Installer for inxware Tools v1.0.0.1B4"
DefaultGroupName=inx
LicenseFile="..\info\licence.rtf"
WizardImageFile="ripple.bmp"
WizardSmallImageFile="inxlogo-2.0-85-px-square-wide.bmp"
VersionInfoCompany="inx Ltd"
VersionInfoVersion=1.0.0.1

[Files]
Source: "..\info\readme.txt"; DestDir: "{app}";
Source: "..\info\licence.pdf"; DestDir: "{app}";
;Source: "..\info\licence.rtf"; DestDir: "{app}";

;Dirs section contains directories created in the application
[Dirs]
Name: "{app}\userdefined"
Name: "{app}\temp"
Name: "{userdocs}\inxware Projects"

[Icons]
Name: "{group}\inxware Tools\inxware Application Builder"; Filename: "{app}\bin\inxware Application Builder.exe";
Name: "{group}\inxware Tools\inxware GUI Builder"; Filename: "{app}\bin\inxware GUI Builder.exe";
Name: "{group}\inxware Tools\README"; Filename: "{app}\readme.txt";
Name: "{group}\inxware Tools\Tutorial"; Filename: "{app}\Tutoral_inxware.pdf";
Name: "{group}\inxware Tools\Uninstall inxware"; Filename: "{uninstallexe}"

[UninstallDelete]
Type: files; Name: "{app}\licence.pdf"
Type: files; Name: "{app}\licence.rtf"
Type: files; Name: "{app}\readme.txt";

#include "inxware_tools_common.iss" 
#include "inxware_ehs_linux_common.iss" 
;; note this maybe replaced with the rpm installer so that files can be made unix executable
;;#include "inxware_ehs_common.iss"


