#pragma once
#include "stdafx.h"

#include "LucidEnums.h"
#include "LucidConstants.h"
#include "RevisionGuru.h"
#include "../LucidApplicationBuilder/FileOperations.h"
#include "ProjFolderMinder.h"


ProjFolderMinder::ProjFolderMinder()
{
}

void ProjFolderMinder::setProjectFolder( const CString &projFolder )
{
	m_csProjDir = projFolder;
}


void ProjFolderMinder::setProjectRevision( const int &projMajorRev, const int &projMinorRev )
{
	m_iCodeMajorRev = projMajorRev;
	m_iCodeMinorRev = projMinorRev;
}


LucidErrEnum ProjFolderMinder::createProjectFolderStructure( )
{

	CFileOperation fo;

	// when overwriting existing project delete old one.
	if (fo.CheckPath(m_csProjDir)) {
		fo.Delete(m_csProjDir);
	}

	CreateDirectory(m_csProjDir, NULL);	

	// Now get list folders hat should be under proj folder.

	RevisionGuru cGuruInst;;

	RevisionGuru::FolderFileDef_t folderDef;
	cGuruInst.getProjFolderStructure( m_iCodeMajorRev, m_iCodeMinorRev, folderDef  );


	// Create directories

	for( int i=0; i<folderDef.folders.nFolders;i++ ){
		CreateDirectory(m_csProjDir + folderDef.folders.relPath[i], NULL);	
	}

	return kErr_NoErr;
}

LucidErrEnum ProjFolderMinder::assessProjectFolderStructure( CString &csMissingFolder )
{

	RevisionGuru cGuruInst;;

	RevisionGuru::FolderFileDef_t folderDef;
	cGuruInst.getProjFolderStructure( m_iCodeMajorRev, m_iCodeMinorRev, folderDef  );

	CFileOperation fo;

	// Check directories exist

	for( int i=0; i<folderDef.folders.nFolders;i++ ){
		if (!fo.CheckPath(m_csProjDir + folderDef.folders.relPath[i] )) {
			csMissingFolder = folderDef.folders.relPath[i];
			return kErr_InvalidFolderStructure;
		}
	}

	return kErr_NoErr;
}


LucidErrEnum ProjFolderMinder::moveSodl_1(void)
{

	CFileOperation fo;
	bool bSucceed;

	// Create a new sodl folder in the right place, if necessary
	if( PATH_NOT_FOUND == fo.CheckPath( m_csProjDir + SODLDIR )){
		CreateDirectory(m_csProjDir + SODLDIR, NULL);
	}

	// An old 'exports' may contain  sodl file - if so, move it to the right place.
	if( PATH_IS_FILE == fo.CheckPath( m_csProjDir + "\\exports\\t.sdl" )  ){

		bSucceed = fo.CopyFileGood( m_csProjDir + "\\exports\\", SODLFILENAME, 
										m_csProjDir + SODLDIR, SODLFILENAME );

	}

	// Now delete the old sodl folder
	bSucceed = fo.Delete( m_csProjDir + "\\SODL\\" );

	CString okDum = "NB. Automatic Project-Folder Structure Update!\nSODL folder and file has been moved, from:\n";
	okDum+= m_csProjDir;
	okDum += "\nto\n";
	okDum += m_csProjDir + DEVICEDATADIR;
	okDum += ".\n\nNB. This internal format change requires no user action";

	AfxMessageBox( okDum ); 

	return kErr_NoErr;
}


LucidErrEnum ProjFolderMinder::moveExports_1(void)
{

	CFileOperation fo;
	bool bSucceed;

	// Create a new exports folder in the right place, if necessary
	if( PATH_NOT_FOUND == fo.CheckPath( m_csProjDir + EXPORTDIR )){
		CreateDirectory(m_csProjDir + EXPORTDIR, NULL);
	}

	// An old 'exports' may contain  sodl file - if so, move it to the right place.
	if( PATH_IS_FILE == fo.CheckPath( m_csProjDir + "\\exports\\t.sdl" )  ){

		bSucceed = fo.CopyFileGood( m_csProjDir + "\\exports\\", SODLFILENAME, 
										m_csProjDir + SODLDIR, SODLFILENAME );

	}

	// Now delete the old exports folder
	bSucceed = fo.Delete( m_csProjDir + "\\exports\\" );

	CString okDum = "NB. Automatic Project-Folder Structure Update!\nexports folder and file has been moved, from:\n";
	okDum+= m_csProjDir;
	okDum += "\nto\n";
	okDum += m_csProjDir + DDATADIR;
	okDum += ".\n\nNB. This internal format change requires no user action";

	AfxMessageBox( okDum ); 

	return kErr_NoErr;
}


LucidErrEnum ProjFolderMinder::createTemp(void)
{

	CFileOperation fo;

	// Create a new 'temp' folder in the right place, if necessary
	if( PATH_NOT_FOUND == fo.CheckPath( m_csProjDir + TEMPDIR )){

		if(CreateDirectory(m_csProjDir + TEMPDIR, NULL) )
			return kErr_NoErr;
		else
			return kErr_CouldNotCreateFolder;

	}else{

		return kErr_NoErr;
	}
}

LucidErrEnum ProjFolderMinder::createLgbTemp(void)
{

	CFileOperation fo;

	// Create a new 'temp' folder in the right place, if necessary
	if( PATH_NOT_FOUND == fo.CheckPath( m_csProjDir + LGB_TEMPDIR )){

		if(CreateDirectory(m_csProjDir + LGB_TEMPDIR, NULL) )
			return kErr_NoErr;
		else
			return kErr_CouldNotCreateFolder;

	}else{

		return kErr_NoErr;
	}
}

LucidErrEnum ProjFolderMinder::CreateNlsDir(void)
{
	CFileOperation fo;

	// Create a new 'NLS' folder in the right place, if necessary
	if (PATH_NOT_FOUND == fo.CheckPath( m_csProjDir + NLSDIR)) {
		if (CreateDirectory(m_csProjDir + NLSDIR, NULL)) {
			return kErr_NoErr;
		}
		else {
			return kErr_CouldNotCreateFolder;
		}

	} else {
		return kErr_NoErr;
	}
}

LucidErrEnum ProjFolderMinder::CreateResourceDir(void)
{
	CFileOperation fo;

	// Create a new 'NLS' folder in the right place, if necessary
	if (PATH_NOT_FOUND == fo.CheckPath( m_csProjDir + RESOURCEDIR)) {
		if (CreateDirectory(m_csProjDir + RESOURCEDIR, NULL)) {
			return kErr_NoErr;
		}
		else {
			return kErr_CouldNotCreateFolder;
		}

	} else {
		return kErr_NoErr;
	}
}
