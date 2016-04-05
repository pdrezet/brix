// LABUnitTest.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "../common/LabLgbBaseApp.h"

// CLABUnitTestApp:
// See LABUnitTest.cpp for the implementation of this class
//

class CLABUnitTestApp : public CLabLgbBaseApp
{
public:
	CLABUnitTestApp();
	BOOL GetInstallationDir(char * workDir);
	BOOL GetInstallationDir( CString &installationDir );

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLABUnitTestApp theApp;