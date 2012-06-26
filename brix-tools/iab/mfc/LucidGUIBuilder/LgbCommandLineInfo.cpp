#include "stdafx.h"
#include "LgbCommandLineInfo.h"
#include <cassert>

CLgbCommandLineInfo::CLgbCommandLineInfo(void)
: m_csFullProjectFilePath(_T(""))
{
}

CLgbCommandLineInfo::~CLgbCommandLineInfo(void)
{
}

int CLgbCommandLineInfo::dummy(void)
{
	return 0;
}

void CLgbCommandLineInfo::ParseParam(   
	const char* pszParam, 
	BOOL bFlag, 
	BOOL bLast )
{
	// This is somewhat cobbled!, but:
	// if '#' is present, assume that
	// b4 the # is the full project path, and after it is the gui file
	// that shouldd be opened.
	// If a # is not present, test for '.lpj' on the end of the argument, and
	// if present, assume that this is the project to be opened.

	CString dumStr = pszParam;
	CCommandLineInfo::ParseParam( pszParam, bFlag, bLast );
	int iPos;

	if( (iPos = dumStr.Find("#")) != -1 ){
		// Ensure something is to right of the #
		assert( iPos < (dumStr.GetLength() -1 ) );

		m_csFullProjectFilePath = dumStr.Left(iPos);
		m_csLayoutFilePath = dumStr.Right( dumStr.GetLength() - iPos -1 );

	}else if(dumStr.Right(4) == ".lpj" ){

		m_csFullProjectFilePath = dumStr;
		m_csLayoutFilePath = "";
	}else{

		m_csFullProjectFilePath = "";
		m_csLayoutFilePath = "";
	}
	return;
}
