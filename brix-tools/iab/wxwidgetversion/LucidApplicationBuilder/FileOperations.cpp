/** \file	FileOperations.cpp
			Project: FopDemo\n
			Project type: MFC App\n
			Author: Vinnichenko Alexey\n
			E-mail: subj@mail.ru\n
			Description: Implementation of CFileOperation class and CFileExeption class.
*/ 

//#include "stdafx.h" 
#include "Resource.h" 
#include <cassert> 
#include "FileOperations.h" 
#ifdef __POSIX_C__
#include <dirent.h>
#endif
#include <wx/filename.h>


//************************************************************************************************************
#ifndef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
CFExeption::CFExeption(unsigned int dwErrCode)
{
	void* lpMsgBuf;
#ifdef __INX_DONE_ERRORMESSAGING
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			      NULL, dwErrCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	m_sError = (char*)lpMsgBuf;
	LocalFree(lpMsgBuf);
	m_dwError = dwErrCode;
#endif
}


CFExeption::CFExeption(INXString sErrText)
{
	m_sError = sErrText;
	m_dwError = 0;
}
#endif

//************************************************************************************************************

CFileOperation::CFileOperation()
{
	Initialize();
}


void CFileOperation::Initialize()
{
	m_sError.Append(wxT("No error"));
	m_dwError = 0;
	m_bAskIfReadOnly = true;
	m_bOverwriteMode = false;
	m_bAborted = false;
	m_iRecursionLimit = -1;
}

#ifndef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
void CFileOperation::DoDelete(INXString sPathName)
{
	
	INXString sPath = sPathName;

	if (CheckPath(sPath) == PATH_IS_FILE)
	{
		if (!CanDelete(sPath)) 
		{
			m_bAborted = true;
			return;
		}
		if (remove(sPath)) throw new CFExeption("Couldn't remove path");
		return;
	}
	/* else this is a directory */
	PreparePath(sPath);
	sPath += "*.*";
#ifdef __MFC_
	CFileFind ff;
	bool bRes = ff.FindFile(sPath);
	while(bRes)
	{
		bRes = ff.FindNextFile();
		if (ff.IsDots()) continue;
		if (ff.IsDirectory())
		{
			sPath = ff.GetFilePath();
			DoDelete(sPath);
		}
		else DoDelete(ff.GetFilePath());
	}
	ff.Close();
	if (!RemoveDirectory(sPathName) && !m_bAborted) throw new CFExeption(GetLastError());
#else
#ifdef __POSIX_C__
	DIR *theFolder = opendir(sPath);
	struct dirent *next_file;
	char filepath[2048];

	while ( (next_file = readdir(theFolder)) != NULL )
	{
		// build the path for each file in the folder
		sprintf(filepath, "%s/%s", "path/of/folder", next_file->d_name);
		remove(filepath);
	}
	closedir(theFolder);
#else 
	// @todo:
	//#warning "Remove Directory is not implemented"
#endif
#endif
}


void CFileOperation::DoFolderCopy(INXString sSourceFolder, INXString sDestFolder, bool bDelteAfterCopy)
{
#ifdef __INX_DONE_FOLDER COPY	
	CFileFind ff;
	INXString sPathSource = sSourceFolder;
	BOOL bRes = ff.FindFile(sPathSource);
	while (bRes)
	{
		bRes = ff.FindNextFile();
		if (ff.IsDots()) continue;
		if (ff.IsDirectory()) // source is a folder
		{
			// ignore .svn folders
			if (ff.GetFileName() == ".svn") continue;

			if (m_iRecursionLimit == 0) continue;
			sPathSource = (INXString)ff.GetFilePath() + INXString("\\") + INXString("*.*");
			INXString sPathDest = sDestFolder + (INXString)ff.GetFileName() + INXString("\\");
			if (CheckPath(sPathDest) == PATH_NOT_FOUND) 
			{
				if (!CreateDirectory(sPathDest, NULL))
				{
					ff.Close();
					throw new CFExeption(GetLastError());
				}
			}
			if (m_iRecursionLimit > 0) m_iRecursionLimit --;
			DoFolderCopy(sPathSource, sPathDest, bDelteAfterCopy);
		}
		else // source is a file
		{
			INXString sNewFileName = sDestFolder + (INXString)ff.GetFileName();
			DoFileCopy(ff.GetFilePath(), sNewFileName, bDelteAfterCopy);
		}
	}
	ff.Close();
#endif
}

