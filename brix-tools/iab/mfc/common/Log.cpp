#include "stdafx.h"
#include "Log.h"
#include "LabLgbBaseApp.h"

FILE* Log::c_pFile;

Log::Log(void)
{
	m_bOpen = FALSE;
	c_pFile = NULL;
}

Log::~Log(void)
{
}

bool Log::Open(CString csFileName)
{
	bool bRet = FALSE;
	CString csInstallDir;
	CLabLgbBaseApp *pBaseApp = (CLabLgbBaseApp *) AfxGetApp();

	pBaseApp->GetInstallationBaseDir(csInstallDir);
	CString csFilePath = csInstallDir + LOGDIR + csFileName;
	CString csTmp;

	c_pFile = NULL;
	c_pFile = fopen(csFilePath,"w");
	
	if (c_pFile) {
		m_bOpen = TRUE;
		bRet = TRUE;
	}

	return bRet;
}

bool Log::Close()
{
	fclose(c_pFile);
	m_bOpen = FALSE;
	return TRUE;
}

bool Log::IsOpen()
{
	return m_bOpen;
}

void Log::WriteLogMsg(const CString csMsg)
{
	if (c_pFile) {
		fprintf(c_pFile,"%s\n", csMsg);
	}
}