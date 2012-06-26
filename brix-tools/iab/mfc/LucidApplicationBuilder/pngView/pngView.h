// pngView.h : main header file for the pngView DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CpngViewApp
// See pngView.cpp for the implementation of this class
//

class CpngViewApp : public CWinApp
{
public:
	CpngViewApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
