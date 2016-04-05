// colourKey.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "colourKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColourKey dialog


ColourKey::ColourKey(CWnd* pParent /*=NULL*/)
	: CDialog(ColourKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(ColourKey)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ColourKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ColourKey)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColourKey, CDialog)
	//{{AFX_MSG_MAP(ColourKey)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColourKey message handlers