bool CFileOperation::DeleteFolderFiles(INXString sPathName)
{

//	if( PATH_IS_FOLDER != CheckPath( sPathName ))

		//return false;int 
//		int i = 1;

//	else{

		try {
#ifdef __INX_DONE_DELETEFOLDERFILES
			CFileFind ff;
			BOOL bRes = ff.FindFile(sPathName);

			while (bRes)
			{
				bRes = ff.FindNextFile();

				if (!ff.IsDirectory()) {	// source is a folder
					DoDelete( ff.GetFilePath() );
				}

			}
#endif

		} catch(CFExeption* e) {

			m_sError = e->GetErrorText();
			m_dwError = e->GetErrorCode();
			delete e;

			if (m_dwError == 0)
				return true;
			else
				return false;

		}

		return true;

	//}
}

bool CFileOperation::Delete(INXString sPathName)
{
	try
	{
		DoDelete(sPathName);
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		if (m_dwError == 0) return true;
		return false;
	}
	return true;
}


bool CFileOperation::Rename(INXString sSource, INXString sDest)
{
	try
	{
		DoRename(sSource, sDest);
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		return false;
	}
	return true;
}


void CFileOperation::DoRename(INXString sSource, INXString sDest)
{
	if (rename(sSource, sDest)) throw new CFExeption("Couldn't rename file");
}


