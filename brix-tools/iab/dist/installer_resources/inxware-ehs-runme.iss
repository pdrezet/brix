;
; This is the common component of the installer setup script. It is referenced
; either by the inxwareTools or one of the inxwareTools_<target> installers.
;
; This file contains features that are common to all inxware installations

[Setup]
DefaultGroupName=inx
Compression=lzma
SolidCompression=yes
OutputDir="../installers"
OutputBaseFilename=setup-inxware-windows-runtime
ChangesAssociations=yes
LicenseFile="../info/licence.rtf"
WizardImageFile="ripple.bmp"
WizardSmallImageFile="inxlogo-2.0-85-px-square-wide.bmp"
VersionInfoCompany="inx limited"
VersionInfoVersion=1.0.0.1
AppVerName=inxware ehs (application runtime)
AppName=inxware ehs
UsePreviousAppDir=yes
;DefaultDirName={pf}\inx\ehs\win\    - doesn't work on WIndows7 & Vista
DefaultDirName={userappdata}\inx\ehs\win\
VersionInfoDescription="Installer for inxware ehs (BETA release)"

[files]
Source: "..\info\licence.pdf"; DestDir: "{app}";
Source: "..\info\licence.rtf"; DestDir: "{app}";
Source: "..\info\readme_ehs.txt"; DestDir: "{app}";

[Icons]
Name: "{group}\inxware\readme"; Filename: "{app}\readme_ehs.txt";

#include "inxware_ehs_common_gst_windows.iss"





