#pragma once
#include "afxwin.h"

class CLgbCommandLineInfo :
	public CCommandLineInfo
{

public:
	CLgbCommandLineInfo(void);
	~CLgbCommandLineInfo(void);
	int dummy(void);

	void ParseParam( const char* pszParam, BOOL bFlag, BOOL bLast );
	CString m_csFullProjectFilePath;
	CString m_csLayoutFilePath;

protected:

};