void CFileOperation::DoCopy(INXString sSource, INXString sDest, bool bDelteAfterCopy)
{
	CheckSelfRecursion(sSource, sDest);
	// source not found
	if (CheckPath(sSource) == PATH_NOT_FOUND)
	{
		INXString sError = sSource + INXString(" not found");
		throw new CFExeption(sError);
	}
	// dest not found
	if (CheckPath(sDest) == PATH_NOT_FOUND)
	{
		INXString sError = sDest + INXString(" not found");
		throw new CFExeption(sError);
	}
	// folder to file
	if (CheckPath(sSource) == PATH_IS_FOLDER && CheckPath(sDest) == PATH_IS_FILE) 
	{
		throw new CFExeption("Wrong operation");
	}
#ifdef __INX_DONE_CFLILEFIND
	// folder to folder
	if (CheckPath(sSource) == PATH_IS_FOLDER && CheckPath(sDest) == PATH_IS_FOLDER) 
	{
		CFileFind ff;
		INXString sError = sSource + INXString(" not found");
		PreparePath(sSource);
		PreparePath(sDest);
		sSource += "*.*";
		if (!ff.FindFile(sSource)) 
		{
			ff.Close();
			throw new CFExeption(sError);
		}
		if (!ff.FindNextFile()) 
		{
			ff.Close();
			throw new CFExeption(sError);
		}
		INXString sFolderName = ParseFolderName(sSource);
		if (!sFolderName.IsEmpty()) // the source is not drive
		{
			sDest += sFolderName;
			PreparePath(sDest);
			if (!CreateDirectory(sDest, NULL))
			{
				unsigned int dwErr = GetLastError();
				if (dwErr != 183)
				{
					ff.Close();
					throw new CFExeption(dwErr);
				}
			}
		}
		ff.Close();
		DoFolderCopy(sSource, sDest, bDelteAfterCopy);
	}
#endif
	// file to file
	if (CheckPath(sSource) == PATH_IS_FILE && CheckPath(sDest) == PATH_IS_FILE) 
	{
		DoFileCopy(sSource, sDest);
	}
	// file to folder
	if (CheckPath(sSource) == PATH_IS_FILE && CheckPath(sDest) == PATH_IS_FOLDER) 
	{
		PreparePath(sDest);
		char drive[MAX_PATH], dir[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
		_splitpath_s(sSource, drive, dir, name, ext);
		sDest = sDest + INXString(name) + INXString(ext);
		DoFileCopy(sSource, sDest);
	}
}


void CFileOperation::DoFileCopy( INXString sSourceFile, INXString sDestFile, const bool bDeleteAfterCopy, const bool bUpdateAfterCopy )
{
#ifdef __INX_COPYFILE_DONE
	bool bOvrwriteFails = FALSE;
	if (!m_bOverwriteMode)
	{
		while (IsFileExist(sDestFile)) 
		{
			sDestFile = ChangeFileName(sDestFile);
		}
		bOvrwriteFails = TRUE;
	}
	if (!CopyFile(sSourceFile, sDestFile, bOvrwriteFails)) throw new CFExeption(GetLastError());

	if (bDeleteAfterCopy)
	{
		DoDelete(sSourceFile);
	}

	if( bUpdateAfterCopy ) {

		TCHAR psFileName[300];
		_tcscpy_s( psFileName, 300, _T(sDestFile) );	

		CFileStatus status;
		CTime dummyTime;

		CFile::GetStatus( psFileName, status );
		status.m_mtime = CTime::GetCurrentTime();
		CFile::SetStatus( psFileName, status );

	}
#endif
}


bool CFileOperation::CopyFileGood(
							  const INXString &sSourceFolder, 
							  const INXString &sSourceFile,
							  const INXString &sDestFolder, 
							  const INXString &sDestFile )
{

	INXString fullSource = sSourceFolder + sSourceFile;

	// Check folders are terminated with a backslash.
	assert(sSourceFolder.GetAt(sSourceFolder.GetLength()-1) == '\\');
	assert(sDestFolder.GetAt(sDestFolder.GetLength()-1) == '\\');

	if (CheckPath(fullSource) == PATH_NOT_FOUND)
	{
		INXString sError = fullSource + INXString(" not found");
		throw new CFExeption(sError);
	}

	// folder to file
	if (CheckPath(sDestFolder) != PATH_IS_FOLDER) 
	{
		INXString sError = sDestFolder + INXString(" not found");
		throw new CFExeption(sError);
	}

	INXString fullDest = sDestFolder + sDestFile;

	DoFileCopy( fullSource, fullDest );

	return true;
}

bool CFileOperation::Copy(INXString sSource, INXString sDest)
{
	if (CheckSelfCopy(sSource, sDest)) return true;
	bool bRes;
	try
	{
		DoCopy(sSource, sDest);
		bRes = true;
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		if (m_dwError == 0) bRes = true;
		bRes = false;
	}
	m_iRecursionLimit = -1;
	return bRes;
}


bool CFileOperation::Replace(INXString sSource, INXString sDest)
{
	if (CheckSelfCopy(sSource, sDest)) return true;
	bool bRes;
	try
	{
		bool b = m_bAskIfReadOnly;
		m_bAskIfReadOnly = false;
		DoCopy(sSource, sDest, true);
		DoDelete(sSource);
		m_bAskIfReadOnly = b;
		bRes = true;
	}
	catch(CFExeption* e)
	{
		m_sError = e->GetErrorText();
		m_dwError = e->GetErrorCode();
		delete e;
		if (m_dwError == 0) bRes = true;
		bRes = false;
	}
	m_iRecursionLimit = -1;
	return bRes;
}


INXString CFileOperation::ChangeFileName(INXString sFileName)
{
	INXString sName, sNewName, sResult="";
	char drive[MAX_PATH];
	char dir  [MAX_PATH];
	char name [MAX_PATH];
	char ext  [MAX_PATH];
#ifdef __INX_DONE_RENAME 
	_splitpath_s((LPCTSTR)sFileName, drive, dir, name, ext);
	sName = name;

	int pos = sName.Find("Copy ");
	if (pos == -1)
	{
		sNewName = INXString("Copy of ") + sName + INXString(ext);
	}
	else
	{
		int pos1 = sName.Find('(');
		if (pos1 == -1)
		{
			sNewName = sName;
			sNewName.Delete(0, 8);
			sNewName = INXString("Copy (1) of ") + sNewName + INXString(ext);
		}
		else
		{
			INXString sCount;
			int pos2 = sName.Find(')');
			if (pos2 == -1)
			{
				sNewName = INXString("Copy of ") + sNewName + INXString(ext);
			}
			else
			{
				sCount = sName.Mid(pos1 + 1, pos2 - pos1 - 1);
				sName.Delete(0, pos2 + 5);
				int iCount = atoi((LPCTSTR)sCount);
				iCount ++;
				sNewName.Format("%s%d%s%s%s", "Copy (", iCount, ") of ", (LPCTSTR)sName, ext);
			}
		}
	}

	sResult = INXString(drive) + INXString(dir) + sNewName;
#endif
	return sResult;
}


bool CFileOperation::IsFileExist(INXString sPathName)
{
#ifdef __INX_DONE_FILEEXISTS
	HANDLE hFile;
	hFile = CreateFile(sPathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return false;
	CloseHandle(hFile);
#endif
	return true;
}


#endif
int CFileOperation::CheckPath(INXString sPath)
{
	/*
	unsigned int dwAttr = GetFileAttributes(sPath);

	if (dwAttr == 0xffffffff) 
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_PATH_NOT_FOUND) {
			return PATH_NOT_FOUND;
		}else{
			return PATH_ERROR;
		}
	}

	if (dwAttr & FILE_ATTRIBUTE_DIRECTORY) {
		return PATH_IS_FOLDER;
	}else{
		return PATH_IS_FILE;
	}*/

	wxFileName dwAttr(sPath);
	if(dwAttr.IsDir()){
		if (!dwAttr.DirExists())
			return PATH_NOT_FOUND;
		else
			return PATH_IS_FOLDER;
	}else{
		if(!dwAttr.FileExists())
			return PATH_NOT_FOUND;
		else
			return PATH_IS_FILE;
	}	
}


#ifndef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
void CFileOperation::PreparePath(INXString &sPath)
{
	if(sPath.Right(1) != "\\") sPath += "\\";
}


bool CFileOperation::CanDelete(INXString sPathName)
{
#ifdef __INX_DONE_CANDELETE
	unsigned int dwAttr = GetFileAttributes(sPathName);
	if (dwAttr == -1) return false;
	if (dwAttr & FILE_ATTRIBUTE_READONLY)
	{
		if (m_bAskIfReadOnly)
		{
			INXString sTmp = sPathName;
			int pos = sTmp.ReverseFind('\\');
			if (pos != -1) sTmp.Delete(0, pos + 1);
			INXString sText = sTmp + INXString(" is read olny. Do you want delete it?");
			int iRes = MessageBox(NULL, sText, _T("Warning"), MB_YESNOCANCEL | MB_ICONQUESTION);
			switch (iRes)
			{
				case IDYES:
				{
					if (!SetFileAttributes(sPathName, FILE_ATTRIBUTE_NORMAL)) return false;
					return true;
				}
				case IDNO:
				{
					return false;
				}
				case IDCANCEL:
				{
					m_bAborted = true;
					throw new CFExeption(0);
					return false;
				}
			}
		}
		else
		{
			if (!SetFileAttributes(sPathName, FILE_ATTRIBUTE_NORMAL)) return false;
			return true;
		}
	}
#endif
	return true;
}


INXString CFileOperation::ParseFolderName(INXString sPathName)
{
	INXString sFolderName = sPathName;
	int pos = sFolderName.ReverseFind('\\');
	if (pos != -1) sFolderName.Delete(pos, sFolderName.GetLength() - pos);
	pos = sFolderName.ReverseFind('\\');
	if (pos != -1) sFolderName = sFolderName.Right(sFolderName.GetLength() - pos - 1);
	else sFolderName.Empty();
	return sFolderName;
}


void CFileOperation::CheckSelfRecursion(INXString sSource, INXString sDest)
{
	if (sDest.Find(sSource) != -1)
	{
		int i = 0, count1 = 0, count2 = 0;
		for(i = 0; i < sSource.GetLength(); i ++)	if (sSource[i] == '\\') count1 ++;
		for(i = 0; i < sDest.GetLength(); i ++)	if (sDest[i] == '\\') count2 ++;
		if (count2 >= count1) m_iRecursionLimit = count2 - count1;
	}
}


bool CFileOperation::CheckSelfCopy(INXString sSource, INXString sDest)
{
	bool bRes = false;
	if (CheckPath(sSource) == PATH_IS_FOLDER)
	{
		INXString sTmp = sSource;
		int pos = sTmp.ReverseFind('\\');
		if (pos != -1)
		{
			sTmp.Delete(pos, sTmp.GetLength() - pos);
			char *tempstr = sDest;
			if (sTmp.CompareNoCase(tempstr) == 0) bRes = true;
		}
	}
	return bRes;
}

#ifdef __INX_WE_DONETNEEDTHESE
void CFileOperation::getStatus( const INXString &csFileName, CFileStatus & status )
{
	CFile::GetStatus( csFileName, status ); 
}

DBTIMESTAMP CFileOperation::getLastUpdate( const INXString &csFileName )
{
	CFileStatus status;
	DBTIMESTAMP ts;

	CFile::GetStatus( csFileName, status ); 

	status.m_mtime.GetAsDBTIMESTAMP( ts );
	return ts;
}

INXString CFileOperation::getExecutablePath(LPCTSTR lpFileName)
{
	LPTSTR lpBuffer;
	LPTSTR* lpFilePart;
	::SearchPathA(NULL, "RTA-TRACE.exe", NULL,1024,lpBuffer,lpFilePart);
	//LPTSTR tmp = *(LPTSTR*)lpFilePart;
	//csTmp.Compare(lpBuffer);
	//return (INXString)lpFilePart;
	return "";
}
#endif
#endif
