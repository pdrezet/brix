/** \file	FileOperations.h                   
			Project: FopDemo\n
			Project type: MFC App\n
			Author: Vinnichenko Alexey\n
			E-mail: subj@mail.ru\n
			Description: Declaration of CFileOperation class and CFileExeption class.
*/ 

#pragma once

#define PATH_ERROR			-1
#define PATH_NOT_FOUND		0
#define PATH_IS_FILE		1
#define PATH_IS_FOLDER		2

#include "Porting_Classes/INXString.h"

class CFExeption
{
public:
	CFExeption(DWORD dwErrCode);
	CFExeption(INXString sErrText);
	INXString GetErrorText() {return m_sError;}
	DWORD GetErrorCode() {return m_dwError;}

private:
	INXString m_sError;
	DWORD m_dwError;
};


//*****************************************************************************************************

class CFileOperation
{
public:
	CFileOperation(); // constructor
	bool Delete(INXString sPathName); // delete file or folder
	bool DeleteFolderFiles(INXString sPathName); // delete file-contents of a folder
	bool Copy(INXString sSource, INXString sDest); // copy file or folder
	bool CopyFileGood(const INXString &sSourceFolder, 
				  const INXString &sSourceFile,
				  const INXString &sDestFolder, 
				  const INXString &sDestFile );

	bool Replace(INXString sSource, INXString sDest); // move file or folder
	bool Rename(INXString sSource, INXString sDest); // rename file or folder
	INXString GetErrorString() {return m_sError;} // return error description
	DWORD GetErrorCode() {return m_dwError;} // return error code
	void ShowError() // show error message
		{MessageBox(NULL, m_sError, _T("Error"), MB_OK | MB_ICONERROR);}
	void SetAskIfReadOnly(bool bAsk = true) // sets behavior with readonly files(folders)
		{m_bAskIfReadOnly = bAsk;}
	bool IsAskIfReadOnly() // return current behavior with readonly files(folders)
		{return m_bAskIfReadOnly;}
	bool CanDelete(INXString sPathName); // check attributes
	void SetOverwriteMode(bool bOverwrite = false) // sets overwrite mode on/off
		{m_bOverwriteMode = bOverwrite;}
	bool IsOverwriteMode() {return m_bOverwriteMode;} // return current overwrite mode
	int CheckPath(INXString sPath);
	bool IsAborted() {return m_bAborted;}
	INXString getExecutablePath(LPCTSTR lpFileName);

protected:
	void DoDelete(INXString sPathName);
	void DoCopy(INXString sSource, INXString sDest, bool bDelteAfterCopy = false);
	void DoFileCopy(INXString sSourceFile, INXString sDestFile, bool bDeleteAfterCopy=false, const bool bUpdateAfterCopy=true );
	void DoFolderCopy(INXString sSourceFolder, INXString sDestFolder, bool bDelteAfterCopy = false);
	void DoRename(INXString sSource, INXString sDest);
	bool IsFileExist(INXString sPathName);
	void PreparePath(INXString &sPath);
	void Initialize();
	void CheckSelfRecursion(INXString sSource, INXString sDest);
	bool CheckSelfCopy(INXString sSource, INXString sDest);
	INXString ChangeFileName(INXString sFileName);
	INXString ParseFolderName(INXString sPathName);

private:
	INXString m_sError;
	DWORD m_dwError;
	bool m_bAskIfReadOnly;
	bool m_bOverwriteMode;
	bool m_bAborted;
	int m_iRecursionLimit;
	void getStatus( const INXString &csFileName, CFileStatus & status );
	DBTIMESTAMP getLastUpdate( const INXString &csFileName );
};


//*****************************************************************************************************

